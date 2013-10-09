#ifndef __USER_DATA__
#define __USER_DATA__
class UserData{
public :
	static char server[20];
	static char username[20];
	static char passwd[20];
	static int userid;
	static int face;
	static int rank;
	static int magicBubbleNum;
	static int emotion;
	static int httpAns;
	static void fetchData();
	static void regist();
	static void login();
	static void checkName();
	static size_t writehtml(uint8_t* ptr,size_t size,size_t number,void *stream);
};
char UserData::server[20];
char UserData::passwd[20];
char UserData::username[20]="ROOT";
int UserData::userid=1;
int UserData::face=2;
int UserData::rank=19;
int UserData::magicBubbleNum=999;
int UserData::emotion=3;
int UserData::httpAns;
void UserData::fetchData(){
	UserData::face=1;
	UserData::rank=1;
	UserData::magicBubbleNum=0;
	UserData::emotion=1;
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
       curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writehtml); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
	if(res!=0){
		httpAns=-404;
	}
	else
	    UserData::userid=httpAns;
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
       curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writehtml); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
    curl_easy_cleanup(curl);
    if(httpAns!=-1 and httpAns!=-404){
    	sprintf(UserData::username,"%s",username);
    	UserData::userid=httpAns;
    	UserData::fetchData();
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
       curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writehtml); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
    curl_easy_cleanup(curl);
}
size_t UserData::writehtml(uint8_t* ptr,size_t size,size_t number,void *stream){
	char ans[4];
	ans[0]=*(ptr+12);	ans[1]=*(ptr+13);	ans[2]=*(ptr+14);	ans[3]=*(ptr+15);
	UserData::httpAns=atoi(ans);
	return size*number;
}
#endif
