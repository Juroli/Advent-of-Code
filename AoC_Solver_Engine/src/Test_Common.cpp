
#include "Test_Common.h"


TTestResult_Group::operator bool() const noexcept
{
	for (const auto& curr : m_LResults)
	{
		if (!curr)
		{
			return false;
		}
	}

	return true;
}

