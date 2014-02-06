//
//  HMChatView.h
//  hipmob
//
//  Created by Olufemi Omojola on 6/1/13.
//  Copyright (c) 2012 - 2013 Orthogonal Labs, Inc.
//
#ifndef _hipmob_hmchatview_h_
#define _hipmob_hmchatview_h_

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreData/CoreData.h>

@class HMChatView;
@class HMRemoteConnection;
@class HMChatMessage;
@protocol HMRemoteConnectionDelegate;

/**
 * The HMRegisterUserDelegate protocol defines the required methods implemented by delegates using an HMRegisterUser instance to perform a background registration.
 */
@protocol HMRegisterUserDelegate<NSObject>;

@required
/**
 * Tells the delegate that a registration request succeeded.
 *
 * @param app The application the registration request was for.
 */
-(void)didRegistrationSucceed:(NSString *)app;

/**
 * Tells the delegate that a registration request failed.
 *
 * @param app The application the registration request was for.
 */
-(void)didRegistrationFail:(NSString *)app;
@end

/** The HMRegisterUser class.
 
 HMRegisterUser is a simple class that allows an app to register a user for a specific application with a push token. 
 * This allows the user to receive push messages even if they haven't opened the chat window.
 */
@interface HMRegisterUser : NSObject
{
    
}
/**
 * The HMRegisterUserDelegate to be notified.
 */
@property (assign) id<HMRegisterUserDelegate>delegate;

/**
 * @param user The user identifier for the user (must not be nil).
 * @param app The application identifier for the app we're interested in (must not be nil).
 * @param token The push notification token for the device (must not be nil).
 * @param userinfo A user information dictionary containing the user's name, context, location or email: can be nil.
 * @param registrationDelegate An HMRegisterUserDelegate instance used to notify the caller of the results of the registration: can be nil.
 */
-(id) initWithUser:(NSString *)user andApp:(NSString *)app andPushToken:(NSString *)token andInfo:(NSDictionary *)userinfo
      withDelegate:(id<HMRegisterUserDelegate>)registrationDelegate;
@end

/**
 * The HMChatOperatorAvailabilityCheckDelegate protocol supports a simple callback that allows an application to check if any operators are available for the associated Hipmob application. This can be used to show/hide the live chat button based on operator availability.
 */
@protocol HMChatOperatorAvailabilityCheckDelegate <NSObject>;
@required
/**
 * Tells the delegate that one or more chat operators are available for a specified app. An HTTP call is made to the Hipmob availability API and the
 * result of the call is returned.
 *
 * @param operatorCheck The HMChatOperatorAvailabilityCheck instance that performed the callback.
 * @param app The Hipmob application ID for which operator(s) are available.
 */
-(void)operatorCheck:(id)operatorCheck isOperatorAvailable:(NSString *)app;

/**
 * Tells the delegate that no chat operators are available for a specified app. An HTTP call is made to the Hipmob availability API and the
 * result of the call is returned.
 *
 * @param operatorCheck The HMChatOperatorAvailabilityCheck instance that performed the callback.
 * @param app The Hipmob application ID for which operator(s) are not available.
 */
-(void)operatorCheck:(id)operatorCheck isOperatorOffline:(NSString *)app;
@end

