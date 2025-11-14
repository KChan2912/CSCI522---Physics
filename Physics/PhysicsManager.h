#ifndef __PYENGINE_2_0_PhysManag
#define __PYENGINE_2_0_PhysManag

#define NOMINMAX
// API Abstraction
#include "PrimeEngine/APIAbstraction/APIAbstractionDefines.h"

// Outer-Engine includes
#include <assert.h>

// Inter-Engine includes
#include "PrimeEngine/MemoryManagement/Handle.h"
#include "PrimeEngine/PrimitiveTypes/PrimitiveTypes.h"
#include "../Events/Component.h"
#include "../Utils/Array/Array.h"
#include "../Scene/RootSceneNode.h"

#include "PhysicsComponent.h"

#include "PrimeEngine/Utils/Networkable.h"

// Sibling/Children includes
namespace PE {
	namespace Components {

		struct PhysicsManager : public Component//, public Networkable
		{
			PE_DECLARE_CLASS(PhysicsManager);
			//PE_DECLARE_NETWORKABLE_CLASS

				// Singleton ------------------------------------------------------------------

			// Constructor -------------------------------------------------------------
			PhysicsManager(PE::GameContext& context, PE::MemoryArena arena, Handle hMyself);
			virtual ~PhysicsManager() {}
			// Methods      ------------------------------------------------------------
			virtual void addDefaultComponents();

			void addPhysicsObject(Handle pHandle);//Stores PhysicsComponent to m_physicsInstances

			// Component ------------------------------------------------------------

			Array<PhysicsComponent*> m_physicsInstances;
			// Individual events -------------------------------------------------------
		};

	}; // namespace Components
}; // namespace PE
#endif


