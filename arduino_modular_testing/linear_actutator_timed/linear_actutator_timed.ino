#define feedrate 17 //in mm/sec
#define home_position 10/// the place where you want motor to start (value in mm from fully closed postion)
#define end_position 140 // the place where you want to end the stroke (value in mm) relative to home 
#define invert 0 // if the motor driver reponse is opposite make this one.
#define driver_A_Pin 4
#define driver_B_Pin 5
void move_home(void);
void move_out(void);
void close_act(void);
void setup() {


  Serial.begin(9600);
  pinMode(driver_A_Pin,OUTPUT);
  pinMode(driver_B_Pin,OUTPUT);
  delay(10);
  digitalWrite(driver_A_Pin,LOW);
  digitalWrite(driver_B_Pin,LOW);
  // put your setup code here, to run once:
 Serial.println("press 'h' to get to home");
 while(!Serial.available()){
  delay(5);
  }
 char recv = Serial.read();
 if(recv == 'h')
      move_home();
else{
  return;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("press 's' to start the program");
  while(!Serial.available()){
  delay(5);
  }
    char recieved = Serial.read();
   if(recieved != 's')
                  return;
    delay(10);
    move_out();
    ask:
 Serial.print("press 'c' to close the actuator");
  while(!Serial.available()){
  delay(5);
  }   
  recieved = Serial.read();  
  
  if(recieved != 'c')
       goto ask;
  delay(10);
      close_act();  
   }
  






void move_home(){
  
  if(invert){
  digitalWrite(driver_B_Pin,HIGH);
  digitalWrite(driver_A_Pin,LOW);
  int secs_to_mm = (home_position/feedrate)*1000;
  int init = millis();
  while(millis()-init < secs_to_mm){
    delay(1);
    }
  digitalWrite(driver_B_Pin,LOW);
  digitalWrite(driver_A_Pin,LOW);      
    
    }
    else{
      
       digitalWrite(driver_A_Pin,HIGH);
  digitalWrite(driver_B_Pin,LOW);
  int secs_to_mm = (home_position/feedrate)*1000;
  int init = millis();
  while(millis()-init < secs_to_mm){
    delay(1);
    }
  digitalWrite(driver_A_Pin,LOW);
  digitalWrite(driver_B_Pin,LOW);
      
      
      
      }
  }




  void move_out(){
    
  if(invert){
  digitalWrite(driver_B_Pin,HIGH);
  digitalWrite(driver_A_Pin,LOW);
  int secs_to_mm = (end_position/feedrate)*1000;
  int init = millis();
  while(millis()-init < secs_to_mm){
    delay(1);
    }
  digitalWrite(driver_B_Pin,LOW);
  digitalWrite(driver_A_Pin,LOW);      
    
    }
    else{
      
       digitalWrite(driver_A_Pin,HIGH);
  digitalWrite(driver_B_Pin,LOW);
  int secs_to_mm = (end_position/feedrate)*1000;
  int init = millis();
  while(millis()-init < secs_to_mm){
    delay(1);
    }
  digitalWrite(driver_A_Pin,LOW);
  digitalWrite(driver_B_Pin,LOW);
      }  
    }

    void close_act(){
  if(invert){
  digitalWrite(driver_A_Pin,HIGH);
  digitalWrite(driver_B_Pin,LOW);
  int secs_to_mm = (end_position/feedrate)*1000;
  int init = millis();
  while(millis()-init < secs_to_mm){
    delay(1);
    }
  digitalWrite(driver_A_Pin,LOW);
  digitalWrite(driver_B_Pin,LOW);      
    
    }
    else{
      
       digitalWrite(driver_B_Pin,HIGH);
  digitalWrite(driver_A_Pin,LOW);
  int secs_to_mm = (end_position/feedrate)*1000;
  int init = millis();
  while(millis()-init < secs_to_mm){
    delay(1);
    }
  digitalWrite(driver_B_Pin,LOW);
  digitalWrite(driver_A_Pin,LOW);
      }      
    }
