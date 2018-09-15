var io = require('socket.io-client'),
socket = io.connect('192.168.15.15', { port: 8080 });
socket.on('connect', function () { console.log("socket connected"); });
socket.emit('notificacao', { user: 'me', msg: 'whazzzup?' });
