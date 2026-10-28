int hours = 14;
int minutes = 17;

const unsigned long MINUTE_MS = 60000;//one minute in mls
//                          g, f, a, b, e, d, c
const int segmentPins[7] = {2, 3, 4, 5, 6, 7, 8};
const int digitPins[4] = {9, 10, 11, 12};

const byte patterns[11][7] = {
  {0,1,1,1,1,1,1},   // 0
  {0,0,0,1,0,0,1},   // 1
  {1,0,1,1,1,1,0},   // 2
  {1,0,1,1,0,1,1},   // 3
  {1,1,0,1,0,0,1},   // 4
  {1,1,1,0,0,1,1},   // 5
  {1,1,1,0,1,1,1},   // 6
  {0,0,1,1,0,0,1},   // 7
  {1,1,1,1,1,1,1},   // 8
  {1,1,1,1,0,1,1},   // 9
  {0,0,0,0,0,0,0}    // 10 = nothing lit (blank digit)
};

byte buffer[4] = {10, 10, 10, 10};

unsigned long lastMinute = 0;

void showTime(int hour, int minutes){
  buffer[0] = hour / 10;
  buffer[1] = hour % 10;
  buffer[2] = minutes / 10;
  buffer[3] = minutes % 10;
}

void refresh(){
  for(int j = 0; j < 4; j++){
    for(int k = 0; k < 4; k++){
      digitalWrite(digitPins[k], HIGH);
    }

    for(int i = 0; i < 7; i++){
      digitalWrite(segmentPins[i], patterns[buffer[j]][i]);
    }

    digitalWrite(digitPins[j], LOW);
    delay(3);
  }
}

void setup(){
  for(int i = 0; i < 7; i++){
    pinMode(segmentPins[i], OUTPUT);
  }
  for(int i = 0; i < 4; i++){
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], HIGH);
    Serial.begin(9600);
  }

  showTime(hours, minutes);
}

void loop(){
  if(millis() - lastMinute >= MINUTE_MS){
    lastMinute += MINUTE_MS;
    minutes++;
    if(minutes >= 60){
      minutes = 0;
      hours++;
      if(hours >= 24){
        hours = 0;
      }
    }

    showTime(hours, minutes);
    Serial.print(hours);
Serial.print(":");
Serial.println(minutes);
  }
  refresh();
}