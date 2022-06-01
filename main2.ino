#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <CapacitiveSensor.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    12
#define OLED_CS    11
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

CapacitiveSensor   cs_15_4 = CapacitiveSensor(15,4);
CapacitiveSensor   cs_19_2 = CapacitiveSensor(19,2);

//int player1_score = 0;
//int player2_score = 0;
long  randNumber1;
long  randNumber2;


const int ledPin1 = 7; 
const int ledPin2 = 6;
const int ledPin3 = 5;
const int buttonPin1 = 1;// the pin our push button is on
const int buttonPin2 = 0;// the pin our push button is on
const int capButton1 = 2;
const int capButton2 = 4;

int prestate1 = 0;
int prestate2 = 0;
int prestate3 = 0;
int prestate4 = 0;

bool runningg = false;

void setup() {
 Serial.begin(9600);
 
 randomSeed(analogRead(0));

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  pinMode(capButton1, INPUT);  //capacitive button1
  pinMode(capButton2, INPUT);
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);


  display.clearDisplay();
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' fon
  display.write("  Be READY   to       start   the GAME");
  display.display();
  delay(1000);
}

void loop() {
  display.clearDisplay();
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' fon
  display.write("  Be READY     to      start   the GAME");
  display.display();
  delay(500);
  //if(digitalRead(buttonPin1) == LOW && runningg == false) {
  if(Serial.parseInt() == 1) {
    runningg = true;
    display.clearDisplay();
    display.setTextSize(2);      // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);     // Start at top-left corner
    display.cp437(true);         // Use full 256 char 'Code Page 437' fon
    display.write("    Pay \n attention   to the     LEDS\n\n");
   
    display.display();
    delay(1000);

    randNumber1 = random(1,4); //nr de apasari
    randNumber2= random(1000,4000); //timp

    int p1_pushes=0;
    int p2_pushes=0;

    delay(randNumber2);

    switch (randNumber1){
      case 1:
        digitalWrite(5, HIGH);
        delay(400);
        digitalWrite(5, LOW);
      break;

      case 2:
        digitalWrite(5, HIGH);
        digitalWrite(6, HIGH);
        delay(600);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
      break;

      case 3:
        digitalWrite(5, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        delay(800);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
      break;
    }

    while(randNumber1 >= p1_pushes || randNumber2 >= p2_pushes) {
      
     if( cs_19_2.capacitiveSensor(50)>3000 && prestate3 == 0) {    //capacitive button 1
        p2_pushes++;
        Serial.println(p1_pushes);
        Serial.println(cs_19_2.capacitiveSensor(50));
        prestate3 = 1;
        delay(200);
      }
      else if(cs_19_2.capacitiveSensor(50)<3000){
      prestate3 = 0;
    //  Serial.println(cs_19_2.capacitiveSensor(50));
      }


      if( cs_15_4.capacitiveSensor(50)>100 && prestate4 == 0) {  // capacitive button 2
        p1_pushes++;
        Serial.println(p1_pushes);
        Serial.println(cs_19_2.capacitiveSensor(50));
        prestate4 = 1;
        delay(200);
      }
      else if(cs_19_2.capacitiveSensor(50)<100){
      prestate4 = 0;
      //Serial.println(cs_19_2.capacitiveSensor(50));
      }
     


      
      if(digitalRead(buttonPin1) == LOW  && prestate1 == 0) {   //normal button 1
        p1_pushes++;
        Serial.println(p1_pushes);
        
        prestate1 = 1;
        delay(200);
      }
      else if(digitalRead(buttonPin1) == HIGH){
      prestate1 = 0;
      }
      
      if(digitalRead(buttonPin2) == LOW  && prestate2 == 0) {      //normal button 2
        p2_pushes++;
        Serial.println(p2_pushes);
        Serial.println(cs_15_4.capacitiveSensor(50));
        prestate2 = 1;
        delay(200);
      }
      else if(digitalRead(buttonPin2) == HIGH){
        prestate2 = 0;
       // Serial.println(cs_15_4.capacitiveSensor(50));
      }
      if(randNumber1 == p1_pushes) {
        Serial.println("player1 wins");
display.clearDisplay();
    display.setTextSize(2);      // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);     // Start at top-left corner
    display.cp437(true);         // Use full 256 char 'Code Page 437' fon
    display.write("\n  Player1     WINS \n\n");

    display.display();
   delay(10000);
    
        break;
        }
      if(randNumber1 == p2_pushes) {
        
        Serial.println("player2 wins");  
        display.clearDisplay();
    display.setTextSize(2);      // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);     // Start at top-left corner
    display.cp437(true);         // Use full 256 char 'Code Page 437' fon
    display.write("\n  Player2     WINS \n\n");
     display.display();
    delay(10000);
  
        
        break;
        }
     
    }

    runningg = false;

    //if(randNumber1 == p1_pushes) Serial.println("player1 wins");
    //else Serial.println("player2 wins");
  }
}
/*

int digitalVal1 = digitalRead(buttonPin1); // Take a reading
int digitalVal2 = digitalRead(buttonPin2); // Take a reading
  if(LOW == digitalVal1 && running==false)
  {
   running=true;
   display.clearDisplay();
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' fon
  display.write("Player1 0p\n\n");
   display.write("Player2 0p");
display.display();
  delay(1000);
   
     randNumber1 = random(1,4);
     randNumber2= random(1000,8000);

     delay(randNumber2);
     
switch (randNumber1){
 
  case 1:
    digitalWrite(5, HIGH);
    delay(400);
    digitalWrite(5, LOW);
    break;

    case 2:
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    delay(600);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    break;

case 3:
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    delay(800);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
     digitalWrite(7, LOW);
    break;
 
}


  Serial.println(randNumber1);
  Serial.println(randNumber2);
  Serial.println("da");
  Serial.println(p1_pushes);
  Serial.println(p2_pushes);
  Serial.println("da");
  delay(100); 

   if(LOW == digitalRead(buttonPin1))
  {
     Serial.println(p1_pushes);
    p1_pushes=p1_pushes+1;
    //delay(100); 
    
  }

   if(LOW == digitalVal2)
  {
    Serial.println(p2_pushes);
    p2_pushes=p2_pushes+1;
   // delay(250); 
    
    
  }

  if(p1_pushes== randNumber1)
  {
    player1_score++;
    
  }
   if(p2_pushes== randNumber1)
  {
    player2_score++;
  
  }

   if(p1_pushes> randNumber1)
  {
    p1_pushes=0;
    
  }
   if(p2_pushes> randNumber1)
  {
     p2_pushes=0;
  }
  

   
  }
 

}
*/
