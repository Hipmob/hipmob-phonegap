//
//  HMHelpDeskSearchViewController.h
//  hipmob
//
//  Created by Olufemi Omojola on 6/1/13.
//  Copyright (c) 2012 - 2013 Orthogonal Labs, Inc.
//
#ifndef _hipmob_hmhelpdesksearchviewcontroller_h_
#define _hipmob_hmhelpdesksearchviewcontroller_h_

#import <UIKit/UIKit.h>
#import "HMHelpDeskSearchView.h"
#import "HMChatView.h"

/**
 * An enumeration that controls whether or not the chat button is shown in the HMHelpDeskSearchViewController's navigation bar.
 */
typedef NS_ENUM(NSInteger, HMHelpDeskSearchChatEnabled){
    /**
     * Always show the chat button.
     */
    HMHelpDeskSearchChatEnabledAlways            = 0,
    
    /**
     * Only show the chat button if an operator is available.
     */
    HMHelpDeskSearchChatEnabledIfOperatorAvailable = 1,
    
    /**
     * Never show the chat button.
     */
    HMHelpDeskSearchChatEnabledNever             = 2
};

/** The HMHelpDeskSearchViewControllerDelegate protocol defines the optional methods implemented by delegates of HMHelpDeskSearchViewController instances. This is largely a wrapper around the internal HMChatView instance, with a number of helpful extras thrown in.
 */
@protocol HMHelpDeskSearchViewControllerDelegate <NSObject>;

@optional
/** Tells the delegate that a specific article was selected. The delegate may choose to handle the article itself: if it does, it should
 * return TRUE or YES. If the delegate does not implement this method or if it returns FALSE or NO (i.e. it either does not handle
 * URLs of this format or if it doesn't want to implement any special logic) then the URL will be opened in a private WebView.
 *
 * @param searchViewController The HMHelpDeskSearchViewController instance that generated the event.
 * @param id The id of the selected article.
 * @param title The title of the selected article.
 * @param url The URL of the selected article.
 * @param baseURL The base URL for resolving embedded images and content.
 * @param content The content of the selected article.
 *
 * @result YES If the delegate handled the article display, NO otherwise.
 */
-(BOOL)searchViewController:(id)searchViewController didSelectArticle:(NSString *)id withTitle:(NSString *)title andURL:(NSString *)url andBaseURL:(NSString *)baseURL andContent:(NSString *)content;

/** Provides the delegate with an array of results that are about to be displayed to the user. The delegate may choose
 * to alter the array to remove specific results or to adjust the sort order. The search view caches search results
 * on a per-query basis: for any specific query this delegate callback will be invoked at most once. The array will contain HMSearchResultRow instances.
 *
 * @param searchViewController The HMHelpDeskSearchView instance that generated the event.
 * @param results The search results: this is an array of HMSearchResultRow instances.
 * @param query The query that produced these results.
 */
-(void)searchViewController:(id)searchViewController willRenderResults:(NSMutableArray *)results forQuery:(NSString *)query;

/**
 * Tells the delegate that the chat button has been displayed, and passes the button so additional styling can be applied.
 *
 * @param searchViewController The HMHelpDeskSearchViewController instance that showed the chat button.
 * @param chatButton The UIButton added to the navigation bar.
 */
-(void)searchViewController:(id)searchViewController hasShownChatButton:(UIButton *)chatButton;

/**
 * Tells the delegate that an error occured in the underlying search view
 *
 * @param searchViewController The HMHelpDeskSearchViewController instance that received the error.
 * @param error The error message that occured.
 */
-(void)searchViewController:(id)searchViewController didErrorOccur:(NSString *)error;

/**
 * Tells the delegate that the user is about to open a chat window.
 *
 * @param searchViewController The HMHelpDeskSearchViewController instance that opened the chat window.
 * @param chatViewController The HMContentChatViewController instance that opened.
 */
-(void)searchViewController:(id)searchViewController willOpenChat:(id)chatViewController;

/**
 * Tells the delegate that the user closed the help desk search.
 *
 * @param searchViewController The HMHelpDeskSearchViewController instance that is closing.
 */
-(void)searchViewControllerWillDismiss:(id)searchViewController;
@end

