/*This program allows you to read the brightness sensor and display the value on
thinger.io as well as controlling a led through a present button
in the dashboard of thinger.io*/

#define _DEBUG_                         // debug method
#define _DISABLE_TLS_                   // disable tls encryption

#include "Wire.h"                       // includ the library wire
#include <Sparkfun_APDS9301_Library.h>  // includ the library for the lux sensor
#include <WiFi.h>         
#include <ThingerWifi.h> //includ the thinger.io library 

#define THINGER_USE_STATIC_MEMORY       
#define THINGER_STATIC_MEMORY_SIZE 512
#define USERNAME "valmnt"                // set username valmnt
#define DEVICE_ID "arduino"              // set ID device arduino
#define DEVICE_CREDENTIAL "IN0vntp804zP" // set device secret key 

#define SSID "A3Pro"                     // set connexion name A3Pro
#define SSID_PASSWORD "valentin"         // set password connexion valentin

#define INT_PIN 2              // We'll connect the INT pin from our sensor to the
                               // INT0 interrupt pin on the Arduino.

// make the connection between entered informations and thinger.io
ThingerWifi thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);  
APDS9301 apds;
    
bool lightIntHappened = false; // flag set in the interrupt to let the
                               // mainline code know that an interrupt occurred.

/* In this program, we read the DHT11 Humidity and Temperature and if H 30% or T > 30 °C blink red LED.
We read the SEN0193 Moisture value and if it is very dry (higher 20%), we switch on yellow
LED. On any other case, we leave the LED green.*/

#include "DHT.h"        // import the library DHT 

#define DHTPIN 3        // initialize the value of the pin at 2    
#define DHTTYPE DHT11   // initialize the type of DHT 
#define redPin 10       // initialization of the redPin variable on pine 10
#define greenPin 9      // initialization of the greenPin variable on pine 9        
#define bluePin 6       // initialization of the bluePin variable on pine 6 
#define LED 7           // connect to the PIN 7 to use the LED 
#define minHt 255       // initialization of the minHt variable and assigned the value 255   
#define maxHt 510       // initialize the maxHt variable and assign it the value 510 

DHT dht(DHTPIN, DHTTYPE);  

int ledState = 0;       // initialize the value of ledState at 0        
int ht;                 // initialization of variable ht (soil moisture)            
float h      = 0;       // initialization of the variable h and we assign the value 0 (humidity)         
float t      = 0;       // initialisation of the variable t and we assign the value 0 (temperature)            
int dry      = 0;       // initialisation of the variable dry and we assign the value 0

/*The setup function initializes all the pins than we need in output.
The Data Debit is initialized at 115 200 bit per second, the DHT library is started
and we calculated the minimum level of drought. */                       
/*The setup function configure the sensor, indicates the data troughput and
make the connection at thinger.io*/
void setup() 
{
  dht.begin();
  pinMode(LED, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  dry = 0.8 * (maxHt - minHt) + minHt;
  Serial.begin(115200);                // speed of the sending informations at 115200 bit per second 
  thing.add_wifi(SSID, SSID_PASSWORD); // make the connexion between the source connexion and the thinger.io 
  pinMode(13, OUTPUT);                 // initialize the led 13 in output
  delay(5);                            // The CCS811 wants a brief delay after startup.
  Wire.begin();                        
    
  // APDS9301 sensor setup.
  apds.begin(0x39);  // We're assuming you haven't changed the I2C
                    // address from the default by soldering the
                   // jumper on the back of the board.
                         
  apds.setGain(APDS9301::LOW_GAIN); // Set the gain to low. Strictly
                         //  speaking, this isn't necessary, as the gain
                         //  defaults to low.
                         
  apds.setIntegrationTime(APDS9301::INT_TIME_13_7_MS); // Set the
                         //  integration time to the shortest interval.
                         //  Again, not strictly necessary, as this is
                         //  the default.
                         
  apds.setLowThreshold(0); // Sets the low threshold to 0, effectively
                          //  disabling the low side interrupt.
                         
  apds.setHighThreshold(50); // Sets the high threshold to 500. This
                         //  is an arbitrary number I pulled out of thin
                         //  air for purposes of the example. When the CH0
                         //  reading exceeds this level, an interrupt will
                         //  be issued on the INT pin.
                         
  apds.setCyclesForInterrupt(1); // A single reading in the threshold
                                //  range will cause an interrupt to trigger.
                         
  apds.enableInterrupt(APDS9301::INT_ON); // Enable the interrupt.
  apds.clearIntFlag();

  // Interrupt setup
  pinMode(INT_PIN, INPUT_PULLUP); // This pin must be a pullup or have
                                 // a pullup resistor on it as the interrupt is a
                                // negative going open-collector type output.
  
  // if the value of lightInt decrease execute the function digitalPinToInterrupt(2)
  attachInterrupt(digitalPinToInterrupt(2), lightInt, FALLING);
  // print apds.getLowThreshold()
  Serial.println(apds.getLowThreshold());                       
  // print apds.getHighThreshold()    
  Serial.println(apds.getHighThreshold());                           
}

/*The loop function will manage the colors of the led according to the 
humidity of the earth as well as the temperature and humidity of the air.*/
/* The loop function is the part that will read and display the values 
of brightness sensor in the console as well as add widgets  
to control the led and to display luminux values on thinger.io*/
void loop() 
{ 
  static unsigned long outLoopTimer = 0;
  apds.clearIntFlag();                          
  thing.handle();
  
  // led control by thinger.io
  thing["led"] << digitalPin(13);                        
      
  // declare the lux value to use it in the interface of thinger.io
  thing["LuxValue"] >> outputValue(apds.readCH0Level()); 
     
  // This is a once-per-second timer that calculates and display the luminux value
  //  the current lux reading.
  if (millis() - outLoopTimer >= 1000)
    {
      outLoopTimer = millis();
      Serial.print("Luminous flux: ");
      Serial.println(apds.readCH0Level(),10);

  if (lightIntHappened)
    {
      Serial.println("Interrupt");
      lightIntHappened = false;    
    }
  }
 /*connect sensor to Analog 0*/
  ht = analogRead(0);  
  
  /*moisture reading is assigned to the h variable*/
  h = dht.readHumidity(); 
  
  /*the temperature reading is assigned to the varible t*/ 
  t = dht.readTemperature(); 
  
  /*If humidity is below 30% or temperature is above 30°C then blink red LED*/
  if (t > 30 || h < 30)                    
  {
    setColor(255, 0, 0);
  }
  /*otherwise if soil moisture variable is greater than dry variable then the led flashes in yellow. */
  else if (ht > dry)                        
  {
    setColor(255, 100, 0);
  }
  /*otherwise the led flashes in green*/
  else                                      
  {
    setColor(0, 255, 0);
  }
  
  /*here the value of soil moisture is displayed in the console */
  Serial.print("Humidity of the earth :");  
  Serial.print(ht); 
  Serial.print("    ");
  delay(100);
  
  /*If the sensor fails to pick up values then we say "impossible reading"*/
  if (isnan(t) || isnan(h))                 
  {
    Serial.println("Impossible reading !");
  }
  /*otherwise the humidity and temperature values are displayed*/
  else                                     
  {
    Serial.print("Humidity :");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature :");
    Serial.print(t);
    Serial.println("*C");
  }
  delay(100);    
}

/*The function lightInt set lightIntHappened at true*/
void lightInt()
{
  lightIntHappened = true; 
}

/*the setColor function allows the display color 
desired according to the parameters indicated.*/

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
