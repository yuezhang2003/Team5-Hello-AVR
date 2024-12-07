#define F_CPU 16000000UL
#define BAUD 9600       
#define MYUBRR F_CPU / 16 / BAUD - 1
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD_GFX.h"
#include "ST7735.h"
#include <stdlib.h>
#include "uart.h"
#include <string.h>

// Timer & Button Defines
#define LED_PIN PC2
#define BUTTON_INC PD2
#define BUTTON_DEC PD3
#define BUTTON_START PD4
#define BUTTON_SHIFT PD5

// DHT11 Defines
#define SENSOR_PIN PC3
#define SENSOR_DDR DDRC
#define SENSOR_PORT PORTC
#define SENSOR_PIN_IN PINC
#define SENSOR_OK 0
#define SENSOR_FAIL 1

// RTC Defines
#define DS1307_ADDR 0xD0
#define SCL_CLOCK 100000UL
#define TWBR_VAL ((F_CPU / SCL_CLOCK - 16) / 2)

// Timer Variables
volatile uint32_t remaining_seconds = 10;
volatile uint8_t update_display = 1;
volatile uint8_t timer_running = 0;
volatile uint8_t timer_ended = 0;
volatile uint8_t time_unit = 0;
#define MAX_SECONDS 86400

// Sensor Variables
volatile uint8_t current_temp = 0;
volatile uint8_t current_humid = 0;
volatile uint8_t prev_temp = 0;
volatile uint8_t prev_humid = 0;

//pressure sensor
volatile int adc_value;

// I2C Functions for RTC

static void I2C_Init(void) {
    TWBR0 = 0x48;
    TWSR0 = 0x00;
    TWCR0 = (1 << TWEN);
}

static void I2C_Start(void) {
    TWCR0 = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
    while (!(TWCR0 & (1 << TWINT)));
}

static void I2C_Stop(void) {
    TWCR0 = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
}

static void I2C_Write(uint8_t data) {
    TWDR0 = data;
    TWCR0 = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR0 & (1 << TWINT)));
}

static uint8_t I2C_ReadACK(void) {
    TWCR0 = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
    while (!(TWCR0 & (1 << TWINT)));
    return TWDR0;
}

static uint8_t I2C_ReadNACK(void) {
    TWCR0 = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR0 & (1 << TWINT)));
    return TWDR0;
}

// RTC Helper Functions

static uint8_t BCD_To_Dec(uint8_t bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

static uint8_t Dec_To_BCD(uint8_t dec) {
    return ((dec / 10) << 4) | (dec % 10);
}

// DHT11 Functions

static void Timer2_Init(void) {
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 0;
}

static void timer2_delay_us(uint16_t us) {
    TCCR2B = (1 << CS21);
    TCNT2 = 0;
    while (TCNT2 < us * 2);
    TCCR2B = 0;
}

static void set_output_mode(void) {
    SENSOR_DDR |= (1 << SENSOR_PIN);
}

static void set_input_mode(void) {
    SENSOR_DDR &= ~(1 << SENSOR_PIN);
    SENSOR_PORT |= (1 << SENSOR_PIN);
}

static uint8_t read_pin_state(void) {
    return (SENSOR_PIN_IN & (1 << SENSOR_PIN));
}

// DHT11 Read Function

static uint8_t get_sensor_data(uint8_t *temp_value, uint8_t *humid_value) {
    uint8_t data[5] = {0};
    uint16_t timeout = 0;

    set_output_mode();
    SENSOR_PORT &= ~(1 << SENSOR_PIN);
    _delay_ms(20);
    SENSOR_PORT |= (1 << SENSOR_PIN);
    timer2_delay_us(40);
    set_input_mode();

    timeout = 0;
    while (read_pin_state() && timeout < 200) {
        timer2_delay_us(1);
        timeout++;
    }
    if (timeout >= 200) return SENSOR_FAIL;

    timeout = 0;
    while (!read_pin_state() && timeout < 200) {
        timer2_delay_us(1);
        timeout++;
    }
    if (timeout >= 200) return SENSOR_FAIL;

    timeout = 0;
    while (read_pin_state() && timeout < 200) {
        timer2_delay_us(1);
        timeout++;
    }
    if (timeout >= 200) return SENSOR_FAIL;

    for (uint8_t i = 0; i < 5; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            timeout = 0;
            while (!read_pin_state() && timeout < 200) {
                timer2_delay_us(1);
                timeout++;
            }
            if (timeout >= 200) return SENSOR_FAIL;

            timer2_delay_us(30);

            if (read_pin_state()) {
                data[i] |= (1 << (7 - j));
                timeout = 0;
                while (read_pin_state() && timeout < 200) {
                    timer2_delay_us(1);
                    timeout++;
                }
                if (timeout >= 200) return SENSOR_FAIL;
            }
        }
    }

    if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
        *humid_value = data[0];
        *temp_value = data[2];
        return SENSOR_OK;
    }

    return SENSOR_FAIL;
}

