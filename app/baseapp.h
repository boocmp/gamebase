#pragma once

#include "../graphics/graphics.h"

namespace app {

class GameApp : public render::RenderWindow {
 public:
  using render::RenderWindow::RenderWindow;
  ~GameApp() override;

  void Run();
  void GameOver();

 private:
  virtual void Initialize() {}
  virtual void Free() {}
  virtual void Update(Uint32 millis ) {}
  virtual void Render() {}
  virtual void ProcessInput(const Uint8* keyboard) {}

  bool is_over_ = false;
};

}  // namespace app
