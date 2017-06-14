//FUSION Temperature & light intensity & movement

//Include library and variables for temperature
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include <Adafruit_ADXL345_U.h>

#define ONE_WIRE_BUS 9
#define SD_CARD_PIN 10

float temperatureValue;
File myFile;
String to_save;



/*********************************************************************************************************************************/

//FOR TEMPERATURE
// Data wire for temperature is plugged into port 12 on the Arduino
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/*********************************************************************************************************************************/

//FOR MOVEMENT
/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

/*********************************************************************************************************************************/

//FOR LIGHT INTENSITY AND MOVEMENT
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);


/*********************************************************************************************************************************/

//FOR LIGHT INTENSITY
void configureSensor(void){
 tsl.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */

 /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
 //tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
 tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
 // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */
}





/*********************************************************************************************************************************/



//MAIN FUNCTION SETUP FOR TEMPERATURE AND LIGHT INTENSITY AND MOVEMENT

void setup(){
 //Setup of temperature sensor
 Serial.begin(9600);
 Serial.println("Dallas Temperature IC Control Library Demo");
 sensors.begin();

 //Setup of light intensity sensor

 Serial.begin(9600);
 Serial.println("Light Sensor Test"); Serial.println("");
 if(!tsl.begin()){
     Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
     while(1);
 }
 configureSensor();
 Serial.println("");


 //Setup for movement
 #ifndef ESP8266
    while (!Serial); // for Leonardo/Micro/Zero
 #endif
 Serial.begin(9600);
 Serial.println("Accelerometer Test"); Serial.println("");

 /* Initialise the sensor */
 if(!accel.begin()){
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
 }

 /* Set the range to whatever is appropriate for your project */
 accel.setRange(ADXL345_RANGE_16_G);
 // displaySetRange(ADXL345_RANGE_8_G);
 // displaySetRange(ADXL345_RANGE_4_G);
 // displaySetRange(ADXL345_RANGE_2_G);

 /* Display some basic information on this sensor */

 /* Display additional settings (outside the scope of sensor_t) */
 Serial.println("");

 //Setup for SD card
 Serial.begin(9600);
 while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
 }
 Serial.print("Initializing SD card...");
 pinMode(SD_CARD_PIN, OUTPUT);
 if (!SD.begin(SD_CARD_PIN)) {
    Serial.println("SD card initialization failed!");
    return;
 }
 Serial.println("initialization done.");

 myFile = SD.open("result.txt", FILE_WRITE);

 // if the file opened okay, write to it:
 if (myFile) {
   Serial.print("Writing to result.txt...");
   myFile.println("temperature light X Y Z");
 // close the file:
   myFile.close();
   Serial.println("done.");
 } else {
   // if the file didn't open, print an error:
   Serial.println("error opening result.txt");
 }

}


/*********************************************************************************************************************************/


//MAIN FUNCTION LOOP FOR TEMPERATURE AND LIGHT INTENSITY AND MOVEMENT AND SAVING TO SD
void loop(void){
 //TEMPERATURE
 // call sensors.requestTemperatures() to issue a global temperature
 // request to all devices on the bus
 sensors.requestTemperatures(); // Send the command to get temperatures
 // print temperature value
 temperatureValue = sensors.getTempCByIndex(0);
 Serial.println(temperatureValue);

 //LIGHT INTENSITY

 /* Get a new sensor event */
 sensors_event_t event;
 tsl.getEvent(&event);

 /* Display the results (light is measured in lux) */
 if (event.light){
 Serial.print(event.light); Serial.println(" lux");
 } else {
    /* If event.light = 0 lux the sensor is probably saturated
    and no reliable data could be generated! */
    Serial.println("Sensor overload");
 }
 delay(250);


 //MOVEMENT

 /* Get a new sensor event */
 accel.getEvent(&event);

 /* Display the results (acceleration is measured in m/s^2) */
 Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
 Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
 Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
 delay(500);


//SD card
 String to_save = "";
 to_save = String(temperatureValue);
 to_save = to_save +"," + String(event.light) +"," + String(event.acceleration.x) +","+ String(event.acceleration.y) +"," String(event.acceleration.z) ;
 myFile = SD.open("result.txt", FILE_WRITE);

  // if the file opened okay, write to it:
 if (myFile) {
    Serial.print("Writing to result.txt...");
    myFile.println(to_save);
    // close the file:
    myFile.close();
    Serial.println("done.");
} else {
    // if the file didn't open, print an error:
    Serial.println("error opening result.txt");
   }
}
