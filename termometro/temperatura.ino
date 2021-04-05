#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED largura, em pixels
#define SCREEN_HEIGHT 64 // OLED altura, em pixels


#define OLED_RESET     -1 // Pino para resetar
//Criar um objeto display para manipular o OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 // não modifique este valor, do contrário poderá ocasionar falha
#define LOGO16_GLCD_WIDTH  16 // não modifique este valor, do contrário poderá ocasionar falha


int analogPin = A2;
int val = 0;
String temp = "Temperatura: ";

void setup()   {                
  Serial.begin(9600);

  // inicializa o OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  
}


void loop() {
  val = analogRead(analogPin)/10;
  Serial.write(val);
  temp.concat(val); temp.concat("C");
  display.clearDisplay();
  escreveTela("ADS Unesc", 3, 0, 2, false);
  escreveTela("Informa", 3, 22, 2, false);
  escreveTela(temp, 4, 45, 1, true);
  display.drawLine(1, 37, 120, 37, WHITE);
  display.drawRect(1, 20, 120,40, WHITE);  
  display.display();
  delay(3000);
  temp = "Temperatura: ";
}

/*
 * escreveTela(String text, int x, int y,int size, boolean d) 
 * rotina para facilitar a escrita
 * text é a string que será apresentada
 * x posição X do texto
 * y posição Y do texto
 * z tamanho do texto, 1, 2, 3 etc
 * d redesenha o texto "true" ou "false".
 */

void escreveTela(String text, int x, int y,int size, boolean d) {

  display.setTextSize(size);
  display.setTextColor(WHITE);
  display.setCursor(x,y);
  display.println(text);
  if(d){
    display.display();
  }  
  delay(100);
}
