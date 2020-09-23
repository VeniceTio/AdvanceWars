#include "unit.h"

int GetUnitIDFromChar(char p_unitChar)
{
	for (size_t i = 0; i < NB_UNIT_TYPE; i++)
	{
		if (p_unitChar == s_unitChar[i])
			return i;
	}

	return -1;
}
