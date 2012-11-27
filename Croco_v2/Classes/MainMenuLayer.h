#include "CrocoBoardGame.h"

#define ID_TONE				1
#define ID_RADIO			2

class MainMenuLayer : public CCLayer
{
	int m_isGameStarted;
	CCSprite* pS_Light;

	CCMenu* mn_radio;
	CCMenuItemImage* itm_radio;
	int radio_active;
public:
	MainMenuLayer(int isGame_Started);
	// The CallBack for back to the main menu scene
	void itm_ContinueCallback(CCObject* pSender);
    void itm_StartCallback(CCObject* pSender);
	void itm_CreditsCallback(CCObject* pSender);
	
	void itm_radioCallback(CCObject* pSender);
	void RadioOn(int active);

	void ShowTonesCallback();
	void ShowTones(CCMenuItemImage* parent);
	void ToneTerminateCallback();

	void ShowBlickCallback();
	void ShowBlick(CCSprite* parent, const char* dot, float Time, int intensive);
};

