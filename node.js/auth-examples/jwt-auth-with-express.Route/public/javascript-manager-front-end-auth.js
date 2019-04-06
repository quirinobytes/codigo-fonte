var token = ''
var jwtJSON = {}
var username = ''
// document.getElementById('jwtJSON').innerHTML = localStorage.getItem('jwtJSON')

function checkToken () {
  // document.getElementById('jwtJSON').innerHTML = jwtJSON
  console.log('ls=' + localStorage.getItem('jwtJSON'))
  var jwtData = localStorage.getItem('jwtJSON')
  jwtJSON = JSON.parse(jwtData)
  console.log('jwtJSON=>')
  console.log(jwtJSON)
  if (jwtJSON != null) {
    if (jwtJSON.sucess === true) {
      console.log('estava logado pelo localstorage=' + jwtJSON.sucess)
      token = jwtJSON.token
      let jwtUser = token.split('.')[1]
      let decodedJwtJsonUser = window.atob(jwtUser)
      let decodedJwtUser = JSON.parse(decodedJwtJsonUser)
      console.log('Username=' + decodedJwtUser.username)
      let isAdmin = decodedJwtUser.admin
      this.username = decodedJwtUser.username
      // document.querySelectorAll('#logged_user').innerHTML = '<a href="" onclick="logout();"> Logout </a>'
    } else {
      console.log('jwtJSON = null')
      token = ''
    }
  }
}

function logout () {
  if (this.jwtJSON) {
    destroyToken()
    delete this.jwtJSON
    document.getElementById('logged_user').innerHTML = '<a href="" onclick="login();" > Login </a>'
    //toastr.info('Are you the 6 fingered man?')
  } else {
    console.log('nao havia token para destruir.')
  }
}
function login () {
  var xhttp = new XMLHttpRequest()
  var data = { username: document.getElementById("username").value, password: document.getElementById("password").value }
  xhttp.onreadystatechange = function () {
    if (xhttp.readyState === 4) {
      var response = xhttp.responseText
      
      console.log('response=' + response)

      var json = response;
      var obj = JSON.parse(json)

      // Caso logado com sucesso, cria o localStorage com o jwtJSON
      if (obj.success) {
        this.token = obj.token
        localStorage.setItem('jwtJSON', response)
        token = obj.token
        let jwtUser = token.split('.')[1]
        let decodedJwtJsonUser = window.atob(jwtUser)
        let decodedJwtUser = JSON.parse(decodedJwtJsonUser)
        
        getURL_inContainer('/index')

        // document.getElementById('logged_user').innerHTML = '<a href="" onclick="account(\'' + decodedJwtJsonUser.username + "');\" > " + decodedJwtJsonUser.username +' </a>' + '<a href="" onclick="logout();" > Logout </a>'
      } else {
        toastr.warning('Usuario ou senha invalidos')
      }
      console.log('Token = ' + obj.token)
    }
  }
  xhttp.open("POST", "./login", true)
  xhttp.setRequestHeader("Content-type", 'application/json; charset=UTF-8')
  xhttp.send(JSON.stringify(data))
}

function getURL_inContainer(url) {
  var xhttp = new XMLHttpRequest()
  var jwtData = localStorage.getItem('jwtJSON')
  var jwtObj = JSON.parse(jwtData)
  toastr.success('Url ["' + url + ']: carregada com sucesso!')
  xhttp.open('GET', url, true)
  xhttp.setRequestHeader( 'Authorization', 'Bearer ' + jwtObj.token)
  xhttp.send()
 //window.open(url)
  xhttp.onload = function (nome) {  
    document.getElementById('container').innerHTML = this.responseText
  }
}

