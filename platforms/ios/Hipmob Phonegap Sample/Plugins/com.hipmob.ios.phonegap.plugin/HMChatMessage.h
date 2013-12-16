//
//  HMChatMessage.h
//  hipmob
//
//  Created by Olufemi Omojola on 7/10/13.
//  Copyright (c) 2013 Orthogonal Labs, Inc. All rights reserved.
//

#ifndef hipmob_HMChatMessage_h
#define hipmob_HMChatMessage_h

/** The HMChatMessage class includes all the information about a single chat message.
 */
@interface HMChatMessage : NSObject
{
    
}
/**
 * The Hipmob application identifier for the Hipmob app that sent/received this message.
 */
@property (readonly, nonatomic, retain) NSString * app;

/**
 * The session this chat message was received in: every message received within the same session will have the same session value.
 */
@property (readonly, nonatomic, retain) NSString * session;

/**
 * The type of message this is: will be one of "text", "url", "image", "audio", "json", or "binary"
 */
@property (readonly, nonatomic, retain) NSString * subtype;

/**
 * The display name of the sender of this message.
 */
@property (readonly, nonatomic, retain) NSString * from;

/**
 * The unique identifier of the sender of this message: if it was sent by this device the value will be nil.
 */
@property (readonly, nonatomic, retain) NSString * sender;

/**
 * The remote identifier of the message: if it was sent by this device the value will be nil.
 */
@property (readonly, nonatomic, retain) NSString * remoteId;

/**
 * The body of the message: for text messages, it will be the text of the message. For json messages, it will be a JSON string. For binary messages, it will be the base64 encoded content. For an image or audio message it will be the URL of the message content.
 */
@property (readonly, nonatomic, retain) NSString * body;

/**
 * Indicates if the message has been delivered (0) or not (1). This is for image/audio messages.
 */
@property (readonly, nonatomic, assign) NSInteger context;

/**
 * Indicates if the message has been queued (1) or not (0). This is for outgoing messages sent while we're offline.
 */
@property (readonly, nonatomic, assign) NSInteger queued;

/**
 * Stores additional message attributes: for image messages, stores the url, size, thumbnail url and thumbnail size. For audio messages, stores the format, the size and the url.
 */
@property (readonly, nonatomic, retain) NSDictionary * attributes;

/**
 * Stores the date this message was created.
 */
@property (readonly, nonatomic, retain) NSDate * created;

/**
 * Stores the date this message was updated: currently always nil.
 */
@property (readonly, nonatomic, retain) NSDate * updated;

/**
 * The unique identifier of the recipient of this message, or nil if it is from this device.
 */
@property (readonly, nonatomic, retain) NSString * to;

@end


#endif
