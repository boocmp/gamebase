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
    render::LoadResource("resources/images/slash.png", "slash");

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
    money_atlas.AddAnimationLine("money").SetFramesCount(10, true).SetFrameHeight(32).SetFrameWidth(18);
    render::BakeAtlas(money_atlas);
  }

  void Render() override {
    render::DrawImage("backdrop", 1, 1, 800, 600);
    
    render::DrawImageFromAtlas("time", "time", 10, 698, 14);
    render::DrawImageFromAtlas("time", "time", 0, 682, 14);
    render::DrawImageFromAtlas("time", "time", min, 692, 14);
    render::DrawImageFromAtlas("time", "time", sec2, 708, 14);
    render::DrawImageFromAtlas("time", "time", sec1, 718, 14);

    bank.Render();
    shop.Render();
    stump.Render();
    goals.Render();


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

    if (click1.Process(mouse)){
      shop.MinusDuck();
      bank.WasteMoney(100);
      ducks.push_back(std::make_unique<Duck> (300, 400));
    }

    if (click2.Process(mouse)){
      if (!stump.IsWorking() && !stump.IsFull() && bank.GetMoney() > 19) {
        bank.WasteMoney(19);
        stump.Water();
      }
    }

    for (auto& egg: eggs){
      float _x = egg->GetX(), _y = egg->GetY();
      click3.ChangeXY((int)_x, (int)_y);
      if (click3.Process(mouse)){
        egg->Taken(true);
        store.Add();
        goals.AchiveGoal();
      }
    }
    auto ne = std::remove_if(eggs.begin(), eggs.end(),
                            [](auto& g) { return g->IsTaken(); });
    eggs.erase(ne, eggs.end());

    if (stump.GetWaterCount()){
      if (click4.Process(mouse)) {
        _grass.push_back(std::make_unique<Grass> (x, y));
        _grass.push_back(std::make_unique<Grass> (x+30, y+30));
        _grass.push_back(std::make_unique<Grass> (x+20, y));
        _grass.push_back(std::make_unique<Grass> (x-30, y));
        _grass.push_back(std::make_unique<Grass> (x, y+30));
        stump.TakeWater();
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
    auto ne = std::remove_if(ducks.begin(), ducks.end(),
                                [](auto& d) { return d->IsDied(); });
    ducks.erase(ne, ducks.end());
  }

  float x = 0, y = 0;
  Uint32 buttons;
  Uint32 millis_ = 0;
  int sec1 = 0, sec2 = 0, min = 0;
  int _time = 0;

  Grass grass{x, y};
  Store store;
  Stump stump;
  Bank bank{245};
  Shop shop{245};
  Goals goals;

  std::vector<std::unique_ptr<Grass>> _grass;
  std::vector<std::unique_ptr<Egg>> eggs;
  std::vector<std::unique_ptr<Duck>> ducks;
  
  ClickArea click1{8, 23, 45, 57};
  ClickArea click2{324, 42, 135, 120};
  ClickArea click3{0, 0, 24, 30};
  ClickArea click4{170, 170, 350, 200};

};

#undef main
int main() {
  Ferma(800, 600).Run();
  return 0;
}