#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__
typedef unsigned int size_t;
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
class TitleScene : public CCLayer ,public CCTextFieldDelegate
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static CCScene* scene();
    // a selector callback

    // implement the "static node()" method manually
    CREATE_FUNC(TitleScene);
    void showBackground();
    void showTitle();
	CCSize size;
	CCSprite *bomb,*title,*touch;
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent);
    virtual void registerWithTouchDispatcher();

};
CCScene* TitleScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	TitleScene *layer = TitleScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("audio/bg_0.ogg");
	size = CCDirector::sharedDirector()->getWinSize();
	bomb=CCSprite::create("image/bomb.png");
	CCFiniteTimeAction* place=CCPlace::create(ccp(size.width/2,size.height+bomb->getContentSize().height));
	CCAction *movein=CCEaseExponentialOut::create(CCMoveTo::create(2,ccp(size.width/2,size.height/4)));
	CCAction *moveback=CCEaseExponentialOut::create(CCMoveTo::create(2,ccp(size.width/2,size.height/2)));
	CCFiniteTimeAction *showbackground=CCCallFuncN::create(this,callfuncN_selector(TitleScene::showBackground));
	CCFiniteTimeAction *showtitle=CCCallFuncN::create(this,callfuncN_selector(TitleScene::showTitle));
	CCAction *action=CCSequence::create(place,movein,showbackground,moveback,showtitle,NULL);
	this->addChild(bomb,3);
	bomb->runAction(action);
	return true;
}
void TitleScene::showBackground(){
	SimpleAudioEngine::sharedEngine()->preloadEffect("audio/ef_11.ogg");
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_11.ogg");
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("audio/bg_0.ogg",true);
	CCSprite *background=CCSprite::create("image/bg.png");
	background->setPosition( ccp(size.width/2, size.height/2) );
	background->setScaleX(size.width/background->getContentSize().width);
	background->setScaleY(size.height/background->getContentSize().height);
	CCAction *fadein=CCFadeIn::create(0.5);
	background->runAction(fadein);
	this->addChild(background,0);
	CCSprite *title_left=CCSprite::create("image/title_left.png");
	CCSprite *title_right=CCSprite::create("image/title_right.png");
	title_left->setPosition(ccp(size.width/2,size.height/2));
	title_right->setPosition(ccp(size.width/2,size.height/2));
	title_left->setScale(0);
	title_right->setScale(0);
	CCScaleTo *scale_left=CCScaleTo::create(1,size.height/title_left->getContentSize().height);
	CCScaleTo *scale_right=CCScaleTo::create(1,size.height/title_right->getContentSize().height);
	CCMoveTo *move_left=CCMoveTo::create(1,ccp(title_left->getContentSize().width*size.height/title_left->getContentSize().height/2,size.height/2));
	CCMoveTo *move_right=CCMoveTo::create(1,ccp(size.width-title_right->getContentSize().width*size.height/title_right->getContentSize().height/2,size.height/2));
	title_left->runAction(move_left);
	title_left->runAction(scale_left);
	title_right->runAction(move_right);
	title_right->runAction(scale_right);
	this->addChild(title_left,1);
	this->addChild(title_right,1);
	CCSprite *lefttop=CCSprite::create("image/title_lefttop.png");
	CCSprite *leftbottom=CCSprite::create("image/title_leftbottom.png");
	CCSprite *righttop=CCSprite::create("image/title_righttop.png");
	CCSprite *rightbottom=CCSprite::create("image/title_rightbottom.png");
//	leftbottom->setScale(0);lefttop->setScale(0);rightbottom->setScale(0);righttop->setScale(0);
	leftbottom->setPosition(ccp(size.width/2,size.height/2));
	lefttop->setPosition(ccp(size.width/2,size.height/2));
	rightbottom->setPosition(ccp(size.width/2,size.height/2));
	righttop->setPosition(ccp(size.width/2,size.height/2));
	CCMoveTo *move_lefttop=CCMoveTo::create(1,ccp(size.width/3,size.height/3*2));
	CCMoveTo *move_leftbottom=CCMoveTo::create(1,ccp(size.width/3,size.height/3));
	CCMoveTo *move_righttop=CCMoveTo::create(1,ccp(size.width/3*2,size.height/3*2));
	CCMoveTo *move_rightbottom=CCMoveTo::create(1,ccp(size.width/3*2,size.height/3));
	lefttop->runAction(move_lefttop);
	leftbottom->runAction(move_leftbottom);
	righttop->runAction(move_righttop);
	rightbottom->runAction(move_rightbottom);
	this->addChild(lefttop,2);
	this->addChild(leftbottom,2);
	this->addChild(rightbottom,2);
	this->addChild(righttop,2);
}
void TitleScene::showTitle(){
	title=CCSprite::create("image/003c.png");
	CCAnimation *animation = CCAnimation::create();
	animation->setDelayPerUnit(0.25f);
	animation->addSpriteFrameWithFileName("image/003c-r.png");
	animation->addSpriteFrameWithFileName("image/003c-g.png");
	animation->addSpriteFrameWithFileName("image/003c-b.png");
	animation->addSpriteFrameWithFileName("image/003c.png");
	CCAnimate *animate = CCAnimate::create(animation);
	title->runAction(CCRepeatForever::create(animate));
	title->setScale(size.width/3/title->getContentSize().width);
	title->setPosition(ccp(size.width / 2, size.height/2 - title->boundingBox().size.height));
	CCAction *fadein=CCFadeIn::create(0.5);
	title->runAction(fadein);
	// add the label as a child to this layer
	this->addChild(title, 4);
	touch=CCSprite::create("image/touch.png");
	touch->setPosition(ccp	(size.width/2,size.height/4));
	CCAction *delay2=CCDelayTime::create(1);
	CCAction *delay1=CCDelayTime::create(0.5);
	CCActionInterval *blink=CCSequence::create(CCShow::create(),delay2,CCHide::create(),delay1,NULL);
	touch->runAction(fadein);
	touch->runAction(CCRepeatForever::create(blink));
	this->addChild(touch,4);
	this->setTouchEnabled(true);
}
bool TitleScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	CCAction* action=CCEaseExponentialOut::create(CCMoveBy::create(0.5,ccp(0, size.height/2 - bomb->boundingBox().size.height/2)));
	bomb->runAction(action);
	action=CCEaseExponentialOut::create(CCMoveBy::create(0.5,ccp(0, size.height/2 - bomb->boundingBox().size.height/2)));
	title->runAction(action);
	touch->stopAllActions();
	touch->setVisible(false);
	this->setTouchEnabled(false);
	return true;
}
void TitleScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
}
void TitleScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
}
void TitleScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
}
void TitleScene::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCLayer::registerWithTouchDispatcher();
}
#endif // __TitleScene_SCENE_H__
