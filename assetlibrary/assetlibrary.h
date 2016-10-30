#ifndef ASSET_LIBRARY_H
#define ASSET_LIBRARY_H

#include <string>
#include <engine/core/varmap.h>
#include <engine/core/stringutil.h>
#include <engine/core/map.h>
#include <engine/assetlibrary/dll.h>

class AssetLibrary{
private:

    static string rootDirectory;

	static map<void*> loadedFiles;

	static VarMap LoadSettingsFile(string fileName);

public:

    //static Texture* LoadTexture();
	//static Sound* LoadSound();

	static VarMap LoadSettings(string fileName);

	template <class T>
    static T Load(string fileName,VarMap settings){
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
    }

    //Node*               LoadCustom(Node* loader,string settingsName,VarMap settings);

	//EngineControl*      LoadEngineControl(Node* loader,VarMap settings);
    //View*               LoadView(Node* loader,VarMap settings);
    //Camera*             LoadCamera(Node* loader,VarMap settings);
    //H3DRes              LoadH3DRes(Node* loader,string);

};



#endif // LIBRARY_H
