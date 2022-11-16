#include <stdint.h>
#include "app/baseapp.h"
#include "ferma/ferma.h"

class Ferma : public app::GameApp {
 public:
  Ferma(int w, int h) : app::GameApp(w, h){}

 private:
  void Initialize() override {
    render::LoadResource("resources/images/egg.png", "egg"); 
    render::LoadResource("resources/images/backdrop.png", "backdrop");
    render::LoadResource("resources/images/grass.png", "grass");

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
    grass_atlas.AddAnimationLine("g_1").SetFramesCount(7, true).SetFrameHeight(150).SetFrameWidth(122);
    grass_atlas.AddAnimationLine("g_2").SetFramesCount(7, true).SetFrameHeight(150).SetFrameWidth(122);
    grass_atlas.AddAnimationLine("g_3").SetFramesCount(7, true).SetFrameHeight(150).SetFrameWidth(122);
    grass_atlas.AddAnimationLine("g_4").SetFramesCount(7, true).SetFrameHeight(150).SetFrameWidth(122);
    grass_atlas.AddAnimationLine("g_5").SetFramesCount(7, true).SetFrameHeight(150).SetFrameWidth(122);
    grass_atlas.AddAnimationLine("g_6").SetFramesCount(7, true).SetFrameHeight(150).SetFrameWidth(122);
    grass_atlas.AddAnimationLine("g_7").SetFramesCount(7, true).SetFrameHeight(150).SetFrameWidth(122);
    render::BakeAtlas(grass_atlas);

  }

  void Render() override {
    render::DrawImage("backdrop", 1, 1, 800, 600);
    //render::DrawImage("grass", 200, 1, 800, 100);

    //duck.Create(x, y);
    duck.Moving();
    duck.Render();

    render::DrawImageFromAtlas("grass", "g_3", frame/4, 300, 300);
    // grass.Render(0, 0);
    // grass.Grow();

  }

  void ProcessInput(const Uint8* keyboard, const MouseState& mouse) override {
    // if (frame == 0){
    //   x = mouse.x;
    //   y = mouse.y;
    // }
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


  // void OnWindowResized(int widht, int height) override  { 
  //   //тут запоминаем размеры окна и используем потом в Render 
  // }

  void Update(Uint32 millis) override {
    const int kQuant = 30;
    millis_ += millis;
    if (millis_ < kQuant) {
      return;
    }
    millis_ -= kQuant;
  }

  //int x = 300;
  //int y = 300;
  int up = 0, down = 0, right = 0, left = 0;
  int frame = 0;
  Uint32 millis_ = 0;

  Duck duck;
  //duck.Create(x, y);
  //Grass grass;
  //std::string animation = "g_1";
};

#undef main
int main() {
  Ferma(800, 600).Run();
  return 0;
}