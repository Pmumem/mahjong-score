#include <M5StickC.h>

void displayScore(int hu);
int calScore(int hu, int han, bool isChild);

int cnt = -1;
bool isHomeButtonState = HIGH;
bool isRstButtonState = HIGH;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("\n\n\n          Mahjong\n");
  M5.Lcd.printf("           Score\n\n\n");
  M5.Lcd.print("      PRESS ANY BUTTON");

  pinMode(M5_BUTTON_HOME, INPUT);
  pinMode(M5_BUTTON_RST, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    if (isHomeButtonState == HIGH) {
      isHomeButtonState = LOW;

      cnt++;
      if (cnt > 9) {
       cnt = 0;
      }
      displayScore(20 + cnt * 10);
    }
  } else if (digitalRead(M5_BUTTON_RST) == LOW) {
    if (isRstButtonState == HIGH) {
      isRstButtonState = LOW;

      cnt--;
      if (cnt == -2) {
        cnt = 0;
      } else if (cnt < 0) {
        cnt = 9;
      }
      displayScore(20 + cnt * 10);
    }
  } else {
    isHomeButtonState = HIGH;
    isRstButtonState = HIGH;
  }
}

void displayScore(int hu) {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 2);
  M5.Lcd.printf("%6d     C          P\n", hu);
  int i;
  for (i = 1; i < 5; i++) {
    M5.Lcd.printf("%3d", i);
    if (hu == 20 && i == 1) {
      M5.Lcd.print("        -");
      M5.Lcd.println("          -");
      M5.Lcd.print("      ");
      M5.Lcd.print("  ( -, - )  ");
      M5.Lcd.println("  ( - )");
    } else {
      M5.Lcd.printf("%10d", calScore(hu, i, true));
      M5.Lcd.printf("%11d\n", calScore(hu, i, false));
      M5.Lcd.print("      ");
      M5.Lcd.printf("(%4d,%4d)  ", (int)(ceil(calScore(hu, i, true) / 400.0) * 100), (int)(ceil(calScore(hu, i, true) / 200.0) * 100)); 
      M5.Lcd.printf("(%4d)\n", (int)(ceil(calScore(hu, i, false) / 300.0) * 100));
    }
  }
}

int calScore(int hu, int han, bool isChild) {
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
