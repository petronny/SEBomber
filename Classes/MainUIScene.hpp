#ifndef __MAINUI_SCENE__
#define __MAINUI_SCENE__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
class MainUIScene : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static CCScene* scene();
    // a selector callback
    void logout();
    void multiplayerSelected();
    void buddylistSelected();
    void inventorySelected();
    void storeSelected();
    void okButtonClicked();
    // implement the "static node()" method manually
    CREATE_FUNC(MainUIScene);
	CCSize size;
	CCSprite* buttonSurround;
	CCMenuItemImage *multiplayerItem,*buddylistItem,*inventoryItem,*storeItem,*okButtonItem;
	static CCScene *mainUIScene;
};
#include "TitleScene.hpp"
#include "ShareData.hpp"
#include "MainUISceneBuddyListLayer.hpp"
#include "MainUISceneInventoryLayer.hpp"
#include "MainUISceneMultiplayerLayer.hpp"
#include "MainUISceneStoreLayer.hpp"
#include "GameScene.hpp"
CCScene *MainUIScene::mainUIScene;
CCScene* MainUIScene::scene()
{
	// 'scene' is an autorelease object
	mainUIScene = CCScene::create();
	// 'layer' is an autorelease object
	MainUIScene *layer = MainUIScene::create();
	// add layer as a child to scene
	mainUIScene->addChild(layer,2);
	// return the scene
	return mainUIScene;
}
// on "init" you need to initialize your instance
bool MainUIScene::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("audio/bg_6.ogg");
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("audio/bg_6.ogg",true);
	SimpleAudioEngine::sharedEngine()->preloadEffect("audio/ef_0.ogg");
	size = CCDirector::sharedDirector()->getWinSize();

	CCMenu* pMenu = CCMenu::create();
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu,2);

	CCLayer *layer0 = CCLayer::create();
	mainUIScene->addChild(layer0,0);
	CCSprite *background=CCSprite::create("image/ui/bg.jpg");
	background->setPosition( ccp(size.width/2, size.height/2) );
	background->setScaleX(size.width/background->getContentSize().width);
	background->setScaleY(size.height/background->getContentSize().height);
	layer0->addChild(background,0);

	CCSprite *ui_right=CCSprite::create("image/ui/ui_right.png");
	ui_right->setScale(size.height/ui_right->getContentSize().height);
	ui_right->setPosition(ccp(ui_right->boundingBox().size.width/2,size.height/2));
	this->addChild(ui_right,1);

	CCLabelTTF *logoutLabel=CCLabelTTF::create("登\t出","fonts/FZKaTong-M19T.ttf",25);
	logoutLabel->setColor(ccYELLOW);
	CCMenuItemLabel *logoutItem=CCMenuItemLabel::create(logoutLabel,this,menu_selector(MainUIScene::logout));
	logoutItem->setPosition(ccp(ui_right->boundingBox().size.width/128*67,size.height/64*59));
	pMenu->addChild(logoutItem);

	char facePath[80];
	sprintf(facePath,"image/face/face%d.png",ShareData::face);
	CCSprite *face=CCSprite::create(facePath);
	face->setScale(size.height/ui_right->getContentSize().height*1.12);
	face->setPosition(ccp(ui_right->boundingBox().size.width/128*67,size.height/64*39));
	this->addChild(face,2);

	CCLabelTTF *usernameLabel=CCLabelTTF::create(ShareData::username,"fonts/FZKaTong-M19T.ttf",30);
	usernameLabel->setPosition(ccp(ui_right->boundingBox().size.width/128*67,size.height/64*49));
	usernameLabel->setColor(ccMAGENTA);
	this->addChild(usernameLabel,2);

	multiplayerItem=CCMenuItemImage::create("image/ui/button_normal.png","image/ui/button_selected.png",this,menu_selector(MainUIScene::multiplayerSelected));
	multiplayerItem->setScaleX((size.width-ui_right->boundingBox().size.width)/4/multiplayerItem->getContentSize().width);
	multiplayerItem->setScaleY(size.height/8/multiplayerItem->getContentSize().height);
	multiplayerItem->setPosition(ccp(ui_right->boundingBox().size.width+multiplayerItem->boundingBox().size.width/2,size.height-multiplayerItem->boundingBox().size.height/2));
	pMenu->addChild(multiplayerItem);
	CCLabelTTF *multiplayerLabel=CCLabelTTF::create("多人模式","fonts/FZKaTong-M19T.ttf",25);
	multiplayerLabel->setPosition(multiplayerItem->getPosition());
	multiplayerLabel->setColor(ccYELLOW);
	this->addChild(multiplayerLabel,3);

	buddylistItem=CCMenuItemImage::create("image/ui/button_normal.png","image/ui/button_selected.png",this,menu_selector(MainUIScene::buddylistSelected));
	buddylistItem->setScaleX((size.width-ui_right->boundingBox().size.width)/4/multiplayerItem->getContentSize().width);
	buddylistItem->setScaleY(size.height/8/multiplayerItem->getContentSize().height);
	buddylistItem->setPosition(ccp(ui_right->boundingBox().size.width+multiplayerItem->boundingBox().size.width*3/2,size.height-multiplayerItem->boundingBox().size.height/2));
	pMenu->addChild(buddylistItem);
	CCLabelTTF *buddylistLabel=CCLabelTTF::create("我的好友","fonts/FZKaTong-M19T.ttf",25);
	buddylistLabel->setPosition(buddylistItem->getPosition());
	buddylistLabel->setColor(ccYELLOW);
	this->addChild(buddylistLabel,3);

	inventoryItem=CCMenuItemImage::create("image/ui/button_normal.png","image/ui/button_selected.png",this,menu_selector(MainUIScene::inventorySelected));
	inventoryItem->setScaleX((size.width-ui_right->boundingBox().size.width)/4/multiplayerItem->getContentSize().width);
	inventoryItem->setScaleY(size.height/8/multiplayerItem->getContentSize().height);
	inventoryItem->setPosition(ccp(ui_right->boundingBox().size.width+multiplayerItem->boundingBox().size.width*5/2,size.height-multiplayerItem->boundingBox().size.height/2));
	pMenu->addChild(inventoryItem);
	CCLabelTTF *inventoryLabel=CCLabelTTF::create("我的物品","fonts/FZKaTong-M19T.ttf",25);
	inventoryLabel->setPosition(inventoryItem->getPosition());
	inventoryLabel->setColor(ccYELLOW);
	this->addChild(inventoryLabel,3);

	storeItem=CCMenuItemImage::create("image/ui/button_normal.png","image/ui/button_selected.png",this,menu_selector(MainUIScene::storeSelected));
	storeItem->setScaleX((size.width-ui_right->boundingBox().size.width)/4/multiplayerItem->getContentSize().width);
	storeItem->setScaleY(size.height/8/multiplayerItem->getContentSize().height);
	storeItem->setPosition(ccp(ui_right->boundingBox().size.width+multiplayerItem->boundingBox().size.width*7/2,size.height-multiplayerItem->boundingBox().size.height/2));
	pMenu->addChild(storeItem);
	CCLabelTTF *storeLabel=CCLabelTTF::create("道具商店","fonts/FZKaTong-M19T.ttf",25);
	storeLabel->setPosition(storeItem->getPosition());
	storeLabel->setColor(ccYELLOW);
	this->addChild(storeLabel,3);

	buttonSurround=CCSprite::create("image/ui/button_surround.png");
	buttonSurround->setScaleX(multiplayerItem->boundingBox().size.width/buttonSurround->getContentSize().width);
	buttonSurround->setScaleY(multiplayerItem->boundingBox().size.height/buttonSurround->getContentSize().height);
	multiplayerSelected();
	this->addChild(buttonSurround,3);

	CCSprite *rankSprite=CCSprite::create("image/ui/rank.png");
	rankSprite->setScale(size.height/16/rankSprite->getContentSize().height);
	rankSprite->setPosition(ccp(ui_right->boundingBox().size.width/128*37,size.height/64*27));
	this->addChild(rankSprite,2);

	char rankPath[80];
	sprintf(rankPath,"image/rank/rank%d.png",ShareData::rank);
	CCSprite *rank=CCSprite::create(rankPath);
	rank->setScale(rankSprite->boundingBox().size.width/rank->getContentSize().width);
	rank->setPosition(rankSprite->getPosition());
	this->addChild(rank,3);

	char rankMessage[20];
	sprintf(rankMessage,"Lv.%d",ShareData::rank);
	CCLabelTTF *rankLabel=CCLabelTTF::create(rankMessage,"fonts/FZKaTong-M19T.ttf",25);
	rankLabel->setPosition(ccp(ui_right->boundingBox().size.width/128*82,rankSprite->getPositionY()));
	this->addChild(rankLabel,3);

	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("image/ui/magic_bubble.png");
	float w = texture->getContentSize().width / 2;
	float h = texture->getContentSize().height;
	CCAnimation *animation = CCAnimation::create();
	animation->setDelayPerUnit(0.5f);
	for(int i = 0; i <2; i ++)
		animation->addSpriteFrameWithTexture(texture, CCRectMake(i * w, 0, w, h));
	CCAnimate *animate = CCAnimate::create(animation);
	CCSprite *magicBubble=CCSprite::create("image/ui/magic_bubble.png",CCRectMake(0,0,w,h));
	magicBubble->setScale(rankSprite->boundingBox().size.width/magicBubble->getContentSize().width*1.4);
	magicBubble->runAction(CCRepeatForever::create(animate));
	magicBubble->setPosition(ccp(rank->getPositionX(),size.height/128*45));
	this->addChild(magicBubble,2);

	char magicBubbleNum[80];
	sprintf(magicBubbleNum,"%d",ShareData::magicBubbleNum);
	CCLabelTTF *magicBubbleLabel=CCLabelTTF::create(magicBubbleNum,"fonts/FZKaTong-M19T.ttf",25);
	magicBubbleLabel->setPosition(ccp(rankLabel->getPositionX(),magicBubble->getPositionY()));
	this->addChild(magicBubbleLabel,2);

	okButtonItem=CCMenuItemImage::create("image/ui/ok_button_normal.png","image/ui/ok_button_selected.png","image/ui/ok_button_disabled.png",this,menu_selector(MainUIScene::okButtonClicked));
	okButtonItem->setScale(size.height/ui_right->getContentSize().height);
	okButtonItem->setPosition(ccp(ui_right->boundingBox().size.width/128*67,size.height/512*77));
