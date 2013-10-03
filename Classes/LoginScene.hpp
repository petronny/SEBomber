#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__
typedef unsigned int size_t;
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameScene.hpp"
#include "curl/curl.h"
#include "stdio.h"
#include "stdlib.h"
#include "ShareClass.hpp"
using namespace cocos2d;
using namespace CocosDenshion;
class LoginScene : public CCLayer ,public CCTextFieldDelegate
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static CCScene* scene();
    
    // a selector callback
    void loginButtonClicked(CCObject* pSender);
    void registButtonClicked(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(LoginScene);
    static size_t writehtml(uint8_t* ptr,size_t size,size_t number,void *stream);
    void textFieldPressed1(CCObject *sender);   
    void textFieldPressed2(CCObject *sender);   
    void textFieldPressed3(CCObject *sender);
    void checkNameExist();
    void login();
    void regist();
    CCTextFieldTTF *text1;
    CCTextFieldTTF *text2;
    CCTextFieldTTF *text3;
    CCMenuItemFont* tapItem2;
    CCLabelTTF * message;
    bool onTextFieldAttachWithIME(CCTextFieldTTF *sender);
    bool onTextFieldDetachWithIME(CCTextFieldTTF *sender);
    static int httpAns;
    void menuCloseCallback(CCObject* pSender);
};
int LoginScene::httpAns;

