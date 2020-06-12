const int ledPin8 = 8; //led no pino 8
const int ledPin9 = 9; //led no pino 9
const int BotaoPin2 = 2; //botao no pino 2
const int BotaoPin3 = 3; //botao no pino 3

int EstadoBotaoPin2 = 0; //Variavel para ler o status do pushbutton
int EstadoBotaoPin3 = 0;

void setup() {
  // put your setup code here, to run once: (coloque seu código de configuração aqui para ser executado uma vez:)
  pinMode(ledPin8, OUTPUT); //Pino 8 do led será saída
  pinMode(ledPin9, OUTPUT); //Pino 9 do led será saída
  
  pinMode(BotaoPin2, INPUT); //Pino 2 com botão será entrada
  pinMode(BotaoPin3, INPUT); //Pino 3 com botão será entrada

}

void loop() {
  // put your main code here, to run repeatedly: (coloque seu código principal aqui, para rodar repetidamente:)
  
  EstadoBotaoPin2 = digitalRead(BotaoPin2); /*novo estado do botão vai ser igual ao que
  Arduino ler no pino onde está o botão.Poderá ser ALTO (HIGH) se o botão estiver
  Pressionado, ou BAIXO (LOW),se o botão estiver solto */
  EstadoBotaoPin3 = digitalRead(BotaoPin3);
  
  if (EstadoBotaoPin2 == HIGH){
    //Se botão estiver pressionado (HIGH)
    digitalWrite(ledPin8, HIGH); // acende o led do pino 8.
  }
  else{
    //se não estiver pressionado
    digitalWrite(ledPin8, LOW); //deixa o led do pino 8 apagado
  }

  if (EstadoBotaoPin3 == HIGH){
    //Se botão estiver pressionado (HIGH)
    digitalWrite(ledPin9, HIGH); // acende o led do pino 9.
  }
  else{
    //se não estiver pressionado
    digitalWrite(ledPin9, LOW); //deixa o led do pino 9 apagado
  }

  

}
