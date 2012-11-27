#include "CrocoBoardGame.h"

//Name and color choise
#define ID_CONTROLLAYER		2010
#define ID_CGL_INDEX		2020
#define ID_COLORBOX			2021
#define ID_STRIPE			2022
#define ID_TEXTFIELD		2023

#define PAGE_INDICATOR		1000

//input name of the group
#define	CHAR_LIMIT			18

class GroupCustomization : public CCLayer
{
public:
	//GameMode
	int m_GameMode;

	//group names
	std::string * m_groups[4];

	GroupCustomization(int Gamemode);
	//Coordinates of center
	float x,y;

	void itm_backCallback(CCObject* pSender);
	void itm_startCallback(CCObject* pSender);
	void setPageIndicator(int currentPage, int count);
	void setGroupName(int index, const char* name);
	const char* getGroupName(int index);

	int CheckGroupNames(int GameMode);

	void scaleElements(bool active, int currentScreen);
	
	//scroll layers
	CCArray layers;
	CCScrollLayer* pScrollLayer;
};

// KeyboardNotificationLayer for test IME keyboard notification.
class KeyboardNotificationLayer : public CCLayer, public CCIMEDelegate
{
public:
    KeyboardNotificationLayer();

    virtual void onClickTrackNode(bool bClicked)=0;

    virtual void registerWithTouchDispatcher();
    virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info);
    virtual void keyboardWillHide(CCIMEKeyboardNotificationInfo& info);
    
    // CCLayer
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

protected:
    CCNode * m_pTrackNode;
    CCPoint  m_beginPos;
};

struct Colors
{
	const char* file;
	int used;
};

class CurrentGroupLayer: public CCTextFieldDelegate, public KeyboardNotificationLayer
{
	CCTextFieldTTF*    m_pTextField;
    CCAction*          m_pTextFieldAction;
    bool               m_bAction;
    int                m_nCharLimit;       // the textfield max char limit

	const wchar_t*		m_title;
	int					index;

public:
	//Coordinates of center
	float x,y;
	int m_index;

	CurrentGroupLayer(int idColor, int index);
	const char* getTextField();

	void setContentAccess(bool state);
	bool m_isAccessable;

	// CCLayer
    virtual void onEnter();
    virtual void onExit();
	
    // CCTextFieldDelegate
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF * pSender);
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * pSender);
    virtual bool onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen);
    virtual bool onDraw(CCTextFieldTTF * pSender);
	
	virtual void onClickTrackNode(bool bClicked);

	void callbackRemoveNodeWhenDidAction(CCNode * pNode);
};