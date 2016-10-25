#include "enginecontrol.h"



void EngineControl::OnSetSettings(){
    VarMap settings = Settings();
    VarMap props = settings.GetGroup("props");
    VarMap prop;
    List<string> pNames = props.GroupNames();
    string type;
    for(int i=0;i<pNames.GetCount();i++){
        prop = props.GetGroup(pNames[i]);
        if(prop.IsSet("type")){
            type = prop.get<string>("type");
            cout << " - has a type " << type << endl;
            //Child(Assets().LoadCustom(this,("prop."+type),prop));
        }
    }
}


void EngineControl::OnGlobalRequest(Node* globalNodeRef,string name){

}





void EngineControl::Update(){
    Node::Update();
}
