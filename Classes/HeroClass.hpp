#ifndef __HERO_CLASS__
#define __HERO_CLASS__
#include "cocos2d.h"
USING_NS_CC;
class Hero{
public:
	virtual ~Hero(){}
	virtual void moveto(CCPoint a){}
	CCTexture2D* texture;
	CCAnimate* animate;
	CCAnimation* animation;

};
#endif