function getCHAT_inContainer(url) {
  var xhttp = new XMLHttpRequest()
  var jwtData = localStorage.getItem('jwtJSON')
  var jwtObj = JSON.parse(jwtData)
  toastr.success('Url ["' + url + ']: carregada com sucesso!')
  xhttp.open('GET', url, true)
  xhttp.setRequestHeader( 'Authorization', 'Bearer ' + jwtObj.token)
  xhttp.send()
 //window.open(url)
  xhttp.onload = function (nome) {  
    document.getElementById('container').innerHTML = this.responseText

    // a jogada  aqui
    //
    // abre um chat e ja passa um username para ele chamar a socket.emit({username=username})
    // esse chat esta no arquivo 
    chat(document.getElementById('username').value)
    

    document.getElementById("message").addEventListener("keyup", event => {
      if(event.key !== "Enter") return; // Use `.key` instead.
          document.getElementById("send_message").click(); // Things you want to do.
          event.preventDefault(); // No need to `return false;`.
      })
    

  }
}

function deleteFile(filename) {
  var xrequest = new XMLHttpRequest()
  var jwtData = localStorage.getItem('jwtJSON')
  var jwtObj = JSON.parse(jwtData)
  xrequest.open('GET', '/deletefile/' + filename, true)
  xrequest.setRequestHeader( 'Authorization', 'Bearer ' + jwtObj.token)
  xrequest.send()
  xrequest.onload = function () {  
    var json = xrequest.responseText;
    var obj = JSON.parse(json)
    token = obj.token
    let jwtUser = token.split('.')[1]
    let decodedJwtJsonUser = window.atob(jwtUser)
    let decodedJwtUser = JSON.parse(decodedJwtJsonUser)
    if (obj.success) {
      //toastr: arquivo excluido com sucesso
      toastr.warning(obj.message)
      getURL_inContainer('/upload')
    } else {
      toastr.error(obj.message)
      getURL_inContainer('/upload')
    }
  } 
}
// ####################### UPLOAD ############
function uploadFile(){
  //cabecalho neh kkk pra pegar o token no ocalstorage
  var xrequest = new XMLHttpRequest()
  var jwtData = localStorage.getItem('jwtJSON')
  var jwtObj = JSON.parse(jwtData)

  //var url = "/ReadMoveWebServices/WSUploadFile.asmx/UploadFile";
  var url = "/fileupload";
  var archivoSeleccionado = document.getElementById("myfile");
  var file = archivoSeleccionado.files[0];
  var fd = new FormData();
  fd.append("filetoupload", file);
  var xmlHTTP = new XMLHttpRequest();
  //xmlHTTP.upload.addEventListener("loadstart", loadStartFunction, false);
  xmlHTTP.upload.addEventListener("progress", progressFunction, false);
  xmlHTTP.addEventListener("load", transferCompleteFunction, false);
  xmlHTTP.addEventListener("error", uploadFailed, false);
  xmlHTTP.addEventListener("abort", uploadCanceled, false);


  xmlHTTP.open("POST", url, true);
  xmlHTTP.setRequestHeader( 'Authorization', 'Bearer ' + jwtObj.token)

  //xmlHTTP.setRequestHeader('book_id','10');
  xmlHTTP.send(fd);
  xmlHTTP.onload = function () {  
    var json = xmlHTTP.responseText;
    var obj = JSON.parse(json)
    token = obj.token
    let jwtUser = token.split('.')[1]
    let decodedJwtJsonUser = window.atob(jwtUser)
    let decodedJwtUser = JSON.parse(decodedJwtJsonUser)
    if (obj.success) {
      toastr.success(obj.message)
      getURL_inContainer('/upload')
    } else {
      toastr.error(obj.message)
      getURL_inContainer('/upload')
    }
  }
 }

 function progressFunction(evt){
  var progressBar = document.getElementById("progressBar");
  var percentageDiv = document.getElementById("percentageCalc");
  if (evt.lengthComputable) {
      progressBar.max = evt.total;
      progressBar.value = evt.loaded;
      percentageDiv.innerHTML = Math.round(evt.loaded / evt.total * 100) + "%";
  }
  
}

