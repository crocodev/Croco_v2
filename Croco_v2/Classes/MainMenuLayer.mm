#import "MainMenuLayer.h"
#import "layerSN_icons.h"
#include "SubMenu.h"
#include "Credits.h"

#import "AppController.h"

MainMenuLayer::MainMenuLayer(int isGameStarted)
{
    // This makes relative paths work in C++ in Xcode by changing directory to the Resources folder inside the .app bundle *commented. Workdir=projectdir
#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX_FILE];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX_FILE))
    {
        // error!
    }
    CFRelease(resourcesURL);
    
    chdir(path);
    //chdir("/Users/totrin/Downloads/asnikitin-Croco-913f24d/Croco/Resource");
    //chdir("/Users/admin/Documents/Development/Croco/Croco/Resource");
#endif
    //hui
	//screen center
    CCSize size = CCDirector::sharedDirector()->getWinSize();
	float x = size.width/2;
    float y = size.height/2;

	m_isGameStarted=isGameStarted;

    CCMenuItemImage* itm_Continue = CCMenuItemImage::create("MainMenu/btn_continue.png","MainMenu/btn_continue_a.png",this,menu_selector(MainMenuLayer::itm_ContinueCallback));
	CCMenuItemImage* itm_Start = CCMenuItemImage::create("MainMenu/btn_start.png","MainMenu/btn_start_a.png",this,menu_selector(MainMenuLayer::itm_StartCallback));
	CCMenuItemImage* itm_Help = CCMenuItemImage::create("MainMenu/btn_help.png","MainMenu/btn_help_a.png",this,menu_selector(ActionLayer::itm_card5Callback));
    CCMenuItemImage* itm_Credits = CCMenuItemImage::create("MainMenu/btn_credits.png","MainMenu/btn_credits_a.png",this,menu_selector(MainMenuLayer::itm_CreditsCallback));
	CCMenu* im_MainMenu = CCMenu::create(itm_Continue, itm_Start, itm_Help, itm_Credits, NULL);
    im_MainMenu->alignItemsVerticallyWithPadding(10.0f);
	addChild(im_MainMenu,2);    
	
	if(!m_isGameStarted) itm_Continue->setVisible(0);
	im_MainMenu->setPosition(ccp(size.width*3/4,y));

    /*
     call CCTextureCache::sharedTextureCache()->addImage("MyTexture.png"); to preload images into CCTextureCache. So next time you use CCSprite::initWithFile("MyTexture.png") to create a sprite, it will use the exiting texture in the cache
     CCSpriteSheet is replaced by CCSpriteBatchcreate since cocos2d-iphone 0.9.x. It can definitely improve your performance if you have more than 30 sprites in one frame. But CCSpriteBatchcreate can not optimize the situation that you have "many animates between different frames".
     */
    
    CCSprite* pS_background = CCSprite::create(MainMenu_background);
    addChild(pS_background,0);
	pS_background->setPosition(ccp(x,y));

    //add leather
	CCSprite* lth = CCSprite::create("MainMenu/lead.png");
    addChild(lth,0);
    lth->setAnchorPoint(ccp(0.5,1));
	lth->setPosition(ccp(x,y*2));
    
    //add croco & cards
	CCSprite* croco = CCSprite::create("MainMenu/croco.png");
    addChild(croco,0);
	croco->setPosition(ccp(size.width/4.25,size.height/2.63));
    
    //add token
    CCActionInterval* token_rotate = CCEaseInOut::create(CCRotateBy::create(1.5f, 2),3.0f);
    CCFiniteTimeAction* fta = CCSequence::create(token_rotate,token_rotate->reverse(),NULL);
	CCSprite* token = CCSprite::create("MainMenu/token.png");
    addChild(token,0);
	token->setPosition(ccp(size.width/2.88,size.height/12.93));
    token->setAnchorPoint(ccp(1.2,-2));
    token->runAction(CCRepeatForever::create((CCActionInterval*)fta));
    
    //MUSIC
	//PLAYBGMUSIC(MUSIC_MAIN)
  
    //Radio
    /*
	radio_active = 0;
	itm_radio = CCMenuItemImage::itemFromNormalImage("MainMenu/radio.png","MainMenu/radio.png",this,menu_selector(MainMenuLayer::itm_radioCallback));
	itm_radio->setAnchorPoint(ccp(0.5f,0.0f));
	mn_radio = CCMenu::menuWithItem(itm_radio);
	addChild(mn_radio,0, ID_RADIO);
	mn_radio->setPosition(ccp(100,25));
    */
    
	/*
	CCSprite* pS_bk = CCSprite::create("mmdot/bk.png");
	addChild(pS_bk,1);
	pS_bk->setPosition(ccp(x,y));

	pS_Light = CCSprite::create("mmdot/l.png");
	addChild(pS_Light,0);
	pS_Light->setPosition(ccp(x,y));

	CCFiniteTimeAction* seq = CCSequence::create(CCDelayTime::create(2.0f), CCCallFunc::create(this,callfunc_selector(MainMenuLayer::ShowBlickCallback)), NULL);
	this->runAction(CCRepeatForever::create((CCActionInterval*)seq));
	*/
    
layerSN_icons *lSN = new layerSN_icons();
addChild(lSN);
}
void MainMenuLayer::itm_radioCallback(CCObject* pSender)
{
	RadioOn(radio_active);
}
void MainMenuLayer::RadioOn(int active)
{
	if(!radio_active)
	{
	CCActionInterval* ai_scale_in = CCEaseInOut::create(CCScaleTo::create(0.3f,1.0f,1.05f),2.0f);
	CCActionInterval* ai_scale_out = CCEaseInOut::create(CCScaleTo::create(0.2f,1.0f,1.0f),2.0f);
	
	CCActionInterval* ai_scale2_in = CCEaseInOut::create(CCScaleTo::create(0.3f,1.0f,1.1f),2.0f);
	CCActionInterval* ai_scale2_out = CCEaseInOut::create(CCScaleTo::create(0.2f,1.0f,1.0f),2.0f);

	CCActionInterval* ai_skew_ri = CCEaseInOut::create(CCSkewTo::create(0.3f,4.1f,1.0f),2.0f);
	CCActionInterval* ai_skew_ro = CCEaseInOut::create(CCSkewTo::create(0.2f,1.0f,1.0f),2.0f);	

	CCActionInterval* ai_skew_li = CCEaseInOut::create(CCSkewTo::create(0.3f,-1.1f,1.0f),2.0f);
	CCActionInterval* ai_skew_lo = CCEaseInOut::create(CCSkewTo::create(0.2f,1.0f,1.0f),2.0f);

	CCFiniteTimeAction* fta1 = CCSequence::create(ai_scale_in,ai_scale_out,ai_scale2_in,ai_scale2_out,NULL);
	CCFiniteTimeAction* fta2 = CCSequence::create(ai_skew_ri,ai_skew_ro,ai_skew_li,ai_skew_lo,NULL);
	CCFiniteTimeAction* fta3 = CCSequence::create(CCDelayTime::create(0.5f), CCCallFunc::create(this,callfunc_selector(MainMenuLayer::ShowTonesCallback)), NULL);

	itm_radio->runAction(CCRepeatForever::create((CCActionInterval*)fta1));
	itm_radio->runAction(CCRepeatForever::create((CCActionInterval*)fta2));
	itm_radio->runAction(CCRepeatForever::create((CCActionInterval*)fta3));

	//preload background music and effect
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSIC_MAIN);
	//SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCFileUtils::fullPathFromRelativePath(MUSIC_GAME) );
	//SimpleAudioEngine::sharedEngine()->preloadEffect( CCFileUtils::fullPathFromRelativePath(EFFECT_FILE) );
    
    //set default volume
    //SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
    //SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(-1.5f);
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic((MUSIC_MAIN), true);
	radio_active++;
	}
	else
	{
		itm_radio->stopAllActions();
		itm_radio->retain();
        itm_radio->setScale(1.0f);
        itm_radio->setSkewX(1.0f);
        itm_radio->setSkewY(1.0f);
		radio_active=0;
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
}
void MainMenuLayer::itm_ContinueCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->popScene();
    
    PLAYEFFECT(_sndButton_plastik)
}
void MainMenuLayer::itm_StartCallback(CCObject* pSender)
{
	CCScene* pS_SubMenuScene = CCScene::create();
	CCLayer* pL_SubMenu = new SubMenu();
	pS_SubMenuScene->addChild(pL_SubMenu);
	CCScene* s = CCTransitionFade::create((1.0f), pS_SubMenuScene);
	pL_SubMenu->release();
	CCDirector::sharedDirector()->pushScene(s);
    
    PLAYEFFECT(_sndButton_plastik)
}

