#ifndef NAVIGATOR_CONSOLEVIEW_CONSOLEVIEW_H
#define NAVIGATOR_CONSOLEVIEW_CONSOLEVIEW_H
#include <iostream>
#include <map>

#include "controller.h"

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

 private:
  void BreadthFirstSearch();
  void DepthFirstSearch();
  void DisplayMenu();
  void ExitAction();
  void ExportGraph();
  void LeastSpanningTree();
  void LoadGraph();
  void NoAction();
  int PerformChoice();
  int PerformNumericInput(const std::string &msg);
  void PerformStringInput();
  void ShortestPathBetweenVertices();
  void ShortestPathsBetweenAllVertices();
  void SolveTravellingSalesmanProblem();
  void TSPComare();

  void ErrorMessage(const std::string &);
  void FinalMessage(const std::string &);
  void PrintArray(const GraphAlgorithms::ResultArray &array);
  void PrintMatrix(const Graph::AdjacencyMatrix &matrix);
  void PrintValue(const GraphAlgorithms::Result result,
                  const std::string &msg = "Smallest distance: ");

  Controller *controller_ = nullptr;
  GraphAppData data_{};
  bool event_loop_end_ = false;
  std::map<int, MenuItem> menu_{};
};

}  // namespace s21

#endif  // NAVIGATOR_CONSOLEVIEW_CONSOLEVIEW_H
