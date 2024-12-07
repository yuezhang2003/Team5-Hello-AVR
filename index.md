<style>
  body {
      background-color: #d7e8ec; /* background */
      font-family: Arial, sans-serif;
      line-height: 1.6;
      margin: 0;
      padding: 0;
  }
  .content {
      background-color: #ffffff; /* content area */
      max-width: 900px;
      margin: 20px auto;
      padding: 20px;
      border-radius: 10px;
      box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
  }
  h1 {
      font-size: 36px;
      color: #000000; /* text color */
  }
  p {
      font-size: 18px;
      color: #000000; /* text color */
  }
</style>

<div style="background-color: #e0f7fa; padding: 30px; border-radius: 8px; text-align: center; margin-bottom: 10px;">
    <h1 style="color: #00796b; font-size: 36px;">Smart Room System</h1>
    <p style="color: #004d40; font-size: 20px;">Team 5: Xinmi Wang & Yue Zhang</p>
</div>


<nav style="background-color: #444; color: white; padding: 10px; text-align: center;">
    <a href="#videos" style="color: white; text-decoration: none; margin: 0 10px;">Videos</a>
    <a href="#images" style="color: white; text-decoration: none; margin: 0 10px;">Images</a>
    <a href="#requirements" style="color: white; text-decoration: none; margin: 0 10px;">Requirements</a>
    <a href="#results" style="color: white; text-decoration: none; margin: 0 10px;">Results</a>
    <a href="#conclusion" style="color: white; text-decoration: none; margin: 0 10px;">Conclusion</a>
</nav>

**Team Number:** 5

**Team Members:** Xinmi Wang, Yue Zhang

