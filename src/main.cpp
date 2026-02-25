#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader_s.h>
#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main(){
    // glfw initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,600, "Learning Graphics", NULL, NULL); // (width, height, title, Null, NUll)
    if(window == NULL){
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Setup shaderProgram
    Shader ourShader("/home/memanuele/dev/graphics/src/shader.vs", "/home/memanuele/dev/graphics/src/shader.fs");

    //vertices of a triangle
    float vertices[] = {
        // positions         // colours
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // top right
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // top left
        //-0.5f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f  // bottom left  
    };

    unsigned int indices[] =
        {
            0,1,3,
            1,2,3
        };

    //Setup vertex index buffer
    unsigned int VBO;
    unsigned int VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);

    //Bind vertex attribute
    glBindVertexArray(VAO);

    //Bind buffer 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Additional calls will be made to currently bound buffer(VBO)
    //Copy user data into buffer array
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 6*sizeof(float), (void*)(3* sizeof(float)));
    // Create element buffer object with list of indices
    unsigned int EBO;
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    glBindVertexArray(0);
    float offSet = 0.5f;
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Render loop
    while(!glfwWindowShouldClose(window)){
        //input
        processInput(window);

        //render commands
        glClearColor(0.4f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.setFloat("xOffset", offSet);
        ourShader.use();
        //Setup uniform vector
        //float timeValue = glfwGetTime();
        //float colorValue = sin(timeValue) / 2.0f + 0.5f;
        
        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "OurColor");
        //glUniform4f(vertexColorLocation, 0.0f, colorValue, 0.0f, 1.0f);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //check and call
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    // close out glfw; clear out allocated GLFW resources
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
