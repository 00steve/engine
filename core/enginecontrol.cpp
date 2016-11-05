#include "enginecontrol.h"



void EngineControl::OnSetSettings(){
    VarMap settings = Settings();
    string type;
    VarMap prop;
    Node* newChild = NULL;

    VarMap props = settings.GetGroup("props");
    List<string> pNames = props.GroupNames();
    for(int i=0;i<pNames.GetCount();i++){
        prop = props.GetGroup(pNames[i]);
        if(prop.IsSet("type")){
            type = prop.get<string>("type");
            cout << " - has a type " << type << endl;
            Child(Load("prop",prop));
        }
    }


    VarMap nodes = settings.GetGroup("nodes");
    List<string> nNames = nodes.GroupNames();
    for(int i=0;i<nNames.GetCount();i++){
        prop = nodes.GetGroup(nNames[i]);
        if(prop.IsSet("type")){
            type = prop.get<string>("type");
            cout << " - node has a type " << type << endl;
            newChild = Load("",prop);
            if(newChild){
                //cout << "   - LOADED " << type << endl;
                Child(newChild);
            }
        }
    }

}


void EngineControl::OnGlobalRequest(Node* globalNodeRef,string name){

}





void EngineControl::Update(){
    Node::Update();
}
