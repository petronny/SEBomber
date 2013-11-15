#ifndef __Props_CLASS__
#define __Props_CLASS__
#include "cocos2d.h"
#include "AniReader.hpp"
USING_NS_CC;
class Props:public CCNode{
public:
	CCTexture2D* texture;
	CCAnimation* animation;
	CCAction* action;
	CCActionInterval* animate;
	CCSprite *sprite;
	int type;
	int num;
	int list[100][4];
	virtual ~Props() {}
	virtual void create(CCPoint a,float scale) {}
	void destory();
};
#endif
