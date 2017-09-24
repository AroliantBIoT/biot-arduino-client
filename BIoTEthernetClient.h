#ifndef _BIOTETHERNETCLIENT_H
#define _BIOTETHERNETCLIENT_H

#include <SPI.h>
#include <Ethernet.h>
#include <BIoT.h>
#include <BIoTMessage.h>

class BIoTEthernetClient{

public:
	EthernetClient client;
	int count = 0;
	byte server[];
	int port;

	void begin(const byte ip[], const byte mac[]){
		Ethernet.begin(mac,ip);
	}

	bool connect(const byte _server[], const int _port, const String token){
		memcpy(server, _server,sizeof( _server));
		port = _port;
		client.connect(_server,_port);

	}

	bool connected(){
		return client.connected();
	}

	bool available(){
		return client.available();
	}

	char read(){
		return client.read();
	}
	

	String readString(){
		return client.readString();
	}	

	void sendUpdate(int deviceID, String param, String value){
		char buff[50];
		String message = "device:set:state|";
		message += String(deviceID);
		message += ",";
		message += param;
		message += ",";
		message += value;
		message.getBytes(buff,50);
		if(client.connected()){
			client.write(buff);
			return true;
		}
		
		return false;
	}

	void run(const byte server[], const int port, const String token){
		if(client.connected()){
			
		}else{
			//Connect Client with the details provided
			client.connect(server,port);
		}
	}

	
};


#endif
