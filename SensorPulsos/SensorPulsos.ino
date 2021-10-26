//Definimos que vamos utilizar las interrupciones de Arduino y la libreria Pulsesensor
#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

//Le decimos que esta variable va a ser de tipo serial_plotter para graficar los pulsos
const int tipoSalida = SERIAL_PLOTTER;

//Pin el cual va a tener mi entrada de pulsos
const int Entrada_Pulsos = A0;
//El primer pin es para cuándo lee un pulso y el segundo es cuando baja
const int Pin_Parpadeante = 13;    
const int Pin_Desvanecido = 5;

//Instanciamos un objeto de tipo PulseSensorPlayground para poder utilizar sus métodos
//los cuáles nos ayudarán en el proyecto 
PulseSensorPlayground pulseSensor;

void setup() {
  //Inicializamos la comunicación serial en una taza de 115200 de bits por segundo para que
  //podamos transmitir la información
  Serial.begin(115200);

  //Configuramos nuestros pines de entrada de pulsos, y los dos leds para que parpadeen cuando
  //hay un pulso
  pulseSensor.analogInput(Entrada_Pulsos);
  pulseSensor.blinkOnPulse(Pin_Parpadeante);
  pulseSensor.fadeOnPulse(Pin_Desvanecido);

  //Establecemos las otras configuraciones, le vamos a decir que el formato en el que va a
  //salir la información, la tome de la variable, tipoSalida, que es de tipo SERIAL_PLOTER.
  pulseSensor.setSerial(Serial);
  pulseSensor.setOutputType(tipoSalida);


//Validación en caso de que Arduino no reconozca el código, para esto, vamos a mostrar un led
//que se prenda y se apague de manera rápida para indicar de manera visual que hay un
//error
  if (!pulseSensor.begin()) {
    for(;;) {
      // Flash the led to show things didn't work.
      digitalWrite(Pin_Parpadeante, LOW);
      delay(50);
      digitalWrite(Pin_Parpadeante, HIGH);
      delay(50);
    }
  }
}

void loop() {
  //Pequeña pausa entre cada loop
  delay(20);

  /*Con las configuraciones que ya hice anteriormente y con la ayuda de la libreria de PulseSensorPlayground
   * lo único que tengo que hacer es pasar al serial la información con el outputSample, luego voy a preguntarle
   * si hay detecta algún latido, si es así, voy ejectuar el méotod outputBeat para que me mande los datos
   * al plotter y podamos verlos de manera gráfica
  */
 pulseSensor.outputSample();
  if (pulseSensor.sawStartOfBeat()) {
   pulseSensor.outputBeat();
  }
}
