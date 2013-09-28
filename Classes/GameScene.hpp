#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ShareClass.hpp"
#include "SimpleAudioEngine.h"
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
    void moveActionEnd(CCNode* sender);
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
    cocos2d::CCSprite* gbird;
};

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
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("audio/bg_1.ogg");
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("audio/bg_1.ogg",true);
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
	SimpleAudioEngine::sharedEngine()->preloadEffect("audio/ef_0.ogg");
	SimpleAudioEngine::sharedEngine()->preloadEffect("audio/ef_2.ogg");
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_7.ogg");
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(GameScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create(ShareClass::username, "fonts/FZZYHandelGotD.ttf", 30);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    CCTMXTiledMap *map=CCTMXTiledMap::create("map/map_fact.tmx");
    map->setScaleX(visibleSize.width/(map->getMapSize().width*map->getTileSize().width));
    map->setScaleY(visibleSize.height/(map->getMapSize().height*map->getTileSize().height));
    this->addChild(map,0);

	gbird = CCSprite::create("green_bird.png", CCRectMake(0,0,49,30));
	gbird->setPosition(ccp(40,visibleSize.height/2));
	this->addChild(gbird, 2);
     return true;
}



void GameScene::menuCloseCallback(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_0.ogg");
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	CCMoveTo* move = CCMoveTo::create(2, ccp(size.width-40, size.height/2));
	CCMoveTo* moveback = CCMoveTo::create(2, ccp(40, size.height/2));
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("green_bird.png");
	float w = texture->getContentSize().width / 2;
	float h = texture->getContentSize().height;
	CCAnimation* animation = CCAnimation::create();
	animation->setDelayPerUnit(0.1f);
	for(int i = 0; i <2; i ++)
		animation->addSpriteFrameWithTexture(texture, CCRectMake(i * w, 0, w, h));
	CCAnimate* animate = CCAnimate::create(animation);
	gbird->runAction(CCRepeatForever::create(animate));

	CCFiniteTimeAction* flipXAction = CCFlipX::create(true);
	CCCallFuncN* end = CCCallFuncN::create(this,callfuncN_selector(GameScene::moveActionEnd));
	CCAction* action = CCSequence::create(flipXAction,move, flipXAction->reverse(),moveback,end, NULL);
	gbird->runAction(action);
}

void GameScene::moveActionEnd(CCNode* sender)
{
	CCDirector::sharedDirector()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	    exit(0);
	#endif
}

#endif // __HELLOWORLD_SCENE2_H__
