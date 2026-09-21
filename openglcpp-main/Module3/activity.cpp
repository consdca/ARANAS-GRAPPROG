#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif
#include <iostream>
using namespace std;

void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void drawText(void* font, float x, float y, const char* str) {
    glRasterPos2f(x, y);
    drawBitmapString(font, str);
}

void display() {

    glClearColor(0.93f, 0.91f, 0.86f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.65f, 0.25f, 0.15f);
    drawText(GLUT_BITMAP_HELVETICA_18, -0.98f, 0.85f, "Enrollment Status : ENROLLED");

    glColor3f(0.20f, 0.15f, 0.10f);
    drawText(GLUT_BITMAP_HELVETICA_12, -0.98f, 0.75f, "Student # : 201530088");
    drawText(GLUT_BITMAP_HELVETICA_12, -0.98f, 0.65f, "Name : ARANAS, KENNETH CONS DELA CRUZ");
    drawText(GLUT_BITMAP_HELVETICA_12, -0.98f, 0.55f, "Classification :");

    drawText(GLUT_BITMAP_HELVETICA_12,  0.05f, 0.75f, "College : COMPUTER STUDIES    Program : BSEMCDA");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.05f, 0.65f, "Year Level : 3    1st term, SY 26-27");

    glColor3f(0.70f, 0.62f, 0.52f);
    glLineWidth(2.0f);

    glBegin(GL_LINES);
        glVertex2f(-0.99f, 0.45f);
        glVertex2f( 0.99f, 0.45f);
    glEnd();

    glColor3f(0.35f, 0.45f, 0.25f); 
    float headerY = 0.40f;
    drawText(GLUT_BITMAP_HELVETICA_12, -0.98f, headerY, "Courses");
    drawText(GLUT_BITMAP_HELVETICA_12, -0.80f, headerY, "Title");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.05f, headerY, "Section");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.18f, headerY, "Units");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.28f, headerY, "Days");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.42f, headerY, "Time");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.85f, headerY, "Room");

    glColor3f(0.70f, 0.62f, 0.52f);
    glBegin(GL_LINES);
        glVertex2f(-0.99f, 0.35f);
        glVertex2f( 0.99f, 0.35f);
    glEnd();

    float startY = 0.28f;
    float rowSpacing = 0.11f;

    // Row 1
    glColor3f(0.55f, 0.35f, 0.20f); // Warm Sienna for Course Codes
    drawText(GLUT_BITMAP_9_BY_15, -0.98f, startY, "CCS0021");
    glColor3f(0.20f, 0.15f, 0.10f); // Espresso for standard data
    drawText(GLUT_BITMAP_HELVETICA_12, -0.80f, startY, "INFORMATION MANAGEMENT (LEC)");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.05f, startY, "TN25");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.18f, startY, "2");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.28f, startY, "T");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.42f, startY, "13:00:00-15:40:00");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.85f, startY, "ONLINE");

    // Row 2
    startY -= rowSpacing;
    glColor3f(0.55f, 0.35f, 0.20f);
    drawText(GLUT_BITMAP_9_BY_15, -0.98f, startY, "CCS0021L");
    glColor3f(0.20f, 0.15f, 0.10f);
    drawText(GLUT_BITMAP_HELVETICA_12, -0.80f, startY, "INFORMATION MANAGEMENT (LAB)");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.05f, startY, "TN25");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.18f, startY, "1");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.28f, startY, "F");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.42f, startY, "13:00:00-15:50:00");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.85f, startY, "ONLINE");

    // Row 3
    startY -= rowSpacing;
    glColor3f(0.55f, 0.35f, 0.20f);
    drawText(GLUT_BITMAP_9_BY_15, -0.98f, startY, "CCS0043");
    glColor3f(0.20f, 0.15f, 0.10f);
    drawText(GLUT_BITMAP_HELVETICA_12, -0.80f, startY, "APPLICATIONS DEVELOPMENT AND EMERGING TECHNOLOGIES (LEC)");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.05f, startY, "TW291");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.18f, startY, "2");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.28f, startY, "F");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.42f, startY, "17:00:00-19:40:00");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.85f, startY, "ONLINE");

    // Row 4
    startY -= rowSpacing;
    glColor3f(0.55f, 0.35f, 0.20f);
    drawText(GLUT_BITMAP_9_BY_15, -0.98f, startY, "CCS0043L");
    glColor3f(0.20f, 0.15f, 0.10f);
    drawText(GLUT_BITMAP_HELVETICA_12, -0.80f, startY, "APPLICATIONS DEVELOPMENT AND EMERGING TECHNOLOGIES (LAB)");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.05f, startY, "TW291");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.18f, startY, "1");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.28f, startY, "S");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.42f, startY, "17:00:00-19:50:00");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.85f, startY, "F1211");

    // Row 5
    startY -= rowSpacing;
    glColor3f(0.55f, 0.35f, 0.20f);
    drawText(GLUT_BITMAP_9_BY_15, -0.98f, startY, "CS0045");
    glColor3f(0.20f, 0.15f, 0.10f);
    drawText(GLUT_BITMAP_HELVETICA_12, -0.80f, startY, "CS ELECTIVE - COMPUTER GRAPHICS AND VISUAL COMPUTING");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.05f, startY, "TN35");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.18f, startY, "3");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.28f, startY, "M / TH");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.42f, startY, "13:00:00-14:50:00 / 13:00:00-14:50:00");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.85f, startY, "E601 / E610");

    // Row 6
    startY -= rowSpacing;
    glColor3f(0.55f, 0.35f, 0.20f);
    drawText(GLUT_BITMAP_9_BY_15, -0.98f, startY, "GED0081");
    glColor3f(0.20f, 0.15f, 0.10f);
    drawText(GLUT_BITMAP_HELVETICA_12, -0.80f, startY, "COLLEGE PHYSICS 1 LECTURE");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.05f, startY, "TN25");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.18f, startY, "2");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.28f, startY, "T");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.42f, startY, "10:00:00-12:40:00");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.85f, startY, "ONLINE");

    // Row 7
    startY -= rowSpacing;
    glColor3f(0.55f, 0.35f, 0.20f);
    drawText(GLUT_BITMAP_9_BY_15, -0.98f, startY, "GED0081L");
    glColor3f(0.20f, 0.15f, 0.10f);
    drawText(GLUT_BITMAP_HELVETICA_12, -0.80f, startY, "COLLEGE PHYSICS 1 LABORATORY");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.05f, startY, "TN25");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.18f, startY, "1");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.28f, startY, "W");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.42f, startY, "10:00:00-12:50:00");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.85f, startY, "F1003");

    // Row 8
    startY -= rowSpacing;
    glColor3f(0.55f, 0.35f, 0.20f);
    drawText(GLUT_BITMAP_9_BY_15, -0.98f, startY, "IT0041");
    glColor3f(0.20f, 0.15f, 0.10f);
    drawText(GLUT_BITMAP_HELVETICA_12, -0.80f, startY, "E-COMMERCE WITH DIGITAL MARKETING");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.05f, startY, "TW391");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.18f, startY, "3");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.28f, startY, "T / TH");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.42f, startY, "19:00:00-20:50:00 / 19:00:00-20:50:00");
    drawText(GLUT_BITMAP_HELVETICA_12,  0.85f, startY, "ONLINE / F1206");

    glColor3f(0.70f, 0.62f, 0.52f);
    glBegin(GL_LINES);
        glVertex2f(-0.99f, startY - 0.08f);
        glVertex2f( 0.99f, startY - 0.08f);
    glEnd();

    glColor3f(0.65f, 0.25f, 0.15f);
    drawText(GLUT_BITMAP_HELVETICA_18, -0.98f, startY - 0.15f, "TOTAL UNITS 15");

    glColor3f(0.70f, 0.62f, 0.52f);
    glBegin(GL_LINES);
        glVertex2f(-0.99f, startY - 0.18f);
        glVertex2f( 0.99f, startY - 0.18f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1500, 600); 
    glutCreateWindow("Earth Tone Enrollment Layout");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}