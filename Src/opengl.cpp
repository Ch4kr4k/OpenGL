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
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Setting up", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW is not OK" << std::endl;
    }
    else {
        std::cout << "GLEW is OK" << std::endl <<"GL Ver: " << glGetString(GL_VERSION) << std::endl;
    }

    float positions[] = {
        -0.5f, -0.5f,  0.0f, 0.0f,  // Bottom-left
         0.5f, -0.5f,  1.0f, 0.0f,  // Bottom-right
         0.5f,  0.5f,  1.0f, 1.0f,  // Top-right
        -0.5f,  0.5f,  0.0f, 1.0f   // Top-left
    };

    u4 indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniforms("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

    Texture texture("res/textures/pngegg.png");
    texture.Bind();
    shader.SetUniforms1i("u_Texture", 0);

    va.UnBind();
    ib.UnBind();
    vb.UnBind();
    shader.Unbind();
    // animating the color
    float r = 0.0f;
    float increment = 0.05f;

    Renderer renderer;
    /* Loop until the user closes the window ← actual rendeing here */
    ImGui::CreateContext();
    //ImGui_ImplGlfw_InitForOpenGL(window, true);
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

        renderer.Clear();
        ImGui::NewFrame();
        shader.Bind();
        //shader.SetUniforms("u_Color", r, 0.3f, 0.8f, 1.0f);
        /*va.Bind();
        ib.Bind();*/
        renderer.Draw(va, ib, shader);
        ImGui::Render();
        //GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); 
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