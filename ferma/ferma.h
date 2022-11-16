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
//     public:
//     State CurrentState;

//     void Initialize(State startState){
//         CurrentState = startState;
//         CurrentState.Enter();
//     }

//     void ChangeState (State newState){
//         CurrentState.Exit();
//         CurrentState = newState;
//         CurrentState.Enter();
//     }
// };

// class MovingState: public State{
//     public:
//     void Enter() override {
//         base.Enter();
//     }

//     void Exit() override {
//         base.Exit();
//     }

//     void Update() override {
//         base.Update();
//     }
// };

class Grass {
    public:
    void Render(int x, int y){
        render::DrawImageFromAtlas("grass", animation, frame/4, x, y);
    }
    void Grow(){
        if (animation == "g_1") animation = "g_2";
        else if (animation == "g_2") animation = "g_3";
        else if (animation == "g_3") animation = "g_4";
        else if (animation == "g_4") animation = "g_5";
        else if (animation == "g_5") animation = "g_6";
        else if (animation == "g_6") animation = "g_7";
        frame++;
    }
    private:
    std::string animation = "g_1";
    int frame = 0;
};

class Animal {
    public:
    enum States {_Moving, FindingGrass, Eating, Dying};
    private: States _state;
    public:
    void ChangeState(States newState){
        _state = newState;
    }
    virtual ~Animal(){};
    virtual void Render() = 0;
    virtual void Moving() = 0;
    //virtual void Create(int _x, int _y) = 0;
};

class Duck: public Animal {
    private:
    int move_frame = 0;
    public:
    // void Create(int _x, int _y) override {
    //     x = _x;
    //     y = _y;
    // }
    void Moving() override {
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
    void Render() override {
        render::DrawImageFromAtlas("duck", animation, move_frame/4, x, y);
    }
    private:
    std::string animation = "up_left";
    int x = 300, y = 300;
    int direction = 0;
};