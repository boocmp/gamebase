#pragma once

#include "../graphics/graphics.h"

#include <functional>
#include <memory>
#include <vector>

// class State{
//     public:
//     virtual void Enter(){}
//     virtual void Exit(){}
//     virtual void Update(){}
// };

// class StateMachine{
//     void SetDicision(Uint32 millis){
//         if (millis == 100) return;
//     }
// };

class Animal {
    public:
    enum States {_Moving, Find_Grass, _Eating, Die};
    States _state;
    public:
    virtual void ChangeState(States newState){
        _state = newState;
    }
    virtual ~Animal(){};
    virtual void Render() = 0;
    virtual void Moving() = 0;
    virtual int FindFood() = 0;
    virtual int GoingToFood() = 0;
    virtual void Eating() = 0;
    virtual void Died() = 0;
    //virtual void Update(Uint32 millis) = 0;
};

class Duck: public Animal {
    private:
    int move_frame = 0;
    int eating_frame = 0;
    int die_frame = 0;
    public:
    Duck (int x, int y){
        this->x = x;
        this->y = y;
    }

    void Moving() override {
        render::DrawImageFromAtlas("duck", animation, move_frame/4, x, y);
        move_frame++;
        if (x < 200 || x > 600 || y < 150 || y > 400) {
        switch (direction)
        {
        case 0:
            direction = 3;
            animation = "down_right";
            break;
        case 1:
            direction = 2;
            animation = "down_left";
            break;
        case 2:
            direction = 1;
            animation = "up_right";
            break;
        case 3:
            direction = 0;
            animation = "up_left";
            break;
        case 4:
            direction = 5;
            animation = "down";
            break;
        case 5:
            direction = 4;
            animation = "up";
            break;
        case 6:
            direction = 7;
            animation = "right";
            break;
        case 7:
            direction = 6;
            animation = "left";
            break;
        }
        move_frame = 0;
        }
        if (move_frame < 120) {
            if (direction == 0 || direction == 1 || direction == 4) y--;
            if (direction == 2 || direction == 3 || direction == 5) y++;
            if (direction == 1 || direction == 3 || direction == 7) x++;
            if (direction == 0 || direction == 2 || direction == 6) x--;
            return;
        }
        move_frame = 0;
        int dir = direction;
        direction = rand() % 8;
        switch (direction)
        {
        case 0:
            animation = "up_left";
            break;
        case 1:
            animation = "up_right";
            break;
        case 2:
            animation = "down_left";
            break;
        case 3:
            animation = "down_right";
            break;
        case 4:
            animation = "up";
            break;
        case 5:
            animation = "down";
            break;
        case 6:
            animation = "left";
            break;
        case 7:
            animation = "right";
            break;
        }
        // animation = [&]() {
        //     if (up && left) return "up_left";
        //     if (up && right) return "up_right";
        //     if (down && left) return "down_left";
        //     if (down && right) return "down_right";

        //     if (up) return "up";
        //     if (down) return "down";
        //     if (left) return "left";
        //     if (right) return "right";

        //     return "down";
        // }();
        //if (left + right + up + down > 0) move_frame++;
    }
    
    int FindFood(){
        if ((this->x - x)*(this->x - x) + (this->y - y)*(this->y - y) < d_x*d_x + d_y*d_y) {
            d_x = this->x - x;
            d_y = this->y - y;
        }
        if (d_x == 1000 && d_y == 1000) return 0;
        return 1;
        delta = abs(d_x/d_y);
    }

    int GoingToFood(){
        if (d_y > 0 && d_x > 0) { y++;   x += delta;   d_y--;   d_x -= delta;}
        else if (d_y > 0 && d_x < 0) { y++;   x -= delta;   d_y--;   d_x += delta;}
        else if (d_y < 0 && d_x > 0) { y--;   x += delta;   d_y++;   d_x -= delta;}
        else if (d_y < 0 && d_x < 0) { y--;   x -= delta;   d_y++;   d_x += delta;}

        if (d_x > 0) render::DrawImageFromAtlas("duck", "right", move_frame/4, x, y);
        else if (d_x < 0) render::DrawImageFromAtlas("duck", "left", move_frame/4, x, y);

        if (move_frame != 35) move_frame++;
        else move_frame = 0;

        if (d_x == 0 && d_y == 0) return 1;
        return 0;
    }
    
    void Eating(){
        render::DrawImageFromAtlas("duck_eating", "duck_eating", eating_frame/8, x, y);
        if (eating_frame != 63) eating_frame++;
        else eating_frame = 0;
    }

    void Died(){
        render::DrawImageFromAtlas("duck_die", "duck_die", die_frame/8, x, y);
        if (die_frame != 53) die_frame++;
        die_frame = 0;
    }

    // void Update(Uint32 millis){
    //     t += millis;
    //     if (t > 200){  // For example, 200
    //         Died();
    //         return;
    //     }
    //     if (t < 100) {  // For example, 100
    //         Moving();
    //         return;
    //     }
    //     if (FindFood()) {
    //         if (GoingToFood()) {
    //             Eating();
    //             t -= 10;   // For example, 10
    //         }
    //     else Moving;
    // }

    void Render() override {
        render::DrawImageFromAtlas("duck", animation, move_frame/4, x, y);
    }
    
    private:
    std::string animation = "up_left";
    int x, y;
    int f_x = x, f_y = y;
    int d_x = 1000, d_y = 1000;
    int direction = 0;
    int delta;
    Uint32 t = 0;
};

class Grass {
    public:
    Grass (int x, int y){
        this->x = x;
        this->y = y;
    }
    void Render(){
        render::DrawImageFromAtlas("grass", "grass", frame/4, x, y);
    //     render::DrawImageFromAtlas("grass", "grass", frame/4, x+30, y+30);
    //     render::DrawImageFromAtlas("grass", "grass", frame/4, x+20, y);
    //     render::DrawImageFromAtlas("grass", "grass", frame/4, x-30, y);
    //     render::DrawImageFromAtlas("grass", "grass", frame/4, x, y+30);
    }
    void Grow(){
        if (frame == 23) return;
        frame++;
    }
    private:
    int x, y;
    int frame = 0;
};
