/*
o  o o--o   O  o-o    o-o      o   o o--o  
|  | |     / \ |  \  |         |   | |   | 
O--O O-o  o---o|   O  o-o      |   | O--o  
|  | |    |   ||  /      |     |   | |     
o  o o--o o   oo-o   o--o       o-o  o     
                                           
1. If you have a new ATmega328P , you’ll need to burn the bootloader onto the chip first.
Please follow our instructions in the following tutorial:
https://www.circuito.io/blog/atmega328p-bootloader/                                      

2. After uploading the sketches onto the ATMega328P, open the serial monitor and reboot the ATMega328P to view the test code menu.
*/
// Include Libraries
#include "Arduino.h"
#include "LiquidCrystal.h"
#include "SoilMoisture.h"
#include "Button.h"


// Pin Definitions
#define LCD_PIN_RS	7
#define LCD_PIN_E	6
#define LCD_PIN_DB4	2
#define LCD_PIN_DB5	3
#define LCD_PIN_DB6	4
#define LCD_PIN_DB7	5
#define SOILMOISTURE_5V_PIN_SIG	A0
#define WATERLEVELSENSOR_PIN_SIG	8



// Global variables and defines

// object initialization
LiquidCrystal lcd(LCD_PIN_RS,LCD_PIN_E,LCD_PIN_DB4,LCD_PIN_DB5,LCD_PIN_DB6,LCD_PIN_DB7);
SoilMoisture soilMoisture_5v(SOILMOISTURE_5V_PIN_SIG);
Button WaterLevelSensor(WATERLEVELSENSOR_PIN_SIG);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    // set up the LCD's number of columns and rows
    lcd.begin(16, 2);
    WaterLevelSensor.init();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1')
    {
    // Disclaimer: The BME680 Temperature, Humidity, Pressure and Gas sensor is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '2') {
    // LCD 16x2 - Test Code
    // Print a message to the LCD.
    lcd.setCursor(0, 0);
    lcd.print("Circuito Rocks !");
    // Turn off the display:
    lcd.noDisplay();
    delay(500);
    // Turn on the display:
    lcd.display();
    delay(500);
    }
    else if(menuOption == '3') {
    // Soil Moisture Sensor - Test Code
    int soilMoisture_5vVal = soilMoisture_5v.read();
    Serial.print(F("Val: ")); Serial.println(soilMoisture_5vVal);

    }
    else if(menuOption == '4') {
    // Gravity: Non-contact Digital Water / Liquid Level Sensor - Test Code
    //read Water Level Sensor state. 
    //If the Water Level Sensor detects the liquid level, it will output HIGH (1) and turn the LED ON. 
    //If no liquid is detected it output LOW (0) and turn the LED off.. 
    bool WaterLevelSensorVal = WaterLevelSensor.read();
    Serial.print(F("Val: ")); Serial.println(WaterLevelSensorVal);

    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) BME680 Temperature, Humidity, Pressure and Gas sensor"));
    Serial.println(F("(2) LCD 16x2"));
    Serial.println(F("(3) Soil Moisture Sensor"));
    Serial.println(F("(4) Gravity: Non-contact Digital Water / Liquid Level Sensor"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing BME680 Temperature, Humidity, Pressure and Gas sensor - note that this component doesn't have a test code"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing LCD 16x2"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing Soil Moisture Sensor"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing Gravity: Non-contact Digital Water / Liquid Level Sensor"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/