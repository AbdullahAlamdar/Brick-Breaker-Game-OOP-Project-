//============================================================================
// Name        : game.cpp
// Author      : Abdullah
// Version     :
// Copyright   : (c) Reserved
// Description : Brick Breaker
//============================================================================

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_

#include "util.h"
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib> // for basic math functions such as cos, sin, sqrt

using namespace std;

class Game;

class Paddle {
protected:
    int x_axis;
    int y_axis;
    int width;
    int height;
    int movement;

public:
    Paddle() {
        x_axis = 0;
        y_axis = 0;
        width = 0;
        height = 0;
        movement = 0;
    }

    Paddle(int canvas_width, int canvas_height, int paddle_width, int paddle_height, int movement) {
        x_axis = canvas_width - paddle_width;
        y_axis = 20;
        width = paddle_width;
        height = paddle_height;
        this->movement = movement;
    }

    void Draw_paddle() {
        DrawRoundRect(x_axis, y_axis, width, height, colors[WHITE], 10);
    }

    void set_x(int x) {
        x_axis = x;
    }

    int get_x() {
        return x_axis;
    }

    int get_y() {
        return y_axis;
    }

    int get_width() {
        return width;
    }

    int get_height() {
        return height;
    }
    void increase_size(){
        width=width+6;
    }
    void decrease_size(){
        width=width-6;
    }
};

class Ball:public Paddle {
private:
    int x_axis;
    int y_axis;
    int velocity_x;
    int velocity_y;
    float radius;
    int lives;

public:
    Ball() {
        x_axis = 0;
        y_axis = 0;
        velocity_x = 0;
        velocity_y = 0;
        radius = 0.0;
        lives=0;
    }

    Ball(int x_axis, int y_axis, float radius, int v_x, int v_y,int lives) {
        this->x_axis = x_axis;
        this->y_axis = y_axis;
        this->radius = radius;
        velocity_x = v_x;
        velocity_y = v_y;
        this->lives=lives;
    }

    void movement() {
        x_axis += velocity_x;
        y_axis += velocity_y;
        if (x_axis < 0) {
            velocity_x *= -1;
        }
        if (y_axis > 840) {
            velocity_y *= -1;
        }
        if (x_axis > 1020) {
            velocity_x *= -1;
        }
    }

    void update_movement() {
        velocity_y *= -1;
    }

    void movement_after_brick_ball_collision() {
        velocity_y *= -1;
    }

    void movement_after_brick_ball_collision_vertical() {
        velocity_x *= -1;
    }

    void draw_ball() {
        DrawCircle(x_axis, y_axis, radius, colors[LIME_GREEN]);
    }

    int get_x() {
        return x_axis;
    }

    int get_y() {
        return y_axis;
    }

    int get_radius() {
        return radius;
    }
    int get_velocity_x(){
        return velocity_x;
    }
    int get_velocity_y(){
        return velocity_y;
    }
    int get_lives(){
        return lives;
    }
    void slow_down(){
        velocity_x-=3;
        velocity_y-=3;
    }
    void speed_up(){
        velocity_x+=3;
        velocity_y+=3;
    }
    void ball_rebirth(){
        lives--;
        x_axis=400;
        y_axis=200;
        if(lives==0){
            x_axis=0;
            y_axis=0; 
            Paddle::x_axis=0;
        }
    }
    void draw_lives_and_game_over(){
            DrawString(1000,1000,10,2.0,("Ball Lives : " + to_string(lives)));
            if(lives==0){
        DrawString(500,400,200,2.0,("GAME OVER"));  
        }
    }
    
};

class Bricks : public Ball {
protected:
    int brick_width;
    int reduced_health;
    int brick_height;
    int brick_x;
    int brick_y;
    bool destroyed;
    int brick_health;
    ColorNames brick_color[6] = {FOREST_GREEN, HOT_PINK, DARK_BLUE, DARK_RED, GOLD,GRAY};
    ColorNames random_color;

public:
    Bricks() {
        brick_width = 0;
        brick_height = 0;
        brick_x = 0;
        brick_y = 0;
        destroyed=false;
        brick_health=0;
    }

