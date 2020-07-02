//voice
String voice;

//sensor
const int SL = 2; //sensor left
const int SR = 3; //sensor right
int test;

//motor
const int MR1 = 4;//sens1 right motor
const int MR2 = 5;//sens2 right motor
const int MRS = 6;//speed right motor
const int ML1 = 7;//sens1 left motor
const int ML2 = 8;//sens 2 left motor 
const int MLS = 9;//speed left motor 

//ultrason
const int trig=10;
const int echo=11;
long duration;
float distance;

//colorSensor
const int S0 = 22;
const int S1 = 23;
const int S2 = 24;
const int S3 = 25;
const int OUT = 26;
int R,G,B = 0;

//carte bluetooth(TX: transmitter;RX:receiver)


void setup() {
  Serial.begin(9600);
  
  pinMode(ML1, OUTPUT);
  pinMode(ML2, OUTPUT);
  pinMode(MLS, OUTPUT);
  pinMode(MR1, OUTPUT);
  pinMode(MR1, OUTPUT);
  pinMode(MRS, OUTPUT);
  
  pinMode(SL, INPUT);
  pinMode(SR, INPUT);

  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
}

void turnLeft(){
  digitalWrite(ML1,HIGH);
  digitalWrite(ML2,LOW);
  analogWrite(MLS,80);
  digitalWrite(MR1,LOW);
  digitalWrite(ML2,LOW);
  analogWrite(MLS,0);
    
}
void turnRight(){
  digitalWrite(ML1,LOW);
  digitalWrite(ML2,LOW);
  analogWrite(MLS,0);
  digitalWrite(MR1,HIGH);
  digitalWrite(ML2,LOW);
  analogWrite(MLS,80);
    
}
void stop(){
  digitalWrite(ML1,LOW);
  digitalWrite(ML2,LOW);
  analogWrite(MLS,0);
  digitalWrite(MR1,LOW);
  digitalWrite(ML2,LOW);
  analogWrite(MLS,0);   
}
void forward(){
  digitalWrite(ML1,HIGH);
  digitalWrite(ML2,LOW);
  analogWrite(MLS,80);
  digitalWrite(MR1,HIGH);
  digitalWrite(ML2,LOW);
  analogWrite(MLS,80); 
}
void detecterCouleurReturn(){
  // Reading the output Red
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  R = pulseIn(OUT, LOW);  
  delay(100); 
  // Reading the output Green
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  G = pulseIn(OUT, LOW);  
  delay(100);
  // Reading the output Blue
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  B = pulseIn(OUT, LOW);  
  delay(100);
  // to detect red
  if (R>20 && R<35 && G>80 && G<105 && B>70 && B<90){       
    if(test == 1){
      turnRight();
    }
    else{
      turnLeft();
    }
  }
  // to detect green
  else if (R>75 && R<100 && G>60 && G<85 && B>75 && B<95){  
    if(test == 1){
      turnRight();
    }
    else{
      turnLeft();
    }
  }
  // to detect blue
  else if (R>95 && R<115 && G>70 && G<95 && B>30 && B<55){  
    if(test == 1){
      turnRight();
    }
    else{
      turnLeft();
    }
  }
}
void detecterCouleur(){
  // Reading the output Red
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  R = pulseIn(OUT, LOW);  
  delay(100); 
  // Reading the output Green
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  G = pulseIn(OUT, LOW);  
  delay(100);
  // Reading the output Blue
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  B = pulseIn(OUT, LOW);  
  delay(100);
  // to detect red
  if (R>20 && R<35 && G>80 && G<105 && B>70 && B<90){       
    if(voice == "*table one"){
      turnRight();
      test=0;
    }
    else if(voice == "*table two"){
      turnLeft();
      test=1;
    }
  }
  // to detect green
  else if (R>75 && R<100 && G>60 && G<85 && B>75 && B<95){  
    if(voice == "*table three"){
      turnRight();
      test=0;
    }
    else if(voice == "*table four"){
      turnLeft();
      test=1;
    }
  }
  // to detect blue
  else if (R>95 && R<115 && G>70 && G<95 && B>30 && B<55){  
    if(voice == "*table five"){
      turnRight();
      test=0;
    }
    else if(voice == "*table six"){
      turnLeft();
      test=1;
    }
  }
}
void detecterObstacle(){
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance=duration*0.034/2;
  if (distance <= 20)
  {
    stop();
  }
  delay(4000);
}

void detecterVoice(){
  while (Serial.available()){ //Check if there is an available byte to read
    delay(10); //Delay added to make thing stable 
    char c = Serial.read(); //Conduct a serial read
    if (c == '#') {
      break;
      } 
    voice += c;
  }
}
void followLine(){
    if(SL==1 && SR==0){
        turnRight();
      }
    else if(SL==0 && SR==1){
        turnLeft();
      }
    else if(SL==1 && SR==0){
        forward();
      }
    else if(SL==1 && SR==1){
        stop();
        if(voice=="*return"){
          turnRight();
      }
}
}


void loop() {
  detecterVoice();
  if(voice!="*return"){
    detecterCouleur();
  }
  else{
    detecterCouleurReturn();
  }
  followLine();
  detecterObstacle(); 
}




  
