#ifndef __MESSAGE_LAYER__
#define __MESSAGE_LAYER__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
class MessageLayer : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // a selector callback
    // implement the "static node()" method manually
    CREATE_FUNC(MessageLayer);
	CCSize size;
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent);
    virtual void registerWithTouchDispatcher();
};
// onserverField "init" you need to initialize your instance
bool MessageLayer::init()
{
	if (!CCLayer::init()){
		return false;
	}
	size = CCDirector::sharedDirector()->getWinSize();
	SimpleAudioEngine::sharedEngine()->preloadEffect("audio/ef_13.ogg");
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_13.ogg");
	CCSprite *messageBackground=CCSprite::create("image/ui/black_blank.png");
	messageBackground->setScaleX(size.width/messageBackground->getContentSize().width);
	messageBackground->setScaleY(size.height/messageBackground->getContentSize().height);
	messageBackground->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(messageBackground,0);
	this->setTouchEnabled(true);
	CCFadeIn *fadein=CCFadeIn::create(1);
	this->runAction(fadein);
	return true;
}
bool MessageLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	this->setTouchEnabled(false);
	this->removeFromParentAndCleanup(true);
	return true;
}
void MessageLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
}
void MessageLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
}
void MessageLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
}
void MessageLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCLayer::registerWithTouchDispatcher();
}
#endif