    Bricks(int width, int height, int x_axis, int y_axis, int received_color) {
        brick_width = width;
        brick_height = height;
        brick_x = x_axis;
        brick_y = y_axis;
        destroyed=false;
        brick_health=120;
        random_color = brick_color[received_color];
    }

    void Draw_brick() {
        if(!destroyed)
        DrawRectangle(brick_x, brick_y, brick_width, brick_height, colors[random_color]);
    }

    int get_brick_x() {
        return brick_x;
    }

    int get_brick_y() {
        return brick_y;
    }

    int get_brick_width() {
        return brick_width;
    }

    int get_brick_height() {
        return brick_height;
    }
    bool get_destroyed(){
        return destroyed;
    }
    void reduce_brick_health(){
    if (random_color == FOREST_GREEN) {
        brick_health -= 120;
    } else if (random_color == HOT_PINK || random_color == GOLD) {
        brick_health -= 60;
    } else {
        brick_health -= 40; 
    }
    if (brick_health <= 0) {
        destroyed = true;
    }
    }
    void set_destroyed_to_true(){
        destroyed=true;
    }
    void delete_brick(){
        brick_x=0;
        brick_y=0;
        brick_width=0;
        brick_height=0;
        destroyed=true;
        brick_health=0;
    }
};
class PowerUps{
    private:
    int x_axis;
    int y_axis;
    int shape;
    int type;
    bool active;
    time_t activation_time;
    /*1. shape=triangle green , double paddle size
      2. shape=square pink half paddle size
      3.shape=circle blue  slow ball speed for 5s
      4.shape=rectangle  red speeds ball for 5s
      5. shape=square yellow     two more balls for 5s */
    public:
    PowerUps(int x, int y, int shape, int type){
        x_axis=x;
        y_axis=y;
        this->shape=shape;
        this->type=type;
        active=false;
        activation_time=0;
    }
    void draw_power_ups(){
        if(shape==1){
            DrawTriangle(x_axis,y_axis,x_axis+5,y_axis+5,x_axis+10,y_axis+10,colors[FOREST_GREEN]);
        }
        else if(shape==2){
            DrawSquare(x_axis,y_axis,7,colors[HOT_PINK]);
        }
        else if(shape==3){
            DrawCircle(x_axis,y_axis,7,colors[DARK_BLUE]);
        }
        else if(shape==4){
            DrawRectangle(x_axis,y_axis,7,4,colors[DARK_RED]);
        }
        else if(shape==5){
            DrawSquare(x_axis,y_axis,7,colors[GOLD]);
        }
    }
    void apply_power_ups(Ball& ball , Paddle& paddle){
         if(type==1){
            paddle.increase_size();
         }
         if(type==2){
            paddle.decrease_size();
         }
         if(type==3){
            ball.slow_down();
         }
         if(type==4){
            ball.speed_up();
         }
         active=true;
         activation_time=time(nullptr);
    }
    void powerup_skeleton(){
          draw_power_ups();
    }

};
class Menu{
    protected:
    bool is_menu_active;
    int button_x;
    int button_y;
    int button_width;
    int button_height;
    string button_text;
    public:
    Menu(){
        is_menu_active=true;
        button_x=0;
        button_y=0;
        button_width=0;
        button_height=0;
        button_text="XYZ";
    }
    Menu(int button_x,int button_y,int button_width,int button_height,string button_text){
        is_menu_active=true;
        this->button_x=button_x;
        this->button_y=button_y;
        this->button_width=button_width;
        this->button_height=button_height;
        this->button_text=button_text;
    }
    void Draw_button(){
        DrawRectangle(button_x,button_y,button_width,button_height,colors[WHITE]);
        DrawString(button_x + 5, button_y + button_height / 2, 10,1.0, button_text.c_str());
    }
    bool is_button_clicked(int mouse_x,int mouse_y){
        return (mouse_x >= button_x && mouse_x <= (button_x + button_width) &&
                mouse_y >= button_y && mouse_y <= (button_y + button_height));
    }  
};

class Game : public Paddle, public Ball, public Bricks , public Menu{
protected:
    int score;
    bool collision;
    Paddle paddle;
    Ball ball;
    Bricks bricks[20][15];
    Menu menu;
    int brick_rows = 20;
    int brick_cols = 15;

public:
    friend void Timer(int);

