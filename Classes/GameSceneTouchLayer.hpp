#ifndef __GAME_SCENE_TOUCH_LAYER__
#define __GAME_SCENE_TOUCH_LAYER__
#include "cocos2d.h"
USING_NS_CC;
class GameSceneTouchLayer : public CCLayer
 {
 public:
	CC_SYNTHESIZE(TouchLayerDelegate*,m_pDelegate,Delegate);
public:
 bool init();
 void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
 void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
 void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
 void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
 void onExit();

};

#endif
