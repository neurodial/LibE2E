#pragma once

#include <istream>
#include <vector>
#include <string>


#include "baseelement.h"

namespace E2E
{
	class MDbData;

	class StringListElement : public BaseElement
	{
	public:
		typedef std::vector<std::u16string> StringList;
		StringListElement(std::istream& stream, MDbData& data);
		virtual ~StringListElement();

		const std::u16string& getString(std::size_t pos) const   { return stringList.at(pos); }

		StringList::const_iterator begin() const                 { return stringList.begin(); }
		StringList::const_iterator end()   const                 { return stringList.end()  ; }

		std::size_t                size()  const                 { return stringList.size() ; }
		
	private:
		StringList stringList;
	};
}


