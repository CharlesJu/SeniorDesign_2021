#define IN1 7
#define IN2 8
#define ENA 9
#define ENC 0

int pot;

void setup() {
  // put your setup code here, to run once:
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(ENC, INPUT);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  Serial.begin(9600);
}

void loop() {


  
  for(int i = 0; i < 255; i++){
    analogWrite(ENA,i);
    pot = analogRead(ENC);
    Serial.println(pot);  
    delay(50);
  }

  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  for(int i = 0; i < 255; i++){
    analogWrite(ENA,i);
    pot = analogRead(ENC);
    Serial.println(pot);  
    delay(50);
  }
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
}
