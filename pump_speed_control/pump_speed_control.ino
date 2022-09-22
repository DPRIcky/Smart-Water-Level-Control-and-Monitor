int a = 8;
int b = 9;
void setup() {
  // put your setup code here, to run once:
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(a,LOW);
    digitalWrite(b,HIGH);
}
