#include "marker.h"


string Marker::geometry = "sphere";


void Marker::OnSetSettings(){
    cout << ">marker";
    PhysicalSingleBody::OnSetSettings();
    Virtual(true);
    Static(true);
}


bool Marker::HandleMessage(NodeMessage message){
    switch(message.code){
    case MESSAGE_REGISTER_PHYSICS_OFFER: {
        VarMap *physics = new VarMap();
        physics->Add<string>(&geometry,"sphere.geometry");
        physics->Add<double>(&radius,"sphere.radius");
        physics->Add<double>(&density,"sphere.density");
        physics->Add<double3>(&position,"sphere.position");
        physics->Add<double3>(&velocity,"sphere.velocity");
        CreateAndSendMessage(message.sender,MESSAGE_REGISTER_PHYSICS_REQUEST,(void*)physics);
        return true;
        }

    case MESSAGE_REGISTER_PHYSICS_FINISHED: {
        PhysicsGroup *pGroup = (PhysicsGroup*) message.data;
        body = pGroup->body["sphere"];
        geom = pGroup->geom["sphere"];
        dBodySetPosition(body,position.x,position.y,position.z);
        dBodySetForce(body,0,0,0);
        return true;
        }
    }
    return PhysicalSingleBody::HandleMessage(message);
}


Marker::Marker(){
    radius = 1;
}

void Marker::Update(){
    cout << "update marker\n";
    PhysicalSingleBody::Update();
}


void Marker::Draw(){

    glPushMatrix();
        glTranslated(position.x,position.y,position.z);
        GLUquadricObj *quadric = gluNewQuadric();
        glColor4f(0,0,0,.5);
        gluQuadricDrawStyle(quadric, GLU_FILL );
        gluSphere( quadric , 1 , 25 , 20 );
        gluDeleteQuadric(quadric);
    glPopMatrix();

}
