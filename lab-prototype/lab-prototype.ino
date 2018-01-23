/*
This program allows the user to input coordinate values (mimicking the input from a TFT screen) and 
writes html code to an svg file to draw a line connecting the coordinates inputted.
Reference to https://batchloaf.wordpress.com/2011/11/23/simple-data-plotting-from-a-c-console-application-using-svg/.
Function "void serialFlush();" obtained from https://forum.arduino.cc/index.php?topic=234151.0.
*/
#include <stdio.h>
#include <stdlib.h>
//struct for contructing colors
typedef struct{
  int r,g,b;
}color;
//Some comments is code that will be used when be get the hardware
//maxX and maxY are the values of the size of the screen
//int maxX=200;
//int maxY=500;
//varaible x and y are used to get the coordinates from the user
//reseting Serial buffer
void serialFlush(){
  while(Serial.available()>0){
    char reset = Serial.read();
  }
}
int x,y;
int i=0;
int sel;
//construct color black(0) and red(1) more colors can be easily added
color var[]={{0,0,0},{255,0,0}};
void setup (){
  Serial.begin(9600);
}
void loop(){
//assigns a name to the file
char filename[10];
sprintf(filename,"img%d.svg",i);
Serial.println(filename);
//initializes the file
//FILE *f = fopen(filename, "w");
//sets the max of the heigh and width of the file
//fprintf(f,"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"%d\" height=\"%d\">",maxX,maxY);
Serial.println("<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"500\">");
//print out the code (html) that would draw several lines between all coordinates, till the user inputs 1 has a coordinate value
while(1){
  //select colors
  while(Serial.available()==0);
  sel=Serial.parseInt();
  serialFlush();
  Serial.print("<polyline style=\"fill:none;stroke:rgb(");
  Serial.print(var[sel].r);
  Serial.print(",");
  Serial.print(var[sel].g);
  Serial.print(",");
  Serial.print(var[sel].b);
  Serial.print(");stroke-width:3\" points=\"");
  //print out the code (html) that draws a line between two coordinates, till the user inputs 0 or 1
  while(1){
    while(Serial.available()==0);
    x=Serial.parseInt();
    serialFlush();
    while(Serial.available()==0);
    y=Serial.parseInt();
    serialFlush();
    if(x!=0&&x!=1) {Serial.print(x);Serial.print(",");Serial.print(y);Serial.print(" ");};
    if(x==0||x==1) break;
  }
  Serial.println("\"/>");
  if(x==1) break;
}
//prints out the closing tag of the file
Serial.print("</svg>\n\n");
//fclose(f);
i++;
}

