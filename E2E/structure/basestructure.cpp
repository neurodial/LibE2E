#include "basestructure.h"


#include "../dataelements/baseelement.h"
#include "../e2edata.h"


namespace E2E
{

	BaseStructure::BaseStructure()
	{
	}

	BaseStructure::BaseStructure(E2EData* parentData)
	: parentData(parentData)
	, createFromLoadedFileNum(parentData->getFilesLoaded())
	{
	}


	BaseStructure::~BaseStructure()
	{
		for(BaseElement* ele : rawDataVec)
			delete ele;
		
		for(StringListElement* ele : unknownStringListElement)
			delete ele;
	}





}
