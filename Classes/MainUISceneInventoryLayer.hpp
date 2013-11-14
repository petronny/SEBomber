#ifndef __MAINUI_SCENE_INVENTORY_LAYER__
#define __MAINUI_SCENE_INVENTORY_LAYER__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MainUISceneStoreLayer.hpp"
#include "ItemData.h"
#include "MainUISceneChooseLayer.hpp"
USING_NS_CC;
using namespace CocosDenshion;
class MainUISceneInventoryLayer : public CCLayer
{
public:

    virtual bool init();
    virtual void ccTouchesBegan(CCSet* touches, CCEvent* pEvent);
    virtual void ccTouchesMoved(CCSet* touches, CCEvent* pEvent);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* pEvent);
    virtual void ccTouchesCancelled(CCSet* touches, CCEvent* pEvent);
    virtual void registerWithTouchDispatcher();
    void isSelect();
    void noSelect();

    CREATE_FUNC(MainUISceneInventoryLayer);
    CCSize size;
    CCSprite *ui_right, *menuItem;
    CCLayer *chooseLayer;
    CCMenu* pMenu;
    int itemNum,n, myNum,doubleTouchCount, selectItemNumber[MAX_NUM_ITEM];
    float w, h;
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
	this->setTouchEnabled(true);
	size = CCDirector::sharedDirector()->getWinSize();
	ui_right =(CCSprite*) MainUIScene::mainUIScene->getChildByTag(10)->getChildByTag(10);
	menuItem =(CCSprite*) MainUIScene::mainUIScene->getChildByTag(10)->getChildByTag(11);

	w=(size.width-ui_right->boundingBox().size.width)/3;
	h=w/8*5;
	itemNum=MainUISceneStoreLayer::itemNum;
	n=-1;


	myNum=0;
	for(int i=0; i<itemNum; i++){
		if(UserData::current->item[i]>0){

		    CCSprite *itemBackground=CCSprite::create("image/ui/itemBackground.png");
			itemBackground->setScaleX(w/itemBackground->getContentSize().width);
			itemBackground->setScaleY(h/itemBackground->getContentSize().height);
			itemBackground->setPosition(ccp(ui_right->boundingBox().size.width+(myNum%3)*w+w/2, size.height-menuItem->boundingBox().size.height-(myNum/3)*h-h/2));
			this->addChild(itemBackground,0,1000+myNum);

			char itemPath[80];
			sprintf(itemPath, "image/store/item_%d.png", i);
			CCSprite *item=CCSprite::create(itemPath);
			item->setScaleX(h/item->getContentSize().width*1/2);
			item->setScaleY(h/item->getContentSize().height*1/2);
			item->setPosition(ccp(itemBackground->getPositionX()-4*h/10,itemBackground->getPositionY()));
			this->addChild(item,2,myNum);

			CCLabelTTF *name = CCLabelTTF::create(itemName[i], "fonts/FZKaTong-M19T.ttf", 25);
			name->setPositionX(itemBackground->getPositionX()+h/3);
			name->setPositionY(itemBackground->getPositionY()+h/4);
			name->setColor(ccYELLOW);
			this->addChild(name, 2);

			char num[5];
			sprintf(num, "x %d", UserData::current->item[i]);
			CCLabelTTF *value=CCLabelTTF::create(num, "font/FZKaTong-M19T.ttf", 25);
			value->setPositionX(itemBackground->getPositionX()+h/3);
			value->setPositionY(itemBackground->getPositionY()-h/4);
			value->setColor(ccYELLOW);
			this->addChild(value,2);

			if(UserData::current->itemSelect[i]){
				CCSprite *ok=CCSprite::create("image/ui/common_gate.png");
				ok->setScaleX(h*2/5/ok->getContentSize().width);
				ok->setScaleY(h*2/5/ok->getContentSize().height);
				ok->setPositionX(itemBackground->getPositionX()-w/3);
				ok->setPositionY(itemBackground->getPositionY()-h/3);
				this->addChild(ok,2,10000+myNum);
			}

			selectItemNumber[myNum]=i;
			myNum++;
		}
	}
	return true;
}
void MainUISceneInventoryLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
	if(pTouches->count()==1){
		CCTouch *touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
		CCPoint position=convertTouchToNodeSpace(touch);
		if(position.x-ui_right->boundingBox().size.width>0 && position.y+menuItem->boundingBox().size.height-size.height<0){
			n=(int)(position.x-ui_right->boundingBox().size.width)/w+int((size.height-menuItem->boundingBox().size.height-position.y)/h)*3;
			if(n<myNum and this->getChildByTag(1111)==NULL){
			    CCSprite *itemBackground=CCSprite::create("image/ui/itemSelected.png");
				itemBackground->setScaleX(w/itemBackground->getContentSize().width);
				itemBackground->setScaleY(h/itemBackground->getContentSize().height);
				itemBackground->setPosition(ccp(ui_right->boundingBox().size.width+(n%3)*w+w/2, size.height-menuItem->boundingBox().size.height-(n/3)*h-h/2));
				this->addChild(itemBackground,1,1111);
			}
		}
	}
}
void MainUISceneInventoryLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent){
}
void MainUISceneInventoryLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
	if(pTouches->count()==2){
		if(this->getChildByTag(1111)!=NULL){
			this->removeChildByTag(1111, true);
		}
			if(h*((myNum+2)/3)+menuItem->boundingBox().size.height > size.height){
				CCTouch* touch=dynamic_cast<CCTouch*>(*pTouches->begin());
				float y=ccpAdd(this->getPosition(),touch->getDelta()).y;
				if(y>(h*((myNum+2)/3)+menuItem->boundingBox().size.height)-size.height) y=(h*((myNum+2)/3)+menuItem->boundingBox().size.height)-size.height;
				if(y<0) y=0;
				this->setPositionY(y);
			}
		doubleTouchCount=2;
	}
	if(pTouches->count()==1 and doubleTouchCount==0){
		CCTouch *touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
		CCPoint position=convertTouchToNodeSpace(touch);
		if(position.x-ui_right->boundingBox().size.width>0 && position.y+menuItem->boundingBox().size.height-size.height<0){
			n=(int)(position.x-ui_right->boundingBox().size.width)/w+int((size.height-menuItem->boundingBox().size.height-position.y)/h)*3;
			if(n<itemNum){
				this->getChildByTag(1111)->setPosition(ccp(ui_right->boundingBox().size.width+(n%3)*w+w/2, size.height-menuItem->boundingBox().size.height-(n/3)*h-h/2));
			}
			else{
				if(this->getChildByTag(1111)!=NULL)
					this->removeChildByTag(1111,true);
			}
		}
		else{
			if(this->getChildByTag(1111)!=NULL)
				this->removeChildByTag(1111,true);
		}
	}
}
void MainUISceneInventoryLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
	if(pTouches->count()==1 and doubleTouchCount==0 and n!=-1 and n<myNum){
		this->setTouchEnabled(false);
		chooseLayer=MainUISceneChooseLayer::create();
		MainUIScene::mainUIScene->addChild(chooseLayer,4);

		CCSprite *blackboard = CCSprite::create("image/ui/black_blank.png");
		blackboard->setScaleX(size.width/2/blackboard->getContentSize().width);
		blackboard->setScaleY(size.height*9/10/blackboard->getContentSize().height);
		blackboard->setPosition(ccp(size.width/2, size.height/2));
		chooseLayer->addChild(blackboard,0,1);

		CCSprite *blackboard2 = CCSprite::create("image/ui/black_blank.png");
		blackboard2->setScaleX(size.width/2/blackboard->getContentSize().width);
		blackboard2->setScaleY(size.height*9/20/blackboard->getContentSize().height);
		blackboard2->setPosition(ccp(size.width/2, size.height*3/4));
		chooseLayer->addChild(blackboard,1);

		char itemSelect[80];
		sprintf(itemSelect, "image/store/item_%d.png", selectItemNumber[n]);
		CCSprite* selectedItem = CCSprite::create(itemSelect);
		selectedItem->setScale(blackboard->boundingBox().size.height/3/selectedItem->getContentSize().height);
		selectedItem->setPosition(ccp(size.width/2,size.height/2+blackboard->boundingBox().size.height/5));
		chooseLayer->addChild(selectedItem,2);

		CCLabelTTF *message;
		if(UserData::current->itemSelect[selectItemNumber[n]])
			message = CCLabelTTF::create("是否脱下装备？", "fonts/FZKaTong-M19T.ttf", 30);
		else
			message = CCLabelTTF::create("是否穿戴装备？", "fonts/FZKaTong-M19T.ttf", 30);
		message->setPosition(ccp(size.width/2, size.height/3));
		message->setColor(ccYELLOW);
		chooseLayer->addChild(message, 2);

		CCLabelTTF *numLabel = CCLabelTTF::create("x 1", "fonts/FZKaTong-M19T.ttf", 30);
		numLabel->setPosition(ccp(size.width/2, size.height/2));
		numLabel->setColor(ccYELLOW);
		chooseLayer->addChild(numLabel,2);

		pMenu=CCMenu::create();
		pMenu->setPosition( CCPointZero );
		chooseLayer->addChild(pMenu,4);
		CCLabelTTF *isLabel = CCLabelTTF::create("是", "fonts/FZKaTong-M19T.ttf", 32);
		//isSelected->setPosition(ccp(size.width/2-blackboard->boundingBox().size.width/4, size.height/5));
		isLabel->setColor(ccYELLOW);
		CCMenuItemLabel *isItem=CCMenuItemLabel::create(isLabel,this,menu_selector(MainUISceneInventoryLayer::isSelect));
		isItem->setPosition(ccp(size.width/2-blackboard->boundingBox().size.width/4, size.height/6));
		pMenu->addChild(isItem);

		CCLabelTTF *noLabel = CCLabelTTF::create("否", "fonts/FZKaTong-M19T.ttf", 32);
		//noSelected->setPosition(ccp(size.width/2+blackboard->boundingBox().size.width/4, size.height/5));
		noLabel->setColor(ccYELLOW);
		CCMenuItemLabel *noItem=CCMenuItemLabel::create(noLabel,this,menu_selector(MainUISceneInventoryLayer::noSelect));
		noItem->setPosition(ccp(size.width/2+blackboard->boundingBox().size.width/4, size.height/6));
		pMenu->addChild(noItem);
	}
	else if(doubleTouchCount!=0){
		doubleTouchCount--;
		if(this->getChildByTag(1111)!=NULL){
			this->removeChildByTag(1111, true);
		}
	}
}
void MainUISceneInventoryLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
    CCLayer::registerWithTouchDispatcher();
}
void MainUISceneInventoryLayer::noSelect()
{
	MainUIScene::mainUIScene->removeChild(chooseLayer, true);
	this->removeChildByTag(1111, true);
	this->setTouchEnabled(true);
}
void MainUISceneInventoryLayer::isSelect()
{
	if(UserData::current->itemSelect[selectItemNumber[n]]){
		UserData::current->itemSelect[selectItemNumber[n]]=false;
		this->removeChildByTag(10000+n);
	}
	else{
		UserData::current->itemSelect[selectItemNumber[n]]=true;
		CCSprite *ok=CCSprite::create("image/ui/common_gate.png");
		ok->setScaleX(h*2/5/ok->getContentSize().width);
		ok->setScaleY(h*2/5/ok->getContentSize().height);
		ok->setPositionX(this->getChildByTag(1000+n)->getPositionX()-w/3);
		ok->setPositionY(this->getChildByTag(1000+n)->getPositionY()-h/3);
		this->addChild(ok,2,10000+n);

	}
	MainUIScene::mainUIScene->removeChild(chooseLayer, true);

	this->removeChildByTag(1111, true);
	this->setTouchEnabled(true);
}
#endif
