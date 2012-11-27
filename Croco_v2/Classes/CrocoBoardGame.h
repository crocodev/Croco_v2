#ifndef __CROCO_H__
#define __CROCO_H__

#include "cocos2d.h"
using namespace cocos2d;

//music
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#include "AppDelegate.h"

//Scroll menu
#include "CCScrollLayer.h"

#include "dbword.h"
#include "Group.h"
#include <sstream>

#include "TextureCache.h"

class CGameLogic;
class ActionLayer;

//Font
#define FONT_NAME			"fonts/MinionPro-Regular.otf"/*"fonts/Neucha.ttf"*/
#define FONT_SIZE			22

#define PATH_MAX_FILE    255

//less
#define ADDIMAGE(IMG)                   CCTextureCache::sharedTextureCache()->addImageAsync(IMG, this, callfuncO_selector(TextureCacheLayer::loadingCallBack));
#define ADDBGMUSIC(MUSIC)               SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSIC);
#define ADDEFFECT(EFFECT)               SimpleAudioEngine::sharedEngine()->preloadEffect(EFFECT);

// play background music
#define PLAYBGMUSIC(MUSIC)              SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC), true);
// stop background music
#define STOPBGMUSIC                     SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
// pause background music
#define PAUSEBGMUSIC                    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
// resume background music
#define RESUMEBGMUSIC                   SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
// rewind background music
#define REWINDBGMUSIC                   SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();

/* play effect
   return unsigned int EFFECTID */
#define PLAYEFFECT(EFFECT)              CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(EFFECT);
/* play effect recursive
   return unsigned int EFFECTID */
#define PLAYEFFECTRECURSE(EFFECT)       SimpleAudioEngine::sharedEngine()->playEffect((EFFECT), true);
// stop effect
#define STOPEFFECT(EFFECTID)            SimpleAudioEngine::sharedEngine()->stopEffect(EFFECTID);
// unload effect
#define UNLOADEFFECT(EFFECT)            SimpleAudioEngine::sharedEngine()->unloadEffect(EFFECT);
// add bakcground music volume
#define ADDBGMUSVOL(NUM)                 SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() + NUM);
// sub backgroud music volume
#define SUBBGMUSVOL(NUM)                 SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() - NUM);
// add effects volume
#define ADDEFFECTVOL(NUM)                SimpleAudioEngine::sharedEngine()->setEffectsVolume(SimpleAudioEngine::sharedEngine()->getEffectsVolume() + NUM);
// sub effects volume
#define SUBEFFECTVOL(NUM)               SimpleAudioEngine::sharedEngine()->setEffectsVolume(SimpleAudioEngine::sharedEngine()->getEffectsVolume() - NUM);
#define PAUSEEFFECT(EFFECTID)           SimpleAudioEngine::sharedEngine()->pauseEffect(EFFECTID);
#define RESUMEEFFECT(EFFECTID)          SimpleAudioEngine::sharedEngine()->resumeEffect(EFFECTID);
#define PAUSEALLEFFECTS                 SimpleAudioEngine::sharedEngine()->pauseAllEffects();
#define RESUMEALLEFFECTS                SimpleAudioEngine::sharedEngine()->resumeAllEffects();
#define STOPALLEFFECTS                  SimpleAudioEngine::sharedEngine()->stopAllEffects();

