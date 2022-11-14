
#include "Arduino.h"
#include "DHT.h"
#include "LiquidCrystal.h"
#include "SoilMoisture.h"
#include "Button.h"


// Pin Definitions
#define DHT_PIN_DATA	2
#define LCD_PIN_RS	8
#define LCD_PIN_E	7
#define LCD_PIN_DB4	3
#define LCD_PIN_DB5	4
#define LCD_PIN_DB6	5
#define LCD_PIN_DB7	6
#define SOILMOISTURE_5V_PIN_SIG	A0
#define WATERLEVELSENSOR_PIN_SIG	10



// Global variables and defines

// object initialization
DHT dht(DHT_PIN_DATA);
LiquidCrystal lcd(LCD_PIN_RS,LCD_PIN_E,LCD_PIN_DB4,LCD_PIN_DB5,LCD_PIN_DB6,LCD_PIN_DB7);
SoilMoisture soilMoisture_5v(SOILMOISTURE_5V_PIN_SIG);
Button WaterLevelSensor(WATERLEVELSENSOR_PIN_SIG);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    dht.begin();
  
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

    }
    else if(menuOption == '2') {
      
    // DHT22/11 Humidity and Temperature Sensor - Test Code
    // Reading humidity in %
      
    float dhtHumidity = dht.readHumidity();
      
    // Read temperature in Fahrenheit 
      
    float dhtTempC = dht.readTempF();
    Serial.print(F("Humidity: ")); Serial.print(dhtHumidity); Serial.print(F(" [%]\t"));
    Serial.print(F("Temp: ")); Serial.print(dhtTempC); Serial.println(F(" [C]"));

    }
    else if(menuOption == '3') {
      
    // LCD 16x2 - Test Code
      
    lcd.setCursor(0, 0);
 
    // Turn off the display:
    lcd.noDisplay();
    delay(500);
    // Turn on the display:
    lcd.display();
    delay(500);
    }
    else if(menuOption == '4') {
      
    // Soil Moisture Sensor - Test Code
    int soilMoisture_5vVal = soilMoisture_5v.read();
    Serial.print(F("Val: ")); Serial.println(soilMoisture_5vVal);

    }
    else if(menuOption == '5') {
    // Gravity: Non-contact Digital Water / Liquid Level Sensor - Test Code
    //read Water Level Sensor state. 
    //If the Water Level Sensor detects the liquid level, it will output HIGH (1) and turn the LED ON. 
    //If no liquid is detected it output LOW (0) and turn the LED off
      
    bool WaterLevelSensorVal = WaterLevelSensor.read();
    Serial.print(F("Val: ")); Serial.println(WaterLevelSensorVal);

    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested

char menu()
{
Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) BME680 Temperature, Humidity, Pressure and Gas sensor"));
    Serial.println(F("(2) DHT22/11 Humidity and Temperature Sensor"));
    Serial.println(F("(3) LCD 16x2"));
    Serial.println(F("(4) Soil Moisture Sensor"));
    Serial.println(F("(5) Gravity: Non-contact Digital Water / Liquid Level Sensor"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing BME680 Temperature, Humidity, Pressure sensor - 
    		else if(c == '2') 
    			Serial.println(F("Now Testing DHT22/11 Humidity and Temperature Sensor"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing LCD 16x2"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing Soil Moisture Sensor"));
    		else if(c == '5') 
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

