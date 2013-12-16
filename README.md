hipmob-phonegap
===============
The Hipmob PhoneGap sample application is an application built on the HelloCordova sample that shows how to use the Hipmob iOS and Android native PhoneGap plugins to access the Hipmob help and support functions for helpdesk, live chat and support CRM tools using the Hipmob platform. For more information visit https://www.hipmob.com.

It is compatible with iOS 4.3 and higher and Android 2.1 and higher, and works on versions of Cordova greater than 2.9.0.

Installation
---------------------------
This sample comes with the plugins installed: for more information about the plugins see [Hipmob PhoneGap Plugin for iOS](https://github.com/Hipmob/cordova-plugin-hipmob-ios) and [Hipmob PhoneGap Plugin for Android](https://github.com/Hipmob/cordova-plugin-hipmob-android).

The iOS platform build must be built on OSX. Open the **platforms/ios/Hipmob Phonegap Sample.xcodeproj project in Xcode and then build and run it.

To build the Android platform build, copy the **platforms/android/local.properties.template** file to **platforms/android/local.properties** and then edit it to point to your Android SDK directory. You can then do ***cordova build android*** or ***cordova run android***.
