//
//  HMContentHelpDeskSearchViewController.h
//  hipmob
//
//  Created by Olufemi Omojola on 6/1/13.
//  Copyright (c) 2012 - 2013 Orthogonal Labs, Inc.
//
#ifndef _hipmob_hmcontenthelpdesksearchviewcontroller_h_
#define _hipmob_hmcontenthelpdesksearchviewcontroller_h_

#import <UIKit/UIKit.h>
#import "HMHelpDeskSearchView.h"

/** The HMContentHelpDeskSearchViewControllerDelegate protocol defines the optional methods implemented by delegates of HMContentHelpDeskSearchViewController instances. This is largely a wrapper around the internal HMChatView instance, with a number of helpful extras thrown in.
 */
@protocol HMContentHelpDeskSearchViewControllerDelegate <NSObject>;

@required
/** Tells the delegate that a specific article was selected. The delegate may choose to handle the article itself: if it does, it should
 * return TRUE or YES. If the delegate does not implement this method or if it returns FALSE or NO (i.e. it either does not handle
 * URLs of this format or if it doesn't want to implement any special logic) then the URL will be opened in a private WebView.
 *
 * @param contentSearchViewController The HMContentHelpDeskSearchViewController instance that generated the event.
 * @param id The id of the selected article.
 * @param title The title of the selected article.
 * @param url The URL of the selected article.
 * @param baseURL The base URL for resolving embedded images and content.
 * @param content The content of the selected article.
 *
 * @result YES If the delegate handled the article display, NO otherwise.
 */
-(BOOL)contentSearchViewController:(id)contentSearchViewController didSelectArticle:(NSString *)id withTitle:(NSString *)title andURL:(NSString *)url andBaseURL:(NSString *)baseURL andContent:(NSString *)content;

@optional
/**
 * Tells the delegate that an error occured in the underlying search view
 *
 * @param contentSearchViewController The HMContentHelpDeskSearchViewController instance that received the error.
 * @param error The error message that occured.
 */
-(void)contentSearchViewController:(id)contentSearchViewController didErrorOccur:(NSString *)error;

/**
 * Tells the delegate that the view controller is closing.
 *
 * @param contentSearchViewController The HMContentHelpDeskSearchViewController instance that is closing.
 */
-(void)contentSearchViewControllerWillDismiss:(id)contentSearchViewController;
@end

/**
 * Provides a simple UIViewController that renders a full-screen chat window.
 */
@interface HMContentHelpDeskSearchViewController : UIViewController <HMHelpDeskSearchViewDelegate, UIGestureRecognizerDelegate>
{
    HMHelpDeskSearchView * searchView;
}

/**
 * Returns the actual HMHelpDeskSearchView instance that handles the search.
 */
@property (readonly,nonatomic,retain) HMHelpDeskSearchView * searchView;

/**
 * Set to YES to have the controller open URLs in an external browser. By default URLs are opened in a web view presented in a view controller (defaults to NO).
 */
@property (nonatomic, assign) BOOL shouldUseSystemBrowser;

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

/** The HMContentHelpDeskSearchViewControllerDelegate for this search view.
 */
@property (assign) id<HMContentHelpDeskSearchViewControllerDelegate> searchDelegate;

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
 * @param user The user identifier for this user. Can be set to nil if not in use.
 */
-(id) initWithAppID:(NSString *)app andUser:(NSString *)user;
@end
#endif