    Game() : paddle(540, 420, 90, 20, 10), ball(400, 200, 10.0, 6, 6,3) {
        make_level1();
        if(score>=1500){
            score=0;
          make_level2();
          if(score>=375){
            score=0;
            make_level3();

          }
          
        } 
       score=0;
    }
    void initialize_menu(){
        menu=Menu(200,300,200,60,"PLAY");
    }

    void game_skeleton() {
        if(is_menu_active){
            menu.Draw_button();
        }
        //ball_rebirth();
        draw_score_bar();
        paddle.Draw_paddle();
        ball.draw_ball();
        // drawing brick layout
        for (int i = 0; i < brick_rows; i++) {
            for (int j = 0; j < brick_cols; j++) {
                if (!(bricks[i][j].get_destroyed())){
                    bricks[i][j].Draw_brick();
                }
            }
        }
        draw_top_boundary_of_canvas();
    }

    Paddle& get_paddle() {
        return paddle;
    }

    Ball& get_ball() {
        return ball;
    }

    Bricks& get_brick(int i, int j) {
        return bricks[i][j];
    }

    int get_brick_rows() {
        return brick_rows;
    }

    int get_brick_cols() {
        return brick_cols;
    }

    void make_level1() {
        int width = 60;
        int height = 20;
        int start_x = 50;
        int start_y = 800;
        for (int i = 0; i < brick_rows; i++) {
            for (int j = 0; j < brick_cols; j++) {
                int x = start_x + j * width;
                int y = start_y - i * height;
                bricks[i][j] = Bricks(width, height, x, y, rand() % 5);
            }
        }
    }
    void make_level2(){
        int width = 30;
        int height = 10;
        int start_x = 50;
        int start_y = 800;
        for (int step = 0; step < 3; step++) {
            for (int row = 0; row < 5; row++) {
                for (int col = 0; col < 5; col++) {
                    int x = start_x + col * width + step * (width * 5);  
                    int y = start_y - row * height;
                    bricks[row + step * 5][col] = Bricks(width, height, x, y, rand() % 5);
                }
            }
            start_y -= height * 5; 
        }
    }
    void make_level3(){
        int width=30;
        int height=10;
        int start_x=50;
        int start_y=800;
        int i;
        int j;
        int n=9;
        int c1=(n-1)/2;
        int c2=3*n/2-1;
        int x;
        int y;
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if(i+j<=c1||i-j>=c1||j-i>=c1||i+j>c2){
                    x=start_x+j*width;
                    y=start_y-1*width;
                    
                }
                else{
                  
                }
            }
            
            bricks[i][j]=Bricks(width,height,x,y,rand()%5);
        }
    }

    


void brick_ball_collision_detection() {
    for (int i = 0; i < brick_rows; i++) {
        for (int j = 0; j < brick_cols; j++) {
            if (bricks[i][j].get_destroyed()) {
                continue; // for Skiping  destroyed bricks
            }

            int brickX = bricks[i][j].get_brick_x();
            int brickY = bricks[i][j].get_brick_y();
            int brickWidth = bricks[i][j].get_brick_width();
            int brickHeight = bricks[i][j].get_brick_height();
            int ballX = ball.get_x();
            int ballY = ball.get_y();
            int ballRadius = ball.get_radius();
            if (ballX + ballRadius >= brickX && ballX - ballRadius <= brickX + brickWidth &&
                ballY + ballRadius >= brickY && ballY - ballRadius <= brickY + brickHeight) {
                    ball.movement_after_brick_ball_collision();
                     ball.movement_after_brick_ball_collision_vertical();
                //  collision based on ball movement direction
                if (ball.get_velocity_x() > 0 && ballX - ballRadius <= brickX + brickWidth) {
                    // Collision from the left
                    ball.movement_after_brick_ball_collision_vertical();
                } else if (ball.get_velocity_x() < 0 && ballX + ballRadius >= brickX) {
                    // Collision from the right
                    ball.movement_after_brick_ball_collision_vertical();
                } else if (ball.get_velocity_y() > 0 && ballY - ballRadius <= brickY + brickHeight) {
                    // Collision from the top
                    ball.movement_after_brick_ball_collision();
                } else {
                    // Collision from the bottom
                    ball.movement_after_brick_ball_collision();
                }
                //reduce_brick_health();
                bricks[i][j].set_destroyed_to_true();
                score+=5;
                collision=true;
                int random_shape = rand() % 5 + 1;
                int random_type = rand() % 4 + 1;
                PowerUps power_up(brickX, brickY, random_shape, random_type);
                //power_up.draw_power_ups();
                //power_up.apply_power_ups(ball, paddle); 

                break; // Exiting inner loop after first collision
            }
        }
    }
}
void draw_top_boundary_of_canvas(){
    Bricks top_line[10];
    int startx=0;
    int starty=830;
    int width=100;
    int height=15;
    for(int i=0;i<10;i++){
           int x=startx+i*width;
          top_line[i]=Bricks(width,height,x,starty,5);
          top_line[i].Draw_brick();
    }
}
void draw_score_bar(){
DrawString(50, 950, 10, 2.0, ("Score: " + to_string(score)).c_str());
DrawString(50, 1000, 5.0, 2.0, ("Abdullah  23i-2597"));
int startx=130;
int starty=950;
int width=40;
int height=10;
Bricks score_bar;
score_bar=Bricks(width,height,startx,starty,5);
score_bar.Draw_brick();
if (score > 0) {
        int additional_width = score / 5; 
        score_bar.set_destroyed_to_true(); 
        score_bar = Bricks(width + additional_width, height, startx, starty, 5);
    }
    score_bar.Draw_brick();
}
};

