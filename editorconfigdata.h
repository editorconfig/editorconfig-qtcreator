/*
 *  Copyright 2016 Herbert Graeber
 */

#ifndef EDITORCONFIGDATA_H
#define EDITORCONFIGDATA_H

#include <texteditor/tabsettings.h>
#include <texteditor/storagesettings.h>
#include <utils/fileutils.h>

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QTextCodec>

class EditorConfigData : QObject {
    Q_OBJECT
public:
    EditorConfigData(const Utils::FileName &, QObject *parent = 0);

    bool overrideTabSettings(TextEditor::TabSettings &tabSettings) const;
    bool overrideStorageSettings(TextEditor::StorageSettings &storageSettings) const;
    bool overrideCodec(const QTextCodec *&codec) const;

private:
    void message(const QString &msg) const;

    QString file_name;
    QMap<QByteArray, QByteArray> m_data;
};

#endif
