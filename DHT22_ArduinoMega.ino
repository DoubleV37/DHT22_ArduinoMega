#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <stdio.h>
#include <DHT.h>

#define TFT_CS    10
#define TFT_RST   8
#define TFT_DC    9
#define TFT_SCLK 13   
#define TFT_MOSI 11   


#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

#define COLOR1 ST7735_BLACK
#define COLOR2 ST7735_WHITE

int text_color_humidex;

float humidity, temperature;

String message;

void setup(void)
{
    //Serial.begin(9600);
    // Initialize device.
    dht.begin();
    //Serial.println("DHT Sensor Initalized");
    tft.initR(0); // initialize a ST7735S chip, black tab
    tft.fillScreen(COLOR2);
}

void testdrawtext(char* text, uint16_t color)
{
    tft.setCursor(0, 0);
    tft.setTextColor(color);
    tft.setTextWrap(true);
    tft.print(text);
}

void loop()
{
    // get data from DHT-11
    humidity = dht.readHumidity();

    temperature = dht.readTemperature();
    //Serial.print("humidity:   "); Serial.println(humidity);
    //Serial.print("temperature:   "); Serial.println(temperature);

    // Table
    //tft.drawRect(0, 0, 128, 160, COLOR1);
    //tft.drawLine(0, 50, 128, 50, COLOR1);
    //tft.drawLine(0, 100, 128, 100, COLOR1);

    // data is outputed
    temperature_to_lcd(temperature, 4);
    humidity_to_lcd(humidity, 55);
    tft.flush();
    delay(5000);
}


// outputs temperature to LCD

void temperature_to_lcd(float temperature, unsigned char text_position)
{
    int text_color;
    tft.setCursor(4, text_position);
    tft.setTextColor(COLOR1, COLOR2);
    tft.setTextSize(1);

    tft.print("Temperature:");
    tft.setTextSize(3);
    if (temperature > 0)
    {
        text_color = ST7735_BLUE;
    }
    else
    {
        text_color = ST7735_BLUE;
    }

    tft.setCursor(1, text_position + 20);
    fix_number_position(temperature);
    tft.setTextColor(text_color, COLOR2);
    tft.print(temperature, 1);
    tft.setCursor(108, text_position + 20);
    tft.print("C");
    tft.drawChar(90, text_position + 20, 247, text_color, COLOR2, 2); //degree symbol

}

//outputs humidity to LCD

void humidity_to_lcd(float humidity, unsigned char text_position)
{
    tft.setTextColor(COLOR1, COLOR2);
    tft.setCursor(4, text_position);
    tft.setTextSize(1);
    tft.println("Humidity:");
    tft.setTextSize(3);
    tft.setCursor(1, text_position + 20);
    fix_number_position(humidity);
    tft.print(humidity, 1);
    tft.print(" %");
}

// aligs number to constant position

void fix_number_position(float number)
{
    if ((number >= -40) && (number < -9.9))
    {
        ;
    }
    if ((number >= -9.9) && (number < 0.0))
    {
        tft.print(" ");
    }
    if ((number >= 0.0) && (number < 9.9))
    {
        tft.print(" ");
    }
    if ((number >= 9.9) && (number < 99.9))
    {
        tft.print(" ");
    }
    if ((number >= 99.9) && (number < 151))
    {
        tft.print("");
    }
}
