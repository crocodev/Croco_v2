#include "AppDelegate.h"

#include "CrocoBoardGame.h"
#include "GroupCustomization.h"
#include "MainMenuLayer.h"

#include "math.h"

CellTable::CellTable(int id, float x, float y, char activity, int F)
{
	m_Id = id;
	m_X=x; m_Y=y;
	m_Activity=activity;
	m_F=F;
}
void CellTable::ChangeCellF(int F)
{
	m_F^=F;
}
/*
 layer	- ÒÎÓÈ, Ì‡ ÍÓÚÓ˚È ‰Ó·‡‚ÎˇÂÚÒˇ ÙË¯Í‡;
 ps		- ÒÔ‡ÈÚ ÙË¯ÍË;
 pss		- ÒÔ‡ÈÚ ÚÂÌË ÙË¯ÍË
 cs		- ÚÂÍÛ˘‡ˇ ÔÓÁËˆËˇ ‚ Ú‡·ÎËˆÂ ÍÓÓ‰ËÌ‡Ú
 pos		- ÔÓÁËˆËˇ ‚ ÔËÍÒÂÎˇı ÔË ËÌËˆË‡ÎËÁ‡ˆËË
 */
SpriteTokenClass::SpriteTokenClass(ActionLayer* layer, CCSprite* ps, CCSprite* pss, int cs, CCPoint pos)
{
    act=layer;
    ingame=1;
	pS_FShadow = pss;
	pS_F = ps;
	layer->addChild(ps,1);
	layer->addChild(pss,2);
	ps->setPosition(pos);
	pss->setPosition(pos);
	
	pss->setScale(0.24f);
	ps->setScale(0.3f);
	pss->setPosition(pos);
	pss->setAnchorPoint(ccp(0.5,0.1));
	pss->setPosition(pos);
	pss->setScaleX(0.24f);
	pss->setScaleY(0.76f*pos.y/LUM_Y+0.15f);
	pss->setRotation(atan((pos.x-LUM_X)/LUM_Y)*180.0f/PI);
    
	m_CurrentPosition=cs;
}
void SpriteTokenClass::setCurrentPos(int pos)
{
	this->m_CurrentPosition=pos;
}
bool SpriteTokenClass::tokenIsActive()
{
    if(ingame) return true; else return false;
}
void SpriteTokenClass::removeToken()
{
    ingame = 0;
    pS_F->setVisible(false);
    pS_FShadow->setVisible(false);
    //pS_F->removeFromParentAndCleanup(true);
    //pS_FShadow->removeFromParentAndCleanup(true);
    act->ChangeSelectorCallback((CCObject*)act);
    act->allactivetokens--;
}


ActionLayer::~ActionLayer()
{
	delete(dbw);
}

ActionLayer::ActionLayer()
{
}

ActionLayer::ActionLayer(int GameMode, std::string *RedName, std::string *GreenName, std::string *BlueName, std::string *YellowName)
{
    dbw = new DBWord("cards.xml");
    
	//game mode
	m_GameMode = GameMode;
	m_RedName = RedName;
	m_GreenName = GreenName;
	m_BlueName = BlueName;
	m_YellowName = YellowName;
    
    //Готовность взять карту
    gamestate = 0;
    
	//screen center
    size = CCDirector::sharedDirector()->getWinSize();
	x = size.width/2;
    y = size.height/2;
    
	//init tokens
	//numGroupsInGame
#define R_X         835.0
#define R_Y         690.0
#define G_X         870.0
#define G_Y         630.0
#define B_X         915.0
#define B_Y         690.0
#define Y_X         951.0
#define Y_Y         630.0
	switch(m_GameMode)
	{
		case GAMERS_3:
			tokens[0] = new SpriteTokenClass(this,CCSprite::create(tokens_token_red),CCSprite::create(tokens_token_shadow),0,ccp(R_X,R_Y)); tokens[0]->pS_F->setTag(ID_RED); tokens[0]->m_groupname=RedName;
			tokens[1] = new SpriteTokenClass(this,CCSprite::create(tokens_token_green),CCSprite::create(tokens_token_shadow),0,ccp(G_X,G_Y)); tokens[1]->pS_F->setTag(ID_GREEN);	tokens[1]->m_groupname=GreenName;
			tokens[2] = new SpriteTokenClass(this,CCSprite::create(tokens_token_blue),CCSprite::create(tokens_token_shadow),0,ccp(B_X,B_Y)); tokens[2]->pS_F->setTag(ID_BLUE); tokens[2]->m_groupname=BlueName;
			groups[0].CurGroupPosition(0);	groups[0].NextGroupPtr(&groups[1]);
			groups[1].CurGroupPosition(0);	groups[1].NextGroupPtr(&groups[2]);
			groups[2].CurGroupPosition(0);	groups[2].NextGroupPtr(&groups[0]);
			numGroupsInGame=3;break;
		case GROUP_2:
			tokens[0] = new SpriteTokenClass(this,CCSprite::create(tokens_token_red),CCSprite::create(tokens_token_shadow),0,ccp(R_X,R_Y)); tokens[0]->pS_F->setTag(ID_RED); tokens[0]->m_groupname=RedName;
			tokens[1] = new SpriteTokenClass(this,CCSprite::create(tokens_token_green),CCSprite::create(tokens_token_shadow),0,ccp(G_X,G_Y)); tokens[1]->pS_F->setTag(ID_GREEN);	tokens[1]->m_groupname=GreenName;
			groups[0].CurGroupPosition(0);	groups[0].NextGroupPtr(&groups[1]);
			groups[1].CurGroupPosition(0);	groups[1].NextGroupPtr(&groups[0]);
			numGroupsInGame=2;break;
		case GROUP_3:
			tokens[0] = new SpriteTokenClass(this,CCSprite::create(tokens_token_red),CCSprite::create(tokens_token_shadow),0,ccp(R_X,R_Y)); tokens[0]->pS_F->setTag(ID_RED); tokens[0]->m_groupname=RedName;
			tokens[1] = new SpriteTokenClass(this,CCSprite::create(tokens_token_green),CCSprite::create(tokens_token_shadow),0,ccp(G_X,G_Y)); tokens[1]->pS_F->setTag(ID_GREEN);	tokens[1]->m_groupname=GreenName;
			tokens[2] = new SpriteTokenClass(this,CCSprite::create(tokens_token_blue),CCSprite::create(tokens_token_shadow),0,ccp(B_X,B_Y)); tokens[2]->pS_F->setTag(ID_BLUE); tokens[2]->m_groupname=BlueName;
			groups[0].CurGroupPosition(0);	groups[0].NextGroupPtr(&groups[1]);
			groups[1].CurGroupPosition(0);	groups[1].NextGroupPtr(&groups[2]);
			groups[2].CurGroupPosition(0);	groups[2].NextGroupPtr(&groups[0]);
			numGroupsInGame=3;break;
		case GROUP_4:
			tokens[0] = new SpriteTokenClass(this,CCSprite::create(tokens_token_red),CCSprite::create(tokens_token_shadow),0,ccp(R_X,R_Y)); tokens[0]->pS_F->setTag(ID_RED); tokens[0]->m_groupname=RedName;
			tokens[1] = new SpriteTokenClass(this,CCSprite::create(tokens_token_green),CCSprite::create(tokens_token_shadow),0,ccp(G_X,G_Y)); tokens[1]->pS_F->setTag(ID_GREEN);	tokens[1]->m_groupname=GreenName;
			tokens[2] = new SpriteTokenClass(this,CCSprite::create(tokens_token_blue),CCSprite::create(tokens_token_shadow),0,ccp(B_X,B_Y)); tokens[2]->pS_F->setTag(ID_BLUE); tokens[2]->m_groupname=BlueName;
			tokens[3] = new SpriteTokenClass(this,CCSprite::create(tokens_token_yellow),CCSprite::create(tokens_token_shadow),0,ccp(Y_X,Y_Y)); tokens[3]->pS_F->setTag(ID_YELLOW); tokens[3]->m_groupname=YellowName;
			groups[0].CurGroupPosition(0);	groups[0].NextGroupPtr(&groups[1]);
			groups[1].CurGroupPosition(0);	groups[1].NextGroupPtr(&groups[2]);
			groups[2].CurGroupPosition(0);	groups[2].NextGroupPtr(&groups[3]);
			groups[3].CurGroupPosition(0);	groups[3].NextGroupPtr(&groups[0]);
			numGroupsInGame=4;break;
	}
	for (int i = 0; i < numGroupsInGame; i++)
		tokens[i]->m_CurNumber = i;
    
    allactivetokens = numGroupsInGame;
    
	//randomize start
	srand((unsigned)time(NULL));
	current_group=rand()%numGroupsInGame;
	active_token = tokens[current_group];
	curGroupPtr = &groups[current_group];
    
	// push to vec
	CGroupsSnapshot gs(groups);
	snaps.PushSnapshot(gs);
	snaps.IncCurAct();
    
	// game logic
	gl.setActionLayerPtr(this);
	gl.StartGame();
    
	
    //Таблица действий для каждой ячейки
    char create[45]={'O','R','P','O','O','P','O','R','P','O',
        'R','O','R','P','P','R','O','P','P','P',
        'R','R','R','P','R','O','P','O','P','O',
        'R','R','R','P','P','O','P','R','R','P',
        'R','O','O','P','O'};
	//Таблица координат ячеек в пикселях
    float mtx[45][2] = {
        {746,662},
        {661,662},
        {579,662},
        {496,662},
        {408,662},
        {323,662},
        {238,662},
        //7
        {141,641},
        {141,549},
        //2
        {238,521},
        {323,521},
        {408,521},
        {496,521},
        {579,521},
        {661,521},
        //6
        {741,511},
        {741,451},
        //2
        {661,439},
        {579,439},
        {496,439},
        {408,439},
        //4
        {324,424},
        {324,347},
        //2
        {408,329},
        {496,329},
        {579,329},
        {661,329},
        //4
        {741,317},
        {741,256},
        //2
        {661,245},
        {579,245},
        {496,245},
        {408,245},
        {323,245},
        {238,245},
        //6
        {141,222},
        {141,126},
        //2
        {238,105},
        {323,105},
        {408,105},
        {496,105},
        {579,105},
        {661,105},
        {746,105},
        {883,105},
        //8
    };//45
    
	//»ÌËˆË‡ÎËÁ‡ˆËˇ Ú‡·ÎËˆ˚
	for(int i=0;i<TABLEMAX;i++)
    {
        tbl[i] = new CellTable(i,mtx[i][0],mtx[i][1],create[i],0);
    }
    
	//tbl[0]->ChangeCellF(15);
    
	//Игровое поле
	CCSprite* sDesk=CCSprite::create(_desk);
	addChild(sDesk,0);
	sDesk->setPosition(CCPointMake(x,y));
    
	//GameMenu
	CCMenuItemImage* itm_rewind = CCMenuItemImage::create(GameMenu_menu_rewind,GameMenu_menu_rewind_a,this,menu_selector(ActionLayer::itm_rewindCallback));
	CCMenuItemImage* itm_gamemenu = CCMenuItemImage::create(GameMenu_menu_button,GameMenu_menu_button_a,this, menu_selector(ActionLayer::itm_gamemenuCallback));
	CCMenuItemImage* itm_forward = CCMenuItemImage::create(GameMenu_menu_forward,GameMenu_menu_forward_a,this, menu_selector(ActionLayer::itm_forwardCallback));
	game_menu = CCMenu::create(itm_rewind,itm_gamemenu, itm_forward, NULL);
	game_menu->alignItemsHorizontallyWithPadding(60);
	addChild(game_menu);
	game_menu->setPosition(ccp(x,18));
    
	//TestMenu
	CCMenuItemFont* item1 = CCMenuItemFont::create("go 3", this, menu_selector(ActionLayer::Card3Callback));
	CCMenuItemFont* item2 = CCMenuItemFont::create("go 4", this, menu_selector(ActionLayer::Card4Callback));
	CCMenuItemFont* item3 = CCMenuItemFont::create("go 5", this, menu_selector(ActionLayer::Card5Callback));
	CCMenuItemFont* itemA = CCMenuItemFont::create("go -1", this, menu_selector(ActionLayer::GoBackOneCallback));
	CCMenuItemFont* item4 = CCMenuItemFont::create("change token", this, menu_selector(ActionLayer::ChangeSelectorCallback));
	menu_question = CCMenu::create(item1,item2, item3, itemA, item4, NULL);
	menu_question->alignItemsVertically();
	addChild(menu_question);
	menu_question->setPosition(CCPointMake(x+200,y-200));
    
	//Cards
	itm_card3 = CCMenuItemImage::create(RightControl_c3,RightControl_c3,this,menu_selector(ActionLayer::itm_card3Callback));
	itm_card4 = CCMenuItemImage::create(RightControl_c4,RightControl_c4,this,menu_selector(ActionLayer::itm_card4Callback));
	itm_card5 = CCMenuItemImage::create(RightControl_c5,RightControl_c5,this,menu_selector(ActionLayer::itm_card5Callback));
	mn_Cards = CCMenu::create(itm_card5, itm_card4, itm_card3, NULL);
	mn_Cards->alignItemsVerticallyWithPadding(CARD_PADDING);
	addChild(mn_Cards);
	m_mnCardsX=x+CARD_OFFSET_X;
	m_mnCardsY=y+CARD_OFFSET_Y;
	mn_Cards->setPosition(CCPointMake(m_mnCardsX,m_mnCardsY));
	mn_Cards->setVisible(1);
	mn_Cards->setTouchEnabled(true);
    
	//Answers
	itm_yes = CCMenuItemImage::create(RightControl_itm_yes_norm,RightControl_itm_yes_norm,this,menu_selector(ActionLayer::itm_yesCallback));
	itm_no = CCMenuItemImage::create(RightControl_itm_no_norm,RightControl_itm_no_norm,this,menu_selector(ActionLayer::itm_noCallback));
	itm_other = CCMenuItemImage::create(RightControl_itm_other_norm,RightControl_itm_other_norm,this,menu_selector(ActionLayer::itm_otherCallback));
	itm_other->setTag(RED);
	mn_Answers = CCMenu::create(itm_yes, itm_no, itm_other, NULL);
	mn_Answers->alignItemsVerticallyWithPadding(CARD_PADDING);
	addChild(mn_Answers);
	mn_Answers->setPosition(ccp(m_mnCardsX,m_mnCardsY));
	mn_Answers->setVisible(false);
    
	//Timer
	//stop timer
	pL_Timer = CCLayer::create();
	addChild(pL_Timer,0);
	pL_Timer->setPosition(ccp(-120,y)); //-110
    //timer
	CCSprite* pS_TimerDesk = CCSprite::create(Timer_timer_forest);
	pL_Timer->addChild(pS_TimerDesk,1);
    //timer_digits
	CCSprite* pS_Timer_digits = CCSprite::create(Timer_timer_digits_passive);
	pL_Timer->addChild(pS_Timer_digits,1);
	pS_Timer_digits->setPosition(ccp(11,-3));
    //timer_digits_light
	CCSprite* pS_Timer_digits_l = CCSprite::create(Timer_timer_digits_light);
	pS_Timer_digits_l->setOpacity(255);
	pL_Timer->addChild(pS_Timer_digits_l,3,ID_DIGITS_L);
	pS_Timer_digits_l->setPosition(ccp(-4,-24));
    //button
	itm_Timer_start = CCMenuItemImage::create(Timer_itm_timer_norm,Timer_itm_timer_sel,this,menu_selector(ActionLayer::itm_TimerStartCallback));
	itm_Timer_pause = CCMenuItemImage::create(Timer_itm_timer_stop_norm,Timer_itm_timer_stop_sel,this,menu_selector(ActionLayer::itm_TimerPauseCallback));
	itm_Timer_run = CCMenuItemImage::create(Timer_itm_timer_run_norm,Timer_itm_timer_run_sel,this,menu_selector(ActionLayer::itm_TimerRunCallback));
	mn_Timer = CCMenu::create(itm_Timer_start,itm_Timer_pause,itm_Timer_run,NULL);
	pL_Timer->addChild(mn_Timer,3);
	mn_Timer->setPosition(ccp(8,-8));
	itm_Timer_pause->setVisible(false);
	itm_Timer_run->setVisible(false);
    //button_light
	CCSprite* pS_Timer_button_l = CCSprite::create(Timer_itm_timer_norm_light);
	pS_Timer_button_l->setOpacity(100);
	pL_Timer->addChild(pS_Timer_button_l,3,ID_BUTTON_L);
	pS_Timer_button_l->setPosition(ccp(3,-12));
    
	//audio
    /*
     SimpleAudioEngine::sharedEngine()->playBackgroundMusic(std::string(CCFileUtils::fullPathFromRelativePath(MUSIC_GAME)).c_str(), true);
     */
	/*
     CCSprite* anim = CCSprite::create("sonic.png");
     addChild(anim);
     anim->setPosition(ccp(x-200,y));
     
     CCAnimation* ca = CCAnimation::animation();
     char frameName[100] = {0};
     for(int i=1;i<4;i++)
     {
     sprintf(frameName, "anim/h_%d.png", i);
     ca->addFrameWithFileName(frameName);
     }
     
     CCActionInterval*  action = CCAnimate::create(2, ca, false);
     CCActionInterval*  action_back = action->reverse();
     anim->runAction( CCSequence::create( action, action_back, NULL));
     */
}