void MainMenuLayer::itm_CreditsCallback(CCObject* pSender)
{
	CCScene* pS_CreditsScene = CCScene::create();
	CCLayer* pL_CreditsLayer = new Credits();
	pS_CreditsScene->addChild(pL_CreditsLayer,0);
	CCScene* s = CCTransitionFade::create((1.0f), pS_CreditsScene);
	pL_CreditsLayer->release();
	CCDirector::sharedDirector()->pushScene(s);
    
    PLAYEFFECT(_sndButton_plastik)
}

void MainMenuLayer::ShowTonesCallback()
{
	ShowTones(itm_radio);
}
void MainMenuLayer::ShowTones(CCMenuItemImage* parent)
{
	//float x = 0.0f;
	float S = parent->getContentSize().width;
	float H = parent->getContentSize().height;

	//Tones
	CCSprite* tones[3];
	tones[0] = CCSprite::create("MainMenu/tone1.png");
	tones[1] = CCSprite::create("MainMenu/tone2.png");
	tones[2] = CCSprite::create("MainMenu/tone3.png");
	int currentTone = rand()%3;
	float moveParameter = 1.2f-(rand()%4)/10;

	CCActionInterval* ai_movedown = CCMoveTo::create(moveParameter,ccp(S-rand()%(int)(2*S),H+50));
	CCActionInterval* ai_rotate = CCRotateBy::create(0.4f,-30.0);
	CCActionInterval* ai_rotate_back = ai_rotate->reverse();
	CCActionInterval* ai_fade_out = CCFadeOut::create(moveParameter);

	parent->addChild(tones[currentTone],0,ID_TONE);
	tones[currentTone]->setAnchorPoint(ccp(0.5,1.0));
	tones[currentTone]->setPosition(ccp(parent->getContentSize().width/2-rand()%(int)S/2,parent->getPosition().y+H/2));
	tones[currentTone]->setRotation(30.0f);

	CCFiniteTimeAction* seq = CCSequence::create(ai_rotate,ai_rotate_back, NULL);
	CCFiniteTimeAction* seq2 = CCSequence::create((CCActionInterval*)ai_movedown->copy()->autorelease(),CCCallFunc::create(this,callfunc_selector(MainMenuLayer::ToneTerminateCallback)),NULL);
	tones[currentTone]->runAction(CCRepeatForever::create((CCActionInterval*)seq));
	tones[currentTone]->runAction(seq2);
	tones[currentTone]->runAction((CCActionInterval*)ai_fade_out->copy()->autorelease());
}
void MainMenuLayer::ToneTerminateCallback()
{
	((CCMenuItemImage*)(this->getChildByTag(ID_RADIO)))->removeChildByTag(ID_TONE,1);
}

