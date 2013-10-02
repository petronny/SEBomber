#ifndef __GAME_SCENE_TOUCH_LAYER__
#define __GAME_SCENE_TOUCH_LAYER__
#include "cocos2d.h"
USING_NS_CC;
class GameSceneTouchLayer : public CCLayer
 {
public:
  bool init();
  bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
  void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
  void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
  void ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent);
  void registerWithTouchDispatcher();
};
bool GameSceneTouchLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setTouchEnabled(true);
    return true;
}
bool GameSceneTouchLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	return false;
}
void GameSceneTouchLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
}
void GameSceneTouchLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
}
void GameSceneTouchLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
}
void GameSceneTouchLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCLayer::registerWithTouchDispatcher();
}
#endif
