

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266WIFI_LIB_POINT
#include <ESP8266WiFi.h>

#include <RemoteXY.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);//crear un objeto lcd (DIRECCIÓN pantalla, Tamaño x, Tamño y)
int A;
int B;
int C;
int D;

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "RemoteXY"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377

static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t RX   = 3;
static const uint8_t TX   = 1;

// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,4,0,0,0,89,0,13,82,1,
  2,0,20,18,22,11,246,26,31,31,
  79,78,0,79,70,70,0,2,0,20,
  40,22,11,94,26,31,31,79,78,0,
  79,70,70,0,2,0,20,60,22,11,
  178,26,31,31,79,78,0,79,70,70,
  0,2,0,20,81,22,11,136,26,31,
  31,79,78,0,79,70,70,0,129,0,
  15,8,30,6,65,84,86,32,99,111,
  110,116,114,111,108,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  uint8_t switch_2; // =1 if switch ON and =0 if OFF 
  uint8_t switch_3; // =1 if switch ON and =0 if OFF 
  uint8_t switch_4; // =1 if switch ON and =0 if OFF 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_SWITCH_1 D5
#define PIN_SWITCH_2 D6
#define PIN_SWITCH_3 D7
#define PIN_SWITCH_4 D8


void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_SWITCH_1, OUTPUT);
  pinMode (PIN_SWITCH_2, OUTPUT);
  pinMode (PIN_SWITCH_3, OUTPUT);
  pinMode (PIN_SWITCH_4, OUTPUT);
  
  // TODO you setup code
  // Inicializamos el objeto lcd
  lcd.init();
  
  //Encendemos la luz de fondo.
  lcd.backlight();

  
  // Escribimos un Mensaje en la pantalla LCD.
  lcd.print("Hola Mundo");
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  digitalWrite(PIN_SWITCH_1, (RemoteXY.switch_1==0)?LOW:HIGH);
  digitalWrite(PIN_SWITCH_2, (RemoteXY.switch_2==0)?LOW:HIGH);
  digitalWrite(PIN_SWITCH_3, (RemoteXY.switch_3==0)?LOW:HIGH);
  digitalWrite(PIN_SWITCH_4, (RemoteXY.switch_4==0)?LOW:HIGH);
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 

A=digitalRead(PIN_SWITCH_1);
B=digitalRead(PIN_SWITCH_2);
C=digitalRead(PIN_SWITCH_3);
D=digitalRead(PIN_SWITCH_4);
// Canal 1
if (A == HIGH && B == LOW && C == LOW && D == LOW) {
 lcd.setCursor (0, 0);
lcd.print("TV 1 encendida ");
delay(100);
}
// Canal 2
if (B == HIGH && A == LOW && C == LOW && D == LOW) {
 lcd.setCursor (0, 0);
lcd.print("TV 2 encendida ");
}
// Canal 3
if (C == HIGH && B == LOW && A == LOW && D == LOW) {
 lcd.setCursor (0, 0);
lcd.print("TV 3 encendida ");
}
// Canal 4
if (D == HIGH && B == LOW && C == LOW && A == LOW) {
 lcd.setCursor (0, 0);
lcd.print("TV 4 encendida ");
}
// Canal 1 y 2
if (A == HIGH && B == HIGH && C == LOW && D == LOW ) {
   lcd.setCursor (0, 0);
lcd.print("  TV1 & TV2 ON  ");
}
// Canal 2 y 3
if (C == HIGH && B == HIGH && A == LOW && D == LOW ) {
   lcd.setCursor (0, 0);
lcd.print("  TV2 & TV3 ON  ");
}
// Canal 3 y 4
if (C == HIGH && D == HIGH && A == LOW && B == LOW ) {
   lcd.setCursor (0, 0);
lcd.print("  TV3 & TV4 ON  ");
}
// Canal 1 y 3
if (A == HIGH && C == HIGH && B == LOW && D == LOW ) {
   lcd.setCursor (0, 0);
lcd.print("  TV1 & TV3 ON  ");
}
// Canal 1 y 4
if (A == HIGH && D == HIGH && C == LOW && B == LOW ) {
   lcd.setCursor (0, 0);
lcd.print("  TV1 & TV4 ON  ");
}
// Canal 2 y 4
if (D == HIGH && B == HIGH && C == LOW && A == LOW ) {
   lcd.setCursor (0, 0);
lcd.print("  TV2 & TV4 ON  ");
}
// Canal 1 2 3
if (A == HIGH && B == HIGH && C == HIGH && D == LOW ) {
   lcd.setCursor (0, 0);
lcd.print("TV1 & TV2 & TV3 ON ");
}
// Canal 2 3 4
if (A == LOW && B == HIGH && C == HIGH && D == HIGH ) {
   lcd.setCursor (0, 0);
lcd.print("TV2 & TV3 & TV4 ON ");
}
// Canal 1 3 4
if (A == HIGH && B == LOW && C == HIGH && D == HIGH ) {
   lcd.setCursor (0, 0);
lcd.print("TV1 & TV3 & TV4 ON ");
}
// Canal 1 2 4
if (A == HIGH && B == HIGH && C == LOW && D == HIGH ) {
   lcd.setCursor (0, 0);
lcd.print("TV1 & TV2 & TV4 ON ");
}
//APAGADOS
if (A == LOW && B == LOW && C == LOW && D == LOW ) {
   lcd.setCursor (0, 0);
lcd.print("TV's apagadas");
}
//APAGADOS
if (A == HIGH && B == HIGH && C == HIGH && D == HIGH ) {
   lcd.setCursor (0, 0);
lcd.print("TV's ENCENDIDAS");
}
}
