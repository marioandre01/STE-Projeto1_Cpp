
int led = 9;
int estado_led = 0;
int interrupt_source = 1; 
int sensitivity = HIGH;
int debounce_limit = 200;
int ultimo_tempo_interup = 0;
 
void interrupt_handler(){
  if(debounce()){
    estado_led = !estado_led;  
  }
 
}

int debounce(){ 
  if((millis () - ultimo_tempo_interup) > debounce_limit){
    ultimo_tempo_interup = millis ();
    return 1;   
  }else{
    return 0;  
  }
}

void valor_led(int el){
  digitalWrite(led, el);  
}
 
void setup() {
  pinMode(led, OUTPUT); // Configura o pino do led (digital) como saída
  attachInterrupt(interrupt_source,interrupt_handler,sensitivity); //Configurando a interrupção
}

void loop() {
  valor_led(estado_led);
 
}

 
