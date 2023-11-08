// Codigo complementario para lectura de valores
/****************************************
* Librerias
****************************************/
#include "Ubidots.h"//Link de la librería externa https://github.com/ubidots/ubidots-esp32

/****************************************
* Constantes
****************************************/ 
const char* UBIDOTS_TOKEN = "BBFF-8fA1DnSVpwdiNCJ5GbEppJsl0EZkrE";  // Ubidots TOKEN
const char* WIFI_SSID = "Margomez";      // Wi-Fi SSID
const char* WIFI_PASS = "3108201204";      // Wi-Fi password 
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

String lectura_radiacion_solar(){
  float lectura;
  int promedio;
  String lectura_envio;
  
// Codigo si se tiene en cuenta un voltaje de referencia de 5V
  int lectura_min = 0;// Valor minimo del adc
  int lectura_max = 1024;// Depende del numero de bits del arduino
  float variable_min = 500;// Valor minimo del rango de lectura del sensor W/m2
  float variable_max = 2500;// Valor máximo del rango de lectura del sensor W/m2
  
  promedio = 0;
  for (int i=0; i<10; i++) {
    promedio = promedio + analogRead(0);//Numero del pin ADC
  }
  promedio = promedio/10;
  
  // Asegurando unos valores dentro del rango de la lectura.
  lectura = constrain(promedio, lectura_min, lectura_max);

  // Convertir la lectura en variable con interpolación lineal.
  float variable = map(lectura, lectura_min, lectura_max, variable_min, variable_max);
   
 //lectura = (promedio * 5.0)/1023.0;// 5.0 equivale al voltaje de referencia
  lectura_envio = String(variable);
  return lectura_envio;
}

String lectura_epar(){
  float lectura;
  int promedio;
  String lectura_envio;
  
// Codigo si se tiene en cuenta un voltaje de referencia de 5V
  int lectura_min = 0;// Valor minimo del adc
  int lectura_max = 1024;// Depende del numero de bits del arduino
  float variable_min = 0.000;// Valor minimo del rango de lectura del sensor 0 umol m-2 s-1
  float variable_max = 4000.000;// Valor máximo del rango de lectura del sensor
  
  promedio = 0;
  for (int i=0; i<10; i++) {
    promedio = promedio + analogRead(0);//Numero del pin ADC
  }
  promedio = promedio/10;
  
  // Asegurando unos valores dentro del rango de la lectura.
  lectura = constrain(promedio, lectura_min, lectura_max);

  // Convertir la lectura en variable con interpolación lineal.
  float variable = map(lectura, lectura_min, lectura_max, variable_min, variable_max);
   
 //lectura = (promedio * 5.0)/1023.0;// 5.0 equivale al voltaje de referencia
  lectura_envio = String(variable);
  return lectura_envio;
}


void setup() {
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  ubidots.setDebug(true);  // Uncomment this line for printing debug  messages   
}

void loop() {
  double value1 = random(0, 9) * 10;
  double value2 = random(0, 9) * 100;
  double value3 = random(0, 9) * 1000;
  ubidots.add("Variable_Name_One", value1);
  ubidots.add("Variable_Name_Two", value2);
  ubidots.add("Variable_Name_Three", value3);

  bool bufferSent = false;
  bufferSent = ubidots.send();

  if (bufferSent) {  
    Serial.println("Valores enviados a Ubidots");
    Serial.println("Valor obtenido del sensor");
  }

  delay(5000);
 
}
