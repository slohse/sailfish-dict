# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = DictQuery

CONFIG += sailfishapp c++11

QT += webkitwidgets

SOURCES += src/DictQuery.cpp \
    src/dictquerycore.cpp \
    src/dictproviders/dictcc.cpp \
    src/dictproviders/singletranslationitem.cpp

OTHER_FILES += qml/DictQuery.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml \
    rpm/DictQuery.changes.in \
    rpm/DictQuery.spec \
    rpm/DictQuery.yaml \
    translations/*.ts \
    DictQuery.desktop \
    $$files(qml/components/*) \
    $$files(qml/delegates/SingleTranslation/*)


# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/DictQuery-de.ts

HEADERS += \
    src/dictquerycore.h \
    src/dictproviders/dictcc.h \
    src/dictproviders/singletranslationitem.h

DISTFILES +=


