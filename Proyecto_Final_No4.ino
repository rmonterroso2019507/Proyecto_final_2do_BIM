/*
Fundación Kinal
Centro Educativo Técnico Labral Kinal 
Electrónica
Grado: Quinto
Sección: A
Curso: Taller de Electrónica Digital y Reparación de Computadoras I
Nombre: Grupo 6
*/
//Incluimos las librerias necesarias
#include <Keypad.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
#define NUMPIXELS 33 // definimos la cantidad da leds del NEOPIXEL
#define NEO 14 // definimos el pin del neopixel

enum NeoColor { // Definir los colores posibles
  RED = 0xFF0000,
  GREEN = 0x00FF00,
  BLUE = 0x0000FF,
  YELLOW = 0xFFFF00,
  MAGENTA = 0xFF00FF,
  CYAN = 0x00FFFF,
  AQUA = 0xFFF33
};

// Declaración de funciones de cada secuencia
void ascendente();
void descendente();
void auto_fantastico();
void alternancia();
void grupal();

// Declaración de funciones para el menu
void colorespixel();
void grupo_secuencias();

// Inicialización de objetos
Adafruit_NeoPixel pixels(NUMPIXELS, NEO, NEO_GRB + NEO_KHZ800);
LiquidCrystal_I2C lcd(0x27,16,2);

// Inicialización de objeto
const byte FILAS = 4;
const byte COLUMNAS = 4;
char keys[FILAS][COLUMNAS]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte pinesFilas[FILAS] = {9,8,7,6};
byte pinesColumnas[COLUMNAS] = {5,4,3,2};
Keypad keypad = Keypad(makeKeymap(keys),pinesFilas,pinesColumnas,FILAS,COLUMNAS);

// Variables globales
unsigned long color;
char key;
int x = 1; 

void setup() {
  Serial.begin(9600);
  lcd.init(); //inicio la comunicacion serial con el modulo i2c
  lcd.backlight(); //Enciendo la luz de fondo para poder ver el texto
  lcd.setCursor(0,0);
  lcd.print(">>BIENVENIDO A<<");
  lcd.setCursor(0,1);
  lcd.print(">>LA DISCOTECA<<");
  delay(3000);
  pixels.begin(); // Inicializa el Neopixel
  pixels.show();
}

void loop(){  

  randomSeed(analogRead(1)); //generamos una semilla aleatoria para los valores que usaremos para variar los colores
    
  if(x == 1){ //aqui realizamos el llamado de la función para poder escojer el color
    colorespixel();
  }
  if(x == 2){ //luego de escoger el color llamamos la función para elejir la secuencia
    grupo_secuencias();
  } 
}

//Funciones para realizar las acciones del proyecto

void colorespixel(){  //función donde seleccionamos el color dependiendo de la tecla seleccionada
  key = keypad.getKey(); // Comprueba la tecla presionada y establece el color correspondiente
  
  lcd.setCursor(0,0);
  lcd.print(">>>>ELIJA SU<<<<");
  lcd.setCursor(0,1);
  lcd.print(">>>>COLOR :b<<<<"); 
  
  switch (key) { 
    case '1':
      lcd.setCursor(0,0);
      lcd.print("----COLOR :D----");
      lcd.setCursor(0,1);
      lcd.print(">>>>>>ROJO<<<<<<");
      color =  RED;
      delay(2000);
      x = 2;
      break;
    case '2':
      lcd.setCursor(0,0);
      lcd.print("----COLOR :D----");
      lcd.setCursor(0,1);
      lcd.print(">>>>>VERDE<<<<<<");
      color = GREEN;
      delay(2000);
      x = 2;
      break;
    case '3':
      lcd.setCursor(0,0);
      lcd.print("----COLOR :D----");
      lcd.setCursor(0,1);
      lcd.print(">>>>>>AZUL<<<<<<");
      color = BLUE;
      delay(2000);
      x = 2;
      break;
    case '4':
      lcd.setCursor(0,0);
      lcd.print("----COLOR :D----");
      lcd.setCursor(0,1);
      lcd.print(">>>>AMARILLO<<<<");
      color = YELLOW;
      delay(2000);
      x = 2;
      break;
    case '5':
      lcd.setCursor(0,0);
      lcd.print("----COLOR :D----");
      lcd.setCursor(0,1);
      lcd.print(">>>>MAGENTA<<<<<");
      color = MAGENTA;
      delay(2000);
      x = 2;
      break;
    case '6':
      lcd.setCursor(0,0);
      lcd.print("----COLOR :D----");
      lcd.setCursor(0,1);
      lcd.print(">>>>>>CIAN<<<<<<");
      color = CYAN;
      delay(2000);
      x = 2;
      break;
    case '7':
      lcd.setCursor(0,0);
      lcd.print("----COLOR :D----");
      lcd.setCursor(0,1);
      lcd.print(">>>>>>AQUA<<<<<<");
      color = AQUA;
      delay(2000);
      x = 2;
      break;
    case '*':
      lcd.setCursor(0,0);
      lcd.print("-ESCOJE OTRA :D-");
      lcd.setCursor(0,1);
      lcd.print(">>SECUENCIA :)<<");
      color = color;
      delay(2000);
      x = 2;      
  }  
}

