int ledlight[7];
int button_pressed[7];
int level=1;
int j=0;
int counter=0;
int check=0;
bool generate=true;

long randNumber;

void setup() {
  //butões
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  //leds
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(18,OUTPUT);
  pinMode(19,OUTPUT);

  Serial.begin(9600);
  randomSeed(analogRead(1));
}

void loop() {
  if(level == 5){
    generate = false;
  }

  //gerar sequência random
  if(generate){
    for(int i=0; i<=2+level; i++){
      ledlight[i]=random(2,6);
    }
    for(int i=0; i<=2+level; i++){
      digitalWrite(ledlight[i],HIGH);
      delay(250);
      digitalWrite(ledlight[i],LOW);
      delay(250);
    }
    generate=false; 
    Serial.println(ledlight[0]);
    Serial.println(ledlight[1]);
    Serial.println(ledlight[2]);
    Serial.println(ledlight[3]);
    Serial.println(ledlight[4]);
    Serial.println(ledlight[5]);
    Serial.println(ledlight[6]);
  }

  //sequencia de butões
  if(!generate){
    for(int i=8; i<12; i++){
      if(digitalRead(i)==HIGH && counter == 0){
        button_pressed[j] = i - 6;
        j++;
        counter = 500;
      }  
    }
    if(counter > 0){
      counter--;  
    }
    delay(1);
  }
  if(j==3+level){
    Serial.println("");
    for(int i=0; i<7; i++){
     if (ledlight[i]== button_pressed[i]){
      check++;
     } 
    }
  
    if(check!=7){
      digitalWrite(18,HIGH);
      delay(500);
      digitalWrite(18,LOW);
      j=0;
      check=0;
    }
    else{
      digitalWrite(19,HIGH);
      delay(500);
      digitalWrite(19,LOW); 
      level++;  
      j=0;
      generate=true; 
      check=0;
    }
  }
}
