#include <LiquidCrystal.h>
#include <Servo.h>

//pin layout
const uint16_t  d4 = 6, d5 = 5, d6 = 4, d7 = 3;
const uint16_t btnUP = 7, btnDWN = 8;
const uint16_t cold_valve = 9, warm_valve=10;
const uint16_t rs = 12, en = 11;
const uint16_t flow_up_btn = A1;
const uint16_t flow_dn_btn = A2;



Servo cold_servo;
Servo warm_servo;
int num = 0;


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


bool btnUPclicked = false;
bool btnDWNclicked = false;

float wantedTemp = 40.0;
float currentTemp = 38;
float p = 1;//value to correct of error in p feedback
double waterflow = 0;// goes from 0-1





bool move_valve(Servo valve, uint16_t deg);
void checkButtons();
float measureTemp();//todo
void printWntTmp();
void printCrntTmp();
void p_feedback(int T,double waterflow);


void setup() {
	Serial.begin(9600);
	pinMode(btnUP, INPUT_PULLUP);
	pinMode(btnDWN, INPUT_PULLUP);

	lcd.begin(16, 2);


	printWntTmp();
	printCrntTmp();

	cold_servo.attach(cold_valve);
	warm_servo.attach(warm_valve);
}




void loop() {
	checkButtons();
	measureTemp();
	printCrntTmp();
	delay(10);
}



void p_feedback(int T)
{

}

void printWntTmp() {
	lcd.setCursor(0, 0);
	lcd.print(((float)((int)(wantedTemp * 10))) / 10);
	lcd.setCursor(4, 0);
	lcd.print((char)223);
}

void printCrntTmp() {
	lcd.setCursor(0, 1);
	lcd.print('(');
	lcd.print(((float)((int)(currentTemp * 10))) / 10);
	lcd.setCursor(5, 1);
	lcd.print((char)223);
	lcd.print(')');
}

void checkButtons() {
	if (digitalRead(btnUP) == LOW) {
		if (!btnUPclicked) { //clicked
			wantedTemp++;
			printWntTmp();
			Serial.print("+");
			Serial.println(wantedTemp);
			btnUPclicked = true;
		}
	}
	else btnUPclicked = false;


	if (digitalRead(btnDWN) == LOW) {
		if (!btnDWNclicked) { //clicked
			wantedTemp--;
			printWntTmp();
			Serial.print("-");
			Serial.println(wantedTemp);
			btnDWNclicked = true;
		}
	}
	else btnDWNclicked = false;
}

bool move_valve(Servo valve, uint16_t deg)//WARNING when using dont call all the time if in a loop
{
	if (deg < 0 || deg>180)
		return false;
	else
	{
		valve.write(deg);
	}
	return true;
}
