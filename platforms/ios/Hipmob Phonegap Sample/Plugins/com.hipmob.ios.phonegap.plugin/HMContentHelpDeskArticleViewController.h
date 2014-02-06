//
//  HMContentHelpDeskArticleViewController.h
//  hipmob
//
//  Created by Olufemi Omojola on 08/12/2013
//  Copyright (c) 2012 - 2013 Orthogonal Labs, Inc.
//
#ifndef _hipmob_hmcontenthelpdeskarticleviewcontroller_h_
#define _hipmob_hmcontenthelpdeskarticleviewcontroller_h_

#import <UIKit/UIKit.h>

/**
 * An enumeration that controls whether or not the chat button is shown in the HMHelpDeskArticleViewController's navigation bar.
 */
typedef NS_ENUM(NSInteger, HMContentHelpDeskArticleChatEnabled){
    /**
     * Always show the chat button.
     */
    HMContentHelpDeskArticleChatEnabledAlways            = 0,
    
    /**
     * Only show the chat button if an operator is available.
     */
    HMContentHelpDeskArticleChatEnabledIfOperatorAvailable = 1,
    
    /**
     * Never show the chat button.
     */
    HMContentHelpDeskArticleChatEnabledNever             = 2
};


/** The HMContentHelpDeskArticleViewControllerDelegate protocol defines the optional methods implemented by delegates of HMContentHelpDeskArticleViewController instances. 
 */
@protocol HMContentHelpDeskArticleViewControllerDelegate <NSObject>;

@required
/** Tells the delegate that a specific article was loaded. The delegate must handle the article display by itself.
 * This is invoked in response to the loadArticle call.
 *
 * @param contentArticleViewController The HMContentHelpDeskArticleViewController instance that generated the event.
 * @param articleId The id of the loaded article.
 * @param title The title of the loaded article.
 * @param url The URL of the loaded article.
 * @param baseURL The base URL for resolving embedded images and content.
 * @param content The content of the loaded article.
 *
 */
-(void)contentArticleViewController:(id)contentArticleViewController didLoadArticle:(NSString *)articleId withTitle:(NSString *)title andURL:(NSString *)url andBaseURL:(NSString *)baseURL andContent:(NSString *)content;

@optional
/**
 * Tells the delegate that an error occured in the view controller.
 *
 * @param contentArticleViewController The HMContentHelpDeskArticleViewController instance that received the error.
 * @param error The error message that occured.
 */
-(void)contentArticleViewController:(id)contentArticleViewController didErrorOccur:(NSString *)error;

/**
 * Tells the delegate that the user closed the help desk article.
 *
 * @param contentArticleViewController The HMContentHelpDeskArticleViewController instance that is closing.
 */
-(void)contentArticleViewControllerWillDismiss:(id)contentArticleViewController;

/**
 * Tells the delegate that the chat button has been displayed, and passes the button so additional styling can be applied.
 *
 * @param contentArticleViewController The HMContentHelpDeskArticleViewController instance that showed the chat button.
 * @param chatButton The UIButton added to the navigation bar.
 */
-(void)contentArticleViewController:(id)contentArticleViewController hasShownChatButton:(UIButton *)chatButton;

/**
 * Tells the delegate that the user is about to open a chat window.
 *
 * @param contentArticleViewController The HMContentHelpDeskArticleViewController instance that opened the chat window.
 * @param chatViewController The HMContentChatViewController instance that opened.
 */
-(void)contentArticleViewController:(id)contentArticleViewController willOpenChat:(id)chatViewController;

@end

/**
 * Provides a simple UIViewController that renders a help desk article.
 */
@interface HMContentHelpDeskArticleViewController : UIViewController <UIGestureRecognizerDelegate>
{

}

/**
 * A constant indicating the conditions under which the chat button should be displayed. See [HMContentHelpDeskArticleChatEnabled](../Constants/HMContentHelpDeskArticleChatEnabled.html) for descriptions of these constants. The user id passed when the search view was initialized must NOT be nil for the chat button to appear.
 */
