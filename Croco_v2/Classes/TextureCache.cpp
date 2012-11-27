//
//  TextureCache.cpp
//  Croco
//
//  Created by admin on 18.07.12.
//
//

#include "TextureCache.h"
#include "MainMenuLayer.h"

using namespace cocos2d;

TextureCacheLayer::TextureCacheLayer()
: m_nNumberOfSprites(71)
, m_nNumberOfLoadedSprites(0)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pS_background = CCSprite::create("MainMenu/preload.png");
    addChild(pS_background);
    pS_background->setPosition(CCPointMake(size.width/2, size.height/2));
    
    m_pLabelLoading = CCLabelTTF::create("Загрузка..", "fonts/neucha.ttf", 30);
	m_pLabelPercent = CCLabelTTF::create("%0", "fonts/neucha.ttf", 30);
    
	m_pLabelLoading->setPosition(CCPointMake(size.width / 2, size.height / 2 - 100));
	m_pLabelPercent->setPosition(CCPointMake(size.width / 2, size.height / 2 - 140));
    
	this->addChild(m_pLabelLoading);
	this->addChild(m_pLabelPercent);
    
	//Load textrues
    //MainMenu 1
	ADDIMAGE(MainMenu_background)
    //GroupCustomization 12
    ADDIMAGE(GroupCustomization_start)
    ADDIMAGE(GroupCustomization_start_selected)
    ADDIMAGE(GroupCustomization_back)
    ADDIMAGE(GroupCustomization_back_selected)
    ADDIMAGE(GroupCustomization_blue)
    ADDIMAGE(GroupCustomization_green)
    ADDIMAGE(GroupCustomization_red)
    ADDIMAGE(GroupCustomization_yellow)
    ADDIMAGE(GroupCustomization_stripe)
    ADDIMAGE(GroupCustomization_dot)
    ADDIMAGE(GroupCustomization_lead_choise_colors);
    //Timer 11
    ADDIMAGE(Timer_itm_timer_norm)
    ADDIMAGE(Timer_itm_timer_norm_light)
    ADDIMAGE(Timer_itm_timer_run_norm)
    ADDIMAGE(Timer_itm_timer_run_sel)
    ADDIMAGE(Timer_itm_timer_sel)
    ADDIMAGE(Timer_itm_timer_stop_norm)
    ADDIMAGE(Timer_itm_timer_stop_sel)
    ADDIMAGE(Timer_timer_digits_active)
    ADDIMAGE(Timer_timer_digits_light)
    ADDIMAGE(Timer_timer_digits_passive)
    ADDIMAGE(Timer_timer_forest)
    //Desk 2
    ADDIMAGE(_desk)
    ADDIMAGE(_c_big)
    //GameMenu 11
    ADDIMAGE(GameMenu_gamemenu)
    ADDIMAGE(GameMenu_help)
    ADDIMAGE(GameMenu_menu_button_a)
    ADDIMAGE(GameMenu_menu_button)
    ADDIMAGE(GameMenu_menu_forward_a)
    ADDIMAGE(GameMenu_menu_forward)
    ADDIMAGE(GameMenu_menu_button)
    ADDIMAGE(GameMenu_menu_rewind_a)
    ADDIMAGE(GameMenu_menu_rewind)
    ADDIMAGE(GameMenu_sound)
    ADDIMAGE(GameMenu_swipe)
    //RightControl 19
    ADDIMAGE(RightControl_c3_hybrid)
    ADDIMAGE(RightControl_c3)
    ADDIMAGE(RightControl_c3bottom)
    ADDIMAGE(RightControl_c3div)
    ADDIMAGE(RightControl_c4_hybrid)
    ADDIMAGE(RightControl_c4)
    ADDIMAGE(RightControl_c4div)
    ADDIMAGE(RightControl_c4bottom)
    ADDIMAGE(RightControl_c5_hybrid)
    ADDIMAGE(RightControl_c5)
    ADDIMAGE(RightControl_c5bottom)
    ADDIMAGE(RightControl_c5div)
    ADDIMAGE(RightControl_itm_no_norm)
    ADDIMAGE(RightControl_itm_other_norm)
    ADDIMAGE(RightControl_itm_yes_norm)
    ADDIMAGE(RightControl_c_blank0)
    ADDIMAGE(RightControl_c_blank1)
    ADDIMAGE(RightControl_c_blank2)
    ADDIMAGE(RightControl_c_blank3)
    //RewindAnimation 2
    ADDIMAGE(RewindAnimation_rewind)
    ADDIMAGE(RewindAnimation_rewind2)
    //Tokens 5
    ADDIMAGE(tokens_token_blue)
    ADDIMAGE(tokens_token_green)
    ADDIMAGE(tokens_token_red)
    ADDIMAGE(tokens_token_yellow)
    ADDIMAGE(tokens_token_shadow)
    //SubMenu 6
    ADDIMAGE(SubMenu_3gamers)
    ADDIMAGE(SubMenu_3groups)
    ADDIMAGE(SubMenu_2groups)
    ADDIMAGE(SubMenu_4groups)
    ADDIMAGE(SubMenu_lead_choise_groups)
    ADDIMAGE(SubMenu_hint_bottom)
    //SN_icons 3
    ADDIMAGE(SN_icons_facebook_icon)
    ADDIMAGE(SN_icons_twitter_icon)
    ADDIMAGE(SN_icons_vkontakte_icon)
    
    //load music and effects
    //preload background music and effect
	ADDBGMUSIC(MUSIC_MAIN)
	ADDEFFECT(_sndAlert)
    ADDEFFECT(_sndButton_group)
    ADDEFFECT(_sndButton_inputname_end)
    ADDEFFECT(_sndButton_inputname_start)
    ADDEFFECT(_sndButton_plastik)
    ADDEFFECT(_sndButton_timer)
    ADDEFFECT(_sndButton_wood)
    ADDEFFECT(_sndCamera)
    ADDEFFECT(_sndCheckcard)
    ADDEFFECT(_sndForall)
    ADDEFFECT(_sndMovescreen)
    ADDEFFECT(_sndSwipe)
    ADDEFFECT(_sndTimer)
    ADDEFFECT(_sndToken)
    ADDEFFECT(_sndVictory)
    
    //set default volume
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
}

void TextureCacheLayer::loadingCallBack(CCObject *obj)
{
    loadMainMenu();
    
    /*
	++m_nNumberOfLoadedSprites;
	char tmp[10];
	sprintf(tmp,"%%%d", (int)(((float)m_nNumberOfLoadedSprites / m_nNumberOfSprites) * 100));
	m_pLabelPercent->setString(tmp);
    
	if (m_nNumberOfLoadedSprites == m_nNumberOfSprites)
	{
		loadMainMenu();
	}*/
}

void TextureCacheLayer::loadMainMenu()
{
	CCScene* pS_MainMenuScene = CCScene::create();
    CCLayer* pL_MainMenu = new MainMenuLayer(0);
    pS_MainMenuScene->addChild(pL_MainMenu,0);
    pL_MainMenu->release();
    CCDirector::sharedDirector()->pushScene(pS_MainMenuScene);
}
