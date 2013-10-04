#ifndef __LOGIN_LAYER__
#define __LOGIN_LAYER__
typedef unsigned int size_t;
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "curl/curl.h"
USING_NS_CC;
class LoginLayer : public CCLayer ,public CCTextFieldDelegate
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // a selector callback
    void loginButtonClicked(CCObject* pSender);
    void registButtonClicked(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(LoginLayer);
    static size_t writehtml(uint8_t* ptr,size_t size,size_t number,void *stream);
    void usernameFieldPressed(CCObject *sender);
    void passwdFieldPressed(CCObject *sender);
    void serverFieldPressed(CCObject *sender);
    void checkNameExist();
    void login();
    void regist();
    void fetchData();
    CCTextFieldTTF *usernameField,*passwdField,*serverField;
    CCMenuItemFont* passwdTapItem;
    CCLabelTTF * message;
	CCSize size;
    bool onTextFieldAttachWithIME(CCTextFieldTTF *sender);
    bool onTextFieldDetachWithIME(CCTextFieldTTF *sender);
    static int httpAns;
    void menuCloseCallback(CCObject* pSender);
    void showMessage(const char* st);
};
#include "MainUIScene.hpp"
#include "ShareData.hpp"
#include "MessageLayer.hpp"
int LoginLayer::httpAns;
// onserverField "init" you need to initialize your instance
bool LoginLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	size = CCDirector::sharedDirector()->getWinSize();
	SimpleAudioEngine::sharedEngine()->preloadEffect("audio/ef_0.ogg");
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create("image/ui/CloseNormal.png","image/ui/CloseSelected.png",this,menu_selector(LoginLayer::menuCloseCallback));
    pCloseItem->setPosition(ccp(size.width - pCloseItem->getContentSize().width/2 ,pCloseItem->getContentSize().height/2));
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu,1);

	CCSprite* menuBackground=CCSprite::create("image/ui/mainmenu.png");
	menuBackground->setScale(size.height/24*14/menuBackground->getContentSize().height);
	menuBackground->setPosition(ccp(size.width/2,menuBackground->boundingBox().size.height/2+size.height/64*7));
	this->addChild(menuBackground,0);

	CCLabelTTF *serverLabel=CCLabelTTF::create("请输入服务器地址","fonts/FZKaTong-M19T.ttf",25);
	serverLabel->setPosition(ccp(size.width/2,menuBackground->boundingBox().size.height/32*27+size.height/64*7));
	this->addChild(serverLabel,1);
	serverField = CCTextFieldTTF::textFieldWithPlaceHolder("", "fonts/FZKaTong-M19T.ttf", 25);
	serverField->setString("192.168.1.122");
	serverField->setPosition(ccp(size.width/2, menuBackground->boundingBox().size.height/8*6+size.height/64*7));
	serverField->setDelegate(this);
	this->addChild(serverField,1);
	CCMenuItem* serverTapItem = CCMenuItemFont::create("              ",this,menu_selector(LoginLayer::serverFieldPressed));
	serverTapItem->setPosition(ccp(size.width/2, menuBackground->boundingBox().size.height/8*6+size.height/64*7));
	pMenu->addChild(serverTapItem, 1);

	CCLabelTTF* usernameLabel=CCLabelTTF::create("请输入用户名","fonts/FZKaTong-M19T.ttf",25);
	usernameLabel->setPosition(ccp(size.width/2, menuBackground->boundingBox().size.height/16*9+size.height/64*7));
	this->addChild(usernameLabel,1);
	usernameField=CCTextFieldTTF::textFieldWithPlaceHolder("", "fonts/FZKaTong-M19T.ttf", 25);
	usernameField->setPosition(ccp(size.width/2, menuBackground->boundingBox().size.height/16*7+size.height/64*7));
	usernameField->setDelegate(this);
	this->addChild(usernameField,1);
	CCMenuItem* usernameTapItem = CCMenuItemFont::create("              ",this,menu_selector(LoginLayer::usernameFieldPressed));
	usernameTapItem->setPosition(ccp(size.width/2, menuBackground->boundingBox().size.height/16*7+size.height/64*7));
	pMenu->addChild(usernameTapItem, 1);

	CCLabelTTF *passwdLabel=CCLabelTTF::create("请输入密码","fonts/FZKaTong-M19T.ttf",25);
	passwdLabel->setPosition(ccp(size.width/2, menuBackground->boundingBox().size.height/8*2+size.height/64*7));
	this->addChild(passwdLabel,1);
	passwdField=CCTextFieldTTF::textFieldWithPlaceHolder("", "fonts/FZKaTong-M19T.ttf", 25);
	passwdField->setPosition(ccp(size.width/2, menuBackground->boundingBox().size.height/32*5+size.height/64*7));
	passwdField->setDelegate(this);
	this->addChild(passwdField,1);
	passwdTapItem = CCMenuItemFont::create("              ",this,menu_selector(LoginLayer::passwdFieldPressed));
	passwdTapItem->setPosition(ccp(size.width/2, menuBackground->boundingBox().size.height/32*5+size.height/64*7));
	pMenu->addChild(passwdTapItem, 1);

	CCMenuItemImage *loginButton = CCMenuItemImage::create("image/ui/c8.png","image/ui/c3.png",this,menu_selector(LoginLayer::loginButtonClicked));
	loginButton->setScaleY(size.height/64*7/loginButton->getContentSize().height);
	loginButton->setScaleX(menuBackground->boundingBox().size.width/2/loginButton->getContentSize().width);
	loginButton->setPosition( ccp(size.width/2-menuBackground->boundingBox().size.width/4,loginButton->boundingBox().size.height/2));
	pMenu->addChild(loginButton,2);
	CCLabelTTF *loginLabel=CCLabelTTF::create("登录","fonts/FZKaTong-M19T.ttf",25);
	loginLabel->setPosition( ccp(size.width/2-menuBackground->boundingBox().size.width/4,loginButton->boundingBox().size.height/2));
	loginLabel->setColor(ccYELLOW);
	this->addChild(loginLabel,3);

	CCMenuItemImage *registButton = CCMenuItemImage::create("image/ui/c8.png","image/ui/c3.png",this,menu_selector(LoginLayer::registButtonClicked));
	registButton->setScaleY(size.height/64*7/registButton->getContentSize().height);
	registButton->setScaleX(menuBackground->boundingBox().size.width/2/registButton->getContentSize().width);
	registButton->setPosition( ccp(size.width/2+menuBackground->boundingBox().size.width/4,registButton->boundingBox().size.height/2));
	pMenu->addChild(registButton,2);
	CCLabelTTF *registLabel=CCLabelTTF::create("注册","fonts/FZKaTong-M19T.ttf",25);
	registLabel->setPosition( ccp(size.width/2+menuBackground->boundingBox().size.width/4,registButton->boundingBox().size.height/2));
	registLabel->setColor(ccYELLOW);
	this->addChild(registLabel,3);

    return true;
}
void LoginLayer::usernameFieldPressed(CCObject *sender)
{
	usernameField->attachWithIME();
}
void LoginLayer::serverFieldPressed(CCObject *sender)
{
	serverField->attachWithIME();
}
void LoginLayer::passwdFieldPressed(CCObject *sender)
{
	passwdField->attachWithIME();
	passwdField->setVisible(false);
	passwdTapItem->setString("********");
}
bool LoginLayer::onTextFieldAttachWithIME(CCTextFieldTTF *sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_0.ogg");
	return false;
}
bool LoginLayer::onTextFieldDetachWithIME(CCTextFieldTTF *sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_0.ogg");
	return false;
}
void LoginLayer::checkNameExist(){
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80],writeData[80],url[80];
	if (curl){
		sprintf(url,"http://%s:8080/Server/check.jsp",serverField->getString());
		CCLog("%s!",url);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		sprintf(postField,"username=%s",usernameField->getString());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField);
       curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
       curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writehtml); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
	if(res!=0){
		showMessage("连接失败");
		httpAns=-404;
	}
	else
	    ShareData::userid=httpAns;
    curl_easy_cleanup(curl);
}
void LoginLayer::regist(){
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80],writeData[80],url[80];
	if (curl){
		sprintf(url,"http://%s:8080/Server/regist.jsp",serverField->getString());
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		sprintf(postField,"username=%s&password=%s",usernameField->getString(),passwdField->getString());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField);
       curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
       curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writehtml); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
    curl_easy_cleanup(curl);
}
void LoginLayer::login(){
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80],writeData[80],url[80];
	if (curl){
		sprintf(url,"http://%s:8080/Server/login.jsp",serverField->getString());
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		sprintf(postField,"username=%s&password=%s",usernameField->getString(),passwdField->getString());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField);
       curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
       curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writehtml); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
    curl_easy_cleanup(curl);
    if(httpAns==-1 or httpAns==-404){
    	showMessage("密码错误");
    }
    else{
    	strcpy(ShareData::username,usernameField->getString());
    	ShareData::userid=httpAns;
    	fetchData();
    	CCScene *pScene = MainUIScene::scene();
    	CCDirector::sharedDirector()->replaceScene(CCTransitionFlipY::create(0.5f, pScene));
    }
}
void LoginLayer::loginButtonClicked(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_0.ogg");
	checkNameExist();
	if(httpAns!=-404){
		if(ShareData::userid==-1)
			showMessage("用户名不存在");
		else
			login();
	}
}
void LoginLayer::registButtonClicked(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_0.ogg");
	checkNameExist();
	if(httpAns!=-404){
		if(ShareData::userid!=-1)
			showMessage("该用户名已存在");
		else{
			regist();
			login();
		}
	}
}
size_t LoginLayer::writehtml(uint8_t* ptr,size_t size,size_t number,void *stream){
	char ans[4];
	ans[0]=*(ptr+12);	ans[1]=*(ptr+13);	ans[2]=*(ptr+14);	ans[3]=*(ptr+15);
	httpAns=atoi(ans);
	return size*number;
}
void LoginLayer::showMessage(const char* st){
	CCLayer* messageLayer=MessageLayer::create();
	CCLabelTTF *message=CCLabelTTF::create(st,"fonts/FZKaTong-M19T.ttf",60);
	message->setPosition(ccp(size.width/2,size.height/2));
	messageLayer->addChild(message,1);
	this->getParent()->addChild(messageLayer,20);
}//
void LoginLayer::menuCloseCallback(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_0.ogg");
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void LoginLayer::fetchData(){
	ShareData::face=1;
}
#endif // __LoginLayer_LAYER__
