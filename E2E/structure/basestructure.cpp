#include "basestructure.h"


#include "../dataelements/baseelement.h"


namespace E2E
{

	BaseStructure::BaseStructure()
	{
	}


	BaseStructure::~BaseStructure()
	{
		for(BaseElement* ele : rawDataVec)
			delete ele;
	}





}