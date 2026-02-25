
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
public:
    unsigned int shaderProgram;

    //Constructor reads and builds the Shader
    Shader(const char* vertexPath, const char* fragmentPath){

        //Read code from files
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        //ifstream can now throw exceptions
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

        try{
            //Open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            //read file's buffers
            std::stringstream vStreamSize, fStreamSize;
            vStreamSize << vShaderFile.rdbuf();
            fStreamSize << fShaderFile.rdbuf();

            //close files
            vShaderFile.close();
            fShaderFile.close();
            //convert to string
            vertexCode =   vStreamSize.str();
            fragmentCode = fStreamSize.str();

        }
        catch(std::ifstream::failure e){
            std::cout << "ERROR STREAM FAILURE\n" << e.what() << std::endl;
        }
        // == vertexShaderSource and fragmentShaderSource
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // 2. compile shaders
        // vertex Shader
        unsigned int vertexShader, fragmentShader;
        int success;
        char infoLog[512];
        //Create v shader
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        //Set the source of the shader
        glShaderSource(vertexShader, 1, &vShaderCode, NULL);
        glCompileShader(vertexShader);
        
        // print compile errors if any
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout<<"ERROR:::SHADER::VERTEX:: \n"<< infoLog << std::endl;
        }
        // similiar for Fragment Shader
        
        //Create the fragement shader
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        //Set the source of the fragement shader
        glShaderSource(fragmentShader, 1, &fShaderCode, NULL);

        //compile the fragement shader
        glCompileShader(fragmentShader);
        //Print errors for it
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout<<"ERROR::FRAGMENT::SHADER::\n"<<infoLog<<std::endl;
        }
        // shader Program
        shaderProgram = glCreateProgram();
        // Attach shaders to the program
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);

        // Link shaders together
        glLinkProgram(shaderProgram);
        // print linking errors if any
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::\n" << infoLog << std::endl;
        }
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    //Activate the shader  
    void use(){
        glUseProgram(shaderProgram);
    }

    void setFloat(const std::string &name, float value) const{
        glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }
    void setInt(const std::string &name, int value) const{
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }
    void setBool(const std::string &name, bool value) const{
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
    }
};

#endif
