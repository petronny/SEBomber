#ifndef __MAINUI_SCENE_MULTIPLAYER_LAYER__
#define __MAINUI_SCENE_MULTIPLAYER_LAYER__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "UserData.hpp"
USING_NS_CC;
using namespace CocosDenshion;
/**
@brief
*/
class MainUISceneMultiplayerLayer : public CCLayer
{
	public:
		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	/**
	@brief 初始化函数
	*/
		virtual bool init();  //
		//  //
		/**
		@brief 触摸响应相关函数
		*/
		virtual void ccTouchesBegan (CCSet* touches, CCEvent* pEvent);
		/**
		@brief
		*/
		virtual void ccTouchesMoved (CCSet* touches, CCEvent* pEvent);
		/**
		@brief
		*/
		virtual void ccTouchesEnded (CCSet* touches, CCEvent* pEvent);
		/**
		@brief
		*/
		virtual void ccTouchesCancelled (CCSet* touches, CCEvent* pEvent);
		/**
		@brief
		*/
		virtual void registerWithTouchDispatcher();
		/**
		@brief //参数，房间号
		*/
		void houseShow (int number);
		/**
		@brief 改变自己的角色
		*/
		void changeCharactor();//
		/**
		@brief 玩家准备
		*/
		void ready();//
		/**
		@brief 离开房间
		*/
		void leave();//
		/**
		@brief 用来显示第number号房间信息，例如某玩家加入
		*/
		void Show (); //
		/**
		@brief 对话框确定选项
		*/
		void characterSelect(CCObject*);//
		void groupSelect();
		/**
		@brief implement the "static node()" method manually
		*/
		// a selector callback
		//
		CREATE_FUNC (MainUISceneMultiplayerLayer);
		/**
		@brief
		*/
		CCSize size;
		/**
		@brief
		*/
		CCSprite *ui_right, *menuItem;
		/**
		@brief
		*/
		float w, h;
		/**
		@brief
		*/
		CCMenu *pMenu, *pMenu2;

