#include "ManagedObject.h"

namespace ForgeEngine
{
	/*static*/ ObjectID ManagedObject::s_LastGivenID{};

	ManagedObject::ManagedObject() :
		m_ID(++s_LastGivenID)
	{
	}
}