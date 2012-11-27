//
//  FBC.h
//  Croco
//
//  Created by admin on 14.06.12.
//
//

#import <Foundation/Foundation.h>
#import "FBConnect.h"

@interface FBC : NSObject <UIApplicationDelegate, FBSessionDelegate, FBDialogDelegate>
{
    Facebook *facebook;
}

@property (strong, nonatomic) UIWindow *window;
@property (nonatomic, retain) Facebook *facebook;

-(void) FBExec;

@end