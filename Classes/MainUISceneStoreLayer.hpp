#ifndef __MAINUI_SCENE_STORE_LAYER__
#define __MAINUI_SCENE_STORE_LAYER__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ItemData.h"
USING_NS_CC;

using namespace CocosDenshion;
/**
@brief 当玩家选择道具商店按钮后，会进入道具商店界面。该界面下显示当前服务器上线的道具。在手机界面上以每行三个显示，每个块里显示的信息有道具图片，道具名称、道具价格。另外，在该界面上，开启了手机屏幕的触摸响应，支持单点触控和多点触控。玩家双指滑动可以滚动界面，类似滚动条的功能。玩家单点某个道具，可以进行购买，玩家相应的金钱也会减少。

*/
class MainUISceneStoreLayer : public CCLayer
{
	public:
	/**
	@brief //初始化函数
	*/
		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init();

		//
		/**
		@brief //触摸响应相关函数
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
		@brief 对话框确定选项
		*/
		void isSelect();//
		/**
		@brief 对话框取消选项
		*/
		void noSelect();//
		/**
		@brief
		*/
		// a selector callback
		// implement the "static node()" method manually
		CREATE_FUNC (MainUISceneStoreLayer);
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
		CCLayer *chooseLayer;
		/**
		@brief
		*/
		CCMenu* pMenu;
		/**
		@brief
		*/
		int doubleTouchCount, n;
		/**
		@brief
		*/
		static int itemNum;
		/**
		@brief
		*/

