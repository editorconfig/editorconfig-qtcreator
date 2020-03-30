/*
 *  Copyright 2017 Herbert Graeber
 */

#include "editorconfigwizarddialog.h"

#include "editorconfigwizard.h"
#include "editorconfigwizardpage.h"

#include "editorconfiglogging.h"


using namespace EditorConfig;
using namespace Internal;

EditorConfigDialog::EditorConfigDialog(const EditorConfigWizard *factory, QWidget *parent) :
    Core::BaseFileWizard(factory, QVariantMap(), parent)
{
    qCDebug(editorConfigLog) << "EditorConfigDialog::EditorConfigDialog";

    setWindowTitle(tr("Editorconfig File"));

    m_editorConfigPage = new EditorConfigPage(this);
    setPage(0, m_editorConfigPage);

    foreach (QWizardPage *p, extensionPages())
        addPage(p);
}

QString EditorConfigDialog::path() const {
    return m_editorConfigPage->path();
}

void EditorConfigDialog::setPath(const QString &path) {
    m_editorConfigPage->setPath(path);
}

bool EditorConfigDialog::validateCurrentPage()
{
    return QWizard::validateCurrentPage();
}


