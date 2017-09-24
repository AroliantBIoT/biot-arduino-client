#ifndef _BIOTMESSAGE_H
#define _BIOTMESSAGE_H

#include <BIoT.h>

using namespace std;

class BIoTMessage{

	public:
		String message;			
		int deviceID;	
		String eventName;
		String paramName;
		String paramValue;
		int count = 0;

		BIoTMessage(String message){
			char st[50];
	    	message.toCharArray(st, 50);
			count = 0; 
			char *ch;
		    ch = strtok(st, "|");
		    while (ch != NULL)
		    {
		      String str(ch);
		      if (count == 0 ) {
		      	eventName = str;
		      }else if( count == 1 ){
		      	deviceID = str.toInt();
		      }else if( count == 2 ){
		      	paramName = str;
		      }else if( count == 3 ){
		      	paramValue = str;
		      }
		      count++;
		      ch = strtok(NULL, ",");
		  	}
		}

		int getDeviceID(){
			return deviceID;
		}

		String getEventName(){
			return eventName;
		}

		String getParamName(){
			return paramName;
		}

		String getParamValue(){
			return paramValue;
		}

		String getLog(){
			String log = "";
			log += "Device ID : ";
			log += deviceID;
			log += "\n";
			log += "Event Name : ";
			log += eventName + "\n";
			log += "Param Name : ";
			log += paramName + "\n";
			log += "Param Value : ";
			log += paramValue;
			return log;
		}



};


#endif
