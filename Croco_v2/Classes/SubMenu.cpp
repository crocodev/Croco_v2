#include "SubMenu.h"
#include "GroupCustomization.h"

SubMenu::SubMenu(void)
{
	//set center of the screen
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	float x = size.width/2;
        float y = size.height/2;

	//add background sprite
	CCSprite* background = CCSprite::spriteWithFile(MainMenu_background);
	addChild(background,0);
	background->setPosition(ccp(x,y));

	//add leather
	CCSprite* lth = CCSprite::spriteWithFile(SubMenu_lead_choise_groups);
    addChild(lth,0);
    lth->setAnchorPoint(ccp(0.5,1));
	lth->setPosition(ccp(x,y*2));
    
	//menu icons
	CCMenuItem* itm_3gamers = CCMenuItemImage::itemWithNormalImage(SubMenu_3gamers,SubMenu_3gamers,this,menu_selector(SubMenu::itm_3gamersCallback));
	CCMenuItem* itm_2groups = CCMenuItemImage::itemWithNormalImage(SubMenu_2groups,SubMenu_2groups,this,menu_selector(SubMenu::itm_2groupsCallback));
	CCMenuItem* itm_3groups = CCMenuItemImage::itemWithNormalImage(SubMenu_3groups,SubMenu_3groups,this,menu_selector(SubMenu::itm_3groupsCallback));
	CCMenuItem* itm_4groups = CCMenuItemImage::itemWithNormalImage(SubMenu_4groups,SubMenu_4groups,this,menu_selector(SubMenu::itm_4groupsCallback));
	CCMenuItem* itm_back = CCMenuItemImage::itemWithNormalImage(GroupCustomization_back,GroupCustomization_back_selected,this,menu_selector(SubMenu::itm_backCallback));
	CCMenu* menu = CCMenu::menuWithItems(itm_3gamers,itm_2groups,itm_3groups,itm_4groups,itm_back,NULL);
	addChild(menu);
	itm_3gamers->setPosition(ccp(-(y*2/3.5),+(x*2/7.5)));
	itm_2groups->setPosition(ccp(+(y*2/3.5),+(x*2/7.5)));
	itm_3groups->setPosition(ccp(-(y*2/3.5),-(x*2/7.5)));
	itm_4groups->setPosition(ccp(+(y*2/3.5),-(x*2/7.5)));
	itm_back->setPosition(ccp(-(x*2/2.2),-(y*2/2.22)));
	menu->setPosition(CCPointMake(x,y));
}
void SubMenu::itm_3gamersCallback(CCObject* pSender)
{
	GoGroupCustomization(GAMERS_3);
    
    PLAYEFFECT(_sndButton_group)
}
void SubMenu::itm_2groupsCallback(CCObject* pSender)
{
	GoGroupCustomization(GROUP_2);
    
    PLAYEFFECT(_sndButton_group)
}
void SubMenu::itm_3groupsCallback(CCObject* pSender)
{
	GoGroupCustomization(GROUP_3);
    
    PLAYEFFECT(_sndButton_group)
}
void SubMenu::itm_4groupsCallback(CCObject* pSender)
{
	GoGroupCustomization(GROUP_4);
    
    PLAYEFFECT(_sndButton_group)
}
void SubMenu::GoGroupCustomization(int GameMode)
{
	CCScene* pScene = CCScene::create();
	CCLayer* pLayer = new GroupCustomization(GameMode);
	pScene->addChild(pLayer,0);
	CCScene* s = CCTransitionFade::transitionWithDuration(1.0f, pScene);
	pLayer->release();
	CCDirector::sharedDirector()->pushScene(s);
}
void SubMenu::itm_backCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->popScene();
    
    PLAYEFFECT(_sndButton_plastik)
}