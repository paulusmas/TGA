/*
 *  Copyleft (C) 2018, Pavel Masny
 *  This file is part of the TGA SDK (TGASdk).
 */

#pragma once
#ifndef _TGA_EXPORTS_
#define _TGA_EXPORTS_

#define TGA_DLL_EXPORT __declspec(dllexport)
#define TGA_DLL_IMPORT __declspec(dllimport)

#define TGA_STATIC_EXPORT
#define TGA_STATIC_IMPORT TGA_DLL_IMPORT

#ifdef TGA_EXPORTS
#define TGA_EXPORT        TGA_DLL_EXPORT
#define TGA_EXPORT_STATIC TGA_STATIC_EXPORT
#else
#define TGA_EXPORT        TGA_DLL_IMPORT
#define TGA_EXPORT_STATIC TGA_STATIC_IMPORT
#endif

#endif
