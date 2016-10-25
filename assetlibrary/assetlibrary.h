#ifndef ASSET_LIBRARY_H
#define ASSET_LIBRARY_H
#include "../core/varmap.h"
#include <string>
#include <engine/core/stringutil.h>
#include <engine/core/map.h>
#include <engine/assetlibrary/dll.h>
#include <engine/core/enginecontrol.h>
#include <engine/graphics/view.h>
#include <engine/graphics/camera.h>
#include <engine/core/node.h>


class AssetLibrary{
private:

    string rootDirectory;

	map<void*> loadedFiles;

	VarMap LoadSettingsFile(Node* loader,string fileName);

public:

    AssetLibrary();
    //static Texture* LoadTexture();
	//static Sound* LoadSound();

	VarMap              LoadSettings(Node* loader,string fileName);

	template <class T>
    T                   Load(Node* loader,string fileName,VarMap settings);

    Node*               LoadCustom(Node* loader,string settingsName,VarMap settings);

	EngineControl*      LoadEngineControl(Node* loader,VarMap settings);
    View*               LoadView(Node* loader,VarMap settings);
    Camera*             LoadCamera(Node* loader,VarMap settings);
    //H3DRes              LoadH3DRes(Node* loader,string);

};



#endif // LIBRARY_H
