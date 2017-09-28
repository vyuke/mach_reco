/*note：
上电后指示灯白灯亮起后保持蓝灯状态，
此时操作控制杆可以移动机械臂位置，
按下黑色按钮红灯亮起记录当前位置数据，
记录多组数据后点击触摸开关进行动作播放。
*/
#define R_PIN 4
#define G_PIN 5
#define B_PIN 6
#define bottom_PIN 7
#define touch_PIN 19

#include <Servo.h>

int A0v, A1v, A2v, A3v, resis;
int motion_count = 1;
Servo myservo0, myservo1, myservo2, myservo3, myservo4;
//动作数据数组，目前为4组
int motion_msater[4][5] =   
{
  {0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0,}
};

void servo_attach()
{
  myservo0.attach(8);
  myservo1.attach(9);
  myservo2.attach(10);
  myservo3.attach(11);
  myservo4.attach(12);
}

void servo_detach()
{
  myservo0.detach();
  myservo1.detach();
  myservo2.detach();
  myservo3.detach();
  //myservo4.detach();
}

void motion_record()
{ //servo_detach();
  Serial.println();
  for (int pin = 14; pin <= 18; pin++)
  {
    motion_msater[motion_count - 1][pin - 14] = analogRead(pin);
  }
  for (int printt = 0; printt < 5; printt++)
  {
    Serial.print(motion_msater[motion_count - 1][printt]);
    Serial.print(" ");
  }
  motion_count++;
  digitalWrite(R_PIN, 0);
  digitalWrite(G_PIN, 1);
  digitalWrite(B_PIN, 1);
  delay(500);
}

int map_compute(int index)
{ int index_val = map(index, 0, 1023, 0, 180);
  return index_val;
}

void motion_play()
{
  servo_attach();
  for (int motion = 0; motion <= 3; motion++)
  {
    myservo0.write(map_compute(motion_msater[motion][0]));
    myservo1.write(map_compute(motion_msater[motion][1]));
    myservo2.write(map_compute(motion_msater[motion][2]));
    myservo3.write(map_compute(motion_msater[motion][3]));
    myservo4.write(map_compute(motion_msater[motion][4]));
    delay(1000);
  }
  digitalWrite(G_PIN, 0);
  digitalWrite(R_PIN, 1);
  digitalWrite(B_PIN, 1);
  delay(5);
}

void setup() {
  pinMode(R_PIN, 1);
  pinMode(G_PIN, 1);
  pinMode(B_PIN, 1);
  pinMode(bottom_PIN, INPUT_PULLUP);
  pinMode(touch_PIN, 0);
  //attachInterrupt(bottom_PIN, motion_record, LOW);
  Serial.begin(9600);
  servo_attach();
  //servo_detach();
  digitalWrite(R_PIN, 0);
  digitalWrite(G_PIN, 0);
  digitalWrite(B_PIN, 0);
  delay(500);
  digitalWrite(R_PIN, 1);
  digitalWrite(G_PIN, 1);
  digitalWrite(B_PIN, 1);
  digitalWrite(B_PIN, 0);
  delay(5);
}

void loop() {
  int val_4 = analogRead(A4);
  val_4 = map(val_4, 0, 1023, 0, 180);
  myservo4.write(val_4);

  int val_3 = analogRead(A3);
  val_3 = map(val_3, 0, 1023, 0, 180);
  myservo3.write(val_3);

  int val_2 = analogRead(A2);
  val_2 = map(val_2, 0, 1023, 0, 180);
  myservo2.write(val_2);

  int val_1 = analogRead(A1);
  val_1 = map(val_1, 0, 1023, 0, 180);
  myservo1.write(val_1);

  int val_0 = analogRead(A0);
  val_0 = map(val_0, 0, 1023, 0, 180);
  myservo0.write(val_0);

  digitalWrite(R_PIN, 1);
  digitalWrite(G_PIN, 1);
  digitalWrite(B_PIN, 1);
  digitalWrite(B_PIN, 0);
  delay(5);

  if (digitalRead(bottom_PIN) == 0)
  {
    delay(30);
    if (digitalRead(bottom_PIN) == 0)
    { while (digitalRead(bottom_PIN) == 0);
      motion_record();
    }
  }

  if (digitalRead(touch_PIN) == 1)
  {
    delay(30);
    if (digitalRead(touch_PIN) == 1)
    { while (digitalRead(touch_PIN) == 1);
      motion_play();
    }
  }

}
