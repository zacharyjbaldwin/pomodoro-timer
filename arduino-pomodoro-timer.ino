#include <LiquidCrystal_I2C.h>

// Device settings:
const bool useBuzzer = true;
const int buzzerPin = 3;
const int buttonPin = 2;

// Time settings:
const int pomodoroStage = 1500; // 1500 seconds, or 25 minutes
const int shortBreak = 300;     // 300 seconds, or 5 minutes
const int longBreak = 1200;     // 1200 seconds, or 20 minutes

//
bool cycledOnce = false;
int buttonState = 0;
int lastButtonState = 0;

LiquidCrystal_I2C lcd(0x3F, 4, 20);

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("testing.!");

  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  chirp(3);

}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("press to start");
  
  if (!cycledOnce)
  {
    while (true)
    {
      buttonState = digitalRead(buttonPin);
      if (buttonState != lastButtonState)
      {
        if (buttonState == HIGH)
        {
          Serial.println("gotten button press");
          chirp(1);
          break;
        }
      }
      lastButtonState = buttonState;
    }
  }
  
  doPomodoroStage(4);
//  doShortBreak();
}

void chirp(int repeat) {
  if (useBuzzer) {
    for (int i = 0; i < repeat; i++) {      
      digitalWrite(buzzerPin, HIGH);
      delay(10);
      digitalWrite(buzzerPin, LOW);
      delay(65);
    }
  }
}

void doPomodoroStage(int iteration) {

  String message = (iteration == 4) ? "Up next: long break" : "Up next: short break";
  
  lcd.clear();

  lcd.setCursor(0, 2);
  lcd.print(message);
  
  for (int i = pomodoroStage; i > 0; i--)
  {
    int minute = i/60;
    int second = i%60;

    lcd.setCursor(0, 0);
    lcd.print("Pomodoro ends: ");
    
    lcd.print(minute);
    lcd.print(":");

    if (second < 10) {
      lcd.print("0");
      lcd.print(second);
    } else {
      lcd.print(second);
    }

    Serial.print("Current remaining time in pomodoro stage: ");
    Serial.print(minute);
    Serial.print(":");
    if (second < 10) {
      Serial.print("0");
      Serial.print(second);
    } else {
      Serial.print(second);
    }
    Serial.print(" (");
    Serial.print(i);
    Serial.println(")");
        
    delay(1000);
  }
}

void doShortBreak() {
  lcd.clear();
  for (int i = shortBreak; i > 0; i--)
  {
    int minute = i/60;
    int second = i%60;
    
    lcd.setCursor(0, 0);
    lcd.print("Short Break Ends: ");
    lcd.print(minute);
    lcd.print(":");

    if (second < 10) {
      lcd.print("0");
      lcd.print(second);
    } else {
      lcd.print(second);
    }

    Serial.print("Current remaining time in short break: ");
    Serial.print(minute);
    Serial.print(":");
    if (second < 10) {
      Serial.print("0");
      Serial.print(second);
    } else {
      Serial.print(second);
    }
    Serial.print(" (");
    Serial.print(i);
    Serial.println(")");
        
    delay(1000);
  }
}
