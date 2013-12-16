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
@end

/**
 * Provides a simple UIViewController that renders a help desk article.
 */
@interface HMContentHelpDeskArticleViewController : UIViewController <UIGestureRecognizerDelegate>
{

}

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