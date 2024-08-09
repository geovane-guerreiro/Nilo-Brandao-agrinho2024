/*
Código feito por: Geovane Guerreiro Nilo Brandão

Conexões 
Botão de abrir-------------- 2
Botão de fechar------------- 3
Botão do automático--------- 4
Sensor de chuva------------- 5
Motor-Abrindo--------------- 6
Motor-Fechando-------------- 7
Led verde------------------- 8
Trig sensor frente---------- 9
Echo sensor frente---------- 10
Trig sensor atrás----------- 11
Echo sensor atrás----------- 12
*/


//Variáveis de controle
int automatic = 0;
int auto_open = 0;
int auto_close = 0;
int open = 0;
int close = 0;

//Sensor ultrassonico-fechado.
  int uf = 0;//Variável que fará a leitura do ultrassônico.

  long Ultrassonic_front(int triggerPin, int echoPin){
    pinMode(triggerPin, OUTPUT);  //Define o pino trigger como saída.
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    //Define o pino trigger como ligado por 10 milesegundos.
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    pinMode(echoPin, INPUT);//Define o pino echo como entrada.

    //Lê o pino echo e retorna o tempo da onda de som em milesegundos
    return pulseIn(echoPin, HIGH);
  }
//


//Sensor ultrassonico-Aberto.
  int ub = 0;//Variável que fará a leitura do ultrassônico.

  long Ultrassonic_back(int triggerPin, int echoPin){
    pinMode(triggerPin, OUTPUT);  //Define o pino trigger como saída.
    digitalWrite(triggerPin, LOW); 
    delayMicroseconds(2);
    //Define o pino trigger como ligado por 10 milesegundos.
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    pinMode(echoPin, INPUT);//Define o pino echo como entrada.

    //Lê o pino echo e retorna o tempo da onda de som em milesegundos.
    return pulseIn(echoPin, HIGH);
  }
//



void setup() {
  //cria os pinos de entrada.
  for (int i = 1; i<=5; i++) {
    pinMode(i, INPUT);
  }

  //cria os pinos de saída.
  for (int i = 5; i<=8; i++) {
    pinMode(i, OUTPUT);
  }

  pinMode(13, OUTPUT);

  pinMode(5, INPUT);
    
  digitalWrite(6, LOW);//Desliga os relés de abrir.
  digitalWrite(7, LOW);//Desliga os relés de fechar.


}

void loop() {
  delay(500);
  //Se o botão de abrir for pressionado, chama a função "open".
  if (digitalRead(2) == LOW) {//Lê o status do botão abrir e define a variável automatic como 0.
    Open(25);//Função open.
    open = 1;
    automatic = 0;
  }

  delay(500); 

  //Se o botão de fechar for pressionado, chama a função "close" e define a variável automatic como 0.  
  if (digitalRead(3) == LOW) {//Lê o status do botão fechar.
    Close(25);//Função close.
    close = 1;
    automatic = 0;
  }

  delay(500); 

  //Se o botão do automático for pressionado, define a variável automatic como 1 e liga o led verde. 
  if(digitalRead(4) == LOW){//Lê o status do botão automático.
    automatic = 1;
    auto_open = 0;
    auto_close = 0;
  } 


  if (automatic == 1) {
    digitalWrite(8, HIGH);//Liga o led verde.

  } else{
    digitalWrite(8, LOW);//Desliga o led verde.

  }


 if(digitalRead(5) == LOW && automatic == 1 && auto_open == 0){ //Verifica se o sensor de chuva está molhado ou não.
    //Caso não esteja, chama a função de abrir, caso contrario, chama a função de fechar.
    open = 1;
    Open(25);
    auto_close = 0;
  }else if(digitalRead(5) == HIGH && automatic == 1 && auto_close == 0){
    close = 1;
    Close(25);
    auto_open = 0;
  }

}


void Open(int distance){//Definir o ultrassônico e a distancia.
  while (open == 1) {
    ub = 0.01723 * Ultrassonic_back(11, 12);//Leitura do ultrassônico aberto(trig, Echo).
    if(ub > distance){
      digitalWrite(6, HIGH);//Liga os relés para abrir o telhado.
    }else{
      digitalWrite(6, LOW);//Desliga os relés de abrir o telhado.
      auto_open = 1;
      open = 0; //Para o loop.
    }
  }
}


void Close(int distance){//Definir o ultrassônico e a distancia.
  while (close == 1) {
     uf = 0.01723 * Ultrassonic_front(9, 10);//Leitura do ultrassônico fechado(Trig, Echo).
     if(uf > distance){
      digitalWrite(7, HIGH);//Liga os relés para abrir o telhado.
    }else{
      digitalWrite(7, LOW);//Desliga os relés de abrir o telhado.
      auto_close = 1;
      close = 0; //Para o loop.
    }
  }
}

