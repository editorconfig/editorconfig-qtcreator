#
# Copyright 2021 Herbert Graeber
#
cmake_minimum_required(VERSION 3.10)

project(Editorconfig LANGUAGES CXX VERSION 0.3.6)

find_package(QtCreator REQUIRED)
find_package(EditorConfig 0.12 REQUIRED)
find_package(KF5SyntaxHighlighting)

add_qtc_plugin(EditorConfig
  PLUGIN_DEPENDS QtCreator::Core QtCreator::ProjectExplorer QtCreator::TextEditor
  DEPENDS editorconfig_shared KF5::SyntaxHighlighting
  PROPERTIES
    AUTOMOC On
    AUTOUIC On
    AUTORCC On
  SOURCES
    editorconfigconstants.h
    editorconfigdata.h editorconfigdata.cpp
    editorconfig_global.h
    editorconfiglogging.h editorconfiglogging.cpp
    editorconfigpage.ui
    editorconfigplugin.h editorconfigplugin.cpp
    editorconfigwizard.cpp
    editorconfigwizarddialog.h editorconfigwizarddialog.cpp
    editorconfigwizard.h
    editorconfigwizardpage.h editorconfigwizardpage.cpp
)
