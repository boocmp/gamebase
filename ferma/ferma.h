#pragma once

#include "../graphics/graphics.h"

#include <functional>
#include <memory>
#include <vector>

using MouseState = app::GameApp::MouseState;

class ClickArea{
    public:
    ClickArea(int x, int y, int w, int h){
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

    void ChangeXY(int x, int y){
        this->x = x;
        this->y = y;
    }

    bool Process(const MouseState& mouse){
        _x = (float)mouse.x;
        _y = (float)mouse.y;
        bool _click = false;
        if ((mouse.buttons & SDL_BUTTON_LMASK) != 0) {
            click = true;
        }
        else if (click) {
            _click = true;
            click = false;
        }
        if (_x >= x && _x <=x+w && _y >= y && _y<= y+h && _click){
            return true;
        }
        return false;
    }
    private:
    bool click = false;
    int x, y, w, h;
    int _x, _y;
};

class Goals{
    public:
    void Render(){
        render::DrawImageFromAtlas("money", "money", count, 710, 40);
        render::DrawImage("slash", 723, 50, 15, 15);
        render::DrawImageFromAtlas("money", "money", final_count, 736, 40);
    }
    void AchiveGoal(){
        count++;
    } 
    bool IsAchived(){
        return count == final_count;
    }
    private:
    int count = 0;
    int final_count = 4;
};

class Shop{
    public:
    Shop(int money){
        this->money = money;
    }
    void Render(){
        if (money >= 100) render::DrawImage("shop_duck", 8, 23, 45, 57);
    }
    int IsDuck(){
        return money >= 100;
    }
    void MinusDuck(){
        money -= 100;
    }
    private:
    int money;
};

class Bank{
    public:
    Bank(int money){
        this->money = money;
    }
    void Render(){
        int _money = money;
        int i = 0;
        while (_money > 0){
            render::DrawImageFromAtlas("money", "money", _money % 10, 662 - 15*i, 525);
            i++;
            _money /= 10;
        }
    }
    
    int GetMoney(){
        return money;
    }

    void WasteMoney(int _money){
        money -= _money;
    }
    private:
    int money;
};

class Stump{
    public:
    void Render(){
        render::DrawImageFromAtlas("sump", "sump", stump_frame/6, 324, 42);
        for (int i = 0; i < level_count; i++){
            render::DrawImage("level", 462, 122 - 13*i, 11, 11);
        }
        if (water_count == 0 && state == 0) render::DrawImage("19", 440, 40, 57, 30);
        if (stump_frame == 0) stump_frame = 6;
        if (state == 1){
            stump_frame++;
            if (stump_frame > 47) {
                work_count--;
                level_count++;
                stump_frame = 7;
            }
            if (work_count == 0) {
                state = 0;
                stump_frame = 6;
                work_count = 5;
                water_count = 5;
            }
        }
    }
    
    int IsWorking(){
        return state;
    }

    int IsFull(){
        return !!water_count;
    }

    void ChangeState(){
        if (stump_frame == 6) stump_frame = 0;
    }
    void Water(){
        if (water_count == 0) state = 1;
    }

    int GetWaterCount(){
        return water_count;
    }

    void TakeWater(){
        water_count--;
        level_count--;
    }

    private:
    int stump_frame = 6;
    int work_count = 5;
    int state = 0;
    int water_count = 5, level_count = 5;
};

class Store{
    public:
    void Add() {count += 3;}
    void Render(){
        int _count = count;
        int _x = 0, _y = 0;
        while (_count > 0){
            _count--;
            render::DrawImage("_egg", 350 + 12*_x, 540 - 13*_y, 12, 13);
            if (_y >= 4) {
                _y = 0;
                _x++;
            } else _y++;
        }
    }
    int GetCount(){
        return count;
    }
    private:
    int count = 0;
};

class Egg{
    public:
    Egg (float x, float y){
        this->x = x;
        this->y = y;
    }
    void Render(){
        if (time < 450 || time/4 % 2 == 0) render::DrawImageFromAtlas("egg", "egg", state, (int)x, (int)y);
        else  render::DrawImageFromAtlas("egg", "egg", 2, (int)x, (int)y);
        state = 0;
        time++;
    }
    void ChangeState(){
        state = 1;
    }

