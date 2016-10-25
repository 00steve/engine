#include "physical_single_body.h"



void PhysicalSingleBody::OnSetSettings(){
    Physical::OnSetSettings();
    cout << "physical single body settings : \n";
    cout << " - asset id " << &Assets() << endl;
    if(Settings().IsSet("position")){
        List<double> pos = Settings().get<List<double> >("position");
        if(pos.GetCount() == 3){
            position = double3(pos[0],pos[1],pos[2]);
        }

    }

}


PhysicalSingleBody::PhysicalSingleBody() :
    trackFloor(false),
    floorAngle(0)
{
}

PhysicalSingleBody::~PhysicalSingleBody()
{
    #if DEBUG_DELETES
        cout << " single body >";
    #endif
    //Ode::RemoveGeom(geom);
    //Ode::RemoveBody(body);
    //delete gl_matrix; //falls out of scope, no "new", so doesn't need delete
}


void PhysicalSingleBody::Update(){
    if(body && (active = dBodyIsEnabled(body))){
        PhysicsWorld::GlMatrix(body,gl_matrix);
        //const dReal *tPos = dBodyGetPosition(body);
        //position.x = tPos[0];
        //position.y = tPos[1];
        //position.z = tPos[2];
    }
    Physical::Update();
}

	/*bool handleMessage(node_message* m){
        switch(m->code){
        case MESSAGE_PROJECTILE_IMPACT:
            cout << this->getName() << " hit with bullet!\n";
            return true;
        }
        return physical::handleMessage(m);
	}*/

bool PhysicalSingleBody::HandleMessage(NodeMessage m){
    /*
    switch(m->code){
    case MESSAGE_PROJECTILE_IMPACT:
        Impact* i = (Impact*)m.data;
        AddForceAtPoint(i->velocity * i->mass * .25f, i->position);
        return true;
    case MESSAGE_SET_PHYSICS_SPACE:

        return true;
    case MESSAGE_UNSET_PHYSICS_SPACE:
    }
    */
    return Physical::HandleMessage(m);
}

void PhysicalSingleBody::Kinematic(){
    dBodySetKinematic(body);
}
void PhysicalSingleBody::Dynamic(){
    dBodySetDynamic(body);
}


void PhysicalSingleBody::LinearDampening(double scale){
    //dBodySetLinearDamping(body,scale);
}

void PhysicalSingleBody::AngularDampening(double scale){
    dBodySetAngularDamping(body,scale);
}

void PhysicalSingleBody::DisableBodies(){
    dBodyDisable(body);
}

double3 PhysicalSingleBody::Position(){ return position; }

void PhysicalSingleBody::Position(double3 newPosition){
    dBodySetPosition(body,newPosition.x,newPosition.y,newPosition.z);
}

void PhysicalSingleBody::ShiftPosition(const double3 offset){
    //dBodySetPosition(body, position.x+offset.x, position.y+offset.y, position.z+offset.z);

    //ode::glMatrix(body,gl_matrix);
    //const dReal *tPos = dBodyGetPosition(body);
    //position.x = tPos[0];
    //position.y = tPos[1];
    //position.z = tPos[2];
}

/**\brief adds a force at the COG of an object.

The force is added at the COG(center of gravity)
of the object. This force causes acceleration, but
not rotational change because it is acting on the
center of gravity. If you want to simulate push or
some type of force acting on an object that could
cause velocity or rotational change, use the
addForceAtPoint() function**/
void PhysicalSingleBody::AddForce(const double3 force){
    dBodyAddForce(body,force.x,force.y,force.z);
}

/**\brief adds a force to the object at a specific point.

This is useful for a collision or simulating a force acting
on an object somewhere on the surface.**/
void PhysicalSingleBody::AddForceAtPoint(const double3 force,const double3 origin){
    dBodyAddForceAtPos(body,force.x,force.y,force.z,origin.x,origin.y,origin.z);
    Enabled(true);
}

void PhysicalSingleBody::Velocity(const double3 velocity){
    dBodySetLinearVel(body,velocity.x,velocity.y,velocity.z);
}

bool PhysicalSingleBody::Enabled(){ return dBodyIsEnabled(body); }
bool PhysicalSingleBody::Enabled(const bool enabled){
    if(enabled){
        dBodyEnable(body);
    } else {
        dBodyDisable(body);
    }
    return enabled;
}