/** HMChatOperatorAvailabilityCheck is a simple class that allows an app to check if any operators are available for a specific Hipmob app.
 
 As an example, if you'd like to only show the live chat button when an operator is available, you can implement the HMChatViewAvailabilityCheckDelegate protocol and then create an instance of [HMChatOperatorAvailabilityCheck](./Classes/HMChatOperatorAvailabilityCheck.html). This will make the necessary network calls to the Hipmob chat network and then invoke the appropriate delegate methods. For example, here we call the method in the viewDidAppear function.
 
     - (void)viewDidAppear:(BOOL)animated
     {
     [super viewDidAppear:animated];
     
     HMChatOperatorAvailabilityCheck * check = [[HMChatOperatorAvailabilityCheck alloc] initWithAppID:@"2ea7d86854df4ca185af84e68ea72fe1" andNotify:self];
     }
 
 And in the delegate methods we change the background color of the live chat button to orange if there are no operators available, or green if there are.
 
     -(void)operatorCheck:(id)operatorCheck isOperatorOffline:(NSString *)app
     {
     _navBar.topItem.rightBarButtonItem.tintColor = [UIColor orangeColor];
     [check release];
     }
     
     -(void)operatorCheck:(id)operatorCheck isOperatorAvailable:(NSString *)app
     {
     _navBar.topItem.rightBarButtonItem.tintColor = [UIColor colorWithRed:0/255.0 green:153.0/255.0 blue:0/255.0 alpha:1];
     [check release];
     }

 */
@interface HMChatOperatorAvailabilityCheck : NSObject
{
    
}
/** The HMChatOperatorAvailabilityCheckDelegate to be notified.
 */
@property (assign) id<HMChatOperatorAvailabilityCheckDelegate>delegate;

///------------------------------------------------------------------------------------------
/// @name Initialization
///------------------------------------------------------------------------------------------
/** Initializes the HMChatAvailabilityCheck object to check if any operators are available
 * for the app with the specified Hipmob app identifier.
 *
 * The application identifier can be obtained from https://manage.hipmob.com/#apps and will
 * let the Hipmob communication network identify which set of operators, users and other resources
 * to use for this connection. Typically there will be one application identifier for each app.
 * After this call a private connection will be made to the Hipmob communication network to check
 * if there are any operators online for this app.
 *
 * @param appid The Hipmob application identifier for this app.
 * @param delegate THe HMChatOperatorAvailabilityCheckDelegate to be notified. Must not be null.
 */
-(id) initWithAppID:(NSString *)appid andNotify:(id<HMChatOperatorAvailabilityCheckDelegate>)delegate;


/**
 * Cancels the call.
 */
-(void)cancel;
@end

/** The HMChatViewDelegate protocol defines the required and optional methods implemented by delegates of HMChatView instances.
 *
 * The delegate will be notified when a URL is received, and will be notified when the view is being dismissed.
 * All methods are optional
 */
@protocol HMChatViewDelegate <NSObject>;

@optional
/** Tells the delegate that a URL was pushed from the server. The delegate may choose to handle the URL itself: if it does, it should
 * return TRUE or YES. If the delegate does not implement this method or if it returns FALSE or NO (i.e. it either does not handle
 * URLs of this format or if it doesn't want to implement any special logic) then the URL will be opened in the platform browser (i.e. Safari.
 *
 * @param chatView The HMChatView instance that received the URL.
 * @param url The URL that was received.
 * @param messageId The id of the message that contained the URL. If you have the delegate associated with multiple chat view instances then you may receive multiple calls: you can use the messageId to ensure you only take action a single time.
 * @result TRUE If the delegate handled the URL, FALSE otherwise.
 */
-(BOOL)chatView:(id)chatView willHandleURL:(NSString*)url messageId:(NSString*)messageId;

/**
 * Tells the delegate that an error occured.
 *
 * @param chatView The HMChatView instance that received the error.
 * @param error The error message that occured.
 */
-(void)chatView:(id)chatView didErrorOccur:(NSString *)error;

/**
 * Tells the delegate that a message was received that was relevant to this view.
 *
 * If multiple views are connected to a single remote connection a message may come in that is not relevant to the current view
 * (for example, a message from a peer may arrive when the currently visible chat view is for support messages). This provides a 
 * way for the chatview to indicate to its delegate that a new message that arrived is actually relevant to this chat view, so the 
 * owner may perform some additional notification.
 *
 * @param chatView The HMChatView instance that received the message.
 * @param message The HMChatMessage instance that was received.
 */
-(void)chatView:(id)chatView didReceiveMessage:(HMChatMessage *)message;

