#ifndef __MAINUI_SCENE_INVENTORY_LAYER__
#define __MAINUI_SCENE_INVENTORY_LAYER__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
class MainUISceneInventoryLayer : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // a selector callback
    // implement the "static node()" method manually
    CREATE_FUNC(MainUISceneInventoryLayer);
	CCSize size;
};
// onserverField "init" you need to initialize your instance
bool MainUISceneInventoryLayer::init()
{
	//目标：双指上下滑动可以翻滚
	//对每个物品显示一个背景格子，样子
	//对可以重叠的物品显示数量
	//点击一个道具即表示使用（例如头像，特效等等），右下角显示对勾，该道具背景变色
	if (!CCLayer::init()){
		return false;
	}
	size = CCDirector::sharedDirector()->getWinSize();
	CCSprite *background=CCSprite::create("image/ui/black_blank.png");
	background->setScaleX(size.width/background->getContentSize().width);
	background->setScaleY(size.height/background->getContentSize().height);
	background->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(background,0);
	CCLabelTTF *implentmenting=CCLabelTTF::create("Inventory施工中","fonts/FZKaTong-M19T.ttf",25);
	implentmenting->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(implentmenting);
	return true;
}
#endif
