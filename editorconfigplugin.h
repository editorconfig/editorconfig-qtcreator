/*
 *  Copyright 2016,2017 Herbert Graeber
 */

#ifndef EDITORCONFIGPLUGIN_H
#define EDITORCONFIGPLUGIN_H

#include "editorconfig_global.h"

#include <extensionsystem/iplugin.h>
#include <coreplugin/editormanager/ieditor.h>
#include <texteditor/texteditor.h>
#include <texteditor/textdocument.h>

#include <QtCore/QMultiMap>
#include <QtCore/QSet>
#include <QtCore/QMetaObject>
#include <QTranslator>

namespace EditorConfig {
namespace Internal {

class EditorConfigPlugin final : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "EditorConfig.json")

public:
    EditorConfigPlugin() = default;
    ~EditorConfigPlugin() final;

    bool initialize(const QStringList &arguments, QString *errorString) final;
    void extensionsInitialized() final;
    ShutdownFlag aboutToShutdown();

private slots:
    void editorCreated(Core::IEditor *, const QString &);
    void overrideSettings(TextEditor::TextDocument *textDocument);
    void tabSettingsChanged();
    void editorAboutToClose(Core::IEditor *editor);

private:
    QTranslator translator;

    QMap<TextEditor::TextDocument *, QMetaObject::Connection> documents;
    QSet<TextEditor::TextDocument *> changingDocuments;
};

}
}

#endif
