/**************************************************
  Name: Plant Moisture Monitor and Auto-Watering System
  Description: This project monitors the soil moisture level and controls a water pump to automatically water the plants when the soil is dry. It also displays the moisture level and the pump status on an LCD.
  Email: sfarrag@smu.com
  Website: https://www.arduino.cc/reference/en/libraries/liquidcrystal-i2c/

  Components:
  - Arduino Uno Rev3
  - Soil Moisture Sensor
  - Relay Module
  - Water Pump
  - LiquidCrystal I2C Display (LCD 1602)
  - Connecting Wires
  - Breadboard

  Instructions:
  - Connect the soil moisture sensor, relay module, water pump, and LCD as described in the comments below.
  - Upload the code to the Arduino Uno Rev3.
  - The system will monitor the soil moisture level and automatically water the plants when needed.
 **************************************************/

#include <LiquidCrystal_I2C.h>  // Include the LiquidCrystal_I2C library for LCD

// Define pin connections and LCD size
#define SOIL_MOISTURE_PIN A0  // Analog pin connected to the soil moisture sensor
#define RELAY_PIN 2           // Digital pin connected to the relay module

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD I2C address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(9600);  // Initialize serial communication for debugging
  
  // Initialize the LCD
  lcd.init();  // Initialize the LCD
  lcd.backlight();  // Turn on the backlight
  lcd.clear();  // Clear any previous text on the LCD
  lcd.setCursor(0, 0);  // Set cursor to column 0, row 0
  lcd.print("IRRIGATION");  // Print static text
  lcd.setCursor(0, 1);  // Set cursor to column 0, row 1
  lcd.print("SYSTEM IS ON ");  // Print static text
  delay(3000);  // Display message for 3 seconds
  lcd.clear();  // Clear the display
  
  // Initialize the relay pin
  pinMode(RELAY_PIN, OUTPUT);  // Set the relay pin as an output
  digitalWrite(RELAY_PIN, HIGH); // Ensure the relay is off initially (using HIGH logic to turn off relay)
}

void loop() {
  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);  // Read the analog value from the soil moisture sensor
  Serial.println(soilMoistureValue);  // Print the soil moisture value to the Serial Monitor for debugging
  
  // Display the moisture level on the LCD
  if (soilMoistureValue < 300) {  // Check if moisture is HIGH
    lcd.setCursor(0, 1);
    lcd.print("Moisture : HIGH ");
  } else if (soilMoistureValue >= 300 && soilMoistureValue <= 950) {  // Check if moisture is MID
    lcd.setCursor(0, 1);
    lcd.print("Moisture : MID  ");
  } else {  // Otherwise, moisture is LOW
    lcd.setCursor(0, 1);
    lcd.print("Moisture : LOW  ");
  }

  // Control the water pump based on soil moisture level
  if (soilMoistureValue > 950) {  // If soil is dry
    digitalWrite(RELAY_PIN, LOW); // Turn on the water pump (using LOW logic to turn on relay)
    lcd.setCursor(0, 0);  // Update LCD to show pump status
    lcd.print("Water Pump is ON ");
  } else {  // If soil is sufficiently moist
    digitalWrite(RELAY_PIN, HIGH); // Turn off the water pump (using HIGH logic to turn off relay)
    lcd.setCursor(0, 0);  // Update LCD to show pump status
    lcd.print("Water Pump is OFF");
  }
  
  delay(1000);  // Check moisture level every second
}

