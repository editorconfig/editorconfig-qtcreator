add_qtc_plugin(EditorConfig
  DEPENDS editorconfig
  PLUGIN_DEPENDS Core TextEditor ProjectExplorer
  SOURCES
    editorconfig_global.h editorconfigconstants.h
    editorconfigplugin.cpp editorconfigplugin.h
    editorconfigdata.cpp editorconfigdata.h
    editorconfiglogging.cpp editorconfiglogging.h
    editorconfigwizard.cpp editorconfigwizard.h
    editorconfigwizardpage.cpp editorconfigwizardpage.h
    editorconfigwizarddialog.cpp editorconfigwizarddialog.h
    editorconfigpage.ui
    editorconfig_de.ts editorconfig_it.ts
)
