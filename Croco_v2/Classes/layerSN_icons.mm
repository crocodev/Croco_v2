//
//  layerSN_icons.cpp
//  Croco
//
//  Created by admin on 08.07.12.
//
//

#include "layerSN_icons.h"

layerSN_icons::layerSN_icons()
{
    //screen center
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItemImage *itm_Tw = CCMenuItemImage::create(SN_icons_twitter_icon,SN_icons_twitter_icon,this,menu_selector(layerSN_icons::itm_TwCallback));
    CCMenuItemImage *itm_Fb = CCMenuItemImage::create(SN_icons_facebook_icon,SN_icons_facebook_icon,this,menu_selector(layerSN_icons::itm_FbCallback));
    CCMenuItemImage *itm_Vk = CCMenuItemImage::create(SN_icons_vkontakte_icon,SN_icons_vkontakte_icon,this,menu_selector(layerSN_icons::itm_VkCallback));
    CCMenu *mnSN_icons = CCMenu::create(itm_Tw,itm_Fb,itm_Vk,NULL);
    mnSN_icons->alignItemsHorizontallyWithPadding(size.width/24);
    addChild(mnSN_icons);
    mnSN_icons->setPosition(ccp(size.width*3/4,size.height/16));
}

layerSN_icons::~layerSN_icons()
{
    ;
}

void layerSN_icons::itm_TwCallback(CCObject* pSender)
{
    // Create an account store object.
	ACAccountStore *accountStore = [[ACAccountStore alloc] init];
	
	// Create an account type that ensures Twitter accounts are retrieved.
    ACAccountType *accountType = [accountStore accountTypeWithAccountTypeIdentifier:ACAccountTypeIdentifierTwitter];
	
	// Request access from the user to use their Twitter accounts.
    [accountStore requestAccessToAccountsWithType:accountType withCompletionHandler:^(BOOL granted, NSError *error) {
        if(granted) {
			// Get the list of Twitter accounts.
            NSArray *accountsArray = [accountStore accountsWithAccountType:accountType];
			
			// For the sake of brevity, we'll assume there is only one Twitter account present.
			// You would ideally ask the user which account they want to tweet from, if there is more than one Twitter account present.
			if ([accountsArray count] > 0) {
				// Grab the initial Twitter account to tweet from.
				ACAccount *twitterAccount = [accountsArray objectAtIndex:0];
				
				// Create a request, which in this example, posts a tweet to the user's timeline.
				// This example uses version 1 of the Twitter API.
				// This may need to be changed to whichever version is currently appropriate.
				TWRequest *postRequest = [[TWRequest alloc] initWithURL:[NSURL URLWithString:@"http://api.twitter.com/1/statuses/update.json"] parameters:[NSDictionary dictionaryWithObject:@"Hello. This is a tweet." forKey:@"status"] requestMethod:TWRequestMethodPOST];
				
				// Set the account used to post the tweet.
				[postRequest setAccount:twitterAccount];
				
				// Perform the request created above and create a handler block to handle the response.
				[postRequest performRequestWithHandler:^(NSData *responseData, NSHTTPURLResponse *urlResponse, NSError *error) {
					NSString *output = [NSString stringWithFormat:@"HTTP response status: %i", [urlResponse statusCode]];
					//[self performSelectorOnMainThread:@selector(displayText:) withObject:output waitUntilDone:NO];
				}];
			}
        }
	}];
}

void layerSN_icons::itm_FbCallback(CCObject* pSender)
{
    //Facebook
     FBC *pFBC = [[FBC alloc] init];
     [pFBC FBExec];
}

void layerSN_icons::itm_VkCallback(CCObject* pSender)
{
    //VK
     VKConnectViewController* vkw = [[VKConnectViewController alloc] init];
     [vkw Connect];
}