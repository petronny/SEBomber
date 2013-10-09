#ifndef __GAME_SCENE__
#define __GAME_SCENE__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GreenBird.hpp"
#include "math.h"
USING_NS_CC;
using namespace CocosDenshion;
class GameScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback    	map->setScale(MAX(size.height/map->getContentSize().height,size.width/map->getContentSize().width));

    void menuCloseCallback(CCObject* pSender);
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
    Hero* gbird;
	CCSize size;
	virtual void ccTouchesBegan(CCSet* touches, CCEvent* pEvent);
	virtual void ccTouchesMoved(CCSet* touches, CCEvent* pEvent);
	virtual void ccTouchesEnded(CCSet* touches, CCEvent* pEvent);
	virtual void ccTouchesCancelled(CCSet* touches, CCEvent* pEvent);
    virtual void registerWithTouchDispatcher();
    CCTMXTiledMap *map;
    CCTMXLayer *mapBackgroundLayer,*mapItemLayer;
    static CCScene *gameScene;
    CCLayer *statusLayer,*chatLayer;
    int doubleTouchCount,tripleTouchCount;
    CCPoint firstTripleTouchPoint;
};
#include "UserData.hpp"
#include "GameSceneChatLayer.hpp"
#include "GameSceneMessageLayer.hpp"
#include "GameSceneStatusLayer.hpp"
CCScene *GameScene::gameScene;
CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    gameScene = CCScene::create();
    
    // 'layer' is an autorelease object
    CCLayer *gameLayer = GameScene::create();
    // add layer as a child to scene
    gameScene->addChild(gameLayer,0);
    // return the scene
    return gameScene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setTouchEnabled(true);
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("audio/bg_1.ogg");
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("audio/bg_1.ogg",true);
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
	SimpleAudioEngine::sharedEngine()->preloadEffect("audio/ef_0.ogg");
	SimpleAudioEngine::sharedEngine()->preloadEffect("audio/ef_2.ogg");
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_7.ogg");
    size = CCDirector::sharedDirector()->getWinSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    statusLayer=GameSceneStatusLayer::create();
    statusLayer->setPosition(ccp(0,size.height));
    chatLayer=GameSceneChatLayer::create();
    chatLayer->setPosition(ccp(0,-size.height));
    gameScene->addChild(chatLayer,1);
    gameScene->addChild(statusLayer,1);
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("image/ui/CloseNormal.png","image/ui/CloseSelected.png",this,menu_selector(GameScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(size.width - pCloseItem->getContentSize().width/2 ,
                                pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    CCLabelTTF* pLabel = CCLabelTTF::create(UserData::username, "fonts/FZZYHandelGotD.ttf", 30);
    pLabel->setPosition(ccp(origin.x + size.width/2,
                            origin.y + size.height - pLabel->getContentSize().height));
    this->addChild(pLabel, 1);
    map=CCTMXTiledMap::create("map/map_fact.tmx");
    map->setPosition(CCPointZero);
    mapBackgroundLayer=map->layerNamed("background");
    mapItemLayer=map->layerNamed("item");
    if(map->getContentSize().height<size.height or map->getContentSize().width<size.width){
    	mapBackgroundLayer->setScale(MAX(size.height/map->getContentSize().height,size.width/map->getContentSize().width));
    	mapItemLayer->setScale(MAX(size.height/map->getContentSize().height,size.width/map->getContentSize().width));
    }
    this->addChild(mapItemLayer,3);
    this->addChild(mapBackgroundLayer,0);
    gbird=new GreenBird(ccp(size.width/2,size.height/2));
    this->addChild(gbird->sprite, 2);
    doubleTouchCount=0;tripleTouchCount=0;
     return true;
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
	this->setTouchEnabled(false);
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_0.ogg");
	if(statusLayer->getPositionY()!=size.height){
		CCAction *move=CCEaseExponentialOut::create(CCMoveTo::create(0.5,ccp(0,size.height)));
		statusLayer->runAction(move);
	}
	if(chatLayer->getPositionY()!=-size.height){
		CCAction *move=CCEaseExponentialOut::create(CCMoveTo::create(0.5,ccp(0,-size.height)));
		chatLayer->runAction(move);
	}
	CCLayer* messageLayer=GameSceneMessageLayer::create();
	gameScene->addChild(messageLayer,2);
}
void GameScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
}
void GameScene::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent){
}
void GameScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
	if(pTouches->count()==2 and tripleTouchCount==0){
		CCTouch* touch=dynamic_cast<CCTouch*>(*pTouches->begin());
		float x=ccpAdd(this->getPosition(),touch->getDelta()).x;
		float y=ccpAdd(this->getPosition(),touch->getDelta()).y;
		if(x>0)x=0;if(y>0)y=0;
		if(x<size.width-mapBackgroundLayer->boundingBox().size.width)x=size.width-mapBackgroundLayer->boundingBox().size.width;
		if(y<size.height-mapBackgroundLayer->boundingBox().size.height)y=size.height-mapBackgroundLayer->boundingBox().size.height;
		this->setPosition(ccp(x,y));
		doubleTouchCount=2;
	}
	if(pTouches->count()==3 and tripleTouchCount==0){
		firstTripleTouchPoint=dynamic_cast<CCTouch*>(*pTouches->begin())->getLocationInView();
		tripleTouchCount=3;
	}
}
void GameScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
	if(tripleTouchCount==3){
		CCTouch* touch=dynamic_cast<CCTouch*>(*pTouches->begin());
		if(touch->getLocationInView().y-firstTripleTouchPoint.y>100){
			if(chatLayer->getPositionY()!=-size.height){
				CCAction *move=CCEaseExponentialOut::create(CCMoveTo::create(0.5,ccp(0,-size.height)));
				chatLayer->runAction(move);
			}else{
				CCAction *move=CCEaseExponentialOut::create(CCMoveTo::create(0.5,ccp(0,0)));
				statusLayer->runAction(move);
			}
		}
		if(touch->getLocationInView().y-firstTripleTouchPoint.y<-100){
			if(statusLayer->getPositionY()!=size.height){
				CCAction *move=CCEaseExponentialOut::create(CCMoveTo::create(0.5,ccp(0,size.height)));
				statusLayer->runAction(move);
			}else{
				CCAction *move=CCEaseExponentialOut::create(CCMoveTo::create(0.5,ccp(0,0)));
				chatLayer->runAction(move);
			}
		}
	}
	if(pTouches->count()==1 and doubleTouchCount==0 and tripleTouchCount==0)
	{
		if(statusLayer->getPositionY()!=size.height){
			CCAction *move=CCEaseExponentialOut::create(CCMoveTo::create(0.5,ccp(0,size.height)));
			statusLayer->runAction(move);
		}
		if(chatLayer->getPositionY()!=-size.height){
			CCAction *move=CCEaseExponentialOut::create(CCMoveTo::create(0.5,ccp(0,-size.height)));
			chatLayer->runAction(move);
		}
		CCTouch* touch=dynamic_cast<CCTouch*>(pTouches->anyObject());
		CCPoint ptNode = convertTouchToNodeSpace(touch);
		gbird->moveto(ptNode);
	}
	if(doubleTouchCount>0)doubleTouchCount--;
	if(tripleTouchCount>0)tripleTouchCount--;
}
void GameScene::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
    CCLayer::registerWithTouchDispatcher();
}
#endif
