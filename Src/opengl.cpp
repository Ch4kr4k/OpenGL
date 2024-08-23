#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include <datatypes.h>
#include <Renderer.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <VertexBufferLayout.h>
#include <Shader.h>
#include <Texture.h>
#include "imgui.h"
#include "imgui_impl_opengl3.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Setting up", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(2); // seting the sync to hz
    /*Initialize Glew*/
    /*make us enable to use all the opengl funftions*/
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW is not OK" << std::endl;
    }
    else {
        std::cout << "GLEW is OK" << std::endl << "GL Ver: " << glGetString(GL_VERSION) << std::endl;
    }

    // Draw triangle
    float positions[] = { // vertex pposition for triangle
        -0.5f, -0.5,
        0.5f,  -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5
    };

    u4 indices[] = { // indice buffer telling to draw triangle
        0, 1, 2,
        2, 3, 0
    };


    VertexArray va;
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniforms("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

    va.UnBind();
    shader.Unbind();
    ib.UnBind();
    vb.UnBind();
    // animating the color
    float r = 0.0f;
    float increment = 0.05f;

    /* Loop until the user closes the window ← actual rendeing here */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        shader.SetUniforms("u_Color", r, 0.3f, 0.8f, 1.0f);
        va.Bind();
        ib.Bind();

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        // begining, indices draws a current buffer that is bind
        /* Swap front and back buffers */

        if (r > 1.0f)
            increment = -0.5f;
        else if (r < 0.0f)
            increment = 0.5f;

        r += increment;

        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }
    glfwTerminate();
    return 0;
}