/**
 * Tells the delegate that a message was sent that was relevant to this view.
 *
 * If multiple views are connected to a single remote connection a message may have been sent that is not relevant to the current view
 * (for example, a message from another chat view with a peer may be sent when the currently visible chat view is for support messages).
 * This provides a way for the chatview to indicate to its delegate that a new message that was sent was from this chat view, so the
 * owner may perform some additional notification.
 *
 * @param chatView The HMChatView instance that sent the message.
 * @param message The HMChatMessage instance that was sent.
 */
-(void)chatView:(id)chatView didSendMessage:(HMChatMessage *)message;

/**
 * Tells the delegate that an operator accepted the chat.
 *
 * @param chatView The HMChatView instance that sent the message.
 * @param operator The operator's user identifier.
 */
-(void)chatView:(id)chatView didOperatorAccept:(NSString *)operator;

/**
 * Tells the delegate that the connection came online.
 *
 * @param chatView The HMChatView instance that received the notification.
 */
-(void)viewDidConnect:(id)chatView;

/**
 * Tells the delegate that the connection went offline.
 *
 * @param chatView The HMChatView instance that received the notification.
 */
-(void)viewDidDisconnect:(id)chatView;

/**
 * Tells the delegate that an operator is online.
 *
 * @param chatView The HMChatView instance that received the notification.
 */
-(void)viewDidOperatorComeOnline:(id)chatView;

/**
 * Tells the delegate that no operators are online.
 *
 * @param chatView The HMChatView instance that received the notification.
 */
-(void)viewDidOperatorGoOffline:(id)chatView;

/**
 * Tells the delegate that a peer came online.
 *
 * @param chatView The HMChatView instance that received the notification.
 * @param peer The peer that came online.
 */
-(void)chatView:(id)chatView didPeerGoOnline:(NSString *)peer;

/**
 * Tells the delegate that a peer went offline.
 *
 * @param chatView The HMChatView instance that received the notification.
 * @param peer The peer that went offline.
 */
-(void)chatView:(id)chatView didPeerGoOffline:(NSString *)peer;

/**
 * Asks the delegate to give us the height of a specific row.
 *
 * @param chatView The HMChatView instance that received the notification.
 * @param message The HMChatMessage instance. This instance is auto released: if it is further retained by the delegate then any additional memory management tasks will need to be handled by the delegate.
 * @param tableView The tableView instance used to render the messages.
 */
-(CGFloat)chatView:(id)chatView heightForMessageRow:(HMChatMessage *)message withTableView:(UITableView *)tableView;

/**
 * Asks the delegate to give us the UITableViewCell for a specific message.
 *
 * @param chatView The HMChatView instance that received the notification.
 * @param message The HMChatMessage instance. This instance is auto released: if it is further retained by the delegate then any additional memory management tasks will need to be handled by the delegate.
 * @param tableView The tableView instance used to render the messages.
 */
- (UITableViewCell *)chatView:(id)chatView cellForMessageRow:(HMChatMessage *)message withTableView:(UITableView *)tableView;
@end

/** The core Hipmob chat view.
 
 HMChatView is a custom UIView that renders a Hipmob chat conversation. It provides a set of delegate callbacks that allow the view controller to be notified of changes in the connection to the Hipmob remote connection (if it was created by this class). If the remote connection was supplied to the view then no delegate callbacks will occur based on changes in the connection: this allows a global connection to be used by multiple views.
 
 <h2>Connecting to the Hipmob chat network</h2>
 Once the chat view is fully setup, you'll need to call the connect method to actually connect to the Hipmob chat network. Typically this can be called from the enclosing view controller's viewDidAppear method. Once the user starts typing a message then the connect method will be invoked if necessary.
 
 <h2>Customizing the messages</h2>
 By default, the HMChatView control emulates the iOS Messages interface, and provides properties to let the fonts and text colors be customized. For applications that require additional customization, the [HMChatViewDelegate chatView:cellForMessageRow:withTableView:] and [HMChatViewDelegate chatView:heightForMessageRow:withTableView:] methods of the HMChatViewDelegate protocol allow complete control over the appearance of each row.

 These emulate the standard table view delegate functions: the first passes you the chat message object (with all the details such as the sender's name, the time the message was delivered and the message text) and the UITableView and expects to receive the height of the row for that message, and the second passes you the chat message object and UITableView and expects to get back the UITableViewCell that will be displayed. This should let you completely control the appearance of every message row: the HMChatMessage.h header describes the fields in the individual header, and with this you can also completely choose fonts and colors or add avatars to each row.
 */