//MainMenu 1
#define MainMenu_background                 "MainMenu/background.png"
//GroupCustomization 10
#define GroupCustomization_start            "GroupCustomization/start.png"
#define GroupCustomization_start_selected   "GroupCustomization/start_selected.png"
#define GroupCustomization_back             "GroupCustomization/back.png"
#define GroupCustomization_back_selected    "GroupCustomization/back_selected.png"
#define GroupCustomization_blue             "GroupCustomization/blue.png"
#define GroupCustomization_green            "GroupCustomization/green.png"
#define GroupCustomization_red              "GroupCustomization/red.png"
#define GroupCustomization_yellow           "GroupCustomization/yellow.png"
#define GroupCustomization_stripe           "GroupCustomization/stripe.png"
#define GroupCustomization_dot              "GroupCustomization/dot.png"
#define GroupCustomization_lead_choise_colors              "GroupCustomization/lead_choise_colors.png"
//Timer
#define Timer_itm_timer_norm                "Timer/itm_timer_norm.png"
#define Timer_itm_timer_norm_light          "Timer/itm_timer_norm_light.png"
#define Timer_itm_timer_run_norm            "Timer/itm_timer_run_norm.png"
#define Timer_itm_timer_run_sel             "Timer/itm_timer_run_sel.png"
#define Timer_itm_timer_sel                 "Timer/itm_timer_sel.png"
#define Timer_itm_timer_stop_norm           "Timer/itm_timer_stop_norm.png"
#define Timer_itm_timer_stop_sel            "Timer/itm_timer_stop_sel.png"
#define Timer_timer_digits_active           "Timer/timer_digits_active.png"
#define Timer_timer_digits_light            "Timer/timer_digits_light.png"
#define Timer_timer_digits_passive          "Timer/timer_digits_passive.png"
#define Timer_timer_forest                  "Timer/timer_forest.png"
//Desk
#define _desk                               "desk.png"
#define _c_big                              "c_big.png"
//GameMenu 10
#define GameMenu_gamemenu                   "GameMenu/gamemenu.png"
#define GameMenu_help                       "GameMenu/help.png"
#define GameMenu_menu_button_a              "GameMenu/menu_button_a.png"
#define GameMenu_menu_button                "GameMenu/menu_button.png"
#define GameMenu_menu_forward_a             "GameMenu/menu_forward_a.png"
#define GameMenu_menu_forward               "GameMenu/menu_forward.png"
#define GameMenu_menu_button                "GameMenu/menu_button.png"
#define GameMenu_menu_rewind_a              "GameMenu/menu_rewind_a.png"
#define GameMenu_menu_rewind                "GameMenu/menu_rewind.png"
#define GameMenu_sound                      "GameMenu/sound.png"
#define GameMenu_swipe                      "GameMenu/swipe.png"
//RightControl 11
#define RightControl_c3_hybrid              "RightControl/c3_hybrid.png"
#define RightControl_c3                     "RightControl/c3.png"
#define RightControl_c3bottom               "RightControl/c3bottom.png"
#define RightControl_c3div                  "RightControl/c3div.png"
#define RightControl_c4_hybrid              "RightControl/c4_hybrid.png"
#define RightControl_c4                     "RightControl/c4.png"
#define RightControl_c4div                  "RightControl/c4div.png"
#define RightControl_c4bottom               "RightControl/c4bottom.png"
#define RightControl_c5_hybrid              "RightControl/c5_hybrid.png"
#define RightControl_c5                     "RightControl/c5.png"
#define RightControl_c5bottom               "RightControl/c5bottom.png"
#define RightControl_c5div                  "RightControl/c5div.png"
#define RightControl_itm_no_norm            "RightControl/itm_no_norm.png"
#define RightControl_itm_other_norm         "RightControl/itm_other_norm.png"
#define RightControl_itm_yes_norm           "RightControl/itm_yes_norm.png"
#define RightControl_c_blank0               "RightControl/c_blank0.png"
#define RightControl_c_blank1               "RightControl/c_blank1.png"
#define RightControl_c_blank2               "RightControl/c_blank2.png"
#define RightControl_c_blank3               "RightControl/c_blank3.png"
//RewindAnimation 2
#define RewindAnimation_rewind2             "RewindAnimation/rewind2.png"
#define RewindAnimation_rewind              "RewindAnimation/rewind.png"
//Tokens 5
#define tokens_token_blue                   "tokens/token_blue.png"
#define tokens_token_green                  "tokens/token_green.png"
#define tokens_token_red                    "tokens/token_red.png"
#define tokens_token_yellow                 "tokens/token_yellow.png"
#define tokens_token_shadow                 "tokens/token_shadow.png"
//SubMenu 6
#define SubMenu_2groups                     "SubMenu/2groups.png"
#define SubMenu_3gamers                     "SubMenu/3gamers.png"
#define SubMenu_3groups                     "SubMenu/3groups.png"
#define SubMenu_4groups               	    "SubMenu/4groups.png"
#define SubMenu_hint_bottom                 "SubMenu/hint_bottom.png"
#define SubMenu_lead_choise_groups          "SubMenu/lead_choise_groups.png"
//SN_icons 3
#define SN_icons_facebook_icon              "SN_icons/facebook_icon_60.png"
#define SN_icons_twitter_icon               "SN_icons/twitter_icon_60.png"
#define SN_icons_vkontakte_icon             "SN_icons/vkontakte_icon_60.png"

