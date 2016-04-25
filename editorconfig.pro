#
#   Copyright 2016 Herbert Graeber
#

DEFINES += EDITORCONFIG_LIBRARY

# EditorConfig files

SOURCES += editorconfigplugin.cpp \
    editorconfigdata.cpp

HEADERS += editorconfigplugin.h \
    editorconfig_global.h \
    editorconfigdata.h

# Qt Creator linking

isEmpty(QTCREATOR_SOURCES) QTCREATOR_SOURCES = $$(QTC_SOURCE)
isEmpty(IDE_BUILD_TREE) IDE_BUILD_TREE = $$(QTC_BUILD)

LIBS += -leditorconfig

###### If the plugin can be depended upon by other plugins, this code needs to be outsourced to
###### <dirname>_dependencies.pri, where <dirname> is the name of the directory containing the
###### plugin's sources.

QTC_PLUGIN_NAME = EditorConfig
QTC_LIB_DEPENDS += \
    # nothing here at this time

QTC_PLUGIN_DEPENDS += \
    coreplugin \
    texteditor

QTC_PLUGIN_RECOMMENDS += \
    # optional plugin dependencies. nothing here at this time

###### End _dependencies.pri contents ######

include($$QTCREATOR_SOURCES/src/qtcreatorplugin.pri)

DISTFILES += \
    README.md \
    .editorconfig
