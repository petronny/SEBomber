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
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
										"CloseNormal.png",
										"CloseSelected.png",
										this,
										menu_selector(HelloWorld::menuCloseCallback) );
	pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label
	CCLabelTTF* pLabel = CCLabelTTF::create("SE泡泡堂", "fonts/FZZYHandelGotD.ttf", 34);

	// ask director the window size
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	// position the label on the center of the screen
	pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("NPJH-50614.jpg");

	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width/2, size.height/2) );

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);
	
	text1 = CCTextFieldTTF::textFieldWithPlaceHolder("点此输入用户名", "fonts/FZZYHandelGotD.ttf", 20);
	text1->setPosition(ccp(size.width / 2, size.height / 2 - 40));
	this->addChild(text1);
	text1->setDelegate(this);

	CCMenuItem* tapItem1 = CCMenuItemFont::create("       ",this,menu_selector(HelloWorld::textFieldPressed1));
	tapItem1->setPosition(ccp(size.width / 2, size.height / 2 - 40));
	pMenu->addChild(tapItem1, 1);

	text2 = CCTextFieldTTF::textFieldWithPlaceHolder("点此输入密码", "fonts/FZZYHandelGotD.ttf", 20);
	text2->setPosition(ccp(size.width / 2, size.height / 2 ));
	this->addChild(text2);
	text2->setDelegate(this);
	
	CCMenuItem* tapItem2 = CCMenuItemFont::create("        ",this,menu_selector(HelloWorld::textFieldPressed2));
	tapItem2->setPosition(ccp(size.width / 2, size.height / 2));
	pMenu->addChild(tapItem2, 1);
	return true;
}
void HelloWorld::textFieldPressed1(cocos2d::CCObject *sender)
{
	text1->attachWithIME();
}
void HelloWorld::textFieldPressed2(cocos2d::CCObject *sender)
{
	text2->attachWithIME();
}
bool HelloWorld::onTextFieldAttachWithIME(cocos2d::CCTextFieldTTF *sender)
{
	this->setPosition(ccp(0, 100));
	return false;
}
bool HelloWorld::onTextFieldDetachWithIME(cocos2d::CCTextFieldTTF *sender)
{
	this->setPosition(ccp(0, 0));
	return false;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCScene *pScene = HelloWorld2::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFlipY::create(2, pScene));
//	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//	exit(0);
#endif
}
