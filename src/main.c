#define GL_SILENCE_DEPRECATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "CUBE/gl_error.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 600
#define INCREMENT     5.0f



GLfloat camera_x = 0;
GLfloat camera_y = 0;



static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void error_callback(int error, const char* description);
static void print_versions();
static void init();
static void face(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat d[]);
static void cube(GLfloat v0[], GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat v4[], GLfloat v5[], GLfloat v6[], GLfloat v7[]);
static void display();



static void
init() {
    GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GL_CALL(glEnable(GL_DEPTH_TEST));

    GL_CALL(glMatrixMode(GL_PROJECTION));
    GL_CALL(glLoadIdentity());
    GL_CALL(glFrustum(-1, 1, -1, 1, 2, 10));
    GL_CALL(glMatrixMode(GL_MODELVIEW));
}



static void
face(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat d[]) {
    glBegin(GL_POLYGON);
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
        glVertex3fv(d);
    glEnd();
}



static void
cube(GLfloat v0[], GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat v4[], GLfloat v5[], GLfloat v6[], GLfloat v7[]) {
    GL_CALL(glColor3f(1.0f, 0.0f, 0.0f));
    face(v0, v1, v2, v3); // front

    GL_CALL(glColor3f(0.0f, 1.0f, 0.0f));
    face(v4, v5, v6, v7); // back

    GL_CALL(glColor3f(0.0f, 0.0f, 1.0f));
    face(v0, v4, v7, v3); // left

    GL_CALL(glColor3f(1.0f, 1.0f, 0.0f));
    face(v1, v5, v6, v2); // right

    GL_CALL(glColor3f(1.0f, 0.0f, 1.0f));
    face(v3, v2, v6, v7); // bottom

    GL_CALL(glColor3f(0.0f, 1.0f, 1.0f));
    face(v0, v1, v5, v4); // top
}



static void
display() {
    GLfloat v[ 8 ][ 3 ] = {
            {-0.5f, 0.5f,  0.5f},
            {0.5f,  0.5f,  0.5f},
            {0.5f,  -0.5f, 0.5f},
            {-0.5f, -0.5f, 0.5f},

            {-0.5f, 0.5f,  -0.5f},
            {0.5f,  0.5f,  -0.5f},
            {0.5f,  -0.5f, -0.5f},
            {-0.5f, -0.5f, -0.5f},
    };

    GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GLfloat distance = 3;
    GLfloat camX =  distance * -sinf((float) (camera_x * (M_PI / 180))) * cosf((float) (camera_y * (M_PI / 180)));
    GLfloat camY =  distance * -sinf((float) (camera_y * (M_PI / 180)));
    GLfloat camZ = -distance *  cosf((float) (camera_x * (M_PI / 180))) * cosf((float) (camera_y * (M_PI / 180)));

    GL_CALL(glLoadIdentity());
    GL_CALL(gluLookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0));

    cube(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7]);
}



int
main(void) {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "3D Cube", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glfwSwapInterval(1);

    GLuint err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "[GLEW error]: glewInit failed: %s\n", glewGetErrorString(err));
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    print_versions();

    init();

    while (!glfwWindowShouldClose(window)) {
        display();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
}



static void
print_versions() {
    GL_CALL(fprintf(stdout, "OpenGL version: %s\n", glGetString(GL_VERSION)));
    fprintf(stdout, "GLEW   version: %s\n", glewGetString(GLEW_VERSION));
    fprintf(stdout, "GLFW   version: %s\n\n", glfwGetVersionString());
}



static void
error_callback(int error, const char* description) {
    fprintf(stderr, "[GLFW error] (%d): %s\n", error, description);
}



static void
key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    switch (key) {
        case GLFW_KEY_UP:
            camera_y -= INCREMENT;
            break;

        case GLFW_KEY_DOWN:
            camera_y += INCREMENT;
            break;

        case GLFW_KEY_LEFT:
            camera_x += INCREMENT;
            break;

        case GLFW_KEY_RIGHT:
            camera_x -= INCREMENT;
            break;

        default:
            break;
    }

    printf("camera_y: %f\n", camera_y);
}
