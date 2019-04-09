#define STIM_PIN  9
#define BMC_PIN  11
#define COMM_PIN  6


long unsigned int on_delay;
long unsigned int off_delay;
long unsigned int t=0;

int bmc_state = 0;

int on_delay_millis;
int on_delay_micros;
  
int off_delay_millis;
int off_delay_micros;

int loop_revs;

void setup() {
  Serial.begin(9600);
  pinMode(STIM_PIN, OUTPUT);
  pinMode(BMC_PIN, OUTPUT);
  pinMode(COMM_PIN, INPUT_PULLUP);

  //1
  


}

void loop() {
  delay(1000);
  while(bmc_state == 0){
    bmc_state = digitalRead(COMM_PIN);
  }
  delay(7);
  singleStimulation(1, 20, 0.2, 3000);
  while(bmc_state == 0){
    bmc_state = digitalRead(COMM_PIN);
  }
  singleStimulation(1, 20, 0.2, 5000);
  
  //5 i 6
  //delay(55000);
  //7
  //jointStimulation(0.5, 40, 0.5, 10000);
  //8
  //jointStimulation(0.5, 40, 0.2, 30000);
  //9
  //singleStimulation(10, 5, 5, 10000);
  //10
  //singleStimulation(10, 5, 5, 10000);
  //11
  //singleStimulation(10, 5, 2, 10000);
  //12
  //singleStimulation(10, 5, 2, 10000);
  //13
  //singleStimulation(20, 5, 10, 10000);
  //14
  //singleStimulation(20, 5, 10, 10000);
  //15
  //singleStimulation(20, 5, 4, 10000);
  //16
  //singleStimulation(20, 5, 4, 0);
}


void singleStimulation(float freq, int duration, float duty_cycle, int delay_after){
  on_delay = long(10000/freq)*duty_cycle;
  off_delay = long(10000/freq)*(100-duty_cycle);
  on_delay_millis = on_delay/1000;
  on_delay_micros = on_delay%1000;
  
  off_delay_millis = off_delay/1000;
  off_delay_micros = off_delay%1000;

  loop_revs = duration*freq;
  t = 0;
  while (t<loop_revs){
      PORTB = B00001010;
      delayMicrosAndMillis(on_delay_millis,on_delay_micros);

      PORTB = B00000000;
      delayMicrosAndMillis(off_delay_millis, off_delay_micros);
      t++;
  }
  if (t==loop_revs) {
      t++;
  }
  delay(delay_after);
  return;
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
      PORTD = B01000000;
      delayMicrosAndMillis(on_delay_millis, on_delay_micros);

      PORTB = B00000000;
      PORTD = B00000000;
      delayMicrosAndMillis(off_delay_millis, off_delay_micros);
      t++;
  }

  Serial.println(off_delay_millis);
  if (t==loop_revs) {
      t++;
  }
  delay(delay_after);
}


void delayMicrosAndMillis(int millis_delay, int micros_delay){
  delay(millis_delay);
  delayMicroseconds(micros_delay);
}




