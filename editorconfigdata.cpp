/*
 *  Copyright 2016 Herbert Graeber
 */

#include "editorconfigdata.h"

#include <editorconfig/editorconfig.h>

#include <QtDebug>
#include <QtCore/QByteArray>

EditorConfigData::EditorConfigData(const Utils::FileName &name) {
    QByteArray nativeName = QFile::encodeName(name.toString());
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
    }
}

bool EditorConfigData::overrideTabSettings(TextEditor::TabSettings &tabSettings) const {
    bool changed = false;

    QByteArray value;
    bool ok;

    value = m_data["tab_width"];
    int tabSize = value.toInt(&ok);
    if (ok && tabSize > 0 && tabSettings.m_tabSize != tabSize) {
        qDebug() << "EditorConfig: override tab width with" << tabSize;
        tabSettings.m_tabSize = tabSize;
        ++changed;
    }

    value = m_data["indent_size"];
    int indentSize = value.toInt(&ok);
    if (ok && indentSize > 0 && tabSettings.m_indentSize != indentSize) {
        qDebug() << "EditorConfig: override indent size with" << indentSize;
        tabSettings.m_indentSize = indentSize;
        ++changed;
    }

    value = m_data["indent_style"];
    if (value == "tab") {
        if (tabSettings.m_tabPolicy != TextEditor::TabSettings::TabsOnlyTabPolicy) {
            qDebug() << "EditorConfig: override indent style with TabsOnlyTabPolicy";
            tabSettings.m_tabPolicy = TextEditor::TabSettings::TabsOnlyTabPolicy;
            ++changed;
        }
    }
    else if (value == "space") {
        if (tabSettings.m_tabPolicy != TextEditor::TabSettings::SpacesOnlyTabPolicy) {
            qDebug() << "EditorConfig: override indent style with SpacesOnlyTabPolicy";
            tabSettings.m_tabPolicy = TextEditor::TabSettings::SpacesOnlyTabPolicy;
            ++changed;
        }
    }

    return changed;
}

bool EditorConfigData::overrideStorageSettings(TextEditor::StorageSettings &storageSettings) const {
    bool changed = false;

    QByteArray value;

    value = m_data["insert_final_newline"];
    if (value == "true" && !storageSettings.m_addFinalNewLine) {
        qDebug() << "EditorConfig: override add final newline with true";
        storageSettings.m_addFinalNewLine = true;
        ++changed;
    }
    else if (value == "false" && storageSettings.m_addFinalNewLine) {
        qDebug() << "EditorConfig: override add final newline with false";
        storageSettings.m_addFinalNewLine = false;
        ++changed;
    }

    value = m_data["trim_trailing_whitespace"];
    if (value == "true" && !storageSettings.m_cleanWhitespace) {
        qDebug() << "EditorConfig: override trim trailing whitespace with true";
        storageSettings.m_cleanWhitespace = true;
        ++changed;
    }
    else if (value == "false" && storageSettings.m_cleanWhitespace) {
        qDebug() << "EditorConfig: override trim trailing whitespace with false";
        storageSettings.m_cleanWhitespace = false;
        ++changed;
    }

    return changed;
}

bool EditorConfigData::overrideCodec(const QTextCodec *&codec) const {
    bool changed = false;

    QByteArray value = m_data["charset"];
    QTextCodec *newCodec = QTextCodec::codecForName(value);
    if (newCodec && codec != newCodec) {
        codec = newCodec;
        ++changed;
    }

    return changed;
}
