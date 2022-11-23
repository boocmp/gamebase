#include <stdint.h>
#include "app/baseapp.h"
#include "ferma/ferma.h"
#include <string>

class Ferma : public app::GameApp {
 public:
  Ferma(int w, int h) : app::GameApp(w, h){}

 private:
  void Initialize() override {
    render::LoadResource("resources/images/egg.png", "egg"); 
    render::LoadResource("resources/images/backdrop.png", "backdrop");
    //render::LoadResource("resources/images/grass.png", "grass");

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

  }

  void Render() override {
    render::DrawImage("backdrop", 1, 1, 800, 600);
    render::DrawImageFromAtlas("time", "time", 10, 698, 14);
    render::DrawImageFromAtlas("time", "time", 0, 682, 14);
    render::DrawImageFromAtlas("time", "time", min, 692, 14);
    render::DrawImageFromAtlas("time", "time", sec2, 708, 14);
    render::DrawImageFromAtlas("time", "time", sec1, 718, 14);

    for (auto& grass: _grass){
      grass->Render();
      grass->Grow();
    }

    duck.Update(millis_, _grass);
    // grass.Render();
    // grass.Grow();
    // Grass* food = nullptr;
    // if (frame < 200) duck.Moving();
    // else if (frame == 200) food = duck.FindFood(_grass);
    // else if (f == 1) f = duck.GoingToFood();
    // else if (duck.Eating(food)) {
    //   auto ne = std::remove_if(_grass.begin(), _grass.end(),
    //                            [](auto& g) { return g->IsEaten(); });
    //   _grass.erase(ne, _grass.end());
    //   //_grass.erase(find(_grass.begin(),_grass.end(), std::make_unique<Grass> (x, y)));
    //   //_grass.pop_back();
    //   //_grass.erase(std::remove_if(_grass.begin(), _grass.end(), [](std::make_unique<Grass>&g)){return x == duck.GetS() && y == duck.GetY();}),_grass.end());
    //   frame = 150;
    //   f = 1;
    // }
    // frame++;

    //duck.Render();
  }

  void ProcessInput(const Uint8* keyboard, const MouseState& mouse) override { 
    if ((mouse.buttons & SDL_BUTTON_LMASK) != 0) {
      x = mouse.x;
      y = mouse.y;
      _grass.push_back(std::make_unique<Grass> (x, y));
      _grass.push_back(std::make_unique<Grass> (x+30, y+30));
      _grass.push_back(std::make_unique<Grass> (x+20, y));
      _grass.push_back(std::make_unique<Grass> (x-30, y));
      _grass.push_back(std::make_unique<Grass> (x, y+30));

      // grass.AddGrass(x, y, 0);
      // grass.AddGrass(x+30, y+30, 0);
      // grass.AddGrass(x+20, y, 0);
      // grass.AddGrass(x-30, y, 0);
      // grass.AddGrass(x, y+30, 0);
  
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

  }

  int x = 0, y = 0;
  Uint32 buttons;
  int up = 0, down = 0, right = 0, left = 0;
  int frame = 0;
  Uint32 millis_ = 0;
  int sec1 = 0, sec2 = 0, min = 0;
  int f = 1;
  int _time = 0;


  Duck duck{300, 300};
  Grass grass{x, y};
  //Time time;
  std::vector<std::unique_ptr<Grass>> _grass;
};

#undef main
int main() {
  Ferma(800, 600).Run();
  return 0;
}