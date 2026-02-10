/********* TEMPLATE OpenGL PROJECT ********
 *           Uses GLFW and GLAD           *
 *           1/18/2025 SourMnMs           *
 *****************************************/


#include "bufferLog.h"
#include "../Shapes/Shape.h"
#include "Shader.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <vector>
#include <string>
#include <iostream>


#define TO_LITERAL(s) #s
#define FILE_PATH(X,Y) TO_LITERAL(X/Y)

#define FP_SHADERS ../shaders
#define FP_UTILS ../utils
#define FP_ASSETS ../assets


// callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPosIn, double yPosIn);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);

// input management
void processInput(GLFWwindow* window);


constexpr GLuint WIN_WIDTH = 729, WIN_HEIGHT = 729;
constexpr bool DO_TEXTURES = false;

Camera camera{glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f};
float lastX = WIN_WIDTH / 2.0f;
float lastY = WIN_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;


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
    GLFWwindow* myWin = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Area Calculator", nullptr, nullptr);
    if (!myWin)
    {
        std::cout << "Failed to create window." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(myWin);
    glfwSetFramebufferSizeCallback(myWin, framebuffer_size_callback);
    glfwSetCursorPosCallback(myWin, mouse_callback);
    glfwSetScrollCallback(myWin, scroll_callback);
    glfwSetInputMode(myWin, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
    // https://learnopengl.com/Advanced-OpenGL/Advanced-Data
    /*std::vector<glm::vec3> verticesSub = {
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),
        glm::vec3(-0.5f, 0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f)

        glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(-0.5f, 0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f),

        glm::vec3(-0.5f, 0.5f, 0.5f),
        glm::vec3(-0.5f, 0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, 0.5f, 0.5f),

        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),

        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),

        glm::vec3(-0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(-0.5f, 0.5f, 0.5f),
        glm::vec3(-0.5f, 0.5f, -0.5f)
    };
    GLsizeiptr vertMemSize = verticesSub.size()*sizeof(glm::vec3);
    GLvoid* vertData = &verticesSub[0]; */

    // std::vector<unsigned int> indices = {
    //     0, 1, 2, 3, 4, 5,
    //     6, 7, 8, 9, 10, 11,
    //     12, 13, 14, 15, 16, 17,
    //     18, 19, 20, 21, 22, 23,
    //     24, 25, 26, 27, 28, 29,
    //     30, 31, 32, 33, 34, 35
    // };
    // GLsizeiptr indicesMemSize = indices.size()*sizeof(unsigned int);


    /*std::vector<float> texCoordsSub = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
    };
    GLsizeiptr texCoordMemSize = texCoordsSub.size()*sizeof(float);
    */

    // const unsigned int numCubePositions = cubePositions.size();
    std::vector<glm::vec2> shapeVerts = {
        glm::vec2(-0.5f, -0.5f),    // bottom left
        glm::vec2(-0.5f, 0.5f),     // top left
        glm::vec2(0.5f, 0.5f),      // top right
        glm::vec2(0.5f, -0.5f)      // bottom right
    };
    std::vector<unsigned int> shapeInds = {
        0, 1, 2,
        2, 3, 0
    };
    Shape testShape{shapeVerts, shapeInds};

    // *************** BUFFERS ***************

    // vertex array object (VAO) is basically a whole scene, a lot is drawn on a vao
    // vertex buffer object (VBO) keeps track of a bunch of vertices
    // element buffer object (EBO) uses indices to tell what vertices to draw in what order
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    /***** REMEMBER: WHEN USING glBufferSubData(), YOU NEED TO glBufferData(total_mem_size, NULL) FIRST *******
     *     glBufferData takes in 123123123 arrays, glBufferSubData puts them in glBufferData as 111222333     *
     ***** Thus, the offset in glVertexAttribPointer is the sum of the arrays before it **********************/
    constexpr int OneMB = 1024 * 1024;

    bufferLog VBO = {GL_ARRAY_BUFFER, 4*OneMB, GL_DYNAMIC_DRAW};
    // VBO.bufferSubData(vertMemSize, &verticesSub[0]);

    bufferLog EBO = {GL_ELEMENT_ARRAY_BUFFER, 2*OneMB, GL_DYNAMIC_DRAW};
    // EBO.bufferSubData(indicesMemSize, &indices[0]);

    testShape.addToBuffer(VBO, EBO);


    // *************** VERTEX ATTRIBUTES ***************

    // position attribute is the first 3 (index, size)
    // you need to jump 6 float sizes to get to the next position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)VBO.memToAttrib(0));
    glEnableVertexAttribArray(0);
    // color attribute is same as above, same stride, offset of 3 floats
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)VBO.memToAttrib(1));
    glEnableVertexAttribArray(1);
    // texture attribute, takes 2 floats
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)vertMemSize);
    // glEnableVertexAttribArray(1);

    /*
    // *************** TEXTURE STUFF ***************
    unsigned int textureContainer, textureFace;
    {
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
    } */


    // *************** OBJECT INITIALIZATION ***************
    Shader shader1{FILE_PATH(FP_SHADERS, vertShader.vert), FILE_PATH(FP_SHADERS, fragShader.frag)};

    // shader1.use();
    // shader1.setInt("tex1", 0);
    // shader1.setInt("tex2", 1);

    camera.setCameraType(Camera::Type::FPS);


    GLint testSize = 0;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &testSize);
    std::cout << "VBO size: " << testSize << std::endl;


    /* *******************************************************************
     *                            RENDER LOOP                            *
     * ******************************************************************/
    // TODO: CLASS THAT HAS A LIST OF EVERY OBJECT
    // THIS CLASS ALSO HAS A STREAM OF INPUTS
    // PEAK ENCAPSULATION

    while (!glfwWindowShouldClose(myWin))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(myWin);

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        {
            // textures
            // glActiveTexture(GL_TEXTURE0);
            // glBindTexture(GL_TEXTURE_2D, textureContainer);
            // glActiveTexture(GL_TEXTURE1);
            // glBindTexture(GL_TEXTURE_2D, textureFace);

            // rendering
            glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera.zoom), WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);
            glm::mat4 viewMatrix = camera.getViewMatrix();

            shader1.use();

            // shader1.setMat4("model", modelMatrix);
            shader1.setMat4("view", viewMatrix);
            shader1.setMat4("projection", projectionMatrix);
            // int transformLocation = glGetUniformLocation(shader1.programID, "transform");
            // glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(trans));

            glBindVertexArray(VAO);

            testShape.translateDefault(222);
            testShape.render(shader1);

            // testShape.setTranslation({1.0, 1.0}, 90.0f);
            testShape.translate({1.0f, 1.0f});
            testShape.rotate(glm::degrees(currentFrame));
            testShape.scale({2.0f, 1.0f});
            testShape.render(shader1);
            glBindVertexArray(0);
        }

        // check/call events, swap buffers
        glfwSwapBuffers(myWin);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    VBO.deleteBuffer();
    EBO.deleteBuffer();

    glfwTerminate();
    return 0;
}


// whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow *window, double xPosIn, double yPosIn)
{
    float xPos = static_cast<float>(xPosIn);
    float yPos = static_cast<float>(yPosIn);

    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}
void scroll_callback(GLFWwindow *window, double xOffset, double yOffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yOffset));
}


void processInput(GLFWwindow* window)
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

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera::Movement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera::Movement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera::Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera::Movement::RIGHT, deltaTime);
    // glfwGetInputMode ???
}