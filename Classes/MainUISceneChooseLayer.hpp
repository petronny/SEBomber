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
#endif
