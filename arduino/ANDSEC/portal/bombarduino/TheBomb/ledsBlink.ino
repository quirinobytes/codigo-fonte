
void setupGPIO()
{
  
 //Preparando os GPIO
  //PINO-1UP
  pinMode(3, OUTPUT);
  //PINO2UP
  pinMode(13, OUTPUT);
  //PINO4UP
  pinMode(14, OUTPUT);
  //PINO-8UP
  pinMode(4, OUTPUT);
  //PINO-16UP
  pinMode(0, OUTPUT);
  
  //PINO2DOWN
  pinMode(15, OUTPUT);
  //PINO4DONW
  pinMode(12, OUTPUT); 
  //PINO8DONW
  pinMode(2, OUTPUT);
  //PINO16DONW
  pinMode(5, OUTPUT);
  //PINO32DOWN
  pinMode(16, OUTPUT);


  //APARENTEMENTE NENHUM
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(17, OUTPUT);

  /*<-----NAO APAGAR-----
  //PINO-1DONN (DA PAU ESSA ZICA -> LIGOU PARA A FUNCAO LOOP)
  //pinMode(1, OUTPUT);
  //software board restart -> Se ligar fica dando => Wdt Reset
  //pinMode(6, OUTPUT);]
  //pinMode(7, OUTPUT);
  // pinMode(9, OUTPUT);
  // pinMode(8, OUTPUT); tirar duvida depois
  //pinMode(11, OUTPUT);
  -------------------->*/
  
}
 
void piscar(){
  digitalWrite(15, 1);
  digitalWrite(12, 1);
  digitalWrite(2, 1);
  digitalWrite(5, 1);
  digitalWrite(16, 1);
  digitalWrite(0, 1);
  digitalWrite(4, 1);
  digitalWrite(14, 1);
  digitalWrite(13, 1);
  digitalWrite(3, 1);
  delay(100);
  digitalWrite(15, 0);
  digitalWrite(12, 0);
  digitalWrite(2, 0);
  digitalWrite(5, 0);
  digitalWrite(16, 0);
  digitalWrite(13, 0);
  digitalWrite(3, 0);
  digitalWrite(14, 0);
  digitalWrite(0, 0);
  digitalWrite(4, 0);
  delay(30);
  }
//padrao temp 10
void girar(int tempo){  
  int s=tempo*tempo;
  digitalWrite(15, 1);
  delay(s+20);
  digitalWrite(15, 0);
  delay(s);

  digitalWrite(12, 1);
  delay(s+20);
  digitalWrite(12, 0);
  delay(s);

  digitalWrite(2, 1);
  delay(s+20);
  digitalWrite(2, 0);
  delay(s);

  digitalWrite(5, 1);
  delay(s+20);
  digitalWrite(5, 0);
  delay(s);

  digitalWrite(16, 1);
  delay(s+20);
  digitalWrite(16, 0);
  delay(s);

  digitalWrite(0, 1);
  delay(s+20);
  digitalWrite(0, 0);
  delay(s);

  digitalWrite(4, 1);
  delay(s+20);
  digitalWrite(4, 0);
  delay(s);

  digitalWrite(14, 1);
  delay(s+20);
  digitalWrite(14, 0);
  delay(s);
  
  digitalWrite(13, 1);
  delay(s+20);
  digitalWrite(13, 0);
  delay(s);
  
  digitalWrite(3, 1);
  delay(s+20);
  digitalWrite(3, 0);
  delay(s);
}
