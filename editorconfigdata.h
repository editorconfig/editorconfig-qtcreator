/*
 *  Copyright 2016 Herbert Graeber
 */

#ifndef EDITORCONFIGDATA_H
#define EDITORCONFIGDATA_H

#include <texteditor/tabsettings.h>
#include <texteditor/storagesettings.h>
#include <utils/fileutils.h>

#include <QtCore/QMap>
#include <QtCore/QTextCodec>

class EditorConfigData {
public:
    EditorConfigData(const Utils::FileName &);

    bool overrideTabSettings(TextEditor::TabSettings &tabSettings) const;
    bool overrideStorageSettings(TextEditor::StorageSettings &storageSettings) const;
    bool overrideCodec(const QTextCodec *&codec) const;

private:
    QMap<QByteArray, QByteArray> m_data;
};

#endif
