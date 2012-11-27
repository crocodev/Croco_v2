#include "GroupCustomization.h"

#define ID_LABEL	10

void GroupCustomization::itm_backCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->popScene();
}
void GroupCustomization::itm_startCallback(CCObject* pSender)
{
	int check = CheckGroupNames(m_GameMode);
	
	//if exists fails move to fail page
	if(check) pScrollLayer->moveToPage(check); else
	{
	CCScene* pScene = CCScene::node();	
	CCLayer* pLayer = new ActionLayer(m_GameMode,m_groups[0],m_groups[1],m_groups[2],m_groups[3]);
	pScene->addChild(pLayer);
	
	CCScene* s = CCTransitionFade::transitionWithDuration((1.2f), pScene);
	pLayer->release();
	CCDirector::sharedDirector()->replaceScene(s);
	}
}

static CCRect getRect(CCNode * pNode)
{
    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();
    rc.origin.x -= rc.size.width / 2;
    rc.origin.y -= rc.size.height / 2;
    return rc;
}

// implement KeyboardNotificationLayer
KeyboardNotificationLayer::KeyboardNotificationLayer()
: m_pTrackNode(0)
{
    setIsTouchEnabled(true);
}
void KeyboardNotificationLayer::registerWithTouchDispatcher()
{
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, false);
}
void KeyboardNotificationLayer::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{
    CCLOG("TextInputTest:keyboardWillShowAt(origin:%f,%f, size:%f,%f)",
        info.end.origin.x, info.end.origin.y, info.end.size.width, info.end.size.height);
	
    if (! m_pTrackNode)
    {
        return;
    }

	CCRect rectTracked = getRect(m_pTrackNode);
    CCLOG("TextInputTest:trackingNodeAt(origin:%f,%f, size:%f,%f)",
        rectTracked.origin.x, rectTracked.origin.y, rectTracked.size.width, rectTracked.size.height);
	
    // if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
    if (! CCRect::CCRectIntersectsRect(rectTracked, info.end))
    {
        return;
    }

    // assume keyboard at the bottom of screen, calculate the vertical adjustment.
    float adjustVert = CCRect::CCRectGetMaxY(info.end) - CCRect::CCRectGetMinY(rectTracked);
    CCLOG("TextInputTest:needAdjustVerticalPosition(%f)", adjustVert);

    // move all the children node of KeyboardNotificationLayer
    
	CCArray * children = getChildren();
    CCNode * node = 0;
    int count = children->count();
    CCPoint pos;
    for (int i = 0; i < count; ++i)
    {
        node = (CCNode*)children->objectAtIndex(i);
        pos = node->getPosition();
        pos.y += adjustVert;
        node->setPosition(pos);
    }
	
}
// CCLayer function
bool KeyboardNotificationLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLOG("++++++++++++++++++++++++++++++++++++++++++++");
    m_beginPos = pTouch->locationInView(pTouch->view());	
    m_beginPos = CCDirector::sharedDirector()->convertToGL(m_beginPos);
    return true;
}
void KeyboardNotificationLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (! m_pTrackNode)
    {
        return;
    }
    
    CCPoint endPos = pTouch->locationInView(pTouch->view());	
    endPos = CCDirector::sharedDirector()->convertToGL(endPos);

    float delta = 5.0f;
    if (::abs(endPos.x - m_beginPos.x) > delta
        || ::abs(endPos.y - m_beginPos.y) > delta)
    {
        // not click
        m_beginPos.x = m_beginPos.y = -1;
        return;
    }

    // decide the trackNode is clicked.
    CCRect rect;
    CCPoint point = convertTouchToNodeSpaceAR(pTouch);
    CCLOG("KeyboardNotificationLayer:clickedAt(%f,%f)", point.x, point.y);

    rect = getRect(m_pTrackNode);
    CCLOG("KeyboardNotificationLayer:TrackNode at(origin:%f,%f, size:%f,%f)",
        rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);

    this->onClickTrackNode(CCRect::CCRectContainsPoint(rect, point));
    CCLOG("----------------------------------");
}

void CurrentGroupLayer::onClickTrackNode(bool bClicked)
{
    CCTextFieldTTF * pTextField = (CCTextFieldTTF*)m_pTrackNode;
    if (bClicked)
    {
        // TextFieldTTFTest be clicked
        CCLOG("TextFieldTTFActionTest:CCTextFieldTTF attachWithIME");
        pTextField->attachWithIME();
    }
    else
    {
        // TextFieldTTFTest not be clicked
        CCLOG("TextFieldTTFActionTest:CCTextFieldTTF detachWithIME");
        pTextField->detachWithIME();
    }
}

// implement GroupCustomization
void CurrentGroupLayer::onEnter()
{
}

