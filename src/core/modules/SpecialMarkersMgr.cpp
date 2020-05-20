/*
 * Stellarium
 * Copyright (C) 2020 Alexander Wolf
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */

#include "SpecialMarkersMgr.hpp"
#include "StelApp.hpp"
#include "StelCore.hpp"
#include "StelPainter.hpp"
#include "StelProjector.hpp"
#include "StelFader.hpp"
#include "StelModuleMgr.hpp"
#include "StelTranslator.hpp"

#include <QSettings>

//! @class SpecialSkyMarker
class SpecialSkyMarker
{
public:
	enum SKY_MARKER_TYPE
	{
		FOV_CENTER,
		FOV_CIRCLE,
		FOR_RECTANGULAR
	};
	SpecialSkyMarker(SKY_MARKER_TYPE _marker_type = FOV_CENTER);
	virtual ~SpecialSkyMarker();
	void draw(StelCore* core) const;
	void setColor(const Vec3f& c) {color = c;}
	const Vec3f& getColor() const {return color;}
	void setAngularSize(const Vec2d& s) {angularSize = s;}
	const Vec2d& getAngularSize() const {return angularSize;}
	void setRotationAngle(const double pa) { rotationAngle = pa; }
	double getRotationAngle() const { return rotationAngle; }
	void update(double deltaTime) {fader.update(static_cast<int>(deltaTime*1000));}
	void setFadeDuration(float duration) {fader.setDuration(static_cast<int>(duration*1000.f));}
	void setDisplayed(const bool displayed){fader = displayed;}
	bool isDisplayed() const {return fader;}

private:
	SKY_MARKER_TYPE marker_type;
	Vec3f color;
	Vec2d angularSize;
	double rotationAngle;
	StelCore::FrameType frameType;
	LinearFader fader;
};

SpecialSkyMarker::SpecialSkyMarker(SKY_MARKER_TYPE _marker_type) : marker_type(_marker_type), color(1.f, 0.f, 0.f), angularSize(1.,1.), rotationAngle(0.)
{
	switch (marker_type)
	{
		case FOV_CENTER:
		case FOV_CIRCLE:
		case FOR_RECTANGULAR:
			frameType = StelCore::FrameEquinoxEqu;
			break;
		default:
			Q_ASSERT(0);
	}
}

SpecialSkyMarker::~SpecialSkyMarker()
{
	//
}

void SpecialSkyMarker::draw(StelCore *core) const
{
	if (fader.getInterstate()<=0.0001f)
		return;

	StelProjectorP prj = core->getProjection(frameType, frameType!=StelCore::FrameAltAz ? StelCore::RefractionAuto : StelCore::RefractionOff);

	// Initialize a painter and set openGL state
	StelPainter sPainter(prj);
	StelProjector::StelProjectorParams params = core->getCurrentStelProjectorParams();
	sPainter.setColor(color);
	Vec2i centerScreen(prj->getViewportPosX() + prj->getViewportWidth() / 2, prj->getViewportPosY() + prj->getViewportHeight() / 2);

	/////////////////////////////////////////////////
	// Draw the marker
	switch (marker_type)
	{
		case FOV_CENTER:
		{
			QPoint a, b;
			QTransform transform = QTransform().translate(centerScreen[0], centerScreen[1]);
			const int radius = qRound(10 * params.devicePixelsPerPixel);
			sPainter.drawCircle(centerScreen[0], centerScreen[1], radius);
			const int cross = qRound(15 * params.devicePixelsPerPixel);
			a = transform.map(QPoint(0, -cross));
			b = transform.map(QPoint(0, cross));
			sPainter.drawLine2d(a.x(), a.y(), b.x(), b.y());
			a = transform.map(QPoint(-cross, 0));
			b = transform.map(QPoint(cross, 0));
			sPainter.drawLine2d(a.x(), a.y(), b.x(), b.y());
		}
			break;
		case FOV_CIRCLE:
		{
			const float pixelsPerRad = prj->getPixelPerRadAtCenter(); // * params.devicePixelsPerPixel;
			sPainter.drawCircle(centerScreen[0], centerScreen[1], 0.5f * pixelsPerRad * static_cast<float>(M_PI/180) * (angularSize[0]));
		}
			break;
		case FOR_RECTANGULAR:
		{
			QPoint a, b;
			const double fovRatio = qMax(angularSize[0], angularSize[1])/static_cast<double>(params.fov);
			const float pixelsPerRad = prj->getPixelPerRadAtCenter();
			const double width = pixelsPerRad * (M_PI/180) * angularSize[0];
			const double height = pixelsPerRad * (M_PI/180) * angularSize[1];
			QTransform transform = QTransform().translate(centerScreen[0], centerScreen[1]).rotate(-rotationAngle);
			// bottom line
			a = transform.map(QPoint(static_cast<int>(-width*0.5f), static_cast<int>(-height*0.5f)));
			b = transform.map(QPoint(static_cast<int>(width*0.5f), static_cast<int>(-height*0.5f)));
			sPainter.drawLine2d(a.x(), a.y(), b.x(), b.y());
			// top line
			a = transform.map(QPoint(static_cast<int>(-width*0.5f), static_cast<int>(height*0.5f)));
			b = transform.map(QPoint(static_cast<int>(width*0.5f), static_cast<int>(height*0.5f)));
			sPainter.drawLine2d(a.x(), a.y(), b.x(), b.y());
			// left line
			a = transform.map(QPoint(static_cast<int>(-width*0.5f), static_cast<int>(-height*0.5f)));
			b = transform.map(QPoint(static_cast<int>(-width*0.5f), static_cast<int>(height*0.5f)));
			sPainter.drawLine2d(a.x(), a.y(), b.x(), b.y());
			// right line
			a = transform.map(QPoint(static_cast<int>(width*0.5f), static_cast<int>(height*0.50f)));
			b = transform.map(QPoint(static_cast<int>(width*0.5f), static_cast<int>(-height*0.5f)));
			sPainter.drawLine2d(a.x(), a.y(), b.x(), b.y());

			if (fovRatio>=0.25)
			{
				QString info = QString("%1%4x%2%4 @ %3%4").arg(QString::number(angularSize[0], 'f', 2)).arg(QString::number(angularSize[1], 'f', 2)).arg(QString::number(rotationAngle, 'f', 1)).arg(QChar(0x00B0));
				a = transform.map(QPoint(qRound(width*0.5 - sPainter.getFontMetrics().width(info)*params.devicePixelsPerPixel), qRound(height*0.5 + 5.)));
				sPainter.drawText(a.x(), a.y(), info, static_cast<float>(-rotationAngle));
			}
		}
			break;
		default:
			Q_ASSERT(0);
	}
}


