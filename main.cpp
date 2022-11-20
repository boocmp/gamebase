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

  }

  void Render() override {
    render::DrawImage("backdrop", 1, 1, 800, 600);

    for (auto& grass: _grass){
      grass->Render();
      grass->Grow();
    }

    for (auto& food: food){
      food->FindFood();
    }

    if (frame < 200) duck.Moving();
    else duck.Eating();
    // duck.Moving();
    // duck.Render();
    frame++;
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
      food.push_back(std::make_unique<Duck> (x, y));
      food.push_back(std::make_unique<Duck> (x+30, y+30));
      food.push_back(std::make_unique<Duck> (x+20, y));
      food.push_back(std::make_unique<Duck> (x-30, y));
      food.push_back(std::make_unique<Duck> (x, y+30));
  
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
  }

  int x = 0, y = 0;
  Uint32 buttons;
  int up = 0, down = 0, right = 0, left = 0;
  int frame = 0;
  Uint32 millis_ = 0;


  Duck duck{300, 300};
  Grass grass{x, y};
  std::vector<std::unique_ptr<Grass>> _grass;
  std::vector<std::unique_ptr<Duck>> food;
};

#undef main
int main() {
  Ferma(800, 600).Run();
  return 0;
}