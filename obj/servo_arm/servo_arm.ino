#include <CurieEEPROM.h>
#include <Servo.h> 
 
Servo myservo0,myservo1,myservo2,myservo3,myservo4;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards

int addr = 0;
int pos = 0;    // variable to store the servo position 
int read_Servo0, read_Servo1, read_Servo2, read_Servo3, read_Servo4;
bool bottom = false;
bool bottom_pressed = false;
int min_0, max_0, min_1, max_1, min_2, max_2, min_3, max_3;
//int R_PIN, G_PIN, B_PIN;
#define R_PIN  4
#define G_PIN  5
#define B_PIN  6

bool eeprom_end()
{
	if (EEPROM.read(addr) == 6666) {
		delay(100);
		return false;
	}
	else
		return true;
}

bool match_servo()
{
	int read_Servo0_p, read_Servo1_p, read_Servo2_p, read_Servo3_p, read_Servo4_p;

	read_Servo0_p = analogRead(A0);
	if (read_Servo0_p > max_0)
		read_Servo0_p = max_0;
	if (read_Servo0_p < min_0)
		read_Servo0_p = min_0;
	read_Servo0_p = map(read_Servo0_p, min_0, max_0, 611, 2389);

	read_Servo1_p = analogRead(A1);
	if (read_Servo1_p > max_1)
		read_Servo1_p = max_1;
	if (read_Servo1_p < min_1)
		read_Servo1_p = min_1;
	read_Servo1_p = map(read_Servo1_p, min_1, max_1, 611, 2389);

	read_Servo2_p = analogRead(A2);
	if (read_Servo2_p > max_2)
		read_Servo2_p = max_2;
	if (read_Servo2_p < min_2)
		read_Servo2_p = min_2;
	read_Servo2_p = map(read_Servo2_p, min_2, max_2, 611, 2389);

	read_Servo3_p = analogRead(A3);
	if (read_Servo3_p > max_3)
		read_Servo3_p = max_3;
	if (read_Servo3_p < min_3)
		read_Servo3_p = min_3;
	read_Servo3_p = map(read_Servo3_p, min_3, max_3, 611, 2389);

	read_Servo4_p = analogRead(A4);
	if (read_Servo4_p > 1024)
		read_Servo4_p = 1024;
	if (read_Servo4_p < 0)
		read_Servo4_p = 0;
	read_Servo4_p = map(read_Servo4_p, 0, 1024, 1222, 1722);

	Serial.print("read_Servo_p:");
	Serial.print(read_Servo0_p);
	Serial.print(":");
	Serial.print(read_Servo1_p);
	Serial.print(":");
	Serial.print(read_Servo2_p);
	Serial.print(":");
	Serial.print(read_Servo3_p);
	Serial.print(":");
	Serial.print(read_Servo4_p);
	Serial.print("\n");


	if (abs(read_Servo0_p - read_Servo0) > 20) {
		//Serial.print(read_Servo0_p - read_Servo0);
		Serial.println("!0");
		return false;
	}
	else if (abs(read_Servo1_p - read_Servo1_p) > 20) {
		Serial.println("!1");
		return false;
	}
	else if (abs(read_Servo2_p - read_Servo2_p) > 20) {
		Serial.println("!2"); 
		return false;
	}
	else if (abs(read_Servo3_p - read_Servo3_p) > 20) {
		Serial.println("!3");
		return false;
	}
	else if (abs(read_Servo4_p - read_Servo4_p) > 20) {
		Serial.println("!4");
		return false;
	}
	else if (abs(EEPROM.read(addr - 5) - read_Servo0) > 20) {
		/*Serial.print(":");
		Serial.print(EEPROM.read(addr - 5) - read_Servo0);
		Serial.print("\n");*/
		Serial.println("!5");
		return false;
	}
	else if (abs(EEPROM.read(addr - 4) - read_Servo1) > 20) {
		Serial.println("!6");
		return false;
	}
	else if (abs(EEPROM.read(addr - 3) - read_Servo2) > 20) {
		Serial.println("!7");
		return false;
	}
	else if (abs(EEPROM.read(addr - 2) - read_Servo3) > 20) {
		Serial.println("!8");
		return false;
	}
	else if (abs(EEPROM.read(addr - 1) - read_Servo4) > 20) {
		Serial.println("!9");
		return false;
	}
	else
		return true;
}

