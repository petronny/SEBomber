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
	//目标：双指上下滑动可以翻滚列表
	//一开始禁用okbutton
	//首先显示房间列表
	//点击一个房间显示房间内的页面，激活okbutton
	//房间内的页面包含8个格，显示每个玩家的头像，等级，名称，以及打算使用的角色
	//点击自己那个格子里的角色可以更换角色，弹出一个新的层显示4种角色，以及4个角色各自赢过多少场
	//不同位置的玩家使用的角色色调需要有变化
	//okbutton实际上相当于准备按钮，点下okbutton后显示准备
	//点击okbutton后不能再切换到其他页面,除非从房间中退出否则不能切换到其他页面
	//可以使用一个新的层来处理提示信息
	if (!CCLayer::init()){
		return false;
	}
	size = CCDirector::sharedDirector()->getWinSize();
	CCSprite *messageBackground=CCSprite::create("image/ui/black_blank.png");
	messageBackground->setScaleX(size.width/messageBackground->getContentSize().width);
	messageBackground->setScaleY(size.height/messageBackground->getContentSize().height);
	messageBackground->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(messageBackground,0);
	CCLabelTTF *implentmenting=CCLabelTTF::create("Multiplayer施工中","fonts/FZKaTong-M19T.ttf",25);
	implentmenting->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(implentmenting);
	return true;
}
#endif
