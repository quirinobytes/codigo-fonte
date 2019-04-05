require('rootpath')()
const express = require('express')
const rootController = require('./controllers/root')
const loginController = require('./controllers/login')
const compression = require('compression')
const router = express.Router()
const jwt = require('jsonwebtoken')
const exjwt = require('express-jwt')
const path = require('path')
const fs = require('fs')
// Formidable para upload de arquivos
var formidable = require('formidable')

//  const accountRoutes = require('./account.js')
const jwtCheckAuth = exjwt({
  secret: 'moto4ever'
})

let users = [
  {
    id: 1,
    username: 'admin',
    password: '123'
  },
  {
    id: 2,
    username: 'test2',
    password: 'asdf12345'
  }
]

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
    const { username, password } = req.body;
    console.log('req.body=' + req.body)
    // Use your DB ORM logic here to find user and compare password
    for (let user of users) { // I am using a simple array users which i made above
      if (username === user.username && password === user.password /* Use your password hash checking logic here !*/) {
        // If all credentials are correct do this
        let token = jwt.sign({ id: user.id, username: user.username }, 'moto4ever', { expiresIn: 129600 }); // Sigining the token
        res.json({
          success: true,
          err: null,
          token
        })
        break
      } else {
        res.status(401).json({
          success: false,
          token: null,
          err: 'Username or password is incorrect'
        })
      }
    }
  })

router.post('/getusers', jwtCheckAuth, (req, res) => {
  var users = [
    {
      name: 'admin',
      password: '123',
      role: 'admin'
    },
    {
      name: 'rafael',
      password: 'rafa123',
      role: 'user'
    }
  ]
  var user_list = []
  users.forEach((user) => {
    user_list.push({ 'name': user.name })
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
  console.log('cheguei na Chat')
 // console.log(req.headers.authorization)
  res.header('Authorization', req.headers.authorization)
  res.redirect('/authorize/chat')
  // res.render('chat', { page: 'Chat Web' })
})
router.get('/authorized/chat', function (req, res) {
  console.log('cheguei na Autorized/Chat')
  res.render('chat', { page: 'Chat Web' })
})

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
router.get('/upload', jwtCheckAuth, function (req, res) {
  var path = './fileupload/'
  // abre o diretorio path e renderiza para o ejs renderizar o arquivo upload.ejc com a var items
  fs.readdir(path, (err, files) => res.render('upload', { page: 'Home Pages', items: files }))
})

router.post('/fileupload', function (req, res) {
  var form = new formidable.IncomingForm()
  form.parse(req, function (err, fields, files) {
    var oldpath = files.filetoupload.path
    var newpath = './fileupload/' + files.filetoupload.name
    fs.rename(oldpath, newpath, function (err) {
      if (err) throw err
        // res.write('File uploaded and moved!');
        res.redirect ('./upload')
        res.end()
    })
  })
})

// ####################################
router.get('/favicon.ico', function (req, res) {
  console.log('Someone request file: favicon.ico')
  res.sendFile('favicon.ico', {
    root: path.join(__dirname, '../img/')
  })
})

// router.use('/account', accountRoutes)
// router.get('/', jwtCheckAuth, function (req, res) {
//   res.send('Wiki home page')
// })
//router.use('/', rootController.root)
// use some middleware and compress all outgoing responses


module.exports = router
