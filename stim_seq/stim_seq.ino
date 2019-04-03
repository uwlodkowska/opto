#define STIM_PIN  9
#define BMC_PIN  11

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
  
  

}

void loop() {
  //1
  singleStimulation(1, 20, 0.5, 5000);
  //2
  singleStimulation(1, 20, 0.5, 5000);
  //3
  singleStimulation(1, 20, 0.2, 5000);
  //4
  singleStimulation(1, 20, 0.2, 5000);
  //5 i 6
  delay(55000);
  //7
  jointStimulation(0.5, 40, 0.5, 10000);
  //8
  jointStimulation(0.5, 40, 0.2, 30000);
  //9
  singleStimulation(10, 5, 5, 10000);
  //10
  singleStimulation(10, 5, 5, 10000);
  //11
  //12
  //13
  //14
  //15
  //16
}

void singleStimulation(float freq, int duration, float duty_cycle, int delay_after){
  on_delay = long(10000/freq)*long(duty_cycle);
  off_delay = long(10000/freq)*long(100-duty_cycle);

  on_delay_millis = on_delay/1000;
  on_delay_micros = on_delay%1000;
  
  off_delay_millis = off_delay/1000;
  off_delay_micros = off_delay%1000;

  loop_revs = duration*freq;

  while (t<loop_revs){
      PORTB = B00001010;
      delayMicrosAndMillis(on_delay_millis, on_delay_micros);

      PORTB = B00000000;
      delayMicrosAndMillis(off_delay_millis, off_delay_micros);
      t++;
  }
  if (t==loop_revs) {
      t++;
  }
  delay(delay_after);
}

//dodac komunikacje po bmc
void jointStimulation(float freq, int duration, float duty_cycle, int delay_after){
  on_delay = long(10000/freq)*long(duty_cycle);
  off_delay = long(10000/freq)*long(100-duty_cycle);

  on_delay_millis = on_delay/1000;
  on_delay_micros = on_delay%1000;
  
  off_delay_millis = off_delay/1000;
  off_delay_micros = off_delay%1000;

  loop_revs = duration*freq;

  while (t<loop_revs){
      PORTB = B00001010;
      delayMicrosAndMillis(on_delay_millis, on_delay_micros);

      PORTB = B00000000;
      delayMicrosAndMillis(off_delay_millis, off_delay_micros);
      t++;
  }
  if (t==loop_revs) {
      t++;
  }
  delay(delay_after);
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



