// APIAbstraction
#include "PrimeEngine/APIAbstraction/APIAbstractionDefines.h"

// Outer-Engine includes

// Inter-Engine includes
#include "../Lua/LuaEnvironment.h"

// Sibling/Children includes
#include "PhysicsComponent.h"
#include "PhysicsManager.h"


#include "PrimeEngine/Scene/Skeleton.h"
#include "PrimeEngine/Scene/MeshInstance.h"
#include "PrimeEngine/Scene/SkeletonInstance.h"
#include "PrimeEngine/Scene/DebugRenderer.h"

namespace PE {
	namespace Components {

		using namespace PE::Events;

		PE_IMPLEMENT_CLASS1(PhysicsComponent, Component);

		// Singleton ------------------------------------------------------------------

		// Constructor -------------------------------------------------------------
		PhysicsComponent::PhysicsComponent(PE::GameContext& context, PE::MemoryArena arena, Handle hMyself, HitBoxType HBT)
			: Component(context, arena, hMyself)
		{
			HBType = HBT;
		}

		// Methods      ------------------------------------------------------------
		void PhysicsComponent::addDefaultComponents()
		{
			Component::addDefaultComponents();
			_addStaticMethodToHandlerQueue(Event_UPDATE::GetClassId(), &PhysicsComponent::do_UPDATEwrapper);
		}
		void PhysicsComponent::getHitBox()
		{
			//passed mesh 
			if (HBType == SPHERE)
			{	
				BoxMidPoint = Vector3(0,1,0);
			}
			if (HBType == BOX)
			{
				MeshInstance* pmesh = MeshSN->getFirstComponent<MeshInstance>();
				Corner1 = pmesh->aabbCorners[0];// THIS IS MIN X Y Z I HOPE
				Corner2 = pmesh->aabbCorners[2];
				Corner3 = pmesh->aabbCorners[4];
				Corner4 = pmesh->aabbCorners[3];
				Corner5 = pmesh->aabbCorners[6];
				Corner6 = pmesh->aabbCorners[5];
				Corner7 = pmesh->aabbCorners[7];
				Corner8 = pmesh->aabbCorners[1];//THIS IS MAX X Y Z I HOPE

				BoxMidPoint = (Corner1 + Corner8) / 2;
			}
			

		}
		void PhysicsComponent::do_UPDATE(PE::Events::Event* pEvt)
		{
			
			//DEBUG DRAW FOR HIT BOXES
			PhysicsManager* PhysManag = m_pContext->getPhysicsManager();
			for (int i = 0; i<PhysManag->m_physicsInstances.m_size; i++)
			{
				//Getting WorldTransforms
				if (PhysManag->m_physicsInstances[i]->HBType == SPHERE)
				{
					PE::Handle hParent = getFirstParentByType<Component>();
					SceneNode* pSN = hParent.getObject<Component>()->getFirstComponent<SceneNode>();

					PhysManag->m_physicsInstances[i]->WorldTrans = pSN->m_base;
					

				}
				if (PhysManag->m_physicsInstances[i]->HBType == BOX) {
					PhysManag->m_physicsInstances[i]->WorldTrans = PhysManag->m_physicsInstances[i]->MeshSN->m_base;

				}

				//DebugRenderer
				if (PhysManag->m_physicsInstances[i]->HBType == PhysicsComponent::HitBoxType::SPHERE)
				{
					
					Matrix4x4 base = PhysManag->m_physicsInstances[i]->WorldTrans;
					Vector3 target = base * Vector3(0.5, 1, 0);
					Vector3 pos = base * Vector3(-0.5, 1, 0);
					Vector3 color(1.0f, 0, 1.0f);
					Vector3 linepts[] = { pos, color, target, color };

					DebugRenderer::Instance()->createLineMesh(false, base, &linepts[0].m_x, 2, 1);

					target = base * Vector3(0, 1, 0.5);
					pos = base * Vector3(0, 1, -0.5);

					linepts[0] = pos;
					linepts[2] = target;
					DebugRenderer::Instance()->createLineMesh(false, base, &linepts[0].m_x, 2, 1);


				}
					else if (PhysManag->m_physicsInstances[i]->HBType == PhysicsComponent::HitBoxType::BOX)
					{
						
						Matrix4x4 base = PhysManag->m_physicsInstances[i]->WorldTrans;
						Vector3 target = base * PhysManag->m_physicsInstances[i]->BoxMidPoint;
						Vector3 pos = base * PhysManag->m_physicsInstances[i]->Corner1;
						Vector3 color(1.0f, 0, 0);
						Vector3 linepts[] = { pos, color, target, color };
						/*
						DebugRenderer::Instance()->createLineMesh(false, base, &linepts[0].m_x, 2, 1);

						 target = base * PhysManag->m_physicsInstances[i]->BoxMidPoint;
						 pos = base * PhysManag->m_physicsInstances[i]->Corner2;
						 linepts[0] = pos;
						 linepts[2] = target;

						DebugRenderer::Instance()->createLineMesh(false, base, &linepts[0].m_x, 2, 1);
						 target = base * PhysManag->m_physicsInstances[i]->BoxMidPoint;
						 pos = base * PhysManag->m_physicsInstances[i]->Corner3;
						 linepts[0] = pos;
						 linepts[2] = target;
						

						DebugRenderer::Instance()->createLineMesh(false, base, &linepts[0].m_x, 2, 1);
						 target = base * PhysManag->m_physicsInstances[i]->BoxMidPoint;
						 pos = base * PhysManag->m_physicsInstances[i]->Corner4;
						 linepts[0] = pos;
						 linepts[2] = target;

						DebugRenderer::Instance()->createLineMesh(false, base, &linepts[0].m_x, 2, 1);
						 target = base * PhysManag->m_physicsInstances[i]->BoxMidPoint;
						 pos = base * PhysManag->m_physicsInstances[i]->Corner5;
						 linepts[0] = pos;
						 linepts[2] = target;

						DebugRenderer::Instance()->createLineMesh(false, base, &linepts[0].m_x, 2, 1);
						 target = base * PhysManag->m_physicsInstances[i]->BoxMidPoint;
						 pos = base * PhysManag->m_physicsInstances[i]->Corner6;
						 linepts[0] = pos;
						 linepts[2] = target;

						DebugRenderer::Instance()->createLineMesh(false, base, &linepts[0].m_x, 2, 1);
						 target = base * PhysManag->m_physicsInstances[i]->BoxMidPoint;
						 pos = base * PhysManag->m_physicsInstances[i]->Corner7;
						 linepts[0] = pos;
						 linepts[2] = target;

						DebugRenderer::Instance()->createLineMesh(false, base, &linepts[0].m_x, 2, 1);

						 target = base * PhysManag->m_physicsInstances[i]->BoxMidPoint;
						 pos = base * PhysManag->m_physicsInstances[i]->Corner8;
						 linepts[0] = pos;
						 linepts[2] = target;
						DebugRenderer::Instance()->createLineMesh(false, base, &linepts[0].m_x, 2, 1);*/
					}
			}

			
				
			if (HBType == SPHERE)
			{
				//Start Checks For Collision Of Sphere VS Box
				//For Each Physics Component in the Physics Manager
				//Set hasFloor To False By Default
				hasFloor = false;
				for (int i = 0; i < PhysManag->m_physicsInstances.m_size; i++)
				{
					PhysicsComponent* curComp = PhysManag->m_physicsInstances[i];
					//If the Obtained Component is a BOX Type
					if (curComp->HBType == PhysicsComponent::HitBoxType::BOX)
					{
						//Obtain Necessary Values Related to the Colliders
						Matrix4x4 WorldTransOfBox = curComp->WorldTrans;
						Vector3 MinXYZ = curComp->Corner1;
						Vector3 MaxXYZ = curComp->Corner8;
						Vector3 Mid = WorldTransOfBox * curComp->BoxMidPoint;
						Vector3 HalfWidth = Vector3((MaxXYZ.m_x - MinXYZ.m_x) / 2, (MaxXYZ.m_y - MinXYZ.m_y) / 2, (MaxXYZ.m_z - MinXYZ.m_z) / 2);
						Vector3 CurrentPosOfSphere = WorldTrans * (BoxMidPoint);// +(DirectionObt * DistAllowed));
						Vector3 DifferenceBWSphereBox = CurrentPosOfSphere - Mid;
						//Calculate the Closest Probable Point of Collision
						Vector3 CalculatedClosestPointOnBox = Mid;
						for (int i = 0; i < 3; i++)
						{
							Vector3 Axis = Vector3(WorldTransOfBox.m[0][i], WorldTransOfBox.m[1][i], WorldTransOfBox.m[2][i]);
							Axis.normalize();
							//Distance of Sphere from Middle of Hit Box On Axis
							float dist = DifferenceBWSphereBox.dotProduct(Axis);
							if (dist > HalfWidth.m_values[i])
							{
								dist = HalfWidth.m_values[i];
							}
							if (dist < -HalfWidth.m_values[i])
							{
								dist = -HalfWidth.m_values[i];
							}

							CalculatedClosestPointOnBox += dist * Axis;
						}
							
						//Drawing the Line Between the Closest Point of Probable Collision and the Midpoint of The Box
						Matrix4x4 base = WorldTransOfBox;
						Vector3 target = CalculatedClosestPointOnBox;
						Vector3 pos = Mid;
						Vector3 color(1.0f, 0, 1.0f);
						Vector3 linepts[] = { pos, color, target, color };
						DebugRenderer::Instance()->createLineMesh(false, base, &linepts[0].m_x, 2, 1);

						//Check To See if there Actually is Collision
						if ((CurrentPosOfSphere - CalculatedClosestPointOnBox).lengthSqr() < 0.1f/*radius^2*/)
						{
							PEINFO("Collision HAS OCCURED!!!!!!!!\n");
							//Generate Necessary Planes for the Box Collider and Store the Normal
							
							//Front Plane ->1->2->7
							Vector3 p0 = WorldTransOfBox * curComp->Corner1;
							Vector3 p1 = WorldTransOfBox * curComp->Corner2;
							Vector3 p2 = WorldTransOfBox * curComp->Corner7;
							Vector3 FrontPlaneNormal = (p1 - p0).crossProduct(p2 - p1);
							FrontPlaneNormal.normalize();
							Vector3 FrontPlanePoint = p0;

							//Right Plane ->4->5->2
							p0 = WorldTransOfBox * curComp->Corner4;
							p1 = WorldTransOfBox * curComp->Corner5;
							p2 = WorldTransOfBox * curComp->Corner2;
							Vector3 RightPlaneNormal = (p1 - p0).crossProduct(p2 - p1);
							RightPlaneNormal.normalize();
							Vector3 RightPlanePoint = p0;

							//Back Plane  ->6->8->5
							p0 = WorldTransOfBox * curComp->Corner6;
							p1 = WorldTransOfBox * curComp->Corner8;
							p2 = WorldTransOfBox * curComp->Corner5;
							Vector3 BackPlaneNormal = (p1 - p0).crossProduct(p2 - p1);
							BackPlaneNormal.normalize();
							Vector3 BackPlanePoint = p0;

							//Left Plane  ->3->7->8
							p0 = WorldTransOfBox * curComp->Corner3;
							p1 = WorldTransOfBox * curComp->Corner7;
							p2 = WorldTransOfBox * curComp->Corner8;
							Vector3 LeftPlaneNormal = (p1 - p0).crossProduct(p2 - p1);
							LeftPlaneNormal.normalize();
							Vector3 LeftPlanePoint = p0;

							//Top Plane   ->2->5->8
							p0 = WorldTransOfBox * curComp->Corner2;
							p1 = WorldTransOfBox * curComp->Corner5;
							p2 = WorldTransOfBox * curComp->Corner8;
							Vector3 TopPlaneNormal = (p1 - p0).crossProduct(p2 - p1);
							TopPlaneNormal.normalize();
							Vector3 TopPlanePoint = p0;
							
							//Bottom Plane ->3->6->4
							p0 = WorldTransOfBox * curComp->Corner3;
							p1 = WorldTransOfBox * curComp->Corner6;
							p2 = WorldTransOfBox * curComp->Corner4;
							Vector3 BottomPlaneNormal = (p1 - p0).crossProduct(p2 - p1);
							BottomPlaneNormal.normalize();
							Vector3 BottomPlanePoint = p0;

							//Check Which Plane the Point of Collision is on, and store the Normal as the Modifier

							Vector3 PushBack;
							if ((CalculatedClosestPointOnBox - FrontPlanePoint).dotProduct(FrontPlaneNormal) >= -0.01f && (CalculatedClosestPointOnBox - FrontPlanePoint).dotProduct(FrontPlaneNormal) <= 0.01f)
							{
								PushBack = FrontPlaneNormal;
								
							}
							else if ((CalculatedClosestPointOnBox - RightPlanePoint).dotProduct(RightPlaneNormal) >= -0.01f && (CalculatedClosestPointOnBox - RightPlanePoint).dotProduct(RightPlaneNormal) <= 0.01f)
							{
								PushBack = RightPlaneNormal;
							}
							else if ((CalculatedClosestPointOnBox - BackPlanePoint).dotProduct(BackPlaneNormal) >= -0.01f && (CalculatedClosestPointOnBox - BackPlanePoint).dotProduct(BackPlaneNormal) <= 0.01f)
							{
								PushBack = BackPlaneNormal;
							}
							else if ((CalculatedClosestPointOnBox - LeftPlanePoint).dotProduct(LeftPlaneNormal) >= -0.01f && (CalculatedClosestPointOnBox - LeftPlanePoint).dotProduct(LeftPlaneNormal) <= 0.01f)
							{
								PushBack = LeftPlaneNormal;
							}
							else if ((CalculatedClosestPointOnBox - TopPlanePoint).dotProduct(TopPlaneNormal) >= -0.01f && (CalculatedClosestPointOnBox - TopPlanePoint).dotProduct(TopPlaneNormal) <= 0.01f)
							{
								PushBack = TopPlaneNormal;
							}
							else if ((CalculatedClosestPointOnBox - BottomPlanePoint).dotProduct(BottomPlaneNormal) >= -0.01f && (CalculatedClosestPointOnBox - BottomPlanePoint).dotProduct(BottomPlaneNormal) <= 0.01f)
							{
								PushBack = BottomPlaneNormal;
							}
							//Check If PushBack is in direction of the Colliding Sphere
							if (DifferenceBWSphereBox.dotProduct(PushBack) < 0)
							{
								PushBack = PushBack * -1;
							}

							//Obtain The SceneNode of the Colliding Sphere
							PE::Handle hParent = getFirstParentByType<Component>();
							SceneNode* pSN = hParent.getObject<Component>()->getFirstComponent<SceneNode>();
							//Apply the PushBack to the SceneNode Obtained, and also Obtain the Framtime to calculate allowed Disp.
							Event_UPDATE* pRealEvt = (Event_UPDATE*)(pEvt);
							
							float allowedDisp = speed * pRealEvt->m_frameTime;
							Vector3 CurrentPositionOfSN = pSN->m_base.getPos();
							pSN->m_base.setPos(CurrentPositionOfSN + PushBack*allowedDisp);
						}						
						//Check Soldier's Feet for Floor
						PE::Handle hParent = getFirstParentByType<Component>();
						SceneNode* pSN = hParent.getObject<Component>()->getFirstComponent<SceneNode>();
						Vector3 CurrentPosOfSoldier = pSN->m_base.getPos();
						if ((CurrentPosOfSoldier - CalculatedClosestPointOnBox).lengthSqr() < 0.1f && (CurrentPosOfSoldier - CalculatedClosestPointOnBox).lengthSqr() > -0.1f)
						{
							Fallspeed = speed;
							hasFloor = true;
						}
						
					}

				}
			}

			//If Soldier has No Floor

			if (HBType == SPHERE && !hasFloor)
			{
				Vector3 Gravity = Vector3(0.0f, -1.5f, 0.0f);
				Event_UPDATE* pRealEvt = (Event_UPDATE*)(pEvt);
				Fallspeed = Fallspeed + (4.5f*pRealEvt->m_frameTime);//Allowed increase in speed per frame.
				if (Fallspeed > 9.5)
				{
					Fallspeed = 9.5;
				}
				//Obtain The SceneNode of the Colliding Sphere
				PE::Handle hParent = getFirstParentByType<Component>();
				SceneNode* pSN = hParent.getObject<Component>()->getFirstComponent<SceneNode>();

				//Apply the Gravity to the SceneNode Obtained, and also Obtain the Frametime to calculate allowed Disp.
				
				float allowedDisp = Fallspeed * pRealEvt->m_frameTime;
				Vector3 CurrentPositionOfSN = pSN->m_base.getPos();
				pSN->m_base.setPos(CurrentPositionOfSN + Gravity * (allowedDisp * 1.0));

			}
		}
				
	}; // namespace Components
}; //namespace PE
