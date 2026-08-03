// This is the source code of AyuGram for Desktop.
//
// We do not and cannot prevent the use of our code,
// but be respectful and credit the original author.
//
// Copyright @Radolyn, 2026
#pragma once

// Fast static cache mirroring a subset of AyuSettings, read on paint-time
// hot paths (avatar shape/radius, font selector) that must not touch the
// full AyuSettings singleton on every frame. AyuInfra::init() and
// AyuSettings's own setters keep it in sync with the real settings.
class AyuUiSettings {
public:
	static constexpr auto kMaxAvatarCorners = 24;

	[[nodiscard]] static QString getMonoFont() {
		return _monoFont;
	}
	static void setMonoFont(const QString &value) {
		_monoFont = value;
	}

	static void setWideMultiplier(double value) {
		_wideMultiplier = value;
	}

	static void setMaterialSwitches(bool value) {
		_materialSwitches = value;
	}

	[[nodiscard]] static int getAvatarCorners() {
		return _avatarCorners;
	}
	static void setAvatarCorners(int value) {
		_avatarCorners = value;
	}

private:
	static QString _monoFont;
	static double _wideMultiplier;
	static bool _materialSwitches;
	static int _avatarCorners;
};
