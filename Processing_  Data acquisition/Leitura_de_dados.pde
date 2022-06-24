import processing.serial.*;

Serial mySerial;  /*Funcionalidade serial */
PrintWriter output; /*Funcionalidade de escrita em arquivos */

void setup(){
  /*Configuração da porta serial e criação do arquivo */
 String portName = Serial.list()[0];
 mySerial = new Serial(this, portName, 9600);
 output = createWriter("dados.csv");
 
}

void draw(){
  if(mySerial.available() > 0){
    String value = mySerial.readStringUntil('\n');
    if(value != null){  /* Se o valor recebido não for vazio, captura hh:mm:ss e o valor do sensor*/
      output.print(hour());
      output.print(":");
      output.print(minute());
      output.print(":");
      output.print(second());
      output.print(" ");
      output.print(value);
      print(value);  /* Imprime o valor no console para visualizar a contabilização */
    }
   }
}

void keyPressed() { //Se alguma tecla for pressionada
  output.flush(); // Termina de escrever os dados pro arquivo
  output.close(); // Fecha o arquivo
  exit(); // Para o programa
}
