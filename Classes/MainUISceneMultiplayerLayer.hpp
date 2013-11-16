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
    virtual bool init();  //初始化函数
    //  //触摸响应相关函数
    virtual void ccTouchesBegan(CCSet* touches, CCEvent* pEvent);
    virtual void ccTouchesMoved(CCSet* touches, CCEvent* pEvent);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* pEvent);
    virtual void ccTouchesCancelled(CCSet* touches, CCEvent* pEvent);
    virtual void registerWithTouchDispatcher();
    void houseShow(int number);//参数，房间号
    void changeCharactor();//改变自己的角色
    void ready();// 玩家准备
    void leave();//离开房间
    void infoShow(int number);//用来显示第number号房间信息，例如某玩家加入
    void isSelect();//对话框确定选项
    void noSelect();//对话框取消选项
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
	CCLabelTTF *implentmenting=CCLabelTTF::create("Multiplayer施工中","fonts/FZKaTong-M19T.ttf",25);
	implentmenting->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(implentmenting);
	return true;
}
void MainUISceneMultiplayerLayer::ccTouchesBegan(CCSet* touches, CCEvent* pEvent){

}
void MainUISceneMultiplayerLayer::ccTouchesMoved(CCSet* touches, CCEvent* pEvent){

}
void MainUISceneMultiplayerLayer::ccTouchesEnded(CCSet* touches, CCEvent* pEvent){

}
void MainUISceneMultiplayerLayer::ccTouchesCancelled(CCSet* touches, CCEvent* pEvent){

}
void MainUISceneMultiplayerLayer::registerWithTouchDispatcher(){

}
void MainUISceneMultiplayerLayer::houseShow(int number){

}
void MainUISceneMultiplayerLayer::changeCharactor(){

}
void MainUISceneMultiplayerLayer::ready(){

}
void MainUISceneMultiplayerLayer::leave(){

}
void MainUISceneMultiplayerLayer::infoShow(int number){

}
#endif
