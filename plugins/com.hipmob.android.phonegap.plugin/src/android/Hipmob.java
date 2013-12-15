package com.hipmob.android.phonegap.plugin;

import org.apache.cordova.PluginResult;
import org.apache.cordova.PluginResult.Status;
import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.Intent;
import com.hipmob.android.HipmobCore;
import com.hipmob.android.HipmobHelpDeskSearchActivity;
import com.hipmob.android.HipmobHelpDeskArticleViewActivity;

public class Hipmob extends CordovaPlugin 
{
    @Override
	public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException
    {
	PluginResult result = null;
	if("openChat".equals(action)){
	    try{
		final Intent i = new Intent(cordova.getActivity(), HipmobCore.class);
		i.putExtra(HipmobCore.KEY_APPID, args.get(0).toString());
		JSONObject obj = (JSONObject)args.get(1);
		if(obj.has("title")) i.putExtra(HipmobCore.KEY_TITLE, obj.getString("title"));
		if(obj.has("user")) i.putExtra(HipmobCore.KEY_USERID, obj.getString("user"));
		if(obj.has("name")) i.putExtra(HipmobCore.KEY_NAME, obj.getString("name"));
		if(obj.has("email")) i.putExtra(HipmobCore.KEY_EMAIL, obj.getString("email"));
		if(obj.has("peer")) i.putExtra(HipmobCore.KEY_PEER, obj.getString("peer"));
		if(obj.has("pushtoken")) i.putExtra(HipmobCore.KEY_GCM_TOKEN, obj.getString("pushtoken"));
		if(obj.has("context")) i.putExtra(HipmobCore.KEY_CONTEXT, obj.getString("context"));
		if(obj.has("customdata")) i.putExtra(HipmobCore.KEY_CUSTOM_DATA, obj.getJSONObject("customdata").toString());
		if(obj.has("location")) i.putExtra(HipmobCore.KEY_LOCATION, obj.getString("location"));
		if(obj.has("windowlayout")) i.putExtra(HipmobCore.KEY_WINDOW_LAYOUT, cordova.getActivity().getResources().getIdentifier(obj.getString("windowlayout"), "id", cordova.getActivity().getPackageName()));
		if(obj.has("messagelayout")) i.putExtra(HipmobCore.KEY_MESSAGE_LAYOUT, cordova.getActivity().getResources().getIdentifier(obj.getString("messagelayout"), "id", cordova.getActivity().getPackageName()));
		cordova.getActivity().runOnUiThread(new Runnable(){
			public void run(){
			    cordova.getActivity().startActivity(i);			    
			}
		    });
		callbackContext.sendPluginResult(new PluginResult(Status.OK));
	    }catch(Exception e1){
		callbackContext.sendPluginResult(new PluginResult(Status.ERROR, "Missing app id or title"));
	    }
	    return true;
	}else if("openHelpdeskSearch".equals(action)){
	    try{
		final Intent hd = new Intent(cordova.getActivity(), HipmobHelpDeskSearchActivity.class);
		hd.putExtra(HipmobHelpDeskSearchActivity.KEY_APPID, args.get(0).toString());
		JSONObject obj = (JSONObject)args.get(1);
		if(obj.has("title")) hd.putExtra(HipmobHelpDeskSearchActivity.KEY_TITLE, obj.getString("title"));
		if(obj.has("query")) hd.putExtra(HipmobHelpDeskSearchActivity.KEY_DEFAULT_QUERY, obj.getString("query"));
		if(obj.has("context")) hd.putExtra(HipmobHelpDeskSearchActivity.KEY_CONTEXT, obj.getString("context"));

		// and create a live chat intent
		Intent i = new Intent(cordova.getActivity(), HipmobCore.class);
		i.putExtra(HipmobCore.KEY_APPID, args.get(0).toString());
		if(obj.has("title")) i.putExtra(HipmobCore.KEY_TITLE, obj.getString("title"));
		if(obj.has("user")) i.putExtra(HipmobCore.KEY_USERID, obj.getString("user"));
		if(obj.has("name")) i.putExtra(HipmobCore.KEY_NAME, obj.getString("name"));
		if(obj.has("email")) i.putExtra(HipmobCore.KEY_EMAIL, obj.getString("email"));
		if(obj.has("peer")) i.putExtra(HipmobCore.KEY_PEER, obj.getString("peer"));
		if(obj.has("pushtoken")) i.putExtra(HipmobCore.KEY_GCM_TOKEN, obj.getString("pushtoken"));
		if(obj.has("context")) i.putExtra(HipmobCore.KEY_CONTEXT, obj.getString("context"));
		if(obj.has("customdata")) i.putExtra(HipmobCore.KEY_CUSTOM_DATA, obj.getJSONObject("customdata").toString());
		if(obj.has("location")) i.putExtra(HipmobCore.KEY_LOCATION, obj.getString("location"));
		if(obj.has("windowlayout")) i.putExtra(HipmobCore.KEY_WINDOW_LAYOUT, cordova.getActivity().getResources().getIdentifier(obj.getString("windowlayout"), "id", cordova.getActivity().getPackageName()));
		if(obj.has("messagelayout")) i.putExtra(HipmobCore.KEY_MESSAGE_LAYOUT, cordova.getActivity().getResources().getIdentifier(obj.getString("messagelayout"), "id", cordova.getActivity().getPackageName()));
		hd.putExtra(Intent.EXTRA_INTENT, i);
		cordova.getActivity().runOnUiThread(new Runnable(){
			public void run(){
			    cordova.getActivity().startActivity(hd);
			}
		    });			    
		callbackContext.sendPluginResult(new PluginResult(Status.OK));
	    }catch(Exception e1){
		callbackContext.sendPluginResult(new PluginResult(Status.ERROR, "Missing app id or title"));
	    }
	    return true;
	}else if("openHelpdeskArticle".equals(action)){
	    try{
		final Intent hd = new Intent(cordova.getActivity(), HipmobHelpDeskArticleViewActivity.class);
		hd.putExtra(HipmobHelpDeskArticleViewActivity.KEY_APPID, args.get(0).toString());
		hd.putExtra(HipmobHelpDeskArticleViewActivity.KEY_ARTICLEURL, args.get(1).toString());
		JSONObject obj = (JSONObject)args.get(2);
		if(obj.has("title")) hd.putExtra(HipmobHelpDeskArticleViewActivity.KEY_TITLE, obj.getString("title"));
		if(obj.has("context")) hd.putExtra(HipmobHelpDeskArticleViewActivity.KEY_CONTEXT, obj.getString("context"));

		// and create a live chat intent
		Intent i = new Intent(cordova.getActivity(), HipmobCore.class);
		i.putExtra(HipmobCore.KEY_APPID, args.get(0).toString());
		if(obj.has("title")) i.putExtra(HipmobCore.KEY_TITLE, obj.getString("title"));
		if(obj.has("user")) i.putExtra(HipmobCore.KEY_USERID, obj.getString("user"));
		if(obj.has("name")) i.putExtra(HipmobCore.KEY_NAME, obj.getString("name"));
		if(obj.has("email")) i.putExtra(HipmobCore.KEY_EMAIL, obj.getString("email"));
		if(obj.has("peer")) i.putExtra(HipmobCore.KEY_PEER, obj.getString("peer"));
		if(obj.has("pushtoken")) i.putExtra(HipmobCore.KEY_GCM_TOKEN, obj.getString("pushtoken"));
		if(obj.has("context")) i.putExtra(HipmobCore.KEY_CONTEXT, obj.getString("context"));
		if(obj.has("customdata")) i.putExtra(HipmobCore.KEY_CUSTOM_DATA, obj.getJSONObject("customdata").toString());
		if(obj.has("location")) i.putExtra(HipmobCore.KEY_LOCATION, obj.getString("location"));
		if(obj.has("windowlayout")) i.putExtra(HipmobCore.KEY_WINDOW_LAYOUT, cordova.getActivity().getResources().getIdentifier(obj.getString("windowlayout"), "id", cordova.getActivity().getPackageName()));
		if(obj.has("messagelayout")) i.putExtra(HipmobCore.KEY_MESSAGE_LAYOUT, cordova.getActivity().getResources().getIdentifier(obj.getString("messagelayout"), "id", cordova.getActivity().getPackageName()));
		hd.putExtra(Intent.EXTRA_INTENT, i);
		cordova.getActivity().runOnUiThread(new Runnable(){
			public void run(){
			    cordova.getActivity().startActivity(hd);
			}
		    });			    
		callbackContext.sendPluginResult(new PluginResult(Status.OK));
	    }catch(Exception e1){
		callbackContext.sendPluginResult(new PluginResult(Status.ERROR, "Missing app id or title"));
	    }
	    return true;
	}
	return false;
    }
}
