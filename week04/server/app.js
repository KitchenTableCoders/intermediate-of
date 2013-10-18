/*
npm init
npm install ws --save
npm install mongojs --save
https://github.com/einaros/ws
*/

var util = require('util')
	, mongojs = require('mongojs')
	, WebSocketServer = require('ws').Server
	, wss = new WebSocketServer({port: 8080});

var connectionString = "mongodb://kitchen:274morgan@ds049868.mongolab.com:49868/kitchen";
var db = mongojs(connectionString, ['lines']);




console.log("starting web socket server.");

wss.on('connection', function(ws) {
	console.log((new Date())+" new connection");

	db.lines.find(function(err, docs) {
		docs.forEach(function(doc){
			ws.send(doc);
		});
	});

	ws.on('message', function(message) {
		console.log('received: %s', message);

	});

	ws.on('error', function(err){
		console.log("error: "+err);
	})

	//ws.send('something');
});
