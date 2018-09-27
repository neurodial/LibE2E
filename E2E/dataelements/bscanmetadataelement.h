/*
 * Copyright (c) 2018 Kay Gawlik <kaydev@amarunet.de> <kay.gawlik@beuth-hochschule.de> <kay.gawlik@charite.de>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#pragma once

#include <istream>
#include <vector>

#include "baseelement.h"



namespace E2E
{
	class MDbData;

	class BScanMetaDataElement : public BaseElement
	{
	public:
		enum class ScanType { Unknown, Line, Star, Circle };

		struct BScanData
		{
			double x1 = 0.0;
			double y1 = 0.0;
			double x2 = 0.0;
			double y2 = 0.0;

			double centerX = 0.0;
			double centerY = 0.0;

			ScanType scantype = ScanType::Unknown;

			uint32_t imgSizeX;
			uint32_t imgSizeY;

			double   scaleY; // ?

			uint32_t imgSizeWidth; // redunanz?
			uint32_t numImages;
			uint32_t aktImage;
			uint64_t acquisitionTime;
			uint32_t numAve;
			float    imageQuality;
		};

		BScanMetaDataElement(std::istream& stream, MDbData& data);
		~BScanMetaDataElement();

		double getX1() const                                     { return bscanData.x1; }
		double getY1() const                                     { return bscanData.y1; }
		double getX2() const                                     { return bscanData.x2; }
		double getY2() const                                     { return bscanData.y2; }

		double   getScaleY         () const                      { return bscanData.scaleY         ; }
		uint32_t getImgSizeX       () const                      { return bscanData.imgSizeX       ; }
		uint32_t getImgSizeY       () const                      { return bscanData.imgSizeY       ; }
		uint32_t getImgSizeWidth   () const                      { return bscanData.imgSizeWidth   ; }
		uint32_t getNumImages      () const                      { return bscanData.numImages      ; }
		uint32_t getAktImage       () const                      { return bscanData.aktImage       ; }

		uint64_t getAcquisitionTime() const                      { return bscanData.acquisitionTime; }
		uint32_t getNumAve         () const                      { return bscanData.numAve         ; }

		float    getImageQuality   () const                      { return bscanData.imageQuality   ; }

		ScanType getScanType       () const                      { return bscanData.scantype       ; }
		double   getCenterX        () const                      { return bscanData.centerX        ; }
		double   getCenterY        () const                      { return bscanData.centerY        ; }

	private:
		BScanData bscanData;
	};

}

