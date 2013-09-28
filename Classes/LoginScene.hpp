#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameScene.hpp"
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
    
    void textFieldPressed1(CCObject *sender);   
    void textFieldPressed2(CCObject *sender);   
    void textFieldPressed3(CCObject *sender);
    CCTextFieldTTF *text1;
    CCTextFieldTTF *text2;
    CCTextFieldTTF *text3;
    CCMenuItemFont* tapItem2;
    CCLabelTTF * message;
    bool onTextFieldAttachWithIME(CCTextFieldTTF *sender);
    bool onTextFieldDetachWithIME(CCTextFieldTTF *sender);
    
};


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
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCMenuItemImage *loginButton = CCMenuItemImage::create("c8.png","c3.png",this,menu_selector(LoginScene::loginButtonClicked));
	loginButton->setScale(size.width/6/loginButton->boundingBox().size.width);
	loginButton->setPosition( ccp(size.width/3,size.height/6));
	CCLabelTTF *loginLabel=CCLabelTTF::create("登录","fonts/FZZYHandelGotD.ttf",30);
	loginLabel->setPosition( ccp(size.width/3,size.height/6));
	loginLabel->setColor(ccYELLOW);
	this->addChild(loginLabel,2);
	CCMenuItemImage *registButton = CCMenuItemImage::create("c8.png","c3.png",this,menu_selector(LoginScene::registButtonClicked));
	registButton->setScale(size.width/6/registButton->boundingBox().size.width);
	registButton->setPosition( ccp(size.width/3*2,size.height/6));
	CCLabelTTF *registLabel=CCLabelTTF::create("注册","fonts/FZZYHandelGotD.ttf",30);
	registLabel->setPosition( ccp(size.width/3*2,size.height/6));
	registLabel->setColor(ccYELLOW);
	this->addChild(registLabel,2);
	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(loginButton,registButton, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	CCSprite* title=CCSprite::create("003c.png");
	title->setScale(size.width/2/title->boundingBox().size.width);
	title->setPosition(ccp(size.width / 2, size.height - title->boundingBox().size.height/2) );
	// add the label as a child to this layer
	this->addChild(title, 1);

	// add "LoginScene" splash screen"
	CCSprite* background = CCSprite::create("bg.jpg");
	// position the sprite on the center of the screen
	background->setPosition( ccp(size.width/2, size.height/2) );
	background->setScaleX(size.width/background->boundingBox().size.width);
	background->setScaleY(size.height/background->boundingBox().size.height);
	// add the sprite as a child to this layer
	this->addChild(background, 0);
	
	text1 = CCTextFieldTTF::textFieldWithPlaceHolder("点此输入用户名", "fonts/FZZYHandelGotD.ttf", 30);
	CCLabelTTF * underline1=CCLabelTTF::create("______________", "fonts/FZZYHandelGotD.ttf", 30);
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

	text2 = CCTextFieldTTF::textFieldWithPlaceHolder("点此输入密码", "fonts/FZZYHandelGotD.ttf", 30);
	CCLabelTTF * underline2=CCLabelTTF::create("______________", "fonts/FZZYHandelGotD.ttf", 30);
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

	text3 = CCTextFieldTTF::textFieldWithPlaceHolder("点此输入IP地址", "fonts/FZZYHandelGotD.ttf", 30);
	CCLabelTTF * underline3=CCLabelTTF::create("______________", "fonts/FZZYHandelGotD.ttf", 30);
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

    message = CCLabelTTF::create("请登录或注册", "fonts/FZZYHandelGotD.ttf", 30);
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
//	this->setPosition(ccp(0, 100));
	return false;
}
bool LoginScene::onTextFieldDetachWithIME(CCTextFieldTTF *sender)
{
//	this->setPosition(ccp(0, 0));
	return false;
}

void LoginScene::loginButtonClicked(CCObject* pSender)
{
	CCScene *pScene = GameScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFlipY::create(0.5f, pScene));
	
/*	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
*/}
void LoginScene::registButtonClicked(CCObject* pSender)
{
}

#endif // __LoginScene_SCENE_H__