@interface HMChatView : UIView
{
    
}

/**
 * The Hipmob remote connection used by this chat view.
 */
@property (readonly, nonatomic, retain) NSString * app;

/**
 * The peer id this chat view was initialized with: this will be nil if it was initialized as a support chat.
 */
@property (readonly, nonatomic, retain) NSString * peer;

/** The HMChatViewDelegate for this chat view.
 */
@property (assign) id<HMChatViewDelegate>delegate;

/**
 * Returns the send button: this can be used to customize the button appearance.
 */
@property (readonly, nonatomic, retain) UIButton * send;

/**
 * Returns the input textfield: this can be used to customize the textfield appearance and behavior.
 */
@property (readonly, nonatomic, retain) UITextView * input;

/**
 * Returns the table view: this can be used to customize the tableview appearance.
 */
@property (readonly, nonatomic, retain) UITableView * table;

/**
 * Returns the toolbar that contains the send button and the input field: this can be used to customize the toolbar appearance.
 */
@property (readonly, nonatomic, retain) UIToolbar * toolbar;

/**
 * Indicates the maximum number of lines the input view should expand to accommodate. If the user types more lines than this number
 * the input will scroll.
 */
@property (assign, nonatomic) int maxInputLines;

/**
 * Contains the placeholder text. If not set, the input will be blank when no text has been entered.
 */
@property (nonatomic, retain) NSString * placeholder;

/**
 * Contains the color for the placeholder text. Defaults to gray.
 */
@property (nonatomic, retain) UIColor * placeholderColor;

/**
 * Contains the font used to render chat messages sent by the user. Defaults to the system font at a size of 14.0.
 */
@property (nonatomic, retain) UIFont * sentMessageFont;

/**
 * Contains the font used to render chat messages received by the user. Defaults to the system font at a size of 14.0.
 */
@property (nonatomic, retain) UIFont * receivedMessageFont;

/**
 * Contains the color used to render chat messages sent by the user. Defaults to black.
 */
@property (nonatomic, retain) UIColor * sentTextColor;

/**
 * Contains the color used to render chat messages received by the user. Defaults to black.
 */
@property (nonatomic, retain) UIColor * receivedTextColor;

/**
 * Contains the margins to be applied to the text bubble for sent messages.
 */
@property (nonatomic, assign) UIEdgeInsets sentMargin;

/**
 * Contains the margins to be applied to the text bubble for received messages.
 */
@property (nonatomic, assign) UIEdgeInsets receivedMargin;

/**
 * Contains the padding to be applied to the text bubble for sent messages.
 */
@property (nonatomic, assign) UIEdgeInsets sentPadding;

/**
 * Contains the padding to be applied to the text bubble for received messages.
 */
@property (nonatomic, assign) UIEdgeInsets receivedPadding;

/**
 * Contains extra padding to be applied to the text bubble for sent messages. This is useful to tune the position of the text within the bubble.
 */
@property (nonatomic, assign) UIEdgeInsets sentExtraPadding;

/**
 * Contains extra padding to be applied to the text bubble for received messages. This is useful to tune the position of the text within the bubble.
 */
@property (nonatomic, assign) UIEdgeInsets receivedExtraPadding;

