require('rootpath')()
var config = require('../config').get(process.env.NODE_ENV)
const express = require('express')
const rootController = require('./controllers/root')
const loginController = require('./controllers/login')
const compression = require('compression')
const router = express.Router()
const jwt = require('jsonwebtoken')
const exjwt = require('express-jwt')
const path = require('path')
const fs = require('fs')
const atob = require('atob')

// Formidable para upload de arquivos
var formidable = require('formidable')

//  const accountRoutes = require('./account.js')
const jwtCheckAuth = exjwt({
  secret: 'moto4ever'
})

//carregando os usuarios da config.
let users = config.users

// let users = [
//   {
//     id: 1,
//     username: 'admin',
//     password: '123'
//   },
//   {
//     id: 2,
//     username: 'test2',
//     password: 'asdf12345'
//   }
// ]

// ####################################

router.use(compression())

router.get('/', function (req, res) {
  res.redirect('/index')
})
// ####################################
// Fazendo uma rota com middlewqare(controller) rootRoutes.login
router
  .get('/login', loginController.login)
  .post('/login', (req, res) => {
    var retornaErro401 = false
    const { username, password } = req.body;
    console.log('req.body=' + req.body)
    // Use your DB ORM logic here to find user and compare password
    for (let user of users) { // I am using a simple array users which i made above
      console.log('entrou a vez do user= '+ user.username)
      // Use your password hash checking logic here ! 
      if (username === user.username && password === user.password ) {
        // If all credentials are correct do this
        console.log('Usuario e senha certinho')
        let token = jwt.sign({ id: user.id, username: user.username }, 'moto4ever', { expiresIn: 129600 })
        res.json({
          success: true,
          err: null,
          token
        })
        break
      } else {
        retornaErro401 = true
      }
    }
    if (retornaErro401 === true) {
      // isso aqui tem que ficar fora do For, senha nao percorre todos os users, e responde null antes da hora.
      res.status(401).json({
        success: false,
        token: null,
        err: 'Username or password is incorrect'
      })
    }
})

router.post('/getusers', jwtCheckAuth, (req, res) => {
  var users = [
    {
      username: 'admin',
      password: '123',
      role: 'admin'
    },
    {
      username: 'rafael',
      password: 'rafa123',
      role: 'user'
    }
  ]
  var user_list = []
  users.forEach((user) => {
    user_list.push({ 'name': user.username })
  })
  res.send(JSON.stringify({ users: user_list }))
})

// ####################################
router.get('/admin', jwtCheckAuth, function (req, res) {
  console.log('cheguei na Admin')
  res.render('admin', { page: 'Admin Pages' })
  // res.send('<h1> Admin Pages load sucessful </h1>')
})

// ####################################
router.get('/chat', jwtCheckAuth, function (req, res) {
  console.log('### CHAT=> Username=' + req.headers.authorization )
  token = req.headers.authorization
  let jwtUser = token.split('.')[1]
  let decodedJwtJsonUser = atob(jwtUser)
  let decodedJwtUser = JSON.parse(decodedJwtJsonUser)

  console.log('cheguei na Chat/ LoggedUser:' + decodedJwtUser.username)
  res.render('chat', { page: 'Chat Web', username: decodedJwtUser.username })
})

// router.get('/authorized/chat', function (req, res) {
//   res.header('Authorization', req.headers.authorization)
//   res.redirect('/authorize/chat')
//   // res.render('chat', { page: 'Chat Web' })
// })

// ####################################
router.get('/users', jwtCheckAuth, function (req, res) {
  res.render('users', { page: 'User Manager', users: users })
})

// ####################################
router.get('/index',jwtCheckAuth,  function (req, res) {
  console.log('cheguei na Index')
  res.render('index', { page: 'Home Pages' })
})

// ####################################
router.get('/menu', jwtCheckAuth, function (req, res) {
  res.sendFile('menu.html', {
    root: path.join(__dirname, '../views/')
  })
})

// ####################################
router.get('/upload', function (req, res) {
  var path = './fileupload/'
  // abre o diretorio path e renderiza para o ejs renderizar o arquivo upload.ejc com a var items
  fs.readdir(path, (err, files) => res.render('upload', { page: 'Home Pages', items: files }))
})

router.post('/fileupload', function (req, res) {
  let token = req.headers.authorization
  var form = new formidable.IncomingForm()
  form.parse(req, function (err, fields, files) {
    
    // kkkkk esse eh estrategico para exainar o arquivo chegando.
    // console.log(files)
    if (files.filetoupload !== undefined ){
      var oldpath = files.filetoupload.path
      var newpath = './fileupload/' + files.filetoupload.name

      fs.rename(oldpath, newpath, function (err) {
      
        if (err){
          throw err
          res.status(401).json({
            success: false,
            token: null,
            err: 'Username or password is incorrect'
          })
        } else {

          res.json({
            success: true,
            message: 'Arquivo subido', // + //filename + ' excluido.',
            token
          })
        }
    })
  }
      //if (files)
  })
})

// ####################################
router.get('/favicon.ico', function (req, res) {
  console.log('Someone request file: favicon.ico')
  res.sendFile('favicon.ico', {
    root: path.join(__dirname, '../img/')
  })
})

router.get('/deletefile/:filename', function (req,res) {

  const filename = req.params.filename
  const path = './fileupload/'
  let token = req.headers.authorization

  //responder certinho neh.
  try {
    fs.unlinkSync(path+filename)
    console.log("Arquivo apagado="+filename)
    res.json({
      success: true,
      message: 'Arquivo ' + filename + ' excluido.',
      token
    })
  } catch(err) {
    console.error(err)
    res.status(401).json({
      success: false,
      token: token,
      err: 'Falha ao excluir arquivo.',
      message: 'Falha ao excluir arquivo: ' + filename
    })
  }
})

// router.use('/account', accountRoutes)
// router.get('/', jwtCheckAuth, function (req, res) {
//   res.send('Wiki home page')
// })
//router.use('/', rootController.root)
// use some middleware and compress all outgoing responses


module.exports = router
