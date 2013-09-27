#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
class HelloWorld : public cocos2d::CCLayer ,public cocos2d::CCTextFieldDelegate
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
    void textFieldPressed1(CCObject *sender);   
    void textFieldPressed2(CCObject *sender);   
    cocos2d::CCTextFieldTTF *text1;
    cocos2d::CCTextFieldTTF *text2;
    cocos2d::CCMenuItemFont* tapItem2;
    bool onTextFieldAttachWithIME(cocos2d::CCTextFieldTTF *sender);
    bool onTextFieldDetachWithIME(cocos2d::CCTextFieldTTF *sender);
    
};

#endif // __HELLOWORLD_SCENE_H__
