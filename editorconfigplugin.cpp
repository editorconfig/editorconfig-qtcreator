/*
 *  Copyright 2016,2017 Herbert Graeber
 */

#include "editorconfigplugin.h"

#include "editorconfigdata.h"
#include "editorconfiglogging.h"
#include "editorconfigwizard.h"

#include <coreplugin/icore.h>
#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/idocument.h>
#include <coreplugin/iwizardfactory.h>
#include <texteditor/textdocument.h>
#include <extensionsystem/pluginmanager.h>

#include <QtPlugin>
#include <QtDebug>
#include <QApplication>

using namespace EditorConfig::Internal;

EditorConfigPlugin::EditorConfigPlugin()
{
}

EditorConfigPlugin::~EditorConfigPlugin()
{
}

bool EditorConfigPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    if (translator.load(QLatin1String("editorconfig")))
        QApplication::instance()->installTranslator(&translator);

    Core::IWizardFactory::registerFactoryCreator([] {
        return QList<Core::IWizardFactory *> {
            new EditorConfigWizard
        };
    });

    if (Core::EditorManager *editorManager = Core::EditorManager::instance()) {
        connect(editorManager, SIGNAL(editorCreated(Core::IEditor*,QString)), SLOT(editorCreated(Core::IEditor*,QString)));
        connect(editorManager, SIGNAL(editorAboutToClose(Core::IEditor*)), SLOT(editorAboutToClose(Core::IEditor*)));
    }

    return true;
}

void EditorConfigPlugin::extensionsInitialized()
{
}

ExtensionSystem::IPlugin::ShutdownFlag EditorConfigPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}

void EditorConfigPlugin::editorCreated(Core::IEditor *editor, const QString &name) {
    qCDebug(editorConfigLog) << "EditorConfig: created editor" << name;

    if (TextEditor::BaseTextEditor *textEditor = qobject_cast<TextEditor::BaseTextEditor *>(editor)) {
        if (TextEditor::TextDocument *textDocument = textEditor->textDocument()) {
            documents.insert(
                textDocument,
                connect(textDocument, &TextEditor::TextDocument::tabSettingsChanged,
                        this, [=](){ this->overrideSettings(textDocument); }, Qt::QueuedConnection)
            );
            emit textDocument->tabSettingsChanged();
        }
    }
}

void EditorConfigPlugin::overrideSettings(TextEditor::TextDocument *textDocument)
{
    if (!changingDocuments.contains(textDocument)) {
        qCDebug(editorConfigLog) << "EditorConfig: overrideSettings for" << textDocument->filePath();

        EditorConfigData data(textDocument->filePath());

        TextEditor::TabSettings tabSettings = textDocument->tabSettings();
        TextEditor::StorageSettings storageSettings = textDocument->storageSettings();
        const QTextCodec *codec = textDocument->codec();

        changingDocuments.insert(textDocument);

        if (data.overrideTabSettings(tabSettings))
            textDocument->setTabSettings(tabSettings);

        if (data.overrideStorageSettings(storageSettings))
            textDocument->setStorageSettings(storageSettings);

        if (data.overrideCodec(codec))
            textDocument->setCodec(codec);

        changingDocuments.remove(textDocument);
    }
}

void EditorConfigPlugin::tabSettingsChanged()
{
    if (TextEditor::TextDocument *textDocument = qobject_cast<TextEditor::TextDocument *>(sender())) {
        qCDebug(editorConfigLog) << "EditorConfig: tabSettingsChanged" << textDocument->filePath();

        overrideSettings(textDocument);
    }
}

void EditorConfigPlugin::editorAboutToClose(Core::IEditor *editor)
{
    if (TextEditor::BaseTextEditor *textEditor = qobject_cast<TextEditor::BaseTextEditor *>(editor)) {
        if (TextEditor::TextDocument *textDocument = textEditor->textDocument()) {
            qCDebug(editorConfigLog) << "EditorConfig: documentclosed" << textDocument->filePath();

            if (auto connection = documents[textDocument]) {
                textDocument->disconnect(connection);
                documents.remove(textDocument);
            }
        }
    }
}
