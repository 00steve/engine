#ifndef SHADER_H
#define SHADER_H

#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <GL/glew.h>

using namespace std;


class Shader{
private:

    /*store the names of the fragment and vertex shader
    files that are being read and compiled in openGL. These
    are needed later to compare against other shaders to see
    if they already exist.*/
    string fragment_shader_file_name;
    string vertex_shader_file_name;

    GLuint fragment_shader;
    GLuint vertex_shader;

    GLuint program;

    bool construct_success;

    /*given the file_names, it loads the text files and compiles them
    into shaders that are used to build the program that is used to
    determine how everything is rendered.*/
    void LoadShaders();

public:

    Shader(string fragment_shader_file_name,string vertex_shader_file_name);


    /*set openGL to use this program to render things*/
    void MakeCurrent();

    void ClearCurrent();
    /*set uniform variable value*/
    bool SetUniform1f(string uniform_name,float val);

    /*set uniform variable value*/
    bool SetUniform4f(string uniform_name,float x,float y,float z,float w);

    bool SetUniform1d(string uniform_name,double val);

    bool SetUniform1i(string uniform_name,int val);


    /*if this object is tested as a boolean value, it will return
    if the construction proccess was successful or now. So something
    like if(this_object){} will return true if the shader was loaded
    and set up correctly. If it failed at any point, if(this_object)
    will return false and you shouldn't try and use this because it
    will probably cause your computer to burst into flames or something.*/
    bool operator == (bool test);

    operator bool() const;

    //bool operator == (const shader other);
};

#endif // SHADER_H