//GameMenuCallbacks
void ActionLayer::itm_rewindCallback(CCObject* pSender)
{
	if(!mn_Cards->isTouchEnabled())
	{
		mn_WhoAnswer->setVisible(0);
		mn_Cards->setVisible(1);
		mn_Cards->setTouchEnabled(1);
        
		HideTimer();
		DropCard();
		//RewindAnimation(this); //rewind animation
		return;
	}
    
	int chPos, actGlobal;
	actGlobal = snaps.getCurActGlobal();
	while(actGlobal == snaps.getCurActGlobal())
	{
		CGroupsSnapshot oldGs, curGs;
		snaps.GetSnapshot(curGs);
		snaps.PopSnapshot(oldGs);
		if((chPos = curGs.CompareSnapshots(&oldGs, current_group)))
		{
			curGroupPtr = &groups[current_group];
			curGroupPtr->ChangeCurGroupPos(chPos);
			active_token = tokens[current_group];
			FMove(active_token, chPos);
			RewindAnimation(this); //rewind animation
            
            PLAYEFFECT(_sndButton_wood)
		}
		else
			break;
	}
    
	gl.ContinueGame();
}
void ActionLayer::itm_gamemenuCallback(CCObject* pSender)
{
    SaveMenuState();
	CCLayerColor* lc = CCLayerColor::create();
	lc->setOpacity(165.0f);
	addChild(lc,5,ID_SHADOWLAYER);
	//lc->runAction(CCEaseIn::create(CCFadeTo::create(0.4f,165),0.8f));
    
	GameMenuLayer* pL_GameMenu = new GameMenuLayer();
	this->addChild(pL_GameMenu,6, ID_GAMEMENU);
    
    PLAYEFFECT(_sndButton_wood)
}
void ActionLayer::itm_forwardCallback(CCObject* pSender)
{
	// Í‡ÚÛ ‚ÁˇÚ¸ ???
	/*
     if(!mn_Cards->getIsTouchEnabled())
     {
     mn_WhoAnswer->setIsVisible(0);
     mn_Cards->setIsVisible(1);
     mn_Cards->setIsTouchEnabled(1);
     
     HideTimer();
     DropCard();
     return;
     }*/
	if(snaps.CheckZero())
		return;
	
	int chPos, actGlobal;
	actGlobal = snaps.getFCurActGlobal();
	while(actGlobal == snaps.getFCurActGlobal())
	{
		CGroupsSnapshot newGs, curGs;
		snaps.GetSnapshot(curGs);
		snaps.PopFSnapshot(newGs);
		//CGroupsSnapshot oldGs, curGs(groups);
		//snaps.PopSnapshot(oldGs);
		if((chPos = curGs.CompareSnapshots(&newGs, current_group)))
		{
			curGroupPtr = &groups[current_group];
			curGroupPtr->ChangeCurGroupPos(chPos);
			active_token = tokens[current_group];
			FMove(active_token, chPos);
			RewindAnimation(this); //rewind animation
            
            PLAYEFFECT(_sndButton_wood)
		}
		else
			break;
        
		gl.ContinueGame();
	}
    /*
     CGroupsSnapshot newGs, curGs(groups);
     snaps.PopFSnapshot(newGs);
     
     int chPos;
     while(chPos = curGs.CompareSnapshots(&newGs, current_group))
     {
     curGroupPtr = &groups[current_group];
     curGroupPtr->ChangeCurGroupPos(chPos);
     active_token = tokens[current_group];
     FMove(active_token, chPos);
     }
     */
}