///------------------------------------------------------------------------------------------
/// @name Initialization
///------------------------------------------------------------------------------------------
/** Initializes the HMChatView object to connect with a specific Hipmob app identifier. By default
 * support messages will be shown (messages sent to/from the Hipmob app's operators).
 *
 * The application identifier can be obtained from https://manage.hipmob.com/#apps and will
 * let the Hipmob communication network identify which set of operators, users and other resources
 * to use for this connection. Typically there will be one application identifier for each app.
 * After this call a private connection will be made to the Hipmob communication network for this 
 * chat view. Not that when the view is dismissed the connection will be closed.
 *
 * @param frame The initial frame for the chat view.
 * @param appid The Hipmob application identifier for this app.
 * @param user The user identifier for this user. Can be set to nil to use an internally generated id.
 */
-(id) initWithFrame:(CGRect)frame andAppID:(NSString *)appid andUser:(NSString *)user;

/** Initializes the HMChatView object to connect with a specific Hipmob app identifier. By default
 * support messages will be shown (messages sent to/from the Hipmob app's operators).
 *
 * The application identifier can be obtained from https://manage.hipmob.com/#apps and will
 * let the Hipmob communication network identify which set of operators, users and other resources
 * to use for this connection. Typically there will be one application identifier for each app.
 * After this call a private connection will be made to the Hipmob communication network for this
 * chat view. Not that when the view is dismissed the connection will be closed.
 *
 * @param frame The initial frame for the chat view.
 * @param appid The Hipmob application identifier for this app.
 * @param user The user identifier for this user. Can be set to nil to use an internally generated id.
 * @param info Additional connection information to be provided to the connection. Acceptable keys are *name*, 
 * *email*, *context* and *pushtoken*.
 */
-(id) initWithFrame:(CGRect)frame andAppID:(NSString *)appid andUser:(NSString *)user andInfo:(NSDictionary *)info;

/** Initializes the HMChatView object to connect with a specific Hipmob app identifier and to show
 * messages to/from a specific peer.
 *
 * The application identifier can be obtained from https://manage.hipmob.com/#apps and will
 * let the Hipmob communication network identify which set of operators, users and other resources
 * to use for this connection. Typically there will be one application identifier for each app.
 * After this call a private connection will be made to the Hipmob communication network for this
 * chat view. Not that when the view is dismissed the connection will be closed.
 *
 * @param frame The initial frame for the chat view.
 * @param appid The Hipmob application identifier for this app.
 * @param user The user identifier for this user. For peer messaging the user identifier MUST NOT be nil.
 * @param peer The user identifier for the peer to be communicated with.
 */
-(id) initWithFrame:(CGRect)frame andAppID:(NSString *)appid andUser:(NSString *)user andPeer:(NSString*)peer;

/** Initializes the HMChatView object to use an existing Hipmob remote connection.  By default
 * support messages will be shown (messages sent to/from the Hipmob app's operators).
 *
 * This is an advanced usage: it allows a single global Hipmob remote connection instance to be 
 * used with multiple chat views. When the view is dismissed the connection will NOT be closed.
 *
 * @param frame The initial frame for the chat view.
 * @param connection The HMRemoteConnection instance for this app.
 */
-(id) initWithFrame:(CGRect)frame andConnection:(HMRemoteConnection *)connection;

/** Initializes the HMChatView object to use an existing Hipmob remote connection and to show
 * messages to/from a specific peer.
 *
 * This is an advanced usage: it allows a single global Hipmob remote connection instance to be
 * used with multiple chat views. When the view is dismissed the connection will NOT be closed.
 * Note that the user id MUST have been set when the connection was created to allow peer messages
 * to be sent and received.
 *
 * @param frame The initial frame for the chat view.
 * @param connection The HMRemoteConnection instance for this app.
 * @param peer The user identifier for the peer to be communicated with.
 */
-(id) initWithFrame:(CGRect)frame andConnection:(HMRemoteConnection *)connection andPeer:(NSString*)peer;

