/*

 * MFRC522 - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.

 * The library file MFRC522.h has a wealth of useful info. Please read it.

 * The functions are documented in MFRC522.cpp.

 *

 * Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )

 * Created by Miguel Balboa (circuitito.com), Jan, 2012.

 * Rewritten by Søren Thing Andersen (access.thing.dk), fall of 2013 (Translation to English, refactored, comments, anti collision, cascade levels.)

 * 

 * Released into the public domain.

 *

 * This sample shows how to setup a block on a MIFARE Classic PICC to be in "Value Block" mode.

 * In Value Block mode the operations Increment/Decrement/Restore and Transfer can be used.

 * 

 ----------------------------------------------------------------------------- empty_skull 



 - Aggiunti pin per arduino Mega

 - Scritto semplice codice per la scrittura e lettura 

 

 - add pin configuration for arduino mega

 - write simple read/write Code for new entry user

 

 http://mac86project.altervista.org/

 

 ----------------------------------------------------------------------------- Nicola Coppola

 * Pin layout should be as follows:

 * Signal     Pin              Pin               Pin

 *            Arduino Uno      Arduino Mega      MFRC522 board

 * ------------------------------------------------------------

 * Reset      9                5                 RST

 * SPI SS     10               53                SDA

 * SPI MOSI   11               51                MOSI

 * SPI MISO   12               50                MISO

 * SPI SCK    13               52                SCK

 *

 * The reader can be found on eBay for around 5 dollars. Search for "mf-rc522" on ebay.com. 

 */



#include <SPI.h>

#include <MFRC522.h>



#define SS_PIN 10

#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);        // Create MFRC522 instance.

String storedids[10];



// This program shown how to control arduino from PC Via Bluetooth

// Connect ...

// arduino>>bluetooth

// D11   >>>  Rx

// D10   >>>  Tx

// you will need arduino 1.0.1 or higher to run this sketch



#include <SoftwareSerial.h>// import the serial library



SoftwareSerial softserve(3, 2); // RX, TX

int ledpin=5; // led on D13 will show blink on / off

int BluetoothData; // the data given from Computer

int ispresent=0;
int nocard=0;
int nocard2=0;
void setup() {

        Serial.begin(9600);        // Initialize serial communications with the PC

        SPI.begin();                // Init SPI bus

        mfrc522.PCD_Init();        // Init MFRC522 card

        //Serial.println("Scan a MIFARE Classic PICC to demonstrate Value Blocks.");

        //bluetooth serial begin

        softserve.begin(9600);

        softserve.println("Bluetooth On please press 1 or 0 blink LED ..");

        pinMode(ledpin,OUTPUT);

}


void loop() {
        

        // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.

        MFRC522::MIFARE_Key key;
        
        //I think this boosts range

        for (byte i = 0; i < 6; i++) {

                key.keyByte[i] = 0xFF;

        }

        // Look for new cards

          
        if ( ! mfrc522.PICC_IsNewCardPresent()) {
          return;

        }



        // Select one of the cards

        if (mfrc522.PICC_ReadCardSerial()) {
        nocard = 1;
        nocard2 = 1;
        ispresent = 1;
        }
        else
        {
        return;
        }

        // Now a card is selected. The UID and SAK is in mfrc522.uid.

        // Dump UID

        Serial.print("Card UID:");

        for (byte i = 0; i < mfrc522.uid.size; i++) {
                
                Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");

                Serial.print(mfrc522.uid.uidByte[i], HEX);

        } 

        Serial.println();



        // Dump PICC type

        byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);

        Serial.print("PICC type: ");

        Serial.println(mfrc522.PICC_GetTypeName(piccType));

        if (        piccType != MFRC522::PICC_TYPE_MIFARE_MINI 

                &&        piccType != MFRC522::PICC_TYPE_MIFARE_1K

                &&        piccType != MFRC522::PICC_TYPE_MIFARE_4K) {

                //Serial.println("This sample only works with MIFARE Classic cards.");

                return;

        }

               

            //Check through an array of 10 known IDs to see if the UID is new or known

        for (int i = 0; i<10; i++){

          if (storedids[i] == 0){

            Serial.print("no value stored in slot " + String(i) + " yet \n");

            storedids[i] = String(mfrc522.uid.uidByte[0]);

            Serial.print("current card value stored in slot " + String(i) + "\n");

            i=10;            

            }        



          else{

            Serial.print("testing card against stored value in slot " + String(i) + " \n");

            if (String(mfrc522.uid.uidByte[0]) != storedids[i]){

              Serial.print("this is not card " + String(i) + " \n");

               digitalWrite(ledpin,0);

            }

            if (String(mfrc522.uid.uidByte[0]) == storedids[i]){

              Serial.print("CARD " + String(i) + " MUHFUCKIN RECOGNIZED \n"); 

                 digitalWrite(ledpin,1);

               softserve.println(String(i));

              i=10;

              }

          }

        }

        

        

        // risponde successo

        //Serial.println(mfrc522.GetStatusCodeName(status));

        

        // Dump the result

        //mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);

        

        // Halt PICC

        //mfrc522.PICC_HaltA();



        // Stop encryption on PCD

        //mfrc522.PCD_StopCrypto1();

        

        

}
