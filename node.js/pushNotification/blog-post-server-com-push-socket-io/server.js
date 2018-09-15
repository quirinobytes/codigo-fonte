#!/usr/bin/env node
var express = require('express')
  , app = express()
  , server = require('http').createServer(app).listen(4555)
  , io = require('socket.io').listen(server)
  , bodyParser = require('body-parser');
  app.use(bodyParser.urlencoded({ extended: true }));
  app.use(bodyParser.json());
  var port = process.env.PORT || 8080;
  var router = express.Router();
  /* Socket irá aqui depois */
  var emitir = function(req, res, next){
	var notificar = req.query.notificacao || '';
		if(notificar != '')	 {
		io.emit('notificacao', notificar);
		next();
	} else {
			next();
		}
	}
  app.use(emitir);
  app.use('/api', router);
  router.route('/notificar')
    .get(function(req, res){
    //aqui vamos receber a mensagem
    res.json({message: "testando essa rota"})
    })
   app.get('/', function(req, res){
    //aqui vamos receber a mensagem
    res.sendfile("index.html")
	res.end
    })


  app.listen(port);
  console.log('conectado a porta ' + port);






 //MANUEL

  // enviar apenas para o cliente atual
  // client.emit('message', "this is a test");
  //
  // // enviar para todos os clientes, inclusive o atual
  // io.emit('message', "this is a test");
  //
  // // enviar para todos os clientes, exceto o atual
  // client.broadcast.emit('message', "this is a test");
  //
  // // enviar para todos os clientes (com exceção do atual) para uma sala específica
  // socket.broadcast.to('game').emit('message', 'nice game');
  //
  // // enviar para todos os clientes em uma sala específica
  // io.in('game').emit('message', 'cool game');
  //
  // // enviar para o atual, caso ele esteja na sala
  // client.to('game').emit('message', 'enjoy the game');
  //
  // // enviar para todos os clientes em um namespace 'namespace1'
  // io.of('namespace1').emit('message', 'gg');
  //
  // // enviando para um socketid individual
  // client.broadcast.to(socketid).emit('message', 'for your eyes only');