/** Provides a simple UIViewController that renders a full-screen help desk search window.
 
 A usage example is below: this creates an instance of the controller, changes the tint of the title bar and then sets a default search query that should be displayed. It also ensures that help pages opened by the user are opened within the application:
 
    helpdesk = [[HMHelpDeskSearchViewController alloc] initWithAppID:APPID andUser:userid andInfo:nil];
    helpdesk.navigationBar.tintColor = [UIColor colorWithRed:236.0/255.0 green:244.0/255.0 blue:243.0/255.0 alpha:1];
    helpdesk.searchDelegate = self;
    helpdesk.searchView.defaultQuery = @"iOS";
    helpdesk.shouldUseSystemBrowser = NO;
    [self presentModalViewController:helpdesk animated:YES];
 
 Any modifications to the appearance of the helpdesk search view can be made by accessing the `helpdesk.searchView` 
 */
@interface HMHelpDeskSearchViewController : UINavigationController <HMHelpDeskSearchViewDelegate, HMChatOperatorAvailabilityCheckDelegate, UIGestureRecognizerDelegate>
{
    HMHelpDeskSearchView * searchView;
}

/**
 * Returns the actual HMHelpDeskSearchView instance that handles the chat.
 */
@property (readonly,nonatomic,retain) HMHelpDeskSearchView * searchView;

/**
 * Returns the UIViewController that contains the searchView. This can be used to customize
 * the bar.
 */
@property (readonly, nonatomic, retain) UIViewController * body;

/**
 * A constant indicating the conditions under which the chat button should be displayed. See [HMHelpDeskSearchChatEnabled](../Constants/HMHelpDeskSearchChatEnabled.html) for descriptions of these constants. The user id passed when the search view was initialized must NOT be nil for the chat button to appear.
 */
@property (nonatomic, assign) HMHelpDeskSearchChatEnabled chatEnabled;

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

/**
 * Set to YES to prevent the controller from automatically wrapping the help content with a meta viewport tag (defaults to NO). This is useful if you are using the content view controller in a non-full screen manner.
 */
@property (nonatomic, assign) BOOL disableViewportWrap;

/**
 * Sets the preferred status bar style.
 */
@property (nonatomic, assign) UIStatusBarStyle overridePreferredStatusBarStyle;

/**
 * Sets/return the extra UIBarButtonItems to be shown on the right for this controller. If this is nil
 * then no extra button items are shown.
 */
@property(nonatomic, copy) NSArray * extraBarButtonItems;

/** The HMHelpDeskSearchViewControllerDelegate for this chat view.
 */
@property (assign) id<HMHelpDeskSearchViewControllerDelegate> searchDelegate;

///------------------------------------------------------------------------------------------
/// @name Initialization
///------------------------------------------------------------------------------------------
/** Initializes the HMHelpDeskSearchViewController object to connect with a specific Hipmob app identifier. This
 * will control which help desk the search runs through.
 *
 * The application identifier can be obtained from https://manage.hipmob.com/#apps and will
 * let the Hipmob network identify the specific help desk you wish to searches to be run against.
 * Typically there will be one application identifier for each app.
 *
 * @param app The Hipmob application identifier for this app.
 */
-(id) initWithAppID:(NSString *)app;

/** Initializes the HMHelpDeskSearchViewController object to connect with a specific Hipmob app identifier. This
 * will control which help desk the search runs through.
 *
 * The application identifier can be obtained from https://manage.hipmob.com/#apps and will
 * let the Hipmob network identify the specific help desk you wish to searches to be run against.
 * Typically there will be one application identifier for each app. If this method is used then a check
 * will be made to see if any operators are online for the specified Hipmob app: if there are operators
 * available then a chat button will also be shown.
 *
 * @param app The Hipmob application identifier for this app.
 * @param user The user identifier for this user. Can be set to nil to use an internally generated id.
 * @param userInfo Additional connection information to be provided to the connection. Acceptable keys are {name},
 * {email}, {context} and {pushtoken}.
 */
-(id) initWithAppID:(NSString *)app andUser:(NSString *)user andInfo:(NSDictionary *)userInfo;

///------------------------------------------------------------------------------------------
/// @name Utilities
///------------------------------------------------------------------------------------------
/** Opens up the specified URL in an embedded UIWebView.
 *
 * @param url The URL to open.
 */
-(void)view:(NSString *)url;

/** Opens up the specified URL in an embedded UIWebView.
 *
 * @param url The URL to open.
 * @param title The title for the web view.
 */
-(void)view:(NSString *)url withTitle:(NSString *)title;

/** 
 * Notifies the controller that a close has been requested (used in the popover controller).
 */
-(void)closeRequested;
@end
#endif