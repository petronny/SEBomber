#ifndef __GREEN_BIRD__
#define __GREEN_BIRD__
#include "cocos2d.h"
USING_NS_CC;
class GreenBird{
public:
	void moveto(CCPoint a);
	GreenBird(CCPoint a);
	CCSprite *sprite;
	CCTexture2D* texture;
	CCAnimate* animate;
	CCAnimation* animation;
	CCMoveTo* move;
};
GreenBird::GreenBird(CCPoint a){
	sprite = CCSprite::create("image/unit/green_bird.png", CCRectMake(0,0,49,30));
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
	move=NULL;
}
void GreenBird::moveto(CCPoint ptNode){
	if(move!=NULL)sprite->stopAction(move);
	sprite->setFlipX(ptNode.x>sprite->getPosition().x);
	move = CCMoveTo::create(ccpDistance(sprite->getPosition(),ptNode)/200, ptNode);
	sprite->runAction(move);
}
#endif
