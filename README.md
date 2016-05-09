# EditorConfig QtCreator Plugin

This is an EditorConfig plugin for Qt-Creator. It has no real user
interface and simply overrides all settings of text documents with
a matching entry in an .editorconfig file. QtCreators own settings
will be ignored for concernd files.

## License

### Commercial Usage

Licensees holding valid Qt Commercial licenses may use this plugin
in accordance with the Qt Commercial License Agreement provided
with the Software or, alternatively, in accordance with the terms
contained in a written agreement between you and The Qt Company.

### GNU Lesser General Public License Usage

Alternatively, this plugin may be used under the terms of the GNU
Lesser General Public License version 2.1 or version 3 as published
by the Free Software Foundation.  Please review the following
information to ensure the GNU Lesser General Public License
requirements will be met: https://www.gnu.org/licenses/lgpl.html and
http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.

## Installation

### Binaries

A precompiled plugin for QtCreator Windows with statically linked
editorconfig-core-c and pcre can be found
[here](https://github.com/editorconfig/editorconfig-qtcreator/releases/latest).
It has to be unpacked into the Qt folder (Usually `C:\Qt`).

RPMs for openSUSE Leap 42.1 and Tumbleweed are available from the
[openSUSE Build Service](http://download.opensuse.org/repositories/home:/hgraeber:/Qt5/).

### From Source

Requirements:

- QtCreator source and build folders
- editorconfig-core-c
- pcre

The last two are best taken from your linux distribution. For Windows they
usually must be build locally and added to the `INCLUDEPATH` and `LIBS`
variables. Static editorconfig-core-c and pcre libraries are best for easy
deployment of the plugin.

For building plugins you usually have to build QtCreator yourself. For
openSUSE the special libqt5-creator-plusgin-devel RPM provided in the
repository mentioned above caon be used instead.

The environment variables `QTC_SOURCE` shall contain the path to qt-creators
source, `QTC_BUILD` to it's build folder. Now run

    mkdir build
    cd  build
    qmake ../editorconfig.pro
    make
    make install

Instead of using the environment variables you can specify `QTCREATOR_SOURCES`
and `IDE_BUILD_TREE` on the qmake command line.

Additionally you can specify `USE_USER_DESTDIR=yes`, so that the plugin is
installed in the users plugin folder for direct use with the next run of
QtCreator. QtCreator option `-noload EditorConfig` can be used to suppress
the load of the plugin, for the case that something goes wrong.

## Supported properties

The EditorConfig QtCreator plugin supports the following EditorConfig properties:

- charset
- indent_style
- indent_size
- tab_width
- trim_trailing_whitespace
- insert_final_newline
