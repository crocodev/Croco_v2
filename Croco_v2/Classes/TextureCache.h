//
//  TextureCache.h
//  Croco
//
//  Created by admin on 18.07.12.
//
//

#ifndef __Croco__TextureCache__
#define __Croco__TextureCache__

#include "CrocoBoardGame.h"

class TextureCacheLayer : public CCLayer
{
public:
	TextureCacheLayer();
	void loadMainMenu();
	void loadingCallBack(cocos2d::CCObject *obj);
    
private:
	cocos2d::CCLabelTTF *m_pLabelLoading;
	cocos2d::CCLabelTTF *m_pLabelPercent;
	int m_nNumberOfSprites;
	int m_nNumberOfLoadedSprites;
};

#endif /* defined(__Croco__TextureCache__) */