// RTC Functions

static void DS1307_ReadTime(uint8_t *hour, uint8_t *minute, uint8_t *second) {
    I2C_Start();
    I2C_Write(DS1307_ADDR);
    I2C_Write(0x00);
    I2C_Start();
    I2C_Write(DS1307_ADDR | 0x01);
    *second = BCD_To_Dec(I2C_ReadACK());
    *minute = BCD_To_Dec(I2C_ReadACK());
    *hour = BCD_To_Dec(I2C_ReadNACK());
    I2C_Stop();
}

static void DS1307_SetTime(uint8_t hour, uint8_t minute, uint8_t second) {
    I2C_Start();
    I2C_Write(DS1307_ADDR);
    I2C_Write(0x00);
    I2C_Write(Dec_To_BCD(second) & 0x7F);
    I2C_Write(Dec_To_BCD(minute));
    I2C_Write(Dec_To_BCD(hour));
    I2C_Stop();
}

// Timer and UART Functions

static void UART_Init(unsigned int baud) {
    unsigned int ubrr = F_CPU / 16 / baud - 1;
    UBRR0H = (unsigned char) (ubrr >> 8);
    UBRR0L = (unsigned char) (ubrr);
    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

static void Timer1_Init(void) {
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12) | (1 << CS10);
    OCR1A = 15624;
    TIMSK1 |= (1 << OCIE1A);
    sei();
}

// LCD Update Functions

static void Update_LCD_Time(uint8_t hour, uint8_t minute, uint8_t second) {
    static uint8_t prev_hour = 99;
    static uint8_t prev_minute = 99;
    static uint8_t prev_second = 99;
    char buffer[8];

    // Only update hour if changed
    if (hour != prev_hour) {
        snprintf(buffer, sizeof (buffer), "%02d", hour);
        LCD_drawBlock(60, 50, 70, 66, BLACK);
        LCD_drawString(60, 50, buffer, WHITE, BLACK);
        prev_hour = hour;
    }

    // Only update minute if changed
    if (minute != prev_minute) {
        snprintf(buffer, sizeof (buffer), "%02d", minute);
        LCD_drawBlock(80, 50, 90, 66, BLACK);
        LCD_drawString(80, 50, buffer, WHITE, BLACK);
        prev_minute = minute;
    }

    // Only update second if changed
    if (second != prev_second) {
        snprintf(buffer, sizeof (buffer), "%02d", second);
        LCD_drawBlock(100, 50, 110, 66, BLACK);
        LCD_drawString(100, 50, buffer, WHITE, BLACK);
        prev_second = second;
    }
}

static void Update_LCD_Seconds_Units(uint8_t seconds_units) {
    char buffer[2];
    snprintf(buffer, sizeof (buffer), "%u", seconds_units);
    LCD_drawBlock(70, 0, 78, 16, BLACK);
    LCD_drawString(70, 0, buffer, WHITE, BLACK);
}

static void Update_LCD_Seconds_Tens(uint8_t seconds_tens) {
    char buffer[2];
    snprintf(buffer, sizeof (buffer), "%u", seconds_tens);
    LCD_drawBlock(60, 0, 70, 16, BLACK);
    LCD_drawString(60, 0, buffer, WHITE, BLACK);
}

static void Update_LCD_Minutes_Units(uint8_t minutes_units) {
    char buffer[2];
    snprintf(buffer, sizeof (buffer), "%u", minutes_units);
    LCD_drawBlock(50, 0, 60, 16, BLACK);
    LCD_drawString(50, 0, buffer, WHITE, BLACK);
}

static void Update_LCD_Minutes_Tens(uint8_t minutes_tens) {
    char buffer[2];
    snprintf(buffer, sizeof (buffer), "%u", minutes_tens);
    LCD_drawBlock(40, 0, 50, 16, BLACK);
    LCD_drawString(40, 0, buffer, WHITE, BLACK);
}

