//
//  HMHelpDeskArticleViewController.h
//  hipmob
//
//  Created by Olufemi Omojola on 6/1/13.
//  Copyright (c) 2012 - 2013 Orthogonal Labs, Inc.
//
#ifndef _hipmob_hmhelpdeskarticleviewcontroller_h_
#define _hipmob_hmhelpdeskarticleviewcontroller_h_

#import <UIKit/UIKit.h>
#import "HMContentHelpDeskArticleViewController.h"
#import "HMChatView.h"

/**
 * Provides a simple UIViewController that renders a full-screen help desk article window.
 */
@interface HMHelpDeskArticleViewController : UINavigationController
{
}

/**
 * Returns the View Controller that contains the article view. This can be used to customize
 * the bar.
 */
@property (readonly, nonatomic, retain) HMContentHelpDeskArticleViewController * body;

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
 * Sets the preferred status bar style.
 */
@property (nonatomic, assign) UIStatusBarStyle overridePreferredStatusBarStyle;

///------------------------------------------------------------------------------------------
/// @name Initialization
///------------------------------------------------------------------------------------------
/** Initializes the HMHelpDeskArticleViewController object to connect with a specific Hipmob app identifier. This
 * will control which help desk the article will be loaded from.
 *
 * The application identifier can be obtained from https://manage.hipmob.com/#apps and will
 * let the Hipmob network identify the specific help desk you wish to searches to be run against.
 * Typically there will be one application identifier for each app.
 *
 * @param app The Hipmob application identifier for this app.
 * @param articleId The helpdesk article identifier to be displayed.
 */
-(id) initWithAppID:(NSString *)app andArticle:(NSString *)articleId;

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
 * @param articleId The helpdesk article identifier to be displayed.
 * @param user The user identifier for this user. Can be set to nil to use an internally generated id.
 * @param userInfo Additional connection information to be provided to the connection. Acceptable keys are {name},
 * {email}, {context} and {pushtoken}.
 */
-(id) initWithAppID:(NSString *)app andArticle:(NSString *)articleId andUser:(NSString *)user andInfo:(NSDictionary *)userInfo;

/** Initializes the HMHelpDeskArticleViewController object to connect with a specific Hipmob app identifier. This
 * will control which help desk the article will be loaded from.
 *
 * The application identifier can be obtained from https://manage.hipmob.com/#apps and will
 * let the Hipmob network identify the specific help desk you wish to searches to be run against.
 * Typically there will be one application identifier for each app.
 *
 * @param app The Hipmob application identifier for this app.
 * @param articleUrl The URL of the helpdesk article to be displayed.
 */
-(id) initWithAppID:(NSString *)app andArticleURL:(NSString *)articleUrl;

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
 * @param articleUrl The URL of the helpdesk article to be displayed.
 * @param user The user identifier for this user. Can be set to nil to use an internally generated id.
 * @param userInfo Additional connection information to be provided to the connection. Acceptable keys are {name},
 * {email}, {context} and {pushtoken}.
 */
-(id) initWithAppID:(NSString *)app andArticleURL:(NSString *)articleUrl andUser:(NSString *)user andInfo:(NSDictionary *)userInfo;
@end
#endif