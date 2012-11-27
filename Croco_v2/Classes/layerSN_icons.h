//
//  layerSN_icons.h
//  Croco
//
//  Created by admin on 08.07.12.
//
//

#ifndef __Croco__layerSN_icons__
#define __Croco__layerSN_icons__

#include "CrocoBoardGame.h"
#import <Twitter/Twitter.h>
#import <Accounts/Accounts.h>
#import "FBC.h"
#import "VKConnectViewController.h"

#include "TextureCache.h"

class layerSN_icons : public CCLayer
{
public:
    layerSN_icons(void);
    ~layerSN_icons(void);
    
    void itm_TwCallback(CCObject* pSender);
    void itm_FbCallback(CCObject* pSender);
    void itm_VkCallback(CCObject* pSender);
};

#endif /* defined(__Croco__layerSN_icons__) */
