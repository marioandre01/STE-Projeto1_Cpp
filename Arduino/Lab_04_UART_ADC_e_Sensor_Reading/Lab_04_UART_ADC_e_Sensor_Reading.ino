
const int analogInPin = A0;  // Entrada analogica do potenciometro
const int pinoPwm = 9;  // Saida analogica onde o LED esta conectado

int sensorValue = 0;        // leitura do potenciometro
int outputValue = 0;        // leitura da saida PWM (analogica)
int val = 0;
float voltagem;

void setup() {
  // inicializa a comunicacao serial:
  Serial.begin(9600);
}

void loop() {

  val = RMS(30);
   
  // faz a leitura da entrada analogica:
  sensorValue = analogRead(analogInPin); 
  voltagem = volt(sensorValue);
            
  // mapeia o resultado da entrada analogica dentro do intervalo de 0 a 255:
  outputValue = map(sensorValue, 0, 1023, 0, 255);  
  
  // muda o valor da saida analogica:
  analogWrite(pinoPwm, outputValue);          

  // imprime o resultado no monitor serial:
  Serial.print("Valor analogico = " );                      
  Serial.print(sensorValue);      
  Serial.print("\t Valor digital PWM = ");      
  Serial.print(outputValue);  
  Serial.print("\t RMS = ");      
  Serial.print(val); 
  Serial.print("\t Volts = ");      
  Serial.println(voltagem);  

  

  // Aguarda 2 milissegundos antes do proximo loop:
  delay(2);                    
}

float RMS(int repeat){
  int x = 0;
  long digital_value = 0;
  long accumulated = 0;
  long average = 0;
  
  do{
    digital_value = analogRead(analogInPin); 
    accumulated += digital_value*digital_value;
    x++;
  } while (x < repeat);

  average = accumulated/repeat;
    
  return sqrt(average);
}

float volt(float valor){
  float a1 = 5;
  float a2 = 1023;
  return (valor*(a1/a2)); 

}




