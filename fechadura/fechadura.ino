#include <Keypad.h>
#include <Servo.h>

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

//cria uma instância do objeto Servo
Servo myservo;

//Leds que acenderão se a senha 
//for válida ou inválida
int LEDSim = 12;
int LEDNao = 13;

const String senha = "20212020";
String readData = ""; 

int pos = 0;

void setup(){
	myservo.attach(11);
	Serial.begin(9600);
	
	pinMode(LEDSim, OUTPUT);
	pinMode(LEDNao, OUTPUT);
	
}

void loop(){
	char key = keypad.getKey();
	
	if (key != NO_KEY) {
		if (key != '#'){
			switch (key){
				case '*': 
					readData = "";
					break;
				default:
					readData += key;
					break;			
			}
		}
		Serial.println(key);
		Serial.println(readData);
	}
	
	if (key == '#')
	{
		if (readData == senha){
		
			digitalWrite(LEDSim, HIGH);
			
			for (pos = 0; pos <= 180; pos +=1){
				myservo.write(pos);
				delay(15);
			}
			LimpaSenha();
		}
		else{
		    digitalWrite(LEDNao, HIGH);
			delay(1000);
			LimpaSenha();
			Serial.println("Senha errada");
		}
	}
}

void LimpaSenha(){
	delay(1000);
	readData = "";
	digitalWrite(LEDSim, LOW);
	digitalWrite(LEDNao, LOW);
}
