#include <NewPing.h>
//NewPing sonar(10,11, 20);   //TRIG,ECHO,MAXDISTANCE in cm


int number[9][8] = {              //i        //number array
  {0, 0, 1, 1, 1, 0, 0, 0},//1      0
  {1, 1, 0, 1, 1, 1, 0, 1},//2      1
  {0, 1, 1, 1, 1, 1, 0, 1},//3      2
  {0, 0, 1, 1, 1, 0, 1, 1},//4      3
  {0, 1, 1, 1, 0, 1, 1, 1},//5      4
  {1, 1, 1, 1, 0, 1, 1, 1},//6      5
  {0, 0, 1, 1, 1, 1, 1, 0},//7      6
  {1, 1, 1, 1, 1, 1, 1, 1},//8      7
  {0, 0, 1, 1, 1, 1, 1, 1},//9      8
};


int pins[8] = {2, 3, 4, 5, 6, 7, 8, 9};     //for segment

int distance = 0;
int distancePOT = 0;
int distanceMAP = 0;
int sevenSeg = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(A5,OUTPUT);    //A5 green
  pinMode(A4,OUTPUT);    //A4 yellow
  pinMode(A3,OUTPUT);    //A3 red
  analogWrite(A5,0);
  analogWrite(A4,0);
  analogWrite(A3,0);

  for(int i = 0;i<8;i++){        //7-segment
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }
  
  Serial.begin(9600);
  delay(100);
}

//------------Change here to set your own distances
int MAX_DISTANCE = 30;
int MIN_DISTANCE = 15;
//------------
void loop() {
  // put your main code here, to run repeatedly:
  
  distancePOT = analogRead(A0);                 //reading from potenciometer
  distanceMAP = map(distancePOT,0,1023,MIN_DISTANCE,MAX_DISTANCE);   //mapped max distance
  sevenSeg = map(distanceMAP+1, MIN_DISTANCE,MAX_DISTANCE,9,1);        // mapped seven segment dispaly
  
  NewPing sonar(10,11, distanceMAP);              //trig,echo

  Serial.print("SEGMENT NUMBER: ");
  Serial.println(sevenSeg);

  switch(sevenSeg){                               //7 segment 
    case 1:
      for (int i = 0; i < 8; i++) {
        digitalWrite(pins[i], number[0][i]);
      }
      break;
    case 2:
      for (int i = 0; i < 8; i++) {
        digitalWrite(pins[i], number[1][i]);
      }
      break;
    case 3:
      for (int i = 0; i < 8; i++) {
        digitalWrite(pins[i], number[2][i]);
      }
      break;
    case 4:
      for (int i = 0; i < 8; i++) {
        digitalWrite(pins[i], number[3][i]);
      }
      break;
    case 5:
      for (int i = 0; i < 8; i++) {
        digitalWrite(pins[i], number[4][i]);
      }
      break;
    case 6:
      for (int i = 0; i < 8; i++) {
        digitalWrite(pins[i], number[5][i]);
      }
      break;
    case 7:
      for (int i = 0; i < 8; i++) {
        digitalWrite(pins[i], number[6][i]);
      }
      break;
    case 8:
      for (int i = 0; i < 8; i++) {
        digitalWrite(pins[i], number[7][i]);
      }
      break;
    case 9:
      for (int i = 0; i < 8; i++) {
        digitalWrite(pins[i], number[8][i]);
      }
      break;
    default:
      break;  
  }
  
  distance = sonar.ping_cm();                   //MAIN ULTRASOUND SENSOR FUNCTION

  int UpperBound = distanceMAP * 0.7;           //70%                    
  int LowerBound = distanceMAP * 0.35;          //35%

  //Serial.print("UPPER BOUND");
  //Serial.println(UpperBound);
  //Serial.print("LOWER BOUND");
  //Serial.println(LowerBound);
  
  Serial.print("Distance MAX: ");
  Serial.println(distanceMAP);
  
  Serial.print("Distance: ");
  Serial.println(distance);
  
  if(distance == 0){
    analogWrite(A5,0);
    analogWrite(A4,0);
    analogWrite(A3,0);
  }
  else if(distance >= UpperBound){                              //green
    analogWrite(A5,1023);
    analogWrite(A4,0);
    analogWrite(A3,0);
  }
  else if(distance >= LowerBound && distance < UpperBound){     //yellow
    analogWrite(A5,0);
    analogWrite(A4,1023);
    analogWrite(A3,0);
  }
  else{                                                         //red
    analogWrite(A5,0);
    analogWrite(A4,0);
    analogWrite(A3,1023);
  }

  delay(100);

}