//	okButtonItem->setEnabled(false);
	pMenu->addChild(okButtonItem);
	return true;
}
void MainUIScene::logout(){
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_0.ogg");
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	ShareData::userid=-1;
	CCScene *pScene =TitleScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFlipY::create(0.5f, pScene));
}
void MainUIScene::multiplayerSelected(){
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_0.ogg");
	buttonSurround->stopAllActions();
	CCAction *move=CCEaseExponentialOut::create(CCMoveTo::create(0.5,multiplayerItem->getPosition()));
	buttonSurround->runAction(move);
	mainUIScene->removeChildByTag(1,true);
	CCLayer *multiplayerLayer=MainUISceneMultiplayerLayer::create();
	mainUIScene->addChild(multiplayerLayer,1,1);
}
void MainUIScene::buddylistSelected(){
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_0.ogg");
	buttonSurround->stopAllActions();
	CCAction *move=CCEaseExponentialOut::create(CCMoveTo::create(0.5,buddylistItem->getPosition()));
	buttonSurround->runAction(move);
	mainUIScene->removeChildByTag(1,true);
	CCLayer *buddylistLayer=MainUISceneBuddyListLayer::create();
	mainUIScene->addChild(buddylistLayer,1,1);
}
void MainUIScene::inventorySelected(){
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_0.ogg");
	buttonSurround->stopAllActions();
	CCAction *move=CCEaseExponentialOut::create(CCMoveTo::create(0.5,inventoryItem->getPosition()));
	buttonSurround->runAction(move);
	mainUIScene->removeChildByTag(1,true);
	CCLayer *inventoryLayer=MainUISceneInventoryLayer::create();
	mainUIScene->addChild(inventoryLayer,1,1);
}
void MainUIScene::storeSelected(){
	SimpleAudioEngine::sharedEngine()->playEffect("audio/ef_0.ogg");
	buttonSurround->stopAllActions();
	CCAction *move=CCEaseExponentialOut::create(CCMoveTo::create(0.5,storeItem->getPosition()));
	buttonSurround->runAction(move);
	mainUIScene->removeChildByTag(1,true);
	CCLayer *storeLayer=MainUISceneStoreLayer::create();
	mainUIScene->addChild(storeLayer,1,1);
}
void MainUIScene::okButtonClicked(){
	CCScene *pScene =GameScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFlipY::create(0.5f, pScene));
}
#endif
