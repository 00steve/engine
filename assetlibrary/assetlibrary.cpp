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



