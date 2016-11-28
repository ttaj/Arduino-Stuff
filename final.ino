// Static variables
#define lcd_ticrate 20

// LCD stuff
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// This holds the music string in bytes
byte mus_incomingByte;

// The Bytes are then stored into this temp array
char mus_temp[128];

// char arrays to hold what to print on different y levels of the lcd
char lcd_bot[16]; //bottom
char lcd_top[16]; //top

// Update rate / fps
int lcd_updaterate;

// For debugging
int debug = false;

void setup() 
{ 
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.print("Welcome to test");
  lcd_updaterate = 1000 / lcd_ticrate; // Currently lcd_ticrate is set to 20, thus this will run 20 times a second.
  delay(1000);
}



void loop() 
{  
  // if there is bytes available coming from the serial port
  if (Serial.available()) 
  {
    // Read in music string
    Serial.readBytes(mus_temp, 96);

    // Update top and bottom arrays for lcd
    for(int i = 0; i < 16 ; i++)
    {
      if(mus_temp[i] == 0)
        lcd_bot[i] = 0xA0;
      else
        lcd_bot[i] = mus_temp[i] - 1;
    }
    
    // Bottom
    for(int i = 16; i < 32 ; i++)
    {
      if(mus_temp[i] == 0)
        lcd_bot[i - 16] = 0xA0;
      else
        lcd_bot[i - 16] = mus_temp[i] - 1;
    }

    // Display it on the lcd now.
    // First we clear.
    lcd.clear();

    //  We print the top
    lcd.setCursor(0, 0);
    lcd.print(lcd_top);

    // We print the bottom
    lcd.setCursor(0, 1);
    lcd.print(lcd_bot);

    // Send the newly transferred stuff.
    Serial.print(mus_temp + 32);
  }

  
  
  delay(lcd_updaterate); 
}
