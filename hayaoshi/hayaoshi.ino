#include <Arduino.h>

static const byte START_RY_PIN = 2;
static const byte RY_PIN[] = {3, 4, 5, 6, 7, 8};

static const byte START_SW_PIN = 10;
static const byte SW_PIN[] = {11, 12, 13, 14, 15, 16};

#define SW_NO   (sizeof(SW_PIN)/sizeof(SW_PIN[0]))
#define RY_ON   LOW
#define RY_OFF  HIGH

#define SW_ON   LOW
#define SW_OFF  HIGH:

static void all_ry_off()
{
  digitalWrite(START_RY_PIN, RY_OFF);
  for (int i=0; i < SW_NO; i++) {
    digitalWrite(RY_PIN[i], RY_OFF);
  }

  Serial.println("All RY are OFF");
}
void setup() {
  Serial.begin(9600);

  all_ry_off();

  pinMode(START_SW_PIN, INPUT);
  for (int i=0; i < SW_NO; i++) {
    pinMode(SW_PIN[i], INPUT);
  }

  pinMode(START_RY_PIN, OUTPUT);
  for (int i=0; i < SW_NO; i++) {
    pinMode(RY_PIN[i], INPUT);
  }
}

void loop() {
  Serial.println("1");
  while (true) {
    bool start_sw = digitalRead(START_SW_PIN);
    if (start_sw == SW_ON) {    //スタートSWが押されるのを待つ
      Serial.println("Start SW is ON");
      digitalWrite(START_RY_PIN, RY_ON);
      Serial.println("Start RY is ON");
      break;
    }
  };
  Serial.println("2");
  while (true) {
    byte hayaoshi = 0xff;
    for (int i=0; i < SW_NO; i++) {
      bool sw = digitalRead(SW_PIN[i]);
      Serial.print("SW ");
      Serial.print(i);
      if (sw == SW_ON) {
        Serial.println(" ON");
      } else {
        Serial.println(" OFF");
      }
      if (sw == SW_ON) {
        hayaoshi = i;
        Serial.print("Hayaoshi SW: ");
        Serial.print(hayaoshi + 1);
        Serial.println(" is ON");
        break;
      }
    }
    //SWが押されるのを待つ
    if (hayaoshi != 0xff) {
      //SWに対応するRYを1sオン
      digitalWrite(RY_PIN[hayaoshi], RY_ON);
      Serial.print("Hayaoshi RY: ");
      Serial.print(hayaoshi + 1);
      Serial.println(" is ON");
      delay(1000);
      break;
    }
  };

  all_ry_off(); //全リレーオフ

//  delay(5000);
}
