#ifndef __MAINUI_SCENE_BUDDYLIST_LAYER__
#define __MAINUI_SCENE_BUDDYLIST_LAYER__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MainUISceneChooseLayer.hpp"
#include "ItemData.h"

USING_NS_CC;
using namespace CocosDenshion;
class MainUISceneBuddyListLayer : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();//初始化函数
    //触摸响应相关函数
    virtual void ccTouchesBegan(CCSet* touches, CCEvent* pEvent);
    virtual void ccTouchesMoved(CCSet* touches, CCEvent* pEvent);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* pEvent);
    virtual void ccTouchesCancelled(CCSet* touches, CCEvent* pEvent);
    virtual void registerWithTouchDispatcher();


    void deletefriend();//删除好友，完成好友列表的更新
    void giftItem(); //赠送好友道具，显示玩家物品所有东西
    void chooseGift(); //选择物品，进行赠送，修改玩家道具相应属性
    void isSelect();  //对话框确定选项
    void noSelect(); //对话框取消选项
    // a selector callback
    // implement the "static node()" method manually
    CREATE_FUNC(MainUISceneBuddyListLayer);
	CCSize size;
	int selectNumber;
};
// onserverField "init" you need to initialize your instance
bool MainUISceneBuddyListLayer::init()
{
	//目标：双指上下滑动可以翻滚好友列表
	//点击某一个好友显示是否删除
	//好友要显示是否在线，离线时头像为灰色，显示好友等级，名称，头像，头像可能会有来自商店的特效道具
	//在好友头像上显示表情
	if (!CCLayer::init()){
		return false;
	}
	size = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF *implentmenting=CCLabelTTF::create("BuddyList施工中","fonts/FZKaTong-M19T.ttf",25);
	implentmenting->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(implentmenting);
	return true;
}
void MainUISceneBuddyListLayer::ccTouchesBegan(CCSet* touches, CCEvent* pEvent){

}
void MainUISceneBuddyListLayer::ccTouchesMoved(CCSet* touches, CCEvent* pEvent){

}
void MainUISceneBuddyListLayer::ccTouchesEnded(CCSet* touches, CCEvent* pEvent){

}
void MainUISceneBuddyListLayer::ccTouchesCancelled(CCSet* touches, CCEvent* pEvent){

}
void MainUISceneBuddyListLayer::registerWithTouchDispatcher(){

}
void MainUISceneBuddyListLayer::deletefriend(){

}
void MainUISceneBuddyListLayer::giftItem(){

}
void MainUISceneBuddyListLayer::chooseGift(){

}
#endif
