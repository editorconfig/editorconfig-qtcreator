cmake_minimum_required(VERSION 3.13)

set(CMAKE_USE_RELATIVE_PATHS ON)
set(BUILD_SHARED_LIBS ON)

project("EditorConfig-QtCreator-plugin")

set(CXX_STANDARD 20)
#set(CMAKE_AUTOMOC ON)

set("QTC_SOURCE" "${CMAKE_SOURCE_DIR}/qtcreator" CACHE PATH "Qt Creator sources dir")
set("QTC_SOURCE_SRC" "${QTC_SOURCE}/src")
set("QTC_PLUGINS_SOURCE" "${QTC_SOURCE_SRC}/plugins")
set("QTC_LIBS_SOURCE" "${QTC_SOURCE_SRC}/libs")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake" "${QTC_SOURCE}/cmake")
include(Hardening)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)

set(src_DIR "${CMAKE_SOURCE_DIR}/src")
set(translations_DIR "${CMAKE_SOURCE_DIR}/src")

file(GLOB_RECURSE SRC_FILES "${src_DIR}/*.c" "${src_DIR}/*.cpp")
file(GLOB_RECURSE UI_FILES "${src_DIR}/*.ui")
file(GLOB_RECURSE transl_files "${translations_DIR}/*.ts")


include(GNUInstallDirs)
include(CPackComponent)
set(QT_CREATOR_LIB_DIR "${CMAKE_INSTALL_FULL_LIBDIR}/qtcreator")
set(QT_CREATOR_PLUGINS_ROOT "${QT_CREATOR_LIB_DIR}/plugins")
message(STATUS "QT_CREATOR_PLUGINS_ROOT ${QT_CREATOR_PLUGINS_ROOT}")

include(QtCreatorAPI)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(plugins_deps_libs Core ProjectExplorer TextEditor)


add_qtc_plugin(EditorConfig
DEPENDS Qt5::Core Qt5::Widgets
# works only with co-built plugins
#PLUGIN_DEPENDS 
SOURCES
	${SRC_FILES}
	${UI_FILES}
DEFINES
	EDITORCONFIG_LIBRARY
#doesn't work, use target_link_libraries
#PUBLIC_LIBRARIES
	#editorconfig
	#${plugins_deps_libs}

# doesn't work, use CMAKE_AUTOMOC and CMAKE_AUTOUIC
#ENABLE_AUTOGEN_TOOLS
#	moc
#	uic
TRANSLATIONS
	${transl_files}
)

set_target_properties(EditorConfig PROPERTIES
	_arg_DEPENDS Core ProjectExplorer TextEditor
)
target_include_directories(EditorConfig PRIVATE "${QTC_PLUGINS_SOURCE}" "${QTC_LIBS_SOURCE}")
target_link_directories(EditorConfig PRIVATE ${QT_CREATOR_PLUGINS_ROOT})
target_link_libraries(EditorConfig PRIVATE editorconfig ${plugins_deps_libs})
harden(EditorConfig)

# Workaround. CPack toolchain installs plugins, but it is the same dir where it builds it. We need to install to dirs writable as root and not to harm the system. So we create a component and package only it.
install(TARGETS "EditorConfig"
	LIBRARY DESTINATION "${QT_CREATOR_PLUGINS_ROOT}"
	COMPONENT plugin
)
set(CMAKE_INSTALL_DEFAULT_COMPONENT_NAME "plugin")
set(CPACK_COMPONENTS_ALL "${CMAKE_INSTALL_DEFAULT_COMPONENT_NAME}")
set(CPACK_PACKAGE_NAME "qtcreator-plugin-editorconfig")

foreach(gen DEBIAN RPM NUGET FREEBSD)
	set(CPACK_${gen}_PLUGIN_PACKAGE_NAME "${CPACK_PACKAGE_NAME}")
endforeach()

set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED OFF)
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN OFF)

set(CPACK_PACKAGE_VENDOR "Herbert Graeber")

set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/CPack.description.txt")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/editorconfig/editorconfig-qtcreator")
set(CPACK_HELP_LINK "https://github.com/editorconfig/editorconfig-qtcreator")
set(CPACK_PACKAGE_CONTACT "${CPACK_PACKAGE_HOMEPAGE_URL}")
set(CPACK_PACKAGE_CHECKSUM "SHA512")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.LGPLv3")

set(CPACK_DEBIAN_COMPRESSION_TYPE "xz")
set(CPACK_RPM_COMPRESSION_TYPE "xz")
set(CPACK_NSIS_COMPRESSOR "/SOLID lzma")
set(CPACK_DEBIAN_DEBUGINFO_PACKAGE ON)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_RPM_PACKAGE_AUTOREQ ON)

set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "3")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
set(CPACK_RPM_COMPONENT_INSTALL ON)
set(CPACK_DEB_COMPONENT_INSTALL ON)

include(CPack)