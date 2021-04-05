	#include <SPI.h>
	#include <Wire.h>
	#include <Adafruit_GFX.h>
	#include <Adafruit_SSD13h>
	#include <Keypad.h>
	
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
	  
	//Declaração das estruturas necessárias para 
	//manipular o teclado numérico
	const byte ROWS = 4;
	const byte COLS = 3;
	char keys[ROWS] [COLS] = {
	 {'1', '2', '3'},
	 {'4', '5', '6'},
	 {'7', '8', '9'},
	 {'*', '0', '#'}
	};
	byte rowPins[ROWS] = {2, 3, 4, 5};
	byte colPins[COLS] = {8, 7, 6};
	
	//cria uma instância do objeto Keypad
	Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
	
	
	String temp = "Senha No: ";
	String readData = ""; 
	
	void setup()   {     
	  Serial.begin(9600); //Inicializa a porta Serial
	  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // inicializa o OLED
	}
	
	
	void loop() {
	  
	 char key = keypad.getKey; //recebe a leitura da tecla pressionada no teclado numérico
	 
	 if (key != NO_KEY) { //testa se foi pressionado alguma tecla, do contrário o valor será NO_KEY
	  if (key != '#'){ //verifica se não foi pressionado o #, se ele for pressonado o número é enviado ao OLED
	   switch (key){
	    case '*':  //se pressionar * o número é limpado
	     readData = "";
	     break;
	    default:
	     readData += key; //concatena os números na String
	     break;   
	   }
	  }
	  Serial.println(key);
	  Serial.println(readData);
	 }
	
	 if (key == '#') //Se foi pressionado o #
	 {
	  temp.concat(readData); //contena a string readData na string temp, para ficar algo como Senha No: 213
	  readData = "";
	 }
	
	  
	 display.clearDisplay(); //limpa a tela
	 escreveTela("ADS Unesc", 3, 0, 2, false); //escreve informações na tela
	 escreveTela("Atendimento", 3, 22, 2, false);
	 escreveTela(temp, 4, 45, 1, true);
	 display.drawLine(1, 37, 120, 37, WHITE); //desenha 2 retângulos
	 display.drawRect(1, 20, 120,40, WHITE);  
	
	 display.display();
	 delay(3000);
	 temp = "Senha: "; //retorna o String ao valor sem a concatenação
	}
	
	*
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
