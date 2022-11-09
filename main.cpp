#include <stdint.h>
#include "app/baseapp.h"

class Ferma : public app::GameApp {
 public:
  Ferma(int w, int h) : app::GameApp(w, h) {}

 private:
  void Initialize() override {
    render::LoadResource("resources/images/egg.png", "egg"); 
    render::LoadResource("resources/images/backdrop.png", "backdrop");
    render::LoadResource("resources/images/duck.png", "duck");
  }

  void Render() override {
    render::DrawImage("backdrop", 1, 1, 800, 600);

    int image = (left*down) + 2*(left*!up*!down) + 3*(right*down) + 4*(right*!up*!down) + 5*(up*!right*!left) + 6*(up*right) + 7*(up*left); 
    render::DrawImageFromAtlas("duck", x, y, 56, 83, ((frame % 27)/3)*56, image*83, 56, 83);
    
    right = 0;
    left = 0;
    up = 0;
    down = 0;
  }

  void ProcessInput(const Uint8* keyboard, const MouseState& mouse) override {
    // тут анализируем состояние клавиш клавиатуры
    if (keyboard[SDL_SCANCODE_LEFT])
      {--x; left = 1;}
    if (keyboard[SDL_SCANCODE_RIGHT])
      {++x; right = 1;}
    if (keyboard[SDL_SCANCODE_UP])
      {--y; up = 1;}
    if (keyboard[SDL_SCANCODE_DOWN])
      {++y; down = 1;}

    if (left + right + up + down > 0) frame++;    
  }


  // void OnWindowResized(int widht, int height) override  { 
  //   //тут запоминаем размеры окна и используем потом в Render 
  // }

  void Update(Uint32 millis) override {
    // тут обновляем логику которая зависит от времени
    const int kQuant = 30;
    millis_ += millis;
    if (millis_ < kQuant) {
      return;
    }
    millis_ -= kQuant;
    // в параметре millis содержится количество миллисекунд с предыдущего вызова
  }

  int x = 300;
  int y = 300;
  int up = 0, down = 0, right = 0, left = 0;
  int frame = 0;
  Uint32 millis_ = 0;
};

#undef main
int main() {
  Ferma(800, 600).Run(); // 800 x 600 размер окна
  return 0;
}