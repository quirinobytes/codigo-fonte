var config = require('config').get(process.env.NODE_ENV)
const express = require('express')
const router = express.Router()

var login = function (req, res, next) {
  console.log('Login middleware')
  res.send('Login')
}

var test = function (req, res, next) {
  console.log('Test middleware')
  res.send('Test')
  
}

module.exports = { login: login, test: test }