static void Update_LCD_Hours_Units(uint8_t hours_units) {
    char buffer[2];
    snprintf(buffer, sizeof (buffer), "%u", hours_units);
    LCD_drawBlock(30, 0, 40, 16, BLACK);
    LCD_drawString(30, 0, buffer, WHITE, BLACK);
}

static void Update_LCD_Hours_Tens(uint8_t hours_tens) {
    char buffer[2];
    snprintf(buffer, sizeof (buffer), "%u", hours_tens);
    LCD_drawBlock(20, 0, 30, 16, BLACK);
    LCD_drawString(20, 0, buffer, WHITE, BLACK);
}

static void Display_To_LCD(uint32_t seconds) {
    char buffer[16];
    uint16_t minutes = seconds / 60;
    uint8_t hours = minutes / 60;
    minutes %= 60;
    seconds %= 60;

    snprintf(buffer, sizeof (buffer), "%02u:%02u:%02u", (unsigned int) hours,
            (unsigned int) minutes, (unsigned int) seconds);
    LCD_drawBlock(10, 0, 100, 16, BLACK);
    LCD_drawString(10, 0, buffer, WHITE, BLACK);
}

static void update_sensor_value(uint8_t value, uint8_t is_temp) {
    char msg[32];
    if (is_temp) {
        snprintf(msg, sizeof (msg), "Temp: %d C", value);
        LCD_drawString(5, 100, msg, WHITE, BLACK);
    } else {
        snprintf(msg, sizeof (msg), "Humid: %d%%", value);
        LCD_drawString(5, 120, msg, WHITE, BLACK);
    }
}

// Timer1 ISR

ISR(TIMER1_COMPA_vect) {
    static uint8_t tick_count = 0;
    tick_count++;

    if (tick_count >= 1) {
        tick_count = 0;
        if (timer_running && remaining_seconds > 0) {
            uint8_t old_seconds_units = remaining_seconds % 10;
            uint8_t old_seconds_tens = (remaining_seconds / 10) % 6;
            uint8_t old_minutes_units = (remaining_seconds / 60) % 10;
            uint8_t old_minutes_tens = (remaining_seconds / 600) % 6;
            uint8_t old_hours_units = (remaining_seconds / 3600) % 10;
            uint8_t old_hours_tens = (remaining_seconds / 36000) % 10;

            remaining_seconds--;
            update_display = 1;

            uint8_t new_seconds_units = remaining_seconds % 10;
            uint8_t new_seconds_tens = (remaining_seconds / 10) % 6;
            uint8_t new_minutes_units = (remaining_seconds / 60) % 10;
            uint8_t new_minutes_tens = (remaining_seconds / 600) % 6;
            uint8_t new_hours_units = (remaining_seconds / 3600) % 10;
            uint8_t new_hours_tens = (remaining_seconds / 36000) % 10;

            if (new_seconds_units != old_seconds_units) {
                Update_LCD_Seconds_Units(new_seconds_units);
            }
            if (new_seconds_tens != old_seconds_tens) {
                Update_LCD_Seconds_Tens(new_seconds_tens);
            }
            if (new_minutes_units != old_minutes_units) {
                Update_LCD_Minutes_Units(new_minutes_units);
            }
            if (new_minutes_tens != old_minutes_tens) {
                Update_LCD_Minutes_Tens(new_minutes_tens);
            }
            if (new_hours_units != old_hours_units) {
                Update_LCD_Hours_Units(new_hours_units);
            }
            if (new_hours_tens != old_hours_tens) {
                Update_LCD_Hours_Tens(new_hours_tens);
            }
        } else if (remaining_seconds == 0 && !timer_ended) {
            timer_ended = 1;
            timer_running = 0;
            PORTC |= (1 << LED_PIN);
            DFPlayer_SendCommandWithACK(0x11, 0x01);
        }
    }
}

// Initialize Functions

static void Button_Init(void) {
    DDRD &= ~((1 << BUTTON_INC) | (1 << BUTTON_DEC) | (1 << BUTTON_START) | (1 << BUTTON_SHIFT));
    PORTD &= ~((1 << BUTTON_INC) | (1 << BUTTON_DEC) | (1 << BUTTON_START) | (1 << BUTTON_SHIFT));
}