    void Taken(bool is_taken){
        this->is_taken = is_taken;
    }

    bool IsTaken(){
        return is_taken;
    }

    bool IsTimeOver(){
        return time >= 500;
    }

    float GetX() {return x;}
    float GetY() {return y;}
    private:
    float x, y;
    int state = 0;
    bool is_taken = false;
    int time = 0;
};

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
            mass = 0;
            return 0;
        }
    }

    int GetMass(){
        return mass;
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
    Grass (float x, float y) : Food(6) {
        this->x = x;
        this->y = y;
    }

    void AddGrass(int x, int y, int frame){
        int i = 0;
        while (grass[i] != 0 && grass[i+1] != 0 && i < 30) i += 2;
        grass[i] = x;
        grass[i+1] = y;
    }

    void Less(){
        frame = 12;
    }

    void Render(){
        render::DrawImageFromAtlas("grass", "grass", frame/4, (int)x, (int)y);
        if (frame == 23) return;
        frame++;
    }

    float GetX () const{return x;}
    float GetY () const{return y;}

    private:
    float x, y;
    int frame = 0;
    int grass[30] = {0};
};

class Animal {
    public:
    virtual ~Animal(){};
    virtual void Render() = 0;
    virtual void Moving() = 0;
    virtual Grass* FindFood(const std::vector<std::unique_ptr<Grass>>& food) = 0;
    virtual int GoingToFood() = 0;
    virtual int Eating(Grass* food) = 0;
    virtual void Died() = 0;
    virtual void Update(const std::vector<std::unique_ptr<Grass>>& grass) = 0;

    virtual float GetX() = 0;
    virtual float GetY() = 0;
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
        if (x < 170 || x > 630 || y < 150 || y > 400) {
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
    }
    
    Grass* FindFood(const std::vector<std::unique_ptr<Grass>>& grass){
        float dis = 100000000;

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

        d_x += 5;
        d_y -= 20;
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

        if (abs(d_x) <= cos * 3 || abs(d_y) <= sin * 3) return 0;
        return 1;
    }
    
    int Eating(Grass* food){
        if (!food)
          return 0;
        render::DrawImageFromAtlas("duck_eating", "duck_eating", eating_frame/8, (int)x, (int)y);
        if (eating_frame != 63) eating_frame++;
        else {
            eating_frame = 0;
            return !food->Eat(3);
        }
        return 0;
    }

    float GetX() {return x;}
    float GetY() {return y;}

    void Died(){
        render::DrawImageFromAtlas("duck_die", "duck_die", die_frame/8, (int)x, (int)y);
        if (die_frame != 53) die_frame++;
        else return;
    }

    bool IsEggTime(){
        return egg_time == 500;
    }

    bool IsDied(){
        return t > 1100;
    }

    void Update(const std::vector<std::unique_ptr<Grass>>& grass){
        t ++;
        egg_time++;
        if (egg_time == 501) egg_time = 0;
        
        if (t > 1000) {
            Died();
            return;
        }
        if (t < 500) {  // For example
            s = 1;
            food = nullptr;
            Moving();
            return;
        }
        if (!food || _s) {
            food = FindFood(grass);
            _s = 0;
            s = 1;
        }
        else if (food) {
            if (s == 1) s = GoingToFood();
            else {
                _s = Eating(food);
                _t++;
                if (_t == 200) {
                    t -= 400;
                    _t = 0;
                }
            }
            return;
        }
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
    int t = 0, egg_time = 0;
    Grass* food = nullptr;
    int s = 1, _t = 0, _s = 0;
};
