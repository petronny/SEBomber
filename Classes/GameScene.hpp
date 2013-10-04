#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GreenBird.hpp"
USING_NS_CC;
using namespace CocosDenshion;
class GameScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
    GreenBird* gbird;
	CCSize size;
	virtual void ccTouchesBegan(CCSet* touches, CCEvent* pEvent);
	virtual void ccTouchesMoved(CCSet* touches, CCEvent* pEvent);
	virtual void ccTouchesEnded(CCSet* touches, CCEvent* pEvent);
	virtual void ccTouchesCancelled(CCSet* touches, CCEvent* pEvent);
    virtual void registerWithTouchDispatcher();
    CCTMXTiledMap *map;
    int doubleTouchCount;
};
#include "ShareData.hpp"
CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "image/ui/CloseNormal.png",
                                        "image/ui/CloseSelected.png",
                                        this,
                                        menu_selector(GameScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + size.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create(ShareData::username, "fonts/FZZYHandelGotD.ttf", 30);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + size.width/2,
                            origin.y + size.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    map=CCTMXTiledMap::create("map/map_fact.tmx");
//    map->setScaleX(size.width/(map->getMapSize().width*map->getTileSize().width));
//   map->setScaleY(size.height/(map->getMapSize().height*map->getTileSize().height));
    map->setPosition(CCPointZero);
    this->addChild(map,0);
	gbird=new GreenBird(ccp(size.width/2,size.height/2));
	this->addChild(gbird->sprite, 2);
	doubleTouchCount=0;
     return true;
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_0.ogg");
	CCDirector::sharedDirector()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	    exit(0);
	#endif
}
void GameScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
}
void GameScene::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent){
}
void GameScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
	if(pTouches->count()==2){
		CCTouch* touch=dynamic_cast<CCTouch*>(*pTouches->begin());
		map->setPosition(ccpAdd(map->getPosition(),touch->getDelta()));
		doubleTouchCount=2;
	}
}
void GameScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
	if(pTouches->count()==1 and doubleTouchCount==0)
	{
		CCTouch* touch=dynamic_cast<CCTouch*>(pTouches->anyObject());
		CCPoint ptNode = convertTouchToNodeSpace(touch);
		gbird->moveto(ptNode);
	}
	if(doubleTouchCount>0)doubleTouchCount--;
}
void GameScene::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
    CCLayer::registerWithTouchDispatcher();
}
#endif // __HELLOWORLD_SCENE2_H__
