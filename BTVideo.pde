import processing.serial.*;
Serial myPort;
String sensorReading="";
PFont font;
import ddf.minim.*;


import processing.video.*;
Movie movie0;
Movie movie1;
Movie movie2;

void setup() {
  size(displayWidth, displayHeight);
  movie0 = new Movie(this, "movie0.mov");
  movie1 = new Movie(this, "movie1.mov");
  myPort = new Serial(this, Serial.list()[2], 9600);
  myPort.bufferUntil('\n');
  font = createFont(PFont.list()[2],32);
  textFont(font);
}

void draw() {
  //The serialEvent controls the display
}  

void serialEvent (Serial myPort){
 sensorReading = myPort.readStringUntil('\n');
  if(sensorReading != null){
    sensorReading=trim(sensorReading);
    println(sensorReading);
  }
  writeText("Card Number: " + sensorReading);
  if(int(sensorReading) == 0){
    println("detect2");
    movie1.stop();
    movie0.play();
  }
  if(int(sensorReading) == 1){
    println("detect1");
    movie0.stop();
    movie1.play();
  }
}


void writeText(String textToWrite){
  background(255);
  fill(0);
  text(textToWrite, width/20, height/2);   
}

void stop()
{
  super.stop();
}
