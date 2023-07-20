#ifndef NAVIGATOR_CONSOLEVIEW_CONSOLEVIEW_H
#define NAVIGATOR_CONSOLEVIEW_CONSOLEVIEW_H
#include <iostream>
#include <map>

#include "../controller/controller.h"
namespace s21 {

class ConsoleView {
 public:
  using ConsoleViewFnPtr = void (ConsoleView::*)();
  struct MenuItem {
    std::string name;
    ConsoleViewFnPtr user_action_method;
  };

  explicit ConsoleView(Controller *c);
  void StartEventLoop();

 protected:
  void LoadGraph();
  void BreadthFirstSearch();
  void DepthFirstSearch();
  void DisplayMenu();
  void ExitAction();
  void ExportGraph();
  void NoAction();
  int PerformChoice();
  int PerformNumericInput(const std::string &msg);
  std::string PerformStringInput();
  void ShortestPathBetweenVertices();

  bool event_loop_end_ = false;
  Controller *controller_ = nullptr;
  std::map<int, MenuItem> menu_{};
  GraphAppData data_{};
};
}  // namespace s21
#endif  // NAVIGATOR_CONSOLEVIEW_CONSOLEVIEW_H
