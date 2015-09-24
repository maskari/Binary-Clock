#include <Adafruit_NeoPixel.h>
#include <Timer.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel sstrip = Adafruit_NeoPixel(22, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

Timer t;
byte second=0; // initialize second, minute, hour to zero
byte minute=10; // set data type to byte to ensure that data is 1 byte
byte hour=0;  // and to ensure that the data stored in the bytes is standard litlle endian with no sign bit

bool comp;

void setup() {
  sstrip.begin();
  sstrip.setBrightness(10);
  //sstrip.show(); // Initialize all pixels to 'off'
  //theaterChaseRainbow(50);
  sstrip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  t.every(1000, counter);
   slight();
   mlight();
   hlight();
  
}


void loop() {
 

t.update();


}




void refresh(){ // function to refresh the display
 slight();
 mlight();
 hlight(); 
}


void set(){ // function to set the time
  
  
  
}





void counter(){  // function to count the seconds
//Serial.print("second:  ");  
//Serial.println(second);  // print the number of seconds elapsed/being represented


second = second+1; // increment counter by one


if(second==60){ // count a minute every 60 seconds
 
  minute = minute+1;
  mlight();
  Serial.print("time:  ");  
  Serial.print(hour);// print the number of minutes elapsed/being represented
  Serial.print(":");
  Serial.println(minute);
  
  
   if(minute==60){
    hour = hour+1;
    hlight();
         if(hour==24){
         hour=0; //reset hour counter to zero after 24 hours  
         }
   
   minute=0; // reset minute counter to zero every minute 
   }
  
  second = 0; // reset second counter to zero every minute
  
  //return second;
}
  slight();
}





void slight(){
                // initialization and decleration of variables for 0-9 seconds (ones units)
                byte i=1;  // byte value of LED  
                byte j=0;  // LED number // number of first LED represnting seconds
                byte modsec=second%10;
               while (i<=8){   // while loop for going through each pixel, counts to 64 as each pixel is represented as a bit value and 60 seconds require 6 bits, 6 bits == 64
                              //Serial.println("entering while loop");
                                comp=0;  // initializing the comparator, not really necessary but doesn't hurt
                                comp=i&modsec; // ANDing the bit number and the second value to see if the LED representing the bit is required to represent the value or not, eg 2 = B0000 0010 therefore only the 2nd pixel will light up 
                              //  Serial.print("bit number:  ");
                              //  Serial.println(i);
                              //   Serial.print("xor value:  ");
                              //  Serial.println(comp);
                                
                                if(comp==1){ // if pixel is valid then light her up!
                                            //    Serial.print("comp ==1, pixel:  ");
                                              sstrip.setPixelColor(j,i+100,00,0);
                                              //sstrip.show();
                                             // Serial.println("conditional if");
                                            //  Serial.println(j);
                                            }
                              
                                  else{  sstrip.setPixelColor(j,0,0,0); // else shut her down
                                       // sstrip.show();
                                      }
                                  sstrip.show();  // show the changes made to the pixels
                                  i=i*2;  // update the values
                                  j++;
                            }
                            // end of while loop
                              
              
              
              
              
              
                     // initialization and decleration of variables for 10-60 seconds (the tens units)
                      byte k=1; // byte value of LED
                      byte l=6;  // LED number, LEDs are placed in reverse order because of how the LEDs are layed out in one continous strand  // number of last LED represnting seconds
                      byte tensec=second/10;  // tensec == 10s unit of seconds
//                      Serial.print("tensec= ");
//                      Serial.print(tensec);
//                      Serial.print("    second= ");
//                      Serial.println(second);
                       while (k<=4){   // while loop for going through each pixel, counts to 64 as each pixel is represented as a bit value and 60 seconds require 6 bits, 6 bits == 64
                              //Serial.println("entering while loop");
                              
                                comp=0;  // initializing the comparator, not really necessary but doesn't hurt
                                comp=k&tensec; // ANDing the bit number and the 10s second value to see if the LED representing the bit is required to represent the value or not, eg 2 = B0000 0010 therefore only the 2nd pixel will light up 
                              //  Serial.print("bit number:  ");
                              //  Serial.println(i);
                              //   Serial.print("xor value:  ");
                              //  Serial.println(comp);
                                
                                if(comp==1){ // if pixel is valid then light her up!
                                            //    Serial.print("comp ==1, pixel:  ");
                                              sstrip.setPixelColor(l,k+100,00,0);
                                              //sstrip.show();
                                             // Serial.println("tensecyaaay");
                                            //  Serial.println(j);
                                            }
                              
                                  else{  sstrip.setPixelColor(l,0,0,0); // else shut her down
                                       // sstrip.show();
                                      }
                                  sstrip.show();  // show the changes made to the pixels
                                  k=k*2;  // update the values
                                  l--;
                            }
                            // end of while loop
                      
                    
                    i=1; // reinitialize the variables for the next time the function call takes place (legacy code, no longer necessary)
                    j=0;
                    k=1;
                    l=6;
                     
              }
              
              
              
              


