#define motor1_A  A0
#define motor1_B  A1

float pi = 3.14;
float rpm = 0.0;
float userFlowRate = 0.0;
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

  Serial.println("Enter Your Desired Flow Rate: ");
  while (Serial.available()==0){}             // wait for user input
  userFlowRate = Serial.parseFloat();
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
    Serial.println("Enter Your Desired Flow Rate for second phase: ");
    delay(5000);
    if (Serial.available() == 1){}  // check for user input
      int userflowRate = Serial.parseFloat();
      if (userflowRate == 0.0){
        float height = analogRead(A2);
        Serial.println(height);
        computedFlowRate = ((461.25 - height)/461.25)*userFlowRate;
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
      else{
        rpm = (9000/19.73)*userflowRate;
        Serial.print("New Motor RPM: ");
        Serial.print(rpm);
        Serial.println("Revolution/Min");
        float t_2nd = pi*0.035*0.035*(461.25- analogRead(A2));
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