void grupo_secuencias(){ //función donde seleccionamos la secuencia dependiendo de la tecla seleccionada
  key = keypad.getKey();

  lcd.setCursor(0,0);
  lcd.print(">>>>ELIJA SU<<<<");
  lcd.setCursor(0,1);
  lcd.print(">>SECUENCIA :b<<");
  
  switch(key) {
      case 'A':
        for(int a = 0; a < 4; a++){
          ascendente();      
        }
        delay(100);
        x = 1;
        break;
      case 'B':
        for(int b = 0; b < 4; b++){
          descendente();
        }
        delay(100);
        x = 1;
        break;
      case 'C':
        for(int b = 0; b < 4; b++){
          auto_fantastico();
        }
        delay(100);
        x = 1;
        break;
      case 'D':
        for(int d = 0; d < 4; d++){
          alternancia();
        }
        delay(100);
        x = 1;
        break;
      case '#':
        for(int d = 0; d < 15; d++){
          grupal();
        }
        delay(100);
        x = 1;
        break;
  }
}

//Secuencias
void ascendente(){ 
  lcd.setCursor(0,0);
  lcd.print("--SECUENCIA :D--");
  lcd.setCursor(0,1);
  lcd.print(">>>ASCENDENTE<<<");
  
    for(int i = 0; i<33; i++){
      pixels.setPixelColor(i,color);
      pixels.show();  //muestro el color en el led
      delay(100);
    } 
    for(int i = 0; i<33; i++){
      pixels.setPixelColor(i,pixels.Color(0,0,0));
      pixels.show();  //muestro el color en el led
    }
    delay(200);
}

void descendente(){
  lcd.setCursor(0,0);
  lcd.print("--SECUENCIA :D--");
  lcd.setCursor(0,1);
  lcd.print(">>DESCENDENTE<<<");
  
    for(int i = 33; i>=0; i--){
      pixels.setPixelColor(i,color);
      pixels.show();  //muestro el color en el led
      delay(100);
    } 
    
    for(int i = 33; i>=0; i--){
      pixels.setPixelColor(i,pixels.Color(0,0,0));
      pixels.show();  //muestro el color en el led
    } 
    delay(200);      
}

void auto_fantastico(){
  lcd.setCursor(0,0);
  lcd.print("--SECUENCIA :D--");
  lcd.setCursor(0,1);
  lcd.print(">AUTOFANTASTICO<");
  
  for(int i = 0; i<33; i++){
    pixels.setPixelColor(i,color);
    pixels.show();
    delay(50);
    pixels.setPixelColor(i,pixels.Color(0,0,0));
    pixels.show();  //muestro el color en el led
    delay(50);
  }
  
  for(int i = 33; i>0; i--){
    pixels.setPixelColor(i,color);
    pixels.show();
    delay(50);
    pixels.setPixelColor(i,pixels.Color(0,0,0));
    pixels.show();  //muestro el color en el led
    delay(50);
  }
}

void alternancia(){
  lcd.setCursor(0,0);
  lcd.print("--SECUENCIA :D--");
  lcd.setCursor(0,1);
  lcd.print(">>ALTERNANCIAS<<");
  
  //leds pares
  for(int i = 0; i<33; i=i+2){
    pixels.setPixelColor(i,color);
    pixels.show();  //muestro el color en el led
  } 
  delay(150);
  for(int i = 0; i<33; i++){
    pixels.setPixelColor(i,pixels.Color(0,0,0));
    pixels.show();  //muestro el color en el led
  }
  delay(150);
  
  //leds inpares
  for(int i = 1; i<33; i=i+2){
    pixels.setPixelColor(i,color);
    pixels.show();  //muestro el color en el led
  } 
  delay(150);
  for(int i = 0; i<33; i++){
    pixels.setPixelColor(i,pixels.Color(0,0,0));
    pixels.show();  //muestro el color en el led
  }
  delay(150); 
}

void grupal(){
  lcd.setCursor(0,0);
  lcd.print("--SECUENCIA :D--");
  lcd.setCursor(0,1);
  lcd.print(">>>>>GRUPAL<<<<<");
//valores aleatorios para los colores
  unsigned long x = random(256);
  unsigned long y = random(256);
  unsigned long z = random(256);

  // Enciende todos los LEDs
  for(int i = 0; i < 33; i++) {
    pixels.setPixelColor(i, x,y,z); 
    pixels.show();
  }
  delay(100);

  // Apagar todos los LEDs
  for(int i = 0; i < 33; i++) {
    pixels.setPixelColor(i, 0); 
    pixels.show();
  }
  delay(100);
} 
