#include <M5StickC.h>

void displayScore(int hu);
int calScoreLon(int hu, int han, bool isChild);

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(1);

  pinMode(M5_BUTTON_HOME, INPUT);
  pinMode(M5_BUTTON_RST, INPUT);
}

int cnt = 0;
bool oldState = HIGH;
bool currentState = HIGH;

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    currentState = LOW;
    if (oldState == HIGH) {
      displayScore(20 + cnt * 10);
      cnt++;
      if (cnt > 10) {
       cnt = 0;
      }
      oldState = LOW;
    }
  } else {
    oldState = HIGH;
  }
  if (digitalRead(M5_BUTTON_RST) == LOW) {
    M5.Lcd.println("Hello");
  }
}

void displayScore(int hu) {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(40, 0, 2);
  M5.Lcd.printf("%d\n", hu);
  int i;
  for (i = 1; i < 5; i++) {
    M5.Lcd.printf("%4d%9d%9d\n", i, calScoreLon(hu, i, true), calScoreLon(hu, i, false));
  }

  return ;
}

int calScoreLon(int hu, int han, bool isChild) {
  int score = hu * pow(2, han + 2);
  if (isChild == true) {
    score = 4 * score;
  } else {
    score = 6 * score;
  }

  score = (int)ceil(score / 100.0) * 100;

  if (isChild == true && score >= 8000) {
    score = 8000;
  } else if (isChild == false && score >= 12000) {
    score = 12000;
  }

  return score;
}

//int calScore_Tsumo(int lonScore) {
//  score = lonScore / 100;
//  if (score % 2 == 0) {
//    
//  } else {
//    
//  }
//
//  return score;
//}
