const express = require('express')
const rootController = require('./controllers/root')
const loginController = require('./controllers/login')
const compression = require('compression')
const router = express.Router()
//  const accountRoutes = require('./account.js')

// Fazendo uma rota com middlewqare(controller) rootRoutes.login

router.use('/login', loginController.login)
router.use('/test', loginController.test)
router.use('/', rootController.root)
// use some middleware and compress all outgoing responses
router.use(compression())

// router.get('/', function (req, res) {
//   res.send('Wiki home page')
// })

// router.use('/account', accountRoutes)
module.exports = router
