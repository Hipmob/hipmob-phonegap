//
//  HMChatView.h
//  hipmob
//
//  Created by Olufemi Omojola on 6/1/13.
//  Copyright (c) 2012 - 2013 Orthogonal Labs, Inc.
//
#ifndef _hipmob_hmhelpdesksearchview_h_
#define _hipmob_hmhelpdesksearchview_h_

#import "HMVersion.h"
#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreData/CoreData.h>

@interface HMSearchResultRow : NSObject
{

}
/**
 * The id of this article.
 */
@property (nonatomic, retain) NSString * articleId;

/**
 * The title of this article.
 */
@property (nonatomic, retain) NSString * title;

/**
 * The URL for this article.
 */
@property (nonatomic, retain) NSString * url;

/**
 * The baseurl to be used when resolving relative references within the text.
 */
@property (nonatomic, retain) NSString * baseurl;

/**
 * The HTML body of the article.
 */
@property (nonatomic, retain) NSString * body;

/**
 * The plain-text preview for the article.
 */
@property (nonatomic, retain) NSString * plain;

/**
 * The tags for the article.
 */
@property (nonatomic, retain) NSArray * tags;
@end

@class HMHelpDeskSearchView;

/** The HMHelpDeskSearchViewDelegate protocol defines the required and optional methods implemented by delegates of HMHelpDeskSearchView instances.
 *
 * The delegate will be notified when a URL is received, and will be notified when the view is being dismissed.
 * All methods are optional
 */
@protocol HMHelpDeskSearchViewDelegate <NSObject>;

@optional
/** Provides the delegate with an array of results that are about to be displayed to the user. The delegate may choose
 * to alter the array to remove specific results or to adjust the sort order. The search view caches search results
 * on a per-query basis: for any specific query this delegate callback will be invoked at most once. The array will contain HMSearchResultRow instances.
 *
 * @param searchView The HMHelpDeskSearchView instance that generated the event.
 * @param results The search results: this is an array of HMSearchResultRow instances.
 * @param query The query that produced these results.
 */
-(void)searchView:(id)searchView willRenderResults:(NSMutableArray *)results forQuery:(NSString *)query;

/** Tells the delegate that a specific article was selected. The delegate may choose to handle the article itself: if it does, it should
 * return TRUE or YES. If the delegate does not implement this method or if it returns FALSE or NO (i.e. it either does not handle
 * URLs of this format or if it doesn't want to implement any special logic) then the URL will be opened in a private WebView.
 *
 * @param searchView The HMHelpDeskSearchView instance that generated the event.
 * @param articleId The id of the selected article.
 * @param title The title of the selected article.
 * @param url The URL of the selected article.
 * @param baseURL The base URL for resolving embedded images and content.
 * @param content The content of the selected article.
 *
 * @result YES If the delegate handled the article display, NO otherwise.
 */
-(BOOL)searchView:(id)searchView didSelectArticle:(NSString *)articleId withTitle:(NSString *)title andURL:(NSString *)url andBaseURL:(NSString *)baseURL andContent:(NSString *)content;

/** Tells the delegate that a specific article was loaded. The delegate must handle the article display by itself.
 * This is invoked in response to the loadArticle call.
 *
 * @param searchView The HMHelpDeskSearchView instance that generated the event.
 * @param articleId The id of the loaded article.
 * @param title The title of the loaded article.
 * @param url The URL of the loaded article.
 * @param baseURL The base URL for resolving embedded images and content.
 * @param content The content of the loaded article.
 *
 */
-(void)searchView:(id)searchView didLoadArticle:(NSString *)articleId withTitle:(NSString *)title andURL:(NSString *)url andBaseURL:(NSString *)baseURL andContent:(NSString *)content;
/**
 * Tells the delegate that an error occured.
 *
 * @param searchView The HMHelpDeskSearchView instance that received the error.
 * @param error The error message that occured.
 */
-(void)searchView:(id)searchView didErrorOccur:(NSString *)error;
@end

/** The core Hipmob help desk search view.
 
 HMHelpDeskSearchView is a custom UIView that renders a help desk search interface. It provides a set of delegate callbacks that allow the view controller to be notified of user actions in the search view.
 *
 */
@interface HMHelpDeskSearchView : UIView <UISearchBarDelegate>
{
    
}

/**
 * The Hipmob application used by this search view.
 */
@property (readonly, nonatomic, retain) NSString * app;

/**
 * The Hipmob user identifier for the user running this search.
 */
@property (readonly, nonatomic, retain) NSString * user;

/**
 * The default search query to use when the view first appears.
 */
@property (nonatomic, retain) NSString * defaultQuery;

/**
 * The tag filter to apply to all queries.
 */
@property (nonatomic, retain) NSString * tagFilter;

/**
 * The user's context when the search was loaded.
 */
@property (nonatomic, retain) NSString * context;

/**
 * The minimum number of characters the user has to type before the query is processed.
 */
@property (assign, nonatomic) int minimumQueryLength;

/** The HMHelpDeskSearchViewDelegate for this chat view.
 */
@property (assign) id<HMHelpDeskSearchViewDelegate>delegate;

/**
 * Returns the search bar: this can be used to customize the search bar appearance and behavior.
 */
@property (readonly, nonatomic, retain) UISearchBar * search;

/**
 * Returns the table view: this can be used to customize the tableview appearance.
 */
@property (readonly, nonatomic, retain) UITableView * table;

///------------------------------------------------------------------------------------------
/// @name Initialization
///------------------------------------------------------------------------------------------
/** Initializes the HMHelpDeskSearchView object to connect with a specific Hipmob app identifier. This 
 * will control which help desk the search runs through.
 *
 * The application identifier can be obtained from https://manage.hipmob.com/#apps and will
 * let the Hipmob network identify the specific help desk you wish to searches to be run against.
 * Typically there will be one application identifier for each app.
 *
 * @param frame The initial frame for the chat view.
 * @param appid The Hipmob application identifier for this app.
 * @param userid The user identifier for the user making the search.
 */
-(id) initWithFrame:(CGRect)frame andAppID:(NSString *)appid andUser:(NSString *)userid;

///------------------------------------------------------------------------------------------
/// @name Utilities
///------------------------------------------------------------------------------------------
/**
 * Flushes the query cache. Useful to deal with memory warnings.
 */
-(void) flushCache;

/**
 * Loads a specific article (by id). This can be used to retrieve the content for a particular
 * help page.
 *
 * @param articleId The identifier for the help article to be rendered.
 */
-(void) loadArticle:(NSString *)articleId;
@end
#endif