		CCMenuItemImage *characterItem;
		int beforePosition;
		int userid[8];
};
// onserverField "init" you need to initialize your instance
bool MainUISceneMultiplayerLayer::init()
{

	if (!CCLayer::init() )
		{
			return false;
		}
	//this->setTouchEnabled (true);
	size = CCDirector::sharedDirector()->getWinSize();
	memset(userid, 0, sizeof(userid));
	ui_right = CCSprite::create ("image/ui/ui_right.png");
	ui_right->setScale (size.height / ui_right->getContentSize().height);
	menuItem = CCSprite::create ("image/ui/button_normal.png");
	menuItem->setScaleY (size.height / 8 / menuItem->getContentSize().height);

	w = (size.width-ui_right->boundingBox().size.width - 15)/4;
	h = (size.height-menuItem->boundingBox().size.height)/2-5;

	pMenu = CCMenu::create();
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu,1);
	pMenu2 = CCMenu::create();
	pMenu2->setPosition(CCPointZero);
	this->addChild(pMenu2,1);
	for(int i=0; i<8; i++){
		characterItem = CCMenuItemImage::create ("image/ui/itemBackground.png", "image/ui/itemSelected.png", this, menu_selector(MainUISceneMultiplayerLayer::characterSelect));
		characterItem->setScaleX(w/characterItem->getContentSize().width);
		characterItem->setScaleY(h/characterItem->getContentSize().height*4/5);
		characterItem->setPositionX(ui_right->boundingBox().size.width+(5+w)*(i%4)+w/2);
		characterItem->setPositionY(size.height - menuItem->boundingBox().size.height-(h+5)*(i/4)-h*2/5);
		pMenu->addChild(characterItem,0,i);

		CCLabelTTF *groupLabel = CCLabelTTF::create ("队\t\t伍", "fonts/FZKaTong-M19T.ttf", 32);
		//logoutLabel->setColor (ccYELLOW);
		CCMenuItemLabel *groupItem = CCMenuItemLabel::create (groupLabel, this, menu_selector (MainUISceneMultiplayerLayer::groupSelect) );
		groupItem->setPosition (ccp (ui_right->boundingBox().size.width+(5+w)*(i%4)+w/2, size.height - menuItem->boundingBox().size.height-(h+5)*(i/4)-h*2/5-h/2) );
		pMenu2->addChild (groupItem, 0, i);


	}
	beforePosition=-1;
	schedule(schedule_selector(MainUISceneMultiplayerLayer::Show),2.0f);
	return true;
}
void MainUISceneMultiplayerLayer::ccTouchesBegan (CCSet* touches, CCEvent* pEvent)
{
}
void MainUISceneMultiplayerLayer::ccTouchesMoved (CCSet* touches, CCEvent* pEvent)
{
}
void MainUISceneMultiplayerLayer::ccTouchesEnded (CCSet* touches, CCEvent* pEvent)
{
}
void MainUISceneMultiplayerLayer::ccTouchesCancelled (CCSet* touches, CCEvent* pEvent)
{
}
void MainUISceneMultiplayerLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate (this, 0);
	CCLayer::registerWithTouchDispatcher();
}
void MainUISceneMultiplayerLayer::houseShow (int number)
{
}
void MainUISceneMultiplayerLayer::changeCharactor()
{
}
void MainUISceneMultiplayerLayer::ready()
{
}
void MainUISceneMultiplayerLayer::leave()
{
}
void MainUISceneMultiplayerLayer::Show ()
{
	UserData::current->fetchRoomData();
	for(int i=0; i<8; i++){
		if(UserData::current->roomlist[i]>0){
			if(userid[i]!=UserData::current->roomlist[i]){
				userid[i]=UserData::current->roomlist[i];
				UserData* user = new UserData(UserData::current->roomlist[i]);
				sprintf(user->server, "%s", UserData::current->server);
				user->fetchBasicData();
				char facePath[40];
				sprintf (facePath, "image/face/face%d.png", user->face);
				CCSprite*face = CCSprite::create(facePath);
				if(this->getChildByTag(i)!=NULL){
					this->removeChildByTag(i);
					this->removeChildByTag(100+i);
					this->removeChildByTag(1000+i);
					this->removeChildByTag(10000+i);
				}
				face->setPositionX(pMenu->getChildByTag(i)->getPosition().x);
				face->setPositionY(pMenu->getChildByTag(i)->getPosition().y-pMenu->getChildByTag(i)->boundingBox().size.height/5);
				this->addChild(face, 2, i);

				CCLabelTTF *nameLabel = CCLabelTTF::create (user->username, "fonts/FZKaTong-M19T.ttf", 25);
				nameLabel->setPositionX(pMenu->getChildByTag(i)->getPosition().x);
				nameLabel->setPositionY(pMenu->getChildByTag(i)->getPosition().y+pMenu->getChildByTag(i)->boundingBox().size.height/6);
				this->addChild(nameLabel, 2, 100+i);
				delete user;
			}
		}
		else{
			if(this->getChildByTag(i)!=NULL){
				this->removeChildByTag(i);
			}
		}
	}
}
void MainUISceneMultiplayerLayer::characterSelect(CCObject* pSender){
	CCMenuItem *m = (CCMenuItem*)(pSender);
	if(this->getChildByTag(m->getTag())== NULL){
		/*char facePath[40];
		sprintf (facePath, "image/face/face%d.png", UserData::current->face);
		CCSprite*face = CCSprite::create(facePath);
		face->setPosition(m->getPosition());
		this->addChild(face,2, m->getTag());
		if(beforePosition!=-1){
			this->removeChildByTag(beforePosition);
		}
		beforePosition=m->getTag();*/
		//UserData::current->sendRoomData(m->getTag());
	}
}
void MainUISceneMultiplayerLayer::groupSelect(){

}
#endif
