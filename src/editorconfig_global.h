/*
 *  Copyright 2016 Herbert Graeber
 */

#ifndef EDITORCONFIG_GLOBAL_H
#define EDITORCONFIG_GLOBAL_H

#include <QtGlobal>

#if defined(EDITORCONFIG_LIBRARY)
#  define EDITORCONFIGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define EDITORCONFIGSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif
