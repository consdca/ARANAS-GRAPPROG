#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

const int MAX_BURSTS = 10;

struct Burst {
    bool active;
    int type; // 1: Square, 2: Diamond, 3: Starburst Triangles
    float x, y;
    float radius;
    float alpha; // brightness fade
    float r, g, b;
};

Burst bursts[MAX_BURSTS];

void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void spawnBurst(int type) {
    for (int i = 0; i < MAX_BURSTS; i++) {
        if (!bursts[i].active) {
            bursts[i].active = true;
            bursts[i].type = type;
            bursts[i].x = ((rand() % 140) - 70) / 100.0f; // -0.7 to 0.7
            bursts[i].y = ((rand() % 100) - 50) / 100.0f;
            bursts[i].radius = 0.05f;
            bursts[i].alpha = 1.0f;
            bursts[i].r = (rand() % 100) / 100.0f;
            bursts[i].g = (rand() % 100) / 100.0f;
            bursts[i].b = 1.0f;
            break;
        }
    }
}

void drawBurst(const Burst& b) {
    glColor3f(b.r * b.alpha, b.g * b.alpha, b.b * b.alpha);

    if (b.type == 1) { // Concentric Squares
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(b.x - b.radius, b.y - b.radius);
            glVertex2f(b.x + b.radius, b.y - b.radius);
            glVertex2f(b.x + b.radius, b.y + b.radius);
            glVertex2f(b.x - b.radius, b.y + b.radius);
        glEnd();
    } 
    else if (b.type == 2) { // Diamond Lattice
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
            glVertex2f(b.x, b.y + b.radius * 1.3f);
            glVertex2f(b.x + b.radius * 1.3f, b.y);
            glVertex2f(b.x, b.y - b.radius * 1.3f);
            glVertex2f(b.x - b.radius * 1.3f, b.y);
        glEnd();
    } 
    else if (b.type == 3) { // Starburst Triangles
        int count = 8;
        for (int i = 0; i < count; i++) {
            float angle = i * 2.0f * 3.14159f / count;
            float px = b.x + b.radius * cosf(angle);
            float py = b.y + b.radius * sinf(angle);
            glBegin(GL_TRIANGLES);
                glVertex2f(px, py + 0.02f);
                glVertex2f(px - 0.02f, py - 0.02f);
                glVertex2f(px + 0.02f, py - 0.02f);
            glEnd();
        }
    }
}

void drawSidebar() {
    int activeCount = 0;
    for (int i = 0; i < MAX_BURSTS; i++) {
        if (bursts[i].active) activeCount++;
    }

    char buf[64];
    glColor3f(0.85f, 0.85f, 0.85f);
    glRasterPos2f(-0.95f, 0.88f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "=== BURST STUDIO ===");

    snprintf(buf, sizeof(buf), "Active Bursts: %d / %d", activeCount, MAX_BURSTS);
    glRasterPos2f(-0.95f, 0.78f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, buf);

    glRasterPos2f(-0.95f, 0.68f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "[1] Expanding Square");
    glRasterPos2f(-0.95f, 0.60f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "[2] Diamond Lattice");
    glRasterPos2f(-0.95f, 0.52f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "[3] Starburst Particles");
}

void updateBursts(int value) {
    for (int i = 0; i < MAX_BURSTS; i++) {
        if (bursts[i].active) {
            bursts[i].radius += 0.008f;
            bursts[i].alpha -= 0.025f;

            if (bursts[i].alpha <= 0.0f) {
                bursts[i].active = false;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, updateBursts, 0);
}

void display() {
    glClearColor(0.04f, 0.04f, 0.06f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawSidebar();

    for (int i = 0; i < MAX_BURSTS; i++) {
        if (bursts[i].active) {
            drawBurst(bursts[i]);
        }
    }

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == '1') spawnBurst(1);
    else if (key == '2') spawnBurst(2);
    else if (key == '3') spawnBurst(3);
    else if (key == 27) exit(0);

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("MP03 - Dynamic Fireworks & Shape Burst Studio");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(30, updateBursts, 0);
    glutMainLoop();
    return 0;
}