SpecialMarkersMgr::SpecialMarkersMgr()
{
	setObjectName("SpecialMarkersMgr");

	fovCenterMarker = new SpecialSkyMarker(SpecialSkyMarker::FOV_CENTER);
	fovCircleMarker = new SpecialSkyMarker(SpecialSkyMarker::FOV_CIRCLE);
	fovRectangularMarker = new SpecialSkyMarker(SpecialSkyMarker::FOR_RECTANGULAR);
}

SpecialMarkersMgr::~SpecialMarkersMgr()
{
	delete fovCenterMarker;
	delete fovCircleMarker;
	delete fovRectangularMarker;
}

/*************************************************************************
 Reimplementation of the getCallOrder method
*************************************************************************/
double SpecialMarkersMgr::getCallOrder(StelModuleActionName actionName) const
{
	if (actionName==StelModule::ActionDraw)
		return StelApp::getInstance().getModuleMgr().getModule("LandscapeMgr")->getCallOrder(actionName) + 3.;

	return 0.;
}

void SpecialMarkersMgr::init()
{
	QSettings* conf = StelApp::getInstance().getSettings();
	Q_ASSERT(conf);

	setFlagFOVCenterMarker(conf->value("viewing/flag_fov_center_marker").toBool());
	setFlagFOVCircleMarker(conf->value("viewing/flag_fov_circle_marker").toBool());
	setFOVCircleMarkerSize(conf->value("viewing/size_fov_circle_marker", 1.0).toDouble());
	setFlagFOVRectangularMarker(conf->value("viewing/flag_fov_rectangular_marker").toBool());
	setFOVRectangularMarkerWidth(conf->value("viewing/width_fov_rectangular_marker", 4.0).toDouble());
	setFOVRectangularMarkerHeight(conf->value("viewing/height_fov_rectangular_marker", 3.0).toDouble());
	setFOVRectangularMarkerRotationAngle(conf->value("viewing/rot_fov_rectangular_marker", 0.0).toDouble());

	// Load colors from config file
	QString defaultColor = conf->value("color/default_color", "0.5,0.5,0.7").toString();
	setColorFOVCenterMarker(Vec3f(conf->value("color/fov_center_marker_color", defaultColor).toString()));
	setColorFOVCircleMarker(Vec3f(conf->value("color/fov_circle_marker_color", defaultColor).toString()));
	setColorFOVRectangularMarker(Vec3f(conf->value("color/fov_rectangular_marker_color", defaultColor).toString()));

	QString displayGroup = N_("Display Options");
	addAction("actionShow_FOV_Center_Marker", displayGroup, N_("FOV Center marker"), "fovCenterMarkerDisplayed", "");
	addAction("actionShow_FOV_Circle_Marker", displayGroup, N_("FOV circle marker"), "fovCircleMarkerDisplayed", "");
	addAction("actionShow_FOV_Rectangular_Marker", displayGroup, N_("FOV rectangular marker"), "fovRectangularMarkerDisplayed", "");
}

