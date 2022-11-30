#include <stdint.h>
#include "app/baseapp.h"
#include "ferma/ferma.h"
#include <string>

class Ferma : public app::GameApp {
 public:
  Ferma(int w, int h) : app::GameApp(w, h){}

 private:
  void Initialize() override {
    render::LoadResource("resources/images/_egg.png", "_egg"); 
    render::LoadResource("resources/images/level.png", "level"); 
    render::LoadResource("resources/images/backdrop.png", "backdrop");

    render::LoadResource("resources/images/19.png", "19");
    render::LoadResource("resources/images/shop_duck.png", "shop_duck");

    auto duck_atlas = render::Atlas::Create("resources/images/duck.png", "duck");
    duck_atlas.AddAnimationLine("down").SetFramesCount(9, true).SetFrameHeight(83).SetFrameWidth(56);
    duck_atlas.AddAnimationLine("down_left").SetFramesCount(9, true).SetFrameHeight(83).SetFrameWidth(56);
    duck_atlas.AddAnimationLine("left").SetFramesCount(9, true).SetFrameHeight(83).SetFrameWidth(56);
    duck_atlas.AddAnimationLine("down_right").SetFramesCount(9, true).SetFrameHeight(83).SetFrameWidth(56);
    duck_atlas.AddAnimationLine("right").SetFramesCount(9, true).SetFrameHeight(83).SetFrameWidth(56);
    duck_atlas.AddAnimationLine("up").SetFramesCount(9, true).SetFrameHeight(83).SetFrameWidth(56);
    duck_atlas.AddAnimationLine("up_right").SetFramesCount(9, true).SetFrameHeight(83).SetFrameWidth(56);
    duck_atlas.AddAnimationLine("up_left").SetFramesCount(9, true).SetFrameHeight(83).SetFrameWidth(56);
    render::BakeAtlas(duck_atlas);

    auto grass_atlas = render::Atlas::Create("resources/images/grass.png", "grass");
    grass_atlas.AddAnimationLine("grass").SetFramesCount(7, true).SetFrameHeight(60).SetFrameWidth(55);
    render::BakeAtlas(grass_atlas);

    auto duck_eating_atlas = render::Atlas::Create("resources/images/duck_eating.png", "duck_eating");
    duck_eating_atlas.AddAnimationLine("duck_eating").SetFramesCount(8, true).SetFrameHeight(84).SetFrameWidth(75);
    render::BakeAtlas(duck_eating_atlas);

    auto duck_die_atlas = render::Atlas::Create("resources/images/duck_die.png", "duck_die");
    duck_die_atlas.AddAnimationLine("duck_die").SetFramesCount(8, true).SetFrameHeight(84).SetFrameWidth(75);
    render::BakeAtlas(duck_die_atlas);

    auto time_atlas = render::Atlas::Create("resources/images/time.png", "time");
    time_atlas.AddAnimationLine("time").SetFramesCount(11, true).SetFrameHeight(25).SetFrameWidth(18);
    render::BakeAtlas(time_atlas);

    auto egg_atlas = render::Atlas::Create("resources/images/egg.png", "egg");
    egg_atlas.AddAnimationLine("egg").SetFramesCount(3, true).SetFrameHeight(30).SetFrameWidth(24);
    render::BakeAtlas(egg_atlas);

    auto sump_atlas = render::Atlas::Create("resources/images/sump.png", "sump");
    sump_atlas.AddAnimationLine("sump").SetFramesCount(8, true).SetFrameHeight(120).SetFrameWidth(135);
    render::BakeAtlas(sump_atlas);
    
    auto money_atlas = render::Atlas::Create("resources/images/money.png", "money");
    money_atlas.AddAnimationLine("money").SetFramesCount(10, true).SetFrameHeight(40).SetFrameWidth(22);
    render::BakeAtlas(money_atlas);
  }

  void Render() override {
    render::DrawImage("backdrop", 1, 1, 800, 600);
    
    render::DrawImageFromAtlas("time", "time", 10, 698, 14);
    render::DrawImageFromAtlas("time", "time", 0, 682, 14);
    render::DrawImageFromAtlas("time", "time", min, 692, 14);
    render::DrawImageFromAtlas("time", "time", sec2, 708, 14);
    render::DrawImageFromAtlas("time", "time", sec1, 718, 14);

    // render::DrawImageFromAtlas("money", "money", 0, 635, 520);
    // render::DrawImageFromAtlas("money", "money", 1, 650, 520);

    bank.Render();
    shop.Render();
    stump.Render();


    for (auto& grass: _grass){
      grass->Render();
      if (grass->GetMass() == 3) grass->Less();
    }

    for (auto& egg: eggs){
      egg->Render();
    }
    for (auto& duck: ducks){
      duck->Update(_grass);
    }

    auto ne = std::remove_if(_grass.begin(), _grass.end(),
                               [](auto& g) { return g->IsEaten(); });
    _grass.erase(ne, _grass.end());

    auto ne1 = std::remove_if(eggs.begin(), eggs.end(),
                               [](auto& g) { return g->IsTimeOver(); });
    eggs.erase(ne1, eggs.end());

    store.Render();

  }

