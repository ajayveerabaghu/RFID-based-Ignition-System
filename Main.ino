#include <Adafruit_Fingerprint.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd();
char input[12];
int count = 0;
int a = 0;
SoftwareSerial mySerial(2,3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
void setup()
{
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  Serial.begin(9600);
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("   RFID BASED   ");
  lcd.setCursor(0, 1);
  lcd.print("IGNITION SYSTEM    ");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Please swipe           ");
  lcd.setCursor(0, 1);
  lcd.print("Your License          ");
}
void loop()
{
  if (Serial.available())
  {
    count = 0;
    while (Serial.available() && count < 12)
    {
      input[count] = Serial.read();
      count++;
      delay(5);
    }
    if (count == 12)
    {
      if ((strncmp(input, "", 12) == 0) && (a == 0))
      {
        lcd.setCursor(0, 0);
        lcd.print("License Valid         ");
        lcd.setCursor(0, 1);
        lcd.print("Welcome               ");
        delay(1000);
        a = 1;
        fingerprint();
      }
      else if ((strncmp(input, "", 12) == 0) && (a == 0))
      {
        lcd.setCursor(0, 0);
        lcd.print("License Valid         ");
        lcd.setCursor(0, 1);
        lcd.print("Welcome                ");
        delay(1000);
        a = 1;
        fingerprint();
      }
      else
      {
        if (a != 1)
        {
          lcd.setCursor(0, 0);
          lcd.print("License Invalid         ");
          lcd.setCursor(0, 1);
          lcd.print("Try Again!!!            ");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Please swipe           ");
          lcd.setCursor(0, 1);
          lcd.print("Your License          ");
        }
      }
    }
  }
}
int getFingerprintID()
{
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;
  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  return finger.fingerID;
}
void fingerprint()
{
  finger.begin(57600);
        while(a==1)
        {
        int fingerprintID = getFingerprintID();
        delay(50);
        if (fingerprintID == 1)
        {
          lcd.setCursor(0, 0);
          lcd.print("Access Granted        ");
          lcd.setCursor(0, 1);
          lcd.print("Vehicle Started       ");
          digitalWrite(6,LOW);
          digitalWrite(7,HIGH);
          stp();
          while(1);
        }
        else if (fingerprintID == 2)
        {
          lcd.setCursor(0, 0);
          lcd.print("Access Granted        ");
          lcd.setCursor(0, 1);
          lcd.print("Vehicle Started       ");
          digitalWrite(6,LOW);
          digitalWrite(7,HIGH);
          while(1);
        }
        else
        {
          lcd.setCursor(0, 0);
          lcd.print("Pls Place a        ");
          lcd.setCursor(0, 1);
          lcd.print("Valid Finger       ");
        }
        }
}

void stp()
{
  finger.begin(57600);
        while(a==1)
        {
        int fingerprintID = getFingerprintID();
        delay(50);
        if (fingerprintID == 1)
        {
          lcd.setCursor(0, 0);
          lcd.print("Access Granted        ");
          lcd.setCursor(0, 1);
          lcd.print("Vehicle Stopped       ");
          digitalWrite(6,LOW);
          digitalWrite(7,LOW);
          while(1);
        }
        else if (fingerprintID == 2)
        {
          lcd.setCursor(0, 0);
          lcd.print("Access Granted        ");
          lcd.setCursor(0, 1);
          lcd.print("Vehicle Started       ");
          digitalWrite(6,LOW);
          digitalWrite(7,HIGH);
          while(1);
        }
        else
        {
          lcd.setCursor(0, 0);
          lcd.print("Pls Place a        ");
          lcd.setCursor(0, 1);
          lcd.print("Valid Finger       ");
        }
        }
}