/** Sets the Hipmob operator group this chat view should communicate with. This must be set before the connect selector is called.
 *
 * @param group The Hipmob operator group this chat view should communicate with.
 */
-(void)setGroup:(NSString *)group;

/** Clears a custom data attribute from this chat view's connection.
 *
 * This method clears the stored custom data value associated with a specific key. This must be called
 * prior to calling the connect method to take effect: calling it after connect has been called will
 * result in no change to the connection information. In addition, if this chat view was initialized
 * with an existing connection this method will have no effect. 
 * After calling this method value associated with the specified key will no longer be associated with 
 * the connection and will not be available to certain integration services within the Hipmob communication 
 * network.
 *
 * Unless specifically required, this method is safe to ignore.
 *
 * @param key The custom data attribute key to be cleared.
 */
-(void) clearCustomDataForKey:(NSString *)key;

/** Sets a custom data attribute on this chat view's connection.
 *
 * This method stores a custom data attribute and associates it with a specific key. This must be called
 * prior to calling the connect method to take effect: calling it after connect has been called will
 * result in no change to the connection information. In addition, if this chat view was initialized
 * with an existing connection this method will have no effect. The custom data passed here will be associated with
 * the connection and made available to certain integration services within the Hipmob communication network.
 *
 * Unless specifically required, this method is safe to ignore.
 *
 * @param data The custom data attribute value to be attached to this connection.
 * @param key The custom data attribute key to use when attaching this data to this connection.
 */
-(void) setCustomData:(NSString *)data forKey:(NSString *)key;

/** Starts the connection to the Hipmob communication network.
 *
 * This method should be invoked when the host application is ready to start actively using the chat view. The 
 * remote connection will be started up if it was not already set, and the appropriate delegate callbacks will be invoked.
 * as the connection progresses.
 *
 * @result TRUE if the connection process was successfully started, FALSE otherwise (if the connection was already active).
 * @exception NSException If the info property is not set.
 * @exception NSException If the statusmessages property is not set.
 */
-(BOOL) connect;

/** Sets the push token for this device. Must be called prior to connect.
 *
 * @param pushtoken The push token.
 */
-(void) setPushToken:(NSData *)pushtoken;

/** Clears the push token for this device. Must be called prior to connect.
 *
 */
-(void) clearPushToken;
 
/** Updates the user's displayed name.
 *
 * @param value The new name for this user.
 * @exception NSException If the value is nil.
 *
 */
-(void) updateName:(NSString*)value;

/** Updates the user's displayed email.
 *
 * @param value The new email for this user.
 * @exception NSException If the value is nil.
 *
 */
-(void) updateEmail:(NSString*)value;

/** Updates the user's displayed context.
 *
 * @param value The new context for this user.
 * @exception NSException If the value is nil.
 *
 */
-(void) updateContext:(NSString*)value;

/** Updates the user's displayed location.
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

/** Sends a message to the recipient of this chat session.
 *
 * @param text The text of the message.
 * @result YES if the message was successfully sent (the HMChatView instance is connected and the message could be delivered), NO otherwise.
 */
-(BOOL) sendMessage:(NSString *)text;

///------------------------------------------------------------------------------------------
/// @name Chat View Connection Status
///------------------------------------------------------------------------------------------
/** Returns the connection status of this chat view object.
 *
 * @result TRUE if this chat view is currently connected to the Hipmob communication network, and FALSE otherwise.
 */
-(BOOL) isConnected;

///------------------------------------------------------------------------------------------
/// @name Chat View Connection Shutdown
///------------------------------------------------------------------------------------------
/** Shuts down this chat view's connection (if it was internally started).
 *
 * Once this is called this chat view will no longer receive updates: connect will have to be called a second time before any messages will be sent/received. If the chat view was started with initWithConnection then this call has no effect.
 */
-(void) disconnect;
@end
#endif

