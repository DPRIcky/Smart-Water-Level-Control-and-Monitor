#define motor1_A  A0
#define motor1_B  A1

float pi = 3.14;
float rpm = 0.0;
float height = 0.0;
float userFlowRate = 0.0;
float userTime = 0.0;
float computedFlowRate = 0.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(motor1_A,OUTPUT);
  pinMode(motor1_B,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(A2);
  Serial.println(value);
  Serial.println("Enter Your Desired time to fill the tank: ");
  while (Serial.available()==0){}             // wait for user input
  userTime = Serial.parseFloat();
  Serial.println(userTime);
  userFlowRate = (pi*3.5*3.5*461.25)/userTime;
  Serial.println(userFlowRate);
  rpm = (9000/19.73)*userFlowRate;
  Serial.print("Motor RPM: ");
  Serial.print(rpm);
  Serial.println("Revolution/Min");
  
  while (value<=461.25){                        // 5% tallerance on 450
    analogWrite(motor1_A,rpm);
    analogWrite(motor1_B,0);
    value = analogRead(A2);
   }
  analogWrite(motor1_A,0);
  analogWrite(motor1_B,0);
  delay(20000);

  value = analogRead(A2);
  Serial.print("The Tank level at initial of 2nd stage: ");
  Serial.println(value);

  while (438.75<=value && value<=600){
    analogWrite(motor1_A,0);
    analogWrite(motor1_B,0);
    Serial.println("The Tank is Full!");
    Serial.println(value);
    delay(20000);
    value = analogRead(A2);
    
    Serial.println(value);
    }
  if(value<438.75){
    Serial.println("Enter Your Desired Time for second phase: ");
    delay(5000);
    if (Serial.available() == 1){}  // check for user input
     userTime = Serial.parseFloat();
     if (userTime == 0.0){
       rpm = (9000/19.73)*userFlowRate;
       Serial.print("New Motor RPM: ");
       Serial.print(rpm);
       Serial.println("Revolution/Min");
       while (value<=461.25){                        // 5% tallerance on 450
         analogWrite(motor1_A,rpm);
         analogWrite(motor1_B,0);
         value = analogRead(A2);
       }
       analogWrite(motor1_A,0);
       analogWrite(motor1_B,0);
       Serial.println("The Tank is Full!");
       delay(20000);
     }
     else{
       value = analogRead(A2);
       Serial.println(value);
       computedFlowRate = (pi*3.5*3.5*(461.25 - value))/userTime;
       rpm = (9000/19.73)*computedFlowRate;
       Serial.print("New Motor RPM: ");
       Serial.print(rpm);
       Serial.println("Revolution/Min");
       while (value<=461.25){                        // 5% tallerance on 450
         analogWrite(motor1_A,rpm);
         analogWrite(motor1_B,0);
         value = analogRead(A2);
         }
       analogWrite(motor1_A,0);
       analogWrite(motor1_B,0);
       Serial.println("The Tank is Full!");
       delay(20000);
      }
  }   
}
