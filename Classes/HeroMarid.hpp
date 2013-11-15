#ifndef __Hero_Marid__
#define __Hero_Marid__
#include "cocos2d.h"
#include "HeroClass.hpp"
USING_NS_CC;
class HeroMarid: public Hero{
public:
	void createhero(CCPoint a,float scale);
};

void HeroMarid::createhero(CCPoint a,float scale){
	speed = 5;
	direction = 5;
	sprite = CCSprite::create();
	sprite->setScale(scale);
	sprite->setPosition(a);
	AniReader::read("unit_marid.ani");
	num = AniReader::num;
	for (int i = 0; i < 100; i++)
		for(int j = 0; j < 4; j++)
		{
			list[i][j] = AniReader::list[i][j];
		}
	texture = CCTextureCache::sharedTextureCache()->addImage("image/unit/unit_marid.png");
	animate = CCRepeatForever::create(CCAnimate::create(moveanimation(4)));
	sprite->runAction(animate);
	action=NULL;
}

#endif
