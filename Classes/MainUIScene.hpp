#ifndef __MAINUI_SCENE__
#define __MAINUI_SCENE__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
class MainUIScene : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static CCScene* scene();
    // a selector callback
    void logout();
    // implement the "static node()" method manually
    CREATE_FUNC(MainUIScene);
	CCSize size;
	static CCScene *mainUIScene;
};
#include "TitleScene.hpp"
#include "ShareData.hpp"
CCScene *MainUIScene::mainUIScene;
CCScene* MainUIScene::scene()
{
	// 'scene' is an autorelease object
	mainUIScene = CCScene::create();
	// 'layer' is an autorelease object
	MainUIScene *layer = MainUIScene::create();
	// add layer as a child to scene
	mainUIScene->addChild(layer,0);
	// return the scene
	return mainUIScene;
}
// on "init" you need to initialize your instance
bool MainUIScene::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	size = CCDirector::sharedDirector()->getWinSize();
	CCMenu* pMenu = CCMenu::create();
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu,2);
	CCSprite *background=CCSprite::create("image/ui/bg.jpg");
	background->setPosition( ccp(size.width/2, size.height/2) );
	background->setScaleX(size.width/background->getContentSize().width);
	background->setScaleY(size.height/background->getContentSize().height);
	this->addChild(background,0);
	CCSprite *ui_right=CCSprite::create("image/ui/ui_right.png");
	ui_right->setScale(size.height/ui_right->getContentSize().height);
	ui_right->setPosition(ccp(ui_right->boundingBox().size.width/2,size.height/2));
	this->addChild(ui_right,1);
	CCLabelTTF *logoutLabel=CCLabelTTF::create("登\t出","fonts/FZKaTong-M19T.ttf",25);
	logoutLabel->setColor(ccYELLOW);
	CCMenuItemLabel *logoutItem=CCMenuItemLabel::create(logoutLabel,this,menu_selector(MainUIScene::logout));
	logoutItem->setPosition(ccp(ui_right->boundingBox().size.width/64*33,size.height/64*59));
	pMenu->addChild(logoutItem);
	return true;
}
void MainUIScene::logout(){
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	ShareData::userid=-1;
	CCScene *pScene =TitleScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFlipY::create(0.5f, pScene));
}
#endif
