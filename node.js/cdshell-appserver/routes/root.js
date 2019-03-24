// require('rootpath')()
// const express = require("express")
// //const mainController = require('routes/controllers/main')
var config = require('config').get(process.env.NODE_ENV)
const express = require('express')
const router = express.Router()

var login = function (req, res) {
  console.log('Login middleware')
  console.log('req=\n' + req)
  res.send('Login')
}

var rafa = function (req, res) {
  console.log('Rafa middleware')
  res.send('Rafa')
}

var config = (req, res, next) => {
  return config
}

// isso exporta um objeto com os valores de login e config
module.exports = { login: login, rafa: rafa }