/*
 Mode: TR - top right, TL - top left, BR - bottom right, BL - bottom left
 */
void ActionLayer::ShowHint(int Mode, CCPoint TargetPoint, const char* TextHint)
{
	CCLayer* pL_Hint = CCLayer::create();
	addChild(pL_Hint,3,HINT_LAYER);
	CCSprite* pS_Pointer = CCSprite::create("pointer.png");
	pL_Hint->addChild(pS_Pointer);
	CCLabelTTF* txt= CCLabelTTF::create(TextHint,FONT_NAME,22.0f);
	pL_Hint->addChild(txt);
	txt->setPosition(ccp(x,y+330-txt->getContentSize().height/2));
	CCActionInterval* move1;
    
	float move_distanse=10;
    
	switch (Mode)
	{
        case TR:
            pS_Pointer->setPosition(ccp(TargetPoint.x-30,TargetPoint.y-22)); //28 20
            pS_Pointer->setRotation(-45.0f);
            move1 = CCEaseInOut::create(CCMoveBy::create(0.7f,ccp(-move_distanse,-move_distanse)),2.0f);break;
        case TL:
            pS_Pointer->setPosition(ccp(TargetPoint.x+30,TargetPoint.y-22));
            pS_Pointer->setRotation(-135.0f);
            move1 = CCEaseInOut::create(CCMoveBy::create(0.7f,ccp(+move_distanse,-move_distanse)),2.0f);break;
        case BR:
            pS_Pointer->setPosition(ccp(TargetPoint.x-30,TargetPoint.y+22));
            pS_Pointer->setRotation(38.0f);
            move1 = CCEaseInOut::create(CCMoveBy::create(0.7f,ccp(-move_distanse,+move_distanse)),2.0f);break;
        case BL:
            pS_Pointer->setPosition(ccp(TargetPoint.x+30,TargetPoint.y+22));
            pS_Pointer->setRotation(135.0f);
            move1 = CCEaseInOut::create(CCMoveBy::create(0.7f,ccp(+move_distanse,+move_distanse)),2.0f);break;
	}
    
	CCActionInterval* move2 = CCEaseInOut::create(move1->reverse(),2.0f);
	CCActionInterval* fadein = CCFadeIn::create(0.4f);
	CCActionInterval* fadeout = CCFadeOut::create(0.6f);
	
	CCFiniteTimeAction* fta = CCSequence::create((CCFiniteTimeAction*)move1->copy()->autorelease(),move2->copy()->autorelease(),NULL);
	CCFiniteTimeAction* fta2=CCSequence::create((CCActionInterval*)CCDelayTime::create(0.4f),(CCActionInterval*)CCRepeat::create((CCActionInterval*)fta,4),NULL);
	CCFiniteTimeAction* fta3 = CCSequence::create((CCFiniteTimeAction*)CCDelayTime::create(6.7f),fadeout->copy()->autorelease(),CCCallFunc::create(this,callfunc_selector(ActionLayer::ShowHintCallback)), NULL);
	pS_Pointer->runAction((CCActionInterval*)fadein->copy()->autorelease());
	txt->runAction((CCActionInterval*)fadein->copy()->autorelease());
	pS_Pointer->runAction((CCActionInterval*)fta2);
	txt->runAction((CCActionInterval*)fta3->copy()->autorelease());
	pS_Pointer->runAction((CCActionInterval*)fta3->copy()->autorelease());
}
void ActionLayer::ShowHintCallback()
{
	//”‰‡ÎˇÂÏ ÒÎÓÈ Ò ÔÓ‰ÒÍ‡ÁÍ‡ÏË
	removeChildByTag(HINT_LAYER,1);
}

void ActionLayer::GoBackOneCallback(CCObject* pSender)
{
	FMoveCor(this->active_token,-1);
	snaps.IncCurAct();
    
	//ChangeSelectorCallback(pSender);
}

void ActionLayer::CardPriceGo(CCObject* pSender)
{
	FMoveCor(this->active_token,curCardPrice);
	snaps.IncCurAct();
    
	ChangeSelectorCallback(pSender);
}

void ActionLayer::Card3Callback(CCObject* pSender)
{	/*
     FMoveCor(this->active_token,3);
     snaps.IncCurAct();
     
     ChangeSelectorCallback(pSender);
     */
    //Hint
    char text_hint[512];
    const char* hints_colors[4] = {"красная","зеленая","синяя","желтая"};
    const char* hints_create[3] = { "объясните друзьям ","покажите как выглядит ","нарисуйте на бумаге "};
    const char* hints_create_2[3] = { "объясняли ","паказывали ","рисовали "};
    switch (gamestate) {
        case 0:
            strcpy(text_hint, "Необходимо выбрать колоду и взять карту из нее. Ходит ");
            strcat(text_hint,hints_colors[current_group]);
            strcat(text_hint," команда");
            ShowHint(BR, ccp(x+CARD_OFFSET_X-CARD_WIDTH/2-40,y+CARD_HEIGHT*2-50),text_hint);
            break;
        case 1:
            strcpy(text_hint, "Прочитайте слово и ");
            strcat(text_hint,hints_create[hint_act]);
            strcat(text_hint,"понятие, которое это слово отражает. \nКак будите готовы нажмите кнопку \"Старт\" на таймере. \nВ вашем распоряжении будет 60 секунд");
            ShowHint(BL, ccp(200,y),text_hint);
            break;
        case 2:
            strcpy(text_hint, "Можете остановить ход таймера и подсмотреть слово. Если соперник угадал слово,\nкоторое вы ");
            strcat(text_hint,hints_create_2[hint_act]);
            strcat(text_hint,", нажмите на соответствующую кнопку в правой части экрана");
            ShowHint(TR, ccp(300,400),text_hint);
            break;
        case 3:
            strcpy(text_hint, "Подсмотрите слово и как будете готовы нажмите кнопку на таймере");
            ShowHint(TR, ccp(300,400),text_hint);
            break;
        default:
            break;
    }
    
    tokens[current_group]->removeToken();
    
}

void ActionLayer::Card4Callback(CCObject* pSender)
{
	FMoveCor(this->active_token,4);
	snaps.IncCurAct();
    
	ChangeSelectorCallback(pSender);
}
void ActionLayer::Card5Callback(CCObject* pSender)
{
	FMoveCor(this->active_token,5);
	snaps.IncCurAct();
    
	//ChangeSelectorCallback(pSender);
}
void ActionLayer::ChangeSelectorCallback(CCObject* pSender)
{
    pre_current_group = current_group;
    current_group=(current_group+1)%numGroupsInGame;
    if(!tokens[current_group]->tokenIsActive())
    {
        do
        {
            current_group=(current_group+1)%numGroupsInGame;
        }
        while (!tokens[current_group]->tokenIsActive());
    }
    
	active_token = tokens[current_group];
	curGroupPtr = &groups[current_group];
	//game logic
	gl.ContinueGame();
}