  void ProcessInput(const Uint8* keyboard, const MouseState& mouse) override { 
    x = (float)mouse.x;
    y = (float)mouse.y;

    for (auto& egg: eggs){
      float _x = egg->GetX(), _y = egg->GetY();
      if (abs(_x - x) < 20 && abs(_y - y) < 20) egg->ChangeState();
    }

    if (abs(x - 434) < 110 && abs(y - 100) < 40) stump.ChangeState();

    if ((mouse.buttons & SDL_BUTTON_LMASK) != 0) {
      
      if (click > 0) {
        click--;
        return;
      }

      if (abs(x - 28) < 13 && abs(y - 50) < 30 && shop.IsDuck()){
        shop.MinusDuck();
        bank.WasteMoney(100);
        ducks.push_back(std::make_unique<Duck> (300, 350));
        click = 6;
      }


      if (abs(x - 434) < 110 && abs(y - 100) < 40 && bank.GetMoney() >= 19) {
        if (!stump.IsWorking() && !stump.IsFull())bank.WasteMoney(19);
        stump.Water();
      }

      for (auto& egg: eggs){
        float _x = egg->GetX(), _y = egg->GetY();
        if (abs(_x - x) < 20 && abs(_y - y) < 20){
          egg->Taken(true);
          egg_is_taken = 6;
          store.Add();
        }
      }
      auto ne = std::remove_if(eggs.begin(), eggs.end(),
                               [](auto& g) { return g->IsTaken(); });
      eggs.erase(ne, eggs.end());

      if (egg_is_taken > 0) {
        egg_is_taken--;
        return;
      }

      if (stump.GetWaterCount()){
        int flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0;
        int flag = 0;
        for (auto& grass: _grass){
          float _x = grass->GetX(), _y = grass->GetY();
          if (_x == x && _y == y) flag1 = 1;
          if (_x == x+30 && _y == y+30) flag2 = 1;
          if (_x == x+20 && _y == y) flag3 = 1;
          if (_x == x-30 && _y == y) flag4 = 1;
          if (_x == x && _y == y+30) flag5 = 1;
        }
        if (x < 230 || x > 570 || y < 180 || y > 370) flag = 1;
        if (flag!= 1 && flag1!= 1 && flag2!= 1  && flag3!= 1 && flag4!= 1 && flag5!= 1) {
          _grass.push_back(std::make_unique<Grass> (x, y));
          _grass.push_back(std::make_unique<Grass> (x+30, y+30));
          _grass.push_back(std::make_unique<Grass> (x+20, y));
          _grass.push_back(std::make_unique<Grass> (x-30, y));
          _grass.push_back(std::make_unique<Grass> (x, y+30));
          stump.TakeWater();
        }
      }
  
    }

    // if (keyboard[SDL_SCANCODE_LEFT])
    //   {--x; left = 1;}
    // if (keyboard[SDL_SCANCODE_RIGHT])
    //   {++x; right = 1;}
    // if (keyboard[SDL_SCANCODE_UP])
    //   {--y; up = 1;}
    // if (keyboard[SDL_SCANCODE_DOWN])
    //   {++y; down = 1;}

    if (left + right + up + down > 0) frame++;    
  }

  void Update(Uint32 millis) override {
    const int kQuant = 30;
    millis_ += millis;
    if (millis_ < kQuant) {
      return;
    }
    millis_ -= kQuant;

    if (_time % 35 == 0){
      if (sec1 < 9) sec1++;
      else if (sec2 < 5) {
        sec2++;
        sec1 = 0;
      }
      else {
        min++;
        sec2 = 0;
        sec1 = 0;
      }
    }
    _time++;
    for (auto& duck: ducks){
      if (duck->IsEggTime()){
        eggs.push_back(std::make_unique<Egg> (duck->GetX()+15, duck->GetY()+40));
      }
    }
  }

  float x = 0, y = 0;
  Uint32 buttons;
  int up = 0, down = 0, right = 0, left = 0;
  int frame = 0;
  Uint32 millis_ = 0;
  int sec1 = 0, sec2 = 0, min = 0;
  int f = 1;
  int _time = 0;
  int stump_frame = 6;

  int egg_is_taken = 0;
  int click = 0;


  //Duck duck{300, 300};
  Grass grass{x, y};
  Store store;
  Stump stump;
  Bank bank{245};
  Shop shop{245};
  //Time time;
  std::vector<std::unique_ptr<Grass>> _grass;
  std::vector<std::unique_ptr<Egg>> eggs;
  std::vector<std::unique_ptr<Duck>> ducks;
};

#undef main
int main() {
  Ferma(800, 600).Run();
  return 0;
}