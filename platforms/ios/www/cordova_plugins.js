cordova.define('cordova/plugin_list', function(require, exports, module) {
module.exports = [
    {
        "file": "plugins/com.hipmob.android.phonegap.plugin/www/hipmob.js",
        "id": "com.hipmob.android.phonegap.plugin.Hipmob",
        "clobbers": [
            "window.plugins.Hipmob"
        ]
    },
    {
        "file": "plugins/com.hipmob.ios.phonegap.plugin/www/hipmob.js",
        "id": "com.hipmob.ios.phonegap.plugin.Hipmob",
        "clobbers": [
            "window.plugins.Hipmob"
        ]
    }
]
});