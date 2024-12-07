/* 
 * File:   final_pro.c
 * Author: Aurora
 *
 * Created on November 15, 2024, 11:00 AM
 */
#define F_CPU 16000000UL  
#define BAUD 9600       
#define MYUBRR F_CPU / 16 / BAUD - 1

#include <stdio.h>
#include <stdlib.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include <avr/interrupt.h>
#include <string.h>

/*
 * 
 */

volatile uint8_t last_state = 0;

void initial() {
    timer1();
    ESP32pin_int();

}

void ESP32pin_int() {
    cli();
    DDRB &= ~(1 << PB0);
    PORTB &= ~(1 << PB0);

    //Pin Change Interrupt
    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << PCINT0); // PB0 for Pin Change Interrupt

    sei();
}

ISR(PCINT0_vect) {
    _delay_ms(10);
    
    uint8_t current_state = PINB & (1 << PB0); // ??????

    if (current_state != last_state) { // ??????
        last_state = current_state;    // ????

        if (current_state) { // low to high
            motor(0); 
            _delay_ms(1000);
            motor(180);
            _delay_ms(1000);
        } else { // high to low
            motor(180);
            _delay_ms(1000);
            motor(0);
            _delay_ms(1000);
        }
    }

}

void timer1() {
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << WGM12);

    TCCR1A |= (1 << COM1A1);

    TCCR1B |= (1 << CS11);

    ICR1 = 39999; // 16MHz , 20ms (50Hz)

}

//Control servo motor to turn on/off the switch

void motor(int angle) {

    int pulse_width = 1000 + (angle * 22.22);

    OCR1A = pulse_width;
}

int main() {

    initial();
    DDRB |= (1 << PB1);

    while (1) {

    }
}

