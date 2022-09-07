/*        Your Name & E-mail: Angelica Simityan   asimi003@ucr.edu

 *         Discussion Section: 021

 *         Assignment: Lab # 7 Exercise # 1

 *         Exercise Description: [optional - include for your own benefit]

 *

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *

 *         Demo Link:

 https://youtu.be/J4UBqfmNO3Q

 */

#include <LiquidCrystal.h>

enum States{INIT, S0, S1} SM1_state;
unsigned long lastRan;
const unsigned long period = 100;



// Array of Output Pin variables, set to the pins being used
const int rs = 4, en = 5, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
const int xAxis = A0; // Recall that A0 is really a number under the hood.
int b_buf = 0;
int btn_state = 9;
int code_true = 0;
const int button = 2;
int count = 0;

int cursorinc = 0;

int row = 0;
int col = 0;

bool timervalid = false;

unsigned long timer;

bool caps = false;

bool clearscr = false;


int SM1_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case INIT:
         //State Transition
            state = S0;
        break;
      case S0:
        
         //State Transition
         if ( ((millis() - timer) > 2000) && (timervalid == true))
         {
            timervalid = false;
            state = S1;
         }
        break;
      case S1:
            if (clearscr == true){
                state = S0;
                clearscr = false;
               
            }
            else{
                state = S1;
            }
             //State Transition
        break;
    }
    switch(state){ // State Action
      case INIT:
         //State Action
        break;
      case S0:
            //State Action
       
            // if the joystick or button are in center position
          if( cursorinc != 32)
          {
            if(btn_state == 9){

             if(cursorinc >= 16)
             { 
               row =1;
               col = cursorinc - 16;
             }
             else{
               row = 0;
               col = cursorinc;
             }


             lcd.setCursor(col,row);

              if((analogRead(A0) > 850) && !(analogRead(A1) < 200) && !(analogRead(A1) > 600))
              {
                 
                 btn_state =2;
                 if (caps == false){
                  
                   lcd.print("a");
                 }
                 else{
                  lcd.print("A");
                  caps = false;
                 }
                 cursorinc++;
              }
              else if ((analogRead(A0) < 250) && !(analogRead(A1) < 200) && !(analogRead(A1) > 600))
              {
                
                btn_state = 3;
                 if (caps == false){
                  
                   lcd.print("b");
                 }
                 else{
                  lcd.print("B");
                  caps = false;
                 }
                cursorinc++;
              }
              else if ((analogRead(A1) < 200) && !(analogRead(A0) > 850) && !(analogRead(A0) < 250))
              {
                
                btn_state = 0;
                 if (caps == false){
                  
                   lcd.print("c");
                 }
                 else{
                  lcd.print("C");
                  caps = false;
                 }
                cursorinc++;
              }
              else if (analogRead(A1) > 600 && !(analogRead(A0) > 850) && !(analogRead(A0) < 250))
              {
                
                btn_state = 1;
                 if (caps == false){
                  
                   lcd.print("d");
                 }
                 else{
                  lcd.print("D");
                  caps = false;
                 }
                cursorinc++;
              }
              else if ((analogRead(A0) > 850) && (analogRead(A1) < 200))
              {
                
                btn_state = 4;
                 if (caps == false){
                  
                   lcd.print("e");
                 }
                 else{
                  lcd.print("E");
                  caps = false;
                 }
                cursorinc++;
              }
              else if ((analogRead(A0) > 850) && (analogRead(A1) > 600))
              {
                
                btn_state = 5;
                 if (caps == false){
                  
                   lcd.print("f");
                 }
                 else{
                  lcd.print("F");
                  caps = false;
                 }
                cursorinc++;
              }
              else if ((analogRead(A0) < 250) && (analogRead(A1) < 200))
              {
                
                btn_state = 6;
                 if (caps == false){
                  
                   lcd.print("g");
                 }
                 else{
                  lcd.print("G");
                  caps = false;
                 }
                cursorinc++;
              }
               else if ((analogRead(A0) < 250) && (analogRead(A1) > 600))
              {
                
                btn_state = 7;
                 if (caps == false){
                  
                   lcd.print("h");
                 }
                 else{
                  lcd.print("H");
                  caps = false;
                 }
                cursorinc++;
              }
        
              
              
            }
            
          }
          if (btn_state == 9){
               if (digitalRead(button) == 0){
                  btn_state = 8;
                  caps = true;
                  timer = millis();
                  timervalid = true;
              }
            }
          
            
            //If the joystick or button are still pressed
            else
            {
              
              //checks if the up down is on center position
                if (btn_state != 8){
                
                if((analogRead(A1) < 850 && analogRead(A1) >250) && (analogRead(A0) < 850 && analogRead(A0) >250)){
                      //when released                
                      btn_state = 9;
                      timervalid = false;
                  
                     }
               
              
                }
 
              
             

             
             //checks if the button is released
             if(btn_state == 8){
              if(digitalRead(button) == 1){
                btn_state = 9;
                timervalid = false;
                  }
               
               
              
              
             }
              
            
            
            }
         
         
        
         //State Action
        break;
      case S1:
            //State Action
          
            lcd.clear();
            clearscr = true;
            cursorinc = 0;
            caps = false;
         
         //State Action
        break;
     }

    return state;
}


void setup() {
    // OUTPUT is a defined macro in Arduino!

     lcd.begin(16,2);
    for(int i = 0; i < b_size; i++)
        {
            pinMode(b[i], OUTPUT);
           
        }
        pinMode(button, INPUT_PULLUP);
    // We will also read from the serial monitor
    Serial.begin(9600);
    
}

void loop() {
    
    if ((millis() - lastRan) > period) {     
      SM1_state = (States)SM1_Tick(SM1_state);        
      lastRan = millis();   
     }  
}