static void LED_Init(void) {
    DDRC |= (1 << LED_PIN);
    PORTC &= ~(1 << LED_PIN);
}

static void Check_Buttons(void) {
    static uint8_t inc_prev = 0, dec_prev = 0;
    static uint8_t start_prev = 0, shift_prev = 0;

    uint8_t inc_state = PIND & (1 << BUTTON_INC);
    uint8_t dec_state = PIND & (1 << BUTTON_DEC);
    uint8_t start_state = PIND & (1 << BUTTON_START);
    uint8_t shift_state = PIND & (1 << BUTTON_SHIFT);

    if (inc_state && !inc_prev) {
        if (time_unit == 0 && remaining_seconds < MAX_SECONDS - 1) {
            remaining_seconds += 1;
            Update_LCD_Seconds_Units(remaining_seconds % 10);
            if (remaining_seconds % 10 == 0) {
                Update_LCD_Seconds_Tens((remaining_seconds / 10) % 6);
            }
        } else if (time_unit == 1 && remaining_seconds < MAX_SECONDS - 60) {
            remaining_seconds += 60;
            Update_LCD_Minutes_Units((remaining_seconds / 60) % 10);
            if ((remaining_seconds / 60) % 10 == 0) {
                Update_LCD_Minutes_Tens((remaining_seconds / 600) % 6);
            }
        } else if (time_unit == 2 && remaining_seconds < MAX_SECONDS - 3600) {
            remaining_seconds += 3600;
            Update_LCD_Hours_Units((remaining_seconds / 3600) % 10);
            if ((remaining_seconds / 3600) % 10 == 0) {
                Update_LCD_Hours_Tens((remaining_seconds / 36000) % 10);
            }
        }
        update_display = 1;
    }

    if (dec_state && !dec_prev) {
        if (time_unit == 0 && remaining_seconds >= 1) {
            remaining_seconds -= 1;
            Update_LCD_Seconds_Units(remaining_seconds % 10);
            if (remaining_seconds % 10 == 9) {
                Update_LCD_Seconds_Tens((remaining_seconds / 10) % 6);
            }
        } else if (time_unit == 1 && remaining_seconds >= 60) {
            remaining_seconds -= 60;
            Update_LCD_Minutes_Units((remaining_seconds / 60) % 10);
            if ((remaining_seconds / 60) % 10 == 9) {
                Update_LCD_Minutes_Tens((remaining_seconds / 600) % 6);
            }
        } else if (time_unit == 2 && remaining_seconds >= 3600) {
            remaining_seconds -= 3600;
            Update_LCD_Hours_Units((remaining_seconds / 3600) % 10);
            if ((remaining_seconds / 3600) % 10 == 9) {
                Update_LCD_Hours_Tens((remaining_seconds / 36000) % 10);
            }
        }
        update_display = 1;
    }

    if (shift_state && !shift_prev) {
        time_unit = (time_unit + 1) % 3;
        LCD_drawBlock(70, 20, 150, 36, BLACK);

        if (time_unit == 0)
            LCD_drawString(70, 20, "Seconds", WHITE, BLACK);
        else if (time_unit == 1)
            LCD_drawString(70, 20, "Minutes", WHITE, BLACK);
        else if (time_unit == 2)
            LCD_drawString(70, 20, "Hours", WHITE, BLACK);
    }

    if (start_state && !start_prev) {
        if (timer_ended) {
            timer_ended = 0;
            timer_running = 0;
            remaining_seconds = 10;
            PORTC &= ~(1 << LED_PIN);
            DFPlayer_SendCommandWithACK(0x16, 0x0000);

        } else if (timer_running) {
            timer_running = 0;
        } else {
            timer_running = 1;
        }
    }

    inc_prev = inc_state;
    dec_prev = dec_state;
    start_prev = start_state;
    shift_prev = shift_state;

    _delay_ms(50);
}

typedef struct {
    uint8_t start_byte; // start bit 0x7E
    uint8_t version; //  0xFF
    uint8_t length; //  0x06
    uint8_t command; // command
    uint8_t ack; // ACK 
    uint8_t param1; // high bit
    uint8_t param2; // low bit
    uint8_t checksum_h; // check high
    uint8_t checksum_l; // check low
    uint8_t end_byte; // end bit 0xEF
} DFPlayerFrame;