void MainMenuLayer::ShowBlickCallback()
{
	ShowBlick(pS_Light, "mmdot/dot.png",3.0f,10);
}
void MainMenuLayer::ShowBlick(CCSprite* parent, const char* dot, float Time, int intensive)
{
	float x = 0.0f;
	float S = parent->getContentSize().width;
	float H = parent->getContentSize().height;

	for(int i=0;i<intensive;i++)
	{
		CCActionInterval* ai_movedown = CCMoveBy::create(120.0f-(float)(rand()%30),ccp(40-rand()%20,-H-300));
		
		CCActionInterval* ai_rotate = CCRotateBy::create(3.0f,-60.0);
		CCActionInterval* ai_rotate_back = ai_rotate->reverse();

		CCSprite* pS_dot = CCSprite::create(dot);
		parent->addChild(pS_dot);
		pS_dot->setPosition(ccp(x+rand()%(int)S,H));
		pS_dot->setScale(0.3f-(float)(rand()%3)/10.0f);
		pS_dot->setAnchorPoint(ccp(0.5f,7.0f));
		pS_dot->setRotation(30.0f);
		//pS_dot->setOpacity(0);

		CCFiniteTimeAction* seq = CCSequence::create(ai_rotate,ai_rotate_back, NULL);

		pS_dot->runAction(CCRepeatForever::create((CCActionInterval*)seq));
		
		pS_dot->runAction((CCActionInterval*)ai_movedown->copy()->autorelease());
	}
}