#include "physics_world.h"


dWorldID PhysicsWorld::worldID;
dSpaceID PhysicsWorld::spaceID;
dJointGroupID PhysicsWorld::contactGroup;
double PhysicsWorld::stepSize  = .01;




PhysicsWorld::PhysicsWorld(){
    dInitODE();
    Init();
}

PhysicsWorld::~PhysicsWorld(){
    //dJointGroupDestroy (contactGroup);
    //dSpaceDestroy(spaceID);
    //dWorldDestroy(worldID);
    dCloseODE();
}

void PhysicsWorld::Step(){
    // remove all contact joints
    dJointGroupEmpty (contactGroup);
    // find collisions and add contact joints
    dSpaceCollide (spaceID,0,&PhysicsWorld::NearCallback);
    // step the simulation
    dWorldQuickStep(worldID,stepSize);
}

void PhysicsWorld::NearCallback (void *data, dGeomID o1, dGeomID o2) {
    /*see if any of the objects that are colliding have info about
    them that can be checked.*/
    Physical* nA = (Physical*)dGeomGetData(o1);
    Physical* nB = (Physical*)dGeomGetData(o2);
    /*if both either of the geoms doesn't have a physical, or both
    physicals are static or both physicals are virtual, bail from
    the collision check.

    20150924 - If one of the geoms is static or virtual and the other
    geom is also static or virtual, don't count the collision*/
    if(!nA || !nB
        || (nA->Static() && nB->Static())
        //|| ((nA->isStatic() || nA->isVirtual()) && (nB->isStatic() || nB->isVirtual()))
    ){
        return;
    }

    /*check if either of the objects is not grouped, and if they are both
    grouped, make sure they are not in the same group*/
    if(!nA->Grouped() || !nB->Grouped() || nA->Group() != nB->Group()){

        /*check to see if the two physical objects contain contact information
        that should be used to determine how the contact point behaves*/
        dSurfaceParameters* csA = nA->SurfaceParameters(o1);
        dSurfaceParameters* csB = nB->SurfaceParameters(o2);
        dContact contact;
        if(!csA && !csB){ //if neither geom has surface properties
            contact.surface.mode = dContactBounce | dContactSoftCFM;// | dContactFDir1;//dContactSlip1  | dContactSlip2 ;
            contact.surface.mu = 2;
            contact.surface.bounce = 0.2;
            contact.surface.bounce_vel = 0.6;
            contact.surface.soft_cfm = 0.005;
        } else if(csA && !csB){ //if only geom A has surface properties
            contact.surface = *csA;
        } else if(csB && !csA){ //if only geom B has surface properties
            contact.surface = *csB;
        } else{  //if both geoms have surface properties
            cout << "warning, no logic implimented if both objects have surface properties. Fix this shit!\n";
        }
        dContactGeom contacts[8];
        if (int numc = dCollide (o1,o2,8,contacts,sizeof(dContactGeom))) {
            dBodyID b1 = dGeomGetBody(o1);
            dBodyID b2 = dGeomGetBody(o2);
            /*make sure that both physicals are not virtual before
            generating contact points*/
            if(!nA->Virtual() && !nB->Virtual()){
                for(int i=0;i<numc;i++){
                    contact.geom = contacts[i];
                    dJointID c = dJointCreateContact (worldID,contactGroup,&contact);
                    dJointAttach (c,b1,b2);
                }//end of looping through the collision points of the two bodies
            }//end of if both physicals are not virtual
            nA->AddCollision(new Collision(nB,contacts,numc));
            nB->AddCollision(new Collision(nA,contacts,numc));
        }//end of if both geoms have a physical that they are attached to
    }//end of if the two geometries collided
    else {
        cout << "neither geom is grouped\n";
    }
}


