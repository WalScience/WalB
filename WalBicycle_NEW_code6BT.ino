#include <EEPROM.h>
#include <U8glib.h>
#include <SoftwareSerial.h>
#include <DS3231.h>


SoftwareSerial HC06(11,10);

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

DS3231  rtc(SDA, SCL);
Time t;

String messageRecu;
 
int PinDHE = 2;
float Distance;
float Distance1;

int vitessems;
int vitesse;

int minutes;
int heures;
int seconde;
int anciensecondes;


int affichageBatterie;
int ValBatterie;

int adressekmh = 10;
int adressemph = 20;
int adressedebut = 30;



void setup() {
  rtc.begin();
  HC06.begin(9600);  
   
  pinMode(PinDHE, INPUT_PULLUP);
  attachInterrupt(0, calcul_distance, FALLING);
  
  u8g.firstPage();  
  do {

  u8g.setFont(u8g_font_fub17);
  u8g.setPrintPos(0,38); 
  u8g.print("WalScience");
  
   } while( u8g.nextPage() ); 
   delay(1000);
  
  
  if(EEPROM.read(adressedebut == 0)) {
  u8g.firstPage();  
  do {

  u8g.setFont(u8g_font_robot_de_niro);
  u8g.setPrintPos(0,38); 
  u8g.print("Connecter un peripherique bluetooth");
  
   } while( u8g.nextPage() ); 
  }
  


  


}
void loop() {
  heure();
  vitesse1();
  batterie();
  chrono();
  bluetooth();
  affichage();

  
}
 void affichage() {
if(EEPROM.read(adressekmh) == 1 and EEPROM.read(adressemph) == 0) {
u8g.firstPage();  
  do {
   u8g.setFont(u8g_font_7x13B);
  u8g.setPrintPos(0, 60); 
  u8g.print(Distance);
  u8g.setPrintPos(45, 60); 
  u8g.print("km");

  u8g.setPrintPos(110, 60); 
  u8g.print(seconde);

  u8g.setPrintPos(104, 60); 
  u8g.print(":");
  
  u8g.setPrintPos(90, 60); 
  u8g.print(minutes); 
  
  u8g.setPrintPos(84, 60); 
  u8g.print(":");
  
  u8g.setPrintPos(74, 60); 
  u8g.print(heures);
  u8g.setPrintPos(0, 0); 

  u8g.setFont(u8g_font_fub17);
  u8g.setPrintPos(20, 40); 
  u8g.print((int)vitesse); 
  
  
  

   
   
  u8g.setFont(u8g_font_helvB12);
  u8g.setPrintPos(70, 40); 
  u8g.print("km/h");
   
   
  u8g.setFont(u8g_font_7x13B);
  u8g.setPrintPos(48, 10); 
  u8g.print(t.hour, DEC);
  
  u8g.setFont(u8g_font_7x13B);
  u8g.setPrintPos(63, 9); 
  u8g.print(":");
   
  u8g.setFont(u8g_font_7x13B);
  u8g.setPrintPos(68, 10); 
  u8g.print(t.min, DEC);
  
  u8g.setFont(u8g_font_7x13B);
  u8g.setPrintPos(0, 10); 
  u8g.print((int)rtc.getTemp());

  u8g.setFont(u8g_font_7x13B);
  u8g.setPrintPos(13, 10); 
  u8g.print("'C");
  
  u8g.setFont(u8g_font_7x13B);
  u8g.setPrintPos(100, 10); 
  u8g.print(affichageBatterie);
  
  u8g.setFont(u8g_font_7x13B);
  u8g.setPrintPos(121, 10); 
  u8g.print("%");
  
  } while( u8g.nextPage() ); 
}

if(EEPROM.read(adressemph) == 1 and EEPROM.read(adressekmh) == 0) {
u8g.firstPage();  
  do {
   u8g.setFont(u8g_font_7x13B);
  u8g.setPrintPos(0, 60); 
  u8g.print(Distance);
  u8g.setPrintPos(45, 60); 
  u8g.print("mi");

  u8g.setPrintPos(110, 60); 
  u8g.print(seconde);

  u8g.setPrintPos(104, 60); 
  u8g.print(":");
  
  u8g.setPrintPos(90, 60); 
  u8g.print(minutes); 
  
  u8g.setPrintPos(84, 60); 
  u8g.print(":");
  
  u8g.setPrintPos(74, 60); 
  u8g.print(heures);
  u8g.setPrintPos(0, 0); 

  u8g.setFont(u8g_font_fub17);
  u8g.setPrintPos(20, 40); 
  u8g.print((int)vitesse); 
  
  
  

   
   
  u8g.setFont(u8g_font_helvB12);
  u8g.setPrintPos(70, 40); 
  u8g.print("mi/h");
   
   
  u8g.setFont(u8g_font_7x13B);
  u8g.setPrintPos(48, 10); 
  u8g.print(t.hour, DEC);
  
  u8g.setFont(u8g_font_7x13B);
  u8g.setPrintPos(63, 9); 
  u8g.print(":");
   
  u8g.setFont(u8g_font_7x13B);
  u8g.setPrintPos(68, 10); 
  u8g.print(t.min, DEC);
  
  u8g.setFont(u8g_font_7x13B);
  u8g.setPrintPos(0, 10); 
  u8g.print((int)rtc.getTemp());

  u8g.setFont(u8g_font_7x13B);
  u8g.setPrintPos(13, 10); 
  u8g.print("'C");
  
  u8g.setFont(u8g_font_7x13B);
  u8g.setPrintPos(100, 10); 
  u8g.print(affichageBatterie);
  
  u8g.setFont(u8g_font_7x13B);
  u8g.setPrintPos(121, 10); 
  u8g.print("%");
  
  } while( u8g.nextPage() ); 
}
   
 }
 void vitesse1() {
   

 int seconde = millis()/1000; 
  vitessems = Distance1 / seconde; 
  vitesse = vitessems * 3.6; 
   
   if(EEPROM.read(adressemph) == 1 and EEPROM.read(adressekmh) == 0) {
    vitesse = vitesse/1.61;
    
  }
  
  if(vitesse < 0) {
    vitesse = 0;
  }
  
 }
 void calcul_distance() {
  
   Distance1 = Distance1 + 0.09;
   
   Distance = Distance1/1000;
  
  if(EEPROM.read(adressemph) == 1 and EEPROM.read(adressekmh) == 0) {
    Distance = Distance/1.61;
    
  }
   
    }



 void chrono() {
 heures=millis()/3600000;

  minutes=millis()/60000;
  seconde=millis()/1000;
 
  
  seconde = (millis() / 1000) - anciensecondes;
  if(seconde>= 60) {seconde = 0; anciensecondes = millis() / 1000; minutes++;}
  if(minutes >= 60) {minutes = 0; heures++;}

}


 
 void batterie() {
  ValBatterie = analogRead(A3);
  affichageBatterie = map(ValBatterie, 970, 1023, 0, 100);
  if(affichageBatterie<0) {
    affichageBatterie = 0;
  }
   
 }
 
 void bluetooth() {
      while(HC06.available())
    {

      char c = HC06.read();
      messageRecu += c;
    }
    if (messageRecu.length() >0)
    {
      Serial.println(messageRecu);
      if (messageRecu == "Donnees?")     
        {
          HC06.write("Vitesse:");
          HC06.write((int)vitesse);
          HC06.write("Distance:");
          HC06.write(Distance);
        }
    }
    
      if (messageRecu == "Fin!")
      {
       vitesse = 0;
       Distance = 0; 
       
      }
      if (messageRecu == "kmh")
      {
      EEPROM.write(adressekmh, 1);
      EEPROM.write(adressemph,0);
      
      if(EEPROM.read(adressedebut == 0)) {
        EEPROM.write(adressedebut, 1);
      }
        
      }
      
       if (messageRecu == "mph")
      {
      EEPROM.write(adressemph, 1);
      EEPROM.write(adressekmh, 0);
      
       if(EEPROM.read(adressedebut == 0)) {
        EEPROM.write(adressedebut, 1);
      }
      
      }

      messageRecu="";
    
   
   
 }
 
 void heure() {
   
   t = rtc.getTime();
   
 }
 
 
