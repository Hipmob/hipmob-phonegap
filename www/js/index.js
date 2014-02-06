/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
var app = {
    // Application Constructor
    initialize: function() {
        this.bindEvents();
    },
    // Bind Event Listeners
    //
    // Bind any events that are required on startup. Common events are:
    // 'load', 'deviceready', 'offline', and 'online'.
    bindEvents: function() {
        document.addEventListener('deviceready', this.onDeviceReady, false);
    },
    // deviceready Event Handler
    //
    // The scope of 'this' is the event. In order to call the 'receivedEvent'
    // function, we must explicity call 'app.receivedEvent(...);'
    onDeviceReady: function() {
        app.receivedEvent('deviceready');
    },
    // Update DOM on a Received Event
    receivedEvent: function(id) {
        var parentElement = document.getElementById(id);
        var listeningElement = parentElement.querySelector('.listening');
        var receivedElement = parentElement.querySelector('.received');

        listeningElement.setAttribute('style', 'display:none;');
        receivedElement.setAttribute('style', 'display:block;');

        console.log('Received Event: ' + id);

	if( window.plugins && window.plugins.Hipmob ) {
	    var hipmob_app_id = 'b937e4b524f84fde963da380b948c227';
	    var Hipmob = window.plugins.Hipmob;
	    
	    var success = function(){
		//alert("SUCCESS: "+JSON.stringify(arguments));
	    };
	    var failure = function(){
		//alert("FAILED: " + JSON.stringify(arguments));
	    };
	    
	    document.getElementById('openchat').addEventListener('click', function(event){
		/*
		 * Live chat
		 */
		Hipmob.openChat(hipmob_app_id, { 'title': 'Help' }, success, failure);
	    });

	    document.getElementById('openhelpdesk').addEventListener('click', function(event){
		/*
		 * Help desk
		 */
		Hipmob.openHelpdeskSearch(hipmob_app_id, { 'title': 'Help', 'query': 'Android' }, success, failure);
	    });

	    document.getElementById('openarticle').addEventListener('click', function(event){
		/*
		 * Article display.
		 */
		Hipmob.openHelpdeskArticle(hipmob_app_id, "6ca759008f174547b6f2b263f8c7ae77", { 'title': 'Live support for HTML5 & Phonegap apps' }, success, failure);
	    });
	}else{
	    alert('Hipmob plugin not available/ready.');
	}
    }
};
