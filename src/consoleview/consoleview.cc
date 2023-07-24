#include "consoleview.h"

#include <functional>
#include <iomanip>
#include <string>

#include "termcolor.hpp"

using std::cin;
using std::cout;
using std::endl;
using namespace s21;

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
          {7, {"Traveling Salesman Problem", &ConsoleView::NoAction}},
          {8, {"Export graph to file .dot", &ConsoleView::ExportGraph}},
          {9, {"Exit", &ConsoleView::ExitAction}}} {};

void ConsoleView::DisplayMenu() {
  std::cout << "=========" << std::endl;
  std::cout << " M E N U " << std::endl;
  std::cout << "=========" << std::endl;
  for (const auto& item : menu_) {
    std::cout << item.first << ". " << item.second.name << std::endl;
  }
  std::cout << "=========" << std::endl;
}

int ConsoleView::PerformChoice() {
  int choice = PerformNumericInput("Input a menu item digit: ");
  if (menu_.find(choice) == menu_.end()) {
    std::cout << termcolor::red << "Item out of range!" << termcolor::reset
              << std::endl;
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
      std::cout << termcolor::red << "Wrong input!" << termcolor::reset
                << std::endl;
    }
  }

  return number;
}

void ConsoleView::PerformStringInput() {
  std::cout << "Input a filename: ";
  getline(cin, data_.filename);
}

void ConsoleView::LoadGraph() {
  PerformStringInput();
  controller_->LoadGraphFromFile(&data_);
  std::cout << termcolor::green << "File " << data_.filename
            << " loaded successfully" << termcolor::reset << std::endl;
}

void ConsoleView::ExportGraph() {
  PerformStringInput();
  controller_->ExportGraphToDot(&data_);
  std::cout << termcolor::green << "Graph successfully uploaded to file "
            << data_.filename << termcolor::reset << std::endl;
}
void ConsoleView::LeastSpanningTree() {
  if (!controller_->IsModelLoaded()) {
    std::cout << termcolor::red << "Model is not loaded." << termcolor::reset
              << std::endl;
    return;
  }
  controller_->GetLeastSpanningTree();
  Graph::AdjacencyMatrix result_matrix = controller_->adjacency_matrix_result();
  PrintMatrix(result_matrix);
  std::cout << std::endl
            << termcolor::green << "LeastSpanningTree finished"
            << termcolor::reset << std::endl;
}

void ConsoleView::BreadthFirstSearch() {
  if (!controller_->IsModelLoaded()) {
    std::cout << termcolor::red << "Model is not loaded" << termcolor::reset
              << std::endl;
    return;
  }
  std::string prompt = "Input a Vertex number to start search (" +
                       std::to_string(GraphAlgorithms::kVertexStartNumber) +
                       "-" + std::to_string(Graph::kMaxSize) + "): ";
  data_.point_a = PerformNumericInput(prompt);
  controller_->BreadthFirstSearch(&data_);
  for (auto item : controller_->array_result()) {
    std::cout << item;
    if (item != controller_->array_result().back()) std::cout << ", ";
  }
  std::cout << std::endl
            << termcolor::green << "BreadthFirstSearch finished"
            << termcolor::reset << std::endl;
}

void ConsoleView::DepthFirstSearch() {
  if (!controller_->IsModelLoaded()) {
    std::cout << termcolor::red << "Model is not loaded" << termcolor::reset
              << std::endl;
    return;
  }
  std::string prompt = "Input a Vertex number to start search (" +
                       std::to_string(GraphAlgorithms::kVertexStartNumber) +
                       "-" + std::to_string(Graph::kMaxSize) + "): ";
  data_.point_a = PerformNumericInput(prompt);
  controller_->DepthFirstSearch(&data_);
  for (auto item : controller_->array_result()) {
    std::cout << item;
    if (item != controller_->array_result().back()) std::cout << ", ";
  }
  std::cout << std::endl
            << termcolor::green << "DepthFirstSearch finished"
            << termcolor::reset << std::endl;
}

void ConsoleView::ShortestPathBetweenVertices() {
  if (!controller_->IsModelLoaded()) {
    std::cout << termcolor::red << "Model is not loaded" << termcolor::reset
              << std::endl;
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
  std::cout << controller_->value_result() << std::endl;
  std::cout << std::endl
            << termcolor::green << "ShortestPathBetweenVertices finished"
            << termcolor::reset << std::endl;
}

void ConsoleView::ShortestPathsBetweenAllVertices() {
  if (!controller_->IsModelLoaded()) {
    std::cout << termcolor::red << "Model is not loaded" << termcolor::reset
              << std::endl;
    return;
  }
  controller_->GetShortestPathsBetweenAllVertices();
  Graph::AdjacencyMatrix result_matrix = controller_->adjacency_matrix_result();
  PrintMatrix(result_matrix);
  std::cout << std::endl
            << termcolor::green << "ShortestPathsBetweenAllVertices finished"
            << termcolor::reset << std::endl;
}

void ConsoleView::PrintMatrix(const Graph::AdjacencyMatrix& matrix) {
  for (size_t i = 0; i < matrix.size(); i++) {
    for (size_t j = 0; j < matrix.at(i).size(); j++) {
      std::cout << std::setw(5) << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}
void ConsoleView::NoAction() {
  std::cout << termcolor::red << "Action not implemented" << termcolor::reset
            << std::endl;
}

void ConsoleView::ExitAction() { event_loop_end_ = true; };

void ConsoleView::StartEventLoop() {
  while (!event_loop_end_) {
    DisplayMenu();
    int choice = PerformChoice();
    if (menu_.find(choice) != menu_.end()) {
      try {
        std::invoke(menu_[choice].user_action_method, this);
      } catch (const std::exception& e) {
        std::cerr << termcolor::red << "Error: " << e.what() << termcolor::reset
                  << '\n';
      }
    }
  }
}
