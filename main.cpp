#include<iostream>
#include<raylib.h>
using namespace std;


Color Green=Color{38,185,154,255};
Color Dark_Green=Color{20,160,133,255};
Color Light_Green=Color{129,204,184,255};
Color Yellow=Color{243,213,91,255};



int cpu_score=0;
int player_score=0;

class Ball{
    public:
    int radius;
    float x,y;
    int speedx,speedy;
    void draw(){
        DrawCircle(x,y,radius,Yellow); 
    }
    void update(){
        x+=speedx;
        y+=speedy;
        if(y + radius >=GetScreenHeight()||y-radius<=0){
            speedy*=-1;
        }
        if(x + radius >=GetScreenWidth()){
            cpu_score++;
            resetBall();
        }
        if(x - radius <=0){
            player_score++;
            resetBall();
        }
        
        
    }

    void resetBall(){
        x=GetScreenWidth()/2;
        y=GetScreenHeight()/2;

        int speed_choice[2] = {-1,1};
        speedx*=speed_choice[GetRandomValue(0,1)];
        speedy*=speed_choice[GetRandomValue(0,1)];
    }
};


class Paddle{
    protected:
    void limitMovment(){
        if(y<=0){
            y=0;
        }
        if(y+height>=GetScreenHeight()){
            y=GetScreenHeight()-height;
        }
    }


    public:
    float x,y;
    float width, height;
    int speed;
    void draw(){
        DrawRectangleRounded(Rectangle{x,y,width,height},0.8,0,WHITE);
    }
    void update(){
        
        if(IsKeyDown(KEY_UP)){
            y=y-speed;
        }
        if(IsKeyDown(KEY_DOWN)){
            y=y+speed;
        }
        limitMovment();
    }

};

class CpuPaddle :public Paddle{
    public:
    void update(int ball_y){
        if(y+height/2>ball_y){
            y=y-speed;
        }
        if(y+height/2<ball_y){
            y+=speed;
        }
        limitMovment();
    }

};


int main(){
    const int screen_width=1280;
    const int screen_height=700;
    Ball ball;
    Paddle p;
    CpuPaddle cp;

    ball.radius=20;
    ball.speedx=7;
    ball.speedy=7;
    ball.x=screen_width/2;
    ball.y=screen_height/2;

    p.y=screen_height/2-50;
    p.x=screen_width-30;
    p.height=100;
    p.width=20;
    p.speed=6;

    cp.x=10;
    cp.y=(screen_height/2)-100/2;
    cp.height=100;
    cp.width=20;
    cp.speed=6;


    
    InitWindow(screen_width,screen_height,"my pong game");
    SetTargetFPS(60);
    while(WindowShouldClose()==false){
        BeginDrawing();
       
        
        //updating the ball position
        ball.update();
        p.update();
        cp.update(ball.y);
        
        //clear the back ground
        ClearBackground(Dark_Green);
        DrawRectangle(screen_width/2,0,screen_width/2,screen_height,Green);
        DrawCircle(screen_width/2,screen_height/2,150,Light_Green);
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{p.x,p.y,p.width,p.height})){
            ball.speedx*=-1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{cp.x,cp.y,cp.width,cp.height})){
            ball.speedx*=-1;
        }
        //drawing 
        DrawLine(screen_width/2,0,screen_width/2,screen_height,WHITE);
        ball.draw();
        p.draw();
        
        cp.draw();

        DrawText(TextFormat("%i",cpu_score),screen_width/4,20,80,WHITE);
        DrawText(TextFormat("%i",player_score),3*screen_width/4,20,80,WHITE);



        EndDrawing();
    }
    CloseWindow();
    return 0;
}