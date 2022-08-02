
#include "ICondition.h"
#include "IIntegerVariable.h"

class ErrorCondition :
	public ICondition
{

public:
	ErrorCondition();
	modern_Boolean CheckCondition() override;
};
