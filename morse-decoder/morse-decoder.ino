#include "BinaryTree.h"

struct MorseEntry {
  const char* code;
  char letter;
};

MorseEntry table[] = {

    {".-", 'A'},   {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'},  {".", 'E'},
    {"..-.", 'F'}, {"--.", 'G'},  {"....", 'H'}, {"..", 'I'},   {".---", 'J'},
    {"-.-", 'K'},  {".-..", 'L'}, {"--", 'M'},   {"-.", 'N'},   {"---", 'O'},
    {".--.", 'P'}, {"--.-", 'Q'}, {".-.", 'R'},  {"...", 'S'},  {"-", 'T'},
    {"..-", 'U'},  {"...-", 'V'}, {".--", 'W'},  {"-..-", 'X'}, {"-.--", 'Y'},
    {"--..", 'Z'},

    {"-----", '0'}, {".----", '1'}, {"..---", '2'}, {"...--", '3'}, {"....-", '4'},
    {".....", '5'}, {"-....", '6'}, {"--...", '7'}, {"---..", '8'}, {"----.", '9'}
};

BinaryTree<char> morse;

const unsigned int button_pin = 2;
const unsigned int led_pin = 12;

const unsigned long DEBOUNCE = 30;
const unsigned long DOT_MAX = 300;
const unsigned long LETTER_PAUSE = 1500;
const unsigned long WORD_PAUSE = 4000;

unsigned long startPress = 0;
unsigned long endPress = 0;
unsigned long lastReleaseTime = 0;
unsigned long lastChange = 0;
bool isPress = false;

String codMorse = "";
String cuvantFinal = "";

void setup(){
  Serial.begin(9600);
  Serial.println("Apasa butonul pentru a introduce cod!");

  for(size_t i = 0; i < sizeof(table) / sizeof(table[0]); i++)
    morse.insert(table[i].code, table[i].letter);

  pinMode(button_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, HIGH);
}

void loop(){
  int statusButon = digitalRead(button_pin);

  if(millis() - lastChange < DEBOUNCE) return;

  if(statusButon == HIGH && !isPress) {
    startPress = millis();
    lastChange = millis();
    isPress = true;
    digitalWrite(led_pin, LOW);
  }
  else if(statusButon == LOW && isPress) {
      digitalWrite(led_pin, HIGH);
      endPress = millis() - startPress;
      lastReleaseTime = millis();
      lastChange = millis();
      isPress = false;
    
          if(endPress > DEBOUNCE)
            {
              if(endPress < DOT_MAX){ codMorse += '.'; Serial.print(".");
            }
         else { codMorse += '-'; Serial.print("-");
            }
     }
    }
  
  
  if(!isPress && codMorse.length() > 0 &&
   (millis() - lastReleaseTime > LETTER_PAUSE)){
    const char* r = morse.find(codMorse.c_str());
    Serial.print(" -> ");
    if(r){
      Serial.print("Litera: ");
      Serial.println(*r);
      cuvantFinal += *r;
    }
    else{
      Serial.println("Negasit");  
    }
    codMorse = "";
  }

  if(!isPress && codMorse.length() == 0 && cuvantFinal.length() > 0 && (millis() - lastReleaseTime > WORD_PAUSE)){
    Serial.print("Cuvantul final este: ");
    Serial.println(cuvantFinal);
    cuvantFinal = "";
  }
}