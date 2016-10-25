#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H

#define dSINGLE
#include <ode/ode.h>
#include <engine/core/double3.h>
#include <engine/physics/physical.h>
#include <engine/physics/physicsgroup.h>

class PhysicsWorld{
private:

    /*physics world stuff for the fps*/
    static dWorldID worldID;
    static dSpaceID spaceID;
    static dJointGroupID contactGroup;
	static double stepSize;

    static void NearCallback (void *data, dGeomID o1, dGeomID o2);

    static void Init(){
        stepSize  = .01;
        worldID = dWorldCreate();
        spaceID = dHashSpaceCreate(0);
        contactGroup = dJointGroupCreate(0);
    }

public:


    PhysicsWorld();
    ~PhysicsWorld();


    static void Step();


    static void PhysicsSettings(VarMap settings);


    /*set the world settings, like bounciness, constant force mixing, gravity, etc.*/
    static double3 SetGravity(const double3 newGravity);


    /*create new 3d shapes of coolness*/
    static void NewBox(dBodyID &body,dGeomID &geom,double3 dimensions,double density,void* data);
    static void NewStaticPlane(dGeomID &geom,double3 direction,double offset,void* data);

    static PhysicsGroup* BuildPhysicsGroup(VarMap* groupSettings,void* data);


    static void GlMatrix(dBodyID body,float *matrix);



};
#endif // PHYSICS_WORLD_H