//music
#define MUSIC_MAIN                  "music/main.mp3"
#define _sndAlert                   "music/sndAlert.mp3"
#define _sndButton_group            "music/sndButton_group.wav"
#define _sndButton_inputname_end	"music/sndButton_inputname-end.wav"
#define _sndButton_inputname_start	"music/sndButton_inputname-start.wav"
#define _sndButton_plastik          "music/sndButton_plastik.mp3"
#define _sndButton_timer            "music/sndButton_timer.mp3"
#define _sndButton_wood             "music/sndButton_wood.mp3"
#define _sndCamera                  "music/sndCamera.wav"
#define _sndCheckcard               "music/sndCheckcard.mp3"
#define _sndForall                  "music/sndForall.mp3"
#define _sndMovescreen              "music/sndMovescreen.wav"
#define _sndSwipe                   "music/sndSwipe.mp3"
#define _sndTimer                   "music/sndTimer.mp3"
#define _sndToken                   "music/sndToken.mp3"
#define _sndVictory                 "music/sndVictory.wav"

//Положение источника света
#define LUM_X				10.0f//1100
#define LUM_Y				1900.0f
#define PI					3.14159265f

//mode
#define GAMERS_3			30
#define GROUP_2				31
#define GROUP_3				32
#define GROUP_4				33

//ID tokens
#define ID_BLUE				1
#define ID_RED				2
#define ID_GREEN			4
#define ID_YELLOW			8

#define CARDS				1001
#define RIGHTCONTROL		1002
#define DESKTOP				1003

//ID timers
#define TIMER				1004
#define ID_DIGITS_L			1005
#define ID_BUTTON_L			1006

#define HINT_LAYER			1010
#define ANSWER_LAYER		1011
#define CARD_LAYER			1012

#define REWIND_STRIPE		1013

//GameMenu
#define ID_GAMEMENU			1014
#define ID_SWIPE_RESTART	1015
#define ID_SWIPE_MAINMENU	1016
#define ID_TEXT_RESTART		1017
#define ID_TEXT_MAINMENU	1018
#define	ID_SHADOWLAYER		1019
#define ID_GMDESK			1020

//WinnerMenu
#define ID_WINNERMENU       1021
#define ID_WINNERDESK       1022
#define ID_WINNERGROUP      1023

//œÓÁËˆËÓÌËÓ‚‡ÌËÂ Í‡Ú
#define CARD_OFFSET_X		379
#define CARD_OFFSET_Y		-1
#define CARD_WIDTH			154
#define CARD_HEIGHT			126
#define CARD_PADDING		12

#define TABLEMAX			45
#define TABLEMIN			0

//red label
#define RED					1000

//Hint
#define TR					11000
#define TL					11001
#define BR					11002
#define BL					11003

//Cell table
class CellTable
{
public: 
	int m_Id;
	float m_X,m_Y;
	char m_Activity;
	int m_F;
	CellTable(int id, float x, float y, char activity, int F);
	void ChangeCellF(int F);
};

class SpriteTokenClass
{
public:
    ActionLayer* act;
	std::string *m_groupname;
	CCSprite* pS_F;
	CCSprite* pS_FShadow;
	int m_CurrentPosition;
	int m_CurNumber;
    int ingame;
public:
	SpriteTokenClass(ActionLayer* layer, CCSprite* ps, CCSprite* pss, int cp, CCPoint pos);
	void setCurrentPos(int pos);
    bool tokenIsActive();
    void removeToken();
};

class CGameLogic
{
public:
	CGameLogic(void);
	CGameLogic(ActionLayer * ptr);
	~CGameLogic(void);

	void setActionLayerPtr(ActionLayer * ptr) { act = ptr; }
	int StartGame();
	int ContinueGame();
	int FinishGame();

private:
	ActionLayer * act;

};

class GameMenuLayer : public CCLayer
{
public:
    GameMenuLayer();
private:
	//void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event); 
	virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *withEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *withEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *withEvent);	

	bool CheckPoint(CCPoint cp);
	bool checked;

	CCSprite * cex;
	CCLabelTTF* cel;
	CCSprite* pS_Swipe1;
	CCSprite* pS_Swipe2;
	int startSwipe;
	float endSwipe;
	float xStartPos;
	float xdelta;
};

class WinnerMenu : public CCLayer
{
public:
    WinnerMenu(ActionLayer* al, int Group);
private:
    void itm_continueCallback(CCObject* pSender);
    void itm_newgameCallback(CCObject* pSender);
    void itm_mainmenuCallback(CCObject* pSender);
};

class ActionLayer : public CCLayer
{
	DBWord* dbw;
public:
	ActionLayer();
	ActionLayer(int GameMode, std::string *RedName, std::string *GreenName, std::string *BlueName, std::string *YellowName);
	~ActionLayer();

	
	int m_GameMode;
	string *m_RedName, *m_GreenName, *m_BlueName, *m_YellowName;
	int numGroupsInGame;
    int allactivetokens;

	//Центр экрана
	CCSize size;
	float x,y;

