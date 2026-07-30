/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "base/const_string.h"

#define TDESKTOP_REQUESTED_ALPHA_VERSION (0ULL)

#ifdef TDESKTOP_ALLOW_CLOSED_ALPHA
#define TDESKTOP_ALPHA_VERSION TDESKTOP_REQUESTED_ALPHA_VERSION
#else // TDESKTOP_ALLOW_CLOSED_ALPHA
#define TDESKTOP_ALPHA_VERSION (0ULL)
#endif // TDESKTOP_ALLOW_CLOSED_ALPHA

// used in Updater.cpp and Setup.iss for Windows
constexpr auto AppId = "{52A00269-1036-44D2-B80A-AF9949C4640C}"_cs;
constexpr auto AppNameOld = "LibreGram for Windows"_cs;
constexpr auto AppName = "LibreGram"_cs;
constexpr auto AppFile = "LibreGram"_cs;
constexpr auto AppVersion = 7000006;
constexpr auto AppVersionStr = "7.0.6";
constexpr auto AppBetaVersion = false;
constexpr auto AppAlphaVersion = TDESKTOP_ALPHA_VERSION;
