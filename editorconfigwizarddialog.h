/*
 *  Copyright 2021 Herbert Graeber
 */
#ifndef EDITORCONFIGWIZARDDIALOG_H
#define EDITORCONFIGWIZARDDIALOG_H

#include <coreplugin/basefilewizard.h>

namespace EditorConfig {

class EditorConfigWizard;
class EditorConfigPage;

class EditorConfigDialog : public Core::BaseFileWizard {
    Q_OBJECT
public:
    EditorConfigDialog(const EditorConfigWizard *factory, QWidget *parent);

    QString path() const;
    void setPath(const QString &);

    bool validateCurrentPage();

private:
    EditorConfigPage *m_editorConfigPage;
};

}

#endif // EDITORCONFIGWIZARDDIALOG_H