	CellTable* tbl[TABLEMAX];

	//Cancel actions
	CGroup groups[4];
	CGroup * curGroupPtr;
	CSnapshots snaps;

	//game logic
	CGameLogic gl;
	CCLabelTTF * pLabelGroup;
	int curCardPrice;
	int setOpponentCommand;

    //add/remove menu touch delegates
    void SaveMenuState();
    void RestoreMenuState();
    int menustate;
    
	//»„Ó‚˚Â ÙË¯ÍË
	SpriteTokenClass* tokens[4];
	SpriteTokenClass* active_token;//ÛÍ‡Á‡ÚÂÎ¸ Ì‡ ‡ÍÚË‚ÌÛ˛ ÙË¯ÍÛ
	int pre_current_group;
    int current_group;//‘ÓÍÛÒ ‡ÍÚË‚ÌÓÈ ÍÓÏ‡Ì‰˚
	int FMoveTroubles(SpriteTokenClass* active_token, int h);
	int FMove(SpriteTokenClass* st, int h);
	int FMoveCor(SpriteTokenClass* st, int h);
	SpriteTokenClass* GetTokenByTag(int Tag);
    void PlayTokenEffectCallback();

	//??
	CCSprite* checked_card;
	CCSprite* checked_card_face;

	//‘Ë¯ÍË
	CCSprite* token1;
	CCSprite* token;

	//Cards
    int RedCard;
	CCMenu* mn_Cards;
	CCMenuItemImage* itm_card3;
	CCMenuItemImage* itm_card4;
	CCMenuItemImage* itm_card5;
	float m_mnCardsX; //menu position
	float m_mnCardsY;
	void itm_card3Callback(CCObject* pSender);
	void itm_card4Callback(CCObject* pSender);
	void itm_card5Callback(CCObject* pSender);
	void MoveCardFromControl();
	void MoveCardFromControlCallback();
	void MoveCardFaceSide();
	void DropCard();
	CCLabelTTF* word;

	//Answers
	CCMenu* mn_Answers;
	CCMenuItemImage* itm_yes;
	CCMenuItemImage* itm_no;
	CCMenuItemImage* itm_other;
	void itm_yesCallback(CCObject* pSender);
	void itm_noCallback(CCObject* pSender);
	void itm_otherCallback(CCObject* pSender);
	void ShowAnswersMenu(int Mode);
	void ShowAnswerCard(const char* fHybrid, const char* fTop, const char* fBottom, CCPoint Position, float delay);
	void ShowAnswerCardCallback();

	//WhoAnswer
	CCMenu* mn_WhoAnswer;
	CCMenuItem* itm_1opponent;
	CCMenuItem* itm_2opponent;
	CCMenuItem* itm_3opponent;
	void itm_1opponentCallback(CCObject* pSender);
	void itm_2opponentCallback(CCObject* pSender);
	void itm_3opponentCallback(CCObject* pSender);
	void ShowWhoAnswerMenu(int GameMode);

	//Timer
	CCLayer* pL_Timer;
	CCMenu* mn_Timer;
	CCMenuItem* itm_Timer_start;
	CCMenuItem* itm_Timer_pause;
	CCMenuItem* itm_Timer_run;
	CCProgressTo *to1;
	CCProgressTimer *lefttime;
	void itm_TimerStartCallback(CCObject* pSender);
	void itm_TimerPauseCallback(CCObject* pSender);
	void itm_TimerRunCallback(CCObject* pSender);
	void ShowTimer();
	void HideTimer();
	void TimerOver();
	void setTimerMode(int mode);
    unsigned int effect_id;

	//Hint
    int gamestate;
    int hint_act; //0-O, 1-P, 2-R
	void ShowHint(int Mode, CCPoint TargetPoint, const char* TextHint);
	void ShowHintCallback();

	//GameMenu
	CCMenu* game_menu;
	void itm_rewindCallback(CCObject* pSender);
	void itm_gamemenuCallback(CCObject* pSender);
	void itm_forwardCallback(CCObject* pSender);

	CCMenu* menu_question;
	void Card3Callback(CCObject* pSender);
	void Card4Callback(CCObject* pSender);
	void Card5Callback(CCObject* pSender);
	void CardPriceGo(CCObject* pSender);
	void GoBackOneCallback(CCObject* pSender);
	void ChangeSelectorCallback(CCObject* pSender);

	//RewindAnimation
	void RewindAnimation(CCLayer* parent);
	void RewindAnimationCallback();
    
    //Winners
    void ShowWinners(int Group);
};
#endif  // __CROCO_H__