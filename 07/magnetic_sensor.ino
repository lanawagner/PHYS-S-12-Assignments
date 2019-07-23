int N=100; //number to average

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  //analogReference(INTERNAL);
}

float sensorAve = 0;


void loop() {
  // read the input on analog pin 0:
 long int sum = 0;

  for (int i=1; i<N+1; i++){
  int sensorValue = analogRead(A2);
  sum = sum + sensorValue;
  }

  sensorAve = (float)sum/(float)N;    //necessary to cast 
                                      //integer variables as float, 
                                      //in order to get result to be
                                      //floating point number.
  
  //Serial.println(sum);
  Serial.println(sensorAve);
  
}
