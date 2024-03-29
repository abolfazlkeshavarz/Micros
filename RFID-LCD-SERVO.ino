/*
  Door Opener-Closer With :
    <<< Servo motor, RFID module(MFRC522), chracteric LCD 16*2 >>>
    By Abolfazl Keshavarz
    
*/
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;
int pot;

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

//Servo myservo;
//int pot;


void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Scan Your Card...");
  Serial.println();

  
  // Print a message to the LCD.
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Hello EveryOne");

myservo.attach(8);
myservo.write(0);
}
void loop() 
{
 // lcd.setCursor(0,1);
 // lcd.print(millis()/1000);
   // Turn off the display:
  //lcd.noDisplay();
  //delay(500);
  // Turn on the display:
////  lcd.display();
////  delay(500);
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
////  lcd.setCursor(0,0);
  Serial.print("Tag ID :");
////  lcd.print(" Tag ID:");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
////     lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
////     lcd.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println();
  Serial.print("Message : ");
 //// lcd.print("Message : ");
  content.toUpperCase();
 // if (content.substring(1) == "BD 31 15 2B") //change here the UID of the card/cards that you want to give access
  if (content.substring(2) == "F7 97 0E 53", "04 30 5A 3A 51 48 80")
  {

    //myservo.write(0);
////    lcd.setCursor(0,1);
    Serial.println("Authorized access");
    Serial.println();
////    lcd.print("Auth access     ");
 ////   lcd.println();
////    delay(1500);
 ////   lcd.setCursor(1,0);
 ////   lcd.print("Tap to Scan      ");
 ////   lcd.setCursor(0,1);
 ////   lcd.print("                 ");
    myservo.write(270);
    delay(9000);
    myservo.write(0);
  }


   else   {
 ////     lcd.setCursor(0,1);
      Serial.println(" Access denied");
 ////     lcd.print(" Access denied  ");
        delay(3000);
      myservo.write(0);
/////      lcd.setCursor(1,0);
////      lcd.print("Tap to Scan      ");
////      lcd.setCursor(0,1);
 ////     lcd.print("                 ");
  }
} 
