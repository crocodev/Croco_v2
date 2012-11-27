//
//  VKConnectViewController.m
//  Croco
//
//  Created by admin on 06.07.12.
//
//

#import "VKConnectViewController.h"
#import "RootViewController.h"

@interface VKConnectViewController ()

@end

@implementation VKConnectViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void) Connect
{
    //Работает но не переворачивает экран
    webview = [[UIWebView alloc] initWithFrame:[UIScreen mainScreen].applicationFrame];
    webview.scalesPageToFit = YES;
    webview.autoresizesSubviews = YES;
    
    [webview setDelegate:self];
    
    NSString *authLink = [NSString stringWithFormat:@"http://api.vk.com/oauth/authorize?client_id=3004130&scope=wall&redirect_uri=http://api.vk.com/blank.html&display=touch&response_type=token"];
    NSURL *url = [NSURL URLWithString:authLink];
    
    [webview loadRequest:[NSURLRequest requestWithURL:url]];
    
    UIWindow* mWin = (UIWindow*)[[[UIApplication sharedApplication] windows] objectAtIndex:0];
    [mWin addSubview:webview];
}

-(void)webViewDidFinishLoad:(UIWebView *)webView {
    // Если есть токен сохраняем его
    if ([webview.request.URL.absoluteString rangeOfString:@"access_token"].location != NSNotFound) {
        NSString *accessToken = [self stringBetweenString:@"access_token=" 
                                                andString:@"&" 
                                              innerString:[[[webView request] URL] absoluteString]];
        
        // Получаем id пользователя, пригодится нам позднее
        NSArray *userAr = [[[[webView request] URL] absoluteString] componentsSeparatedByString:@"&user_id="];
        NSString *user_id = [userAr lastObject];
        NSLog(@"User id: %@", user_id);
        if(user_id){
            [[NSUserDefaults standardUserDefaults] setObject:user_id forKey:@"VKAccessUserId"];
        }
        
        if(accessToken){
            [[NSUserDefaults standardUserDefaults] setObject:accessToken forKey:@"VKAccessToken"];
            // Сохраняем дату получения токена. Параметр expires_in=86400 в ответе ВКонтакта, говорит сколько будет действовать токен.
            // В данном случае, это для примера, мы можем проверять позднее истек ли токен или нет
            [[NSUserDefaults standardUserDefaults] setObject:[NSDate date] forKey:@"VKAccessTokenDate"];
            [[NSUserDefaults standardUserDefaults] synchronize];
        }
        
        [self Post:(NSString*)[[NSUserDefaults standardUserDefaults] objectForKey:@"VKAccessToken"]];
        
        //NSLog(@"webview response: %@",[[[webView request] URL] absoluteString]);
        [self dismissModalViewControllerAnimated:YES];
    } else if ([webview.request.URL.absoluteString rangeOfString:@"error"].location != NSNotFound) {
        NSLog(@"Error: %@", webview.request.URL.absoluteString);
        [self dismissModalViewControllerAnimated:YES];
    }
}

- (void) Post: (NSString*) access_token
{
    NSString *text = @"Играем в Кроко!";
    NSString *postLink = [NSString stringWithFormat:@"https://api.vk.com/method/wall.post?message=%@&attachments=https://www.facebook.com/CrocoCommunity&access_token=%@",text,access_token];
    NSURL *url = [NSURL URLWithString:postLink];
    [webview loadRequest:[NSURLRequest requestWithURL:url]];
    [webview setDelegate:nil];
    
    //Уведомление об успешном завершении
    UIAlertView *myAlertView = [[UIAlertView alloc] initWithTitle:@"Успешно!" message:@"Спасибо!" delegate:self cancelButtonTitle:@"OK" otherButtonTitles: nil];
    [myAlertView show];
    [myAlertView release];
    //
    [webview removeFromSuperview];
}

- (NSString*)stringBetweenString:(NSString*)start
                       andString:(NSString*)end 
                     innerString:(NSString*)str 
{
    NSScanner* scanner = [NSScanner scannerWithString:str];
    [scanner setCharactersToBeSkipped:nil];
    [scanner scanUpToString:start intoString:NULL];
    if ([scanner scanString:start intoString:NULL]) {
        NSString* result = nil;
        if ([scanner scanUpToString:end intoString:&result]) {
            return result;
        }
    }
    return nil;
}

@end
