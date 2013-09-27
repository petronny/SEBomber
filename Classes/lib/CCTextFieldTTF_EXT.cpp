#ifndef __CC_TEXT_FIELD_H__
#define __CC_TEXT_FIELD_H__
#include "CCTextFieldTTF_EXT.h"
static int _calcCharCount(const char * pszText)
{
    int n = 0;
    char ch = 0;
    while ((ch = *pszText))
    {
        CC_BREAK_IF(! ch);
        
        if (0x80 != (0xC0 & ch))
        {
            ++n;
        }
        ++pszText;
    }
    return n;
}
CCTextFieldTTF_EXT::CCTextFieldTTF_EXT():m_InputType(0),m_TextSize(0)
{ 
	 schedule(schedule_selector(CCTextFieldTTF_EXT::setStringWithCursor), 1.0f);
}

CCTextFieldTTF_EXT::~CCTextFieldTTF_EXT()
{}

void CCTextFieldTTF_EXT::insertText(const char * text, int len)
{
	std::string sInsert(text, len);

    // insert \n means input end
    int nPos = sInsert.find('\n');
    if ((int)sInsert.npos != nPos)
    {
        len = nPos;
        sInsert.erase(nPos);
    }
    
    if (len > 0)
    {
        if (m_pDelegate && m_pDelegate->onTextFieldInsertText(this, sInsert.c_str(), len))
        {
            // delegate doesn't want to insert text
            return;
        }
        
        m_nCharCount += _calcCharCount(sInsert.c_str());
        std::string sText(*m_pInputText);
        sText.append(sInsert);
	if(!m_InputType)
        {
		setString(sText.c_str());
	}
	else
	{
		setString(m_ConstText.substr(0,sText.size()).c_str());
	}
    }
}

CCTextFieldTTF_EXT * CCTextFieldTTF_EXT::create(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
{        
    CCTextFieldTTF_EXT *pRet = new CCTextFieldTTF_EXT();
    if(pRet && pRet->initWithPlaceHolder("", dimensions, alignment, fontName, fontSize))
    {
        pRet->autorelease();
        if (placeholder)
        {
            pRet->setPlaceHolder(placeholder);
        }
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCTextFieldTTF_EXT * CCTextFieldTTF_EXT::create(const char *placeholder, const char *fontName, float fontSize)
{
    CCTextFieldTTF_EXT *pRet = new CCTextFieldTTF_EXT();
    if(pRet && pRet->initWithString("", fontName, fontSize))
    {
        pRet->autorelease();
        if (placeholder)
        {
            pRet->setPlaceHolder(placeholder);
        }
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

//////////////////////////////////////////////////////////////////////////
// initialize
//////////////////////////////////////////////////////////////////////////

bool CCTextFieldTTF_EXT::initWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
{
    if (placeholder)
    {
        CC_SAFE_DELETE(m_pPlaceHolder);
        m_pPlaceHolder = new std::string(placeholder);
    }
    return CCLabelTTF::initWithString(m_pPlaceHolder->c_str(), fontName, fontSize, dimensions, alignment);
}
bool CCTextFieldTTF_EXT::initWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize)
{
    if (placeholder)
    {
        CC_SAFE_DELETE(m_pPlaceHolder);
        m_pPlaceHolder = new std::string(placeholder);
    }
    return CCLabelTTF::initWithString(m_pPlaceHolder->c_str(), fontName, fontSize);
}
void CCTextFieldTTF_EXT::setStringWithCursor(float t)
{
		return;
	static bool first = true;
	if(first)
	{
		string sCursor =  string(getString())+"|";
		setString(sCursor.c_str());
		first = false;
	}
	else
	{
		string sCursor =  string(getString());
		if(sCursor.size())
		{
			sCursor.pop_back();//+"|";
			setString(sCursor.c_str());
		}
		first = true;
	}
}

