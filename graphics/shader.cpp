#include "shader.h"


void Shader::LoadShaders(){
    /*create shader objects in openGL*/
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    /*load the fragment shader into memory and compile it */
    ifstream fragment_file(fragment_shader_file_name.c_str());
    if(!fragment_file.good()) return;
    string fragment_program((std::istreambuf_iterator<char>(fragment_file)), std::istreambuf_iterator<char>());
    std::cout << "\n\n-----------------------------\n\n" << fragment_program << "\n\n-----------------------------\n\n";
    fragment_file.close();
    const char *fragment_chars[] = { fragment_program.c_str() };
    const int fragment_chars_length[] = {(int)fragment_program.length()};
    glShaderSource(fragment_shader, 1, fragment_chars, fragment_chars_length);
    glCompileShader(fragment_shader);

    /*load the vertex shader into memory and compile it in openGL*/
    ifstream vertex_file(vertex_shader_file_name.c_str());
    if(!vertex_file.good()) return;
    string vertex_program((std::istreambuf_iterator<char>(vertex_file)), std::istreambuf_iterator<char>());
    cout << "\n\n-----------------------------\n\n" << vertex_program << "\n\n-----------------------------\n\n";
    vertex_file.close();
    const char *vertex_chars[] = { vertex_program.c_str() };
    const int vertex_chars_length[] = {(int)vertex_program.length()};
    glShaderSource(vertex_shader, 1, vertex_chars, vertex_chars_length);
    glCompileShader(vertex_shader);

    /*create a program for the graphics card using the two new shaders*/
    program = glCreateProgram();
    glAttachShader(program, fragment_shader);
    glAttachShader(program, vertex_shader);
    glLinkProgram(program);

    /*if we made it here, it means that everything in the
    constructor was successful, so the construct_success
    flag should be set to true.*/
    construct_success = true;
}


Shader::Shader(string fragment_shader_file_name,string vertex_shader_file_name) :
    fragment_shader_file_name(fragment_shader_file_name),
    vertex_shader_file_name(vertex_shader_file_name),
    construct_success(false) {
    LoadShaders();
}



/*set openGL to use this program to render things*/
void Shader::MakeCurrent(){
    glUseProgram(program);
}

void Shader::ClearCurrent(){
    glUseProgram(0);
}

/*set uniform variable value*/
bool Shader::SetUniform1f(string uniform_name,float val){
    GLint var = glGetUniformLocation(program, uniform_name.c_str());
    if(var == -1) return false;
    glProgramUniform1f(program, var, val);
    return true;
}

/*set uniform variable value*/
bool Shader::SetUniform4f(string uniform_name,float x,float y,float z,float w){
    GLint var = glGetUniformLocation(program, uniform_name.c_str());
    if(var == -1) return false;
    glProgramUniform4f(program, var, x,y,z,w);
    return true;
}

bool Shader::SetUniform1d(string uniform_name,double val){
    GLint var = glGetUniformLocation(program, uniform_name.c_str());
    if(var == -1) return false;
    glProgramUniform1d(program,var, val);
    return true;
}

bool Shader::SetUniform1i(string uniform_name,int val){
    GLint var = glGetUniformLocation(program, uniform_name.c_str());
    if(var == -1) return false;
    glProgramUniform1i(program,var, val);
    return true;
}


/*if this object is tested as a boolean value, it will return
if the construction proccess was successful or now. So something
like if(this_object){} will return true if the shader was loaded
and set up correctly. If it failed at any point, if(this_object)
will return false and you shouldn't try and use this because it
will probably cause your computer to burst into flames or something.*/
bool Shader::operator == (bool test){
    return construct_success;
}

Shader::operator bool() const{
    return construct_success;
}
/*
bool Shader::operator == (const shader other){
    return
        this->fragment_shader_file_name == other.fragment_shader_file_name &&
        this->vertex_shader_file_name == other.vertex_shader_file_name;
}
*/

