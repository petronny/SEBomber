#ifndef __USER_DATA__
#define __USER_DATA__
#include "curl/curl.h"
#include "AniReader.hpp"
class UserData{
public :
	static UserData *current;
	char server[20];
	char username[20];
	char passwd[20];
	int userid;
	int roomid;
	int face;
	static int http_face;
	int rank;
	static int http_rank;
	int coinNum;
	static int http_coinNum;
	int emotion;
	static int http_emotion;
	static int httpAns;
	int item[30];
	static char http_item[80];
	bool itemSelect[30];
	int buddylist[40];
	int roomlist[8];
	static int http_roomlist[8];
	void fetchBasicData();
	void fetchExtraData();
	void regist();
	void login();
	void checkName();
	UserData();
	void updateMoney();
	void updateEmotion();
	void updateAvatar();
	void fetchRoomData();
	static size_t getUserID(uint8_t* ptr,size_t size,size_t number,void *stream);
	static size_t getBasicData(uint8_t* ptr,size_t size,size_t number,void *stream);
	static size_t getExtraData(uint8_t* ptr,size_t size,size_t number,void *stream);
	static size_t getEmpty(uint8_t* ptr,size_t size,size_t number,void *stream);
	static size_t getRoomData(uint8_t* ptr,size_t size,size_t number,void *stream);
};
UserData *UserData::current=new UserData;
int UserData::httpAns;
int UserData::http_face;
int UserData::http_rank;
int UserData::http_emotion;
int UserData::http_coinNum;
char UserData::http_item[80];
int UserData::http_roomlist[8];
UserData::UserData(){
	coinNum=100;
	roomid=1;
	memset(item, 0, sizeof(item));
	memset(itemSelect, 0, sizeof(itemSelect));
}
void UserData::fetchExtraData(){
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80],writeData[80],url[80];
	if (curl){
		sprintf(url,"http://%s:8080/Server/fetchExtraData.jsp",server);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		sprintf(postField,"userid=%d",userid);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField);
	   curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	   curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,getExtraData); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
		curl_easy_cleanup(curl);
	this->coinNum=UserData::http_coinNum;
	int i=0;
	while(UserData::http_item[i]){
		item[i]=UserData::http_item[i]-'a';
		i++;
	}
}
void UserData::fetchBasicData(){
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80],writeData[80],url[80];
	if (curl){
		sprintf(url,"http://%s:8080/Server/fetchBasicData.jsp",server);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		sprintf(postField,"userid=%d",userid);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField);
	   curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	   curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,getBasicData); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
	curl_easy_cleanup(curl);
	this->face=UserData::http_face;
	this->rank=UserData::http_rank;
	this->emotion=UserData::http_emotion;
}
void UserData::checkName(){
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80],writeData[80],url[80];
	if (curl){
		sprintf(url,"http://%s:8080/Server/check.jsp",server);
		CCLog("%s!",url);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		sprintf(postField,"username=%s",username);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField);
       curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
       curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,getUserID); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
	if(res!=0){
		httpAns=-404;
	}
	else
	    userid=httpAns;
    curl_easy_cleanup(curl);
}
void UserData::login(){
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80],writeData[80],url[80];
	if (curl){
		sprintf(url,"http://%s:8080/Server/login.jsp",server);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		sprintf(postField,"username=%s&password=%s",username,passwd);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField);
       curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
       curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,getUserID); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
    curl_easy_cleanup(curl);
    if(httpAns!=-1 and httpAns!=-404){
    	UserData::userid=httpAns;
    	fetchBasicData();
    	fetchExtraData();
    }
}
void UserData::regist(){
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80],writeData[80],url[80];
	if (curl){
		sprintf(url,"http://%s:8080/Server/regist.jsp",server);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		sprintf(postField,"username=%s&password=%s",username,passwd);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField);
       curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
       curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,getEmpty); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
    curl_easy_cleanup(curl);
}
size_t UserData::getUserID(uint8_t* ptr,size_t size,size_t number,void *stream){
	char ans[4];
	ans[0]=*(ptr+12);	ans[1]=*(ptr+13);	ans[2]=*(ptr+14);	ans[3]=*(ptr+15);
	UserData::httpAns=atoi(ans);
	return size*number;
}
size_t UserData::getBasicData(uint8_t* ptr,size_t size,size_t number,void *stream){
	char ans[80];
	int i=12;
	while(*(ptr+i)){
		ans[i-12]=*(ptr+i);
		i++;
	}
	ans[i-12]=*(ptr+i);
	sscanf(ans,"%d %d %d", &UserData::http_face, &UserData::http_rank, &UserData::http_emotion);
	return size*number;
}
size_t UserData::getExtraData(uint8_t* ptr,size_t size,size_t number,void *stream){
	char ans[80];
	int i=12;
	while(*(ptr+i)){
		ans[i-12]=*(ptr+i);
		i++;
	}
	ans[i-12]=*(ptr+i);
	sscanf(ans,"%d %s", &UserData::http_coinNum, UserData::http_item);
	return size*number;
}
void UserData::updateMoney(){
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80],writeData[80],url[80];
	if (curl){
		sprintf(url,"http://%s:8080/Server/updateMoney.jsp",server);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		sprintf(postField,"userid=%d&money=%d",userid,coinNum);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField);
       curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
       curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,getEmpty); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
    curl_easy_cleanup(curl);
}
size_t UserData::getEmpty(uint8_t* ptr,size_t size,size_t number,void *stream)
{
	return size*number;
}
void UserData::updateEmotion(){
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80],writeData[80],url[80];
	if (curl){
		sprintf(url,"http://%s:8080/Server/updateEmotion.jsp",server);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		sprintf(postField,"userid=%d&emotion=%d",userid,emotion);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField);
	   curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	   curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,getEmpty); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
	curl_easy_cleanup(curl);
}
void UserData::updateAvatar(){
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80],writeData[80],url[80];
	if (curl){
		sprintf(url,"http://%s:8080/Server/updateAvatar.jsp",server);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		sprintf(postField,"userid=%d&avatar=%d",userid,face);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField);
	   curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	   curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,getEmpty); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
	curl_easy_cleanup(curl);
}
void UserData::fetchRoomData(){
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80],writeData[80],url[80];
	if (curl){
		sprintf(url,"http://%s:8080/Server/fetchRoomData.jsp",server);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		sprintf(postField,"roomid=%d", roomid);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField);
	   curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	   curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,getRoomData); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
	curl_easy_cleanup(curl);
	for(int i=0; i<8; i++){
		roomlist[i]=UserData::http_roomlist[i];
	}
}
size_t UserData::getRoomData(uint8_t* ptr,size_t size,size_t number,void *stream){
	char ans[80];
	int i=12;
	while(*(ptr+i)){
		ans[i-12]=*(ptr+i);
		i++;
	}
	ans[i-12]=*(ptr+i);
	sscanf(ans,"%d %d %d %d %d %d %d %d", &UserData::http_roomlist[0], &UserData::http_roomlist[1], &UserData::http_roomlist[2], &UserData::http_roomlist[3], &UserData::http_roomlist[4],
			&UserData::http_roomlist[5], &UserData::http_roomlist[6], &UserData::http_roomlist[7]);
	return size*number;
}
#endif
