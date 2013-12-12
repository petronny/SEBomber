#ifndef __USER_DATA__
#define __USER_DATA__
#include "curl/curl.h"

/**
@brief 无继承关系，主要负责在客户端与服务器的消息传递，主要与之交互的类有GameScene类、TitleSceneLoginLayer类。
*/
class UserData
{
	public :
	/**
	@brief
	*/
		static UserData *current;
		/**
		@brief 保存服务器的地址。

		*/
		char server[20];
		/**
		@brief
		*/
		char username[20];
		/**
		@brief
		*/
		char passwd[20];
		/**
		@brief 当用户成功登录后，服务器返回给该用户一个userid，通过该变量服务器可以知道是哪一用户与之通讯。

		*/
		int userid;
		/**
		@brief
		*/
		int face;
		/**
		@brief 在本地缓存一份用户数据，修改本地数据无法对服务器的数据产生影响，避免了玩家作弊。
		*/
		int rank;
		/**
		@brief 在本地缓存一份用户数据，修改本地数据无法对服务器的数据产生影响，避免了玩家作弊。
		*/
		int coinNum;
		/**
		@brief
		*/
		int emotion;
		/**
		@brief
		*/
		static int httpAns;
		/**
		@brief
		*/
		int item[30];
		/**
		@brief
		*/
		bool itemSelect[30];
		/**
		@brief
		*/
		int buddylist[40];
		int roomlist[8];
		/**
		@brief
		*/
		void fetchBasicData();
		/**
		@brief
		*/
		void fetchExtraData();
		/**
		@brief 向服务器发送注册请求
		*/
		void regist();
		/**
		@brief 向服务器发送登录请求

		*/
		void login();
		/**
		@brief 检测用户名是否正确

		*/
		void checkName();
		/**
		@brief
		*/
		UserData();
		/**
				/**
		@brief
		*/
		UserData(int id);
		/**

		@brief 向服务器发送用户操作

		*/
		void sendmessage();

		static size_t writehtml (uint8_t* ptr, size_t size, size_t number, void *stream);
};
UserData *UserData::current = new UserData;
int UserData::httpAns;
void UserData::sendmessage(){}
UserData::UserData()
{
	coinNum = 100;
	memset (item, 0, sizeof (item) );
	memset (itemSelect, 0, sizeof (itemSelect) );
}
UserData::UserData(int id){
	this->userid = id;
}
void UserData::fetchExtraData()
{
	memset(roomlist,0 ,sizeof(roomlist));
	for(int i=0; i<5; i++){
		roomlist[i]=i+1;
	}
}
void UserData::fetchBasicData()
{
	sprintf (this->server, "59.66.132.177");
	sprintf (this->username, "ROOT");
	this->userid = 1;
	this->face = 1;
	this->rank = 19;
	this->coinNum = 999;
	this->emotion = 3;
}
void UserData::checkName()
{
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80], writeData[80], url[80];

	if (curl)
		{
			sprintf (url, "http://%s:8080/Server/check.jsp", server);
			CCLog ("%s!", url);
			curl_easy_setopt (curl, CURLOPT_URL, url);
			curl_easy_setopt (curl, CURLOPT_POST, true);
			sprintf (postField, "username=%s", username);
			curl_easy_setopt (curl, CURLOPT_POSTFIELDS, postField);
			curl_easy_setopt (curl, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, writehtml); //处理的函数
			curl_easy_setopt (curl, CURLOPT_WRITEDATA, writeData); //处理的函数
			res = curl_easy_perform (curl);
		}

	if (res != 0)
		{
			httpAns = -404;
		}

	else
		userid = httpAns;

	curl_easy_cleanup (curl);
}
void UserData::login()
{
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80], writeData[80], url[80];

	if (curl)
		{
			sprintf (url, "http://%s:8080/Server/login.jsp", server);
			curl_easy_setopt (curl, CURLOPT_URL, url);
			curl_easy_setopt (curl, CURLOPT_POST, true);
			sprintf (postField, "username=%s&password=%s", username, passwd);
			curl_easy_setopt (curl, CURLOPT_POSTFIELDS, postField);
			curl_easy_setopt (curl, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, writehtml); //处理的函数
			curl_easy_setopt (curl, CURLOPT_WRITEDATA, writeData); //处理的函数
			res = curl_easy_perform (curl);
		}

	curl_easy_cleanup (curl);

	if (httpAns != -1 and httpAns != -404)
		{
			UserData::userid = httpAns;
			fetchBasicData();
			fetchExtraData();
		}
}
void UserData::regist()
{
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80], writeData[80], url[80];

	if (curl)
		{
			sprintf (url, "http://%s:8080/Server/regist.jsp", server);
			curl_easy_setopt (curl, CURLOPT_URL, url);
			curl_easy_setopt (curl, CURLOPT_POST, true);
			sprintf (postField, "username=%s&password=%s", username, passwd);
			curl_easy_setopt (curl, CURLOPT_POSTFIELDS, postField);
			curl_easy_setopt (curl, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, writehtml); //处理的函数
			curl_easy_setopt (curl, CURLOPT_WRITEDATA, writeData); //处理的函数
			res = curl_easy_perform (curl);
		}

	curl_easy_cleanup (curl);
}
size_t UserData::writehtml (uint8_t* ptr, size_t size, size_t number, void *stream)
{
	char ans[4];
	ans[0] = * (ptr + 12);
	ans[1] = * (ptr + 13);
	ans[2] = * (ptr + 14);
	ans[3] = * (ptr + 15);
	UserData::httpAns = atoi (ans);
	return size * number;
}
#endif
