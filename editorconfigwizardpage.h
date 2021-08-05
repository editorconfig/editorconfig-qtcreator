/*
 *  Copyright 2021 Herbert Graeber
 */
#ifndef EDITORCONFIGWIZARDPAGE_H
#define EDITORCONFIGWIZARDPAGE_H

#include <utils/wizardpage.h>

class Ui_EditorConfigPage;

namespace EditorConfig {

class EditorConfigPage : public Utils::WizardPage {
    Q_OBJECT
public:
    explicit EditorConfigPage(QWidget *parent = nullptr);

    QString path() const;
    void setPath(const QString &);

private:
    QString m_path;

    Ui_EditorConfigPage *ui;
};

}

#endif // EDITORCONFIGWIZARDPAGE_H
