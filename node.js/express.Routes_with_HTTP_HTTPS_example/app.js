require('rootpath')()
var config = require('config').get(process.env.NODE_ENV)
const bodyParser = require('body-parser')
const https = require('https')
const rotas = require('./routes')
const express = require('express')
var app = express()

// Fala para o App usar o arquivo de configuracao de rotas
app.use(rotas)

// nao sei pra que serve ainda
app.use(bodyParser.json())

// exportando app
module.exports = app
