#include "TestComponent.h"

#include "engine/math/Math.h"

namespace PapierKraft
{
	using namespace ForgeEngine;

	void TestComponent::OnUpdate(float dT) /*override*/
	{
		m_Owner->m_Transform->Rotate(180.f * dT, Vector3(0.f, 1.f, 0.f));
	}
}