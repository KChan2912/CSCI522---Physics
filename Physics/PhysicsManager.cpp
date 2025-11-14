// APIAbstraction
#include "PrimeEngine/APIAbstraction/APIAbstractionDefines.h"

// Outer-Engine includes

// Inter-Engine includes
#include "../Lua/LuaEnvironment.h"

// Sibling/Children includes
#include "PhysicsManager.h"
#include "PhysicsComponent.h"


#include "PrimeEngine/Scene/Skeleton.h"
#include "PrimeEngine/Scene/MeshInstance.h"
#include "PrimeEngine/Scene/SkeletonInstance.h"
#include "PrimeEngine/Scene/DebugRenderer.h"

namespace PE {
	namespace Components {

		using namespace PE::Events;

		PE_IMPLEMENT_CLASS1(PhysicsManager, Component);

		// Singleton ------------------------------------------------------------------

		// Constructor -------------------------------------------------------------
		PhysicsManager::PhysicsManager(PE::GameContext& context, PE::MemoryArena arena, Handle hMyself)
			: Component(context, arena, hMyself),
			m_physicsInstances(context, arena, 512)
		{
		}

		// Methods      ------------------------------------------------------------
		void PhysicsManager::addDefaultComponents()
		{
			Component::addDefaultComponents();

			addComponent(m_pContext->getLuaEnvironment()->getHandle());
		}

		void PhysicsManager::addPhysicsObject(Handle pHandle)
		{
			m_physicsInstances.add(pHandle.getObject<PhysicsComponent>());
		}

	}; // namespace Components
}; //namespace PE