void ActionLayer::itm_yesCallback(CCObject* pSender)
{
	mn_Answers->setVisible(0);
	mn_Cards->setVisible(1);
	mn_Cards->setTouchEnabled(1);
    
	HideTimer();
	DropCard();
    
	CardPriceGo(pSender);
}
void ActionLayer::itm_noCallback(CCObject* pSender)
{
	mn_Answers->setVisible(0);
	mn_Cards->setVisible(1);
	mn_Cards->setTouchEnabled(1);
    
	HideTimer();
	DropCard();
	ChangeSelectorCallback(pSender);
}
void ActionLayer::itm_otherCallback(CCObject* pSender)
{
	mn_Answers->setVisible(0);
	//mn_WhoAnswer->setIsVisible(1);
    
	switch(m_GameMode)
	{
        case GAMERS_3:
            switch(active_token->m_CurNumber)
		{
			case 0:
				//Who answer
				itm_1opponent = CCMenuItemImage::create(RightControl_c_blank1,RightControl_c_blank1,this,menu_selector(ActionLayer::itm_1opponentCallback));
				itm_1opponent->setTag(1);
				itm_2opponent = CCMenuItemImage::create(RightControl_c_blank2,RightControl_c_blank2,this,menu_selector(ActionLayer::itm_2opponentCallback));
				itm_2opponent->setTag(2);
				mn_WhoAnswer = CCMenu::create(itm_1opponent, itm_2opponent, NULL);
				break;
			case 1:
				//Who answer
				itm_1opponent = CCMenuItemImage::create(RightControl_c_blank0,RightControl_c_blank0,this,menu_selector(ActionLayer::itm_1opponentCallback));
				itm_1opponent->setTag(0);
				itm_2opponent = CCMenuItemImage::create(RightControl_c_blank2,RightControl_c_blank2,this,menu_selector(ActionLayer::itm_2opponentCallback));
				itm_2opponent->setTag(2);
				mn_WhoAnswer = CCMenu::create(itm_1opponent, itm_2opponent, NULL);
				break;
			case 2:
				//Who answer
				itm_1opponent = CCMenuItemImage::create(RightControl_c_blank0,RightControl_c_blank0,this,menu_selector(ActionLayer::itm_1opponentCallback));
				itm_1opponent->setTag(0);
				itm_2opponent = CCMenuItemImage::create(RightControl_c_blank1,RightControl_c_blank1,this,menu_selector(ActionLayer::itm_2opponentCallback));
				itm_2opponent->setTag(1);
				mn_WhoAnswer = CCMenu::create(itm_1opponent, itm_2opponent, NULL);
				break;
		}
            break;
        case GROUP_2:
            switch(active_token->m_CurNumber)
		{
			case 0:
				//Who answer
				itm_1opponent = CCMenuItemImage::create(RightControl_c_blank1,RightControl_c_blank1,this,menu_selector(ActionLayer::itm_1opponentCallback));
				itm_1opponent->setTag(1);
				mn_WhoAnswer = CCMenu::create(itm_1opponent, NULL);
				break;
			case 1:
				//Who answer
				itm_1opponent = CCMenuItemImage::create(RightControl_c_blank0,RightControl_c_blank0,this,menu_selector(ActionLayer::itm_1opponentCallback));
				itm_1opponent->setTag(0);
				mn_WhoAnswer = CCMenu::create(itm_1opponent, NULL);
				break;
		}
            break;
        case GROUP_3:
            switch(active_token->m_CurNumber)
		{
			case 0:
				//Who answer
				itm_1opponent = CCMenuItemImage::create(RightControl_c_blank1,RightControl_c_blank1,this,menu_selector(ActionLayer::itm_1opponentCallback));
				itm_1opponent->setTag(1);
				itm_2opponent = CCMenuItemImage::create(RightControl_c_blank2,RightControl_c_blank2,this,menu_selector(ActionLayer::itm_2opponentCallback));
				itm_2opponent->setTag(2);
				mn_WhoAnswer = CCMenu::create(itm_1opponent, itm_2opponent, NULL);
				break;
			case 1:
				//Who answer
				itm_1opponent = CCMenuItemImage::create(RightControl_c_blank0,RightControl_c_blank0,this,menu_selector(ActionLayer::itm_1opponentCallback));
				itm_1opponent->setTag(0);
				itm_2opponent = CCMenuItemImage::create(RightControl_c_blank2,RightControl_c_blank2,this,menu_selector(ActionLayer::itm_2opponentCallback));
				itm_2opponent->setTag(2);
				mn_WhoAnswer = CCMenu::create(itm_1opponent, itm_2opponent, NULL);
				break;
			case 2:
				//Who answer
				itm_1opponent = CCMenuItemImage::create(RightControl_c_blank0,RightControl_c_blank0,this,menu_selector(ActionLayer::itm_1opponentCallback));
				itm_1opponent->setTag(0);
				itm_2opponent = CCMenuItemImage::create(RightControl_c_blank1,RightControl_c_blank1,this,menu_selector(ActionLayer::itm_2opponentCallback));
				itm_2opponent->setTag(1);
				mn_WhoAnswer = CCMenu::create(itm_1opponent, itm_2opponent, NULL);
				break;
		}
            break;
        case GROUP_4:
            switch(active_token->m_CurNumber)
		{
			case 0:
				//Who answer
				itm_1opponent = CCMenuItemImage::create(RightControl_c_blank1,RightControl_c_blank1,this,menu_selector(ActionLayer::itm_1opponentCallback));
				itm_1opponent->setTag(1);
				itm_2opponent = CCMenuItemImage::create(RightControl_c_blank2,RightControl_c_blank2,this,menu_selector(ActionLayer::itm_2opponentCallback));
				itm_2opponent->setTag(2);
				itm_3opponent = CCMenuItemImage::create(RightControl_c_blank3,RightControl_c_blank3,this,menu_selector(ActionLayer::itm_3opponentCallback));
				itm_3opponent->setTag(3);
				mn_WhoAnswer = CCMenu::create(itm_1opponent, itm_2opponent, itm_3opponent, NULL);
				break;
			case 1:
				//Who answer
				itm_1opponent = CCMenuItemImage::create(RightControl_c_blank0,RightControl_c_blank0,this,menu_selector(ActionLayer::itm_1opponentCallback));
				itm_1opponent->setTag(0);
				itm_2opponent = CCMenuItemImage::create(RightControl_c_blank2,RightControl_c_blank2,this,menu_selector(ActionLayer::itm_2opponentCallback));
				itm_2opponent->setTag(2);
				itm_3opponent = CCMenuItemImage::create(RightControl_c_blank3,RightControl_c_blank3,this,menu_selector(ActionLayer::itm_3opponentCallback));
				itm_3opponent->setTag(3);
				mn_WhoAnswer = CCMenu::create(itm_1opponent, itm_2opponent, itm_3opponent, NULL);
				break;
			case 2:
				//Who answer
				itm_1opponent = CCMenuItemImage::create(RightControl_c_blank0,RightControl_c_blank0,this,menu_selector(ActionLayer::itm_1opponentCallback));
				itm_1opponent->setTag(0);
				itm_2opponent = CCMenuItemImage::create(RightControl_c_blank1,RightControl_c_blank1,this,menu_selector(ActionLayer::itm_2opponentCallback));
				itm_2opponent->setTag(1);
				itm_3opponent = CCMenuItemImage::create(RightControl_c_blank3,RightControl_c_blank3,this,menu_selector(ActionLayer::itm_3opponentCallback));
				itm_3opponent->setTag(3);
				mn_WhoAnswer = CCMenu::create(itm_1opponent, itm_2opponent, itm_3opponent, NULL);
				break;
			case 3:
				//Who answer
				itm_1opponent = CCMenuItemImage::create(RightControl_c_blank0,RightControl_c_blank0,this,menu_selector(ActionLayer::itm_1opponentCallback));
				itm_1opponent->setTag(0);
				itm_2opponent = CCMenuItemImage::create(RightControl_c_blank1,RightControl_c_blank1,this,menu_selector(ActionLayer::itm_2opponentCallback));
				itm_2opponent->setTag(1);
				itm_3opponent = CCMenuItemImage::create(RightControl_c_blank2,RightControl_c_blank2,this,menu_selector(ActionLayer::itm_3opponentCallback));
				itm_3opponent->setTag(2);
				mn_WhoAnswer = CCMenu::create(itm_1opponent, itm_2opponent, itm_3opponent, NULL);
				break;
		}
            break;
	}
    
	mn_WhoAnswer->alignItemsVerticallyWithPadding(CARD_PADDING);
	addChild(mn_WhoAnswer);
	mn_WhoAnswer->setPosition(ccp(m_mnCardsX,m_mnCardsY));
	mn_WhoAnswer->setVisible(true);
}

void ActionLayer::itm_card3Callback(CCObject* pSender)
{
	curCardPrice = 3;
    mn_Cards->setTouchEnabled(0);
	checked_card = CCSprite::create(RightControl_c3);
	addChild(checked_card,2,CARD_LAYER);
	checked_card->setPosition(CCPointMake(m_mnCardsX,m_mnCardsY-CARD_HEIGHT-CARD_PADDING));
	MoveCardFromControl();
    
    PLAYEFFECT(_sndCheckcard)
}
void ActionLayer::MoveCardFromControl()
{
	CCActionInterval* move=CCMoveTo::create(0.5f,CCPointMake(m_mnCardsX,m_mnCardsY+2*(117+CARD_PADDING)));
	//CCActionInterval* move_exp_in = (CCActionInterval*)CCEaseExponentialIn::create((CCActionInterval*)(move->copy()->autorelease()));
	CCActionInterval* move_exp_in = (CCActionInterval*)CCEaseInOut::create((CCActionInterval*)(move->copy()->autorelease()),4.0f);
    
	CCActionInterval* delay = CCDelayTime::create(0.2f);
	
	CCFiniteTimeAction* seq = CCSequence::create(move_exp_in, delay, CCCallFunc::create(this,callfunc_selector(ActionLayer::MoveCardFromControlCallback)), NULL);
    
	checked_card->runAction(seq);
}
void ActionLayer::MoveCardFromControlCallback()
{
	CCActionInterval* rot = CCRotateTo::create(0.7f,-90.f);
	CCActionInterval* rot_exp_in = (CCActionInterval*)CCEaseInOut::create((CCActionInterval*)(rot->copy()->autorelease()),3.0f);
    
	CCActionInterval* scale = CCScaleBy::create(0.35f, 0.0f, 3.0f);
	CCActionInterval* scale_exp_in = (CCActionInterval*)CCEaseIn::create((CCActionInterval*)(scale->copy()->autorelease()),3.0f);
    
	CCActionInterval* move_center = CCMoveTo::create(0.7f,CCPointMake(x,y));
	CCActionInterval* move_center_exp_in = (CCActionInterval*)CCEaseInOut::create((CCActionInterval*)(move_center->copy()->autorelease()),3.0f);
    
	checked_card->runAction(move_center_exp_in);
	checked_card->runAction(rot_exp_in);
	checked_card->runAction(CCSequence::create(scale_exp_in,CCCallFunc::create(this,callfunc_selector(ActionLayer::MoveCardFaceSide)),NULL));
    
	ShowTimer();
}
void ActionLayer::MoveCardFaceSide()
{
    //def icon of activity
    CCSprite* s_Activity;
    
	float posx,posy;
	posx = checked_card->getPosition().x;
	posy = checked_card->getPosition().y;
	checked_card->stopAllActions();
	
	float rotc,sccx,sccy;
    
	rotc = checked_card->getRotation();
	sccx = checked_card->getScaleX();
	sccy = checked_card->getScaleY()/3.4f;
    
	this->removeChildByTag(CARD_LAYER,1);
	
    //Word
	int isr;
    //RED_GENERATOR
    isr=(rand()%10)-8;
    
    const char rand_act[3] = {'O','P','R'};
    char act[2];
    if(active_token->m_CurrentPosition==0)
    {
        //srand((unsigned)time(NULL));
        act[0]=rand_act[rand()%3];
        act[1]=0;
    }else{
        act[0]=tbl[active_token->m_CurrentPosition]->m_Activity;
        act[1]=0;
    }
    
    const char* word_actions[3] = { "Объясните друзьям понятие",
        "Покажите как выглядит",
        "Нарисуйте на бумаге"
    };
    const char* word_action;
    if(act[0]=='O') {word_action = word_actions[0]; hint_act=0; s_Activity = CCSprite::create(act_o);}
    if(act[0]=='P') {word_action = word_actions[1]; hint_act=1; s_Activity = CCSprite::create(act_p);}
    if(act[0]=='R') {word_action = word_actions[2]; hint_act=2; s_Activity = CCSprite::create(act_r);}
    
    //Установка флага "Красной карты"
    if(isr>0)
    {
        RedCard=1;
    }else{
        RedCard=0;
    }
    
    //Check sprite for card (if 'ALL' flag is set)
    if(RedCard)
    {
        checked_card = CCSprite::create(_c_big_all);
    }else{
        checked_card = CCSprite::create(_c_big);
    }
	
	this->addChild(checked_card,2);
	checked_card->setPosition(ccp(posx,posy));
	checked_card->setRotation(rotc);
	checked_card->setScaleX(sccx);
	checked_card->setScaleY(sccy);
	
    
    CCLabelTTF* p_wordaction = CCLabelTTF::create(word_action,FONT_NAME,20);
    p_wordaction->setColor(ccc3(255, 240, 195));
    
    //fix /n-bug
    unsigned char* wordch = dbw->getWord(curCardPrice,&act[0]);
    int j=0;
    while (wordch[j]!='\0') {
        if(wordch[j]==' ') wordch[j]='\n';
        j++;
    }
    
	word = CCLabelTTF::create((const char*)wordch,FONT_NAME,32);
    word->setColor(ccc3(255, 255, 255));
    
    checked_card->addChild(p_wordaction);
    p_wordaction->setRotation(90.0f);
	p_wordaction->setPosition(ccp(checked_card->getContentSize().width/4+32.0f,checked_card->getContentSize().height/2));
	checked_card->addChild(word);
	word->setRotation(90.0f);
	word->setPosition(ccp(checked_card->getContentSize().width/4-50.0f,checked_card->getContentSize().height/2));
    
    //add icon of activity
    checked_card->addChild(s_Activity);
    s_Activity->setPosition(ccp(checked_card->getContentSize().width/4+182.0f,checked_card->getContentSize().height/2));
    
	CCActionInterval* rot = CCRotateTo::create(0.35f,-90.0f);
	//CCActionInterval* rot_exp_in = (CCActionInterval*)CCEaseOut::actionWithAction((CCActionInterval*)(rot->copy()->autorelease()),2.0f);
	CCActionInterval* rot_exp_in = (CCActionInterval*)CCEaseExponentialOut::create((CCActionInterval*)(rot->copy()->autorelease()));
    
	CCActionInterval* scale = CCScaleTo::create(0.35f, 1.0f, 1.0f);
	//CCActionInterval* scale_exp_in = (CCActionInterval*)CCEaseOut::actionWithAction((CCActionInterval*)(scale->copy()->autorelease()),2.0f);
	CCActionInterval* scale_exp_in = (CCActionInterval*)CCEaseExponentialOut::create((CCActionInterval*)(scale->copy()->autorelease()));
    
	CCActionInterval* move_center = CCMoveTo::create(0.35f,CCPointMake(x,y));
	//CCActionInterval* move_center_exp_in = (CCActionInterval*)CCEaseOut::actionWithAction((CCActionInterval*)(move_center->copy()->autorelease()),2.0f);
	CCActionInterval* move_center_exp_in = (CCActionInterval*)CCEaseExponentialOut::create((CCActionInterval*)(move_center->copy()->autorelease()));
    
	checked_card->runAction(move_center_exp_in);
	checked_card->runAction(rot_exp_in);
	checked_card->runAction(scale_exp_in);
    
    //Карта выбрана
    gamestate = 1;
}

