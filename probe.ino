
//FUSION Temperature & light intensity & movement & water level

//Include library for temperature
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SD.h>

//Include library for Light intensity
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

//Include library for Movement
#include <Adafruit_ADXL345_U.h>

/*********************************************************************************************************************************/

//FOR TEMPERATURE
// Data wire for temperature is plugged into port 12 on the Arduino
#define ONE_WIRE_BUS 9
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/*********************************************************************************************************************************/

//FOR MOVEMENT
/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void displayDataRate(void)
{
 Serial.print  ("Data Rate:    ");

 switch(accel.getDataRate())
 {
   case ADXL345_DATARATE_3200_HZ:
     Serial.print  ("3200 ");
     break;
   case ADXL345_DATARATE_1600_HZ:
     Serial.print  ("1600 ");
     break;
   case ADXL345_DATARATE_800_HZ:
     Serial.print  ("800 ");
     break;
   case ADXL345_DATARATE_400_HZ:
     Serial.print  ("400 ");
     break;
   case ADXL345_DATARATE_200_HZ:
     Serial.print  ("200 ");
     break;
   case ADXL345_DATARATE_100_HZ:
     Serial.print  ("100 ");
     break;
   case ADXL345_DATARATE_50_HZ:
     Serial.print  ("50 ");
     break;
   case ADXL345_DATARATE_25_HZ:
     Serial.print  ("25 ");
     break;
   case ADXL345_DATARATE_12_5_HZ:
     Serial.print  ("12.5 ");
     break;
   case ADXL345_DATARATE_6_25HZ:
     Serial.print  ("6.25 ");
     break;
   case ADXL345_DATARATE_3_13_HZ:
     Serial.print  ("3.13 ");
     break;
   case ADXL345_DATARATE_1_56_HZ:
     Serial.print  ("1.56 ");
     break;
   case ADXL345_DATARATE_0_78_HZ:
     Serial.print  ("0.78 ");
     break;
   case ADXL345_DATARATE_0_39_HZ:
     Serial.print  ("0.39 ");
     break;
   case ADXL345_DATARATE_0_20_HZ:
     Serial.print  ("0.20 ");
     break;
   case ADXL345_DATARATE_0_10_HZ:
     Serial.print  ("0.10 ");
     break;
   default:
     Serial.print  ("???? ");
     break;
 }
 Serial.println(" Hz");
}

void displayRange(void)
{
 Serial.print  ("Range:         +/- ");

 switch(accel.getRange())
 {
   case ADXL345_RANGE_16_G:
     Serial.print  ("16 ");
     break;
   case ADXL345_RANGE_8_G:
     Serial.print  ("8 ");
     break;
   case ADXL345_RANGE_4_G:
     Serial.print  ("4 ");
     break;
   case ADXL345_RANGE_2_G:
     Serial.print  ("2 ");
     break;
   default:
     Serial.print  ("?? ");
     break;
 }
 Serial.println(" g");
}

/*********************************************************************************************************************************/

//FOR LIGHT INTENSITY AND MOVEMENT
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

void displaySensorDetails(void)
{
 //Light intensity
 sensor_t sensor;
 tsl.getSensor(&sensor);
 Serial.println("------------------------------------");
 Serial.print  ("Sensor:       "); Serial.println(sensor.name);
 Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
 Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
 Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" lux");
 Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" lux");
 Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" lux");
 Serial.println("------------------------------------");
 Serial.println("");
 delay(500);

//Movement
{
 sensor_t sensor;
 accel.getSensor(&sensor);
 Serial.println("------------------------------------");
 Serial.print  ("Sensor:       "); Serial.println(sensor.name);
 Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
 Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
 Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
 Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
 Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");
 Serial.println("------------------------------------");
 Serial.println("");
 delay(500);
}

}

/*********************************************************************************************************************************/

//FOR LIGHT INTENSITY
void configureSensor(void)
{
 /* You can also manually set the gain or enable auto-gain support */
 // tsl.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
 // tsl.setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
 tsl.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */

 /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
 tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
 // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
 // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */

 /* Update these values depending on what you've set above! */
 Serial.println("------------------------------------");
 Serial.print  ("Gain:         "); Serial.println("Auto");
 Serial.print  ("Timing:       "); Serial.println("13 ms");
 Serial.println("------------------------------------");
}



/*********************************************************************************************************************************/

// MAIN FUNCTION SETUP FOR SD CARD
void setup(){

 Serial.begin(9600);
 Serial.print("Initializing SD card...");
 pinMode(10, OUTPUT);

 if (!SD.begin(10)) {
    Serial.println("SD card initialization failed!");
    return;
 }
 Serial.println("initialization done.");

 myFile = SD.open("result.txt", FILE_WRITE);

 // if the file opened okay, write to it:
 if (myFile) {
   Serial.print("Writing to result.txt...");
   myFile.println("temperature light X Y Z water");
 // close the file:
   myFile.close();
   Serial.println("done.");
 } else {
   // if the file didn't open, print an error:
   Serial.println("error opening result.txt");
 }

}



/*********************************************************************************************************************************/



//MAIN FUNCTION SETUP FOR TEMPERATURE AND LIGHT INTENSITY AND MOVEMENT

void setup(void)
{
 //Setup of temperature sensor
 Serial.begin(9600);
 Serial.println("Dallas Temperature IC Control Library Demo");
 sensors.begin();

 //Setup of light intensity sensor
 {
   Serial.begin(9600);
   Serial.println("Light Sensor Test"); Serial.println("");
   if(!tsl.begin())
   {
     Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
     while(1);
   }
   displaySensorDetails();
   configureSensor();
   Serial.println("");
 }

 //Setup for movement
   {
   #ifndef ESP8266
     while (!Serial); // for Leonardo/Micro/Zero
   #endif
     Serial.begin(9600);
     Serial.println("Accelerometer Test"); Serial.println("");

     /* Initialise the sensor */
     if(!accel.begin())
     {
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
     displaySensorDetails();

     /* Display additional settings (outside the scope of sensor_t) */
     displayDataRate();
     displayRange();
     Serial.println("");
   }
 //Setup for water level
   {
     Serial.begin(9600);

   }
}


/*********************************************************************************************************************************/


//MAIN FUNCTION LOOP FOR TEMPERATURE AND LIGHT INTENSITY AND MOVEMENT AND SAVING TO SD
void loop(void)
{
 //TEMPERATURE
 // call sensors.requestTemperatures() to issue a global temperature
 // request to all devices on the bus
 sensors.requestTemperatures(); // Send the command to get temperatures
 // print temperature value
 temperatureValue = sensors.getTempCByIndex(0)
 Serial.println(temperatureValue);

 //LIGHT INTENSITY
 {
   /* Get a new sensor event */
   sensors_event_t event;
   tsl.getEvent(&event);

   /* Display the results (light is measured in lux) */
   if (event.light)
   {
     Serial.print(event.light); Serial.println(" lux");
   }
   else
   {
     /* If event.light = 0 lux the sensor is probably saturated
        and no reliable data could be generated! */
     Serial.println("Sensor overload");
   }
   delay(250);
 }

 //MOVEMENT
 {
   /* Get a new sensor event */
   sensors_event_t event;
   accel.getEvent(&event);

   /* Display the results (acceleration is measured in m/s^2) */
   Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
   Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
   Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
   delay(500);
 }

 //Water level
 {
 waterValue = analogRead(5);
 Serial.println(waterValue);
 delay(100);
 }

 to_save = String(temperatureValue)
 to_save = to_save + String(event.light) + String(event.acceleration.x) + String(event.acceleration.y) + String(event.acceleration.z) + String(waterValue);
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
