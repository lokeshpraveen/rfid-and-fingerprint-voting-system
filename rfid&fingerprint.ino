#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

int getFingerprintIDez();

// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
SoftwareSerial mySerial(2, 3);

LiquidCrystal_I2C lcd(0x3F,16,2); 
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

String read_rfid;                   // Add how many you need and don't forget to include the UID.

/*
 * Initialize.
 */

 int value=0;
 int fake = 0;
 int fake1 = 0;
 int fake2 = 0;
 int ver=0;
 int ver1=0;
 int ver2=0;
 int gen =0;
  int gen1 =0;
   int gen2 =0;
   int fakevote=0;
   int fakevote1=0;
   int fakevote2=0;
void setup()  
{
   lcd.init(); 
  Serial.begin(9600);
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("  WELCOME TO ");
  lcd.setCursor(0,1);
  lcd.print("    VOTING    ");
  delay(2000);
  lcd.clear();
    lcd.setCursor(1,0);
  lcd.print("PLACE YOUR CARD ");
   lcd.setCursor(0,1);
  lcd.print("     HERE");
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  digitalWrite(6,HIGH);
   while (!Serial);            // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    SPI.begin();                // Init SPI bus
    mfrc522.PCD_Init();         // Init MFRC522 card


  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
   

    while (1);
  }
  Serial.println("Waiting for valid finger...");
  
}
void dump_byte_array(byte *buffer, byte bufferSize) {
    read_rfid="";
    for (byte i = 0; i < bufferSize; i++) {
        read_rfid=read_rfid + String(buffer[i], HEX);
    }
}

void loop()                     // run over and over again
{
 
 
    if ( ! mfrc522.PICC_IsNewCardPresent())
        return;

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())
        return;

    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    lcd.clear();
    lcd.setCursor(1,0);
  lcd.print("PLACE YOUR CARD ");
   lcd.setCursor(0,1);
  lcd.print("     HERE");
  Serial.println("fingertest");
    Serial.println(read_rfid);
    if (read_rfid == "832b6a1a" && fake == 0) {
      Serial.println("first int");
    
         lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("SAILESH AGE-21");
      lcd.setCursor(0,1);
      lcd.print("ID.NO-YCV0164822");
        delay(1000);
       // fake=1;
      ver=1;
      fakevote++;
      Serial.println(ver);
      fingerprinttest();
   }
   else if(read_rfid == "9529e96" && fake1 == 0){
    Serial.println("second int");
    
         lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("RAGAV AGE-23");
      lcd.setCursor(0,1);
      lcd.print("ID.NO-NBV0164798");
        delay(1000);
     // fake1=1;
      fakevote1++;
      ver1 = 2;
      fingerprinttest();
   }
   else if(read_rfid == "19cdaab2" && fake2 == 0){
    Serial.println("third int");
    
         lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("PRINCE AGE-18");
      lcd.setCursor(0,1);
      lcd.print("ID.NO-GHT0167522");
        delay(1000);
    //  fake2=1;
      fakevote2++;
      ver2 = 3;
      fingerprinttest();
   }
  else if (read_rfid == "832b6a1a" && fake >= 1) {
      Serial.println("already int");
    
         lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("ALREADY VOTED");
      lcd.setCursor(0,1);
      lcd.print("SAILESH **822");
        delay(1000);
      setup();
      
   }
    else if (read_rfid == "9529e96" && fake1 >= 1) {
      Serial.println("already int");
    
         lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("ALREADY VOTED");
      lcd.setCursor(0,1);
      lcd.print("RAGAV **798");
        delay(1000);
      setup();
      
   }
    else if (read_rfid == "19cdaab2" && fake2 >= 1) {
      Serial.println("already int");
    
         lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("ALREADY VOTED");
      lcd.setCursor(0,1);
      lcd.print("PRINCE **522");
        delay(1000);
      setup();
      
   }
   else{
    lcd.clear();
    lcd.setCursor(1,0);
 lcd.print("NOT FOUND");
 delay(2000);
 lcd.clear();
 setup();
   }
}
void fingerprinttest(){
  delay(1000);
  getFingerprintIDez();
  delay(1000); 
}


uint8_t getFingerprintID() {
  
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  lcd.clear();
    lcd.setCursor(1,0);
      lcd.print("   PLACE YOUR ");
       lcd.setCursor(0,1);
      lcd.print("   FINGERPRINT ");
      delay(1000); 
  lcd.clear();
    lcd.setCursor(0,1);
      lcd.print("5");
      delay(1000);
  lcd.clear();
    lcd.setCursor(0,1);
      lcd.print("4");
      delay(1000);
      lcd.clear();
    lcd.setCursor(0,1);
      lcd.print("3");
      delay(1000);
      lcd.clear();
    lcd.setCursor(0,1);
      lcd.print("2");
      delay(1000);
      lcd.clear();
    lcd.setCursor(0,1);
      lcd.print("1");
      lcd.clear();
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
 
  if (finger.fingerID == 1 && ver == 1 && gen == 0){ 
      digitalWrite(6,LOW);
      digitalWrite(5,HIGH);
      Serial.println("HI");
      lcd.setCursor(1,0);
      lcd.print("   SAILESH ");
      lcd.setCursor(0,1);
      lcd.print("----VERIFIED----");
      delay(2000);
      digitalWrite(5,LOW);
      
      fake = 1;
      gen = 1;
voting();
       return finger.fingerID; 

  }
  
 else if (finger.fingerID == 2 && ver1==2 && gen1 == 0){ 
      digitalWrite(6,LOW);
      digitalWrite(5,HIGH);
      Serial.println("HI");
      lcd.setCursor(1,0);
      lcd.print("   RAGHAV ");
      lcd.setCursor(0,1);
      lcd.print("----VERIFIED----");
      delay(2000);
      digitalWrite(5,LOW);
      fake1++;
      gen1 = 1;
      
voting();
       return finger.fingerID;

  }
  else if (finger.fingerID == 3 && ver1==3 && gen2 ==0){ 
     digitalWrite(6,LOW);
      digitalWrite(5,HIGH);
      Serial.println("HI");
      lcd.setCursor(1,0);
      lcd.print("   RAGHAV ");
      lcd.setCursor(0,1);
      lcd.print("----VERIFIED----");
      delay(2000);
      digitalWrite(5,LOW);
      fake2++;
      gen2 = 1;
voting();
       return finger.fingerID;

  }
 /* else if (finger.fingerID == 1 && ver >= 2 && fakevote != 0){ 
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("INVALID FINGERPRINT");
      lcd.setCursor(0,1);
      lcd.print("WRONG PERSON");
      setup();

  }

else if (finger.fingerID == 2 && ver1 >= 2 && fakevote1 != 0){ 
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("INVALID FINGERPRINT");
      lcd.setCursor(0,1);
      lcd.print("WRONG PERSON");
      setup();

  }
  else if (finger.fingerID == 3 && ver2 >= 3 &&  fakevote2 != 0){ 
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("INVALID FINGERPRINT");
      lcd.setCursor(0,1);
      lcd.print("WRONG PERSON");
      setup();

  }*/
  else if(p == FINGERPRINT_NOTFOUND){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("NO DATA FOUND");
    delay(2000);
    setup();
  }


}
void voting(){
  delay(4000);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("VOTE SUCESSFULLY");
  delay(1000);
  
  setup();
}

 
