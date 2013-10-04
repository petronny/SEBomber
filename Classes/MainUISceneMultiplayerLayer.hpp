#ifndef __MAINUI_SCENE_MULTIPLAYER_LAYER__
#define __MAINUI_SCENE_MULTIPLAYER_LAYER__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
class MainUISceneMultiplayerLayer : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // a selector callback
    // implement the "static node()" method manually
    CREATE_FUNC(MainUISceneMultiplayerLayer);
	CCSize size;
};
// onserverField "init" you need to initialize your instance
bool MainUISceneMultiplayerLayer::init()
{
	if (!CCLayer::init()){
		return false;
	}
	size = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF *implentmenting=CCLabelTTF::create("Multiplayer施工中","fonts/FZKaTong-M19T.ttf",25);
	implentmenting->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(implentmenting);
	return true;
}
#endif