function loadStartFunction (evt) {
  toastr.warning('Comecando a subir o arquivo')
}

function transferCompleteFunction (evt){
  // alert('Transferencia completa');
  var progressBar = document.getElementById('progressBar')
  var percentageDiv = document.getElementById('percentageCalc')
  progressBar.value = 100
  percentageDiv.innerHTML = '100%'
}

function uploadFailed (evt) {
  //alert("Houve algum erro ao subir o arquivo");
  toastr.error('Houve algum erro ao subir o arquivo')
}

function uploadCanceled (evt) {
  //alert("Operacao cancelada ou interrompida.");
  toastr.error('Houve algum erro ao subir o arquivo')
}
// ####################### UPLOAD ############



// function getChat_inContainer(url) {
//   getURL_inContainer(url)
//   chat ('kkkk')
// }
// function loadRequestInHTML () {
//   //console.log(this.responseText)
//   document.getElementById('html').innerHTML = this.responseText

//   // document.innerHTML = this.responseText
//   // document.location.reload()
// }
function selectedFile() {
  var archivoSeleccionado = document.getElementById("myfile");
  var file = archivoSeleccionado.files[0];
     if (file) {
         var fileSize = 0;
         if (file.size > 1048576)
            fileSize = (Math.round(file.size * 100 / 1048576) / 100).toString() + ' MB';
         else
            fileSize = (Math.round(file.size * 100 / 1024) / 100).toString() + ' Kb';
         var divfileSize = document.getElementById('fileSize');
         var divfileType = document.getElementById('fileType');
         divfileSize.innerHTML = 'Tamanho: ' + fileSize;
         divfileType.innerHTML = 'Tipo: ' + JSON.stringify(file);
      }
  }




















function setToken (jwtJSON) {
  console.log('funcao setToken')
  console.log(jwtJSON)
  localStorage.setItem('jwtJSON', jwtJSON)
  this.jwtJSON = jwtJSON
  this.token = jwtJSON.token
  console.log('this.jwtJSON <= ' + jwtJSON)
}

function destroyToken() {
  localStorage.removeItem('jwtJSON')
  console.log('Logout realizado e token destruido')
}

function ReqListener () {
  console.log(this.responseText)
  // document.getElementById('jwtJSON').innerHTML = this.responseText;
  // window.localStorage.setItem('jwtJSON', this.responseText)
  console.log('ReqListener: this.responseText = ' + this.responseText)
}

// $.ajax({
//     url: 'http://192.168.15.3:8080/admin',
//     headers: {
//         'Authorization': 'Bearer ' + obj.token,
//         'Content-Type':'application/x-form-urlencoded'
//     },
//     method: 'GET',
//     dataType: 'text/plain',
//     data: 'sucessoooooo',
//     success: function(data){
//         console.log('succesSSSSSSSSSSSSSS: '+data);
//     }
// });
// var client = new XMLHttpRequest();
// client.open('GET', '/admin');
// client.setRequestHeader( 'Authorization', 'Bearer ' + obj.token );
// client.send();
// client.onload = ReqListener;

window.onload = checkToken()

window.onload = function () {
  jwtJSON = localStorage.getItem('jwtJSON')
  this.jwtJSON = localStorage.getItem('jwtJSON')
  // document.querySelectorAll('div_logged_user').innerHTML = '<div> kkkkkk </div>'
  console.log('rodei a onload  ---------------')
  var jsonobj = JSON.parse(jwtJSON)
  if (jsonobj && jsonobj.sucess) {
    console.log(jsonobj)
    document.getElementById('logged_user').innerHTML = this.username + '<a href="" onclick="logout();" > Logout </a>'
    document.getElementById('logged_user').innerHTML = '<a href="" onclick="account(\'' + this.username + "');\" > " + this.username + ' </a>' + '<a href="" onclick="logout();" > Logout </a>'
  }
  //toaster.success('Have fun storming the castle!', 'Miracle Max Says')
}