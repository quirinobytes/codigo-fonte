  void handleMorse(int tempo){
    girar(0);
    int s=tempo*tempo; 
    traco(tempo);
    ponto(tempo);
    ponto(tempo);
    traco(tempo);

    delay(1000);

    ponto(tempo);
    ponto(tempo);
    traco(tempo); 
    traco(tempo); 
    traco(tempo);

    delay(1000);
 }

  void ponto(int tempo){
  int s=tempo*tempo;
  digitalWrite(16, 1);
  delay(s+20);
  digitalWrite(16, 0);
  delay(s);
  }

 void traco(int tempo){
  int s=tempo*tempo;
  digitalWrite(12, 1);
  digitalWrite(15, 1);
  digitalWrite(2, 1);
  digitalWrite(5, 1);
  digitalWrite(16, 1);
  delay(s+20);
  digitalWrite(12, 0);
  digitalWrite(15, 0);
  digitalWrite(2, 0);
  digitalWrite(5, 0);
  digitalWrite(16, 0);
  delay(s);

 }

