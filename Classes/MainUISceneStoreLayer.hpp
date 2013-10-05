#ifndef __MAINUI_SCENE_STORE_LAYER__
#define __MAINUI_SCENE_STORE_LAYER__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
class MainUISceneStoreLayer : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // a selector callback
    // implement the "static node()" method manually
    CREATE_FUNC(MainUISceneStoreLayer);
	CCSize size;
};
// onserverField "init" you need to initialize your instance
bool MainUISceneStoreLayer::init()
{
	if (!CCLayer::init()){
		return false;
	}
	//目标：双指上下滑动可以翻滚
	//对每个物品显示一个背景格子，样子和价格
	//对可以重复购买的物品提供批量购买
	//单次购买的物品如果已购买显示禁用样式
	//如果出现无法支付显示对应信息
	//购买时提供确认购买的信息，可以使用一个新的层来完成提示信息
	size = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF *implentmenting=CCLabelTTF::create("Store施工中","fonts/FZKaTong-M19T.ttf",25);
	implentmenting->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(implentmenting);
	return true;
}
#endif
