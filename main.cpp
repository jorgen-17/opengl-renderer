#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ogldev_math_3d.h"

GLuint VBO;
const int numDots = 2;
Vector3f Vertices[numDots];

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_POINTS, 0, numDots);

    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}

static void CreateVertexBuffer()
{
    Vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);
    Vertices[1] = Vector3f(0.5f, 0.5f, 0.0f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    int width = 2560;
    int height = 1600;
    glutInitWindowSize(width, height);

    int x = 0;
    int y = 0;
    glutInitWindowPosition(x, y);
    int win = glutCreateWindow("Tutorial 02");
    printf("window id: %d\n", win);

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);

    CreateVertexBuffer();

    glutDisplayFunc(RenderSceneCB);

    glutMainLoop();

    return 0;
}
