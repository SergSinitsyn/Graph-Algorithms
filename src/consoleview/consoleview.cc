#include "consoleview.h"

#include <functional>
#include <iomanip>
#include <string>

#include "termcolor.hpp"

namespace s21 {

ConsoleView::ConsoleView(Controller* c)
    : controller_(c),
      menu_{
          {1, {"Load graph file", &ConsoleView::LoadGraph}},
          {2, {"BreadthFirstSearch", &ConsoleView::BreadthFirstSearch}},
          {3, {"DepthFirstSearch", &ConsoleView::DepthFirstSearch}},
          {4,
           {"Shortest path search", &ConsoleView::ShortestPathBetweenVertices}},
          {5,
           {"All shoortest paths search",
            &ConsoleView::ShortestPathsBetweenAllVertices}},
          {6, {"Get least spanning tree", &ConsoleView::LeastSpanningTree}},
          {7,
           {"Travelling Salesman Problem",
            &ConsoleView::SolveTravellingSalesmanProblem}},
          {8, {"Export graph to file .dot", &ConsoleView::ExportGraph}},
          {9,
           {"Compare Travelling Salesman Problem solving methods",
            &ConsoleView::TSPComare}},
          {10, {"Exit", &ConsoleView::ExitAction}}} {};

void ConsoleView::StartEventLoop() {
  while (!event_loop_end_) {
    DisplayMenu();
    int choice = PerformChoice();
    auto it = menu_.find(choice);
    if (it != menu_.end()) {
      try {
        auto& user_action_method = it->second.user_action_method;
        (this->*user_action_method)();
      } catch (const std::exception& e) {
        ErrorMessage(e.what());
      }
    }
  }
}

void ConsoleView::BreadthFirstSearch() {
  if (!controller_->IsModelLoaded()) {
    ErrorMessage("Model is not loaded");
    return;
  }
  std::string prompt = "Input a Vertex number to start search (" +
                       std::to_string(GraphAlgorithms::kVertexStartNumber) +
                       "-" + std::to_string(Graph::kMaxSize) + "): ";
  data_.point_a = PerformNumericInput(prompt);
  controller_->BreadthFirstSearch(&data_);
  PrintArray(controller_->array_result());
  FinalMessage("BreadthFirstSearch finished");
}

void ConsoleView::DepthFirstSearch() {
  if (!controller_->IsModelLoaded()) {
    ErrorMessage("Model is not loaded");
    return;
  }
  std::string prompt = "Input a Vertex number to start search (" +
                       std::to_string(GraphAlgorithms::kVertexStartNumber) +
                       "-" + std::to_string(Graph::kMaxSize) + "): ";
  data_.point_a = PerformNumericInput(prompt);
  controller_->DepthFirstSearch(&data_);
  PrintArray(controller_->array_result());
  FinalMessage("DepthFirstSearch finished");
}

void ConsoleView::DisplayMenu() {
  std::cout << "=========" << std::endl;
  std::cout << " M E N U " << std::endl;
  std::cout << "=========" << std::endl;
  for (const auto& item : menu_) {
    std::cout << item.first << ". " << item.second.name << std::endl;
  }
  std::cout << "=========" << std::endl;
}

void ConsoleView::ExitAction() { event_loop_end_ = true; };

void ConsoleView::ExportGraph() {
  PerformStringInput();
  controller_->ExportGraphToDot(&data_);
  std::string message = "Graph successfully exported to file " + data_.filename;
  FinalMessage(message);
}

void ConsoleView::LeastSpanningTree() {
  if (!controller_->IsModelLoaded()) {
    ErrorMessage("Model is not loaded");
    return;
  }
  controller_->GetLeastSpanningTree();
  Graph::AdjacencyMatrix result_matrix = controller_->adjacency_matrix_result();
  PrintMatrix(result_matrix);
  FinalMessage("LeastSpanningTree finished");
}

void ConsoleView::LoadGraph() {
  PerformStringInput();
  controller_->LoadGraphFromFile(&data_);
  std::string message = "File " + data_.filename + " loaded successfully";
  FinalMessage(message);
}

int ConsoleView::PerformChoice() {
  int choice = PerformNumericInput("Input a menu item digit: ");
  if (menu_.find(choice) == menu_.end()) {
    ErrorMessage("Item out of range!");
  }
  return choice;
}

int ConsoleView::PerformNumericInput(const std::string& prompt) {
  int number = 0;
  std::string input;
  while (number == 0) {
    std::cout << prompt;
    getline(std::cin, input);
    try {
      number = std::stoi(input);
    } catch (const std::invalid_argument&) {
      ErrorMessage("Wrong input!");
    }
  }

  return number;
}

void ConsoleView::PerformStringInput() {
  std::cout << "Input a filename: ";
  getline(std::cin, data_.filename);
}

void ConsoleView::ShortestPathBetweenVertices() {
  if (!controller_->IsModelLoaded()) {
    ErrorMessage("Model is not loaded");
    return;
  }
  std::string prompt_start =
      "Input a START Vertex number(" +
      std::to_string(GraphAlgorithms::kVertexStartNumber) + "-" +
      std::to_string(Graph::kMaxSize) + "): ";
  std::string prompt_end = "Input a END Vertex number (" +
                           std::to_string(GraphAlgorithms::kVertexStartNumber) +
                           "-" + std::to_string(Graph::kMaxSize) + "): ";
  data_.point_a = PerformNumericInput(prompt_start);
  data_.point_b = PerformNumericInput(prompt_end);

  controller_->GetShortestPathBetweenVertices(&data_);
  PrintValue(controller_->value_result());
  FinalMessage("ShortestPathBetweenVertices finished");
}

void ConsoleView::ShortestPathsBetweenAllVertices() {
  if (!controller_->IsModelLoaded()) {
    ErrorMessage("Model is not loaded");
    return;
  }
  controller_->GetShortestPathsBetweenAllVertices();
  Graph::AdjacencyMatrix result_matrix = controller_->adjacency_matrix_result();
  PrintMatrix(result_matrix);
  FinalMessage("ShortestPathsBetweenAllVertices finished");
}

void ConsoleView::SolveTravellingSalesmanProblem() {
  if (!controller_->IsModelLoaded()) {
    ErrorMessage("Model is not loaded");
    return;
  }
  controller_->SolveTravellingSalesmanProblem();
  PrintArray(controller_->array_result());
  PrintValue(controller_->value_result());
  FinalMessage("Travelling Salesman Problem is resolved");
}

void ConsoleView::TSPComare() {
  if (!controller_->IsModelLoaded()) {
    ErrorMessage("Model is not loaded");
    return;
  }
  data_.n_cycles = PerformNumericInput("Input number of test cycles:");

  controller_->PerformTSPMethodsCompare(&data_);
  for (auto i = 0; i < 3; ++i)
    PrintValue(controller_->time_result(i).count(),
               "Time " + std::to_string(i + 1) + ": ");
  FinalMessage("Comparison finished");
}

void ConsoleView::ErrorMessage(const std::string& message) {
  std::cout << termcolor::red << message << termcolor::reset << std::endl;
}

void ConsoleView::FinalMessage(const std::string& message) {
  std::cout << termcolor::green << message << termcolor::reset << std::endl;
}

void ConsoleView::PrintArray(const GraphAlgorithms::ResultArray& array) {
  std::cout << "Array traversed vertices: ";
  for (auto it = array.begin(); it != array.end(); ++it) {
    std::cout << *it;
    if (it != array.end() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << std::endl;
}

void ConsoleView::PrintMatrix(const Graph::AdjacencyMatrix& matrix) {
  std::cout << "Result matrix : " << std::endl;
  for (size_t i = 0; i < matrix.size(); i++) {
    for (size_t j = 0; j < matrix.at(i).size(); j++) {
      std::cout << std::setw(5) << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void ConsoleView::PrintValue(const GraphAlgorithms::Result result,
                             const std::string& msg) {
  std::cout << msg << result;
  std::cout << std::endl;
}

}  // namespace s21