@property (nonatomic, assign) HMContentHelpDeskArticleChatEnabled chatEnabled;

/**
 * Returns the actual webview that shows the article.
 */
@property (readonly,nonatomic,retain) UIWebView * webView;

/**
 * Set to FALSE to prevent the use of swipe gestures for forward/backward navigation when using the built in web view (defaults to NO).
 */
@property (nonatomic, assign) BOOL disableWebViewGestures;

/**
 * Set to YES to have the controller stay in portrait mode (defaults to NO).
 */
@property (nonatomic, assign) BOOL forcePortrait;

/**
 * Set to YES to have the controller require full screen (defaults to NO).
 */
@property (nonatomic, assign) BOOL requireFullscreen;

/**
 * Set to YES to prevent the controller from adjusting for keyboard show/hide (defaults to NO). This is particularly useful when embedding in popover view controllers.
 */
@property (nonatomic, assign) BOOL disableKeyboardAdjustment;

/**
 * Sets/return the extra UIBarButtonItems to be shown on the right for this controller. If this is nil
 * then no extra button items are shown.
 */
@property(nonatomic, copy) NSArray * extraBarButtonItems;

/** The HMContentHelpDeskArticleViewControllerDelegate for this view controller.
 */
@property (assign) id<HMContentHelpDeskArticleViewControllerDelegate> articleViewDelegate;

///------------------------------------------------------------------------------------------
/// @name Initialization
///------------------------------------------------------------------------------------------
/** Initializes the HMContentHelpDeskSearchViewController object to connect with a specific Hipmob app identifier. This
 * will control which help desk the search runs through.
 *
 * The application identifier can be obtained from https://manage.hipmob.com/#apps and will
 * let the Hipmob network identify the specific help desk you wish to searches to be run against.
 * Typically there will be one application identifier for each app.
 *
 * @param app The Hipmob application identifier for this app.
 * @param articleId The helpdesk article identifier to be displayed.
 */
-(id) initWithAppID:(NSString *)app andArticle:(NSString *)articleId;

/** Initializes the HMContentHelpDeskSearchViewController object to connect with a specific Hipmob app identifier. This
 * will control which help desk the search runs through.
 *
 * The application identifier can be obtained from https://manage.hipmob.com/#apps and will
 * let the Hipmob network identify the specific help desk you wish to searches to be run against.
 * Typically there will be one application identifier for each app.
 *
 * @param app The Hipmob application identifier for this app.
 * @param articleId The helpdesk article identifier to be displayed.
 * @param user The user identifier for this user. Can be set to nil to use an internally generated id.
 * @param userInfo Additional connection information to be provided to the connection. Acceptable keys are {name},
 * {email}, {context} and {pushtoken}.
 */
-(id) initWithAppID:(NSString *)app andArticle:(NSString *)articleId andUser:(NSString *)user andInfo:(NSDictionary *)userInfo;

/** Initializes the HMContentHelpDeskSearchViewController object to connect with a specific Hipmob app identifier. This
 * will control which help desk the search runs through.
 *
 * The application identifier can be obtained from https://manage.hipmob.com/#apps and will
 * let the Hipmob network identify the specific help desk you wish to searches to be run against.
 * Typically there will be one application identifier for each app.
 *
 * @param app The Hipmob application identifier for this app.
 * @param articleUrl The URL of the helpdesk article to be displayed.
 */
-(id) initWithAppID:(NSString *)app andArticleURL:(NSString *)articleUrl;

-(void)setPopoverSize:(CGSize)size;

/**
 * Returns the title of the artile being shown, or nil if the article hasn't yet been loaded.
 *
 * @result The title of the currently displayed article.
 */
-(NSString *)getTitle;

/**
 * Notifies the controller that a close has been requested (used in the popover controller).
 */
-(void)closeRequested;
@end
#endif