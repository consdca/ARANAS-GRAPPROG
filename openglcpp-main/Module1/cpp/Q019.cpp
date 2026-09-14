#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

float colors[6][3] = {
    {1.0f, 0.0f, 0.0f}, 
    {0.0f, 1.0f, 0.0f}, 
    {0.0f, 0.0f, 1.0f}, 
    {1.0f, 1.0f, 0.0f}, 
    {0.0f, 1.0f, 1.0f}, 
    {1.0f, 0.0f, 1.0f}  
};
const char* colorNames[6] = {"Red", "Green", "Blue", "Yellow", "Cyan", "Magenta"};

int bgColorIdx = 0;

void display() {
    glClearColor(colors[bgColorIdx][0], colors[bgColorIdx][1], colors[bgColorIdx][2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key >= '1' && key <= '6') {
        bgColorIdx = key - '1';
        cout << "Selected color: " << colorNames[bgColorIdx] << endl;
        glutPostRedisplay();
    } else if (key == 27) { 
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q19 - Keyboard Color Picker");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}