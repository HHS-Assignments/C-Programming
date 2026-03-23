#include <GL/glut.h>  // GLUT library for window and input handling
#include <math.h>    // For mathematical functions

float rect2X = 0;
float rect2Y = 0;
float rotation = 0;  // Rotation angle for the main square

// Keyboard handler - responds to WASD keys to move the blue square
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        rect2Y += 0.01f;  // Move up
        break;
    case 's':
        rect2Y -= 0.01f;  // Move down
        break;
    case 'a':
        rect2X -= 0.01f;  // Move left
        break;
    case 'd':
        rect2X += 0.01f;  // Move right
        break;
    case 'r':
        rotation += 5.0f;  // Rotate with 'r' key
        if (rotation >= 360.0f) rotation -= 360.0f;
        break;
    case 27:  // Escape key
        exit(0);
        break;
    }
    glutPostRedisplay();  // Redraw the window
}

// Display callback - renders all graphics
void display() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Dark gray background
    glClear(GL_COLOR_BUFFER_BIT);
    
    /* Draw RED rotating square with glRotatef */
    glPushMatrix();  // Save current transformation matrix
    glRotatef(rotation, 0.0f, 0.0f, 1.0f);  // Rotate around Z-axis
    
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.2f, 0.2f);  // Red color
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();
    
    glPopMatrix();  // Restore transformation matrix
    
    /* Draw GREEN triangle using glScalef */
    glPushMatrix();
    glTranslatef(0.6f, 0.6f, 0.0f);  // Move to top-right
    glScalef(0.3f, 0.3f, 1.0f);      // Scale the triangle
    
    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 1.0f, 0.2f);  // Green color
    glVertex2f(0.0f, 0.5f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();
    
    glPopMatrix();
    
    /* Draw YELLOW triangle */
    glPushMatrix();
    glTranslatef(-0.6f, 0.6f, 0.0f);  // Move to top-left
    glScalef(0.3f, 0.3f, 1.0f);       // Scale the triangle
    
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 0.2f);  // Yellow color
    glVertex2f(0.0f, 0.5f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();
    
    glPopMatrix();
    
    /* Draw BLUE movable square */
    glColor3f(0.2f, 0.4f, 1.0f);  // Blue color
    glRectf(-0.1f + rect2X, -0.1f + rect2Y, 0.1f + rect2X, 0.1f + rect2Y);
    
    glFlush();  // Render now
}

// Reshape callback - handles window resize
void reshape(int w, int h) {
    if (h == 0) h = 1;  // Prevent division by zero
    
    glViewport(0, 0, w, h);  // Set viewport to window dimensions
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Set orthographic projection
    float aspect = (float)w / (float)h;
    if (w >= h) {
        glOrtho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    } else {
        glOrtho(-1.0f, 1.0f, -1.0f/aspect, 1.0f/aspect, -1.0f, 1.0f);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("OpenGL Enhanced Demo");
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    
    glutDisplayFunc(display);      // Register display callback
    glutReshapeFunc(reshape);      // Register reshape callback
    glutKeyboardFunc(keyboard);    // Register keyboard callback
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glutMainLoop();  // Enter event-processing loop
    return 0;
}