void SpecialMarkersMgr::update(double deltaTime)
{
	// Update faders
	fovCenterMarker->update(deltaTime);
	fovCircleMarker->update(deltaTime);
	fovRectangularMarker->update(deltaTime);
}

void SpecialMarkersMgr::draw(StelCore* core)
{
	fovCenterMarker->draw(core);
	fovCircleMarker->draw(core);
	fovRectangularMarker->draw(core);
}

void SpecialMarkersMgr::setFlagFOVCenterMarker(const bool displayed)
{
	if(displayed != fovCenterMarker->isDisplayed()) {
		fovCenterMarker->setDisplayed(displayed);
		emit fovCenterMarkerDisplayedChanged(displayed);
	}
}

bool SpecialMarkersMgr::getFlagFOVCenterMarker() const
{
	return fovCenterMarker->isDisplayed();
}

Vec3f SpecialMarkersMgr::getColorFOVCenterMarker() const
{
	return fovCenterMarker->getColor();
}

void SpecialMarkersMgr::setColorFOVCenterMarker(const Vec3f& newColor)
{
	if(newColor != fovCenterMarker->getColor()) {
		fovCenterMarker->setColor(newColor);
		emit fovCenterMarkerColorChanged(newColor);
	}
}

void SpecialMarkersMgr::setFlagFOVCircleMarker(const bool displayed)
{
	if(displayed != fovCircleMarker->isDisplayed()) {
		fovCircleMarker->setDisplayed(displayed);
		emit fovCircleMarkerDisplayedChanged(displayed);
	}
}

bool SpecialMarkersMgr::getFlagFOVCircleMarker() const
{
	return fovCircleMarker->isDisplayed();
}

Vec3f SpecialMarkersMgr::getColorFOVCircleMarker() const
{
	return fovCircleMarker->getColor();
}

void SpecialMarkersMgr::setColorFOVCircleMarker(const Vec3f& newColor)
{
	if(newColor != fovCircleMarker->getColor()) {
		fovCircleMarker->setColor(newColor);
		emit fovCircleMarkerColorChanged(newColor);
	}
}

void SpecialMarkersMgr::setFOVCircleMarkerSize(const double size)
{
	fovCircleMarker->setAngularSize(Vec2d(size, 0.));
	emit fovCircleMarkerSizeChanged(size);
}

double SpecialMarkersMgr::getFOVCircleMarkerSize() const
{
	return fovCircleMarker->getAngularSize()[0];
}

void SpecialMarkersMgr::setFlagFOVRectangularMarker(const bool displayed)
{
	if(displayed != fovRectangularMarker->isDisplayed()) {
		fovRectangularMarker->setDisplayed(displayed);
		emit fovRectangularMarkerDisplayedChanged(displayed);
	}
}

bool SpecialMarkersMgr::getFlagFOVRectangularMarker() const
{
	return fovRectangularMarker->isDisplayed();
}

void SpecialMarkersMgr::setColorFOVRectangularMarker(const Vec3f& newColor)
{
	if(newColor != fovRectangularMarker->getColor()) {
		fovRectangularMarker->setColor(newColor);
		emit fovRectangularMarkerColorChanged(newColor);
	}
}

Vec3f SpecialMarkersMgr::getColorFOVRectangularMarker() const
{
	return fovRectangularMarker->getColor();
}

void SpecialMarkersMgr::setFOVRectangularMarkerWidth(const double size)
{
	fovRectangularMarker->setAngularSize(Vec2d(size, fovRectangularMarker->getAngularSize()[1]));
	emit fovRectangularMarkerWidthChanged(size);
}

double SpecialMarkersMgr::getFOVRectangularMarkerWidth() const
{
	return fovRectangularMarker->getAngularSize()[0];
}

void SpecialMarkersMgr::setFOVRectangularMarkerHeight(const double size)
{
	fovRectangularMarker->setAngularSize(Vec2d(fovRectangularMarker->getAngularSize()[0], size));
	emit fovRectangularMarkerHeightChanged(size);
}

double SpecialMarkersMgr::getFOVRectangularMarkerHeight() const
{
	return fovRectangularMarker->getAngularSize()[1];
}

void SpecialMarkersMgr::setFOVRectangularMarkerRotationAngle(const double angle)
{
	fovRectangularMarker->setRotationAngle(angle);
	emit fovRectangularMarkerRotationAngleChanged(angle);
}

double SpecialMarkersMgr::getFOVRectangularMarkerRotationAngle() const
{
	return fovRectangularMarker->getRotationAngle();
}
