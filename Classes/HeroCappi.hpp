#ifndef __Hero_Cappi__
#define __Hero_Cappi__
#include "cocos2d.h"
#include "HeroClass.hpp"
USING_NS_CC;
class HeroCappi: public Hero{
public:
	void createhero(CCPoint a,float scale,int id);
};

void HeroCappi::createhero(CCPoint a,float scale,int id){
	speed = 5;
	direction = 5;
	bubble_range = 3;
	bubble_num = 3;
	idx = id;
	islive = true;
	isfree = true;
	sprite = CCSprite::create();
	sprite->setScale(scale);
	sprite->setPosition(a);
	AniReader::read("unit_cappi.ani");
	num = AniReader::num;
	for (int i = 0; i < 100; i++)
		for(int j = 0; j < 4; j++)
		{
			list[i][j] = AniReader::list[i][j];
		}
	texture = CCTextureCache::sharedTextureCache()->addImage("image/unit/unit_cappi.png");
	animate = CCRepeatForever::create(CCAnimate::create(moveanimation(4)));
	sprite->runAction(animate);
	action=NULL;
}


#endif
