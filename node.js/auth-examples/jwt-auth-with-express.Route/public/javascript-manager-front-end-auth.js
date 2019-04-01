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
      //document.getElementById('token-display').innerHTML = response
      //document.getElementById('jwtJSON').innerHTML = response
      console.log('response=' + response)

      var json = response;
      var obj = JSON.parse(json)

      // Caso logado com sucesso, cria o localStorage com o jwtJSON
      if (obj.sucess) {
        this.token = obj.token
        localStorage.setItem('jwtJSON', response)
        token = obj.token
        let jwtUser = token.split('.')[1]
        let decodedJwtJsonUser = window.atob(jwtUser)
        let decodedJwtUser = JSON.parse(decodedJwtJsonUser)

        getURL_inBody('/index')

        // document.getElementById('logged_user').innerHTML = '<a href="" onclick="account(\'' + decodedJwtJsonUser.username + "');\" > " + decodedJwtJsonUser.username +' </a>' + '<a href="" onclick="logout();" > Logout </a>'
      }
      console.log('Token = ' + obj.token)
    }
  }
  xhttp.open("POST", "./login", true)
  xhttp.setRequestHeader("Content-type", 'application/json; charset=UTF-8')
  xhttp.send(JSON.stringify(data))
}

function getURL_inBody(url) {
  var xhttp = new XMLHttpRequest()
  var jwtData = localStorage.getItem('jwtJSON')
  var jwtObj = JSON.parse(jwtData)

  xhttp.open('GET', url)
  xhttp.setRequestHeader( 'Authorization', 'Bearer ' + jwtObj.token)
  xhttp.send()
  xhttp.onload = loadRequestInHTML
}

function loadRequestInHTML () {
  document.getElementById('html').innerHTML = this.responseText
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
}