GroupCustomization::GroupCustomization(int GameMode)
{
	//set game mode
	m_GameMode = GameMode;

	//init colors
	for(int i=0;i<4;i++)
	{
		setGroupName(i,NULL);
	}
	
	//set center of the screen
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	x = size.width/2;
    y = size.height/2;

	CCSprite* background = CCSprite::spriteWithFile("GroupCustomization/background.png");
	addChild(background,0);
	background->setPosition(ccp(x,y));

	KeyboardNotificationLayer* knlGroups[4];

	switch (GameMode)
	{
		case GAMERS_3:
			knlGroups[0] = new CurrentGroupLayer(ID_RED);
			knlGroups[1] = new CurrentGroupLayer(ID_GREEN);
			knlGroups[2] = new CurrentGroupLayer(ID_BLUE);
			layers.addObject(knlGroups[0]);
			layers.addObject(knlGroups[1]);
			layers.addObject(knlGroups[2]);
			knlGroups[0]->release();
			knlGroups[1]->release();
			knlGroups[2]->release();
			break;
		case GROUP_2:
			knlGroups[0] = new CurrentGroupLayer(ID_RED);
			knlGroups[1] = new CurrentGroupLayer(ID_GREEN);
			layers.addObject(knlGroups[0]);
			layers.addObject(knlGroups[1]);
			knlGroups[0]->release();
			knlGroups[1]->release();
			break;
		case GROUP_3:	
			knlGroups[0] = new CurrentGroupLayer(ID_RED);
			knlGroups[1] = new CurrentGroupLayer(ID_GREEN);
			knlGroups[2] = new CurrentGroupLayer(ID_BLUE);
			layers.addObject(knlGroups[0]);
			layers.addObject(knlGroups[1]);
			layers.addObject(knlGroups[2]);
			knlGroups[0]->release();
			knlGroups[1]->release();
			knlGroups[2]->release();
			break;
		case GROUP_4:
			knlGroups[0] = new CurrentGroupLayer(ID_RED);
			knlGroups[1] = new CurrentGroupLayer(ID_GREEN);
			knlGroups[2] = new CurrentGroupLayer(ID_BLUE);
			knlGroups[3] = new CurrentGroupLayer(ID_YELLOW);
			layers.addObject(knlGroups[0]);
			layers.addObject(knlGroups[1]);
			layers.addObject(knlGroups[2]);
			layers.addObject(knlGroups[3]);
			knlGroups[0]->release();
			knlGroups[1]->release();
			knlGroups[2]->release();
			knlGroups[3]->release();
			break;
	}
	pScrollLayer = CCScrollLayer::layerWithLayers(&layers,0);
	addChild(pScrollLayer);
	pScrollLayer->setPosition(ccp(0,0));

	setPageIndicator(pScrollLayer->currentScreen,pScrollLayer->totalScreens);

	CCMenuItem* itm_back = CCMenuItemImage::itemFromNormalImage("GroupCustomization/back_normal.png","GroupCustomization/back_selected.png",this,menu_selector(GroupCustomization::itm_backCallback));
	itm_back->setAnchorPoint(ccp(0,0));
	itm_back->setPosition(ccp(10,10));

	CCMenuItem* itm_start = CCMenuItemImage::itemFromNormalImage("GroupCustomization/start_normal.png","GroupCustomization/start_normal.png",this,menu_selector(GroupCustomization::itm_startCallback));
	itm_start->setAnchorPoint(ccp(0,0));
	itm_start->setPosition(ccp(size.width-195,10));

	CCMenu* mn_GroupCustomization = CCMenu::menuWithItems(itm_back,itm_start,NULL);
	addChild(mn_GroupCustomization,1);
	mn_GroupCustomization->setPosition(ccp(0,0));
}
void CurrentGroupLayer::onExit()
{
    KeyboardNotificationLayer::onExit();
    m_pTextFieldAction->release();
}

// CCTextFieldDelegate protocol
bool CurrentGroupLayer::onTextFieldAttachWithIME(CCTextFieldTTF * pSender)
{
    if (! m_bAction)
    {
        m_pTextField->runAction(m_pTextFieldAction);
        m_bAction = true;
    }
    return false;
}
bool CurrentGroupLayer::onTextFieldDetachWithIME(CCTextFieldTTF * pSender)
{
    if (m_bAction)
    {
        m_pTextField->stopAction(m_pTextFieldAction);
        m_pTextField->setOpacity(255);
        m_bAction = false;
    }
    return false;
}
bool CurrentGroupLayer::onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen)
{
    // if insert enter, treat as default to detach with ime
	if ('\n' == *text)
    {
        return false;
    }
    // if the textfield's char count more than m_nCharLimit, doesn't insert text anymore.
    if (pSender->getCharCount() >= m_nCharLimit)
    {
        return true;
    }
    // create a insert text sprite and do some action
    //CCLabelTTF * label = CCLabelTTF::labelWithString(text, FONT_NAME, FONT_SIZE);
    //this->addChild(label);
    //ccColor3B color = { 226, 121, 7};
    //label->setColor(color);
    return false;
}
bool CurrentGroupLayer::onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen)
{
    // create a delete text sprite and do some action
    //CCLabelTTF * label = CCLabelTTF::labelWithString(delText, FONT_NAME, FONT_SIZE);
    //this->addChild(label);
	return false;
}
bool CurrentGroupLayer::onDraw(CCTextFieldTTF * pSender)
{
    return false;
}
void CurrentGroupLayer::callbackRemoveNodeWhenDidAction(CCNode * pNode)
{
    this->removeChild(pNode, true);
}

