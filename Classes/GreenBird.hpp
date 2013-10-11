#ifndef __GREEN_BIRD__
#define __GREEN_BIRD__
#include "cocos2d.h"
#include "HeroClass.hpp"
USING_NS_CC;
class GreenBird:public CCNode,public Hero{
public:
	GreenBird(CCPoint a);
	void moveto(CCPoint a);
	void clearMove();
	CCSprite *sprite;
	CCAction* action;
};
GreenBird::GreenBird(CCPoint a){
	sprite = CCSprite::create();
	sprite->setPosition(a);
	texture = CCTextureCache::sharedTextureCache()->addImage("image/unit/green_bird.png");
	float w = texture->getContentSize().width / 2;
	float h = texture->getContentSize().height;
	animation = CCAnimation::create();
	animation->setDelayPerUnit(0.2f);
	for(int i = 0; i <2; i ++)
		animation->addSpriteFrameWithTexture(texture, CCRectMake(i * w, 0, w, h));
	animate = CCAnimate::create(animation);
	sprite->runAction(CCRepeatForever::create(animate));
	action=NULL;
}
void GreenBird::moveto(CCPoint ptNode){
	if(action!=NULL)return;
	sprite->setFlipX(ptNode.x>sprite->getPosition().x);
	CCMoveTo *move = CCMoveTo::create(ccpDistance(sprite->getPosition(),ptNode)/200, ptNode);
	CCFiniteTimeAction *clearmove=CCCallFuncN::create(this,callfuncN_selector(GreenBird::clearMove));
	action=CCSequence::create(move,clearmove,NULL);
	sprite->runAction(action);
}
void GreenBird::clearMove(){
	action=NULL;
//	sprite->setVisible(false);
}
#endif
