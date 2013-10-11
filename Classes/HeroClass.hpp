#ifndef __HERO_CLASS__
#define __HERO_CLASS__
#include "cocos2d.h"
#include "AniReader.hpp"
USING_NS_CC;
class Hero{
public:
	virtual ~Hero(){}
	virtual void moveto(CCPoint a){}
	CCSprite *sprite;
	CCTexture2D* texture;
	CCAnimation* animation;
	CCFiniteTimeAction* action;
	CCActionInterval* animate;
	CCMoveTo* move;
	float speed;
	int num;
	int direction;
	int list[100][4];
	//AniReader::read("/image/unit/")

};
#endif
