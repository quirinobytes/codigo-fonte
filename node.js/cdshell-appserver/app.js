require('rootpath')()
var config = require('config').get(process.env.NODE_ENV)
const errorHandler = require('errorhandler')
const bodyParser = require('body-parser')
const https = require('https')
const rotas = require('./routes')
const express = require('express')
var app = express()
const isProduction = process.env.NODE_ENV === 'production'

// Fala para o App usar o arquivo de configuracao de rotas
// app.use(rotas)
app.use(require('./routes'))

// nao sei pra que serve ainda
app.use(bodyParser.json())

// error Handler
if (!isProduction) {
  app.use(errorHandler())
} else {
  console.log('\n\t\t-------------------------')
  console.log('\t -----> |  * PRODUCTION MODE *  |  <-----')
  console.log('\t\t-------------------------\n\n\n')
}

// exportando app
module.exports = app
