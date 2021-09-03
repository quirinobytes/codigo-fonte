#!/usr/bin/env node
const express = require('express');
const bodyParser = require('body-parser');
let jwt = require('jsonwebtoken');
let config = require('./config');
let middleware = require('./middleware');

//Get ENV PORT or set 8000
const port = process.env.PORT || 8000;
var successLogins = 0;

class HandlerGenerator {
  login (req, res) {
    let username = req.body.username;
    let password = req.body.password;
    // For the given username fetch user from DB
    let mockedUsername = 'admin';
    let mockedPassword = 'senha';

    if (username && password) {
      if (username === mockedUsername && password === mockedPassword) {
        let token = jwt.sign({username: username},
          config.secret,
          { expiresIn: '1m' // expires in 1m or 24h
          }
        );
        // return the JWT token for the future API calls
        res.json({
          success: true,
          message: 'Authentication successful!',
          token: token
        });
        successLogins+=1;
        console.log(successLogins + " - Login success from: " + req.connection.remoteAddress);
        console.log("Request IP: " + req.connection.remoteAddress );

      } else {
                res.send(403).json({
          success: false,
          message: 'Incorrect username or password'
        });
        console.log("Incorrect username or password");
        console.log("Request IP: " + req.connection.remoteAddress );

      }
    } else {
      res.send(400).json({
        success: false,
        message: 'Authentication failed! Please check the request'
      });
    }
  }
  index (req, res) {
    res.json({
      success: true,
      message: 'Index page'
    });
  }
}

// Starting point of the server
function main () {
  let app = express(); // Export app for other routes to use
  let handlers = new HandlerGenerator();
  app.use(bodyParser.urlencoded({ // Middleware
    extended: true
  }));
  app.use(bodyParser.json());
  // Routes & Handlers
  app.post('/login', handlers.login);
  app.get('/', middleware.checkToken, handlers.index);
  app.listen(port, () => console.log(`Server is listening on port: ${port}`));
}


console.log("Iniciando a server-jwt-token-bearer")
console.log("use curl -X POST http://localhost:"+port+ "/login --data username=admin --data password=senha");

main();
