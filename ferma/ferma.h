#pragma once

#include "../graphics/graphics.h"

#include <functional>
#include <memory>
#include <vector>


class Food {
    public:
    Food (int mass){
        this->mass = mass;
    }
    virtual ~Food() = default;
    int Eat(int p){
        if (mass > p) {
            mass-=p;
            return p;
        } else {
            int r = mass;
            mass = 0;
            return r;
        }
    }
    int Grow(int p){
        mass+=p;
    }
    bool IsEaten() const{
        return mass <= 0;
    }
    private:
    int mass;
};

class Grass : public Food{
    public:
    Grass (int x, int y) : Food(10) {
        this->x = x;
        this->y = y;
    }

    void AddGrass(int x, int y, int frame){
        int i = 0;
        while (grass[i] != 0 && grass[i+1] != 0 && i < 30) i += 2;
        grass[i] = x;
        grass[i+1] = y;
    }


    void Render(){
        render::DrawImageFromAtlas("grass", "grass", frame/4, (int)x, (int)y);
    }

    void Grow(){
        if (frame == 23) return;
        frame++;
    }

    int GetX () const{return x;}
    int GetY () const{return y;}

    private:
    int x, y;
    int frame = 0;
    int grass[30] = {0};
};

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
    virtual Grass* FindFood(const std::vector<std::unique_ptr<Grass>>& food) = 0;
    virtual int GoingToFood() = 0;
    virtual int Eating(Grass* food) = 0;
    virtual void Died() = 0;
    virtual void Update(Uint32 millis, const std::vector<std::unique_ptr<Grass>>& grass) = 0;

    virtual int GetX() = 0;
    virtual int GetY() = 0;
};

class Duck: public Animal {
    private:
    int move_frame = 0;
    int eating_frame = 0;
    int die_frame = 0;
    public:
    Duck (float x, float y){
        this->x = x;
        this->y = y;
    }

    void Moving() override {
        render::DrawImageFromAtlas("duck", animation, move_frame/4, (int)x, (int)y);
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
    
    Grass* FindFood(const std::vector<std::unique_ptr<Grass>>& grass){
        int dis = 100000000;

        Grass* closest_food = nullptr;
        for (auto& g: grass){
            if ((x - g->GetX())*(x - g->GetX()) + (y - g->GetY())*(y - g->GetY()) < dis){
                d_x = g->GetX() - x;
                d_y = g->GetY() - y;
                _x = g->GetX();
                _y = g->GetY();
                closest_food = g.get();
            }
            dis = d_x*d_x + d_y*d_y;
        }

        // for (int i = 0; i < 40; i += 2){
        //     if (food[i] == 0) continue;
        //     if ((x - grass[i]->GetX())*(x - food[i]) + (y - food[i+1])*(y - food[i+1]) < dis){
        //         d_x = food[i] - x;
        //         d_y = food[i+1] - y;
        //         _x = food[i];
        //         _y = food[i+1];
        //     }
        //     dis = d_x*d_x + d_y*d_y;
        // }

        if (dis == 100000000) return nullptr;
        dis = sqrt(dis);
        sin = abs(d_y/dis);
        cos = abs(d_x/dis);
        return closest_food;
    }

    int GoingToFood(){
        if (d_y > 0 && d_x >= 0) { y += sin * 3;   x += cos * 3;   d_y -= sin * 3;   d_x -= cos * 3;}
        else if (d_y > 0 && d_x <= 0) { y += sin * 3;   x -= cos * 3;   d_y -= sin * 3;   d_x += cos * 3;}
        else if (d_y < 0 && d_x >= 0) { y -= sin * 3;   x += cos * 3;   d_y += sin * 3;   d_x -= cos * 3;}
        else if (d_y < 0 && d_x <= 0) { y -= sin * 3;   x -= cos * 3;   d_y += sin * 3;   d_x += cos * 3;}

        if (d_x > 0) render::DrawImageFromAtlas("duck", "right", move_frame/4, (int)x, (int)y);
        else if (d_x < 0) render::DrawImageFromAtlas("duck", "left", move_frame/4, (int)x, (int)y);

        if (move_frame != 35) move_frame++;
        else move_frame = 0;

        if (abs(d_x) < cos * 3 && abs(d_y) < sin * 3) return 0;
        return 1;
    }
    
    int Eating(Grass* food){
        if (!food)
          return 0;
        render::DrawImageFromAtlas("duck_eating", "duck_eating", eating_frame/8, (int)x, (int)y);
        if (eating_frame != 100) eating_frame++;
        else {
            eating_frame = 0;
            food->Eat(3);
            return 1;
        }
        return 0;
    }

    int GetX() {return _x;}
    int GetY() {return _y;}

    void Died(){
        render::DrawImageFromAtlas("duck_die", "duck_die", die_frame/8, (int)x, (int)y);
        if (die_frame != 53) die_frame++;
        die_frame = 0;
    }

    void Update(Uint32 millis, const std::vector<std::unique_ptr<Grass>>& grass){
        t += millis;
        
        if (t < 1000) {  // For example, 100
            Moving();
            return;
        }
        if (Grass* food = FindFood(grass)) {
          if (GoingToFood()) {
            Eating(food);
            t -= 10;  // For example, 10
          } else
            Moving();
        } else
          Moving();
    }

    void Render() override {
        render::DrawImageFromAtlas("duck", animation, move_frame/4, (int)x, (int)y);
    }
    
    private:
    std::string animation = "up_left";
    float x, y, _x, _y;
    float sin, cos;
    float d_x = 1000, d_y = 1000;
    int direction = 0;
    Uint32 t = 0;
};
