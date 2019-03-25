const express = require('express')
const router = express.Router()
// require('rootpath')()
// //const mainController = require('routes/controllers/main')

var root = function (req, res, next) {
  console.log('Root middleware')
  res.send('Root route')
}

// isso exporta um objeto com os valores de login e config
module.exports = { root: root }
