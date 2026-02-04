/********* TEMPLATE OpenGL PROJECT ********
 *           Uses GLFW and GLAD           *
 *           1/18/2025 SourMnMs           *
 *****************************************/


#include "utils/point/Point.h"
#include "utils/color/Color.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <vector>
#include <string>
#include <string_view>
#include <iostream>


#define TO_LITERAL(s) #s
#define FILE_PATH(X,Y) TO_LITERAL(X/Y)

#define FP_SHADERS ../shaders
#define FP_UTILS ../utils
#define FP_ASSETS ../assets


// callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// input management
void processInput(GLFWwindow* win, Point& thingy);


constexpr GLuint WIN_WIDTH = 729, WIN_HEIGHT = 729;

int main()
{
#ifdef __linux__
    // wayland libdecor is annoying af so we have to do this and set resizable false
    glfwInitHint(GLFW_WAYLAND_LIBDECOR, GLFW_WAYLAND_DISABLE_LIBDECOR);
#endif

    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //this means the user needs at least glfw ver 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //^^^ but at least ver 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHintString(GLFW_WAYLAND_APP_ID, "SourMnMs-OpenGL-Proj");
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


    // Create Window
    GLFWwindow* myWin = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Watch Thing", NULL, NULL);
    if (!myWin)
    {
        std::cout << "Failed to create window." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(myWin);
    glfwSetFramebufferSizeCallback(myWin, framebuffer_size_callback);

    // Make sure glad is working
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    /* ************************************************************************************
     *                                  DRAWING TO WINDOW                                 *
     * GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times. *
     * GL_STATIC_DRAW: the data is set only once and used many times.                     *
     * GL_DYNAMIC_DRAW: the data is changed a lot and used many times.                    *
     * ***********************************************************************************/

    // *************** vertices upon vertices upon vertices ***************
    constexpr int vertexStride = 5*sizeof(float);
    std::vector<float> vertices = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // std::vector<unsigned int> indices = {
    //     0, 1, 2,
    //     2, 3, 0
    // };
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };


    // *************** BUFFERS ***************

    // vertex array object (VAO) is basically a whole scene, a lot is drawn on a vao
            // ^^^ think changing a tab in a menu would be changing a vao
    // vertex buffer object (VBO) keeps track of a bunch of vertices
    // element buffer object (EBO) uses indices to tell what vertices to draw in what order
    unsigned int EBO, VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind the Vertex Array Object first
    glBindVertexArray(VAO);

    // then bind and set the vertex buffer(s) and the element buffer(s)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);


    // *************** VERTEX ATTRIBUTES ***************

    // position attribute is the first 3 (index, size)
    // you need to jump 6 float sizes to get to the next position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexStride, (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute is same as above, same stride, offset of 3 floats
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexStride, (void*)(3*sizeof(float)));
    // glEnableVertexAttribArray(1);
    // texture attribute, takes 2 floats, offset of 6 floats
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexStride, (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    // *************** TEXTURE STUFF ***************
    unsigned int textureContainer, textureFace;
    // how many textures do we want? where to store them (c uint array)?
    glGenTextures(1, &textureContainer);
    glBindTexture(GL_TEXTURE_2D, textureContainer);

    // set s and t axis to the "clamp to border" behavior
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    // because clamp to border is used, need to set a color for the border
    float borderColor[] = {0.19f, 0.20f, 0.32f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    // for magnifying and minifying operators
    // use nearest neighbor (8 bit), bilinear filtering (blur), and/or mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    int width, height, numChannels;
    unsigned char *data = stbi_load(FILE_PATH(FP_ASSETS, container.jpg), &width, &height, &numChannels, 0);
    if (data)
    {
        // texture target (doesn't affect other texture targets like 1D or 3D)
        // mipmap level (base is 0)
        // format to store texture (our image only has rgb vals)
        // width+height (stored with stbi_load())
        // legacy border stuff that should always be 0
        // format and datatype of source image (rgb, chars/bytes),
        // image data (output of stbi_load())
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D); // takes care of making the mipmap for us
    }
    else std::cout << "ERROR::IMAGE::LOADING_FAILED" << std::endl;
    stbi_image_free(data); // frees the image from memory

    glGenTextures(1, &textureFace);
    glBindTexture(GL_TEXTURE_2D, textureFace);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load(FILE_PATH(FP_ASSETS, awesomeface.png), &width, &height, &numChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else std::cout << "ERROR::IMAGE::LOADING_FAILED" << std::endl;
    stbi_image_free(data);


    // *************** TRANSFORMATIONS ***************



    // *************** OBJECT INITIALIZATION ***************
    Shader shader1{FILE_PATH(FP_SHADERS, vertShader.vert), FILE_PATH(FP_SHADERS, fragShader.frag)};
    Point myPoint{};

    shader1.use();
    shader1.setInt("tex1", 0);
    shader1.setInt("tex2", 1);


    /* *******************************************************************
     *                            RENDER LOOP                            *
     * ******************************************************************/
    // IDEA: CLASS THAT HAS A LIST OF EVERY OBJECT
    // THIS CLASS ALSO HAS A STREAM OF INPUTS
    // PEAK ENCAPSULATION

    while (!glfwWindowShouldClose(myWin))
    {
        // input
        processInput(myWin, myPoint);

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        {
            // textures
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureContainer);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, textureFace);

            // rendering
            float time = glfwGetTime();
            shader1.use();

            glm::mat4 modelMatrix{1.0f};
            glm::mat4 viewMatrix{1.0f};
            glm::mat4 projectionMatrix{1.0f};
            // translate scene in reverse direction of where we want to move
            // modelMatrix = glm::rotate(modelMatrix, time, glm::vec3(0.5f, 1.0f, 0.0f));
            viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
            projectionMatrix = glm::perspective(glm::radians(45.0f), (float) WIN_WIDTH / (float) WIN_HEIGHT, 0.1f, 100.0f);

            // shader1.setMat4("model", modelMatrix);
            shader1.setMat4("view", viewMatrix);
            shader1.setMat4("projection", projectionMatrix);
            // int transformLocation = glGetUniformLocation(shader1.programID, "transform");
            // glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(trans));

            glBindVertexArray(VAO);
            // glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            // glDrawArrays(GL_TRIANGLES, 0, 36);
            for (int i = 0; i < 10; i++)
            {
                modelMatrix = glm::mat4(1.0f);
                modelMatrix = glm::translate(modelMatrix, cubePositions[i]);
                float angle = 20.0f*i;
                if (i % 3 == 0) angle = time * 25.0f;
                modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                shader1.setMat4("model", modelMatrix);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            glBindVertexArray(0);
        }

        // check/call events, swap buffers
        glfwSwapBuffers(myWin);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}


// whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window, Point& thingy)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
        std::cout << "Closing window" << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        std::cout << "Pebble has his thinking cap!" << std::endl;
    }

    constexpr float speed = 0.05f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {thingy.x -= speed;}
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {thingy.x += speed;}
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {thingy.y -= speed;}
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {thingy.y += speed;}
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {thingy.z -= 1/180.0f;}
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {thingy.z += 1/180.0f;}
}