#ifndef __MAINUI_SCENE_CHOOSE_LAYER__
#define __MAINUI_SCENE_CHOOSE_LAYER__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
class MainUISceneChooseLayer : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void ccTouchesBegan(CCSet* touches, CCEvent* pEvent);
    virtual void ccTouchesMoved(CCSet* touches, CCEvent* pEvent);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* pEvent);
    virtual void ccTouchesCancelled(CCSet* touches, CCEvent* pEvent);
    virtual void registerWithTouchDispatcher();
    // a selector callback
    // implement the "static node()" method manually
    CREATE_FUNC(MainUISceneChooseLayer);
    int isYes, isNo;
	CCSize size;
};
// onserverField "init" you need to initialize your instance
bool MainUISceneChooseLayer::init()
{
	if (!CCLayer::init()){
		return false;
	}
	//this->setTouchEnabled(true);
	size=CCDirector::sharedDirector()->getWinSize();
	isYes=0; isNo=0;
	return true;
}
void MainUISceneChooseLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
}
void MainUISceneChooseLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent){
}
void MainUISceneChooseLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
	/*if(pTouches->count()==1){
		CCTouch *touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
		CCPoint position=convertTouchToNodeSpace(touch);
		if(ccpDistance(position,this->getChildByTag(2000)->getPosition())<size.height/8){
			CCLabelTTF* is=(CCLabelTTF*)this->getChildByTag(2000);
			is->setColor(ccGREEN);
			is->setPosition(ccp(size.width/2-this->getChildByTag(1)->boundingBox().size.width/4, size.height/5));
			this->addChild(is,2,3000);
			isYes=1;
			isNo=0;
		}
		else if(isYes==1 and isNo==0){
			isYes=0;
			this->removeChildByTag(3000);
		}
		else if(ccpDistance(position,this->getChildByTag(2001)->getPosition())<size.height/8){
			CCLabelTTF* no=(CCLabelTTF*)this->getChildByTag(2001);
			no->setColor(ccGREEN);
			no->setPosition(ccp(size.width/2+this->getChildByTag(1)->boundingBox().size.width/4, size.height/5));
			this->addChild(no,2,3001);
			isNo=1;
			isYes=0;
		}
		else if(isNo==1 and isYes==0){
			isNo=0;
			this->removeChildByTag(3001);
		}
	}*/
}
void MainUISceneChooseLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
/*	if(pTouches->count()==1){
		CCTouch *touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
		CCPoint position=convertTouchToNodeSpace(touch);
		if(isYes==1){
			this->removeFromParentAndCleanup(true);
		}
		else if(isNo==1){
			this->removeFromParentAndCleanup(true);
		}
	}*/
}
void MainUISceneChooseLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
    CCLayer::registerWithTouchDispatcher();
}
#endif
