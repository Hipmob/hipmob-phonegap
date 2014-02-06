//
//  HMChatViewController.h
//  hipmob
//
//  Created by Olufemi Omojola on 6/1/13.
//  Copyright (c) 2012 - 2013 Orthogonal Labs, Inc.
//
#ifndef _hipmob_hmchatviewcontroller_h_
#define _hipmob_hmchatviewcontroller_h_

#import <UIKit/UIKit.h>
#import "HMChatView.h"

/** The HMChatViewControllerDelegate protocol defines the optional methods implemented by delegates of HMChatViewController instances. This is largely a wrapper around the internal HMChatView instance, with a number of helpful extras thrown in.
 *
 * The delegate will be notified when a URL is received.
 * All methods are optional
 */
@protocol HMChatViewControllerDelegate <NSObject>;

@optional
/** Tells the delegate that a URL was pushed from the server. The delegate may choose to handle the URL itself: if it does, it should
 * return YES. If the delegate does not implement this method or if it returns NO (i.e. it either does not handle
 * URLs of this format or if it doesn't want to implement any special logic) then the URL will be opened in either an internal WebView OR the platform browser (i.e. Safari) depending on the value of the shouldUseSystemBrowser property.
 *
 * @param chatViewController The HMChatViewController instance that received the URL.
 * @param url The URL that was received.
 * @param messageId The id of the message that contained the URL. If you have the delegate associated with multiple chat view instances then you may receive multiple calls: you can use the messageId to ensure you only take action a single time.
 * @result TRUE If the delegate handled the URL, FALSE otherwise.
 */
-(BOOL)chatViewController:(id)chatViewController willHandleURL:(NSString*)url messageId:(NSString*)messageId;

/**
 * Tells the delegate that an error occured in the underlying chat view.
 *
 * @param chatViewController The HMChatViewController instance that received the error.
 * @param error The error message that occured.
 */
-(void)chatViewController:(id)chatViewController didErrorOccur:(NSString *)error;

/**
 * Tells the delegate that a message we care about was received.
 *
 * @param chatViewController The HMChatViewController instance that received the message.
 * @param message The message that was received.
 */
-(void)chatViewController:(id)chatViewController didReceiveMessage:(HMChatMessage *)message;

/**
 * Tells the delegate that a message we care about was sent.
 *
 * @param chatViewController The HMChatViewController instance that sent the message.
 * @param message The message that was sent.
 */
-(void)chatViewController:(id)chatViewController didSendMessage:(HMChatMessage *)message;

/**
 * Tells the delegate that the view controller is closing.
 *
 * @param chatViewController The HMChatViewController instance that is closing.
 */
-(void)chatViewControllerWillDismiss:(id)chatViewController;

/**
 * Tells the delegate that an operator came online.
 *
 * @param chatViewController The HMChatViewController instance that was updated.
 */
-(void)chatViewControllerDidOperatorComeOnline:(id)chatViewController;

/**
 * Tells the delegate that all operators went offline.
 *
 * @param chatViewController The HMChatViewController instance that was updated.
 */
-(void)chatViewControllerDidOperatorGoOffline:(id)chatViewController;

/**
 * Tells the delegate that a specific peer came online.
 *
 * @param chatViewController The HMChatViewController instance that was updated.
 * @param peer The peer that came online.
 */
-(void)chatViewController:(id)chatViewController didPeerComeOnline:(NSString *)peer;

/**
 * Tells the delegate that a specific peer went offline.
 *
 * @param chatViewController The HMChatViewController instance that was updated.
 * @param peer The peer that wend offline.
 */
-(void)chatViewController:(id)chatViewController didPeerGoOffline:(NSString *)peer;
@end

/**
 * Provides a simple UIViewController that renders a full-screen chat window.
 */
@interface HMChatViewController : UINavigationController <HMChatViewDelegate, UIGestureRecognizerDelegate>
{
    HMChatView * chatView;
}

/**
 * Returns the actual HMChatView instance that handles the chat.
 */
@property (readonly,nonatomic,retain) HMChatView * chatView;

