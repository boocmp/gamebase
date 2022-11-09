#include <stdint.h>
#include "app/baseapp.h"

class Ferma : public app::GameApp {
 public:
  Ferma(int w, int h) : app::GameApp(w, h) {}

 private:
  void Initialize() override {
    // Тут загружаем ресурсы: картинки и прочее
    render::LoadResource("resources/images/egg.png", "egg"); 
    render::LoadResource("resources/images/backdrop.png", "backdrop");
    render::LoadResource("resources/images/d_r1.png", "d_r1"); 
    render::LoadResource("resources/images/d_r2.png", "d_r2"); 
    render::LoadResource("resources/images/d_r3.png", "d_r3"); 
    render::LoadResource("resources/images/d_r4.png", "d_r4"); 
    render::LoadResource("resources/images/d_r5.png", "d_r5"); 
    render::LoadResource("resources/images/d_r6.png", "d_r6"); 
    render::LoadResource("resources/images/d_r7.png", "d_r7"); 
    render::LoadResource("resources/images/d_r8.png", "d_r8"); 
    render::LoadResource("resources/images/d_r9.png", "d_r9");

    render::LoadResource("resources/images/d_l1.png", "d_l1"); 
    render::LoadResource("resources/images/d_l2.png", "d_l2"); 
    render::LoadResource("resources/images/d_l3.png", "d_l3"); 
    render::LoadResource("resources/images/d_l4.png", "d_l4"); 
    render::LoadResource("resources/images/d_l5.png", "d_l5"); 
    render::LoadResource("resources/images/d_l6.png", "d_l6"); 
    render::LoadResource("resources/images/d_l7.png", "d_l7"); 
    render::LoadResource("resources/images/d_l8.png", "d_l8"); 
    render::LoadResource("resources/images/d_l9.png", "d_l9");

    render::LoadResource("resources/images/d_u1.png", "d_u1"); 
    render::LoadResource("resources/images/d_u2.png", "d_u2"); 
    render::LoadResource("resources/images/d_u3.png", "d_u3"); 
    render::LoadResource("resources/images/d_u4.png", "d_u4"); 

    render::LoadResource("resources/images/d_d1.png", "d_d1"); 
    render::LoadResource("resources/images/d_d2.png", "d_d2"); 
    render::LoadResource("resources/images/d_d3.png", "d_d3"); 
    render::LoadResource("resources/images/d_d4.png", "d_d4"); 
    render::LoadResource("resources/images/d_d5.png", "d_d5"); 

    render::LoadResource("resources/images/d_l_d1.png", "d_l_d1"); 
    render::LoadResource("resources/images/d_l_d2.png", "d_l_d2"); 
    render::LoadResource("resources/images/d_l_d3.png", "d_l_d3"); 
    render::LoadResource("resources/images/d_l_d4.png", "d_l_d4"); 
    render::LoadResource("resources/images/d_l_d5.png", "d_l_d5"); 
    render::LoadResource("resources/images/d_l_d5.png", "d_l_d6"); 

    render::LoadResource("resources/images/d_r_d1.png", "d_r_d1"); 
    render::LoadResource("resources/images/d_r_d2.png", "d_r_d2"); 
    render::LoadResource("resources/images/d_r_d3.png", "d_r_d3"); 
    render::LoadResource("resources/images/d_r_d4.png", "d_r_d4"); 
    render::LoadResource("resources/images/d_r_d5.png", "d_r_d5"); 
    render::LoadResource("resources/images/d_r_d5.png", "d_r_d6"); 

  }

