#define LED  9  // choose the pin for the RELAY
#define PIR 4 
int ldr=0;
int pir=LOW;
int val;
void setup()
{    
  Serial.begin(9600);
  pinMode(LED, OUTPUT); // declare lamp as output
  pinMode(PIR,INPUT);
  //pinMode(A0,INPUT);  
}
void loop() 
{
  ldr = analogRead(A1);
  val=(255.0/1023.0)*ldr;
  pir = digitalRead(PIR); // read input value
  Serial.println(ldr);
  Serial.println(val);
  Serial.println(pir);

 if((ldr<=300) && ( pir==HIGH) ){
       digitalWrite(LED,HIGH);  // Turn ON the light
       delay(250);
       //pir=HIGH; 
       
 
}
else {
  
       digitalWrite(LED,LOW); // Turn OFF the light
      // pir=LOW;
}
 }
