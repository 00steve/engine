#include "assetlibrary.h"


string AssetLibrary::rootDirectory = "assets/";

map<void*> AssetLibrary::loadedFiles;




VarMap AssetLibrary::LoadSettings(string fileName){
	if(loadedFiles.exists(fileName)) {
		cout << "found existing load of " << fileName << endl;
		return *((VarMap*)loadedFiles[fileName]);
	}
	return LoadSettingsFile(fileName);
}


VarMap AssetLibrary::LoadSettingsFile(string fileName){
	fileName = rootDirectory+"settings/"+fileName;
	cout << "load settings file " << fileName << endl;
	VarMap newMap;
	if(!VarMap::Load(fileName,newMap)){
		cout << "couldn't load settings\n";
		return newMap;
	}
	loadedFiles.push((void*)&newMap,fileName);
	return newMap;
}
/*
template <class T>
T AssetLibrary::Load(string fileName,VarMap settings){
	if(!settings.IsSet("type")) return NULL;
	fileName = rootDirectory + fileName;
    eDLL* dll = new eDLL(fileName.c_str());
    if(loadedFiles.isSet(fileName)){
        dll = (eDLL*) loadedFiles.getLastCheck();
    } else {
		if(!dll->IsLoaded()){
			delete dll;
			cout << " - couldn't load the dll for some reason\n";
			return NULL;
		}
		loadedFiles.push((void*)dll,fileName);
    }
    string funcName = string("Build");
	T object = GetDllValue<T>(dll,funcName.c_str());
	return object;
}*/

/*
Node* AssetLibrary::LoadCustom(Node* loader,string settingsName,VarMap settings){
	if(!settings.IsSet("type")) return NULL;
	string fileName = rootDirectory + "extensions/engine." + settingsName
		+ "." + settings.get<string>("type") + ".dll";
	return Load<Node*>(loader,fileName,settings);
}

EngineControl* AssetLibrary::LoadEngineControl(Node* loader,VarMap settings){
    if(!settings.IsSet("type")){
        cout << "invalid settings argument. No \"type\" set.\n";
        return NULL;
    }
    string fileName = rootDirectory + "extensions/engine.control." + settings.get<string>("type") + ".dll";
	return Load<EngineControl*>(loader,fileName,settings);
}

View* AssetLibrary::LoadView(Node* loader,VarMap settings){
    if(!settings.IsSet("type")){
        cout << "invalid settings argument. No \"type\" set.\n";
        return NULL;
    }
    string fileName = rootDirectory + "extensions/engine.view." + settings.get<string>("type") + ".dll";
    return Load<View*>(loader,fileName,settings);
}

Camera* AssetLibrary::LoadCamera(Node* loader,VarMap settings){
    if(!settings.IsSet("type")){
        cout << "invalid settings argument. No \"type\" set.\n";
        return NULL;
    }
    string fileName = rootDirectory + "extensions/engine.camera." + settings.get<string>("type") + ".dll";
    return Load<Camera*>(loader,fileName,settings);
}
*/


