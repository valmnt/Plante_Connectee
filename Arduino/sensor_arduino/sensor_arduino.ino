/*This program allows you to read all sensors and display values on
thinger.io*/
#define _DEBUG_                         // debug method
#define _DISABLE_TLS_                   // disable tls encryption

#include "Wire.h"                       // includ the library wire
#include <Sparkfun_APDS9301_Library.h>  // includ the library for the lux sensor
#include <WiFi.h>         
#include <ThingerWifi.h>                //includ the thinger.io library 

#define THINGER_USE_STATIC_MEMORY       
#define THINGER_STATIC_MEMORY_SIZE 512
#define USERNAME "valmnt"                // set username valmnt
#define DEVICE_ID "arduino"              // set ID device arduino
#define DEVICE_CREDENTIAL "IN0vntp804zP" // set device secret key 

#define SSID "A3Pro"                     // set connexion name A3Pro
#define SSID_PASSWORD "valentin"         // set password connexion valentin

#define INT_PIN 10              // We'll connect the INT pin to the pin 10

ThingerWifi thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);  
APDS9301 apds;

#include "DHT.h"        // import the library DHT 

#define DHTPIN 2        // initialize the value of the pin at 2    
#define DHTTYPE DHT11   // initialize the type of DHT 

DHT dht(DHTPIN, DHTTYPE);  
       
int ht;                 // initialization of variable ht (soil moisture)
int lux;                // initialization of variable lux (luminoux)
float h      = 0;       // initialization of the variable h and we assign the value 0 (humidity)         
float t      = 0;       // initialisation of the variable t and we assign the value 0 (temperature)            
                     
/*The setup function configure sensors, indicates the data troughput and
the used wifi to be connected at thinger.io*/
void setup() 
{
  dht.begin();
  Serial.begin(115200);                // speed of the sending informations at 115200 bit per second 
  thing.add_wifi(SSID, SSID_PASSWORD); // make the connexion between the source connexion and the thinger.io 
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
  
  // print apds.getLowThreshold()
  Serial.println(apds.getLowThreshold());                       
  // print apds.getHighThreshold()    
  Serial.println(apds.getHighThreshold());                           
}

/* The loop function is the part that will read and display the values 
of sensors in the console. The loop function connect sensors at thinger.io and display
sensors values on thinger.io*/
void loop() 
{ 
  apds.clearIntFlag();                          
  thing.handle();
        
  // declare values to use it in the interface of thinger.io
  thing["LuxValue"] >> outputValue(apds.readCH0Level());
  thing["AtmosphericHumidity"] >> outputValue(dht.readHumidity());
  thing["Celsius"] >> outputValue(dht.readTemperature());
  thing["SoilMoisture"] >> outputValue(analogRead(0));
     
 /*connect sensor to Analog 0*/
  ht = analogRead(0);
  
  /*lux reading is assigned to the lux variable*/
  lux = apds.readCH0Level();
  
  /*moisture reading is assigned to the h variable*/
  h = dht.readHumidity(); 
  
  /*the temperature reading is assigned to the varible t*/ 
  t = dht.readTemperature(); 
   
  /*if the sensor fails to pick up values then we say "impossible reading"*/
  if (isnan(h) || isnan(t))                 
  {
    Serial.println("Impossible reading !");
  }
  /*otherwise the humidity, temperature, humidity of the earth and luminosity values are displayed*/
  else                                     
  {
    Serial.print(" ");
    Serial.print("Humidity :");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature :");
    Serial.print(t);
    Serial.println("*C");
    Serial.print("Luminoux flux: ");
    Serial.println(lux);
    Serial.print("Humidity of the earth :");  
    Serial.print(ht);
  }
  delay(1000);    
}
