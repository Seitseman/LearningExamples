import VPlayApps 1.0
import VPlayPlugins 1.0
import QtQuick 2.0
import "helper"
import "pages"

/*/////////////////////////////////////
  NOTE:
  Additional integration steps are needed to use V-Play Plugins, for example to add and link required libraries for Android and iOS.
  Please follow the integration steps described in the plugin documentation of your chosen plugins:
  - AdMob: https://v-play.net/doc/plugin-admob/
  - Chartboost: https://v-play.net/doc/plugin-chartboost/
  - Soomla: https://v-play.net/doc/plugin-soomla/
  - Google Analytics: https://v-play.net/doc/plugin-googleanalytics/
  - Flurry: https://v-play.net/doc/plugin-flurry/
  - HockeyApp: https://v-play.net/doc/plugin-hockeyapp/
  - Facebook: https://v-play.net/doc/plugin-facebook/
  - OneSignal: https://v-play.net/doc/plugin-onesignal/
  - Google Cloud Messaging: https://v-play.net/doc/plugin-gcm/
  - Local Notifications: https://v-play.net/doc/plugin-notification/
  - Firebase: https://v-play.net/doc/plugin-firebase/

  To open the documentation of a plugin item in Qt Creator, place your cursor on the item in your QML code and press F1.
  This allows to view the properties, methods and signals of V-Play Plugins directly in Qt Creator.

/////////////////////////////////////*/

App {
    // You get free licenseKeys from http://v-play.net/licenseKey
    // With a licenseKey you can:
    //  * Publish your games & apps for the app stores
    //  * Remove the V-Play Splash Screen or set a custom one (available with the Pro Licenses)
    //  * Add plugins to monetize, analyze & improve your apps (available with the Pro Licenses)
    //licenseKey: "<generate one from http://v-play.net/licenseKey>"

    // This project contains sample integrations of all selected plugins
    // To use and configure the plugins, please have a look at
    // - Plugin Integration guide of used plugins (https://v-play.net/plugins)
    // - The plugin configuration properties in Constants.qml (qml/common folder)
    // - The plugin QML pages in this project (qml/pages folder)
    // NOTE: Some plugins items within the pages are commented in the QML code, as they require more configuration to be runnable / testable

    // keep only one instance of these plugin-pages alive within app
    // this prevents crashes due to destruction of plugin items when popping pages from the stack
    property alias soomlaPage: soomlaPage
    property alias facebookPage: facebookPage
    property alias notificationPage: notificationPage
    property alias firebasePage: firebasePage

    SoomlaPage {
        id: soomlaPage
        visible: false
        onPushed: soomlaPage.listView.contentY = soomlaPage.listView.originY
        onPopped: { soomlaPage.parent = pluginMainItem; visible = false }
    }

    FacebookPage {
        id: facebookPage
        visible: false
        onPopped: { facebookPage.parent = pluginMainItem; visible = false }
    }

    LocalNotificationPage {
        id: notificationPage
        visible: false
        onPopped: { notificationPage.parent = pluginMainItem; visible = false }
    }

    FirebasePage {
        id: firebasePage
        visible: false
        onPopped:  { firebasePage.parent = pluginMainItem; visible = false }
    }

    // app content with plugin list
    NavigationStack {
        id: pluginMainItem

        // initial page contains list if plugins and opens pages for each plugin when selected
        ListPage {
            id: page
            title: qsTr("V-Play Plugins")

            model: ListModel {
                ListElement { type: "Advertising"; name: "AdMob";
                    detailText: "Ad Monetization and Promotion"; image: "../assets/logo-admob.png" }
                ListElement { type: "Advertising"; name: "Chartboost"
                    detailText: "Ad Monetization and Promotion"; image: "../assets/logo-chartboost.png" }
                ListElement { type: "In-App Purchases"; name: "Soomla"
                    detailText: "In-App Purchases & Virtual Currency"; image: "../assets/logo-soomla.png" }
                ListElement { type: "Social"; name: "Facebook"
                    detailText: "Social Sharing & Friend Invites"; image: "../assets/logo-facebook.png" }
                ListElement { type: "Analytics"; name: "Google Analytics"
                    detailText: "App Analytics & Events"; image: "../assets/logo-ga.png" }
                ListElement { type: "Analytics"; name: "Flurry"
                    detailText: "User Analytics & App Statistics"; image: "../assets/logo-flurry.png" }
                ListElement { type: "Notifications"; name: "Google Cloud Messaging Push Notifications"
                    detailText: "Targeted Push Notifications"; image: "../assets/logo-gcm.png" }
                ListElement { type: "Notifications"; name: "OneSignal Push Notifications"
                    detailText: "Targeted Push Notifications"; image: "../assets/logo-onesignal.png" }
                ListElement { type: "Notifications"; name: "Local Notifications"
                    detailText: "Schedule Local Notifications"; image: "../assets/logo-localpush.png" }
                ListElement { type: "Beta Testing & Crash Reporting"; name: "HockeyApp"
                    detailText: "Beta Distribution & Crash Reports"; image: "../assets/logo-hockey.png" }
                ListElement { type: "Database & Authentication"; name: "Firebase"
                    detailText: "Manage users and use Realtime Database"; image: "../assets/logo-firebase.png" }
            }

            delegate: PluginListItem {
                visible: name !== "GameCenter" || Theme.isIos

                onSelected: {
                    switch (name) {
                    case "AdMob":
                        page.navigationStack.push(Qt.resolvedUrl("pages/AdMobPage.qml"))
                        break
                    case "Chartboost":
                        page.navigationStack.push(Qt.resolvedUrl("pages/ChartboostPage.qml"))
                        break
                    case "Soomla":
                        page.navigationStack.push(soomlaPage)
                        break
                    case "Facebook":
                        page.navigationStack.push(facebookPage)
                        break
                    case "Google Analytics":
                        page.navigationStack.push(Qt.resolvedUrl("pages/GoogleAnalyticsPage.qml"))
                        break
                    case "Flurry":
                        page.navigationStack.push(Qt.resolvedUrl("pages/FlurryPage.qml"))
                        break
                    case "Google Cloud Messaging Push Notifications":
                        page.navigationStack.push(Qt.resolvedUrl("pages/GoogleCloudMessagingPage.qml"))
                        break
                    case "OneSignal Push Notifications":
                        page.navigationStack.push(Qt.resolvedUrl("pages/OneSignalPage.qml"))
                        break
                    case "Local Notifications":
                        page.navigationStack.push(notificationPage)
                        break
                    case "HockeyApp":
                        page.navigationStack.push(Qt.resolvedUrl("pages/HockeyAppPage.qml"))
                        break
                    case "Firebase":
                        page.navigationStack.push(firebasePage)
                        break
                    }
                }
            }

            section.property: "type"
            section.delegate: SimpleSection { }
        }
    }
}
