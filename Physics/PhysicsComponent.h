#ifndef __PYENGINE_2_0_PhysComp
#define __PYENGINE_2_0_PhysComp

#define NOMINMAX
// API Abstraction
#include "PrimeEngine/APIAbstraction/APIAbstractionDefines.h"

// Outer-Engine includes
#include <assert.h>

// Inter-Engine includes
#include "PrimeEngine/MemoryManagement/Handle.h"
#include "PrimeEngine/PrimitiveTypes/PrimitiveTypes.h"
//#include "../Events/Component.h"
#include "../Utils/Array/Array.h"
#include "../Scene/RootSceneNode.h"
#include "../Scene/CameraManager.h"
#include "../Scene/MeshInstance.h"

#include "PrimeEngine/Events/Component.h"

//#include "../Events/Events.h"

#include "PrimeEngine/Utils/Networkable.h"

// Sibling/Children includes
namespace PE {
	namespace Components {

		struct PhysicsComponent : public Component
		{
			PE_DECLARE_CLASS(PhysicsComponent);

			enum HitBoxType //Hit Box type Assigned to each Physics Component upon Initializing
			{
				BOX = 1,
				SPHERE = 2,
			};
			PE_DECLARE_IMPLEMENT_EVENT_HANDLER_WRAPPER(do_UPDATE)
			virtual void do_UPDATE(PE::Events::Event* pEvt);
				

			// Constructor -------------------------------------------------------------
			PhysicsComponent(PE::GameContext& context, PE::MemoryArena arena, Handle hMyself, HitBoxType HBT);
			virtual ~PhysicsComponent() {}
			// Methods      ------------------------------------------------------------
			void getHitBox();
			virtual void addDefaultComponents();
			//Variables   --------------------------------------------------------------
			HitBoxType HBType; //HitBoxType
			Vector3 BoxMidPoint, //MidPoint for Sphere is Soldier Pos moved up by 1, Midpoint for Boxes is calculated.
				Corner1, Corner2, Corner3, Corner4, Corner5, Corner6, Corner7, Corner8;//BOX Type Corners
			Matrix4x4 WorldTrans; //WorldTransform of the Component
			float speed; //Speed of the Soldier//Can Be Used for other types too//Only Soldier Necessary for now
			float Fallspeed;//Speed of Falling
			bool hasFloor;//Whether Sphere Has a floor or not
			SceneNode* MeshSN; //Passed only for BoxType/StaticMesh
			
		};

	}; // namespace Components
}; // namespace PE
#endif

