const int en_pin = 2;//
const int dir_pin = 6;//direction of the motor
const int step_pin = 4;//stepping signal out
const int ra_plus_pin = 5;
const int ra_minus_pin = 7;
const int microstep3 = 3;
const double step_interval = 24.0*3600.0*1000/(100.0*4.0*200.0*8.0);
const int step_interval_millis = 135;
double error_tot=0.0;
int ra_plus_status = 0;
int ra_minus_status = 0;

void setup(){
  //initialize pin mode and initial stage
  pinMode(en_pin,OUTPUT);
  pinMode(dir_pin,OUTPUT);
  pinMode(step_pin,OUTPUT);
  digitalWrite(en_pin, LOW);
  digitalWrite(dir_pin, LOW);
  digitalWrite(step_pin, LOW);
  digitalWrite(microstep3, HIGH);

  pinMode(ra_plus_pin,INPUT);
  pinMode(ra_minus_pin,INPUT);
}

void step(int stepnum){
  if (stepnum>0){
    
    int half_sub_step_interval = step_interval_millis / stepnum /2;
    int sub_step_residual = step_interval_millis-(half_sub_step_interval*stepnum*2);
    for (int i =0; i<stepnum; i++){
      digitalWrite(step_pin, HIGH);
      delay(half_sub_step_interval);
      digitalWrite(step_pin, LOW);
      delay(half_sub_step_interval);
    }
    delay(sub_step_residual);
  }
  else{
    delay(step_interval_millis);
  }
}

void loop(){
  int stepnum = 2;
  
  ra_plus_status = digitalRead(ra_plus_pin);
  ra_minus_status = digitalRead(ra_minus_pin);
  if (ra_plus_status == HIGH){
    stepnum = stepnum + 1;
  }
  if (ra_minus_status == HIGH){
    stepnum = stepnum - 1;
  }
  
  step(stepnum);
}