void get_Servo()
{
	read_Servo0 = analogRead(A0);
	if (read_Servo0 > max_0)
		read_Servo0 = max_0;
	if (read_Servo0 < min_0)
		read_Servo0 = min_0;
	read_Servo0 = map(read_Servo0, min_0, max_0, 611, 2389);


	read_Servo1 = analogRead(A1);
	if (read_Servo1 > max_1)
		read_Servo1 = max_1;
	if (read_Servo1 < min_1)
		read_Servo1 = min_1;
	read_Servo1 = map(read_Servo1, min_1, max_1, 611, 2389);


	read_Servo2 = analogRead(A2);
	if (read_Servo2 > max_2)
		read_Servo2 = max_2;
	if (read_Servo2 < min_2)
		read_Servo2 = min_2;
	read_Servo2 = map(read_Servo2, min_2, max_2, 611, 2389);


	read_Servo3 = analogRead(A3);
	if (read_Servo3 > max_3)
		read_Servo3 = max_3;
	if (read_Servo3 < min_3)
		read_Servo3 = min_3;
	read_Servo3 = map(read_Servo3, min_3, max_3, 611, 2389);


	read_Servo4 = analogRead(A4);
	if (read_Servo4 > 1024)
		read_Servo4 = 1024;
	if (read_Servo4 < 0)
		read_Servo4 = 0;
	read_Servo4 = map(read_Servo4, 0, 1024, 1222, 1722);


	EEPROM.write(addr, read_Servo0);
	delay(100);
	addr++;
	EEPROM.write(addr, read_Servo1);
	delay(100);
	addr++;
	EEPROM.write(addr, read_Servo2);
	delay(100);
	addr++;
	EEPROM.write(addr, read_Servo3);
	delay(100);
	addr++;
	EEPROM.write(addr, read_Servo4);
	delay(100);
	addr++;

	Serial.print("read_Servo:");
	Serial.print(read_Servo0);
	Serial.print(":");
	Serial.print(read_Servo1);
	Serial.print(":");
	Serial.print(read_Servo2);
	Serial.print(":");
	Serial.print(read_Servo3);
	Serial.print(":");
	Serial.print(read_Servo4);
	Serial.print("\n");
}

void write_eeprom_end()
{
	EEPROM.write(addr, 6666);
	delay(100);
}

void read_eeprom()
{
	for (int i = 0; i < 512; i)
	{
		int value = EEPROM.read(i);
		delay(100);
		Serial.print(value);
		if ((i+1) % 5 == 0)
			Serial.print("\n");
		else
			Serial.print(":");
		if (value != 6666)
			i++;
		else
			i = 512;
	}
	Serial.print("\n");
}

void get_Servo4()
{
	pos = analogRead(A4);
	myservo4.writeMicroseconds(map(pos, 0, 1024, 1222, 1722));
}

void servo_detach() 
{
	myservo0.detach();
	myservo1.detach();
	myservo2.detach();
	myservo3.detach();
	//myservo4.detach();
}

void servo_attach()
{
	myservo0.attach(8);
	myservo1.attach(9);
	myservo2.attach(10);
	myservo3.attach(11);
	//myservo4.attach(12);
}

void bottom_press()
{

  Serial.println("interrupt>");
	long now_time = millis();
	
	//detachInterrupt(digitalPinToInterrupt(UPS_INT_PIN));
	detachInterrupt(7);

	delay(5);
	if (digitalRead(7) == LOW)
	{
		bottom = !bottom;
		Serial.println(bottom);
		unsigned long value;

		while (digitalRead(7) == LOW);

		if (millis() - now_time >= 1000)
		{
			bottom_pressed = !bottom_pressed;
			Serial.println("LONG PRESS!");
			digitalWrite(B_PIN, LOW);
			delay(500);
			digitalWrite(B_PIN, HIGH);
			delay(500);
			digitalWrite(B_PIN, LOW);
			delay(500);
			digitalWrite(B_PIN, HIGH);
			delay(500);
			if (bottom_pressed)
			{
				write_eeprom_end();
				read_eeprom();
				addr = 0;

				servo_attach();

				
			}
			/*else
			{
				digitalWrite(G_PIN, LOW);
				delay(500);
				digitalWrite(G_PIN, HIGH);
				delay(500);
				digitalWrite(G_PIN, LOW);
				delay(500);
				digitalWrite(G_PIN, HIGH);
				delay(500);
			}*/
			//read_eeprom();
			//addr = 0;
		}
		else
		{
			get_Servo();
			while (!match_servo())
			{
				addr -= 5;
				get_Servo();
			}
			Serial.println("EEPROM WRITE END");
			Serial.print(EEPROM.read(addr - 5));
			Serial.print(":");
			Serial.print(EEPROM.read(addr - 4));
			Serial.print(":");
			Serial.print(EEPROM.read(addr - 3));
			Serial.print(":");
			Serial.print(EEPROM.read(addr - 2));
			Serial.print(":");
			Serial.println(EEPROM.read(addr - 1));
			digitalWrite(R_PIN, LOW);
			delay(500);
			digitalWrite(R_PIN, HIGH);
			delay(500);
			digitalWrite(R_PIN, LOW);
			delay(500);
			digitalWrite(R_PIN, HIGH);
			delay(500);
		}
	}
	attachInterrupt(7, bottom_press, FALLING);
}

