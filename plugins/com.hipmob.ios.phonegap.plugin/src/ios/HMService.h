//
//  Hipmob.h
//  hipmob
//
//  Created by Olufemi Omojola on 10/12/13.
//  Copyright (c) 2013 Orthogonal Labs, Inc. All rights reserved.
//
#ifndef _hipmob_hmservice_h_
#define _hipmob_hmservice_h_

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreData/CoreData.h>
#import "HMHelpDeskArticleViewController.h"
#import "HMHelpDeskSearchViewController.h"
#import "HMChatViewController.h"

/**
 * Implements a single, global Hipmob service object that can be used to provide convenient access to a number of
 * Hipmob features and services.
 */
@interface HMService : NSObject
/** 
 * Retrieves the shared Hipmob service instance. If the instance hasn't yet been initialized then it will be initialized during this call.
 *
 * @result The shared Hipmob service instance.
 */
+(id)sharedService;

/**
 * Configures the service with your Hipmob application id.
 *
 * @param app The Hipmob application identifier to be used with this app.
 * @param launchOptions The dictionary with information about the application's launch conditions (such as whether or not it was launched from a local or remote notification).
 */
-(void)setup:(NSString *)app withLaunchOptions:(NSDictionary *)launchOptions;

/**
 * Sets the user who is currently using the app.
 *
 * @param user The user currently using the app.
 */
-(void)setUser:(NSString *)user;

/**
 * Sets the push token for the app.
 *
 * @param token The APNS push notification token for this app.
 */
-(void)setPushToken:(NSData *)token;

/**
 * Indicates that a local notification was received, and passes the notification in so we can tell if it was initiated by us (and we can then track what happened).
 *
 * @param notification The local notification.
 * @result YES if the notification was from us, NO otherwise.
 */
-(BOOL)didReceiveLocalNotification:(UILocalNotification *)notification;

/**
 * Indicates that a remote notification was received, and passes the notification in so we can tell if it was initiated by us (and we can then track what happened).
 *
 * @param userInfo The dictionary that contains information related to the remote notification.
 * @result YES if the notification was from us, NO otherwise.
 */
-(BOOL)didReceiveRemoteNotification:(NSDictionary *)userInfo;

/** Updates the user's name.
 *
 * @param value The new name for this user.
 * @exception NSException If the value is nil.
 *
 */
-(void) updateName:(NSString*)value;

/** Updates the user's email.
 *
 * @param value The new email for this user.
 * @exception NSException If the value is nil.
 *
 */
-(void) updateEmail:(NSString*)value;

/** Updates the user's context.
 *
 * @param value The new context for this user.
 * @exception NSException If the value is nil.
 *
 */
-(void) updateContext:(NSString*)value;

/** Updates the user's location. This is a plain-text string intended to be driven by the user's input (for example, "Home" or "Office").
 *
 * @param value The new location for this user.
 * @exception NSException If the value is nil.
 *
 */
-(void) updateLocation:(NSString*)value;

/** Updates the user's latitude/longitude location.
 *
 * @param value The new location for this user.
 * @exception NSException If the value is nil.
 *
 */
-(void) updateGeolocation:(CLLocation *)value;

/**
 * Updates a custom data field.
 *
 * @param value The new value of the data field.
 * @param key The key for the data field.
 *
 */
-(void)updateCustomData:(NSString *)value forKey:(NSString *)key;

/**
 * Sets the window so we can display overlays.
 *
 * @param appWindow The application's window.
 */
-(void)setWindow:(UIWindow *)appWindow;

/**
 * Tracks an inbound URL request.
 *
 * @param url The URL resource to open. This resource can be a network resource or a file. For information about the Apple-registered URL schemes, see Apple URL Scheme Reference.
 * @param source The bundle ID of the app that is requesting your app to open the URL (url).
 * @param details A property-list object supplied by the source app to communicate information to the receiving app.
 */
- (void)openURL:(NSURL *)url from:(NSString *)source withDetails:(id)details;

/**
 * Opens a chat window and presents it using presentModalViewController. This will also return the chat view controller so it can be further customized.
 *
 * @param currentViewController The current view controller being displayed: the chat view will be presented from this view controller.
 */
-(HMChatViewController *)openChat:(UIViewController *)currentViewController;

/**
 * Opens a chat window, customizes it using the specified setup block, and then presents it using presentModalViewController. This will also return the chat view controller so it can be used later.
 *
 * @param currentViewController The current view controller being displayed: the chat view will be presented from this view controller.
 * @param setupBlock A block that is invoked to setup the chat view controller before it is displayed.
 */
-(HMChatViewController *)openChat:(UIViewController *)currentViewController withSetup:(void (^)(HMChatViewController *))setupBlock;

/**
 * Opens a helpdesk search window and presents it using presentModalViewController. This will also return the help desk search view controller so it can be further customized.
 *
 * @param currentViewController The current view controller being displayed: the helpdesk search view will be presented from this view controller.
 */
-(HMHelpDeskSearchViewController *)openHelpdeskSearch:(UIViewController *)currentViewController;

/**
 * Opens a helpdesk search window, customizes it using the specified setup block, and presents it using presentModalViewController. This will also return the help desk search view controller so it can be used later.
 *
 * @param currentViewController The current view controller being displayed: the helpdesk search view will be presented from this view controller.
 * @param setupBlock A block that is invoked to setup the chat view controller before it is displayed.
 */
-(HMHelpDeskSearchViewController *)openHelpdeskSearch:(UIViewController *)currentViewController withSetup:(void (^)(HMHelpDeskSearchViewController *))setupBlock;

/**
 * Opens a helpdesk article and presents it using presentModalViewController. This will also return the help desk article view controller so it can be further customized.
 *
 * @param url The URL of the help desk article to be displayed.
 * @param currentViewController The current view controller being displayed: the helpdesk search view will be presented from this view controller.
 */
-(HMHelpDeskArticleViewController *)openHelpdeskArticle:(NSString *)url fromCurrentView:(UIViewController *)currentViewController;

/**
 * Opens a helpdesk article, customizes it using the specified setup block, and presents it using presentModalViewController. This will also return the help desk article view controller so it can be used later.
 *
 * @param url The URL of the help desk article to be displayed.
 * @param currentViewController The current view controller being displayed: the helpdesk search view will be presented from this view controller.
 * @param setupBlock A block that is invoked to setup the chat view controller before it is displayed.
 */
-(HMHelpDeskArticleViewController *)openHelpdeskArticle:(NSString *)url fromCurrentView:(UIViewController *)currentViewController withSetup:(void (^)(HMHelpDeskArticleViewController *))setupBlock;

@end
#endif