CCScene* LoginScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	LoginScene *layer = LoginScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("audio/bg_0.ogg");
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("audio/bg_0.ogg",true);
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
	SimpleAudioEngine::sharedEngine()->preloadEffect("audio/ef_0.ogg");
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(LoginScene::menuCloseCallback));

	pCloseItem->setPosition(ccp(size.width - pCloseItem->getContentSize().width/2 ,pCloseItem->getContentSize().height/2));

	CCMenuItemImage *loginButton = CCMenuItemImage::create("image/c8.png","image/c3.png",this,menu_selector(LoginScene::loginButtonClicked));
	loginButton->setScale(size.width/6/loginButton->boundingBox().size.width);
	loginButton->setPosition( ccp(size.width/3,size.height/6));
	CCLabelTTF *loginLabel=CCLabelTTF::create("登录","fonts/FZZYHandelGotD.ttf",25);
	loginLabel->setPosition( ccp(size.width/3,size.height/6));
	loginLabel->setColor(ccYELLOW);
	this->addChild(loginLabel,2);
	CCMenuItemImage *registButton = CCMenuItemImage::create("image/c8.png","image/c3.png",this,menu_selector(LoginScene::registButtonClicked));
	registButton->setScale(size.width/6/registButton->boundingBox().size.width);
	registButton->setPosition( ccp(size.width/3*2,size.height/6));
	CCLabelTTF *registLabel=CCLabelTTF::create("注册","fonts/FZZYHandelGotD.ttf",25);
	registLabel->setPosition( ccp(size.width/3*2,size.height/6));
	registLabel->setColor(ccYELLOW);
	this->addChild(registLabel,2);
	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem,loginButton,registButton, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	CCSprite* title=CCSprite::create("image/003c.png");
	CCAnimation *animation = CCAnimation::create();
	animation->setDelayPerUnit(0.25f);
	animation->addSpriteFrameWithFileName("image/003c-r.png");
	animation->addSpriteFrameWithFileName("image/003c-g.png");
	animation->addSpriteFrameWithFileName("image/003c-b.png");
	animation->addSpriteFrameWithFileName("image/003c.png");
	CCAnimate *animate = CCAnimate::create(animation);
	title->runAction(CCRepeatForever::create(animate));
	title->setScale(size.width/2/title->boundingBox().size.width);
	title->setPosition(ccp(size.width / 2, size.height - title->boundingBox().size.height/2) );
	// add the label as a child to this layer
	this->addChild(title, 1);

	// add "LoginScene" splash screen"
	CCSprite* background = CCSprite::create("image/bg.jpg");
	// position the sprite on the center of the screen
	background->setPosition( ccp(size.width/2, size.height/2) );
	background->setScaleX(size.width/background->boundingBox().size.width);
	background->setScaleY(size.height/background->boundingBox().size.height);
	// add the sprite as a child to this layer
	this->addChild(background, 0);
	
	text1 = CCTextFieldTTF::textFieldWithPlaceHolder("点此输入用户名", "fonts/FZZYHandelGotD.ttf", 25);
	CCLabelTTF * underline1=CCLabelTTF::create("______________", "fonts/FZZYHandelGotD.ttf", 25);
	text1->setPosition(ccp(size.width / 2, size.height/2));
	underline1->setPosition(ccp(size.width / 2, size.height/2));
	text1->setColor(ccWHITE);
	underline1->setColor(ccBLACK);
	this->addChild(text1,2);
	this->addChild(underline1);
	text1->setDelegate(this);
	CCMenuItem* tapItem1 = CCMenuItemFont::create("              ",this,menu_selector(LoginScene::textFieldPressed1));
	tapItem1->setPosition(ccp(size.width / 2, size.height/2));
	pMenu->addChild(tapItem1, 1);

	text2 = CCTextFieldTTF::textFieldWithPlaceHolder("点此输入密码", "fonts/FZZYHandelGotD.ttf", 25);
	CCLabelTTF * underline2=CCLabelTTF::create("______________", "fonts/FZZYHandelGotD.ttf", 25);
	text2->setPosition(ccp(size.width / 2, size.height/3));
	underline2->setPosition(ccp(size.width / 2, size.height /3));
	text2->setColor(ccWHITE);
	underline2->setColor(ccBLACK);
	this->addChild(text2,2);
	this->addChild(underline2);
	text2->setDelegate(this);
	tapItem2 = CCMenuItemFont::create("              ",this,menu_selector(LoginScene::textFieldPressed2));
	tapItem2->setPosition(ccp(size.width / 2, size.height/3));
	pMenu->addChild(tapItem2, 1);

	text3 = CCTextFieldTTF::textFieldWithPlaceHolder("", "fonts/FZZYHandelGotD.ttf", 25);
	text3->setString("192.168.1.122");
	CCLabelTTF * underline3=CCLabelTTF::create("______________", "fonts/FZZYHandelGotD.ttf", 25);
	text3->setPosition(ccp(size.width / 2, size.height/3*2));
	underline3->setPosition(ccp(size.width / 2, size.height /3*2));
	text3->setColor(ccWHITE);
	underline3->setColor(ccBLACK);
	this->addChild(text3,2);
	this->addChild(underline3);
	text3->setDelegate(this);
	CCMenuItem* tapItem3 = CCMenuItemFont::create("              ",this,menu_selector(LoginScene::textFieldPressed3));
	tapItem3->setPosition(ccp(size.width / 2, size.height/3*2));
	pMenu->addChild(tapItem3, 1);

    message = CCLabelTTF::create("请登录或注册", "fonts/FZZYHandelGotD.ttf", 25);
    message->setPosition(ccp(size.width / 2, size.height /4*3));
    message->setColor(ccYELLOW);
    this->addChild(message, 1);

	return true;
}
void LoginScene::textFieldPressed1(CCObject *sender)
{
	text1->attachWithIME();
}
void LoginScene::textFieldPressed3(CCObject *sender)
{
	text3->attachWithIME();
}
void LoginScene::textFieldPressed2(CCObject *sender)
{
	text2->attachWithIME();
	text2->setVisible(false);
	tapItem2->setString("********");
}
bool LoginScene::onTextFieldAttachWithIME(CCTextFieldTTF *sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_0.ogg");
	return false;
}
bool LoginScene::onTextFieldDetachWithIME(CCTextFieldTTF *sender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_0.ogg");
	return false;
}
void LoginScene::checkNameExist(){
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80],writeData[80],url[80];
	if (curl){
		sprintf(url,"http://%s:8080/Server/check.jsp",text3->getString());
		CCLog("%s!",url);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		sprintf(postField,"username=%s",text1->getString());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField);
       curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
       curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writehtml); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
	if(res!=0){
		message->setString("连接失败");
		httpAns=-404;
	}
	else
	    ShareClass::userid=httpAns;
    curl_easy_cleanup(curl);
}
void LoginScene::regist(){
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80],writeData[80],url[80];
	if (curl){
		sprintf(url,"http://%s:8080/Server/regist.jsp",text3->getString());
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		sprintf(postField,"username=%s&password=%s",text1->getString(),text2->getString());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField);
       curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
       curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writehtml); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
    curl_easy_cleanup(curl);
}
void LoginScene::login(){
	CURL *curl;
	CURLcode res;
	char buffer[10];
	curl = curl_easy_init();
	char postField[80],writeData[80],url[80];
	if (curl){
		sprintf(url,"http://%s:8080/Server/login.jsp",text3->getString());
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		sprintf(postField,"username=%s&password=%s",text1->getString(),text2->getString());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField);
       curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
       curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writehtml); //处理的函数
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,writeData); //处理的函数
		res = curl_easy_perform(curl);
	}
    curl_easy_cleanup(curl);
    if(httpAns==-1 or httpAns==-404){
    	message->setString("密码错误");
    }
    else{
    	strcpy(ShareClass::username,text1->getString());
    	ShareClass::userid=httpAns;
    	CCScene *pScene = GameScene::scene();
    	CCDirector::sharedDirector()->replaceScene(CCTransitionFlipY::create(0.5f, pScene));
    }
}
void LoginScene::loginButtonClicked(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_0.ogg");
	checkNameExist();
	if(httpAns!=-404){
		if(ShareClass::userid==-1)
			message->setString("用户名不存在");
		else
			login();
	}
}
void LoginScene::registButtonClicked(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_0.ogg");
	checkNameExist();
	if(httpAns!=-404){
		if(ShareClass::userid!=-1)
			message->setString("该用户名已存在");
		else{
			regist();
			login();
		}
	}
}
size_t LoginScene::writehtml(uint8_t* ptr,size_t size,size_t number,void *stream){
	char ans[4];
	ans[0]=*(ptr+12);	ans[1]=*(ptr+13);	ans[2]=*(ptr+14);	ans[3]=*(ptr+15);
	httpAns=atoi(ans);
	return size*number;
}

void LoginScene::menuCloseCallback(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_0.ogg");
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
#endif // __LoginScene_SCENE_H__
