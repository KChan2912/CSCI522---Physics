# CSCI522---Physics
## Implementing a rudimentary Physics Engine to handle Box vs Sphere Collisions as well as Gravity within a Custom Engine for USC's CSCI-522

In order to implement Box vs Sphere Collision, we first need to maintain a list of rigidbodies that have physics enabled. 
This can be done within *PhysicsManager.cpp/.h* as *m_physicsInstances*, which is an array of physicsComponents.  
Also remember to create methods that facilitate the addition of the PhysicsManager to the game environment. 
The Physics Component contains variables that describe the HitBox Type (Sphere or Box), the center of the Hitbox, which can be calculated using the AABB’s previously defined. 
If the hitbox is a Box type, we also store the corners of the AABB. 
We also store the worldTransform, the speed of the object (only the soldier’s is necessary for the homework). 
In order to implement gravity, a boolean variable that determines whether the soldier is on the ground or not is also present. 
The components can be initialised and attached within *GameObjectManager.cpp* and *SoldierNPC.cpp*.

**Calculating Collisions:**

For every object within the PhysicsManager, first update the WorldTransforms by referencing the SceneNode of the object.

Then for every object that is a sphere type (SoldierNPC);

First set the boolean hasFloor to false.

Then for every other object that is not a sphereHitbox, calculate the probable point of collision on the Box hitbox. 
This is done by creating a vector to the center of the sphere hitbox from the center of the Box hitbox. And then we essentially clamp that vector to the extent of the Box hitbox. 

Then we check if this point that we obtained is within the radius of the sphere with respect to the soldier. 
If it is, we know that collision has occurred and we can calculate the normals of the hitbox and pick the appropriate one to push the soldier back by. 
We can use the dot product of the normal with the vector from the center of the box to the sphere for this purpose.

**Gravity:**

As for gravity, we check if the soldier’s feet are colliding with a floor. 
Since the floor also has a hitbox of box type, we simply reuse the calculated point of collision above, but this time with the player’s feet. 
If there is a collision at the player’s feet, we can flip the bool to true, else we apply a downward force at the very end, after all possible collisions have been checked.
