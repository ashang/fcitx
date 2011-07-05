/***************************************************************************
 *   Copyright (C) 2002~2005 by Yuking                                     *
 *   yuking_net@sohu.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef _UI_H
#define _UI_H

#include "fcitx/fcitx.h"
#include "fcitx/ui.h"
#include "fcitx-config/fcitx-config.h"
#include "fcitx-utils/utarray.h"

#include <X11/Xlib.h>
#include <cairo.h>
#include "ui/cairostuff/cairostuff.h"

#ifdef _ENABLE_PANGO
#include <pango/pangocairo.h>
#endif

#include "skin.h"
#include <module/x11/x11stuff.h>

struct MainWindow;
struct AboutWindow;
struct FcitxClassicUIStatus;

typedef enum _HIDE_MAINWINDOW {
    HM_SHOW = 0,
    HM_AUTO = 1,
    HM_HIDE = 2
} HIDE_MAINWINDOW;

/**
 * @brief Config and Global State for Classic UI
 **/
typedef struct FcitxClassicUI {
    GenericConfig gconfig;
    Display* dpy;
    int iScreen;
    Atom protocolAtom;
    Atom killAtom;
    struct InputWindow* inputWindow;
    struct MainWindow* mainWindow;
    struct MessageWindow* messageWindow;
    struct TrayWindow* trayWindow;
    struct AboutWindow* aboutWindow;
    FcitxUIMenu skinMenu;
    
    FcitxSkin skin;
    UT_array skinBuf;
    struct FcitxInstance *owner;
    
    char* font;
    char* menuFont;
    char* strUserLocale;
    boolean bUseTrayIcon;
    boolean bUseTrayIcon_;
    HIDE_MAINWINDOW hideMainWindow;
    boolean bVerticalList;
    char* skinType;
    int iMainWindowOffsetX;
    int iMainWindowOffsetY;
    
    UT_array status;
    struct XlibMenu* mainMenuWindow;
    FcitxUIMenu mainMenu;
} FcitxClassicUI;

void GetScreenSize(FcitxClassicUI* classicui, int* width, int* height);
void
ClassicUIInitWindowAttribute(FcitxClassicUI* classicui, Visual ** vs, Colormap * cmap,
                    XSetWindowAttributes * attrib,
                    unsigned long *attribmask, int *depth);
Visual * ClassicUIFindARGBVisual (FcitxClassicUI* classicui);
boolean ClassicUIMouseClick(FcitxClassicUI* classicui, Window window, int *x, int *y);
boolean IsInRspArea(int x0, int y0, struct FcitxClassicUIStatus* status);
void ClassicUISetWindowProperty(FcitxClassicUI* classicui, Window window, FcitxXWindowType type, char *windowTitle);
void ActivateWindow(Display *dpy, int iScreen, Window window);
void LoadClassicUIConfig(FcitxClassicUI* classicui);
void SaveClassicUIConfig(FcitxClassicUI* classicui);

#define GetPrivateStatus(status) ((FcitxClassicUIStatus*)(status)->priv)

CONFIG_BINDING_DECLARE(FcitxClassicUI);
#endif