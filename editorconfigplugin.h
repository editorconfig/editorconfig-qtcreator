/*
 *  Copyright 2016 Herbert Graeber
 */

#ifndef EDITORCONFIG_H
#define EDITORCONFIG_H

#include "editorconfig_global.h"

#include <extensionsystem/iplugin.h>
#include <coreplugin/editormanager/ieditor.h>
#include <texteditor/texteditor.h>
#include <texteditor/textdocument.h>

#include <QtCore/QMultiMap>
#include <QtCore/QSet>
#include <QtCore/QMetaObject>

namespace EditorConfig {
namespace Internal {

class EditorConfigPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "EditorConfig.json")

public:
    EditorConfigPlugin();
    ~EditorConfigPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private slots:
    void editorCreated(Core::IEditor *, const QString &);
    void overrideSettings(TextEditor::TextDocument *textDocument);
    void tabSettingsChanged();
    void editorAboutToClose(Core::IEditor *editor);

private:
    QMap<TextEditor::TextDocument *, QMetaObject::Connection> documents;
    QSet<TextEditor::TextDocument *> changingDocuments;
};

}
}

#endif
