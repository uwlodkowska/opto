#define STIM_PIN  9
#define BMC_PIN  11

int c;
int f;
unsigned long int settings[] = {5, 2, 3};
bool interupt = false;
bool start_stim = false;
int freq = 10;
int duty_cycle = 2;
int duration = 5;
long unsigned int on_delay;
long unsigned int off_delay;
long unsigned int t=0;

int on_delay_millis;
int on_delay_micros;
  
int off_delay_millis;
int off_delay_micros;

int loop_revs;

void setup() {
  Serial.begin(9600);
  pinMode(STIM_PIN, OUTPUT);
  pinMode(BMC_PIN, OUTPUT);
  
  
  on_delay = long(10000/freq)*long(duty_cycle);
  off_delay = long(10000/freq)*long(100-duty_cycle);

  on_delay_millis = on_delay/1000;
  on_delay_micros = on_delay%1000;
  
  off_delay_millis = off_delay/1000;
  off_delay_micros = off_delay%1000;

  loop_revs = duration*freq;
}

void loop() {
  if (t==0){
    Serial.println(micros());
  }
  while (t<loop_revs){
      //digitalWriteFast(STIM_PIN, HIGH); 
      //digitalWriteFast(BMC_PIN, HIGH); 
      PORTB = B00001010;
      //delay(on_delay_millis);
      //delayMicroseconds(on_delay_micros);
      delayMicrosAndMillis(on_delay_millis, on_delay_micros);
      //delayMicrosecondsCustom(on_delay);
      PORTB = B00000000;
      //delay(off_delay_millis);
      //delayMicroseconds(off_delay_micros);
      //digitalWriteFast(STIM_PIN, LOW);
      //digitalWriteFast(BMC_PIN, LOW);
      //delayMicrosecondsCustom(off_delay);
      delayMicrosAndMillis(off_delay_millis, off_delay_micros);
      t++;
  }
  if (t==loop_revs) {
      Serial.println(micros());
      t++;
  }
}


void delayMicrosAndMillis(int millis_delay, int micros_delay){
  delay(millis_delay);
  delayMicroseconds(micros_delay);
}

void delayMicrosecondsCustom(long unsigned int tmp){
  while (tmp > 0){
    if (tmp > 10000) {
      delayMicroseconds(10000);
      tmp -= 10000;
    }
    else {
      delayMicroseconds(tmp);
      tmp = 0;
    }
  }
}



