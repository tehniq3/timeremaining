  /*
 * time remaining test (countdown big big number)
 * original sketch by Nicu FLORICA (niq_ro)
 */


// counter test

unsigned long timp, timp0, timp1, dtimp;
int zi, ora, minut, secunda;
unsigned long rest, dzi, dora;
int dminut, dsecunda;
int clocire = 21;
int pas = 100;


#define START 8    // START switch
#define STOP 7    // STOP switch

void setup() {
 Serial.begin(9600);

// set push buttons for menu
  pinMode(START, INPUT); 
  pinMode(STOP, INPUT);  
  digitalWrite(START, HIGH); // pull-ups on
  digitalWrite(STOP, HIGH); // pull-ups on

timp1 = clocire * 86400; 
}

void loop() {

if (dtimp > 0)
{
dtimp = dtimp - pas;
Serial.println(dtimp);
dzi = dtimp/86400L;
rest = dtimp%86400L;
dora = rest/3600;
rest = rest%3600;
dminut = rest/60;
dsecunda = rest%60;

  
  Serial.println("Time Remaining:"); 
  if (dzi < 10) Serial.print(" ");  
  Serial.print(dzi); 
  Serial.print("d:");
  if (dora < 10) Serial.print(" ");  
  Serial.print(dora); 
  Serial.print("h:");  
  if (dminut < 10) Serial.print(" ");  
  Serial.print(dminut); 
  Serial.print("m:");  
  if (dsecunda < 10) Serial.print(" ");  
  Serial.print(dsecunda); 
  Serial.println("s ");    
}

if (digitalRead(START) == LOW)
{
dtimp = clocire * 86400;   // initial time
}
  
if (digitalRead(STOP) == LOW)
{
dtimp = 0;
Serial.print("stop");
}

  delay(600); 
}
