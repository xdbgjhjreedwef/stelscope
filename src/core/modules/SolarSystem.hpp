/*
 * Stellarium
 * Copyright (C) 2002 Fabien Chereau
 * Copyright (c) 2010 Bogdan Marinov
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
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

#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP
//sun is already defined in Sun C/Solaris
#if defined(sun)
#undef sun
#endif

#include "StelObjectModule.hpp"
#include "StelTextureTypes.hpp"
#include "Planet.hpp"
#include "StelGui.hpp"
#include "StelHips.hpp"

#include <QFont>

class Orbit;
class StelTranslator;
class StelObject;
class StelCore;
class StelProjector;
class QSettings;

typedef QSharedPointer<Planet> PlanetP;

//! @class SolarSystem
//! This StelObjectModule derivative is used to model SolarSystem bodies.
//! This includes the Major Planets, Minor Planets and Comets.
class SolarSystem : public StelObjectModule
{
	Q_OBJECT
	Q_PROPERTY(bool labelsDisplayed // This is a "forwarding property" which sets labeling into all planets.
		   READ getFlagLabels
		   WRITE setFlagLabels
		   NOTIFY labelsDisplayedChanged)
	Q_PROPERTY(bool flagOrbits // was bool orbitsDisplayed
		   READ getFlagOrbits
		   WRITE setFlagOrbits
		   NOTIFY flagOrbitsChanged)
	Q_PROPERTY(bool trailsDisplayed
		   READ getFlagTrails
		   WRITE setFlagTrails
		   NOTIFY trailsDisplayedChanged)
	Q_PROPERTY(bool flagHints // was bool hintsDisplayed. This is a "forwarding property" only, without own variable.
		   READ getFlagHints
		   WRITE setFlagHints
		   NOTIFY flagHintsChanged)
	Q_PROPERTY(bool flagPointer // was bool pointersDisplayed
		   READ getFlagPointer
		   WRITE setFlagPointer
		   NOTIFY flagPointerChanged)
	Q_PROPERTY(bool flagNativePlanetNames // was bool nativeNamesDisplayed
		   READ getFlagNativePlanetNames
		   WRITE setFlagNativePlanetNames
		   NOTIFY flagNativePlanetNamesChanged)
	Q_PROPERTY(bool flagTranslatedNames
		   READ getFlagTranslatedNames
		   WRITE setFlagTranslatedNames
		   NOTIFY flagTranslatedNamesChanged)
	Q_PROPERTY(bool planetsDisplayed
		   READ getFlagPlanets
		   WRITE setFlagPlanets
		   NOTIFY flagPlanetsDisplayedChanged
		   )
	Q_PROPERTY(bool flagPlanetsOrbitsOnly
		   READ getFlagPlanetsOrbitsOnly
		   WRITE setFlagPlanetsOrbitsOnly
		   NOTIFY flagPlanetsOrbitsOnlyChanged
		   )
	Q_PROPERTY(bool flagIsolatedOrbits
		   READ getFlagIsolatedOrbits
		   WRITE setFlagIsolatedOrbits
		   NOTIFY flagIsolatedOrbitsChanged
		   )
	Q_PROPERTY(bool flagIsolatedTrails
		   READ getFlagIsolatedTrails
		   WRITE setFlagIsolatedTrails
		   NOTIFY flagIsolatedTrailsChanged
		   )
	Q_PROPERTY(bool flagLightTravelTime
		   READ getFlagLightTravelTime
		   WRITE setFlagLightTravelTime
		   NOTIFY flagLightTravelTimeChanged
		   )
	Q_PROPERTY(bool flagUseObjModels
		   READ getFlagUseObjModels
		   WRITE setFlagUseObjModels
		   NOTIFY flagUseObjModelsChanged
		   )
	Q_PROPERTY(bool flagShowObjSelfShadows
		   READ getFlagShowObjSelfShadows
		   WRITE setFlagShowObjSelfShadows
		   NOTIFY flagShowObjSelfShadowsChanged
		   )
	Q_PROPERTY(bool flagMoonScale
		   READ getFlagMoonScale
		   WRITE setFlagMoonScale
		   NOTIFY flagMoonScaleChanged
		   )
	Q_PROPERTY(double moonScale
		   READ getMoonScale
		   WRITE setMoonScale
		   NOTIFY moonScaleChanged
		   )
	Q_PROPERTY(bool flagMinorBodyScale
		   READ getFlagMinorBodyScale
		   WRITE setFlagMinorBodyScale
		   NOTIFY flagMinorBodyScaleChanged
		   )
	Q_PROPERTY(double minorBodyScale
		   READ getMinorBodyScale
		   WRITE setMinorBodyScale
		   NOTIFY minorBodyScaleChanged
		   )
	Q_PROPERTY(double labelsAmount
		   READ getLabelsAmount
		   WRITE setLabelsAmount
		   NOTIFY labelsAmountChanged
		   )
	Q_PROPERTY(bool ephemerisMarkersDisplayed
		   READ getFlagEphemerisMarkers
		   WRITE setFlagEphemerisMarkers
		   NOTIFY ephemerisMarkersChanged
		   )
	Q_PROPERTY(bool ephemerisHorizontalCoordinates
		   READ getFlagEphemerisHorizontalCoordinates
		   WRITE setFlagEphemerisHorizontalCoordinates
		   NOTIFY ephemerisHorizontalCoordinatesChanged
		   )
	Q_PROPERTY(bool ephemerisDatesDisplayed
		   READ getFlagEphemerisDates
		   WRITE setFlagEphemerisDates
		   NOTIFY ephemerisDatesChanged
		   )	
	Q_PROPERTY(bool ephemerisMagnitudesDisplayed
		   READ getFlagEphemerisMagnitudes
		   WRITE setFlagEphemerisMagnitudes
		   NOTIFY ephemerisMagnitudesChanged
		   )

	Q_PROPERTY(bool flagCustomGrsSettings
		   READ getFlagCustomGrsSettings
		   WRITE setFlagCustomGrsSettings
		   NOTIFY flagCustomGrsSettingsChanged
		   )
	Q_PROPERTY(int customGrsLongitude
		   READ getCustomGrsLongitude
		   WRITE setCustomGrsLongitude
		   NOTIFY customGrsLongitudeChanged
		   )
	Q_PROPERTY(double customGrsDrift
		   READ getCustomGrsDrift
		   WRITE setCustomGrsDrift
		   NOTIFY customGrsDriftChanged
		   )
	Q_PROPERTY(double customGrsJD
		   READ getCustomGrsJD
		   WRITE setCustomGrsJD
		   NOTIFY customGrsJDChanged
		   )

	// Colors
	Q_PROPERTY(Vec3f labelsColor
		   READ getLabelsColor
		   WRITE setLabelsColor
		   NOTIFY labelsColorChanged
		   )
	Q_PROPERTY(Vec3f trailsColor
		   READ getTrailsColor
		   WRITE setTrailsColor
		   NOTIFY trailsColorChanged
		   )
	Q_PROPERTY(Vec3f orbitsColor
		   READ getOrbitsColor
		   WRITE setOrbitsColor
		   NOTIFY orbitsColorChanged
		   )
	Q_PROPERTY(Vec3f majorPlanetsOrbitsColor
		   READ getMajorPlanetsOrbitsColor
		   WRITE setMajorPlanetsOrbitsColor
		   NOTIFY majorPlanetsOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f minorPlanetsOrbitsColor
		   READ getMinorPlanetsOrbitsColor
		   WRITE setMinorPlanetsOrbitsColor
		   NOTIFY minorPlanetsOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f dwarfPlanetsOrbitsColor
		   READ getDwarfPlanetsOrbitsColor
		   WRITE setDwarfPlanetsOrbitsColor
		   NOTIFY dwarfPlanetsOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f moonsOrbitsColor
		   READ getMoonsOrbitsColor
		   WRITE setMoonsOrbitsColor
		   NOTIFY moonsOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f cubewanosOrbitsColor
		   READ getCubewanosOrbitsColor
		   WRITE setCubewanosOrbitsColor
		   NOTIFY cubewanosOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f plutinosOrbitsColor
		   READ getPlutinosOrbitsColor
		   WRITE setPlutinosOrbitsColor
		   NOTIFY plutinosOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f scatteredDiskObjectsOrbitsColor
		   READ getScatteredDiskObjectsOrbitsColor
		   WRITE setScatteredDiskObjectsOrbitsColor
		   NOTIFY scatteredDiskObjectsOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f oortCloudObjectsOrbitsColor
		   READ getOortCloudObjectsOrbitsColor
		   WRITE setOortCloudObjectsOrbitsColor
		   NOTIFY oortCloudObjectsOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f cometsOrbitsColor
		   READ getCometsOrbitsColor
		   WRITE setCometsOrbitsColor
		   NOTIFY cometsOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f sednoidsOrbitsColor
		   READ getSednoidsOrbitsColor
		   WRITE setSednoidsOrbitsColor
		   NOTIFY sednoidsOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f interstellarOrbitsColor
		   READ getInterstellarOrbitsColor
		   WRITE setInterstellarOrbitsColor
		   NOTIFY interstellarOrbitsColorChanged
		   )
	Q_PROPERTY(Vec3f mercuryOrbitColor
		   READ getMercuryOrbitColor
		   WRITE setMercuryOrbitColor
		   NOTIFY mercuryOrbitColorChanged
		   )
	Q_PROPERTY(Vec3f venusOrbitColor
		   READ getVenusOrbitColor
		   WRITE setVenusOrbitColor
		   NOTIFY venusOrbitColorChanged
		   )
	Q_PROPERTY(Vec3f earthOrbitColor
		   READ getEarthOrbitColor
		   WRITE setEarthOrbitColor
		   NOTIFY earthOrbitColorChanged
		   )
	Q_PROPERTY(Vec3f marsOrbitColor
		   READ getMarsOrbitColor
		   WRITE setMarsOrbitColor
		   NOTIFY marsOrbitColorChanged
		   )
	Q_PROPERTY(Vec3f jupiterOrbitColor
		   READ getJupiterOrbitColor
		   WRITE setJupiterOrbitColor
		   NOTIFY jupiterOrbitColorChanged
		   )
	Q_PROPERTY(Vec3f saturnOrbitColor
		   READ getSaturnOrbitColor
		   WRITE setSaturnOrbitColor
		   NOTIFY saturnOrbitColorChanged
		   )
	Q_PROPERTY(Vec3f uranusOrbitColor
		   READ getUranusOrbitColor
		   WRITE setUranusOrbitColor
		   NOTIFY uranusOrbitColorChanged
		   )
	Q_PROPERTY(Vec3f neptuneOrbitColor
		   READ getNeptuneOrbitColor
		   WRITE setNeptuneOrbitColor
		   NOTIFY neptuneOrbitColorChanged
		   )

	// Color style
	Q_PROPERTY(QString orbitColorStyle
		   READ getOrbitColorStyle
		   WRITE setOrbitColorStyle
		   NOTIFY orbitColorStyleChanged
		   )

	Q_PROPERTY(QString apparentMagnitudeAlgorithmOnEarth
		   READ getApparentMagnitudeAlgorithmOnEarth
		   WRITE setApparentMagnitudeAlgorithmOnEarth
		   NOTIFY apparentMagnitudeAlgorithmOnEarthChanged)

public:
	SolarSystem();
	virtual ~SolarSystem();

	///////////////////////////////////////////////////////////////////////////
	// Methods defined in the StelModule class
	//! Initialize the SolarSystem.
	//! Includes:
	//! - loading planetary body orbital and model data from data/ssystem.ini
	//! - perform initial planet position calculation
	//! - set display options from application settings
	virtual void init();

	virtual void deinit();
	
	//! Draw SolarSystem objects (planets).
	//! @param core The StelCore object.
	//! @return The maximum squared distance in pixels that any SolarSystem object
	//! has travelled since the last update.
	virtual void draw(StelCore *core);

	//! Update time-varying components.
	//! This includes planet motion trails.
	virtual void update(double deltaTime);

	//! Used to determine what order to draw the various StelModules.
	virtual double getCallOrder(StelModuleActionName actionName) const;

	///////////////////////////////////////////////////////////////////////////
	// Methods defined in StelObjectModule class
	//! Search for SolarSystem objects in some area around a point.
	//! @param v A vector representing a point in the sky.
	//! @param limitFov The radius of the circle around the point v which
	//! defines the size of the area to search.
	//! @param core the core object
	//! @return QList of StelObjectP (pointers) containing all SolarSystem objects
	//! found in the specified area. This vector is not sorted by distance from v.
	virtual QList<StelObjectP> searchAround(const Vec3d& v, double limitFov, const StelCore* core) const;

	//! Search for a SolarSystem object based on the localised name.
	//! @param nameI18n the case in-sensitive translated planet name.
	//! @return a StelObjectP for the object if found, else Q_NULLPTR.
	virtual StelObjectP searchByNameI18n(const QString& nameI18n) const;

	//! Search for a SolarSystem object based on the English name.
	//! @param name the case in-sensitive English planet name.
	//! @return a StelObjectP for the object if found, else Q_NULLPTR.
	virtual StelObjectP searchByName(const QString& name) const;

	virtual StelObjectP searchByID(const QString &id) const
	{
		return searchByName(id);
	}

	virtual QStringList listAllObjects(bool inEnglish) const;
	virtual QStringList listAllObjectsByType(const QString& objType, bool inEnglish) const;
	virtual QString getName() const { return "Solar System"; }
	virtual QString getStelObjectType() const { return Planet::PLANET_TYPE; }

public slots:
	///////////////////////////////////////////////////////////////////////////
	// Method callable from script and GUI
	// Properties setters and getters
	//! Set flag which determines if planets are drawn or hidden.
	void setFlagPlanets(bool b);
	//! Get the current value of the flag which determines if planet are drawn or hidden.
	bool getFlagPlanets() const;

	//! Set flag which determines if planet trails are drawn or hidden.
	void setFlagTrails(bool b);
	//! Get the current value of the flag which determines if planet trails are drawn or hidden.
	bool getFlagTrails() const;

	//! Set flag which determines if planet hints are drawn or hidden along labels
	void setFlagHints(bool b);
	//! Get the current value of the flag which determines if planet hints are drawn or hidden along labels
	bool getFlagHints() const;

	//! Set flag which determines if planet labels are drawn or hidden.
	void setFlagLabels(bool b);
	//! Get the current value of the flag which determines if planet labels are drawn or hidden.
	bool getFlagLabels() const;

	//! Set the amount of planet labels. The real amount is also proportional with FOV.
	//! The limit is set in function of the planets magnitude
	//! @param a the amount between 0 and 10. 0 is no labels, 10 is maximum of labels
	void setLabelsAmount(double a) {if(a!=labelsAmount) {labelsAmount=a; emit labelsAmountChanged(a);}}
	//! Get the amount of planet labels. The real amount is also proportional with FOV.
	//! @return the amount between 0 and 10. 0 is no labels, 10 is maximum of labels
	double getLabelsAmount(void) const {return labelsAmount;}

	//! Set flag which determines if planet orbits are drawn or hidden.
	void setFlagOrbits(bool b);
	//! Get the current value of the flag which determines if planet orbits are drawn or hidden.
	bool getFlagOrbits() const {return flagOrbits;}

	//! Set flag which determines if the planet pointer (red cross) is drawn or hidden on a selected planet.
	void setFlagPointer(bool b) { if (b!=flagPointer) { flagPointer=b; emit flagPointerChanged(b); }}
	//! Get the current value of the flag which determines if planet pointers are drawn or hidden.
	bool getFlagPointer() const { return flagPointer;}

	//! Set flag which determines if the light travel time calculation is used or not.
	void setFlagLightTravelTime(bool b);
	//! Get the current value of the flag which determines if light travel time
	//! calculation is used or not.
	bool getFlagLightTravelTime(void) const {return flagLightTravelTime;}

	//! Set flag whether to use OBJ models for rendering, where available
	void setFlagUseObjModels(bool b) { if(b!=flagUseObjModels) { flagUseObjModels = b; emit flagUseObjModelsChanged(b); } }
	//! Get the current value of the flag which determines wether to use OBJ models for rendering, where available
	bool getFlagUseObjModels(void) const { return flagUseObjModels; }

	//! Set flag whether OBJ models should render self-shadowing (using a shadow map)
	void setFlagShowObjSelfShadows(bool b);
	//! Get the current value of the flag which determines whether OBJ models should render self-shadowing (using a shadow map)
	bool getFlagShowObjSelfShadows(void) const { return flagShowObjSelfShadows; }

	//! Set planet names font size.
	//! @return font size
	void setFontSize(int newFontSize);

	//! Set the color used to draw planet labels.
	//! @param c The color of the planet labels (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setLabelsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setLabelsColor(const Vec3f& c);
	//! Get the current color used to draw planet labels.
	//! @return current color
	const Vec3f& getLabelsColor(void) const;

	//! Set the color used to draw solar system object orbit lines.
	//! @param c The color of the solar system object orbit lines (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw solar system object orbit lines.
	//! @return current color
	Vec3f getOrbitsColor(void) const;

	//! Set the color used to draw orbits lines of the major planets.
	//! @param c The color of orbits lines of the major planets (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setMajorPlanetsOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setMajorPlanetsOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw orbits lines of the major planets.
	//! @return current color
	Vec3f getMajorPlanetsOrbitsColor(void) const;

	//! Set the color used to draw orbits lines of moons of planets.
	//! @param c The color of orbits lines of moons of planets lines (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setMoonsOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setMoonsOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw orbits lines of moons of planets.
	//! @return current color
	Vec3f getMoonsOrbitsColor(void) const;

	//! Set the color used to draw orbits lines of the minor planets.
	//! @param c The color of orbits lines of the minor planets (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setMinorPlanetsOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setMinorPlanetsOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw orbits lines of the minor planets.
	//! @return current color
	Vec3f getMinorPlanetsOrbitsColor(void) const;

	//! Set the color used to draw orbits lines of the dwarf planets.
	//! @param c The color of orbits lines of the dwarf planets (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setDwarfPlanetsOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setDwarfPlanetsOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw orbits lines of the dwarf planets.
	//! @return current color
	Vec3f getDwarfPlanetsOrbitsColor(void) const;

	//! Set the color used to draw orbits lines of cubewanos.
	//! @param c The color of orbits lines of cubewanos (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setCubewanosOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setCubewanosOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw orbits lines of cubewanos.
	//! @return current color
	Vec3f getCubewanosOrbitsColor(void) const;

	//! Set the color used to draw orbits lines of plutinos.
	//! @param c The color of orbits lines of plutinos (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setPlutinosOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setPlutinosOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw orbits lines of plutinos.
	//! @return current color
	Vec3f getPlutinosOrbitsColor(void) const;

	//! Set the color used to draw orbits lines of scattered disk objects.
	//! @param c The color of orbits lines of scattered disk objects (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setScatteredDiskObjectsOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setScatteredDiskObjectsOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw orbits lines of scattered disk objects.
	//! @return current color
	Vec3f getScatteredDiskObjectsOrbitsColor(void) const;

	//! Set the color used to draw orbits lines of Oort cloud objects.
	//! @param c The color of orbits lines of Oort cloud objects (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setOortCloudObjectsOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setOortCloudObjectsOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw orbits lines of Oort cloud objects.
	//! @return current color
	Vec3f getOortCloudObjectsOrbitsColor(void) const;

	//! Set the color used to draw comet orbit lines.
	//! @param c The color of the comet orbit lines (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setCometsOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setCometsOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw comet orbit lines.
	//! @return current color
	Vec3f getCometsOrbitsColor(void) const;

	//! Set the color used to draw sednoid orbit lines.
	//! @param c The color of the sednoid orbit lines (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setSednoidsOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setSednoidsOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw sednoid orbit lines.
	//! @return current color
	Vec3f getSednoidsOrbitsColor(void) const;

	//! Set the color used to draw interstellar orbit (hyperbolic trajectory) lines.
	//! @param c The color of the interstellar orbit lines (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setInterstellarOrbitsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setInterstellarOrbitsColor(const Vec3f& c);
	//! Get the current color used to draw interstellar orbit lines.
	//! @return current color
	Vec3f getInterstellarOrbitsColor(void) const;

	//! Set the color used to draw Mercury orbit line.
	//! @param c The color of Mercury orbit line (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setMercuryOrbitColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setMercuryOrbitColor(const Vec3f& c);
	//! Get the current color used to draw Mercury orbit line.
	//! @return current color
	Vec3f getMercuryOrbitColor(void) const;

	//! Set the color used to draw Venus orbit line.
	//! @param c The color of Venus orbit line (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setVenusOrbitColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setVenusOrbitColor(const Vec3f& c);
	//! Get the current color used to draw Venus orbit line.
	//! @return current color
	Vec3f getVenusOrbitColor(void) const;

	//! Set the color used to draw Earth orbit line.
	//! @param c The color of Earth orbit line (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setEarthOrbitColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setEarthOrbitColor(const Vec3f& c);
	//! Get the current color used to draw Earth orbit line.
	//! @return current color
	Vec3f getEarthOrbitColor(void) const;

	//! Set the color used to draw Mars orbit line.
	//! @param c The color of Mars orbit line (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setMarsOrbitColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setMarsOrbitColor(const Vec3f& c);
	//! Get the current color used to draw Mars orbit line.
	//! @return current color
	Vec3f getMarsOrbitColor(void) const;

	//! Set the color used to draw Jupiter orbit line.
	//! @param c The color of Jupiter orbit line (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setJupiterOrbitColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setJupiterOrbitColor(const Vec3f& c);
	//! Get the current color used to draw Jupiter orbit line.
	//! @return current color
	Vec3f getJupiterOrbitColor(void) const;

	//! Set the color used to draw Saturn orbit line.
	//! @param c The color of Saturn orbit line (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setSaturnOrbitColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setSaturnOrbitColor(const Vec3f& c);
	//! Get the current color used to draw Saturn orbit line.
	//! @return current color
	Vec3f getSaturnOrbitColor(void) const;

	//! Set the color used to draw Uranus orbit line.
	//! @param c The color of Uranus orbit line (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setUranusOrbitColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setUranusOrbitColor(const Vec3f& c);
	//! Get the current color used to draw Uranus orbit line.
	//! @return current color
	Vec3f getUranusOrbitColor(void) const;

	//! Set the color used to draw Neptune orbit line.
	//! @param c The color of Neptune orbit line (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setNeptuneOrbitColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setNeptuneOrbitColor(const Vec3f& c);
	//! Get the current color used to draw Neptune orbit line.
	//! @return current color
	Vec3f getNeptuneOrbitColor(void) const;

	//! Set the color used to draw planet trails lines.
	//! @param c The color of the planet trails lines (R,G,B)
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setTrailsColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setTrailsColor(const Vec3f& c) {trailColor=c;}
	//! Get the current color used to draw planet trails lines.
	//! @return current color
	Vec3f getTrailsColor() const {return trailColor;}

	//! Set the color used to draw planet pointers.
	//! @param c The color of the planet pointers
	//! @code
	//! // example of usage in scripts
	//! SolarSystem.setPointerColor(Vec3f(1.0,0.0,0.0));
	//! @endcode
	void setPointerColor(const Vec3f& c) {pointerColor=c;}
	//! Get the current color used to draw planet pointers.
	//! @return current color
	Vec3f getPointerColor() const {return pointerColor;}

	//! Set flag which determines if Earth's moon is scaled or not.
	void setFlagMoonScale(bool b);
	//! Get the current value of the flag which determines if Earth's moon is scaled or not.
	bool getFlagMoonScale(void) const {return flagMoonScale;}

	//! Set the display scaling factor for Earth's moon.
	void setMoonScale(double f);
	//! Get the display scaling factor for Earth's moon.
	double getMoonScale(void) const {return moonScale;}

	//! Set flag which determines if minor bodies (everything except the 8 planets) are drawn scaled or not.
	void setFlagMinorBodyScale(bool b);
	//! Get the current value of the flag which determines if minor bodies (everything except the 8 planets) are drawn scaled or not.
	bool getFlagMinorBodyScale(void) const {return flagMinorBodyScale;}

	//! Set the display scaling factor for minor bodies.
	void setMinorBodyScale(double f);
	//! Get the display scaling factor for minor bodies.
	double getMinorBodyScale(void) const {return minorBodyScale;}

	//! Translate names. (public so that SolarSystemEditor can call it).
	void updateI18n();

	//! Get the V magnitude for Solar system bodies for scripts
	//! @param planetName the case in-sensitive English planet name.
	//! @param withExtinction the flag for use extinction effect for magnitudes (default not use)
	//! @return a magnitude
	float getPlanetVMagnitude(QString planetName, bool withExtinction=false) const;

	//! Get type for Solar system bodies for scripts
	//! @param planetName the case in-sensitive English planet name.
	//! @return a type of planet (planet, moon, asteroid, comet, plutoid)
	QString getPlanetType(QString planetName) const;

	//! Get distance to Solar system bodies for scripts
	//! @param planetName the case in-sensitive English planet name.
	//! @return a distance (in AU)
	double getDistanceToPlanet(QString planetName) const;

	//! Get elongation for Solar system bodies for scripts
	//! @param planetName the case in-sensitive English planet name.
	//! @return a elongation (in radians)
	double getElongationForPlanet(QString planetName) const;

	//! Get phase angle for Solar system bodies for scripts
	//! @param planetName the case in-sensitive English planet name.
	//! @return a phase angle (in radians)
	double getPhaseAngleForPlanet(QString planetName) const;

	//! Get phase for Solar system bodies for scripts
	//! @param planetName the case in-sensitive English planet name.
	//! @return phase, i.e. illuminated fraction [0..1]
	float getPhaseForPlanet(QString planetName) const;

	//! Set the algorithm for computation of apparent magnitudes for planets in case observer on the Earth.
	//! Possible values:
	//! @li @c Mueller1893 [Explanatory Supplement to the Astronomical Ephemeris, 1961] (visual magnitudes, based on visual observations by G. Mueller, 1877-91)
	//! @li @c AstrAlm1984 [Astronomical Almanac 1984] and later. These give V (instrumental) magnitudes.
	//! @li @c ExpSup1992 [Explanatory Supplement to the Astronomical Almanac, 1992] (algorithm contributed by Pere Planesas, Observatorio Astronomico Nacional)
	//! @li @c ExpSup2013 [Explanatory Supplement to the Astronomical Almanac, 3rd edition, 2013]
	//! @li @c Generic Visual magnitude based on phase angle and albedo.
	//! Details:
	//! @li J. Meeus "Astronomical Algorithms" (2nd ed. 1998, with corrections as of August 10, 2009) p.283-286.
	//! @li O. Montenbruck, T. Pfleger "Astronomy on the Personal Computer" (4th ed.) p.143-145.
	//! @li Daniel L. Harris "Photometry and Colorimetry of Planets and Satellites" http://adsabs.harvard.edu/abs/1961plsa.book..272H
	//! @li Sean E. Urban and P. Kenneth Seidelmann "Explanatory Supplement to the Astronomical Almanac" (3rd edition, 2013)
	//! Hint: Default option in config.ini: astro/apparent_magnitude_algorithm = ExpSup2013
	//! @param algorithm the case in-sensitive algorithm name
	//! @note: The structure of algorithms is almost identical, just the numbers are different!
	//!        You should activate Mueller's algorithm to simulate the eye's impression. (Esp. Venus!)
	void setApparentMagnitudeAlgorithmOnEarth(QString algorithm);

	//! Get the algorithm used for computation of apparent magnitudes for planets in case  observer on the Earth
	//! @see setApparentMagnitudeAlgorithmOnEarth()
	QString getApparentMagnitudeAlgorithmOnEarth() const;

	//! Set flag which enable use native names for planets or not.
	void setFlagNativePlanetNames(bool b);
	//! Get the current value of the flag which enables showing native names for planets or not.
	bool getFlagNativePlanetNames(void) const;

	//! Set flag which enable use translated names for planets or not.
	void setFlagTranslatedNames(bool b);
	//! Get the current value of the flag which enables showing translated names for planets or not.
	bool getFlagTranslatedNames(void) const;

	//! Set flag which enabled the showing of isolated trails for selected objects only or not
	void setFlagIsolatedTrails(bool b);
	//! Get the current value of the flag which enables showing of isolated trails for selected objects only or not.
	bool getFlagIsolatedTrails(void) const;

	//! Set flag which enabled the showing of isolated orbits for selected objects only or not
	void setFlagIsolatedOrbits(bool b);
	//! Get the current value of the flag which enables showing of isolated orbits for selected objects only or not.
	bool getFlagIsolatedOrbits(void) const;

	//! Set flag which enabled the showing of planets orbits only or not
	void setFlagPlanetsOrbitsOnly(bool b);
	//! Get the current value of the flag which enables showing of planets orbits only or not.
	bool getFlagPlanetsOrbitsOnly(void) const;

	//! Set flag which determines if custom settings is using for Great Red Spot on Jupiter
	void setFlagCustomGrsSettings(bool b);
	//! Get the current value of the flag which determines if custom settings for Great Red Spot on Jupiter is used or not.
	bool getFlagCustomGrsSettings() const;

	//! Set longitude of Great Red Spot (System II is used)
	//! @param longitude (degrees)
	void setCustomGrsLongitude(int longitude);
	//! Get longitude of Great Red Spot (System II is used)
	//! @return a longitude (degrees)
	int getCustomGrsLongitude() const;

	//! Set speed of annual drift for Great Red Spot (System II is used)
	//! @param annual drift (degrees)
	void setCustomGrsDrift(double drift);
	//! Get speed of annual drift for Great Red Spot (System II is used)
	double getCustomGrsDrift() const;

	//! Set initial JD for calculation of position of Great Red Spot
	//! @param JD
	// TODO (GZ): Clarify whether this is JD or rather JDE?
	void setCustomGrsJD(double JD);
	//! Get initial JD for calculation of position of Great Red Spot
	double getCustomGrsJD();

	//! Set style of colors of orbits for Solar system bodies
	void setOrbitColorStyle(QString style);
	//! Get style of colors of orbits for Solar system bodies
	QString getOrbitColorStyle() const;

	//! Get list of objects by type
	//! @param objType object type
	QStringList getObjectsList(QString objType="all") const;

signals:
	void labelsDisplayedChanged(bool b);
	void nomenclatureDisplayedChanged(bool b);
	void flagOrbitsChanged(bool b);
	void flagHintsChanged(bool b);
	void trailsDisplayedChanged(bool b);
	void flagPointerChanged(bool b);
	void flagNativePlanetNamesChanged(bool b);
	void flagTranslatedNamesChanged(bool b);
	void flagPlanetsDisplayedChanged(bool b);
	void flagPlanetsOrbitsOnlyChanged(bool b);
	void flagIsolatedOrbitsChanged(bool b);
	void flagIsolatedTrailsChanged(bool b);
	void flagLightTravelTimeChanged(bool b);
	void flagUseObjModelsChanged(bool b);
	void flagShowObjSelfShadowsChanged(bool b);
	void flagMoonScaleChanged(bool b);
	void moonScaleChanged(double f);
	void flagMinorBodyScaleChanged(bool b);
	void minorBodyScaleChanged(double f);
	void labelsAmountChanged(double f);
	void ephemerisMarkersChanged(bool b);
	void ephemerisHorizontalCoordinatesChanged(bool b);
	void ephemerisDatesChanged(bool b);
	void ephemerisMagnitudesChanged(bool b);
	void flagCustomGrsSettingsChanged(bool b);
	void customGrsLongitudeChanged(int l);
	void customGrsDriftChanged(double drift);
	void customGrsJDChanged(double JD);

	void labelsColorChanged(const Vec3f & color) const;
	void trailsColorChanged(const Vec3f & color) const;
	void orbitsColorChanged(const Vec3f & color) const;
	void nomenclatureColorChanged(const Vec3f & color) const;
	void majorPlanetsOrbitsColorChanged(const Vec3f & color) const;
	void minorPlanetsOrbitsColorChanged(const Vec3f & color) const;
	void dwarfPlanetsOrbitsColorChanged(const Vec3f & color) const;
	void moonsOrbitsColorChanged(const Vec3f & color) const;
	void cubewanosOrbitsColorChanged(const Vec3f & color) const;
	void plutinosOrbitsColorChanged(const Vec3f & color) const;
	void scatteredDiskObjectsOrbitsColorChanged(const Vec3f & color) const;
	void oortCloudObjectsOrbitsColorChanged(const Vec3f & color) const;
	void cometsOrbitsColorChanged(const Vec3f & color) const;
	void sednoidsOrbitsColorChanged(const Vec3f & color) const;
	void interstellarOrbitsColorChanged(const Vec3f & color) const;
	void mercuryOrbitColorChanged(const Vec3f & color) const;
	void venusOrbitColorChanged(const Vec3f & color) const;
	void earthOrbitColorChanged(const Vec3f & color) const;
	void marsOrbitColorChanged(const Vec3f & color) const;
	void jupiterOrbitColorChanged(const Vec3f & color) const;
	void saturnOrbitColorChanged(const Vec3f & color) const;
	void uranusOrbitColorChanged(const Vec3f & color) const;
	void neptuneOrbitColorChanged(const Vec3f & color) const;

	void orbitColorStyleChanged(QString style) const;
	void apparentMagnitudeAlgorithmOnEarthChanged(QString algorithm) const;

	void solarSystemDataReloaded();

public:
	///////////////////////////////////////////////////////////////////////////
	// Other public methods
	//! Get a pointer to a Planet object.
	//! @param planetEnglishName the English name of the desired planet.
	//! @return The matching planet pointer if exists or Q_NULLPTR.
	PlanetP searchByEnglishName(QString planetEnglishName) const;

	PlanetP searchMinorPlanetByEnglishName(QString planetEnglishName) const;

	//! Get the Planet object pointer for the Sun.
	PlanetP getSun() const {return sun;}

	//! Get the Planet object pointer for the Earth.
	PlanetP getEarth() const {return earth;}

	//! Get the Planet object pointer for Earth's moon.
	PlanetP getMoon() const {return moon;}

	//! Determine if a lunar eclipse is close at hand?
	bool nearLunarEclipse() const;

	//! Get the list of all the planet english names
	QStringList getAllPlanetEnglishNames() const;

	//! Get the list of all the planet localized names
	QStringList getAllPlanetLocalizedNames() const;

	//! Get the list of all the minor planet common english names
	QStringList getAllMinorPlanetCommonEnglishNames() const;

	//! Reload the planets
	void reloadPlanets();

	//! New 0.16: delete a planet from the solar system. Writes a warning to log if this is not a minor object.
	bool removeMinorPlanet(QString name);

	//! Determines relative amount of sun visible from the observer's position.
	double getEclipseFactor(const StelCore *core) const;

	//! Compute the position and transform matrix for every element of the solar system.
	//! @param dateJDE the Julian Day in JDE (Ephemeris Time or equivalent)	
	//! @param observerPlanet planet of the observer (Required for light travel time or aberration computation).
	void computePositions(double dateJDE, PlanetP observerPlanet);

	//! Get the list of all the bodies of the solar system.	
	const QList<PlanetP>& getAllPlanets() const {return systemPlanets;}
	//! Get the list of all the bodies of the solar system.
	const QList<PlanetP>& getAllMinorBodies() const {return systemMinorBodies;}
	//! Get the list of all minor bodies names.
	const QStringList getMinorBodiesList() const { return minorBodies; }

	//! Get lighttime corrected solar position (essential to draw the sun during solar eclipse and compute things like eclipse factor etc, until we get aberration working.)
	const Vec3d getLightTimeSunPosition() const { return lightTimeSunPosition; }

private slots:
	//! Called when a new object is selected.
	void selectedObjectChange(StelModule::StelModuleSelectAction action);

	//! Called when the sky culture is updated.
	//! Loads native names of planets for a given sky culture.
	//! @param skyCultureDir the name of the directory containing the sky culture to use.
	void updateSkyCulture(const QString& skyCultureDir);

	//! Called following StelMainView::reloadShadersRequested
	void reloadShaders();

	void setFlagEphemerisMarkers(bool b);
	bool getFlagEphemerisMarkers() const;

	void setFlagEphemerisHorizontalCoordinates(bool b);
	bool getFlagEphemerisHorizontalCoordinates() const;

	void setFlagEphemerisDates(bool b);
	bool getFlagEphemerisDates() const;

	void setFlagEphemerisMagnitudes(bool b);
	bool getFlagEphemerisMagnitudes() const;

	//! Called when a new Hips survey has been loaded by the hips mgr.
	void onNewSurvey(HipsSurveyP survey);

private:
	//! Search for SolarSystem objects which are close to the position given
	//! in earth equatorial position.
	//! @param v A position in earth equatorial position.
	//! @param core the StelCore object.
	//! @return a pointer to a StelObject if found, else Q_NULLPTR
	StelObjectP search(Vec3d v, const StelCore* core) const;

	//! Compute the transformation matrix for every elements of the solar system.
	//! observerPos is needed for light travel time computation.
	void computeTransMatrices(double dateJDE, const Vec3d& observerPos = Vec3d(0.));

	//! Draw a nice animated pointer around the object.
	void drawPointer(const StelCore* core);

	//! Load planet data from the Solar System configuration files.
	//! This function attempts to load every possible instance of the
	//! Solar System configuration files in the file paths, falling back if a
	//! given path can't be loaded.
	void loadPlanets();

	//! Load planet data from the given file
	bool loadPlanets(const QString& filePath);

	void recreateTrails();

	//! Calculate a color of Solar system bodies
	//! @param bV value of B-V color index
	unsigned char BvToColorIndex(float bV);

	//! Set flag which enables display of permanent orbits for objects
	// TODO: DOCUMENT what this really does, under which circumstances etc.
	void setFlagPermanentOrbits(bool b);

	//! Used to count how many planets actually need shadow information
	int shadowPlanetCount;
	PlanetP sun;
	PlanetP moon;
	PlanetP earth;

	//! Set selected planets by englishName.
	//! @param englishName The planet name or "" to select no planet
	void setSelected(const QString& englishName);
	//! Set selected object from its pointer.
	void setSelected(PlanetP obj);
	//! Get selected object's pointer.
	PlanetP getSelected(void) const {return selected;}
	//! The currently selected planet.
	PlanetP selected;

	// Separate Moon and minor body scale values. The latter make sense to zoom up and observe irregularly formed 3D objects like minor moons of the outer planets.
	// TBD: It may be wise to remove the sphereScale value from the Planet class: that is only used by the Moon.
	bool flagMoonScale;
	double moonScale;
	bool flagMinorBodyScale;
	double minorBodyScale;

	QFont planetNameFont;

	//! The amount of planet labels (between 0 and 10).
	double labelsAmount;

	//! List of all the bodies of the solar system.
	QList<PlanetP> systemPlanets;
	//! List of all the minor bodies of the solar system.
	QList<PlanetP> systemMinorBodies;

	// Master settings
	bool flagOrbits;
	bool flagLightTravelTime;
	bool flagUseObjModels;
	bool flagShowObjSelfShadows;

	//! The selection pointer texture.
	StelTextureSP texPointer;
	StelTextureSP texCircle;                    // The symbolic circle texture

	bool flagShow;
	bool flagPointer;                           // show red cross selection pointer?
	bool flagNativePlanetNames;                 // show native names for planets?
	bool flagTranslatedNames;                   // show translated names?
	bool flagIsolatedTrails;
	bool flagIsolatedOrbits;
	bool flagPlanetsOrbitsOnly;
	bool ephemerisMarkersDisplayed;
	bool ephemerisDatesDisplayed;
	bool ephemerisMagnitudesDisplayed;
	bool ephemerisHorizontalCoordinates;

	class TrailGroup* allTrails;
	QSettings* conf;
	LinearFader trailFader;
	Vec3f trailColor;
	Vec3f pointerColor;

	QHash<QString, QString> planetNativeNamesMap;
	QStringList minorBodies;

	Vec3d lightTimeSunPosition;			// when observing a solar eclipse, we need solar position 8 minutes ago.
							// Direct shift caused problems (LP:#1699648), circumvented with this construction.
	// 0.16pre observation GZ: this list contains pointers to all orbit objects,
	// while the planets don't own their orbit objects.
	// Would it not be better to hand over the orbit object ownership to the Planet object?
	// This list could then be removed.
	// In case this was originally intended to provide some fast access for time-dependent computation with the same JD,
	// note that we must also always compensate to light time travel, so likely each computation has to be done twice,
	// with current JDE and JDE-lightTime(distance).
	QList<Orbit*> orbits;           // Pointers on created elliptical orbits. 0.16pre: WHY DO WE NEED THIS???
};


#endif // SOLARSYSTEM_HPP
