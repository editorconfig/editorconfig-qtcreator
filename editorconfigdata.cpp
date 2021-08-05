/*
 *  Copyright 2021 Herbert Graeber
 */

#include "editorconfigdata.h"

#include <editorconfig/editorconfig.h>

#include "app/app_version.h"
#include <coreplugin/messagemanager.h>

#include <QtCore/QByteArray>

using namespace EditorConfig;

EditorConfigData::EditorConfigData(const QString &name, QObject *parent) :
    QObject(parent), file_name(name)
{
    QByteArray nativeName = QFile::encodeName(name);
    editorconfig_handle handle = editorconfig_handle_init();
    int ret = editorconfig_parse(nativeName.data(), handle);
    if (ret == 0) {
        int count = editorconfig_handle_get_name_value_count(handle);

        for (int i = 0; i < count; i++) {
            const char *name;
            const char *value;

            editorconfig_handle_get_name_value(handle, i, &name, &value);

            m_data.insert(name, value);
        }
        editorconfig_handle_destroy(handle);
    }
    else if (ret > 0) {
#if IDE_VERSION_MAJOR >= 5 || IDE_VERSION_MAJOR == 4 && IDE_VERSION_MINOR >= 15
		Core::MessageManager::writeFlashing(
            QString::fromUtf8("editorconfig: Parse error in file \"%1\", line %2")
				.arg(QString::fromUtf8(editorconfig_handle_get_err_file(handle))).arg(ret));
#else
        Core::MessageManager::write(
            QString::fromUtf8("editorconfig: Parse error in file \"%1\", line %2")
                .arg(QString::fromUtf8(editorconfig_handle_get_err_file(handle))).arg(ret),
            Core::MessageManager::Flash);

#endif
    }
    else {
#if IDE_VERSION_MAJOR >= 5 || IDE_VERSION_MAJOR == 4 && IDE_VERSION_MINOR >= 15
		Core::MessageManager::writeFlashing(
            QString::fromUtf8("editorconfig: %1")
				.arg(QString::fromUtf8(editorconfig_get_error_msg(ret))));
    }
#else
        Core::MessageManager::writeFlashing(
            QString::fromUtf8("editorconfig: %1")
                .arg(QString::fromUtf8(editorconfig_get_error_msg(ret)))
            Core::MessageManager::Flash);

#endif
}

bool EditorConfigData::overrideTabSettings(TextEditor::TabSettings &tabSettings) const {
    bool changed = false;

    QByteArray value;
    bool ok;

    value = m_data["tab_width"];
    int tabSize = value.toInt(&ok);
    if (ok && tabSize > 0 && tabSettings.m_tabSize != tabSize) {
        message(tr("override tab width with %1").arg(tabSize));
        tabSettings.m_tabSize = tabSize;
        changed = true;
    }

    value = m_data["indent_size"];
    int indentSize = value.toInt(&ok);
    if (ok && indentSize > 0 && tabSettings.m_indentSize != indentSize) {
        message(tr("override indent size with %1").arg(indentSize));
        tabSettings.m_indentSize = indentSize;
        changed = true;
    }

    value = m_data["indent_style"];
    if (value == "tab") {
        if (tabSettings.m_tabPolicy != TextEditor::TabSettings::TabsOnlyTabPolicy) {
            message(tr("override indent style with 'tab'"));
            tabSettings.m_tabPolicy = TextEditor::TabSettings::TabsOnlyTabPolicy;
            changed = true;
        }
    }
    else if (value == "space") {
        if (tabSettings.m_tabPolicy != TextEditor::TabSettings::SpacesOnlyTabPolicy) {
            message(tr("override indent style with 'space'"));
            tabSettings.m_tabPolicy = TextEditor::TabSettings::SpacesOnlyTabPolicy;
            changed = true;
        }
    }

    return changed;
}

bool EditorConfigData::overrideStorageSettings(TextEditor::StorageSettings &storageSettings) const {
    bool changed = false;

    QByteArray value;

    value = m_data["insert_final_newline"];
    if (value == "true" && !storageSettings.m_addFinalNewLine) {
        message(tr("override add final newline with 'true'"));
        storageSettings.m_addFinalNewLine = true;
        changed = true;
    }
    else if (value == "false" && storageSettings.m_addFinalNewLine) {
        message(tr("override add final newline with 'false'"));
        storageSettings.m_addFinalNewLine = false;
        changed = true;
    }

    value = m_data["trim_trailing_whitespace"];
    if (value == "true" && !storageSettings.m_cleanWhitespace) {
        message(tr("override trim trailing whitespace with 'true'"));
        storageSettings.m_cleanWhitespace = true;
        changed = true;
    }
    else if (value == "false" && storageSettings.m_cleanWhitespace) {
        message(tr("override trim trailing whitespace with 'false'"));
        storageSettings.m_cleanWhitespace = false;
        changed = true;
    }

    return changed;
}

bool EditorConfigData::overrideCodec(const QTextCodec *&codec) const {
    bool changed = false;

    QByteArray value = m_data["charset"];
    QTextCodec *newCodec = QTextCodec::codecForName(value);
    if (newCodec && codec != newCodec) {
        message(tr("override charset with '%1'").arg(QString::fromLatin1(newCodec->name())));
        codec = newCodec;
        changed = true;
    }

    return changed;
}

void EditorConfigData::message(const QString &msg) const {
#if IDE_VERSION_MAJOR >= 5 || IDE_VERSION_MAJOR == 4 && IDE_VERSION_MINOR >= 15
	Core::MessageManager::writeSilently(QStringLiteral("%1: %2").arg(file_name, msg));
#else
    Core::MessageManager::write(QStringLiteral("%1: %2").arg(file_name, msg), Core::MessageManager::Silent);
#endif
}
