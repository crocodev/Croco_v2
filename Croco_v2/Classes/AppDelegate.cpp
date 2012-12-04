//
//  Croco_v2AppDelegate.cpp
//  Croco_v2
//
//  Created by admin on 26.11.12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#include "AppDelegate.h"

#include "AppMacros.h"

#include "cocos2d.h"
using namespace cocos2d;

#include "SimpleAudioEngine.h"

#include "CrocoBoardGame.h"
#include "TextureCache.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    
    pDirector->setOpenGLView(pEGLView);
    
    // Set the design resolution
    //pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
    
	CCSize frameSize = pEGLView->getFrameSize();
    
    CCFileUtils::sharedFileUtils()->setResourceDirectory(mediumResource.directory);
    
    
    // In this demo, we select resource according to the frame's height.
    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
    // We use the ratio of resource's height to the height of design resolution,
    // this can make sure that the resource's height could fit for the height of design resolution.
    
    // if the frame's height is larger than the height of medium resource size, select large resource.
	
    if (frameSize.height > mediumResource.size.height)
	{
		CCFileUtils::sharedFileUtils()->setResourceDirectory(largeResource.directory);
        //pDirector->setContentScaleFactor(designResolutionSize.height/largeResource.size.height);
	}
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else 
    {
        CCFileUtils::sharedFileUtils()->setResourceDirectory(mediumResource.directory);
        //pDirector->setContentScaleFactor(mediumResource.size.height/designResolutionSize.height);
    }    
    
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    /*
    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);
    */
    
    /*
    //detect retina
    CCSize size = CCDirector::sharedDirector()->getWinSize();
	if (size.width||size.height==2048)
    {
        CCDirector::sharedDirector()->enableRetinaDisplay(true);
    }
    */
    
    CCScene* pS_TextureCacheScene = CCScene::create();
	CCLayer* pL_TextureCacheLayer = new TextureCacheLayer();
	pS_TextureCacheScene->addChild(pL_TextureCacheLayer,0);
	pL_TextureCacheLayer->release();
    pDirector->runWithScene(pS_TextureCacheScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be paused
     SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
     SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