void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

Game A;

void GameDisplay() {
    glClearColor(0, 0, 0, 0); // Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT); //Update the colors
    A.game_skeleton();
    if(A.get_ball().get_lives()==0){
        A.get_ball().draw_lives_and_game_over();
    }
    glutSwapBuffers(); // do not modify this line..
}

void NonPrintableKeys(int key, int x, int y) {
    if (key == GLUT_KEY_RIGHT) {
        A.get_paddle().set_x(A.get_paddle().get_x() + 10);
    }
    else if (key == GLUT_KEY_LEFT) {
        A.get_paddle().set_x(A.get_paddle().get_x() - 10);
    }
    glutPostRedisplay();
}

void PrintableKeys(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(1);
    }
    glutPostRedisplay();
}

void Timer(int m) {
    A.get_ball().movement();
    bool collision;

    int ballX = A.get_ball().get_x();
    int ballY = A.get_ball().get_y();
    int ballRadius = A.get_ball().get_radius();
    int paddleX = A.get_paddle().get_x();
    int paddleY = A.get_paddle().get_y();
    int paddleWidth = A.get_paddle().get_width();
    int paddleHeight = A.get_paddle().get_height();

    if (ballX + ballRadius >= paddleX && ballX - ballRadius <= paddleX + paddleWidth && ballY + ballRadius >= paddleY && ballY - ballRadius <= paddleY + paddleHeight) {
        collision = true;
    }
    else {
        collision = false;
    }

    if (collision) {
        A.get_ball().update_movement();
    }
    int ball_life=A.get_ball().get_lives();
    if(A.get_ball().get_y()<0&&ball_life>0){
        A.get_ball().ball_rebirth();
    }
    if(ball_life>0){
       A.brick_ball_collision_detection();
    }
    

    glutTimerFunc(1000.0 / 60, Timer, 0);
    glutPostRedisplay();
}

void MousePressedAndMoved(int x, int y) {
    glutPostRedisplay();
}

void MouseMoved(int x, int y) {
    A.get_paddle().set_x(x - 40);
    glutPostRedisplay();
}

void MouseClicked(int button, int state, int x, int y) {
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    int width = 1020, height = 1020;

    InitRandomizer();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(width, height);
    glutCreateWindow("BRICK BREAKER");
    SetCanvasSize(width, height);
    glutDisplayFunc(GameDisplay);
    glutSpecialFunc(NonPrintableKeys);
    glutKeyboardFunc(PrintableKeys);
    glutTimerFunc(1000.0, Timer, 0);
    glutMouseFunc(MouseClicked);
    glutPassiveMotionFunc(MouseMoved);
    glutMotionFunc(MousePressedAndMoved);

    glutMainLoop();
    return 1;
}

#endif /* CENTIPEDE_CPP_ */
