#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define WIRE Wire

int pin = 11;
int val;                                                              //calibration value
long last=0;                                                          //used in timing - holds thelast milis count
int stat1=LOW;                                                         //used in calibration
int stat2;                                                            //used in calibration
int counter=0;                                                        //used to count light/dark iterations

int stat3=0;                                                          //counterit  
int stat4=0;

int sens=75;                                                          //calibration value
                 
int slots=16; 

int milisecs=500;   

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_BME280 bme; // Create BME280 object

void setup() {
  Serial.begin(115200);
WIRE.begin(1,2);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display();
  delay(100);
  display.clearDisplay();
  display.display();
  display.setTextSize(1.9);
  display.setTextColor(WHITE);
  bool status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {

 val=analogRead(pin);                                                  //light or dark?
  if(val<sens)                                                        //within calibartion value?
    stat1=LOW;                                                         //set var to LOW
   else                                                               //if not
    stat1=HIGH;                                                        //set var HIGH
   digitalWrite(13,stat1);                                             //LED on or off
                          
 
   if(stat2!=stat1){                                                   //if there has been a change
                     
     counter++;                                                       //increment counter
     stat2=stat1;                                                      //remember last value
   }
   if(millis()-last>=milisecs){                                       //has time passed?
     double rps=((double)counter/slots)/2.0*1000.0/milisecs;          //do math
     double rpm=((double)counter/slots)/2.0*60000.0/(milisecs);   
     double kmh= 0.0543 * rpm - 9.716;
     double ms= kmh / 3.6;
     /*display.clearDisplay();                                          //clear display & buffer
     display.setTextSize(1);                                          //prepare to show stuff
     display.setTextColor(WHITE);
     display.setCursor(0,0);
     //display.print((counter/2.0));
     //display.println("  RPS ");
     //display.print(rps);
     display.print("RPM ");                                           //print out the units we are using to buffer
     display.println(rpm);                                            //print out the value returned by the maths
     display.display(); */                                              //show me the buffer!
                                                 //remember this moment


  display.setCursor(0,0);
  display.clearDisplay();
  
  display.setCursor(0,0);
  //Serial.print("Temperature = "); Serial.print(bme.readTemperature());
  display.print("Temperature: "); display.print(bme.readTemperature()); display.print("C");

  display.setCursor(0,15);
  //Serial.print("Pressure = "); Serial.print(bme.readPressure() / 100.0F);
  display.print("Pressure: "); display.print(bme.readPressure() / 100.0F); display.print("hPa");

  display.setCursor(0,30);
  //Serial.print("Humidity = "); Serial.print(bme.readHumidity());
  display.print("Humidity: "); display.print(bme.readHumidity()); display.print("%");

  display.setCursor(0,45);  
 // display.print("RPM ");                                           //print out the units we are using to buffer
  //display.println(rpm); 

  display.print("m/s ");                                           
  display.println(ms);

       
  counter=0;                                                       //reset counter
  last=millis();  

  Serial.println();
  display.display();
  //delay(1000);
  //Serial.println(stat3);
  //stat3++;

  //stat3 = 0;
    //RPM();
  }
  }
/*
void RPM(){
    for (int i = 0; i < 100; i++) {
  Serial.println("RPM");
  val=analogRead(pin);                                                  //light or dark?
  if(val<sens)                                                        //within calibartion value?
    stat1=LOW;                                                         //set var to LOW
   else                                                               //if not
    stat1=HIGH;                                                        //set var HIGH
   digitalWrite(13,stat1);                                             //LED on or off
                          
 
   if(stat2!=stat1){                                                   //if there has been a change
                     
     counter++;                                                       //increment counter
     stat2=stat1;                                                      //remember last value
   }
   if(millis()-last>=milisecs){                                       //has time passed?
     double rps=((double)counter/slots)/2.0*1000.0/milisecs;          //do maths
     double rpm=((double)counter/slots)/2.0*60000.0/(milisecs);       //do more maths
     display.clearDisplay();                                          //clear display & buffer
     display.setTextSize(1);                                          //prepare to show stuff
     display.setTextColor(WHITE);
     display.setCursor(0,0);
     //display.print((counter/2.0));
     //display.println("  RPS ");
     //display.print(rps);
     display.print("RPM ");                                           //print out the units we are using to buffer
     display.println(rpm);                                            //print out the value returned by the maths
     display.display();                                               //show me the buffer!
     
     counter=0;                                                       //reset counter
     last=millis();                                                   //remember this moment

}}}
*/