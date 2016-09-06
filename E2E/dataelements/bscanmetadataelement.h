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
		struct BScanData
		{
			double x1 = 0.0;
			double y1 = 0.0;
			double x2 = 0.0;
			double y2 = 0.0;


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

	private:
		BScanData bscanData;
	};

}

