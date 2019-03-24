const express = require('express')
const rootRoutes = require('./root')
const compression = require('compression')
const router = express.Router()
//  const accountRoutes = require('./account.js')

// Fazendo uma rota com router.get
router.get('/test', (req, res) => {
  res.send('test route')
  console.log('Entrei na http://serverip/test')
})

// Fazendo uma rota com middlewqare(controller) rootRoutes.login
router.use('/', rootRoutes.login)

// use some middleware and compress all outgoing responses
router.use(compression())

// router.get('/', function (req, res) {
//   res.send('Wiki home page')
// })

// router.use('/account', accountRoutes)
module.exports = router