/**
 * Returns the status indicator that shows online/offline. This can then be hidden.
 */
@property (readonly, nonatomic, retain) UIView * statusView;

/**
 * Returns the UIViewController that contains the chatView. This can be used to customize
 * the bar.
 */
@property (readonly, nonatomic, retain) UIViewController * body;

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
 * Set to YES to prevent the controller from showing the availability indicator.
 */
@property (nonatomic, assign) BOOL hidesAvailabilityIndicator;

/**
 * Sets the preferred status bar style.
 */
@property (nonatomic, assign) UIStatusBarStyle overridePreferredStatusBarStyle;

/**
 * Sets/return the extra UIBarButtonItems to be shown on the right for this controller. If this is nil
 * then no extra button items are shown.
 */
@property(nonatomic, copy) NSArray * extraBarButtonItems;

/** The HMChatViewControllerDelegate for this chat view.
 */
@property (assign) id<HMChatViewControllerDelegate> chatDelegate;

///------------------------------------------------------------------------------------------
/// @name Initialization
///------------------------------------------------------------------------------------------
/** Initializes the HMChatViewController object to connect with a specific Hipmob app identifier. By default
 * support messages will be shown (messages sent to/from the Hipmob app's operators).
 *
 * The application identifier can be obtained from https://manage.hipmob.com/#apps and will
 * let the Hipmob communication network identify which set of operators, users and other resources
 * to use for this connection. Typically there will be one application identifier for each app.
 * After this call a private connection will be made to the Hipmob communication network for this
 * chat view. Not that when the view is dismissed the connection will be closed.
 *
 * @param appid The Hipmob application identifier for this app.
 * @param user The user identifier for this user. Can be set to nil to use an internally generated id.
 */
-(id) initWithAppID:(NSString *)appid andUser:(NSString *)user;

/** Initializes the HMChatViewController object to connect with a specific Hipmob app identifier. By default
 * support messages will be shown (messages sent to/from the Hipmob app's operators).
 *
 * The application identifier can be obtained from https://manage.hipmob.com/#apps and will
 * let the Hipmob communication network identify which set of operators, users and other resources
 * to use for this connection. Typically there will be one application identifier for each app.
 * After this call a private connection will be made to the Hipmob communication network for this
 * chat view. Not that when the view is dismissed the connection will be closed.
 *
 * @param appid The Hipmob application identifier for this app.
 * @param user The user identifier for this user. Can be set to nil to use an internally generated id.
 * @param info Additional connection information to be provided to the connection. Acceptable keys are *name*,
 * *email*, *context* and *pushtoken*.
 */
-(id) initWithAppID:(NSString *)appid andUser:(NSString *)user andInfo:(NSDictionary *)info;

/** Initializes the HMChatViewController object to connect with a specific Hipmob app identifier and to show
 * messages to/from a specific peer.
 *
 * The application identifier can be obtained from https://manage.hipmob.com/#apps and will
 * let the Hipmob communication network identify which set of operators, users and other resources
 * to use for this connection. Typically there will be one application identifier for each app.
 * After this call a private connection will be made to the Hipmob communication network for this
 * chat view. Not that when the view is dismissed the connection will be closed.
 *
 * @param appid The Hipmob application identifier for this app.
 * @param user The user identifier for this user. For peer messaging the user identifier MUST NOT be nil.
 * @param peer The device identifier for the peer.
 */
-(id) initWithAppID:(NSString *)appid andUser:(NSString *)user andPeer:(NSString*)peer;

///------------------------------------------------------------------------------------------
/// @name Connection Control
///------------------------------------------------------------------------------------------
/** Connects the chat (if it isn't already connected).
 *
 */
-(void) connect;

/** Disconnects the chat (if it is already connected).
 *
 */
-(void) disconnect;

///------------------------------------------------------------------------------------------
/// @name Connection Status
///------------------------------------------------------------------------------------------
/** Returns TRUE if the chat is connected, false otherwise.
 *
 * @result TRUE if the chat is connected, false otherwise.
 */
-(BOOL) isConnected;

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