void get_analog()
{
	for (pos = 10; pos <= 170; pos += 10) // goes from 0 degrees to 180 degrees 
	{                                  // in steps of 1 degree 
		myservo0.write(pos);
		myservo1.write(pos);
		myservo2.write(pos);
		myservo3.write(pos);
		myservo4.write(map(pos, 10, 170, 65*11, 110*11));// tell servo to go to position in variable 'pos' 
		delay(500);                       // waits 15ms for the servo to reach the position 
		if (pos == 10 || pos == 170)
		{
			Serial.print(analogRead(A0));
			Serial.print(" : ");
			Serial.print(analogRead(A1));
			Serial.print(" : ");
			Serial.print(analogRead(A2));
			Serial.print(" : ");
			Serial.print(analogRead(A3));
			Serial.print("\n");
		}
	}
	for (pos = 170; pos >= 10; pos -= 10)     // goes from 180 degrees to 0 degrees 
	{
		myservo0.write(pos);
		myservo1.write(pos);
		myservo2.write(pos);
		myservo3.write(pos);
		//if(pos >= 65 && pos <= 110)
		myservo4.write(map(pos, 10, 170, 65*11, 110*11));// tell servo to go to position in variable 'pos' 
		delay(500);                       // waits 15ms for the servo to reach the position 
		if (pos == 10 || pos == 170)
		{
			Serial.print(analogRead(A0));
			Serial.print(" : ");
			Serial.print(analogRead(A1));
			Serial.print(" : ");
			Serial.print(analogRead(A2));
			Serial.print(" : ");
			Serial.print(analogRead(A3));
			Serial.print("\n");
		}
	}
}

void process_servo()
{
	int servo_pos_0, servo_pos_1, servo_pos_2, servo_pos_3, servo_pos_4;
	int servo_des_0, servo_des_1, servo_des_2, servo_des_3, servo_des_4;
	int servo_move_0, servo_move_1, servo_move_2, servo_move_3, servo_move_4;
	int rate_0, rate_1, rate_2, rate_3, rate_4, servo_move_max, rate_time;

	servo_pos_0 = read_Servo0;
	servo_pos_1 = read_Servo1;
	servo_pos_2 = read_Servo2;
	servo_pos_3 = read_Servo3;
	servo_pos_4 = read_Servo4;

	
	myservo0.writeMicroseconds(servo_pos_0);
	myservo1.writeMicroseconds(servo_pos_1);
	myservo2.writeMicroseconds(servo_pos_2);
	myservo3.writeMicroseconds(servo_pos_3);
	myservo4.writeMicroseconds(servo_pos_4);

	servo_des_0 = EEPROM.read(addr);
	//delay(100);
	addr++;
	servo_des_1 = EEPROM.read(addr);
	//delay(100);
	addr++;
	servo_des_2 = EEPROM.read(addr);
	//delay(100);
	addr++;
	servo_des_3 = EEPROM.read(addr);
	//delay(100);
	addr++;
	servo_des_4 = EEPROM.read(addr);
	//delay(100);
	addr++;

	servo_move_0 = servo_des_0 - servo_pos_0;
	servo_move_1 = servo_des_1 - servo_pos_1;
	servo_move_2 = servo_des_2 - servo_pos_2;
	servo_move_3 = servo_des_3 - servo_pos_3;
	servo_move_4 = servo_des_4 - servo_pos_4;

	servo_move_max = max(abs(servo_move_0), max(abs(servo_move_1), max(abs(servo_move_2), max(abs(servo_move_3), abs(servo_move_4)))));

	rate_0 = servo_move_0 * 50 / servo_move_max;
	rate_1 = servo_move_1 * 50 / servo_move_max;
	rate_2 = servo_move_2 * 50 / servo_move_max;
	rate_3 = servo_move_3 * 50 / servo_move_max;
	rate_4 = servo_move_4 * 50 / servo_move_max;

	/*Serial.print("Servo_rate:");
	Serial.print(rate_0);
	Serial.print(" : ");
	Serial.print(rate_1);
	Serial.print(" : ");
	Serial.print(rate_2);
	Serial.print(" : ");
	Serial.print(rate_3);
	Serial.print(" : ");
	Serial.print(rate_4);
	Serial.print("\n");*/

	rate_time = servo_move_max;
	//rate_num = 5;
	//int rate_num = 0;
	while (rate_time)
	{
		if (rate_time < 50)
		{
			servo_pos_0 = servo_des_0;
			servo_pos_1 = servo_des_1;
			servo_pos_2 = servo_des_2;
			servo_pos_3 = servo_des_3;
			servo_pos_4 = servo_des_4;
			rate_time = 0;
		}
		else
		{
			servo_pos_0 += rate_0;
			servo_pos_1 += rate_1;
			servo_pos_2 += rate_2;
			servo_pos_3 += rate_3;
			servo_pos_4 += rate_4;
			rate_time -= 50;
		}
		//rate_num++;
		/*Serial.print("rate_time:");
		Serial.print(rate_time);
		Serial.print("Servo_test:");
		Serial.print(servo_pos_0);
		Serial.print(" : ");
		Serial.print(servo_pos_1);
		Serial.print(" : ");
		Serial.print(servo_pos_2);
		Serial.print(" : ");
		Serial.print(servo_pos_3);
		Serial.print(" : ");
		Serial.print(servo_pos_4);
		Serial.print(" : ");
		Serial.print(rate_num);
		Serial.print("\n");*/

		myservo0.write(servo_pos_0);
		myservo1.write(servo_pos_1);
		myservo2.write(servo_pos_2);
		myservo3.write(servo_pos_3);
		myservo4.write(servo_pos_4);

		delay(40);
	}

	/*Serial.print(servo_pos_0);
	Serial.print(" : ");
	Serial.print(servo_pos_1);
	Serial.print(" : ");
	Serial.print(servo_pos_2);
	Serial.print(" : ");
	Serial.print(servo_pos_3);
	Serial.print(" : ");
	Serial.print(servo_pos_4);
	Serial.print("\n");*/

	read_Servo0 = servo_des_0;
	read_Servo1 = servo_des_1;
	read_Servo2 = servo_des_2;
	read_Servo3 = servo_des_3;
	read_Servo4 = servo_des_4;
}

