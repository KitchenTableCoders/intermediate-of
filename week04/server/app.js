/*
npm init
npm install ws --save
npm install mongojs --save

https://github.com/mafintosh/mongojs
https://github.com/einaros/ws
*/

var util = require('util')
	, mongojs = require('mongojs')
	, WebSocketServer = require('ws').Server
	, wss = new WebSocketServer({port: 8080});

var connectionString = "mongodb://kitchen:274morgan@ds049868.mongolab.com:49868/kitchen";
var db = mongojs(connectionString, ['lines']);


// TO DO:  When a new line is saved, send it out to all of the clients


console.log("starting web socket server.");

var clients = [];
wss.on('connection', function(client) {
	console.log((new Date())+" new connection");
	clients.push(client);

	db.lines.find(function(err, docs) {
		docs.forEach(function(doc) {
			client.send( JSON.stringify(doc) );
		});
	});


	client.on('message', function(message) {
		var doc = JSON.parse(message);
		db.lines.save(doc, function(doc){
			clients.forEach(function(client){
				if(clients.indexOf(client)!=-1) {
					client.send(doc);
				}
			});
		});
	});

	client.on('close', function() {
		var idx = clients.indexOf(client);
		if(idx!=-1) {
			console.log("removing client "+idx);
			clients.splice(idx, 1);
		}
	});

	client.on('error', function(err){
		console.log("error: "+err);
	});

	//client.send('something');
});
