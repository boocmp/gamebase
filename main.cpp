#include "app/baseapp.h"
#include "snake/snake.h"

#include <iostream>

class GameApp : public app::GameApp {
 public:
  GameApp(int w, int h)
      : app::GameApp(w, h),
        snake({game_field.GetWidth() / 2, game_field.GetHeight() / 2}) {
    // gam
  }

 private:
  void AddApple() {
    int x = rand() % game_field.GetWidth();
    int y = rand() % game_field.GetHeight();
    while (x == snake.GetHead().x && y == snake.GetHead().y) {
      x = rand() % game_field.GetWidth();
      y = rand() % game_field.GetHeight();
    }
    auto* apple = new AppleCell;
    apple->OnVisit([this, x, y]() mutable {
      snake.Grow(1);
      AddApple();
      game_field.SetCell(x, y, new EmptyCell);
    });
    game_field.SetCell(x, y, apple);
  }

  void Initialize() override {
    render::LoadResource("resources/images/apple.png");

    AddApple();
  }

  void ProcessInput(const Uint8* keyboard) override {
    if (keyboard[SDL_SCANCODE_RIGHT]) {
      snake.SetDirection(RIGHT);
    } else if (keyboard[SDL_SCANCODE_LEFT]) {
      snake.SetDirection(LEFT);
    } else if (keyboard[SDL_SCANCODE_UP]) {
      snake.SetDirection(UP);
    } else if (keyboard[SDL_SCANCODE_DOWN]) {
      snake.SetDirection(DOWN);
    }
  }

  void Render() override {
    game_field.Render();
    snake.Render();
  }

  void Update(Uint32 millis) override {
    const int kQuant = 120;
    millis_ += millis;
    if (millis_ < kQuant) {
      return;
    }
    millis_ -= kQuant;

    snake.UpdateState();

    if (Cell* cell = game_field.GetCell(snake.GetHead().x, snake.GetHead().y)) {
      cell->Visit();
    }

    Coords head = snake.GetHead();
    if (head.x < 0)
      head.x = game_field.GetWidth() - 1;
    if (head.x >= game_field.GetWidth())
      head.x = 0;
    if (head.y < 0)
      head.y = game_field.GetHeight() - 1;
    if (head.y >= game_field.GetHeight())
      head.y = 0;
    snake.SetHead(head);

    for (size_t i = 1; i < snake.GetUnits().size(); ++i) {
      if (snake.GetHead() == snake.GetUnits()[i]) {
        GameOver();
        return;
      }
    }
  }

  GameField game_field;
  Snake snake;
  Uint32 millis_ = 0;
};

#undef main
int main() {
  try {
    GameApp(800, 800).Run();
  } catch(std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}