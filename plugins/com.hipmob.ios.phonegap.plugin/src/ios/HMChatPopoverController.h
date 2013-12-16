//
//  HMChatPopoverController.h
//  hipmob
//
//  Created by Olufemi Omojola on 6/1/13.
//  Copyright (c) 2012 - 2013 Orthogonal Labs, Inc.
//
#ifndef _hipmob_hmchatpopovercontroller_h_
#define _hipmob_hmchatpopovercontroller_h_

#import <UIKit/UIKit.h>
#import "HMChatViewController.h"

@class HMRemoteConnection;

/**
 * Default popover frame for landscape orientation.
 */
#define HMDefaultPopoverFrameLandscape  CGRectMake(830, 20, 20, 20)

/**
 * Default popover frame for portrait orientation.
 */
#define HMDefaultPopoverFramePortrait   CGRectMake(590, 20, 20, 20)

/**
 * Default popover size.
 */
#define HMDefaultPopoverSize            CGSizeMake(260, 280)

/**
 * Provides a popover controller for use in tablet displays.
 */
@interface HMChatPopoverController : UIPopoverController
{
    HMChatViewController * content;
}
/**
 * Returns the HMChatViewController instance that provides the content controller for this popover.
 */
@property (readonly, nonatomic, retain) HMChatViewController * content;

/**
 * Sets/returns whether or not to display this popover in portrait mode.
 */
@property (nonatomic, assign) BOOL portrait;

/**
 * Sets/returns whether or not to display this popover in landscape mode.
 */
@property (nonatomic, assign) BOOL landscape;

///------------------------------------------------------------------------------------------
/// @name Initialization
///------------------------------------------------------------------------------------------
/** Initializes the HMChatPopoverController object to connect with a specific Hipmob app identifier. By default
 * support messages will be shown (messages sent to/from the Hipmob app's operators).
 *
 * The application identifier can be obtained from [https://manage.hipmob.com/#apps](https://manage.hipmob.com/#apps) and will
 * let the Hipmob communication network identify which set of operators, users and other resources
 * to use for this connection. Typically there will be one application identifier for each app.
 * After this call a private connection will be made to the Hipmob communication network for this
 * chat view. Not that when the view is dismissed the connection will be closed.
 *
 * @param view The view to attach the popover to.
 * @param appid The Hipmob application identifier for this app.
 * @param user The user identifier for this user. Can be set to nil to use an internally generated id.
 */
-(id) initWithView:(UIView *)view andAppID:(NSString *)appid andUser:(NSString *)user;

/** Initializes the HMChatPopoverController object to connect with a specific Hipmob app identifier. By default
 * support messages will be shown (messages sent to/from the Hipmob app's operators).
 *
 * The application identifier can be obtained from [https://manage.hipmob.com/#apps](https://manage.hipmob.com/#apps) and will
 * let the Hipmob communication network identify which set of operators, users and other resources
 * to use for this connection. Typically there will be one application identifier for each app.
 * After this call a private connection will be made to the Hipmob communication network for this
 * chat view. Not that when the view is dismissed the connection will be closed.
 *
 * @param view The view to attach the popover to.
 * @param appid The Hipmob application identifier for this app.
 * @param user The user identifier for this user. Can be set to nil to use an internally generated id.
 * @param info Additional connection information to be provided to the connection. Acceptable keys are *name*,
 * *email*, *context* and *pushtoken*.
 */
-(id) initWithView:(UIView *)view andAppID:(NSString *)appid andUser:(NSString *)user andInfo:(NSDictionary *)info;

/** Initializes the HMChatPopoverController object to connect with a specific Hipmob app identifier and to show
 * messages to/from a specific peer.
 *
 * The application identifier can be obtained from [https://manage.hipmob.com/#apps](https://manage.hipmob.com/#apps) and will
 * let the Hipmob communication network identify which set of operators, users and other resources
 * to use for this connection. Typically there will be one application identifier for each app.
 * After this call a private connection will be made to the Hipmob communication network for this
 * chat view. Not that when the view is dismissed the connection will be closed.
 *
 * @param view The view to attach the popover to.
 * @param appid The Hipmob application identifier for this app.
 * @param user The user identifier for this user. For peer messaging the user identifier MUST NOT be nil.
 * @param peer The device identifier for the peer.
 */
-(id) initWithView:(UIView *)view andAppID:(NSString *)appid andUser:(NSString *)user andPeer:(NSString*)peer;

///------------------------------------------------------------------------------------------
/// @name Position and Size
///------------------------------------------------------------------------------------------
/** Sets the position of the popover when displayed in portrait mode. Use this if the popover is not being displayed by a UIButtonBarItem.
 *
 * @param newPortrait The new position for the popover in portrait mode.
 */
-(void) setPortraitPosition:(CGRect)newPortrait;

/** Sets the position of the popover when displayed in landscape mode. Use this if the popover is not being displayed by a UIButtonBarItem.
 *
 * @param newLandscape The new position for the popover in landscape mode.
 */
-(void) setLandscapePosition:(CGRect)newLandscape;

///------------------------------------------------------------------------------------------
/// @name Display Control
///------------------------------------------------------------------------------------------
/**
 * Shows the popover: this will automatically connect the chat (if necessary).
 */
-(void) show;

/**
 * Disconnects the chat and hides the popover. The parent controller should release the HMChatPopoverController instance: it can not be shown again.
 */
-(void) dismiss;
@end
#endif