void ActionLayer::itm_card4Callback(CCObject* pSender)
{
	curCardPrice = 4;
	mn_Cards->setTouchEnabled(0);
	checked_card = CCSprite::create(RightControl_c4);
	addChild(checked_card,2,CARD_LAYER);
	checked_card->setPosition(CCPointMake(m_mnCardsX,m_mnCardsY));
	MoveCardFromControl();
    
    PLAYEFFECT(_sndCheckcard)
}
void ActionLayer::itm_card5Callback(CCObject* pSender)
{
	curCardPrice = 5;
	mn_Cards->setTouchEnabled(0);
	checked_card = CCSprite::create(RightControl_c5);
	addChild(checked_card,2,CARD_LAYER);
	checked_card->setPosition(CCPointMake(m_mnCardsX,m_mnCardsY+CARD_HEIGHT+CARD_PADDING));
	MoveCardFromControl();
    
    PLAYEFFECT(_sndCheckcard)
}

void ActionLayer::itm_TimerStartCallback(CCObject* pSender)
{
	to1 = CCProgressTo::create(60.0f, 100.0f);
	lefttime = CCProgressTimer::create(CCSprite::create(Timer_timer_digits_active));
	lefttime->setType(kCCProgressTimerTypeRadial);
	((CCSprite*)lefttime->getSprite())->setOpacity(100);
	pL_Timer->addChild(lefttime,2);
	lefttime->setPosition(ccp(11,-3));
    
    lefttime->runAction(CCRepeat::create(
                                                   CCSequence::create(
                                                                       (CCActionInterval*)to1->copy()->autorelease(),
                                                                       CCCallFunc::create(this,callfunc_selector(ActionLayer::TimerOver)),
                                                                       NULL),60.0f));
    /*
     lefttime->runAction(CCSequence::create(CCRepeat::create((CCActionInterval*)to1->copy()->autorelease(),60.0f),CCCallFunc::create(this,callfunc_selector(ActionLayer::TimerOver)),NULL));
     */
	setTimerMode(1);
	//wordaction
	word->runAction(CCEaseInOut::create(CCScaleTo::create(1.5f,-1.0f,1.0f),3.0f));
    
    if(RedCard)
    {
        ShowAnswersMenu(RED);}else{
            ShowAnswersMenu(0);
        }
    //Нажата кнопка "Старт"
    gamestate = 2;
    effect_id = PLAYEFFECTRECURSE(_sndTimer)
    
    PLAYEFFECT(_sndButton_timer)
}
void ActionLayer::itm_TimerPauseCallback(CCObject* pSender)
{
	// #x3
	if(lefttime->getPercentage()>1)
	{
		lefttime->pauseSchedulerAndActions();
		setTimerMode(2);
		//wordaction
		word->runAction(CCEaseInOut::create(CCScaleTo::create(1.5f,1.0f,1.0f),3.0f));
	    
        //Нажата кнопка "Пауза"
        gamestate = 3;
        PAUSEEFFECT(effect_id)
        
        PLAYEFFECT(_sndButton_timer)
    }
}
void ActionLayer::itm_TimerRunCallback(CCObject* pSender)
{
	lefttime->resumeSchedulerAndActions();
	setTimerMode(1);
	//wordaction
	word->runAction(CCEaseInOut::create(CCScaleTo::create(1.5f,-1.0f,1.0f),3.0f));
    
    //Нажата кнопка "Старт"
    gamestate = 2;
    RESUMEEFFECT(effect_id)
    
    PLAYEFFECT(_sndButton_timer)
}
void ActionLayer::TimerOver()
{
	setTimerMode(0);
	lefttime->removeFromParentAndCleanup(1);
    STOPALLEFFECTS
    PLAYEFFECT(_sndAlert)
    
}
// case:
// 0: start, 1: pause, 2: run
void ActionLayer::setTimerMode(int mode)
{
	itm_Timer_start->setVisible(false);
	itm_Timer_pause->setVisible(false);
	itm_Timer_run->setVisible(false);
	switch (mode)
	{
        case 0:
            itm_Timer_start->setVisible(true);
            break;
        case 1:
            itm_Timer_pause->setVisible(true);
            break;
        case 2:
            itm_Timer_run->setVisible(true);
            break;
	}
}

void ActionLayer::ShowAnswersMenu(int Mode)
{
	mn_Cards->setVisible(0);
	mn_Answers->setVisible(1);
    
	ShowAnswerCard(RightControl_c3_hybrid,RightControl_c3div,RightControl_c3bottom,ccp(m_mnCardsX,m_mnCardsY+CARD_HEIGHT+CARD_PADDING), 0);
	ShowAnswerCard(RightControl_c4_hybrid,RightControl_c4div,RightControl_c4bottom,ccp(m_mnCardsX,m_mnCardsY), 0.1f);
    
	//Обработка отображения варианта "Ответил соперник"
	if(!Mode){
		CCMenuItem* p_other = (CCMenuItem*)mn_Answers->getChildByTag(RED);
		p_other->setVisible(0);
    }else{
        CCMenuItem* p_other = (CCMenuItem*)mn_Answers->getChildByTag(RED);
        p_other->setVisible(1);
		ShowAnswerCard(RightControl_c5_hybrid,RightControl_c5div,RightControl_c5bottom,ccp(m_mnCardsX,m_mnCardsY-CARD_HEIGHT-CARD_PADDING), 0.2f);
	}
}
void ActionLayer::ShowAnswerCard(const char* fHybrid, const char* fTop, const char* fBottom, CCPoint Position, float delay)
{
	CCLayer* pL_Answers = CCLayer::create();
	addChild(pL_Answers,0,ANSWER_LAYER);
	
	CCSprite* cardMask = CCSprite::create(fHybrid);
	pL_Answers->addChild(cardMask);
	cardMask->setPosition(Position);
    
	CCSprite* cardScene1 = CCSprite::create(fTop);
	pL_Answers->addChild(cardScene1);
	cardScene1->setPosition(Position);
	
	CCSprite* cardScene2 = CCSprite::create(fBottom);
	pL_Answers->addChild(cardScene2);
	cardScene2->setPosition(Position);
	cardScene2->setScaleY(0.0f);
	cardScene2->setSkewX(-20.0f);
    
	float t=0.3f;
    
	cardScene1->runAction(
                          (CCActionInterval*)CCSequence::create(
                                                                 CCDelayTime::create(delay),
                                                                 CCEaseIn::create(CCScaleBy::create(t,1,0),3.0f),
                                                                 NULL)
                          );
    
	cardScene1->runAction(
                          (CCActionInterval*)CCSequence::create(
                                                                 CCDelayTime::create(delay),
                                                                 CCEaseIn::create(CCSkewBy::create(t,20,0),3.0f),
                                                                 NULL)
                          );
    
	cardScene2->runAction((CCActionInterval*)CCSequence::create(
                                                                 CCDelayTime::create(t+delay),
                                                                 CCEaseOut::create(
                                                                                             CCScaleTo::create(t,1,1),3.0f)
                                                                 ,NULL)
                          );
	cardScene2->runAction((CCActionInterval*)CCSequence::create(
                                                                 CCDelayTime::create(t+delay),
                                                                 CCEaseOut::create(
                                                                                             CCSkewBy::create(t,20,0),3.0f),
                                                                 CCCallFunc::create(this,callfunc_selector(ActionLayer::ShowAnswerCardCallback))
                                                                 ,NULL)
                          );
}
void ActionLayer::ShowAnswerCardCallback()
{
	removeChildByTag(ANSWER_LAYER,1);
}

