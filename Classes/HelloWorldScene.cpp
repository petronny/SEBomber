#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene2.h"
using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//	you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCMenuItemImage *pCloseItem = CCMenuItemImage::create("c2.png","c9.png",this,menu_selector(HelloWorld::menuCloseCallback));
	pCloseItem->setScale(size.height/5/pCloseItem->boundingBox().size.height);
	pCloseItem->setPosition( ccp(size.width/2,pCloseItem->boundingBox().size.height/2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label
	CCSprite* title=CCSprite::create("003c.png");
	title->setScale(size.width/2/title->boundingBox().size.width);
	title->setPosition(ccp(size.width / 2, size.height - title->boundingBox().size.height/2) );
	// add the label as a child to this layer
	this->addChild(title, 1);

	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("bg.jpg");
	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width/2, size.height/2) );
	pSprite->setScaleX(size.width/pSprite->boundingBox().size.width);
	pSprite->setScaleY(size.height/pSprite->boundingBox().size.height);
	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);
	
	text1 = CCTextFieldTTF::textFieldWithPlaceHolder("点此输入用户名", "fonts/FZZYHandelGotD.ttf", 30);
	CCLabelTTF * underline1=CCLabelTTF::create("______________", "fonts/FZZYHandelGotD.ttf", 30);
	text1->setPosition(ccp(size.width / 2, size.height/2));
	underline1->setPosition(ccp(size.width / 2, size.height/2));
	text1->setColor(ccWHITE);
	underline1->setColor(ccBLACK);
	this->addChild(text1,2);
	this->addChild(underline1);
	text1->setDelegate(this);
	CCMenuItem* tapItem1 = CCMenuItemFont::create("              ",this,menu_selector(HelloWorld::textFieldPressed1));
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
	tapItem2 = CCMenuItemFont::create("              ",this,menu_selector(HelloWorld::textFieldPressed2));
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
	CCMenuItem* tapItem3 = CCMenuItemFont::create("              ",this,menu_selector(HelloWorld::textFieldPressed3));
	tapItem3->setPosition(ccp(size.width / 2, size.height/3*2));
	pMenu->addChild(tapItem3, 1);

	return true;
}
void HelloWorld::textFieldPressed1(cocos2d::CCObject *sender)
{
	text1->attachWithIME();
}
void HelloWorld::textFieldPressed3(cocos2d::CCObject *sender)
{
	text3->attachWithIME();
}
void HelloWorld::textFieldPressed2(cocos2d::CCObject *sender)
{
	text2->attachWithIME();
	text2->setVisible(false);
	tapItem2->setString("********");
}
bool HelloWorld::onTextFieldAttachWithIME(cocos2d::CCTextFieldTTF *sender)
{
//	this->setPosition(ccp(0, 100));
	return false;
}
bool HelloWorld::onTextFieldDetachWithIME(cocos2d::CCTextFieldTTF *sender)
{
//	this->setPosition(ccp(0, 0));
	return false;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCScene *pScene = HelloWorld2::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFlipY::create(0.5f, pScene));
	
/*	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
*/}
