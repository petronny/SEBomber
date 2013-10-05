#ifndef __HERO_CLASS__
#define __HERO_CLASS__
#include "cocos2d.h"
USING_NS_CC;
class Hero{
public:
	virtual void moveto(CCPoint a);
	CCSprite *sprite;
	CCTexture2D* texture;
	CCAnimate* animate;
	CCAnimation* animation;
	CCMoveTo* move;
};
void Hero::moveto(CCPoint a){
}
#endif
