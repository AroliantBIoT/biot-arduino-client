#ifndef _BIOTETHERNETCLIENT_H
#define _BIOTETHERNETCLIENT_H

#include <SPI.h>
#include <Ethernet.h>


class BIoTEthernetClient{

public:
	EthernetClient client;
	String EVENT_UPDATE = "param:update";
	int count = 0;

	void begin(const byte ip[], const byte mac[]){
		Ethernet.begin(mac,ip);
	}

	bool connect(const byte server[], const int port, const String token){

		client.connect(server,port);

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

	String getEventName(String message){
		char st[50];
    	message.toCharArray(st, 50);
		count = 0; 
		char *ch;
	    ch = strtok(st, "|");
	    while (ch != NULL)
	    {
	      String str(ch);
	      if (count == 0 ) {
	      	return str;
	      }
	      count++;
	      ch = strtok(NULL, ",");
	  	}
	}

	int getDeviceID(String message){
		char st[50];
    	message.toCharArray(st, 50);
		count = 0; 
		char *ch;
	    ch = strtok(st, "|");
	    while (ch != NULL)
	    {
	      String str(ch);
	      if (count == 1 ) {
	      	return str.toInt();
	      }
	      count++;
	      ch = strtok(NULL, ",");
	  	}
	}

	String getParamName(String message){
		char st[50];
    	message.toCharArray(st, 50);
		count = 0; 
		char *ch;
	    ch = strtok(st, "|");
	    while (ch != NULL)
	    {
	      String str(ch);
	      if (count == 2 ) {
	      	return str;
	      }
	      count++;
	      ch = strtok(NULL, ",");
	  	}
	}

	String getParamValue(String message){
		char st[50];
    	message.toCharArray(st, 50);
		count = 0; 
		char *ch;
	    ch = strtok(st, "|");
	    while (ch != NULL)
	    {
	      String str(ch);
	      if (count == 3 ) {
	      	return str;
	      }
	      count++;
	      ch = strtok(NULL, ",");
	  	}
	}

	void sendUpdate(int deviceID, String param, String value){
		char buff[50];
		String message = "param:update|";
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

};


#endif
