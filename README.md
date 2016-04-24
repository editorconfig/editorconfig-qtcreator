# EditorConfig QtCreator Plugin

This is an EditorConfig plugin for Qt-Creator. It has no real user
interface and simply overrides all settings of text documents with
a matching entry in an .editorconfig file. QtCreators own settings
will be ignored for concernd files.

## License

This plugins is licensed under the LGPLv3. The license only restricts the
plugin itself. The data produced by the plugin is property of the plugin
user.

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
