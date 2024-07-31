
#include<stdlib.h>
#include<ctime>
#include <windows.h>
#include <GL/glut.h>
#include <Math.h>
#include<stack>
#include<iostream>
#include<vector>
#include<string>


using namespace std;



GLfloat column = 40;
GLfloat row = 40;

char title[] = "Full-Screen & Windowed Mode";
int windowWidth = 700;
int windowHeight = 450;
int windowPosX = 0;
int windowPosY = 0;


GLfloat snakeX = 320;
GLfloat snakeY = 200;

GLfloat snakeXMax = column - 1, snakeXMin = 1, snakeYMax = row - 1, snakeYMin = 1;
GLdouble transaction = 1;

int fps = 20;
int dirction = 0;

int last_dirction = dirction;

GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
GLfloat p1 = 20.0f, p2 = 20.0f;
bool fullScreenMode = true;
int count = 1;

int length = 60;
int score = 0;

int foodx = 10;
int foody = 10;

vector<float> all_x(length + 5);
vector <float>all_y(length + 5);

bool food_eaten = false;
bool game_over = false;
float angle = 0.0;


float head_x;
float head_y;




void initGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
}



void check_next_move() {

    if (dirction == 1 && last_dirction == 2)
    {
        dirction = last_dirction;
    }
    else if (dirction == 2 && last_dirction == 1)
    {
        dirction = last_dirction;
    }
    else if (dirction == 3 && last_dirction == 4)
    {
        dirction = last_dirction;
    }
    else if (dirction == 4 && last_dirction == 3)
    {
        dirction = last_dirction;
    }

}
void move_right() {
    head_x = all_x[1] += transaction;
    if (all_x[1] >= snakeXMax)
        head_x = all_x[1] = snakeXMin;

}


void move_left() {
    head_x = all_x[1] -= transaction;
    if (all_x[1] <= snakeXMin)
        head_x = all_x[1] = snakeXMax;
}
void move_up() {
    head_y = all_y[1] += transaction;
    if (all_y[1] >= snakeYMax)
        head_y = all_y[1] = snakeYMin;
}

void move_down() {
    head_y = all_y[1] -= transaction;
    if (all_y[1] <= snakeYMin)
        head_y = all_y[1] = snakeYMax;
}

bool checkCollision() {
    for (int i = 4; i < score; i++) {
        if (all_x[i] == head_x && all_y[i] == head_y)
            return true;
    }

    return false;
}
void move_snake() {

    check_next_move();


    if (dirction == 1)
    {

        move_right();

    }
    else if (dirction == 2)
    {

        move_left();

    }
    else if (dirction == 3)
    {
        move_up();

    }
    else if (dirction == 4)
    {
        move_down();

    }

    if (checkCollision())
        game_over = true;

}

void update_snake_body() {

    if (length > score)
    {

        all_x.push_back(p1);
        all_y.push_back(p2);
        score++;
    }


}

void random(int& x, int& y) {

    srand(time(NULL));
    foodx = snakeXMin + rand() % (int)(snakeXMax - snakeXMin * 4);
    foody = snakeYMin + rand() % (int)(snakeYMax - snakeXMin * 4);


}



void food() {



    if (foodx == all_x[0] && foody == all_y[0] || foodx == all_x[0] + transaction && foody == all_y[0] + transaction)
        food_eaten = true;

    if (food_eaten)
        update_snake_body();

    if (food_eaten)
        random(foodx, foody);

    food_eaten = false;

    glColor3f(1, 0, 0);
    glRectd(foodx + transaction, foody + transaction, foodx, foody);


    glEnd();


}

void draw_snake() {






    for (int i = score + 2; i > 1; i--)
    {
        all_x[i] = all_x[i - 1];
        all_y[i] = all_y[i - 1];

    }
    all_x[0] = head_x;
    all_y[0] = head_y;


    glPushMatrix();
    for (size_t i = 1; i < score + 1; i++)
    {

        glRectd(all_x[i] + transaction, all_y[i] + transaction, all_x[i], all_y[i]);
        if (i == 0)
            glColor3f(1, 1, 1);
        else
            glColor3f(0, 0, 1);

    }
    glColor3f(1, 1, 1);

    glRectd(head_x + (transaction), head_y + (transaction), head_x, head_y);

    glEnd();
    glPopMatrix();
}


void display() {



    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();



    draw_snake();
    food();



    glutSwapBuffers();
    move_snake();

    if (game_over)
    {
        MessageBoxA(NULL, "", "Game Over", 0);

        exit(0);
    }


}


void reshape(GLsizei width, GLsizei height) {

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, column, 0.0, row, -1.0, 1.0);



}


void Timer(int value) {

    glutPostRedisplay();
    glutTimerFunc(1000 / fps, Timer, 0);
}


void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
        exit(0);
        break;
    }
}


void specialKeys(int key, int x, int y) {

    last_dirction = dirction;
    switch (key) {
        //case GLUT_KEY_F1:    // F1: Toggle between full-screen and windowed mode
        //    fullScreenMode = !fullScreenMode;         // Toggle state
        //    if (fullScreenMode) {                     // Full-screen mode
        //        windowPosX = glutGet(GLUT_WINDOW_X); // Save parameters for restoring later
        //        windowPosY = glutGet(GLUT_WINDOW_Y);
        //        windowWidth = glutGet(GLUT_WINDOW_WIDTH);
        //        windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        //        glutFullScreen();                      // Switch into full screen
        //    }
        //    else {                                         // Windowed mode
        //        glutReshapeWindow(windowWidth, windowHeight); // Switch into windowed mode
        //        glutPositionWindow(windowPosX, windowPosX);   // Position top-left corner
        //        }
        //    break;

    case GLUT_KEY_RIGHT:

        dirction = 1;
        break;
    case GLUT_KEY_LEFT:

        dirction = 2;
        break;
    case GLUT_KEY_UP:

        dirction = 3;
        break;
    case GLUT_KEY_DOWN:

        dirction = 4;
        break;

    }


}

int main(int argc, char** argv) {
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(windowWidth, windowHeight);  // Initial window width and height
    glutInitWindowPosition(windowPosX, windowPosY); // Initial window top-left corner (x, y)
    glutCreateWindow(title);      // Create window with given title
    glutDisplayFunc(display);     // Register callback handler for window re-paint
    glutReshapeFunc(reshape);     // Register callback handler for window re-shape
    glutTimerFunc(10, Timer, 0);   // First timer call immediately
    glutSpecialFunc(specialKeys); // Register callback handler for special-key event
    glutKeyboardFunc(keyboard);   // Register callback handler for special-key event
    // glutFullScreen();             // Put into full screen
    initGL();                     // Our own OpenGL initialization
    glutMainLoop();               // Enter event-processing loop
    return 0;
}