**GitHub Repository URL:** [https://github.com/upenn-embedded/final-project-hello-avr.git](https://github.com/upenn-embedded/final-project-hello-avr.git)

**Description of hardware:** ATmega328PB, ESP32, DFPlayer Mini MP3, DHT11 (Temperature & Humidity Sensor), Pressure sensor, DS1307 (RTC), SG92 motor, LCD, Button, Speaker

<hr style="border: 2px solid #00796b; margin: 20px 0;">

### 1. <a id="videos"></a>Videos

<div style="background: white; padding: 20px; margin: 20px 0; border-radius: 8px; box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);">
    <h2>Final Demo Video</h2>
    <a href="https://drive.google.com/file/d/1vn5B683b3LDdRKbWDvhb38bbrMS9ZKrc/view?usp=sharing">Watch Final Demo</a>
</div>

*Component Introdunction and Subsystem showcase (from MVP demo Section):*

[Components Introduction and RTC Module Verification](https://drive.google.com/file/d/18NRR7TqB4oGcTKR5yJSIYinGD1jU854A/view?usp=sharing)

[Component Introdunction](https://drive.google.com/file/d/14AzF1xIxzB-tOfQj_mY6ar0WchGikSVs/view?usp=sharing)

[Customized Clock](https://drive.google.com/file/d/1ezHeLOP1YmJTWa4lHZ1NpC6UWO31GeAL/view?usp=sharing)

[DHT11 Temperature and Humidity Sensor](https://drive.google.com/file/d/11FWbEXGUWR_x9bL63hSn0uGvAPO8yniR/view?usp=sharing)

[Pressure Sensor and Clock triger MP3 Playback](https://drive.google.com/file/d/1DQekz2rkHUmk5DuU6xqMzBGXYo3vfcFu/view?usp=sharing)

[Wireless Motor Control](https://drive.google.com/file/d/1NSKFJ0k-85PAFJGAMdcvbEJjnYR0jsOx/view?usp=sharing)


*This is code for RTC+Customized Clock+DHT11+MP3+Speaker+LCD Display: [part1Code](/Part1/part_d1.c)*

*This is code for wireless motor control: [part2Code](/Part2/final_pro.c)*

### 2. <a id="images"></a>Images

*2.1.Components:*

Atmega328PB:

![ATmeaga328PB](/images/ATmega.jpg)

ESP32 + Level Shifter :

![ESP32](/images/ESP32.jpg)

Real Time Module (Input1):

![RTC](/images/RTC.jpg)

Temperature & Humidity Sensot DHT11 (Input 2):

![DH11](/images/DHT11.jpg)

Pressure Sensor (Input 3):

![pressureSensor](/images/pressureSensor.jpg)

DFPlayer Mini MP3 (Input 4):

![mp3](/images/mp3.jpg)

Wireless Control App (Input 5):

![app](/images/app.png)

BUtton (Input 6):

![button](/images/button.jpg)


LCD (Output 1):

![LCD](/images/LCD.jpg)

![LCDoutput](/images/LCDoutput.jpg)

Speaker (Output 2):

![speaker](/images/speaker.jpg)

Motor (Output 3):

![motor](/images/motor.jpg)

*2.2.Module Connection:*

![module](/images/connection.jpg)

### 3. <a id="requirements"></a>Requirement Specifications 

- Overview
This software system is designed to enable the seamless operation of a smart bedroom automation system. It integrates features such as real-time clock display, flexible countdown timers, environmental data monitoring, automated MP3 playback, and wireless motor control. The software emphasizes modularity, ensuring efficient interaction between sensors, actuators, and the ATmega328PB microcontroller to provide a reliable and user-friendly experience.

- Users
The primary users are individuals seeking enhanced comfort and convenience in their bedroom environment. This includes students, professionals, and families looking to automate and optimize daily routines such as waking up, sleeping, and monitoring environmental conditions.

### 3.1 Software Requirements Specification (SRS)

*3.1.1. Definition*

- Countdown Timer: A timer of ATmega328PB to manage time countdown and user interactions for timing adjustments.

- I2C (Inter-Integrated Circuit): A software communication protocol to enable data exchange with peripheral such as the RTC.

- SPI (Serial Peripheral Interface): A high-speed, synchronous communication protocol used to interface with devices such as LCD.

- UART (Universal Asynchronous Receiver-Transmitter): A serial communication protocol for transmitting and receiving data, used in the project for sending command to MP3.

- PWM (Pulse Width Modulation): Software logic to generate specific waveforms for motor control

- ADC (Analog-to-Digital Converter): A software-controlled feature of the ATmega328PB used to convert analog signals from the pressure sensor into digital data for decision-making.

*3.1.2. Functionality*

- SRS 01 - The countdown timer shall decrement the time every second with a tolerance of ±0.5 seconds compared to the stopwatch in the mobile phone.

- SRS 02 - The system shall measure temperature and humidity data from the DHT11 sensor every 2 seconds, ensuring the data is accurate with checksum verification.

- SRS 03 - The MP3 playback system will start music within reasonable time (e.g. 5s) when the pressure sensor detects values exceeding the threshold (ADC > 10) and stop within reasonable time (like 5s) when the ADC value falls below the threshold.

- SRS 04 - The ESP32 wireless motor control shall transmit commands and ensure motor actuation within reasonable time, like 1s.

- SRS 05 - The RTC shall communicate with the DS1307 module using the I2C protocol at a clock speed of 100 kHz (standard mode).

- SRS 06 - The system shall debounce ADC values of pressure sensor over 5 or 10 consecutive samples to eliminate noise and stabilize input readings.

### 3.2 Hardware Requirements Specification (HRS)

*3.2.1. Definition*

- ATmega328PB: The main microcontroller responsible for processing inputs and controlling outputs. It integrates features such as ADC, timers, and communication protocols (I2C, UART, and SPI). Another ATmega328PB is used to control the motor under the wireless control by Blynk app.

- RTC (Real-Time Clock): A hardware module that keeps track of accurate time.

- DHT11: A digital temperature and humidity sensor used to monitor environmental conditions in the room.

- LCD (Liquid Crystal Display): A display module used to visually present time, countdown information, and environmental data to the user.

- Pressure Sensor: A sensor used to detect user presence, providing input to trigger MP3 playback.

- DFPlayer Mini MP3 and Spearker: A compact MP3 playback module that supports audio output based on commands received from the ATmeaga328PB.

- ESP32: A Wi-Fi microcontroller used for wireless communication, transmitting motor control commands.

- Motor: An actuator used to toggle switches, driven by PWM signals for direction control.

*3.2.2. Functionality*

- HRS 01 - A DHT11 temperature and humidity sensor shall be used for environmental monitoring. The sensor shall measure temperature range of 0-50°C (+/- 2°C accuracy) and humidity range of 20-90% (+/- 5% accura1), the changes in environment should be updated and visualized on LCD screen by 30 seconds.

- HRS 02 - A 16x2 cm LCD display shall be used for user interface. The display shall communicate with the microcontroller via I2C bus, the updated and display can be corrrectly displayed.

- HRS 03 - A pressure sensor shall be integrated into the pillow for occupancy detection with sensitive sensing.

- HRS 04 - Servo motors shall be turn the 

- HRS 05 - An MP3 module with speakers shall be correctly playing .

- HRS 05 - The RTC module shall display the current time in Philadelphia on the LCD screen. The displayed time should in synchronize no sooner or later than 3 seconds.

- HRS 06 - The esp32 feather should be able to allow the app to wirelessly control the spinnining state of the servo motor with acceptable delay.

### 4. <a id="results"></a>Results

### 4.1 Software Requirements Specification (SRS) Results

- SRS 01 - The countdown timer successfully decrement the time every second, the naked eye can't tell the difference from a cell phone's countdown timer.

- SRS 02 - The humidity temperature is updated within 10s when environment is changed. 

- SRS 03 - The MP3 needs 3s setup time before palying music.

- SRS 04 - The ESP32 wireless motor control transmit commands and motor actuation within 2s.

- SRS 05 - The RTC successfully communicate with the DS1307 (RTC) module using the I2C protocol at a clock speed of 100 kHz (standard mode).

- SRS 06 - The system successfully debounce ADC values of pressure sensor over 10 consecutive samples to eliminate noise and stabilize input readings.

### 4.2 Hardware Requirements Specification (HRS) Results

- HRS 01 - A DHT11 temperature and humidity sensor measured temperature in the room is usually from range of 20-30°C and the measured humidity range is from 15% to 20% at K-lab. If manually apply water mist to the senor, the humidity could reach 93%. Because we lack tools to measure the exact temperature and humidity and focusing on that the  temperature and humidity displayed in LCD is reasonable. 

- HRS 02 - The LCD display successfully communicate with the microcontroller via I2C bus, the updated and display can be corrrectly displayed.

- HRS 03 - The device automatically trigger music playback within 1 seconds When the time count down reaches zero. Pause/resume playback functionality  within 3 seconds because we set the debouncing number to aovid pressure sensor's noise. 

- HRS 04 - Servo motors successfully controls the light switch with 70-degree range of motion, and rotation error within 3 degree.

- HRS 05 - The RTC module display the current time in Philadelphia on the LCD screen with 4-seconds faster than the online time.

- HRS 07 - The ESP32 feather allows the app to wirelessly control the spinnining state of the servo motor with 1s delay.

### 5. <a id="conclusion"></a>Conclusion: Smart Bedroom Automation System

*5.1. Project Overview Success:* Our smart bedroom automation system successfully integrated multiple components using two ATmega328PB microcontrollers to create a comprehensive solution for bedroom automation. The system effectively combines real-time clock functionality, environmental monitoring, pressure-sensitive music control, and wireless light switch automation, meeting all initial requirements specified in both our Software (SRS) and Hardware (HRS) specifications.

*5.2. Main Project Motivation*

*5.2.1. Wake-up Efficiency*: Many people struggle to get out of bed, often setting multiple alarms only to turn them off and fall back asleep. A smart system that detects when the user has truly woken up could help improve morning routines and reduce oversleeping.

*5.2.2. Convenient Lighting Control*: Single-switch lighting setups near bedroom doors are inconvenient, especially when moving back to bed in the dark, often resulting in accidental bumps and clutter disturbances. An automated, responsive lighting solution can make nighttime movement safer and easier.

*5.3. Key Technical Achievements:*

*5.3.1. Multi-Protocol Integration:*

- I2C communication for DS1307 RTC module with proper BCD conversion at 100kHz.
- Custom one-wire protocol implementation for DHT11 sensor with timeout handling.
- SPI communication for LCD to display with optimized LCD refresh improvements, avoid updating the entire LCD every time the data is updated.
- UART communication for DFPlayer Mini MP3 module to receive the command from ATmega328PB and send information back to MCU to indicate the MP3's state.
- ADC implementation for pressure sensor with debouncing logic to avois noise.
- Different types of interrupt (e.g. pin change interrupt, timer interrupt) are used to ensure the system's performance.
- Wireless communication via ESP32 for smooth remote control.

*5.3.2. Technical Innovations for LCD Display and Timer Optimization:*

- Implemented carry propagation logic across time units
- Reduced LCD refresh operations to only changed digits
- Created modular update functions for each digit position
- state machine is used for better performance.

*5.4. Challenges:*

- Although we have completed all parts of the project, there were significant challenges during the development process, particularly in the final stages of integrating all the modules. This presented several difficulties, such making sure the ATmega328PB had enough pin assignments that did not clash. Functionality conflicts were a possibility because of the limited number of pins and the overlapping requirements from several modules. Any errors made at this point might have caused the system as a whole to be delayed or compromised.
- One specific risk we encountered was during the UART communication with the MP3 module. The wrong pin diagram led to significant debugging delays and posed a risk to our timeline.
- The treatment can be to let teammate know ahead of time when specific pins, like ADC pins, will be utilized. Because it will be simpler to replace a typical GPIO pin. Building the code framework beforehand will save a significant amount of time while working with modularized code. Before a lot of code is shown, make sure the basic functioning of the hardware connections is accurate.
- Another is the LCD refresh speed. Once the data is updated, the entire LCD screen needs to be updated. This seriously affects the usability of the system and hence innovative solutions are proposed.

*5.5. Project Management Insights:*

- Recognized the importance of modular code structure
- Learned effective state machine implementation
- Developed strategies for debugging multi-protocol systems

*5.6. Next Steps:*

To build the smart room system more intelligent and high integration.

5.6.1. *Hardware Improvements*

- Using 3D box for better hardware intergration
- Add multiple pressure sensors for improved pressure detection
- Add more functions like RFID reader for automatic room access and implement automatic light activation upon entry
- Enable multiple user authentication
- Implement wireless music control features:
  - Allow music selection through mobile app
  - Enable play/pause/skip functionality via wireless control
  - Synchronize MP3 player status with app display
  - Add playlist management capabilities
  - Implement volume control through wireless interface

5.6.2. *Software Enhancements*

- Implement power optimization through sleep modes
- Enhance wireless communication reliability
- Improve sensors' data acquisition time and transimitting time for high efficiency
- Add more sophisticated debouncing algorithms

*5.7. Takeaways:*

This project provided valuable learning experiences in:

1. Implementing multiple communication protocols in embedded systems
3. Creating robust sensor integration systems
4. Designing user-friendly interfaces for embedded devices
5. Managing complex state machines and timing systems
6. Implementing wireless control systems
7. Optimizing code for resource-constrained environments
8. Code integration for high modularity system
