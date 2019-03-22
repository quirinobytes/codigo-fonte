var express = require('express')
var https = require('https')
var http = require('http')
var fs = require('fs')
var app = express()

const options = {
  key: fs.readFileSync('keys/key.pem'),
  cert: fs.readFileSync('keys/cert.pem')
}

app.get('/http', function (req, res) {
  res.writeHead(200, { 'Content-Type': 'text/plain' })
  res.end('hello world\n')
  res.end('carregado HTTP')
})

app.get('/https', function (req, res) {
  res.writeHead(200, { 'Content-Type': 'text/plain' })
  res.end('hello world\n')
  res.end('carregado HTTPS')
})

http.createServer(app).listen(80)
https.createServer(options, app).listen(443)
