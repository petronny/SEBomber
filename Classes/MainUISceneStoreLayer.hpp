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
	virtual void ccTouchesBegan(CCSet* touches, CCEvent* pEvent);
	virtual void ccTouchesMoved(CCSet* touches, CCEvent* pEvent);
	virtual void ccTouchesEnded(CCSet* touches, CCEvent* pEvent);
	virtual void ccTouchesCancelled(CCSet* touches, CCEvent* pEvent);
    virtual void registerWithTouchDispatcher();
    void isSelect();
    void noSelect();
    // a selector callback
    // implement the "static node()" method manually
    CREATE_FUNC(MainUISceneStoreLayer);
	CCSize size;
	CCSprite *ui_right, *menuItem;
	CCLayer *chooseLayer;
	CCMenu* pMenu;
	int doubleTouchCount, itemNum,n, value[10];
	float w,h;
};
// onserverField "init" you need to initialize your instance
#include "MainUISceneChooseLayer.hpp"
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
	this->setTouchEnabled(true);
	size = CCDirector::sharedDirector()->getWinSize();
	ui_right =(CCSprite*) MainUIScene::mainUIScene->getChildByTag(10)->getChildByTag(10);
	menuItem =(CCSprite*) MainUIScene::mainUIScene->getChildByTag(10)->getChildByTag(11);

	n=-1;
	itemNum=4;
	char *itemName[itemNum], *itemValue[itemNum];
	itemName[0]="南瓜头";  itemValue[0]="￥ 5"; value[0]=5;
	itemName[1]="彩色泡泡"; itemValue[1]="￥ 8"; value[1]=8;
	itemName[2]="无敌盾"; itemValue[2]="￥ 15"; value[2]=15;
	itemName[3]="极速鞋"; itemValue[3]="￥ 10"; value[3]=10;

	w=(size.width-ui_right->boundingBox().size.width)/3;
	h=w/8*5;
	for(int i=0; i<itemNum; i++)
	{
	    CCSprite *itemBackground=CCSprite::create("image/ui/itemBackground.png");
		itemBackground->setScaleX(w/itemBackground->getContentSize().width);
		itemBackground->setScaleY(h/itemBackground->getContentSize().height);
		itemBackground->setPosition(ccp(ui_right->boundingBox().size.width+(i%3)*w+w/2, size.height-menuItem->boundingBox().size.height-(i/3)*h-h/2));
		this->addChild(itemBackground);

		char itemPath[80];
		sprintf(itemPath, "image/store/item_%d.png", i);
		CCSprite *item=CCSprite::create(itemPath);
		item->setScaleX(h/item->getContentSize().width*1/2);
		item->setScaleY(h/item->getContentSize().height*1/2);
		item->setPosition(ccp(itemBackground->getPositionX()-4*h/10,itemBackground->getPositionY()));
		this->addChild(item,2,i);

		CCLabelTTF *name = CCLabelTTF::create(itemName[i], "fonts/FZKaTong-M19T.ttf", 19);
		name->setPositionX(itemBackground->getPositionX()+h/3);
		name->setPositionY(itemBackground->getPositionY()+h/4);
		name->setColor(ccYELLOW);
		this->addChild(name, 2);

		CCLabelTTF *value=CCLabelTTF::create(itemValue[i], "font/FZKaTong-M19T.ttf", 19);
		value->setPositionX(itemBackground->getPositionX()+h/3);
		value->setPositionY(itemBackground->getPositionY()-h/4);
		value->setColor(ccYELLOW);
		this->addChild(value,2);
	}
	doubleTouchCount=0;
	return true;
}
void MainUISceneStoreLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
	if(pTouches->count()==1){
		CCTouch *touch = dynamic_cast<CCTouch*>(pTouches->anyObject());
		CCPoint position=convertTouchToNodeSpace(touch);
		if(position.x-ui_right->boundingBox().size.width>0 && position.y+menuItem->boundingBox().size.height-size.height<0){
			n=(int)(position.x-ui_right->boundingBox().size.width)/w+int((size.height-menuItem->boundingBox().size.height-position.y)/h)*3;
			if(n<itemNum){
			    CCSprite *itemBackground=CCSprite::create("image/ui/itemSelected.png");
				itemBackground->setScaleX(w/itemBackground->getContentSize().width);
				itemBackground->setScaleY(h/itemBackground->getContentSize().height);
				itemBackground->setPosition(ccp(ui_right->boundingBox().size.width+(n%3)*w+w/2, size.height-menuItem->boundingBox().size.height-(n/3)*h-h/2));
				this->addChild(itemBackground,1,1111);
			}
		}
	}
}
void MainUISceneStoreLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent){
}
void MainUISceneStoreLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
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
	/*if(pTouches->count()==2){
		CCTouch* touch=dynamic_cast<CCTouch*>(*pTouches->begin());
		float y=ccpAdd(this->getPosition(),touch->getDelta()).y;
		if(x>0)x=0;if(y>0)y=0;
		if(x<size.width-mapBackgroundLayer->boundingBox().size.width)x=size.width-mapBackgroundLayer->boundingBox().size.width;
		if(y<size.height-mapBackgroundLayer->boundingBox().size.height)y=size.height-mapBackgroundLayer->boundingBox().size.height;
		this->setPosition(ccp(x,y));
		doubleTouchCount=2;
	}
	if(pTouches->count()==1 and doubleTouchCount==0)*/
}
void MainUISceneStoreLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
	if(pTouches->count()==1 and doubleTouchCount==0 and n!=-1){
		this->setTouchEnabled(false);
		chooseLayer=MainUISceneChooseLayer::create();
		MainUIScene::mainUIScene->addChild(chooseLayer,4);

		CCSprite *blackboard = CCSprite::create("image/ui/black_blank.png");
		//blackboard->setScale(0);
		//CCScaleTo *scaleBlackboard=CCScaleTo::create(0.5, size.width/2/blackboard->getContentSize().width, size.width*1.2/2/blackboard->getContentSize().height);
	//	blackboard->runAction(CCEaseExponentialOut::create(scaleBlackboard));
		blackboard->setScaleX(size.width/2/blackboard->getContentSize().width);
		blackboard->setScaleY(size.width*1.2/2/blackboard->getContentSize().height);
		blackboard->setPosition(ccp(size.width/2, size.height/2));
		chooseLayer->addChild(blackboard,0,1);

		char itemSelect[80];
		sprintf(itemSelect, "image/store/item_%d.png", n);
		CCSprite* selectedItem = CCSprite::create(itemSelect);
		selectedItem->setScale(2.0);
		selectedItem->setPosition(ccp(size.width/2,size.height/2+blackboard->boundingBox().size.height/5));
		chooseLayer->addChild(selectedItem,1);

		CCLabelTTF *message = CCLabelTTF::create("确定购买", "fonts/FZKaTong-M19T.ttf", 28);
		message->setPosition(ccp(size.width/2, size.height/3));
		message->setColor(ccYELLOW);
		chooseLayer->addChild(message, 1);

		CCLabelTTF *numLabel = CCLabelTTF::create("x 1", "fonts/FZKaTong-M19T.ttf", 28);
		numLabel->setPosition(ccp(size.width/2, size.height/2));
		numLabel->setColor(ccYELLOW);
		chooseLayer->addChild(numLabel,1);

		pMenu=CCMenu::create();
		pMenu->setPosition( CCPointZero );
		chooseLayer->addChild(pMenu,2);
		CCLabelTTF *isLabel = CCLabelTTF::create("是", "fonts/FZKaTong-M19T.ttf", 30);
		//isSelected->setPosition(ccp(size.width/2-blackboard->boundingBox().size.width/4, size.height/5));
		isLabel->setColor(ccYELLOW);
		CCMenuItemLabel *isItem=CCMenuItemLabel::create(isLabel,this,menu_selector(MainUISceneStoreLayer::isSelect));
		isItem->setPosition(ccp(size.width/2-blackboard->boundingBox().size.width/4, size.height/6));
		pMenu->addChild(isItem);

		CCLabelTTF *noLabel = CCLabelTTF::create("否", "fonts/FZKaTong-M19T.ttf", 30);
		//noSelected->setPosition(ccp(size.width/2+blackboard->boundingBox().size.width/4, size.height/5));
		noLabel->setColor(ccYELLOW);
		CCMenuItemLabel *noItem=CCMenuItemLabel::create(noLabel,this,menu_selector(MainUISceneStoreLayer::noSelect));
		noItem->setPosition(ccp(size.width/2+blackboard->boundingBox().size.width/4, size.height/6));
		pMenu->addChild(noItem);
	}
}
void MainUISceneStoreLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
    CCLayer::registerWithTouchDispatcher();
}
void MainUISceneStoreLayer::noSelect()
{
	MainUIScene::mainUIScene->removeChild(chooseLayer, true);
	this->removeChildByTag(1111, true);
	this->setTouchEnabled(true);
}
void MainUISceneStoreLayer::isSelect()
{
	UserData::item[n]++;
	UserData::magicBubbleNum-=value[n];
	MainUIScene::mainUIScene->removeChild(chooseLayer, true);
	this->removeChildByTag(1111, true);
	this->setTouchEnabled(true);
}
#endif
