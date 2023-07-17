#include "consoleview.h"
#include "controller.h"

using namespace s21;
int main() {
  Graph model;
  Controller controller(&model);
  ConsoleView view(&controller);
  view.StartEventLoop();
  return 0;
}