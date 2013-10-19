/*
npm init
npm install ws --save
npm install mongojs --save

https://github.com/mafintosh/mongojs
https://github.com/einaros/ws
*/

var util = require('util')
	, mongojs = require('mongojs')
	, ObjectId = mongojs.ObjectId
	, WebSocketServer = require('ws').Server
	, wss = new WebSocketServer({port: 8080})
	

var connectionString = "mongodb://kitchen:274morgan@ds049868.mongolab.com:49868/kitchen";
var db = mongojs(connectionString, ['lines']);


// TO DO:  When a new line is saved, send it out to all of the clients


console.log("starting web socket server.");

wss.broadcast = function(data) {
    for(var i in this.clients)
        this.clients[i].send(data);
};

wss.on('connection', function(client) {
	console.log((new Date())+" new connection");

	db.lines.find(function(err, docs) {
		docs.forEach(function(doc) {
			console.log("sending line");
			var message = {"route": "addline", "line": doc};
			client.send( JSON.stringify(message) );
		});
	});


	client.on('message', function(message) {
		var json = JSON.parse(message);
		if(json.route=="addline") {
			db.lines.save(json["line"], function(err, doc){
				if(err) {
					console.log(err);
				} else {
					console.log("saved");
					wss.broadcast( message );
				}
			});
		}

		if(json.route=="removeline") {
			db.lines.remove({"_id": ObjectId(json.id)}, function(err, doc){
				if(err) {
					console.log(err);
				} else {
					console.log("deleted");
					wss.broadcast( message );
				}
			});
		}
	});

	client.on('close', function() {
		
	});

	client.on('error', function(err){
		console.log("error: "+err);
	});

	//client.send('something');
});
