//
//  VKConnectViewController.h
//  Croco
//
//  Created by admin on 06.07.12.
//
//

#import <UIKit/UIKit.h>

@interface VKConnectViewController : UIViewController <UIWebViewDelegate> {
    UIWebView *webview;
}

- (void) Connect;
- (void) Post: (NSString*) access_token;
- (NSString*)stringBetweenString:(NSString*)start 
                       andString:(NSString*)end 
                     innerString:(NSString*)str;

@end