void ActionLayer::ShowTimer()
{
	//show timer
	CCActionInterval* mov_timer = CCMoveBy::create(1.0f,ccp(230,0));
	CCActionInterval* move_timer_eio = (CCActionInterval*)CCEaseInOut::create(mov_timer,4.0f);
	pL_Timer->runAction(move_timer_eio);
    
	CCActionInterval* rot_light = CCRotateBy::create(1.0f,-10.0f);
	
	((CCSprite*)pL_Timer->getChildByTag(ID_DIGITS_L))->runAction((CCActionInterval*)rot_light->copy()->autorelease());
	((CCSprite*)pL_Timer->getChildByTag(ID_BUTTON_L))->runAction((CCActionInterval*)rot_light->copy()->autorelease());
}
void ActionLayer::HideTimer()
{
	//stopcreate
	lefttime->removeFromParentAndCleanup(1);
	setTimerMode(0);
    STOPEFFECT(effect_id)
    
	//hide timer
	CCActionInterval* mov_timer = CCMoveBy::create(1.0f,ccp(-230,0));
	CCActionInterval* move_timer_eio = (CCActionInterval*)CCEaseInOut::create(mov_timer,4.0f);
	pL_Timer->runAction(move_timer_eio);
    
	CCActionInterval* rot_light = CCRotateBy::create(1.0f,10.0f);
	
	((CCSprite*)pL_Timer->getChildByTag(ID_DIGITS_L))->runAction((CCActionInterval*)rot_light->copy()->autorelease());
	((CCSprite*)pL_Timer->getChildByTag(ID_BUTTON_L))->runAction((CCActionInterval*)rot_light->copy()->autorelease());
}
void ActionLayer::itm_1opponentCallback(CCObject* pSender)
{
	FMoveCor(tokens[itm_1opponent->getTag()],2);
	snaps.IncCurAct();
	ChangeSelectorCallback(pSender);
	
	mn_WhoAnswer->setVisible(0);
	mn_Cards->setVisible(1);
	mn_Cards->setTouchEnabled(1);
    
	HideTimer();
	DropCard();
}
void ActionLayer::itm_2opponentCallback(CCObject* pSender)
{
	FMoveCor(tokens[itm_2opponent->getTag()],2);
	snaps.IncCurAct();
	ChangeSelectorCallback(pSender);
	
	mn_WhoAnswer->setVisible(0);
	mn_Cards->setVisible(1);
	mn_Cards->setTouchEnabled(1);
    
	HideTimer();
	DropCard();
}
void ActionLayer::itm_3opponentCallback(CCObject* pSender)
{
	FMoveCor(tokens[itm_3opponent->getTag()],2);
	snaps.IncCurAct();
	ChangeSelectorCallback(pSender);
	
	mn_WhoAnswer->setVisible(0);
	mn_Cards->setVisible(1);
	mn_Cards->setTouchEnabled(1);
    
	HideTimer();
	DropCard();
}
void ActionLayer::DropCard()
{
	CCActionInterval* rotate = CCRotateTo::create(0.5f,480);
	CCActionInterval* move = CCMoveTo::create(0.3f,ccp(-400,600));
	CCActionInterval* ease_move = CCEaseExponentialIn::create(move);
	CCActionInterval* ease_rotate = CCEaseExponentialIn::create(rotate);
    
	checked_card->runAction(ease_move);
	checked_card->runAction(ease_rotate);
    
    //Переход хода
    gamestate = 0;
}

//›ÚÓ ÙÛÌÍˆËˇ ÓÔÂ‰ÂÎˇÂÚ ‚ÓÁÏÓÊÌÓÒÚ¸ ıÓ‰‡.
//¬ÓÁ‚‡˘‡ÂÚ:
//0 - ‚ÓÁÏÓÊÂÌ ıÓ‰ Ì‡ h ıÓ‰Ó‚
//(3<=n<5)|64- ‚ÓÁÏÓÊÂÌ ıÓ‰ Ì‡ n ıÓ‰Ó‚ ËÁ h
//ID_FISHKA|128 - Ì‡ Á‡‰‡ÌÓÏ ÔÓÎÂ ÙË¯ÍË ID_FISH ‚ ÙÓÏ‡ÚÂ 00000xxx, „‰Â ·ËÚ ÛÍ‡Á˚‚‡ÂÚ ID ÙË¯ÍË(ÙË¯ÂÍ)
int ActionLayer::FMoveTroubles(SpriteTokenClass* psF, int h)
{
	if (!psF)
		return -2;
    
	int currentPos = psF->m_CurrentPosition;
	int targetPos = currentPos+h;
	int tablemax_ind=TABLEMAX-1;
    
	if(((currentPos==tablemax_ind)&&h>0)||((currentPos==0)&&(h==-1))) return -2;
    
	if(targetPos>=TABLEMAX) return (tablemax_ind-currentPos)|64;
    
	if(tbl[targetPos]->m_F&15)	return (tbl[targetPos]->m_F&15)|128; else return 0;
}
//’Ó‰ ÚÓÍÂÌ‡ ps Ì‡ h ıÓ‰Ó‚.
//¬ÓÁÏÓÊÂÌ ıÓ‰ Ì‡ -n
int ActionLayer::FMoveCor(SpriteTokenClass* ps, int h)
{
	if(!ps)
		return 0;
	
	int currentPos = ps->m_CurrentPosition;
	tbl[currentPos]->ChangeCellF(ps->pS_F->getTag());
	
	int n=FMoveTroubles(ps,h);
    
	if(n==-2)
	{
		return 0;
	}
    
	if((n!=0)&&(n&64)) h=n&63;
    
	if(n&128) FMoveCor(GetTokenByTag(n&127),-1);//h=n;
    
	//if(n&64) h=n&63;
    
	curGroupPtr = &groups[ps->m_CurNumber];
	curGroupPtr->ChangeCurGroupPos(h);
	if(curGroupPtr->CurGroupPosition() >= 44)	// Ï‡ÍÒ ˜ËÒÎÓ ˇ˜ÂÂÍ ÔÓÎˇ
		gl.FinishGame();
	// push to vec
	CGroupsSnapshot gs(groups);
	snaps.PushSnapshot(gs);
    
	//action
	float MoveDuration = 0.5f;
	CCActionInterval* ScaleIn = CCScaleBy::create(0.2f,1.2f,1.2f);
    
	ps->pS_FShadow->runAction(CCEaseOut::create((CCActionInterval*)ScaleIn->copy()->autorelease(),3.0f));
	ps->pS_F->runAction(CCEaseOut::create((CCActionInterval*)ScaleIn->copy()->autorelease(),3.0f));
	
	ps->pS_FShadow->runAction(CCSequence::create(
                                                  CCDelayTime::create(0.2f),
                                                  CCEaseInOut::create(CCMoveTo::create(MoveDuration,CCPointMake(tbl[currentPos+h]->m_X,tbl[currentPos+h]->m_Y)),3.0f)
                                                  ,NULL));
	ps->pS_FShadow->runAction(CCSequence::create(
                                                  CCDelayTime::create(0.2f),
                                                  CCEaseInOut::create(
                                                                                CCScaleTo::create(0.2f,0.24f,0.76f*tbl[currentPos+h]->m_Y/LUM_Y+0.15f
                                                                                                              ),3.0f),NULL));
	ps->pS_FShadow->runAction(CCSequence::create(
                                                  CCDelayTime::create(0.2f),
                                                  CCEaseInOut::create(
                                                                                CCRotateTo::create(0.3f,atan((tbl[currentPos+h]->m_X-LUM_X)/LUM_Y)*180.0f/PI),3.0f
                                                                                ),NULL));
	ps->pS_F->runAction(CCSequence::create(
                                            CCDelayTime::create(0.2f),
                                            CCEaseInOut::create(CCMoveTo::create(MoveDuration,CCPointMake(tbl[currentPos+h]->m_X,tbl[currentPos+h]->m_Y)),3.0f),
                                            NULL));
	
	ps->pS_FShadow->runAction(
                              CCSequence::create(
                                                  CCDelayTime::create(0.8f),
                                                  CCEaseIn::create((CCActionInterval*)ScaleIn->reverse(),3.0f),NULL));
    
	ps->pS_F->runAction(
                        CCSequence::create(
                                            CCDelayTime::create(0.8f),
                                            CCEaseIn::create((CCActionInterval*)ScaleIn->reverse(),3.0f),CCCallFunc::create(this,callfunc_selector(ActionLayer::PlayTokenEffectCallback)),NULL));
    
	
	ps->setCurrentPos(currentPos+h);
	tbl[currentPos+h]->ChangeCellF(ps->pS_F->getTag());
	return 1;
}
//’Ó‰ ÚÓÍÂÌ‡ ps Ì‡ h ıÓ‰Ó‚.
//¬ÓÁÏÓÊÂÌ ıÓ‰ Ì‡ -n
int ActionLayer::FMove(SpriteTokenClass* ps, int h)
{
	/*
     int n=FMoveTroubles(ps,h);
     
     if(n==-2)
     {
     return 0;
     }
     
     if((n!=0)&&(n&64)) h=n&63;
     
     if(n&128) FMove(GetTokenByTag(n&127),-1);//h=n;
     
     //if(n&64) h=n&63;
     */
	int currentPos = ps->m_CurrentPosition;
    
	//action
	float MoveDuration = 0.5f;
	CCActionInterval* ScaleIn = CCScaleBy::create(0.2f,1.2f,1.2f);
    
	ps->pS_FShadow->runAction(CCEaseOut::create((CCActionInterval*)ScaleIn->copy()->autorelease(),3.0f));
	ps->pS_F->runAction(CCEaseOut::create((CCActionInterval*)ScaleIn->copy()->autorelease(),3.0f));
    
	ps->pS_FShadow->runAction(CCSequence::create(
                                                  CCDelayTime::create(0.2f),
                                                  CCEaseInOut::create(CCMoveTo::create(MoveDuration,CCPointMake(tbl[currentPos+h]->m_X,tbl[currentPos+h]->m_Y)),3.0f)
                                                  ,NULL));
	ps->pS_FShadow->runAction(CCSequence::create(
                                                  CCDelayTime::create(0.2f),
                                                  CCEaseInOut::create(
                                                                                CCScaleTo::create(0.2f,0.24f,0.76f*tbl[currentPos+h]->m_Y/LUM_Y+0.15f
                                                                                                              ),3.0f),NULL));
	ps->pS_FShadow->runAction(CCSequence::create(
                                                  CCDelayTime::create(0.2f),
                                                  CCEaseInOut::create(
                                                                                CCRotateTo::create(0.3f,atan((tbl[currentPos+h]->m_X-LUM_X)/LUM_Y)*180.0f/PI),3.0f
                                                                                ),NULL));
	ps->pS_F->runAction(CCSequence::create(
                                            CCDelayTime::create(0.2f),
                                            CCEaseInOut::create(CCMoveTo::create(MoveDuration,CCPointMake(tbl[currentPos+h]->m_X,tbl[currentPos+h]->m_Y)),3.0f),
                                            NULL));
    
	ps->pS_FShadow->runAction(
                              CCSequence::create(
                                                  CCDelayTime::create(0.8f),
                                                  CCEaseIn::create((CCActionInterval*)ScaleIn->reverse(),3.0f),NULL));
    
	ps->pS_F->runAction(
                        CCSequence::create(
                                            CCDelayTime::create(0.8f),
                                            CCEaseIn::create((CCActionInterval*)ScaleIn->reverse(),3.0f),CCCallFunc::create(this,callfunc_selector(ActionLayer::PlayTokenEffectCallback)),NULL));
    
	ps->setCurrentPos(currentPos+h);
	tbl[currentPos]->ChangeCellF(ps->pS_F->getTag());
	tbl[currentPos+h]->ChangeCellF(ps->pS_F->getTag());
	return 1;
}

