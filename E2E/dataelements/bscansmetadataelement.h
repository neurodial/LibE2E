#pragma once

#include <istream>
#include <vector>

#include "baseelement.h"



namespace E2E
{
	class MDbData;

	class BScansMetaDataElement : public BaseElement
	{
	public:
		struct BScansData
		{
			double x1;
			double y1;
			double x2;
			double y2;
		};
		typedef std::vector<BScansData> MetaDataList;

		BScansMetaDataElement(std::istream& stream, MDbData& data);
		~BScansMetaDataElement();

		const MetaDataList& getMetaData() const                  { return dataVec; }
		MetaDataList::const_iterator begin() const               { return dataVec.begin(); }
		MetaDataList::const_iterator end() const                 { return dataVec.end();   }
	private:
		MetaDataList dataVec;
	};

}

