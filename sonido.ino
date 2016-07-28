#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
 #include <Servo.h>   // incluimos la biblioteca Servo 
#include <DFPlayer_Mini_Mp3.h> // Libreria DFPlayer Sonido


#define RxD 10 // Lectura pin 10 bluetooth
#define TxD 11 // Escritura pin 11 bluetooth

#define DataNeo 9// Pin control iluminacion neopixel
#define NUMPIXELS 60
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, DataNeo,NEO_GRB + NEO_KHZ800); // Hay tres parametros, aunque solo utilizaremos dos; Numero de neopixeles, variable PIN declarada previamente para datos, tipo de neopixel conectado este parametro es opcional NEO_GRB + NEO_KHZ800.
int delayval = 100; // delay for half a second

SoftwareSerial BTSerial(RxD, TxD); // Lectura de RX TX bluetooth definidos previamente en los pines 10 y 11 // Software Serial1 lo implementa el DFPlayer

Servo miservo; // creamos un objecto servo para controlar el motor 
 
 
void setup() // ciclo void inicializar
{
   pinMode(12,OUTPUT); // Pin datos motor salida
   
  BTSerial.begin(9600);
  Serial1.begin(9600);
 // Serial.begin(9600);
  
  mp3_set_serial (Serial1);  //set Serial for DFPlayer-mini mp3 module  // Serial de comunicacion DFPlayer 
  mp3_set_volume (25);          // 15 is low for unpowered speaker  ajustamos el volumen del sonido 

  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
                                      
  strip.begin(); // This initializes the NeoPixel library.
  strip.show(); // Inicializamos los pixeles apagados 'off' o podemos establecer un metodo de animacion 

   miservo.attach(7);  // liga el servo al pin 7
  
  // BTSerial.println("Enter AT commands:");
 //  BTSerial.print("AT");
 // delay(100);

}


  
void loop()
{
  
  while (BTSerial.available())//Declaramos un sentencia, Mientras el puerto Serial del bluetooth este disponible se empieza el ciclo 
  {
   char val= BTSerial.read(); //Declaramos una variable de tipo carácter y Seo lee la variale enviada desde el Bluetooth.

    switch(val)
    {
  
    case 'A': //Si en el caso de ser A cambiara a color azul la iluminacion.
      {
      
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
   for(int i=0;i<NUMPIXELS;i++){ // 

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, strip.Color(0,0,150)); // Moderately bright blue color.
    strip.show(); // This sends the updated pixel color to the hardware.

    //delay(delayval); // Delay for a period of time (in milliseconds).
    Serial.print("azul"); 
    }
    break;//El caso se detiene.
   }
    
    case 'R': //Si en el caso de ser R cambiara a color rojo la iluminacion.
      {
   // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
   for(int i=0;i<NUMPIXELS;i++){ // 

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, strip.Color(150,0,0)); // Moderately bright green color.
    strip.show(); // This sends the updated pixel color to the hardware.

    //delay(delayval); // Delay for a period of time (in milliseconds).
 Serial.print("red"); 
    }
  break;
      }
    case 'V': //Si en el caso de ser V cambiara a color random de la iluminacion.
      {
   for(int i=0;i<NUMPIXELS;i++){
 
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, rainbow());
 
    strip.show(); // This sends the updated pixel color to the hardware.
 
    delay(delayval); // Delay for a period of time (in milliseconds).

    Serial.print("variado"); 
 
  }
          break;
      }
    case 'M': //Si en el caso de ser M cambiara a color rosa la iluminacion.
  {   
    // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
   for(int i=0;i<NUMPIXELS;i++){ // 

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, strip.Color(229,9,127)); // Moderately bright pink color.
    strip.show(); // This sends the updated pixel color to the hardware.

    //delay(delayval); // Delay for a period of time (in milliseconds).
    Serial.print("pink"); 

    }
      break;
      }
    case 'S': //Si en el caso de ser S reproducira una pista de audio, sonido.
      {

// for(int i=0;i<5;i++){
 
    // reproducir random
    int a = random(0,5);  // a tomara un valor de 0 a 5 de pistas 
     mp3_play(a); // reproducir pista aleatoria 
     //delay (6000);
     
    // Serial.println(a);
     //mp3_play (4);

 // }
        mp3_stop ();
        Serial.println("Sonando Ando");  
           
        break;
      }
    case 'O': //Si en el caso de ser O la tapa se abrira, open. 
      {
        for(int angulo = 0; angulo < 90; angulo += 1) {   //  un ciclo para mover el servo entre los 0 y los 90 grados  
       miservo.write(angulo);               //  manda al servo la posicion
        delay(15);                        //  espera unos milisegundos para que el servo llegue a su posicion
     }
      Serial.println("Abierto");  
        break;
      }

   case 'C': //Si en el caso de ser O la tapa se cerrara, close. 
      {
        for(int angulo = 90; angulo >= 1; angulo -= 1)    {   //  un ciclo para mover el servo entre los 90 y los 0 grados                             
       miservo.write(angulo);                 //  manda al servo la posicion
        delay(15);                          //  espera unos milisegundos para que el servo llegue a su posicion
     }
      Serial.println("Cerrado");  
        break;
      }
    }       
  }
}

uint32_t rainbow(){
  return strip.Color(random(0,255), random(0,255), random(0,255)); // Metodo ace es seleccionar un numero aleatorio entre el 0 y el 255.
  } 

