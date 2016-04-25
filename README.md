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
http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.\"

## Installation

Requirements:

- QtCreator source and build folders
- editorconfig-core-c

The environment variables @QTC_SOURCE@ must contain the path to qt-creators
source, @QTC_BUILD@ to it's build folder. Now run

    mkdir build
    cd  build
    qmake ../editorconfig.pro
    make
    make install

## Supported properties

The EditorConfig QtCreator plugin supports the following EditorConfig properties:

- charset
- indent_style
- indent_size
- tab_width
- trim_trailing_whitespace
- insert_final_newline
