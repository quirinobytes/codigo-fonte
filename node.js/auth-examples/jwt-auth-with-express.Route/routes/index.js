const express = require('express')
const rootController = require('./controllers/root')
const loginController = require('./controllers/login')
const compression = require('compression')
const router = express.Router()
const jwt = require('jsonwebtoken')
const exjwt = require('express-jwt')

//  const accountRoutes = require('./account.js')
const jwtMW = exjwt({
    secret: 'keyboard cat 4 ever'
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

// Fazendo uma rota com middlewqare(controller) rootRoutes.login
router
  .get('/login', loginController.login)
  .post('/login', (req, res) => {
        const { username, password } = req.body;
        console.log('req.body=' + req.body)
        // Use your DB ORM logic here to find user and compare password
        for (let user of users) { // I am using a simple array users which i made above
            if (username == user.username && password == user.password /* Use your password hash checking logic here !*/) {
                //If all credentials are correct do this
                let token = jwt.sign({ id: user.id, username: user.username }, 'keyboard cat 4 ever', { expiresIn: 129600 }); // Sigining the token
                res.json({
                    sucess: true,
                    err: null,
                    token
                });
                break;
            }
            else {
                res.status(401).json({
                    sucess: false,
                    token: null,
                    err: 'Username or password is incorrect'
                });
            }
        }
    })

router.post('/getusers', jwtMW, (req, res) => {
    var users=[
        {
          name:"xxxx",
          password:"xxxx"
        },
        {
          name:"yyyy",
          password:"yyyy"
        }
        ]
        var user_list=[];
        users.forEach((user)=>{
            user_list.push({"name":user.name});
        })
        res.send(JSON.stringify({users:user_list}));
    });

router.get('/admin', jwtMW, function (req, res) {
  console.log('cheguei na Admin')
  res.send('<h1> Admin Page, congratulations </h1>')
})

router.get('/', jwtMW, rootController.root)

// router.get('/', jwtMW, function (req, res) {
//   res.send('Wiki home page')
// })



//router.use('/', rootController.root)
// use some middleware and compress all outgoing responses
router.use(compression())




// router.use('/account', accountRoutes)
module.exports = router
