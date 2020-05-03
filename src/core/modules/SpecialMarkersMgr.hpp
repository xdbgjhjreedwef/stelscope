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

#ifndef SPECIALMARKERSMGR_HPP
#define SPECIALMARKERSMGR_HPP

#include "VecMath.hpp"
#include "StelModule.hpp"

class SpecialSkyMarker;

class SpecialMarkersMgr : public StelModule
{
	Q_OBJECT
	Q_PROPERTY(bool fovCenterMarkerDisplayed	READ getFlagFOVCenterMarker		WRITE setFlagFOVCenterMarker		NOTIFY fovCenterMarkerDisplayedChanged)
	Q_PROPERTY(Vec3f fovCenterMarkerColor		READ getColorFOVCenterMarker	WRITE setColorFOVCenterMarker	NOTIFY fovCenterMarkerColorChanged)

	Q_PROPERTY(bool fovCircleMarkerDisplayed	READ getFlagFOVCircleMarker		WRITE setFlagFOVCircleMarker		NOTIFY fovCircleMarkerDisplayedChanged)
	Q_PROPERTY(double fovCircleMarkerSize		READ getFOVCircleMarkerSize		WRITE setFOVCircleMarkerSize		NOTIFY fovCircleMarkerSizeChanged)
	Q_PROPERTY(Vec3f fovCircleMarkerColor		READ getColorFOVCircleMarker		WRITE setColorFOVCircleMarker		NOTIFY fovCircleMarkerColorChanged)

public:
	SpecialMarkersMgr();
	virtual ~SpecialMarkersMgr();

	///////////////////////////////////////////////////////////////////////////
	// Methods defined in the StelModule class
	//! Initialize the GridLinesMgr. This process checks the values in the
	//! application settings, and according to the settings there
	//! sets the visibility of the Equatorial Grids, Ecliptical Grids, Azimuthal Grid, Meridian Line,
	//! Equator Line and Ecliptic Lines.
	virtual void init();

	//! Get the module ID, returns "SpecialMarkersMgr".
	virtual QString getModuleID() const {return "SpecialMarkersMgr";}

	//! Draw the grids and great circle lines.
	//! Draws the Equatorial Grids, Ecliptical Grids, Azimuthal Grid, Meridian Line, Equator Line,
	//! Ecliptic Lines, Precession Circles, Conjunction-Opposition Line, east-west vertical and colures according to the
	//! various flags which control their visibility.
	virtual void draw(StelCore* core);

	//! Update time-dependent features.
	//! Used to control fading when turning on and off the grid lines and great circles.
	virtual void update(double deltaTime);

	//! Used to determine the order in which the various modules are drawn.
	virtual double getCallOrder(StelModuleActionName actionName) const;

	///////////////////////////////////////////////////////////////////////////////////////
	// Setter and getters
public slots:
	//! Setter for displaying the FOV center marker
	void setFlagFOVCenterMarker(const bool displayed);
	//! Accessor for displaying FOV center marker.
	bool getFlagFOVCenterMarker() const;
	//! Get the current color of the FOV center marker.
	Vec3f getColorFOVCenterMarker() const;
	//! Set the color of the FOV center marker.
	//! @param newColor The color of FOV center marker.
	//! @code
	//! // example of usage in scripts
	//! GridLinesMgr.setColorFOVCenterMarker(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setColorFOVCenterMarker(const Vec3f& newColor);

	//! Setter for displaying the circle FOV marker
	void setFlagFOVCircleMarker(const bool displayed);
	//! Accessor for displaying circle FOV marker.
	bool getFlagFOVCircleMarker() const;
	//! Setter for size of circle FOV marker
	void setFOVCircleMarkerSize(const double size);
	//! Accessor for get size of circle FOV marker.
	double getFOVCircleMarkerSize() const;
	//! Get the current color of the circle FOV marker.
	Vec3f getColorFOVCircleMarker() const;
	//! Set the color of the circle FOV marker.
	//! @param newColor The color of circle FOV marker.
	//! @code
	//! // example of usage in scripts
	//! GridLinesMgr.setColorFOVCircleMarker(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setColorFOVCircleMarker(const Vec3f& newColor);

signals:
	void fovCenterMarkerDisplayedChanged(const bool displayed) const;
	void fovCenterMarkerColorChanged(const Vec3f & newColor) const;
	void fovCircleMarkerDisplayedChanged(const bool displayed) const;
	void fovCircleMarkerSizeChanged(const double size) const;
	void fovCircleMarkerColorChanged(const Vec3f & newColor) const;

private:
	SpecialSkyMarker * fovCenterMarker;
	SpecialSkyMarker * fovCircleMarker;
};

#endif // SPECIALMARKERSMGR_HPP
