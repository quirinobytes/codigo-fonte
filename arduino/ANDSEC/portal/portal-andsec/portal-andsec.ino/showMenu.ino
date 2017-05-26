void ShowMenu(){
if (logged_in){
   server.sendContent(
      "<a href=.\> Home </a> | "
      "<a href=\wifi> Wifi Config </a> | "
      "<a href=\manual> Manual </a> | "
      "<a href=\challengerstatus> Challenger Status </a> | "
      "<a href=\tips> Tips </a> | "
      "<a href=\about> About </a> &nbsp;&nbsp;&nbsp;&nbsp; User: <b> admin </b>"
      );
  
}
else{
   server.sendContent(
      "<a href=.\> Home </a> | "
      "<a href=/wifi> Config Wifi </a> | "
      "<a href=/manual> Manual </a> | "
      "<a href=/challengerstatus> Challenger Status </a> | "
      "<a href=/tips> Tips </a> | "
      "<a href=/about> About </a> "
      );

}

}



void includeCss(){
  server.sendContent(
    "<style>"
    ".green { background-color: #3CB057; }"
    ".blue { background-color: #0483DE; }"
    ".brown { background-color: #7D4302; }"
    ".red { background-color: #E60514; }"
    ".orange {    background-color: #f26b31; } "
    ".yellow {    background-color: #F2EA7C; } "
    ".purple {    background-color: #9D2CA3; }  "
    ".grey {   background-color: #595759; } "
    ".white {     background-color: #FFF; } "
    ".gold {   background-color: #D4AF37; } "
    "select.decorated option:hover { "
    "box-shadow: 0 0 10px 100px #1882A8 inset;"
    "}"
    "</style>"
  );

  
}

