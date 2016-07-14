#pragma once

#include "basestructure.h"

#include <map>

namespace E2E
{

	template<typename Type, typename IndexType = int>
	class SubstructureTemplate : public BaseStructure
	{
	public:
		typedef std::pair<const IndexType, Type*>        SubstructurePair;
		typedef std::map<IndexType, Type*>               SubstructureMap;
		typedef typename SubstructureMap::iterator       SubstructureIterator;
		typedef typename SubstructureMap::const_iterator SubstructureCIterator;

		std::size_t subStructureElements() const                { return substructureMap.size();  }

		SubstructureCIterator begin() const                     { return substructureMap.begin(); }
		SubstructureCIterator end()   const                     { return substructureMap.end();   }
		std::size_t size()            const                     { return substructureMap.size();  }

	protected:
		virtual ~SubstructureTemplate()
		{
			for(SubstructurePair obj : substructureMap)
				delete obj.second;
		}

		Type& getAndInsert(IndexType id)
		{
			SubstructureIterator it = substructureMap.find(id);
			if(it == substructureMap.end())
			{
				std::pair<SubstructureIterator, bool> pit = substructureMap.emplace(id, new Type);
				if(pit.second == false)
					throw "SubstructureTemplate pit.second == false";
				return *((pit.first)->second);
			}
			return *(it->second);
		};


		SubstructureMap substructureMap;
	};


}