void uart_init(void) {
    unsigned int ubrr = MYUBRR;

    UBRR0H = (unsigned char) (ubrr >> 8);
    UBRR0L = (unsigned char) (ubrr & 0xFF);

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0))); //
    UDR0 = data; //
    //_delay_ms(1);
}

unsigned char uart_receive(void) {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

uint8_t uart_available() {
    return (UCSR0A & (1 << RXC0));
}

void mp3(uint8_t command, uint8_t ack, uint16_t parameter) {
    uint8_t frame[10];

    frame[0] = 0x7E;
    frame[1] = 0xFF;
    frame[2] = 0x06;

    frame[3] = command;
    frame[4] = ack;
    frame[5] = (parameter >> 8) & 0xFF;
    frame[6] = parameter & 0xFF;

    uint16_t checksum = 0xFFFF - (frame[1] + frame[2] + frame[3] + frame[4] + frame[5] + frame[6]) + 1;
    frame[7] = (checksum >> 8) & 0xFF;
    frame[8] = checksum & 0xFF;

    frame[9] = 0xEF;

    for (int i = 0; i < 10; i++) {
        uart_transmit(frame[i]);
    }
}

int mp3Receive(uint8_t *buffer) {
    uint8_t index = 0;
    char init_message[] = "test\n";
    for (int i = 0; init_message[i] != '\0'; i++) {
        uart_transmit(init_message[i]);
    }

    while (index < 10) {
        if (uart_available()) {
            buffer[index++] = uart_receive();

        } else {
            return -3;
        }
    }

    if (buffer[0] != 0x7E || buffer[9] != 0xEF) {
        return -1;
    }

    uint16_t checksum = 0;
    for (int i = 1; i <= 6; i++) {
        checksum += buffer[i];
    }
    checksum = 0xFFFF - checksum + 1;
    if (((checksum >> 8) & 0xFF) != buffer[7] || (checksum & 0xFF) != buffer[8]) {
        return -2;
    }

    return buffer[3];
}

void DFPlayer_SendCommandWithACK(uint8_t command, uint16_t parameter) {
    uint8_t buffer[10];

    mp3(command, 0x01, parameter);

    int responseType = mp3Receive(buffer);

    if (responseType == 0x41) {

        char message[] = "Command executed successfully!\n";
        for (int i = 0; message[i] != '\0'; i++) {
            uart_transmit(message[i]);
        }
    } else if (responseType == 0x40) {

        char message[100];
        sprintf(message, "Error code: %02X%02X\n", buffer[5], buffer[6]);
        UART_putstring(message);
    } else {

        char message[] = "Invalid response or checksum error.\n";
        for (int i = 0; message[i] != '\0'; i++) {
            uart_transmit(message[i]);
        }
    }
}

void DFPlayer_Init() {
    _delay_ms(1000);

    //reset 0x0C
    //mp3(0x0C, 0x00, 0x00);
    DFPlayer_SendCommandWithACK(0x0C, 0x00);
    _delay_ms(3500);

    // set volume 20
    //mp3(0x06, 0x00, 20);
    DFPlayer_SendCommandWithACK(0x06, 20);
    _delay_ms(500);

    //SD Card play source
    //mp3(0x09, 0x00, 0x02);
    DFPlayer_SendCommandWithACK(0x09, 0x02);
    _delay_ms(500);

    //playback loop
    //DFPlayer_SendCommandWithACK(0x11, 0x01);

}

//pressure sensor

void pressure_adc_ini() {
    PRR0 &= ~(1 << PRADC);

    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << REFS1);

    ADCSRA |= (1 << ADPS0);
    ADCSRA |= (1 << ADPS1);
    ADCSRA |= (1 << ADPS2);

    ADMUX &= ~(1 << MUX0);
    ADMUX &= ~(1 << MUX1);
    ADMUX &= ~(1 << MUX2);
    ADMUX &= ~(1 << MUX3);

    ADCSRA |= (1 << ADATE);
    ADCSRB &= ~(1 << ADTS0);
    ADCSRB &= ~(1 << ADTS1);
    ADCSRB &= ~(1 << ADTS2);

    DIDR0 |= (1 << ADC0D);

    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADSC);

}

void pressure() {
    adc_value = ADC;
    //    if (adc_value <= 10) {
    //        PORTB &= ~(1 << PB2);
    //    } else {
    //        PORTB |= (1 << PB2);
    //    }

}

