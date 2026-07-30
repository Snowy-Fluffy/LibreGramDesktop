// This is the source code of AyuGram for Desktop.
//
// We do not and cannot prevent the use of our code,
// but be respectful and credit the original author.
//
// Copyright @Radolyn, 2026
#include "ayu/ui/components/avatar_corners_preview.h"

#include "data/data_peer.h"
#include "data/data_user.h"
#include "main/main_session.h"
#include "styles/style_ayu_icons.h"
#include "styles/style_dialogs.h"
#include "styles/style_settings.h"
#include "ui/empty_userpic.h"
#include "ui/painter.h"
#include "ui/userpic_view.h"
#include "ui/effects/ripple_animation.h"
#include "window/window_session_controller.h"

AvatarCornersPreview::AvatarCornersPreview(
	QWidget *parent,
	not_null<Window::SessionController*> controller)
: RpWidget(parent)
, _controller(controller)
, _emptyUserpic(
	Ui::EmptyUserpic::UserpicColor(0),
	QString())
, _peer(controller->session().user()) {
	const auto &row = st::defaultDialogRow;
	setFixedHeight(row.height);
	setCursor(Qt::PointingHandCursor);
	_peer->loadUserpic();
	subscribeToUpdates();
}

void AvatarCornersPreview::paintEvent(QPaintEvent *e) {
	auto p = Painter(this);

	const auto &row = st::defaultDialogRow;
	const auto photoSize = row.photoSize;
	const auto xShift = st::settingsButtonNoIcon.padding.left()
		- row.padding.left();
	const auto userpicX = row.padding.left() + xShift;
	const auto userpicY = (height() - photoSize) / 2;

	p.fillRect(rect(), st::windowBg);

	if (_ripple) {
		_ripple->paint(p, 0, 0, width());
		if (_ripple->empty()) {
			_ripple.reset();
		}
	}

	if (_peer) {
		_peer->paintUserpicLeft(
			p, _userpicView, userpicX, userpicY, width(), photoSize);
	} else {
		_emptyUserpic.paintCircle(p, userpicX, userpicY, width(), photoSize);
	}

	const auto nameText = _peer
		? _peer->name()
		: QString();
	p.setPen(st::dialogsNameFg);
	p.setFont(st::semiboldFont);
	p.drawText(row.nameLeft + xShift, row.nameTop + st::semiboldFont->ascent, nameText);

	p.setPen(st::dialogsTextFg);
	p.setFont(st::dialogsTextFont);
	p.drawText(row.textLeft + xShift, row.textTop + st::dialogsTextFont->ascent, u"Better late than never"_q);
}

void AvatarCornersPreview::mousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		if (!_ripple) {
			auto mask = Ui::RippleAnimation::RectMask(size());
			_ripple = std::make_unique<Ui::RippleAnimation>(
				st::defaultRippleAnimation,
				std::move(mask),
				[=] { update(); });
		}
		_ripple->add(e->pos());
	}
}

void AvatarCornersPreview::mouseReleaseEvent(QMouseEvent *e) {
	if (_ripple) {
		_ripple->lastStop();
	}
}

void AvatarCornersPreview::subscribeToUpdates() {
	if (!_peer) return;
	_peer->session().downloaderTaskFinished(
	) | rpl::on_next([=] {
		update();
	}, lifetime());
}
