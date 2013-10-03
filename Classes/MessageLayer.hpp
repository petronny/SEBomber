#ifndef __MESSAGE_LAYER__
#define __MESSAGE_LAYER__
typedef unsigned int size_t;
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
class MessageLayer : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // a selector callback
    // implement the "static node()" method manually
    CREATE_FUNC(MessageLayer);
    static size_t writehtml(uint8_t* ptr,size_t size,size_t number,void *stream);
	CCSize size;
};
// onserverField "init" you need to initialize your instance
bool MessageLayer::init()
{
	if (!CCLayer::init()){
		return false;
	}
	size = CCDirector::sharedDirector()->getWinSize();
	SimpleAudioEngine::sharedEngine()->preloadEffect("audio/ef_0.ogg");
	this->
	return true;
}
#endif // __MessageLayer_LAYER__
