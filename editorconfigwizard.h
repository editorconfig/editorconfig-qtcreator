/*
 *  Copyright 2016,2017 Herbert Graeber
 */
#ifndef EDITORCONFIGWIZARD_H
#define EDITORCONFIGWIZARD_H

#include <coreplugin/basefilewizardfactory.h>

namespace ProjectExplorer {
    class Project;
}

namespace TextEditor {
    class ICodeStylePreferences;
}

class QTextStream;

namespace EditorConfig {

class EditorConfigWizard : public Core::BaseFileWizardFactory {
    Q_OBJECT
public:
    EditorConfigWizard();

    virtual Core::BaseFileWizard *create(QWidget *parent, const Core::WizardDialogParameters &parameters) const;
    virtual Core::GeneratedFiles generateFiles(const QWizard *w, QString *errorMessage) const;

private:
    void createEditorConfigFileSection(QTextStream &stream, TextEditor::ICodeStylePreferences *stylePreferences) const;
    void createEditorConfigFile(QTextStream &stream, ProjectExplorer::Project *project) const;
};

}

#endif // EDITORCONFIGWIZARD_H
