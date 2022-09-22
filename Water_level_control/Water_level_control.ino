//  THE TEAM OF E INFOTAINMENT   
      //https://www.youtube.com/channel/UCr688fGR4aI_tWYD-YKYrzQ
      //https://www.youtube.com/channel/UCr688fGR4aI_tWYD-YKYrzQ
                 //please subscribe to my youtube channel
#include <LiquidCrystal.h>

int motor1_A = A0;
int motor1_B = A1;
float rpm = 0.0;
float userFlowRate = 0.0;
float vol = 0.0,l_minute;
unsigned char flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
unsigned long flow_frequency;

LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

void flow () // Interrupt function to increment flow
{
   flow_frequency++;
}
void setup()
{
   Serial.begin(9600);
   pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup Interrupt

   pinMode(motor1_A,OUTPUT);
   pinMode(motor1_B,OUTPUT);
   
   lcd.begin(16, 2);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Water FlowMeter");
   lcd.setCursor(0,1);
   lcd.print("   sensing...  ");
   delay(500);
   currentTime = millis();
   cloopTime = currentTime;
}

void loop ()
{
   currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
    cloopTime = currentTime; // Updates cloopTime
    Serial.println("Enter Your Desired Flow Rate: ");
    while (Serial.available()==0){}             // wait for user input
    userFlowRate = Serial.parseFloat();
    flow_frequency = (150/19.73)*userFlowRate;  // For Proteus only
    Serial.print("Flow Frequency: ");
    Serial.println(flow_frequency);
    rpm = (9000/19.73)*userFlowRate;
    Serial.print("Motor RPM: ");
    Serial.print(rpm);
    Serial.println("Revolution/Min");
    analogWrite(Motor1_A,rpm);
    analogWrite(Motor1_B,0);
    if(flow_frequency != 0)
    {
      
      l_minute = (flow_frequency / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Rate: ");
      lcd.print(l_minute);
      lcd.print(" L/M");
      l_minute = l_minute/60;
      lcd.setCursor(0,1);
      vol = vol +l_minute;
      lcd.print("Vol:");
      lcd.print(vol);
      lcd.print(" L");
      flow_frequency = 0; // Reset Counter
      Serial.print(l_minute, DEC); // Print litres/hour
      Serial.println(" L/Sec");
    }
    else {
      Serial.println(" flow rate = 0 ");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Rate: ");
      lcd.print( flow_frequency );
      lcd.print(" L/M");
      lcd.setCursor(0,1);
      lcd.print("Vol:");
      lcd.print(vol);
      lcd.print(" L");
    }
   }
}
