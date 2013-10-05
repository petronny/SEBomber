#ifndef __GAME_SCENE_MESSAGE_LAYER__
#define __GAME_SCENE_MESSAGE_LAYER__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
class GameSceneMessageLayer : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // a selector callback
    // implement the "static node()" method manually
    CREATE_FUNC(GameSceneMessageLayer);
	CCSize size;
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent);
    virtual void registerWithTouchDispatcher();
};
// onserverField "init" you need to initialize your instance
bool GameSceneMessageLayer::init()
{
	if (!CCLayer::init()){
		return false;
	}
	//三指下滑移回此层
	//提供对话支持
	size = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF *implentmenting=CCLabelTTF::create("Message施工中","fonts/FZKaTong-M19T.ttf",25);
	implentmenting->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(implentmenting);
	CCSprite *background=CCSprite::create("image/ui/black_blank.png");
	background->setScaleX(size.width/background->getContentSize().width);
	background->setScaleY(size.height/background->getContentSize().height);
	background->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(background,0);
	this->setTouchEnabled(true);
	return true;
}
bool GameSceneMessageLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	this->setTouchEnabled(false);
	this->removeFromParentAndCleanup(true);
	return true;
}
void GameSceneMessageLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
}
void GameSceneMessageLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
}
void GameSceneMessageLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
}
void GameSceneMessageLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCLayer::registerWithTouchDispatcher();
}
#endif
