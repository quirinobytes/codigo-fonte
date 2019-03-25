var config = require('config').get(process.env.NODE_ENV)
const express = require('express')
const router = express.Router()
const path = require('path')

var login = function (req, res, next) {
  res.sendFile('index.html', {
    root: path.join(__dirname, '../../views/')
  })
}

var test = function (req, res, next) {
  console.log('Test middleware')
  res.send('Test')
}

module.exports = { login: login, test: test }