		float w, h;
};
// onserverField "init" you need to initialize your instance
#include "MainUISceneChooseLayer.hpp"
int MainUISceneStoreLayer::itemNum;
bool MainUISceneStoreLayer::init()
{
	if (!CCLayer::init() )
		{
			return false;
		}

	//目标：双指上下滑动可以翻滚
	//对每个物品显示一个背景格子，样子和价格
	//对可以重复购买的物品提供批量购买
	//单次购买的物品如果已购买显示禁用样式
	//如果出现无法支付显示对应信息
	//购买时提供确认购买的信息，可以使用一个新的层来完成提示信息
	this->setTouchEnabled (true);
	size = CCDirector::sharedDirector()->getWinSize();
	ui_right = (CCSprite*) MainUIScene::mainUIScene->getChildByTag (10)->getChildByTag (10);
	menuItem = (CCSprite*) MainUIScene::mainUIScene->getChildByTag (10)->getChildByTag (11);
	n = -1;
	itemNum = 10;
	w = (size.width - ui_right->boundingBox().size.width) / 3;
	h = w / 8 * 5;

	for (int i = 0; i < itemNum; i++)
		{
			CCSprite *itemBackground = CCSprite::create ("image/ui/itemBackground.png");
			itemBackground->setScaleX (w / itemBackground->getContentSize().width);
			itemBackground->setScaleY (h / itemBackground->getContentSize().height);
			itemBackground->setPosition (ccp (ui_right->boundingBox().size.width + (i % 3) *w + w / 2, size.height - menuItem->boundingBox().size.height - (i / 3) *h - h / 2) );
			this->addChild (itemBackground);
			char itemPath[80];
			sprintf (itemPath, "image/store/item_%d.png", i);
			CCSprite *item = CCSprite::create (itemPath);
			item->setScaleX (h / item->getContentSize().width * 1 / 2);
			item->setScaleY (h / item->getContentSize().height * 1 / 2);
			item->setPosition (ccp (itemBackground->getPositionX() - 4 * h / 10, itemBackground->getPositionY() ) );
			this->addChild (item, 2, i);
			CCLabelTTF *name = CCLabelTTF::create (itemName[i], "fonts/FZKaTong-M19T.ttf", 25);
			name->setPositionX (itemBackground->getPositionX() + h / 3);
			name->setPositionY (itemBackground->getPositionY() + h / 4);
			name->setColor (ccYELLOW);
			this->addChild (name, 2);
			char itemValue[10];
			sprintf (itemValue, "￥ %d", value[i]);
			CCLabelTTF *value = CCLabelTTF::create (itemValue, "font/FZKaTong-M19T.ttf", 25);
			value->setPositionX (itemBackground->getPositionX() + h / 3);
			value->setPositionY (itemBackground->getPositionY() - h / 4);
			value->setColor (ccYELLOW);
			this->addChild (value, 2);
		}

	doubleTouchCount = 0;
	return true;
}
void MainUISceneStoreLayer::ccTouchesBegan (CCSet *pTouches, CCEvent *pEvent)
{
	if (pTouches->count() == 1)
		{
			CCTouch *touch = dynamic_cast<CCTouch*> (pTouches->anyObject() );
			CCPoint position = convertTouchToNodeSpace (touch);

			if (position.x - ui_right->boundingBox().size.width > 0 && position.y + menuItem->boundingBox().size.height - size.height < 0)
				{
					n = (int) (position.x - ui_right->boundingBox().size.width) / w + int ( (size.height - menuItem->boundingBox().size.height - position.y) / h) * 3;

					if (n < itemNum and this->getChildByTag (1111) == NULL)
						{
							CCSprite *itemBackground = CCSprite::create ("image/ui/itemSelected.png");
							itemBackground->setScaleX (w / itemBackground->getContentSize().width);
							itemBackground->setScaleY (h / itemBackground->getContentSize().height);
							itemBackground->setPosition (ccp (ui_right->boundingBox().size.width + (n % 3) *w + w / 2, size.height - menuItem->boundingBox().size.height - (n / 3) *h - h / 2) );
							this->addChild (itemBackground, 1, 1111);
						}
				}
		}
}
void MainUISceneStoreLayer::ccTouchesCancelled (CCSet *pTouches, CCEvent *pEvent)
{
}
void MainUISceneStoreLayer::ccTouchesMoved (CCSet *pTouches, CCEvent *pEvent)
{
	if (pTouches->count() == 2)
		{
			if (this->getChildByTag (1111) != NULL)
				{
					this->removeChildByTag (1111, true);
				}

			if (h * ( (itemNum + 2) / 3) + menuItem->boundingBox().size.height > size.height)
				{
					CCTouch* touch = dynamic_cast<CCTouch*> (*pTouches->begin() );
					float y = ccpAdd (this->getPosition(), touch->getDelta() ).y;

					if (y > (h * ( (itemNum + 2) / 3) + menuItem->boundingBox().size.height) - size.height) y = (h * ( (itemNum + 2) / 3) + menuItem->boundingBox().size.height) - size.height;

					if (y < 0) y = 0;

					this->setPositionY (y);
				}

			doubleTouchCount = 2;
		}

	if (pTouches->count() == 1 and doubleTouchCount == 0)
		{
			CCTouch *touch = dynamic_cast<CCTouch*> (pTouches->anyObject() );
			CCPoint position = convertTouchToNodeSpace (touch);

			if (position.x - ui_right->boundingBox().size.width > 0 && position.y + menuItem->boundingBox().size.height - size.height < 0)
				{
					n = (int) (position.x - ui_right->boundingBox().size.width) / w + int ( (size.height - menuItem->boundingBox().size.height - position.y) / h) * 3;

					if (n < itemNum)
						{
							this->getChildByTag (1111)->setPosition (ccp (ui_right->boundingBox().size.width + (n % 3) *w + w / 2, size.height - menuItem->boundingBox().size.height - (n / 3) *h - h / 2) );
						}

					else
						{
							if (this->getChildByTag (1111) != NULL)
								this->removeChildByTag (1111, true);
						}
				}

			else
				{
					if (this->getChildByTag (1111) != NULL)
						this->removeChildByTag (1111, true);
				}
		}
}
void MainUISceneStoreLayer::ccTouchesEnded (CCSet *pTouches, CCEvent *pEvent)
{
	if (pTouches->count() == 1 and doubleTouchCount == 0 and n != -1 and n < itemNum)
		{
			this->setTouchEnabled (false);
			chooseLayer = MainUISceneChooseLayer::create();
			MainUIScene::mainUIScene->addChild (chooseLayer, 4);
			CCSprite *blackboard = CCSprite::create ("image/ui/black_blank.png");
			blackboard->setScaleX (size.width / 2 / blackboard->getContentSize().width);
			blackboard->setScaleY (size.height * 9 / 10 / blackboard->getContentSize().height);
			blackboard->setPosition (ccp (size.width / 2, size.height / 2) );
			chooseLayer->addChild (blackboard, 0, 1);
			CCSprite *blackboard2 = CCSprite::create ("image/ui/black_blank.png");
			blackboard2->setScaleX (size.width / 2 / blackboard->getContentSize().width);
			blackboard2->setScaleY (size.height * 9 / 20 / blackboard->getContentSize().height);
			blackboard2->setPosition (ccp (size.width / 2, size.height * 3 / 4) );
			chooseLayer->addChild (blackboard, 1);
			char itemSelect[80];
			sprintf (itemSelect, "image/store/item_%d.png", n);
			CCSprite* selectedItem = CCSprite::create (itemSelect);
			selectedItem->setScale (blackboard->boundingBox().size.height / 3 / selectedItem->getContentSize().height);
			selectedItem->setPosition (ccp (size.width / 2, size.height / 2 + blackboard->boundingBox().size.height / 5) );
			chooseLayer->addChild (selectedItem, 2);
			CCLabelTTF *message = CCLabelTTF::create ("确定购买？", "fonts/FZKaTong-M19T.ttf", 30);
			message->setPosition (ccp (size.width / 2, size.height / 3) );
			message->setColor (ccYELLOW);
			chooseLayer->addChild (message, 2);
			CCLabelTTF *numLabel = CCLabelTTF::create ("x 1", "fonts/FZKaTong-M19T.ttf", 30);
			numLabel->setPosition (ccp (size.width / 2, size.height / 2) );
			numLabel->setColor (ccYELLOW);
			chooseLayer->addChild (numLabel, 2);
			pMenu = CCMenu::create();
			pMenu->setPosition ( CCPointZero );
			chooseLayer->addChild (pMenu, 4);
			CCLabelTTF *isLabel = CCLabelTTF::create ("是", "fonts/FZKaTong-M19T.ttf", 32);
			//isSelected->setPosition(ccp(size.width/2-blackboard->boundingBox().size.width/4, size.height/5));
			isLabel->setColor (ccYELLOW);
			CCMenuItemLabel *isItem = CCMenuItemLabel::create (isLabel, this, menu_selector (MainUISceneStoreLayer::isSelect) );
			isItem->setPosition (ccp (size.width / 2 - blackboard->boundingBox().size.width / 4, size.height / 6) );
			pMenu->addChild (isItem);
			CCLabelTTF *noLabel = CCLabelTTF::create ("否", "fonts/FZKaTong-M19T.ttf", 32);
			//noSelected->setPosition(ccp(size.width/2+blackboard->boundingBox().size.width/4, size.height/5));
			noLabel->setColor (ccYELLOW);
			CCMenuItemLabel *noItem = CCMenuItemLabel::create (noLabel, this, menu_selector (MainUISceneStoreLayer::noSelect) );
			noItem->setPosition (ccp (size.width / 2 + blackboard->boundingBox().size.width / 4, size.height / 6) );
			pMenu->addChild (noItem);
		}

	else if (doubleTouchCount != 0)
		{
			doubleTouchCount--;

			if (this->getChildByTag (1111) != NULL)
				{
					this->removeChildByTag (1111, true);
				}
		}
}
void MainUISceneStoreLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate (this, 0);
	CCLayer::registerWithTouchDispatcher();
}
void MainUISceneStoreLayer::noSelect()
{
	MainUIScene::mainUIScene->removeChild (chooseLayer, true);
	this->removeChildByTag (1111, true);
	this->setTouchEnabled (true);
}
void MainUISceneStoreLayer::isSelect()
{
	UserData::current->item[n]++;
	UserData::current->coinNum -= value[n];
	MainUIScene::mainUIScene->removeChild (chooseLayer, true);
	( (MainUIScene *) MainUIScene::mainUIScene->getChildByTag (10) )->showCoinNum (UserData::current->coinNum);
	this->removeChildByTag (1111, true);
	this->setTouchEnabled (true);
}
#endif
