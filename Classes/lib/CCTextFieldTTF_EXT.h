#ifndef __CC_TEXT_FIELD_EXT_H__
#define __CC_TEXT_FIELD_EXT_H__
#include "cocos2d.h"
#include <iostream>
using namespace std;
using namespace cocos2d;

class CCTextFieldTTF_EXT : public CCTextFieldTTF
{
public:
 CCTextFieldTTF_EXT();
 ~CCTextFieldTTF_EXT();
 virtual void insertText(const char * text, int len);
 void setm_InputType(int type)
 {
  m_InputType = type;
 }
 int getType()
 {
  return m_InputType;
 }
 void setInputSize(int size)
 {
  m_TextSize = size;
  for(int i=0;i!=size;++i)
  {
   m_ConstText.push_back('*');
  }
 }

public:
 /** creates a CCTextFieldTTF_EXT from a fontname, alignment, dimension and font size */
    static CCTextFieldTTF_EXT * create(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize);
    /** creates a CCLabelTTF from a fontname and font size */
    static CCTextFieldTTF_EXT * create(const char *placeholder, const char *fontName, float fontSize);
    /** initializes the CCTextFieldTTF with a font name, alignment, dimension and font size */
    bool initWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize);
    /** initializes the CCTextFieldTTF with a font name and font size */
    bool initWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize);
public:
 void setStringWithCursor(float t);
protected:
 int m_InputType;
 int m_TextSize;
 string m_ConstText;

};
#endif