void mlight(){
                // initialization and decleration of variables for 0-9 seconds (ones units)
                byte i=1;  // byte value of LED  
                byte j=7;  // LED number  // number of first LED representing minutes
                byte modmin=minute%10;
               while (i<=8){   // while loop for going through each pixel, counts to 64 as each pixel is represented as a bit value and 60 seconds require 6 bits, 6 bits == 64
                              //Serial.println("entering while loop");
                                comp=0;  // initializing the comparator, not really necessary but doesn't hurt
                                comp=i&modmin; // ANDing the bit number and the second value to see if the LED representing the bit is required to represent the value or not, eg 2 = B0000 0010 therefore only the 2nd pixel will light up 
                              //  Serial.print("bit number:  ");
                              //  Serial.println(i);
                              //   Serial.print("xor value:  ");
                              //  Serial.println(comp);
                                
                                if(comp==1){ // if pixel is valid then light her up!
                                            //    Serial.print("comp ==1, pixel:  ");
                                              sstrip.setPixelColor(j,i+100,00,0);
                                              //sstrip.show();
                                             // Serial.println("conditional if");
                                            //  Serial.println(j);
                                            }
                              
                                  else{  sstrip.setPixelColor(j,0,0,0); // else shut her down
                                       // sstrip.show();
                                      }
                                  sstrip.show();  // show the changes made to the pixels
                                  i=i*2;  // update the values
                                  j++;
                            }
                            // end of while loop
                              
              
              
              
              
              
                     // initialization and decleration of variables for 10-60 seconds (the tens units)
                      byte k=1; // byte value of LED
                      byte l=13;  // LED number, LEDs are placed in reverse order because of how the LEDs are layed out in one continous strand   // number of last LED represnting minutes
                      byte tenmin=minute/10;  // tensec == 10s unit of seconds
                       while (k<=4){   // while loop for going through each pixel, counts to 64 as each pixel is represented as a bit value and 60 seconds require 6 bits, 6 bits == 64
                              //Serial.println("entering while loop");
                              
                                comp=0;  // initializing the comparator, not really necessary but doesn't hurt
                                comp=k&tenmin; // ANDing the bit number and the 10s second value to see if the LED representing the bit is required to represent the value or not, eg 2 = B0000 0010 therefore only the 2nd pixel will light up 
                              //  Serial.print("bit number:  ");
                              //  Serial.println(i);
                              //   Serial.print("xor value:  ");
                              //  Serial.println(comp);
                                
                                if(comp==1){ // if pixel is valid then light her up!
                                            //    Serial.print("comp ==1, pixel:  ");
                                              sstrip.setPixelColor(l,k+100,00,0);
                                              //sstrip.show();
                                             // Serial.println("conditional if");
                                            //  Serial.println(j);
                                            }
                              
                                  else{  sstrip.setPixelColor(l,0,0,0); // else shut her down
                                       // sstrip.show();
                                      }
                                  sstrip.show();  // show the changes made to the pixels
                                  k=k*2;  // update the values
                                  l--;
                            }
                            // end of while loop
                      
                    
                    i=1; // reinitialize the variables for the next time the function call takes place (legacy code, no longer necessary)
                    j=7;
                    k=1;
                    l=13;
                     
              }




void hlight(){
                // initialization and decleration of variables for 0-9 seconds (ones units)
                byte i=1;  // byte value of LED  
                byte j=14;  // LED number  // number of first LED representing hours
                byte modhour=hour%10;
               while (i<=8){   // while loop for going through each pixel, counts to 64 as each pixel is represented as a bit value and 60 seconds require 6 bits, 6 bits == 64
                              //Serial.println("entering while loop");
                                comp=0;  // initializing the comparator, not really necessary but doesn't hurt
                                comp=i&modhour; // ANDing the bit number and the second value to see if the LED representing the bit is required to represent the value or not, eg 2 = B0000 0010 therefore only the 2nd pixel will light up 
                              //  Serial.print("bit number:  ");
                              //  Serial.println(i);
                              //   Serial.print("xor value:  ");
                              //  Serial.println(comp);
                                
                                if(comp==1){ // if pixel is valid then light her up!
                                            //    Serial.print("comp ==1, pixel:  ");
                                              sstrip.setPixelColor(j,i+100,00,0);
                                              //sstrip.show();
                                             // Serial.println("conditional if");
                                            //  Serial.println(j);
                                            }
                              
                                  else{  sstrip.setPixelColor(j,0,0,0); // else shut her down
                                       // sstrip.show();
                                      }
                                  sstrip.show();  // show the changes made to the pixels
                                  i=i*2;  // update the values
                                  j++;
                            }
                            // end of while loop
                              
              
              
              
              
              
                     // initialization and decleration of variables for 10-60 seconds (the tens units)
                      byte k=1; // byte value of LED
                      byte l=19;  // LED number, LEDs are placed in reverse order because of how the LEDs are layed out in one continous strand   // number of last LED
                      byte tenhour=hour/10;  // tensec == 10s unit of seconds
                       while (k<=2){   // while loop for going through each pixel, counts to 2 as each pixel is represented as a bit value of either ones or tens and 24 hours require 2 bits for the 10s value
                              //Serial.println("entering while loop");
                              
                                comp=0;  // initializing the comparator, not really necessary but doesn't hurt
                                comp=k&tenhour; // ANDing the bit number and the 10s second value to see if the LED representing the bit is required to represent the value or not, eg 2 = B0000 0010 therefore only the 2nd pixel will light up 
                              //  Serial.print("bit number:  ");
                              //  Serial.println(i);
                              //   Serial.print("xor value:  ");
                              //  Serial.println(comp);
                                
                                if(comp==1){ // if pixel is valid then light her up!
                                            //    Serial.print("comp ==1, pixel:  ");
                                              sstrip.setPixelColor(l,k+100,00,0);
                                              //sstrip.show();
                                             // Serial.println("conditional if");
                                            //  Serial.println(j);
                                            }
                              
                                  else{  sstrip.setPixelColor(l,0,0,0); // else shut her down
                                       // sstrip.show();
                                      }
                                  sstrip.show();  // show the changes made to the pixels
                                  k=k*2;  // update the values
                                  l--;
                            }
                            // end of while loop
                      
                    
                    i=1; // reinitialize the variables for the next time the function call takes place (legacy code, no longer necessary)
                    j=14;
                    k=1;
                    l=19;
                     
              }
