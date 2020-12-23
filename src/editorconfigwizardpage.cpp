/*
 *  Copyright 2017 Herbert Graeber
 */

#include "editorconfigwizardpage.h"

#include "ui_editorconfigpage.h"

#include "editorconfiglogging.h"

#include <utils/wizard.h>
#include <projectexplorer/toolchainmanager.h>

#include <QMap>


using namespace EditorConfig;
using namespace Internal;
using namespace ProjectExplorer;

EditorConfigPage::EditorConfigPage(QWidget *parent) :
    Utils::WizardPage(parent), ui(new Ui_EditorConfigPage)
{
    qCDebug(editorConfigLog) << "EditorConfigPage::EditorConfigPage";

    ui->setupUi(this);

    setProperty(Utils::SHORT_TITLE_PROPERTY, tr("Editorconfig Details"));
}

QString EditorConfigPage::path() const {
    return m_path;
}

void EditorConfigPage::setPath(const QString &path) {
    m_path = path;
    ui->path->setText(path);
}

