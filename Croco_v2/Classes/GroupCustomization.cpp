#include "GroupCustomization.h"

void GroupCustomization::itm_backCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->popScene();
    
    PLAYEFFECT(_sndButton_plastik)
}
void GroupCustomization::itm_startCallback(CCObject* pSender)
{
	int check = CheckGroupNames(m_GameMode);
	
	//if exists fails move to fail page
	if(check) pScrollLayer->moveToPage(check); else
	{
	CCScene* pScene = CCScene::create();
	CCLayer* pLayer = new ActionLayer(m_GameMode,m_groups[0],m_groups[1],m_groups[2],m_groups[3]);
	pScene->addChild(pLayer);
	
	CCScene* s = CCTransitionFade::transitionWithDuration((1.2f), pScene);
	pLayer->release();
	CCDirector::sharedDirector()->replaceScene(s);
	}
    
    PLAYEFFECT(_sndButton_plastik)
}

static CCRect getRect(CCNode * pNode)
{
    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();
    rc.origin.x -= rc.size.width/2;
	rc.origin.y -= rc.size.height;
    return rc;
}

// implement KeyboardNotificationLayer
KeyboardNotificationLayer::KeyboardNotificationLayer()
: m_pTrackNode(0)
{
    setTouchEnabled(true);
}
void KeyboardNotificationLayer::registerWithTouchDispatcher()
{
    (CCDirector::sharedDirector()->getTouchDispatcher())->addTargetedDelegate(this, 0, false);
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
    
    PLAYEFFECT(_sndButton_inputname_start)
}
void KeyboardNotificationLayer::keyboardWillHide(CCIMEKeyboardNotificationInfo& info)
{
    PLAYEFFECT(_sndButton_inputname_end)
}

// CCLayer function
bool KeyboardNotificationLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLOG("++++++++++++++++++++++++++++++++++++++++++++");
    m_beginPos = pTouch->locationInView();	
    m_beginPos = CCDirector::sharedDirector()->convertToGL(m_beginPos);
    return true;
}
void KeyboardNotificationLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (! m_pTrackNode)
    {
        return;
    }
    
    CCPoint endPos = pTouch->locationInView();	
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

	//add background sprite
	CCSprite* background = CCSprite::spriteWithFile(MainMenu_background);
	addChild(background,0);
	background->setPosition(ccp(x,y));
    
    //add leather
	CCSprite* lth = CCSprite::spriteWithFile(GroupCustomization_lead_choise_colors);
    addChild(lth,0);
    lth->setAnchorPoint(ccp(0.5,1));
	lth->setPosition(ccp(x,y*2));

	KeyboardNotificationLayer* knlGroups[4];

	knlGroups[0] = new CurrentGroupLayer(ID_RED,1);
	knlGroups[1] = new CurrentGroupLayer(ID_GREEN,2);
	layers.addObject(knlGroups[0]);
	layers.addObject(knlGroups[1]);
	knlGroups[0]->release();
	knlGroups[1]->release();
	switch (GameMode)
	{
		case GAMERS_3:
			knlGroups[2] = new CurrentGroupLayer(ID_BLUE,3);
			layers.addObject(knlGroups[2]);
			knlGroups[2]->release();
			break;
		case GROUP_3:	
			knlGroups[2] = new CurrentGroupLayer(ID_BLUE,3);
			layers.addObject(knlGroups[2]);
			knlGroups[2]->release();
			break;
		case GROUP_4:
			knlGroups[2] = new CurrentGroupLayer(ID_BLUE,3);
			knlGroups[3] = new CurrentGroupLayer(ID_YELLOW,4);
			layers.addObject(knlGroups[2]);
			layers.addObject(knlGroups[3]);
			knlGroups[2]->release();
			knlGroups[3]->release();
			break;
	}

	pScrollLayer = CCScrollLayer::layerWithLayers(&layers,500);
	addChild(pScrollLayer);
	pScrollLayer->setPosition(ccp(0,0));

	setPageIndicator(pScrollLayer->currentScreen,pScrollLayer->totalScreens);
	//scale and opacity elements on disable layer
	((CurrentGroupLayer*)layers.objectAtIndex(0))->setContentAccess(1);

	CCMenuItem* itm_back = CCMenuItemImage::itemWithNormalImage(GroupCustomization_back,GroupCustomization_back_selected,this,menu_selector(GroupCustomization::itm_backCallback));
	itm_back->setPosition(ccp(-(x*2/2.2),-(y*2/2.22)));

	CCMenuItem* itm_start = CCMenuItemImage::itemWithNormalImage(GroupCustomization_start,GroupCustomization_start_selected,this,menu_selector(GroupCustomization::itm_startCallback));
	itm_start->setPosition(ccp(+(x*2/2.27),-(y*2/2.27)));

	CCMenu* mn_GroupCustomization = CCMenu::menuWithItems(itm_back,itm_start,NULL);
	addChild(mn_GroupCustomization,1);
	mn_GroupCustomization->setPosition(ccp(x,y));
}
void CurrentGroupLayer::onExit()
{
    KeyboardNotificationLayer::onExit();
    m_pTextFieldAction->release();
}

