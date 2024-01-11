#include <glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window and context creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // your code
    {
        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, // 0
            0.5f, -0.5f, 1.0f, 0.0f,  // 1
            0.5f, 0.5f, 1.0f, 1.0f,   // 2
            -0.5f, 0.5f, 0.0f, 1.0f   // 3
        };

        // prettier-ignore
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0};

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        // unsigned int VAO; // this will hold the id(descriptor) of the buffer
        // glGenVertexArrays(1, &VAO);
        // glBindVertexArray(VAO);

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        IndexBuffer ib(indices, 6);

        VertexBufferLayout layout;
        layout.AddFloat(2);
        layout.AddFloat(2);
        va.AddBuffer(vb, layout);

        Shader shader("../res/shaders/Basic.shader");
        shader.Bind();
        // uniform code

        // shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.4f, 1.0f);

        Texture texture("../res/textures/smiley.jpg");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.UnBind();
        vb.UnBind();
        ib.UnBind();
        shader.UnBind();

        Renderer render;

        // render loop
        // -----------

        float r = 0.0f;
        float inc = 0.005f;
        float increment = inc;
        while (!glfwWindowShouldClose(window))
        {
            // input
            // -----
            processInput(window);

            // render
            // ------
            render.Clear();
            shader.Bind();
            // shader.SetUniform4f("u_Color", r, 0.3f, 0.5f, 1.0f);
            render.Draw(va, ib, shader);

            if (r > 1.0f)
                increment = -inc;
            else if (r < 0.0f)
                increment = inc;

            r += increment;

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}