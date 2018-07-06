/*
 * Network.cpp
 *
 *  Created on: 2017年10月27日
 *      Author: Kwolve
 */

#include "Network.h"
#include "pthread.h"
#include "system/Thread.h"
#include "utils/Log.h"

#include "uart/ProtocolData.h"
#include "uart/ProtocolParser.h"
#include "utils/TimeHelper.h"
#include "uart/ProtocolSender.h"
#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>
#include <errno.h>

#include "net/NetManager.h"

#define URL_TIME	"http://www.baidu.com"

class HttpThread:public Thread{
public:
	HttpThread(){

	}
	~HttpThread(){

	}
private:
	virtual bool threadLoop();
};

HttpThread* mThread;
Network::Network() {
	// TODO Auto-generated constructor stub
	mThread = new HttpThread();
	mThread->run("HttpThread");
}

Network::~Network() {
	// TODO Auto-generated destructor stub

}
void Logfun(std::string str){
	LOGD("[HTTP]%s\r\n",str.c_str());
}
static bool bUpdateTime = false;

std::vector<std::string> stringSplit(std::string str,std::string split)
{
	std::string::size_type pos;
	std::vector<std::string> splitstr;
	str += split;			// 扩展字符串以方便操作
	int size = str.size();
	for (int i = 0; i < size; i++) {
		pos = str.find(split, i);
		if (pos < size) {
			std::string s = str.substr(i, pos - i);
			splitstr.push_back(s);
			i = pos + split.size() - 1;
		}
	}
	return splitstr;
}
void updateSystemTime(){

	Log log(Logfun);
	HttpClient client(log);
	HttpResponse* response = client.RunRequest(URL_TIME, "GET");
	Logfun("Client was called, ok!");
	URL* urlObject = response->GetRequestURL();

	if (urlObject == NULL) {
		Logfun("The URL is dead");
		client.releaseRequest();
		return ;
	}
	if(response->GetHttpStatusCode() != "200"){
		Logfun("Request information code:"+response->GetHttpStatusCode());
		Logfun("Request information text:"+response->GetHttpStatusText());
		client.releaseRequest();
		return;
	}

	Logfun("Request information-------------------");
	Logfun("Protocoll: "+ urlObject->GetProtocoll());
	Logfun("Host name: "+ urlObject->GetHostName());
	Logfun("Port number: " + urlObject->GetPortNumber());

	Logfun("Basic information---------------------");
	Logfun("Version: " + response->GetHttpVersion());
	Logfun("Status code: " + response->GetHttpStatusCode());
	Logfun("Status text:" + response->GetHttpStatusText());

	Logfun("Header information---------------------");
	std::map<std::string, std::string> headers = response->GetHttpHeaders();
	std::map<std::string, std::string>::iterator it;
	//Date: Tue, 31 Oct 2017 06:09:06 GMT
	//Date: Sun, 05 Nov 2017 11:24:40 GMT
	for (it=headers.begin(); it != headers.end(); ++it) {
		Logfun(it->first+":"+it->second);
		if(it->first == "Date"){
			std::vector<std::string> strs = stringSplit(it->second," ");
			if(strs.size() == 7){
				int day = atoi(strs[2].c_str());
				int month = 11;
				if(strs[3] == "Nov"){
					month = 11;
				}else if(strs[3] == "Oct")  month = 10;
				else if(strs[3] == "Sep")  month = 9;

				int year = atoi(strs[4].c_str());

				std::vector<std::string> timestrs = stringSplit(strs[5],":");
				int hour = 0,min =  0,sec = 0;
				if(timestrs.size() == 3){
					hour = atoi(timestrs[0].c_str())+8;
					min = atoi(timestrs[1].c_str());
					sec = atoi(timestrs[2].c_str());

					BYTE buff[6];
					buff[0]=year-2000;
					buff[1]=month;
					buff[2]=day;
					buff[3] = hour;
					buff[4] = min;
					buff[5] = 0;
					sendProtocol(CMDID_NOW_TIME, 0, buff, 6);

					struct tm t;
					t.tm_year = year-1900;
					t.tm_mon = month - 1;
					t.tm_mday = day;
					t.tm_hour = hour;
					t.tm_min = min;
					t.tm_sec = sec;
					LOGD("tm_year:%d",t.tm_year);
					LOGD("t.tm_mon:%d",t.tm_mon);
					LOGD("t.tm_mday:%d",t.tm_mday);
					LOGD("t.tm_hour:%d",t.tm_hour);
					LOGD("t.tm_min:%d",t.tm_min);
					LOGD("t.tm_sec:%d",t.tm_sec);

					TimeHelper::setDateTime(&t);
					bUpdateTime = true;
				}
			}
			break;
		}
	}
	//Logfun("Raw response-------------------------");
	//Logfun(response->GetRawResponse());
	client.releaseRequest();
}
bool HttpThread::threadLoop(){
	LOGD("HttpThread Thread run\n");
	while(1){
		sleep(1000);
		bool bOpen = NETMANAGER->getWifiManager()->isWifiEnable();// mWifiManager->isWifiEnable();
		if(bOpen){
			while(1){

				if(NETMANAGER->getWifiManager()->isSupported()){
					if(!NETMANAGER->getWifiManager()->isConnected()){
						LOGD("wifi disconnect....................\n");
						sleep(1000);
						continue;
					}
					if(bUpdateTime == false){
						LOGD("bUpdateTime....................\n");
						updateSystemTime();
					}
				}else{
					LOGD("wifi is no support....................\n");
				}
				sleep(5000);
			}
		}else{
			LOGD("wifi is off\n");
		}
	}
	return false;
}