void ActionLayer::PlayTokenEffectCallback()
{
    PLAYEFFECT(_sndToken)
}

SpriteTokenClass* ActionLayer::GetTokenByTag(int Tag)
{
	SpriteTokenClass* result = NULL;
	for(int i=0;i<numGroupsInGame;i++)
	{
        if(tokens[i]->pS_F->getTag()==Tag)
		{
            result = tokens[i];
		}
	}
	return result;
}

//RewindAnimation
void ActionLayer::RewindAnimation(CCLayer* parent)
{
	CCActionInterval* move_array[] = {CCMoveBy::create(1.0f,ccp(0,60.0f)),CCMoveBy::create(1.0f,ccp(0,50.0f)),CCMoveBy::create(1.0f,ccp(0,-30.0f))};
	CCActionInterval* scale_array[] = {CCScaleBy::create(1.0f,1.0f,1.3f),CCScaleBy::create(1.0f,1.0f,0.8f),CCScaleBy::create(1.0f,1.0f,1.8f)};
	CCLayer* pL_Rewind = CCLayer::create();
	parent->addChild(pL_Rewind,1,REWIND_STRIPE);
	srand((unsigned)time(NULL));
	for(int i=0;i<4;i++)
	{
		CCSprite* sprite_array[] = {CCSprite::create(RewindAnimation_rewind),CCSprite::create(RewindAnimation_rewind2)};
		int numspr = rand()%2;
		pL_Rewind->addChild(sprite_array[numspr]);
		//randomize start
		sprite_array[numspr]->setPosition(ccp(x,+(float)(i*size.height/4+rand()%150)));
		sprite_array[numspr]->setScaleY(0.25f-(rand()%15)/100);
		sprite_array[numspr]->runAction(CCEaseBounceInOut::create((CCActionInterval*)move_array[rand()%3]->copy()->autorelease()));
		sprite_array[numspr]->runAction(CCSequence::create(CCEaseElastic::create((CCActionInterval*)scale_array[rand()%3]->copy()->autorelease(),4.0f),CCCallFunc::create(this,callfunc_selector(ActionLayer::RewindAnimationCallback)),NULL));
	}
}
void ActionLayer::RewindAnimationCallback()
{
	this->removeChildByTag(REWIND_STRIPE,1);
}
/*
 Func for save ActionLayer's menu state
 in menustate variable (bit):
 1: mn_Timer
 2: mn_Cards
 4: mn_Answers
 8: game_menu
 
 use
 RestoreMenuState();
 */
void ActionLayer::SaveMenuState()
{
    menustate=0;
    if (mn_Timer->isTouchEnabled())
    {
        menustate|=1;
        mn_Timer->setTouchEnabled(false);
    }
    if (mn_Cards->isTouchEnabled())
    {
        menustate|=2;
        mn_Cards->setTouchEnabled(false);
    }
    if (mn_Answers->isTouchEnabled())
    {
        menustate|=4;
        mn_Answers->setTouchEnabled(false);
    }
    if (game_menu->isTouchEnabled())
    {
        menustate|=8;
        game_menu->setTouchEnabled(false);
    }
    /*
     if (mn_WhoAnswer->getIsTouchEnabled())
     {
     menustate|=16;
     mn_WhoAnswer->setIsTouchEnabled(false);
     }
     */
}
void ActionLayer::RestoreMenuState()
{
    if (menustate&1)
    {
        mn_Timer->setTouchEnabled(true);
    }
    if (menustate&2)
    {
        mn_Cards->setTouchEnabled(true);
    }
    if (menustate&4)
    {
        mn_Answers->setTouchEnabled(true);
    }
    if (menustate&8)
    {
        game_menu->setTouchEnabled(true);
    }
    if (menustate&16)
    {
        mn_WhoAnswer->setTouchEnabled(true);
    }
}

//////////////////////////////////////////////////////////////////////////
CGameLogic::CGameLogic(void)
{
	act = NULL;
}

CGameLogic::CGameLogic(ActionLayer * ptr)
{
	act = ptr;
}

CGameLogic::~CGameLogic(void)
{
}

int CGameLogic::StartGame()
{
	std::stringstream ss;
	ss << "Current command # " << act->active_token->m_CurNumber;
    
	act->pLabelGroup = CCLabelTTF::create(ss.str().c_str(), "Thonburi", 24);
	act->pLabelGroup->setPosition(ccp(200,50));
	act->addChild(act->pLabelGroup, 1);
    
	return 0;
}

int CGameLogic::ContinueGame()
{
	std::stringstream ss;
	ss << "Current command # " << act->active_token->m_CurNumber;
    
	act->pLabelGroup->setString(ss.str().c_str());
    
	return 0;
}

int CGameLogic::FinishGame()
{
	std::stringstream ss;
	ss << "Command # " << act->active_token->m_CurNumber << " won!!!!!!";
    
	act->pLabelGroup->setString(ss.str().c_str());
    
    //win
    act->ShowWinners(act->active_token->m_CurNumber);
    
    PLAYEFFECT(_sndCamera)
    
	return 0;
}

/////////////////////////////////////////////////////////////////////////
// GameMenuLayer
GameMenuLayer::GameMenuLayer()
{
	this->setTouchEnabled(true);
	// Make sure the layer accepts touches
    (CCDirector::sharedDirector()->getTouchDispatcher())->addTargetedDelegate(this, 0, false);
    
	checked=false;
    
	// Get window size and place the label upper.
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    float x,y;
	x = size.width/2;
	y = size.height/2;
    
	float xs,ys;
	//desk
	CCSprite* pS_Menu = CCSprite::create(GameMenu_gamemenu);
	addChild(pS_Menu,0,ID_GMDESK);
	pS_Menu->setPosition(ccp(x,y));
	xs=x-pS_Menu->getContentSize().width/2;
	ys=y-pS_Menu->getContentSize().height/2;
    
	//swipe
	endSwipe = 258.0f;
	xStartPos = xs+110-35; //34
	
    pS_Swipe1 = CCSprite::create(GameMenu_swipe);
	pS_Swipe1->setAnchorPoint(ccp(0,0));
	addChild(pS_Swipe1,1,ID_SWIPE_RESTART);
	pS_Swipe1->setPosition(ccp(xStartPos,ys+184));
	
    pS_Swipe2 = CCSprite::create(GameMenu_swipe);
	pS_Swipe2->setAnchorPoint(ccp(0,0));
	addChild(pS_Swipe2,1,ID_SWIPE_MAINMENU);
	pS_Swipe2->setPosition(ccp(xStartPos,ys+113));
    
	//unlock animation effect
	//new game
    ccColor3B clr = ccc3(46,20,0);
	CCLabelTTF* label = CCLabelTTF::create("Начать сначала",FONT_NAME,22.0f);
    //CCLabelBMFont* label = CCLabelBMFont::create("New game","fonts/Minion_32.fnt");
	addChild(label,0,ID_TEXT_RESTART);
	label->setPosition(ccp(xs+225,ys+212));
	label->setColor(clr);
	//CCSprite* chars[255];
    /*
     for(int j=0;j<label->getChildrenCount();j++)
     {
     chars[j] = (CCSprite*)label->getChildByTag(j);
     chars[j]->runAction(CCRepeatForever::create((CCActionInterval*)
     CCSequence::create(CCDelayTime::create(j*0.1f),
     CCSequence::create(CCTintTo::create(0.5,230,230,230),CCTintTo::create(0.5,clr.b,clr.g,clr.r),NULL)->copy()->autorelease(),
     CCSequence::create(CCDelayTime::create((label->getChildrenCount()-j)*0.1f)),
     NULL))
     );
     }
     */
	//Main menu
	CCLabelTTF* label2 = CCLabelTTF::create("Главное меню",FONT_NAME,22.0f);
    //CCLabelBMFont* label2 = CCLabelBMFont::create("Main Menu","fonts/Minion_32.fnt");
	addChild(label2,0,ID_TEXT_MAINMENU);
	label2->setPosition(ccp(xs+225,ys+141));
	label2->setColor(clr);
	//CCSprite* chars2[255];
	/*
     for(int j=0;j<label2->getChildrenCount();j++)
     {
     chars2[j] = (CCSprite*)label2->getChildByTag(j);
     chars2[j]->runAction(CCRepeatForever::create((CCActionInterval*)
     CCSequence::create(CCDelayTime::create(j*0.1f),
     CCSequence::create(CCTintTo::create(0.5,230,230,230),CCTintTo::create(0.5,clr.b,clr.g,clr.r),NULL)->copy()->autorelease(),
     CCSequence::create(CCDelayTime::create((label2->getChildrenCount()-j)*0.1f)),
     NULL))
     );
     }
     */
	//buttons
	CCSprite* pS_buttonSound = CCSprite::create(GameMenu_sound);
	addChild(pS_buttonSound);
	pS_buttonSound->setPosition(ccp(xs+125,ys+70));
	CCSprite* pS_buttonHelp = CCSprite::create(GameMenu_help);
	addChild(pS_buttonHelp);
	pS_buttonHelp->setPosition(ccp(xs+280,ys+70));
}

