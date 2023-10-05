#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <prediction.h>

Eloquent::ML::Port::LinearRegression regr;
MCUFRIEND_kbv tft;

#define WHITE 0xFFFF
#define BLACK 0x0000
#define CLK 23
#define DT 22
#define SW 24

int counter = 0;
int currentA;
int lastA;
int i = 0;
float input[3];

void setup() {
  tft.begin(tft.readID());
	pinMode(CLK,INPUT);
	pinMode(DT,INPUT);
  pinMode(SW, INPUT_PULLUP);

	Serial.begin(9600);

	lastA = digitalRead(CLK);
  tft.fillScreen(BLACK);
}

void loop() {
        
	currentA = digitalRead(CLK);


	if (currentA != lastA  && currentA == 1){


		if (digitalRead(DT) != currentA) {
      if (counter > 0){
			  counter --;
        tft.fillRect(20, 20, 100, 100, BLACK);
        tft.setTextSize(3);
        tft.setCursor(20, 20);
        tft.setTextColor(WHITE);
        tft.println(counter);
      }
		} else {
			if (counter < 100){
        counter ++;
        tft.fillRect(20, 20, 100, 100, BLACK);
        tft.setTextSize(3);
        tft.setCursor(20, 20);
        tft.setTextColor(WHITE);
        tft.println(counter);
      }
		}
	}

	lastA = currentA;

  if (digitalRead(SW) == LOW){
    if (i < 3){
      input[i] = (float)counter;
      i++;
    }
    delay(500);
  }
  if (i == 3){
    tft.fillRect(20, 150, 200, 100, BLACK);
    float predict = regr.predict(input);
    tft.setCursor(20, 150);
    tft.setTextColor(WHITE);
    tft.setTextSize(5);
    tft.println(predict);
    i = 0;
  }

	delay(1);
}