void config_init()
{
	min_0 = 177;
	min_1 = 178;
	min_2 = 194;
	min_3 = 172;
	max_0 = 660;
	max_1 = 668;
	max_2 = 704;
	max_3 = 650;
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
	pinMode(A2, INPUT);
	pinMode(A3, INPUT);
	pinMode(A4, INPUT);
	pinMode(7, INPUT_PULLUP);
	pinMode(R_PIN, OUTPUT);
	pinMode(G_PIN, OUTPUT);
	pinMode(B_PIN, OUTPUT);
	digitalWrite(R_PIN, HIGH);
	digitalWrite(G_PIN, HIGH);
	digitalWrite(B_PIN, HIGH);
	attachInterrupt(7, bottom_press, FALLING);
	myservo0.attach(8);
	myservo1.attach(9);
	myservo2.attach(10);
	myservo3.attach(11);
	myservo4.attach(12);
}

void setup() 
{ 
	config_init();
	Serial.begin(9600);
  Serial.println("Start>");
} 
 
void loop() 
{ 
	if (bottom_pressed)
	{
		if (eeprom_end())
			process_servo();
		else
			addr = 0;
	}
	else
	{
		servo_detach();

		get_Servo4();
		delay(50);
	}
}




  //for(pos = 10; pos <= 170; pos += 1) // goes from 0 degrees to 180 degrees 
  //{                                  // in steps of 1 degree 
  //  myservo0.write(90);
  //  myservo1.write(90);
  //  myservo2.write(90);
  //  myservo3.write(90);
  //  //if(pos >= 65 && pos <= 110)
  //  myservo4.write(map(pos,10,170,65,110));// tell servo to go to position in variable 'pos' 
  //  delay(20);                       // waits 15ms for the servo to reach the position 
  //} 
  //for(pos = 170; pos>=10; pos -= 1)     // goes from 180 degrees to 0 degrees 
  //{                                
  //  myservo0.write(90);
  //  myservo1.write(90);
  //  myservo2.write(90);
  //  myservo3.write(90);
  //  //if(pos >= 65 && pos <= 110)
  //  myservo4.write(map(pos,10,170,65,110));// tell servo to go to position in variable 'pos' 
  //  delay(20);                       // waits 15ms for the servo to reach the position 
  //}