bool GameMenuLayer::ccTouchBegan(CCTouch *touch, CCEvent *withEvent)
{
	CCPoint touchPoint = touch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
    
	if (CheckPoint(touchPoint))
	{
		checked = true;
		xdelta=touchPoint.x-cex->getPosition().x;
        
        //fade out text on swipe
        cel->runAction(CCFadeOut::create(0.2f));
	}
    
	//hide menu on touch around
	CCSprite* spr = (CCSprite*)this->getChildByTag(ID_GMDESK);
	float szx = spr->getContentSize().width/2;
	float szy = spr->getContentSize().height/2;
	if(touchPoint.x>spr->getPosition().x+szx||touchPoint.x<spr->getPosition().x-szx||touchPoint.y>spr->getPosition().y+szy||touchPoint.y<spr->getPosition().y-szy)
	{
        //RestoreMenuState();
		ActionLayer* al = (ActionLayer*)this->getParent();
		((CCLayerColor*)al->getChildByTag(ID_SHADOWLAYER))->removeFromParentAndCleanup(1);
		this->removeFromParentAndCleanup(1);
        al->RestoreMenuState();
	}
	return true;
}
void GameMenuLayer::ccTouchMoved(CCTouch *touch, CCEvent *withEvent)
{
	CCPoint touchPoint = touch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
    
    //лимит удаления пальца от контрола
	float limit = 200.0f;
    
	if(checked)
	{
        //проверка на лимит
		if(touchPoint.y>cex->getPosition().y+limit||touchPoint.y<cex->getPosition().y-limit||touchPoint.x<xStartPos-limit||touchPoint.x>xStartPos+endSwipe-cex->getContentSize().width+limit)
		{
			CCFiniteTimeAction* actionMoveRet = CCMoveTo::create(0.1f, ccp(xStartPos, cex->getPosition().y) );
			cex->runAction( CCSequence::create(actionMoveRet, /*actionMoveDone,*/ NULL) );
			cel->runAction(CCFadeIn::create(0.2f));
			checked=false;
			return;
		}
        
        //действие с надписью
		if(touchPoint.x-xdelta<xStartPos+endSwipe-cex->getContentSize().width)
			if(touchPoint.x-xdelta>=xStartPos)
			{
                cex->setPosition(ccp(touchPoint.x-xdelta,cex->getPosition().y));
			}
			else
			{
				CCFiniteTimeAction* actionMove = CCMoveTo::create(0.1f, ccp(xStartPos, cex->getPosition().y));
				cex->runAction( CCSequence::create(actionMove,/*actionMoveDone,*/NULL) );
			}
            else
            {
                CCFiniteTimeAction* actionMove1 = CCMoveTo::create(0.1f, ccp(xStartPos+endSwipe-cex->getContentSize().width, cex->getPosition().y));
                cex->runAction( CCSequence::create(actionMove1,/*actionMoveDone,*/NULL) );
            }
	}
}
void GameMenuLayer::ccTouchEnded(CCTouch *touch, CCEvent *withEvent)
{
	CCPoint touchPoint = touch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
    
	if(checked)
	{
        int newX = (int)touchPoint.x;
        
        if (newX >= xStartPos+endSwipe) {
            checked = false;
			int tag = cex->getTag();
			if(tag==ID_SWIPE_RESTART)
			{
				CCScene* pS_Scene = CCScene::create();
				ActionLayer* al = (ActionLayer*)this->getParent();
				CCLayer* pL_Restart = new ActionLayer(al->m_GameMode, al->m_RedName, al->m_GreenName, al->m_BlueName, al->m_YellowName);
				pS_Scene->addChild(pL_Restart);
				CCScene* s = CCTransitionFade::create((1.0f), pS_Scene);
				pL_Restart->release();
				CCDirector::sharedDirector()->replaceScene(s);
                
                PLAYEFFECT(_sndSwipe)
			}
			if(tag==ID_SWIPE_MAINMENU)
			{
				ActionLayer* al = (ActionLayer*)this->getParent();
				((CCLayerColor*)al->getChildByTag(ID_SHADOWLAYER))->removeFromParentAndCleanup(1);
				this->removeFromParentAndCleanup(1);
                al->RestoreMenuState();
                
				CCScene* pS_MainMenuScene = CCScene::create();
				CCLayer* pL_MainMenu = new MainMenuLayer(1);
				pS_MainMenuScene->addChild(pL_MainMenu,0);
				pL_MainMenu->release();
				//CCScene* s = CCTransitionFade::transitionWithDuration((1.2f), pS_MainMenuScene);
				CCDirector::sharedDirector()->pushScene(pS_MainMenuScene);
                
                PLAYEFFECT(_sndSwipe)
			}
        }
        else
        {
            if(!checked)
                return;
            CCFiniteTimeAction* actionMove = CCMoveTo::create(0.1f, ccp(xStartPos, cex->getPosition().y) );
            cex->runAction( CCSequence::create(actionMove, /*actionMoveDone,*/ NULL) );
            cel->runAction(CCFadeIn::create(0.2f));
        }
        checked = false;
	}
}
bool GameMenuLayer::CheckPoint(CCPoint cp)
{
	int d = 10;
	if(cp.x > pS_Swipe1->getPositionX() - d && cp.x < pS_Swipe1->getPositionX()+pS_Swipe1->getContentSize().width + d)
		if(cp.y > pS_Swipe1->getPositionY() - d && cp.y < pS_Swipe1->getPositionY()+pS_Swipe1->getContentSize().height + d)
		{
			cel = (CCLabelTTF*)this->getChildByTag(ID_TEXT_RESTART);
			cex = pS_Swipe1;
			return true;
		}
    
	if (cp.x > pS_Swipe2->getPositionX() - d && cp.x < pS_Swipe2->getPositionX()+pS_Swipe2->getContentSize().width + d)
		if (cp.y > pS_Swipe2->getPositionY() - d && cp.y < pS_Swipe2->getPositionY()+pS_Swipe2->getContentSize().height + d)
		{
			cel = (CCLabelTTF*)this->getChildByTag(ID_TEXT_MAINMENU);
			cex = pS_Swipe2;
			return true;
		}
    
	return false;
}

void ActionLayer::ShowWinners(int Group)
{
    SaveMenuState();
	CCLayerColor* lc = CCLayerColor::create();
	lc->setOpacity(165.0f);
	addChild(lc,5,ID_SHADOWLAYER);
	//lc->runAction(CCEaseIn::create(CCFadeTo::create(0.4f,165),0.8f));
    
	WinnerMenu* pL_WinnerMenu = new WinnerMenu(this, Group);
	this->addChild(pL_WinnerMenu,6,ID_WINNERMENU);
}

/////////////////////////////////////////////////////////
//              WinnerMenu
WinnerMenu::WinnerMenu(ActionLayer* al, int Group)
{
	// Get window size and place the label upper.
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    float x,y;
	x = size.width/2;
	y = size.height/2;
    
	//desk
	CCSprite* pS_Winners = CCSprite::create("winners/desk.png");
	addChild(pS_Winners,0,ID_WINNERDESK);
	pS_Winners->setPosition(ccp(x,y));
    
    const char* wingroup[4] = {"winners/red.png","winners/green.png","winners/blue.png","winners/yellow.png"};
    CCSprite* pS_wingroup = CCSprite::create(wingroup[Group]);
    this->addChild(pS_wingroup,1,ID_WINNERGROUP);
    pS_wingroup->setPosition(ccp(x,y+150));
    
    CCMenuItemImage* itm_continue = CCMenuItemImage::create("winners/btn_continue.png", "winners/btn_continue_a.png", this,menu_selector(WinnerMenu::itm_continueCallback));
    CCMenuItemImage* itm_newgame = CCMenuItemImage::create("winners/btn_newgame.png", "winners/btn_newgame_a.png", this,menu_selector(WinnerMenu::itm_newgameCallback));
    CCMenuItemImage* itm_mainmenu = CCMenuItemImage::create("winners/btn_mainmenu.png", "winners/btn_mainmenu_a.png", this,menu_selector(WinnerMenu::itm_mainmenuCallback));
    if(al->allactivetokens==1) itm_continue->setVisible(false);
    CCMenu* p_Menu = CCMenu::create(itm_continue,itm_newgame,itm_mainmenu,NULL);
    p_Menu->alignItemsVerticallyWithPadding(10.0f);
    //check if 1 token in game
    this->addChild(p_Menu);
    p_Menu->setPosition(ccp(x,y-175));
}

void WinnerMenu::itm_continueCallback(CCObject* pSender)
{
    ActionLayer* al = (ActionLayer*)this->getParent();
    al->tokens[al->pre_current_group]->removeToken();
    
    //hide menu on touch around
	((CCLayerColor*)al->getChildByTag(ID_SHADOWLAYER))->removeFromParentAndCleanup(1);
    this->removeFromParentAndCleanup(1);
    al->RestoreMenuState();
}

void WinnerMenu::itm_newgameCallback(CCObject* pSender)
{
    CCScene* pS_Scene = CCScene::create();
    ActionLayer* al = (ActionLayer*)this->getParent();
    CCLayer* pL_Restart = new ActionLayer(al->m_GameMode, al->m_RedName, al->m_GreenName, al->m_BlueName, al->m_YellowName);
    pS_Scene->addChild(pL_Restart);
    CCScene* s = CCTransitionFade::create((1.0f), pS_Scene);
    pL_Restart->release();
    CCDirector::sharedDirector()->replaceScene(s);
}

void WinnerMenu::itm_mainmenuCallback(CCObject* pSender)
{
    ActionLayer* al = (ActionLayer*)this->getParent();
    
    
    CCScene* pS_MainMenuScene = CCScene::create();
    CCLayer* pL_MainMenu;
    if(al->allactivetokens==1)
    {
        pL_MainMenu = new MainMenuLayer(0);
    }else{
        pL_MainMenu = new MainMenuLayer(1);
        itm_continueCallback(pSender);
    }
    pS_MainMenuScene->addChild(pL_MainMenu,0);
    pL_MainMenu->release();
    
    //CCScene* s = CCTransitionFade::transitionWithDuration((1.2f), pS_MainMenuScene);
    CCDirector::sharedDirector()->pushScene(pS_MainMenuScene);
}