// CCTextFieldDelegate protocol
bool CurrentGroupLayer::onTextFieldAttachWithIME(CCTextFieldTTF * pSender)
{
    if (!m_bAction)
    {
        m_pTextField->runAction(m_pTextFieldAction);
        m_bAction = true;

		if(((CCScrollLayer*)this->getParent())->currentScreen!=m_index) 
			{
				((CCScrollLayer*)this->getParent())->moveToPage(m_index);
			}
        
        float adjustVert;// = CCRect::CCRectGetMaxY(info.end) - CCRect::CCRectGetMinY(rectTracked);
        adjustVert = 100.0f;
        CCLOG("TextInputTest:needAdjustVerticalPosition(%f)", adjustVert);
        CCActionInterval* ai_move = CCEaseInOut::actionWithAction(CCMoveBy::actionWithDuration(0.8f, ccp(0,adjustVert)),2.0f);
        //move all the children node of KeyboardNotificationLayer
        CCArray * children = ((CCLayer*)m_pTextField->getParent())->getChildren();
        CCNode * node = 0;
        int count = children->count();
        CCPoint pos;
        for (int i = 0; i < count; ++i)
        {
            node = (CCNode*)children->objectAtIndex(i);
            //pos = node->getPosition();
            //pos.y -= adjustVert;
            //node->setPosition(pos);
            node->runAction((CCActionInterval*)ai_move->copy()->autorelease());
        }

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
        
        float adjustVert;// = CCRect::CCRectGetMaxY(info.end) - CCRect::CCRectGetMinY(rectTracked);
        adjustVert = 100.0f;
        CCLOG("TextInputTest:needAdjustVerticalPosition(%f)", adjustVert);
        CCActionInterval* ai_move = CCEaseBounceOut::actionWithAction(CCMoveBy::actionWithDuration(1.0f, ccp(0,-adjustVert)));
        //move all the children node of KeyboardNotificationLayer
        CCArray * children = ((CCLayer*)m_pTextField->getParent())->getChildren();
        CCNode * node = 0;
        int count = children->count();
        CCPoint pos;
        for (int i = 0; i < count; ++i)
        {
            node = (CCNode*)children->objectAtIndex(i);
            //pos = node->getPosition();
            //pos.y -= adjustVert;
            //node->setPosition(pos);
            node->runAction((CCActionInterval*)ai_move->copy()->autorelease());
        }
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
CurrentGroupLayer::CurrentGroupLayer(int idColor, int index)
{	
	m_isAccessable = true;
	m_index = index;
	int color_index=0;
	switch (idColor)
	{
		case ID_GREEN: color_index=1;break;
		case ID_BLUE: color_index=2;break;
		case ID_YELLOW:	color_index=3;break;
	}

	const char* m_colors[] = {
		GroupCustomization_red,
		GroupCustomization_green,
		GroupCustomization_blue,
		GroupCustomization_yellow
	};

	KeyboardNotificationLayer::onEnter();
	
	//Coords of center screen
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	x = size.width/2;
    y = size.height/2;

	//Layer with COLOR and LABEL
	CCLayer* control = CCLayer::node();
	addChild(control,1,ID_CONTROLLAYER);

	//Color box
	CCSprite* s_Color = CCSprite::spriteWithFile(m_colors[color_index]);
	control->addChild(s_Color,1,ID_COLORBOX);
	s_Color->setPosition(ccp(x,y+80.0f));//relative position of color token icon

	
	/*
	CCActionInterval* ai_scale_in = CCEaseOut::actionWithAction(CCScaleTo::actionWithDuration(0.1f,1.05f,1.05f),3.0f);
	CCActionInterval* ai_delay05 = CCDelayTime::actionWithDuration(0.5f);
	CCActionInterval* ai_scale_out = CCEaseElasticOut::actionWithAction(CCScaleTo::actionWithDuration(0.6f,1.0f,1.0f));
	CCActionInterval* ai_delay4 = CCDelayTime::actionWithDuration(4.0f);

	s_Color->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)
		CCSequence::actions(
		ai_scale_in,ai_delay05,ai_scale_out,ai_delay4
		,NULL)->copy()->autorelease()
		));
		*/

	//white stripe
	CCSprite* sStripe = CCSprite::spriteWithFile(GroupCustomization_stripe);
	control->addChild(sStripe,0,ID_STRIPE);
	sStripe->setPosition(ccp(x,y-90.0f)); //relative position of white stripe

	//Default names
	char default_name[CHAR_LIMIT];
	char num[2]; sprintf(num,"%d",index);
	strcpy(default_name,"Команда ");
	strcat(default_name,num);

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
	m_pTextField = CCTextFieldTTF::textFieldWithPlaceHolder(default_name,
        FONT_NAME,
        FONT_SIZE);
    m_pTextField->setColorSpaceHolder(ccc3(28,16,5));
    control->addChild(m_pTextField,1,ID_TEXTFIELD);

	m_pTextField->setDelegate(this);
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	// on android, CCTextFieldTTF cannot auto adjust its position when soft-keyboard pop up
	// so we had to set a higher position
	m_pTextField->setPosition(ccp(x,y - 50));
#else
	m_pTextField->setPosition(ccp(x,y-90.0f)); //-150 Y
#endif
    m_pTrackNode = m_pTextField;
	
	setContentAccess(0);
}
const char* CurrentGroupLayer::getTextField()
{
	return m_pTextField->getString();
}

//SetContentAccess
//state
//1 - active
//2 - passive
void CurrentGroupLayer::setContentAccess(bool state)
{
	CCLayer* spr = (CCLayer*)this->getChildByTag(ID_CONTROLLAYER);
	spr->stopAllActions();
	CCActionInterval* scalein = CCScaleTo::actionWithDuration(0.2f,1.2f,1.2f);
	CCActionInterval* scaleout = CCScaleTo::actionWithDuration(0.2f,1.0f,1.0f);

	CCActionInterval* fadetoin = CCFadeTo::actionWithDuration(0.2f,255);
	CCActionInterval* fadetoout = CCFadeTo::actionWithDuration(0.2f,180);

	if(state)
	{
		((CCSprite*)(spr->getChildByTag(ID_TEXTFIELD)))->runAction(CCEaseInOut::actionWithAction((CCActionInterval*)fadetoin->copy()->autorelease(),2.0f));
		((CCSprite*)(spr->getChildByTag(ID_COLORBOX)))->runAction(CCEaseInOut::actionWithAction((CCActionInterval*)fadetoin->copy()->autorelease(),2.0f));
		((CCSprite*)(spr->getChildByTag(ID_STRIPE)))->runAction(CCEaseInOut::actionWithAction((CCActionInterval*)fadetoin->copy()->autorelease(),2.0f));
		spr->runAction(CCEaseInOut::actionWithAction((CCActionInterval*)scalein->copy()->autorelease(),2.0f));
		m_isAccessable = true;
        
	} else {
		((CCSprite*)(spr->getChildByTag(ID_TEXTFIELD)))->runAction(CCEaseInOut::actionWithAction((CCActionInterval*)fadetoout->copy()->autorelease(),2.0f));
		((CCSprite*)(spr->getChildByTag(ID_COLORBOX)))->runAction(CCEaseInOut::actionWithAction((CCActionInterval*)fadetoout->copy()->autorelease(),2.0f));
		((CCSprite*)(spr->getChildByTag(ID_STRIPE)))->runAction(CCEaseInOut::actionWithAction((CCActionInterval*)fadetoout->copy()->autorelease(),2.0f));
		spr->runAction(CCEaseInOut::actionWithAction((CCActionInterval*)scaleout->copy()->autorelease(),2.0f));
		
		//hide keyboard
		this->onClickTrackNode(0);
		m_isAccessable = false;
	}
}

//Page Indicator
void GroupCustomization::setPageIndicator(int currentPage, int count)
{
	//set parameters
	int interval = 22;
	int opacity = 70;

	//draw indicator
	this->removeChildByTag(PAGE_INDICATOR,1);
	CCLayer* pi = CCLayer::create();
	addChild(pi,2,PAGE_INDICATOR);
	//pi->setPosition(ccp(0,0));
	CCSprite* dots[4];
	for(int i=0;i<count;i++)
	{
		dots[i]=CCSprite::spriteWithFile(GroupCustomization_dot);
		pi->addChild(dots[i],2);
		dots[i]->setPosition(ccp(x-((dots[i]->getContentSize().width*count+interval*count)/count)+i*interval,65));
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
	/*
	for(int i=0;i<count;i++)
	{
		if(strlen(((CurrentGroupLayer*)layers.getObjectAtIndex(i))->getTextField())==0) return i+1;
	}
	*/
	//setGroupName
	for(int i=0;i<count;i++) 
		if(strlen(((CurrentGroupLayer*)layers.objectAtIndex(i))->getTextField())==0)
		{
			setGroupName(i,((CCTextFieldTTF*)((CCLayer*)((CurrentGroupLayer*)layers.objectAtIndex(i))->getChildByTag(ID_CONTROLLAYER))->getChildByTag(ID_TEXTFIELD))->getPlaceHolder());
		}
		else
		{
			setGroupName(i,((CurrentGroupLayer*)layers.objectAtIndex(i))->getTextField());
		}
	return ret;
}

//Scale color box and input label when move to active layer
void GroupCustomization::scaleElements(bool active, int currentScreen)
{
}