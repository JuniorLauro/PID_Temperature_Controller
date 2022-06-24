/*inclusão das bibliotecas necessárias*/
#include <OneWire.h>  
#include <DallasTemperature.h>

#define dados 7   /*o pino de dados do sensor está ligado na porta 7 do Arduino */
#define led   9   /*o pino de saída com o LED simulando a resistência */   

OneWire oneWire(dados);   /* Protocolo OneWire */
DallasTemperature sensors(&oneWire);    /*encaminha referências OneWire para o sensor */

/* Descrição: Controle PID de temperatura. Onde indicando o valor de setPoint, será realizado o controle constante da variável.
 * SetPoint: 30º C
 * 
 * Para este circuito em questão, o LED representando a nossa resistência vai variar conforme o valor do sensor diferir ao do setPoint (parte proporcional). 
 * Quanto maior a diferença, maior será a intensidade de seu brilho, indicando uma "maior ação de aquecimento".
 */

int controlePwm = 0;      /*Variável de controle*/
float setPoint = 25.0;    /*Definindo o setPoint*/
float temperatura = 0.0;  /*Variável que armazena o valor lido pelo sensor*/
float erro = 0.0;         /*Variavél do erro*/ 
float ultTemp = 0.0;      /*Variável que indica ultima temperatura lida*/

/*Variaveis de controle*/
float P = 0.0, 
      I = 0.0, 
      D = 0.0,
      PID = 0.0;

/*Variaveis de ajuste*/
float kP = 10.9, 
      kI = 348,
      kD = 37;

/*Variável de tempo de execução*/
long tempo = 0;

void setup(void)
{ 
 Serial.begin(9600);
// pinMode(led, OUTPUT);
 sensors.begin(); /*Inicia a leitura do(s) sensor(es)*/
 sensors.setResolution(10); /*Define a resolução para 10 bits*/
}
 
void loop(void)
{  
 sensors.requestTemperatures(); /* Envia o comando para leitura da temperatura */
 temperatura = sensors.getTempCByIndex(0); /* Endereço do sensor */
 Serial.print("SetPoint: 25, temperatura: ");
 Serial.println(sensors.getTempCByIndex(0));

 //verificar se precisa da proxima linha, pois eu já recebo o valor da temperatura.
 // int val = map(sensors.getTempCByIndex(0), -10, 85, 0, 255); /* Mapeamento do sensor para controle PWM */
 
 /*Implementação PID*/
 erro = setPoint - temperatura;
 float deltaTime = (millis() - tempo) / 1000.0;
 tempo = millis();
 
 // Proporcional
 P = erro * kP;

 // Integrador
 I += (erro * kI) * deltaTime; 
 
 // Derivativo
 D = (ultTemp - temperatura) * kD * deltaTime;

 // PID
 PID = P + I + D;

 // Conversão de dados p/ controle
 controlePwm = (PID);
 Serial.print("Saída controlador PWM: ");
 Serial.println(controlePwm);
 
 /*Saida do controlador*/
 //analogWrite(led, controlePwm);
}
