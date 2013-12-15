/**
 * @fileOverview The Hipmob Phonegap Android plugin implementation: provides helpdesk search and live chat using the Hipmob support and CRM system. For more information see https://www.hipmob.com/.
 *
 * @author <a href="mailto:femi@hipmob.com">Femi Omojola</a>
 * @version 0.1.0
 * @name Hipmob
 * @copyright 2013 Orthogonal Labs, Inc.
 */
var exec = cordova.require('cordova/exec');

var openChat = function(appid, options, success, failure){
    var opts = {};
    if(options && typeof options == 'object') opts = options;
    var args = [appid, opts];
    exec(success, failure, 'Hipmob', 'openChat', args);
};

var openHelpdeskSearch = function(appid, options, success, failure){
    var opts = {};
    if(options && typeof options == 'object') opts = options;
    var args = [appid, opts];
    exec(success, failure, 'Hipmob', 'openHelpdeskSearch', args);
};

var openHelpdeskArticle = function(appid, url, options, success, failure){
    var opts = {};
    if(options && typeof options == 'object') opts = options;
    var args = [appid, url, opts];
    exec(success, failure, 'Hipmob', 'openHelpdeskArticle', args);
};

module.exports = {
    openChat: openChat,
    openHelpdeskSearch: openHelpdeskSearch,
    openHelpdeskArticle: openHelpdeskArticle
};
