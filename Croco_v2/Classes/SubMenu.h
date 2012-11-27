#include "CrocoBoardGame.h"

#include "TextureCache.h"

class SubMenu : public CCLayer
{
public:
	SubMenu(void);
	void GoGroupCustomization(int GameMode);
	void itm_3gamersCallback(CCObject* pSender);
	void itm_2groupsCallback(CCObject* pSender);
	void itm_3groupsCallback(CCObject* pSender);
	void itm_4groupsCallback(CCObject* pSender);
	void itm_backCallback(CCObject* pSender);
};