#define PRESSURE_THRESHOLD 25 // pressure sensor threshold votage

volatile uint8_t music_playing = 0; // music flag
volatile uint8_t pressure_detected = 0; // pressure sensor flag

void Stop_Music() {
    //    DFPlayer_SendCommandWithACK(0x16, 0x0000);
    //    music_playing = 0;

    if (music_playing) { 
        DFPlayer_SendCommandWithACK(0x16, 0x0000); // stop playing music
        music_playing = 0; 
        char message[] = "Music Stopped\n";
        UART_putstring(message);
    }
}

void Play_Music() {
    //    DFPlayer_SendCommandWithACK(0x11, 0x01); // 
    //    music_playing = 1;
    if (!music_playing) {
        DFPlayer_SendCommandWithACK(0x11, 0x01); // loop music playback
        music_playing = 1;
        char message[] = "Music Playing\n";
        UART_putstring(message);
    }
}
#define DEBOUNCE_THRESHOLD 10

int main(void) {
    uint8_t hour = 0, minute = 0, second = 0;
    uint8_t temp_val = 0;
    uint8_t humid_val = 0;

    lcd_init();
    LCD_setScreen(BLACK);
    LED_Init();
    Button_Init();
    UART_Init(9600);
    Timer1_Init();
    Timer2_Init();
    I2C_Init();
    //DS1307_SetTime(13, 53, 45);//ensure the time is accurate
    DFPlayer_Init();
    pressure_adc_ini();
    uint8_t previous_pressure_state = 0;
    static uint8_t debounce_counter = 0;

    // DHT11 initialization
    set_output_mode();
    SENSOR_PORT |= (1 << SENSOR_PIN);
    _delay_ms(1000);

    // LCD back screen
    LCD_drawString(10, 20, "Editing: ", WHITE, BLACK);
    LCD_drawString(70, 20, "Seconds", WHITE, BLACK);

    // RTC display area in LCD
    LCD_drawString(10, 50, "Time:", WHITE, BLACK);
    LCD_drawString(73, 50, ":", WHITE, BLACK);
    LCD_drawString(93, 50, ":", WHITE, BLACK);

    // Temperature and Humidity display area in LCD
    LCD_drawString(5, 100, "Temp: -- C", WHITE, BLACK);
    LCD_drawString(5, 120, "Humid: --%", WHITE, BLACK);

    while (1) {
        Check_Buttons();

        static uint16_t sensor_timer = 0;
        if (sensor_timer++ >= 50) {
            sensor_timer = 0;

            set_output_mode();
            SENSOR_PORT |= (1 << SENSOR_PIN);
            _delay_ms(50);

            uint8_t sensor_status = get_sensor_data(&temp_val, &humid_val);

            if (sensor_status == SENSOR_OK) {
                current_temp = temp_val;
                current_humid = humid_val;
                if (current_temp != prev_temp) {
                    update_sensor_value(current_temp, 1);
                    prev_temp = current_temp;
                }
                if (current_humid != prev_humid) {
                    update_sensor_value(current_humid, 0);
                    prev_humid = current_humid;
                }
            }
        }

        if (update_display) {
            Display_To_LCD(remaining_seconds);
            update_display = 0;
        }

        // RTC update
        DS1307_ReadTime(&hour, &minute, &second);
        Update_LCD_Time(hour, minute, second);

        if (remaining_seconds == 0 && timer_ended) {
            PORTC |= (1 << LED_PIN);
            //DFPlayer_SendCommandWithACK(0x11, 0x01); //music play

            pressure(); // update pressure value `adc_value`
            pressure_detected = (adc_value > PRESSURE_THRESHOLD);
            if (pressure_detected) {
                if (debounce_counter < DEBOUNCE_THRESHOLD) {
                    debounce_counter++;
                } else if (!music_playing) { //stable state and music isn't played
                    char debug_message[] = "Calling Play_Music\n";
                    UART_putstring(debug_message);
                    Play_Music();
                }
            } else {
                if (debounce_counter > 0) {
                    debounce_counter--;
                } else if (music_playing) { // stable state and music is playing
                    Stop_Music();
                }
            }

            //for debug
            char buffer[50];
            sprintf(buffer, "ADC: %d, Detected: %d, Music: %d\n", adc_value, pressure_detected, music_playing);
            UART_putstring(buffer);
        }

        _delay_ms(50);
    }

    return 0;
}