void PhysicsWorld::PhysicsSettings(VarMap settings){
    cout << " - set physics settings\n";
    if(settings.IsSet("physics.gravity")){
        List<double> gravity = settings.get<List<double> >("physics.gravity");
        if(gravity.GetCount() == 3){
            SetGravity(double3(gravity[0],gravity[1],gravity[2]));
            //dWorldSetGravity(worldID,gravity[0],gravity[1],gravity[2]);
        } else if (gravity.GetCount() == 1){
            //dWorldSetGravity(worldID,0,gravity[0],0);
        } else {
            cout << "Incorrect number of physics.gravity values. Should be 1d or 3d i.e. gravity -9.81 or gravity 0,-9.81,0\n";
        }
    }


    if(settings.IsSet("physics.step-size")){
        //dReal stepSize = (float)settings.get<double>("physics.step-size");
    }

    /*
    dWorldSetERP (worldID, 0.10);	//the springiness of everything
    dWorldSetCFM (worldID, 0.02);//3e-5 (old) //the softness of everything
    dWorldSetAutoDisableFlag(worldID,true);
    dWorldSetQuickStepNumIterations (worldID, 10);
    dWorldSetContactMaxCorrectingVel (worldID, 5);
    dWorldSetAutoDisableLinearThreshold(worldID,0.000001f);
    dWorldSetAutoDisableAngularThreshold(worldID,0.0000001f);
    dWorldSetAutoDisableTime(worldID,.25);

*/
}


double3 PhysicsWorld::SetGravity(const double3 newGravity){
    dWorldSetGravity(worldID,newGravity.x,newGravity.y,newGravity.z);
    return newGravity;
}


/*builds a box of a set size with a set density
and adds the body to the world and the geom
to the space, then returns a reference to that
body.

The last variable is a reference to the node that the
box will be a part of. This is required so that when
collisions are performed, the engine can determine what
to do with the body. If it is set to null, no callback
will be performed.*/
void PhysicsWorld::NewBox(dBodyID &body,dGeomID &geom,double3 dimensions,double density,void* data){
    body = dBodyCreate(worldID);
    dMass m;
    dMassSetZero(&m);
    dMassSetBox(&m, density, dimensions.x, dimensions.y, dimensions.z);
    dBodySetMass(body, &m);
    geom = dCreateBox(spaceID,dimensions.x,dimensions.y,dimensions.z);
    dGeomSetBody (geom, body);
    dGeomSetData(geom,data);
}
void PhysicsWorld::NewStaticPlane(dGeomID &geom,double3 direction,double offset,void* data){
    direction.normalize();
    geom = dCreatePlane (spaceID,direction.x,direction.y,direction.z,offset);
    dGeomSetData(geom,data);
}


PhysicsGroup* PhysicsWorld::BuildPhysicsGroup(VarMap* groupSettings,void* data){
        PhysicsGroup* pGroup = new PhysicsGroup();
        List<string> groupNames = groupSettings->GroupNames();
        for(int i=0;i<groupNames.GetCount();i++){
            VarMap props = groupSettings->GetGroup(groupNames[i]);
            dGeomID geom;
            dBodyID body;
            double density = 0;
            if(props.IsSet("density")){
                density = props.get<double>("density");
            }
            if(props.IsSet("geometry")){
                string shape = props.get<string>("geometry");
                if(shape == "box"){

                    double3 dimensions;
                    if(props.IsSet("lengths")){
                        List<double> lengths = props.get<List<double> >("lengths");
                        dimensions = double3(lengths[0],lengths[1],lengths[2]);
                    } else {
                        dimensions = double3(1,1,1);
                    }
                    NewBox(body,geom,dimensions,density,data);
                }//end of if is a box
            }


            if(body){
                if(props.IsSet("position")){
                    double3 pos = props.get<double3>("position");
                    dBodySetPosition(body,pos.x,pos.y,pos.z);
                }
                pGroup->body.push(body,groupNames[i]);
            }

            if(geom){
                pGroup->geom.push(geom,groupNames[i]);
            }


        }

        return pGroup;
    }


void PhysicsWorld::GlMatrix(dBodyID body,float *matrix){
    const dReal *R = dBodyGetRotation(body);
    const dReal *pos = dBodyGetPosition(body);
    matrix[0]=R[0];
    matrix[1]=R[4];
    matrix[2]=R[8];
    matrix[3]=0;
    matrix[4]=R[1];
    matrix[5]=R[5];
    matrix[6]=R[9];
    matrix[7]=0;
    matrix[8]=R[2];
    matrix[9]=R[6];
    matrix[10]=R[10];
    matrix[11]=0;
    matrix[12]=pos[0];
    matrix[13]=pos[1];
    matrix[14]=pos[2];
    matrix[15]=1;
}