  void Render() override {
    // тут всё рисуем
    render::DrawImage("backdrop", 1, 1, 800, 600); // в координатах x, y рисуем ресурс с именем "apple"
    //render::DrawImage("egg", x, y); // в координатах x, y рисуем ресурс с именем "apple"
    if ((x % 20)/2 == 0 && left == 1 && down == 1) render::DrawImage("d_l_d1", x, y);
    else if ((x % 20)/2 == 1 && left == 1 && down == 1) render::DrawImage("d_l_d2", x, y);
    else if ((x % 20)/2 == 2 && left == 1 && down == 1) render::DrawImage("d_l_d3", x, y);
    else if ((x % 20)/2 == 3 && left == 1 && down == 1) render::DrawImage("d_l_d4", x, y);
    else if ((x % 20)/2 == 4 && left == 1 && down == 1) render::DrawImage("d_l_d5", x, y);
    else if ((x % 20)/2 == 5 && left == 1 && down == 1) render::DrawImage("d_l_d6", x, y);
    else if ((x % 20)/2 == 6 && left == 1 && down == 1) render::DrawImage("d_l_d5", x, y);
    else if ((x % 20)/2 == 7 && left == 1 && down == 1) render::DrawImage("d_l_d4", x, y);
    else if ((x % 20)/2 == 8 && left == 1 && down == 1) render::DrawImage("d_l_d3", x, y);
    else if ((x % 20)/2 == 9 && left == 1 && down == 1) render::DrawImage("d_l_d2", x, y);

    else if ((x % 20)/2 == 0 && right == 1 && down == 1) render::DrawImage("d_r_d1", x, y);
    else if ((x % 20)/2 == 1 && right == 1 && down == 1) render::DrawImage("d_r_d2", x, y);
    else if ((x % 20)/2 == 2 && right == 1 && down == 1) render::DrawImage("d_r_d3", x, y);
    else if ((x % 20)/2 == 3 && right == 1 && down == 1) render::DrawImage("d_r_d4", x, y);
    else if ((x % 20)/2 == 4 && right == 1 && down == 1) render::DrawImage("d_r_d5", x, y);
    else if ((x % 20)/2 == 5 && right == 1 && down == 1) render::DrawImage("d_r_d6", x, y);
    else if ((x % 20)/2 == 6 && right == 1 && down == 1) render::DrawImage("d_r_d5", x, y);
    else if ((x % 20)/2 == 7 && right == 1 && down == 1) render::DrawImage("d_r_d4", x, y);
    else if ((x % 20)/2 == 8 && right == 1 && down == 1) render::DrawImage("d_r_d3", x, y);
    else if ((x % 20)/2 == 9 && right == 1 && down == 1) render::DrawImage("d_r_d2", x, y);

    else if ((x % 18)/2 == 0 && right == 1) render::DrawImage("d_r1", x, y);
    else if ((x % 18)/2 == 1 && right == 1) render::DrawImage("d_r2", x, y);
    else if ((x % 18)/2 == 2 && right == 1) render::DrawImage("d_r3", x, y);
    else if ((x % 18)/2 == 3 && right == 1) render::DrawImage("d_r4", x, y);
    else if ((x % 18)/2 == 4 && right == 1) render::DrawImage("d_r5", x, y);
    else if ((x % 18)/2 == 5 && right == 1) render::DrawImage("d_r6", x, y);
    else if ((x % 18)/2 == 6 && right == 1) render::DrawImage("d_r7", x, y);
    else if ((x % 18)/2 == 7 && right == 1) render::DrawImage("d_r8", x, y);
    else if ((x % 18)/2 == 8 && right == 1) render::DrawImage("d_r9", x, y);

    else if ((x % 18)/2 == 0 && left == 1) render::DrawImage("d_l1", x, y);
    else if ((x % 18)/2 == 1 && left == 1) render::DrawImage("d_l2", x, y);
    else if ((x % 18)/2 == 2 && left == 1) render::DrawImage("d_l3", x, y);
    else if ((x % 18)/2 == 3 && left == 1) render::DrawImage("d_l4", x, y);
    else if ((x % 18)/2 == 4 && left == 1) render::DrawImage("d_l5", x, y);
    else if ((x % 18)/2 == 5 && left == 1) render::DrawImage("d_l6", x, y);
    else if ((x % 18)/2 == 6 && left == 1) render::DrawImage("d_l7", x, y);
    else if ((x % 18)/2 == 7 && left == 1) render::DrawImage("d_l8", x, y);
    else if ((x % 18)/2 == 8 && left == 1) render::DrawImage("d_l9", x, y);

    else if ((y % 12)/2 == 0 && up == 1) render::DrawImage("d_u1", x, y);
    else if ((y % 12)/2 == 1 && up == 1) render::DrawImage("d_u2", x, y);
    else if ((y % 12)/2 == 2 && up == 1) render::DrawImage("d_u3", x, y);
    else if ((y % 12)/2 == 3 && up == 1) render::DrawImage("d_u4", x, y);
    else if ((y % 12)/2 == 4 && up == 1) render::DrawImage("d_u3", x, y);
    else if ((y % 12)/2 == 5 && up == 1) render::DrawImage("d_u2", x, y);

    else if ((y % 16)/2 == 0 && down == 1) render::DrawImage("d_d1", x, y);
    else if ((y % 16)/2 == 1 && down == 1) render::DrawImage("d_d2", x, y);
    else if ((y % 16)/2 == 2 && down == 1) render::DrawImage("d_d3", x, y);
    else if ((y % 16)/2 == 3 && down == 1) render::DrawImage("d_d4", x, y);
    else if ((y % 16)/2 == 4 && down == 1) render::DrawImage("d_d5", x, y);
    else if ((y % 16)/2 == 5 && down == 1) render::DrawImage("d_d4", x, y);
    else if ((y % 16)/2 == 6 && down == 1) render::DrawImage("d_d3", x, y);
    else if ((y % 16)/2 == 7 && down == 1) render::DrawImage("d_d2", x, y);

    else render::DrawImage("d_d3", x, y);
    
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
  Uint32 millis_ = 0;
};

#undef main
int main() {
  Ferma(800, 600).Run(); // 800 x 600 размер окна
  return 0;
}