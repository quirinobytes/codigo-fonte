void printFlag(){

    Serial.print(
    " find the password  \n"
    "                            (                       )    \n"
    "                            |\     _,--------._     / |   \n "
    "                            |\\.,'  aGFja3    `. /  |   \n "
    "                            `  '   RoZXBs     ,-'   '   \n "
    "                             \/_  YW5ldA _  (     /   \n "
    "                            (,-.`.    ,',-.`. `__,'   \n "
    "                             |/#\ ),-','#\`= ,'.` |   \n "
    "                             `._/)  -'.\_,'   ) ))|   \n  "
    "                             /  (_.)\     .   -'//   \n "
    "                             (  /\____/\    ) )`'\   \n "
    "                             \ |V----V||  ' ,    \   \n  "
    "                              |`- -- -'   ,'   \  \      _____  \n  "
    "                       ___    |         .'    \ \  `._,-'     `-  \n  "
    "                          `.__,`---^---'       \ ` -'   \n " 
    "                             -.______  \ . /  ______,-   \n "
    "                                     `.     ,'            \n  "
    "                                         !                  \n   "
    );
}


void printFlag2(){

   //char* str = (char*) random(9000000,99000000);
  //str[10]='/0';
  for (int i=0;i<30;i++){
    for (int c=0;c<80;c++){
      Serial.print(random(22,90));
    }
    Serial.println("200A");
  }
  
  Serial.print("8474F289835073L3898967745A6119333TmFvIGVzdGEgYXF1aSwgbmVtIGFiYWl4bw==");
  for (int i=0;i<30;i++){
    for (int c=0;c<80;c++){
      Serial.print(random(22,90));
    }
    Serial.println("200A");
  }
}

