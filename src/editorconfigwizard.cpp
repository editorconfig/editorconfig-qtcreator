/*
 *  Copyright 2016,2017 Herbert Graeber
 */
#include "editorconfigwizard.h"

#include "editorconfigwizarddialog.h"

#include "editorconfigconstants.h"
#include "editorconfiglogging.h"

#include <projectexplorer/project.h>
#include <projectexplorer/projecttree.h>
#include <projectexplorer/editorconfiguration.h>
#include <texteditor/tabsettings.h>
#include <texteditor/icodestylepreferences.h>
#include <texteditor/storagesettings.h>
#include <texteditor/extraencodingsettings.h>
#include <cpptools/cpptoolsconstants.h>
#include <qmljstools/qmljstoolsconstants.h>

#include <QString>
#include <QTextStream>
#include <QTextCodec>

using namespace EditorConfig;
using namespace Internal;

EditorConfigWizard::EditorConfigWizard() {
    qCDebug(editorConfigLog) << "EditorConfigWizard::EditorConfigWizard";

    setId("Z.EditorConfig");
    setCategory(QLatin1String(Constants::WIZARD_CATEGORY));
    setDisplayCategory(QLatin1String(Constants::WIZARD_CATEGORY_DISPLAY));
    setDisplayName(tr("Editorconfig File"));
    setDescription(tr("Creates an initial editorconfig file derived from the current "
                      "C++, Qml and generic files settings."));
    setFlags(Core::IWizardFactory::PlatformIndependent);
}

Core::BaseFileWizard *EditorConfigWizard::create(QWidget *parent, const Core::WizardDialogParameters &parameters) const {
    EditorConfigDialog *wizardDialog = new EditorConfigDialog(this, parent);
    wizardDialog->setPath(parameters.defaultPath());
    return wizardDialog;
}

Core::GeneratedFiles EditorConfigWizard::generateFiles(const QWizard *w, QString *errorMessage) const {
    Q_UNUSED(errorMessage);

    const EditorConfigDialog *wizardDialog = qobject_cast<const EditorConfigDialog *>(w);

    const QString editorConfigFileName = buildFileName(wizardDialog->path(), QString(), QString::fromUtf8("editorconfig"));

    // UI
    Core::GeneratedFile editorConfigFile(editorConfigFileName);

    if (ProjectExplorer::ProjectTree *projectTree = ProjectExplorer::ProjectTree::instance()) {
        if (ProjectExplorer::Project *project = projectTree->currentProject()) {
            QString contents;
            QTextStream stream(&contents, QIODevice::WriteOnly);
            createEditorConfigFile(stream, project);
            stream.flush();

            editorConfigFile.setContents(contents);
            editorConfigFile.setAttributes(Core::GeneratedFile::OpenEditorAttribute);
        }
    }

    return { editorConfigFile };
}

void EditorConfigWizard::createEditorConfigFileSection(QTextStream &stream,
    TextEditor::ICodeStylePreferences *stylePreferences) const
{
    if (stylePreferences) {
        TextEditor::TabSettings tabSettings = stylePreferences->tabSettings();

        stream << "indent_size = " << tabSettings.m_indentSize << "\n";
        stream << "tab_width = " << tabSettings.m_tabSize << "\n";
        if (tabSettings.m_tabPolicy == TextEditor::TabSettings::TabsOnlyTabPolicy)
           stream << "indent_style = tab\n";
        else if (tabSettings.m_tabPolicy == TextEditor::TabSettings::SpacesOnlyTabPolicy)
           stream << "indent_style = spaces\n";
    }
}

void EditorConfigWizard::createEditorConfigFile(QTextStream &stream,
    ProjectExplorer::Project *project) const
{
    ProjectExplorer::EditorConfiguration *editorConfiguration = project->editorConfiguration();

    stream << "root = true\n";
    stream << "\n";

    stream << "[*.{h,hpp,hxx,c,cpp,cxx}{,.in}]\n";
    createEditorConfigFileSection(stream,
        editorConfiguration->codeStyle(CppTools::Constants::CPP_SETTINGS_ID));
    stream << "\n";

    stream << "[*{.js,.qml}{,.in}]\n";
    createEditorConfigFileSection(stream,
        editorConfiguration->codeStyle(QmlJSTools::Constants::QML_JS_SETTINGS_ID));
    stream << "\n";

    stream << "[*]\n";
    createEditorConfigFileSection(stream, editorConfiguration->codeStyle());
    TextEditor::StorageSettings storageSettings = editorConfiguration->storageSettings();
    stream << "insert_final_newline = " << storageSettings.m_addFinalNewLine << "\n";
    stream << "trim_trailing_whitespace = " << storageSettings.m_cleanWhitespace << "\n";
    if (QTextCodec *codec = editorConfiguration->textCodec()) {
        stream << "charset = " << codec->name() << "\n";
    }
}