//implementation CurrentGroupLayer 
CurrentGroupLayer::CurrentGroupLayer(int idColor)
{	
	int color_index=0;
	switch (idColor)
	{
		case ID_GREEN: color_index=1;break;
		case ID_BLUE: color_index=2;break;
		case ID_YELLOW:	color_index=3;break;
	}

	const char* m_colors[] = {
		"GroupCustomization/red.png",
		"GroupCustomization/green.png",
		"GroupCustomization/blue.png",
		"GroupCustomization/yellow.png"
	};

	KeyboardNotificationLayer::onEnter();
	
	//Coords of center screen
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	x = size.width/2;
    y = size.height/2;

	//Color box
	CCSprite* s_Color = CCSprite::spriteWithFile(m_colors[color_index]);
	addChild(s_Color,1);
	s_Color->setPosition(ccp(x+COLOR_POS_X,y+COLOR_POS_Y));

	//white stripe
	CCSprite* sStripe = CCSprite::spriteWithFile("GroupCustomization/stripe.png");
	addChild(sStripe,0);
	sStripe->setPosition(ccp(x,y-40));
	sStripe->setOpacity(75);

	//TextInput
    m_nCharLimit = CHAR_LIMIT;

    m_pTextFieldAction = CCRepeatForever::actionWithAction(
        (CCActionInterval*)CCSequence::actions(
            CCFadeOut::actionWithDuration(0.25),
            CCFadeIn::actionWithDuration(0.25),
            0
        ));
    m_pTextFieldAction->retain();
    m_bAction = false;
	m_pTextField = CCTextFieldTTF::textFieldWithPlaceHolder("input u name",
        FONT_NAME,
        FONT_SIZE);
    addChild(m_pTextField,1,ID_LABEL);	 

	m_pTextField->setDelegate(this);
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)	
	// on android, CCTextFieldTTF cannot auto adjust its position when soft-keyboard pop up
	// so we had to set a higher position
	m_pTextField->setPosition(ccp(x / 2, y/2 + 50));
#else
	m_pTextField->setPosition(ccp(x,y-40)); //-150 Y
#endif
    m_pTrackNode = m_pTextField;
}
const char* CurrentGroupLayer::getTextField()
{
	return m_pTextField->getString();
}

//Page Indicator
void GroupCustomization::setPageIndicator(int currentPage, int count)
{
	//set parameters
	int interval = 22;
	int opacity = 70;

	//draw indicator
	this->removeChildByTag(PAGE_INDICATOR,1);
	CCLayer* pi = CCLayer::node();
	addChild(pi,2,PAGE_INDICATOR);
	pi->setPosition(ccp(0,0));
	CCSprite* dots[4];
	for(int i=0;i<count;i++)
	{
		dots[i]=CCSprite::spriteWithFile("GroupCustomization/dot.png");
		pi->addChild(dots[i],2);
		dots[i]->setPosition(ccp(x-((dots[i]->getContentSize().width*count+interval*count)/count)+i*interval,25));
		if(i!=currentPage-1) dots[i]->setOpacity(opacity);
	}
}

//Set group name
void GroupCustomization::setGroupName(int index, const char* name)
{
	//CC_SAFE_DELETE(m_groups[index]);
	if (name)
    {
        m_groups[index] = new std::string(name);
    }
    else
    {
        m_groups[index] = new std::string;
    }
}

//get group name
const char* GroupCustomization::getGroupName(int index)
{
	return m_groups[index]->c_str();
}
//check that all groups set names & set names
int GroupCustomization::CheckGroupNames(int GameMode)
{
	int count;
	int ret=0;
	
	if(!ret)
		return ret;

	switch (GameMode)
	{
		case GAMERS_3:
			count = 3;break;
		case GROUP_2:
			count =2;break;
		case GROUP_3:	
			count = 3;break;
			break;
		case GROUP_4:	
			count = 4;break;
			break;
	}
	//check group names
	for(int i=0;i<count;i++)
	{
		if(strlen(((CurrentGroupLayer*)layers.getObjectAtIndex(i))->getTextField())==0) return i+1;
	}
	//setGroupName
	for(int i=0;i<count;i++) setGroupName(i,((CurrentGroupLayer*)layers.getObjectAtIndex(i))->getTextField());
	return ret;
}