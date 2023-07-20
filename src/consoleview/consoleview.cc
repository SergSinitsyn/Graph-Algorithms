#include "consoleview.h"

#include <functional>
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
          {5, {"All shoortest paths search", &ConsoleView::NoAction}},
          {6, {"Get least spanning tree", &ConsoleView::NoAction}},
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
  int number;
  size_t number_length = 0;
  std::string input;
  do {
    std::cout << prompt;
    getline(cin, input);
    try {
      number = stoi(input, &number_length);
    } catch (const std::invalid_argument&) {
      std::cout << termcolor::red << "Wrong input!" << termcolor::reset
                << std::endl;
      number_length = 0;
    }
  } while (number_length < 1);

  return number;
}

std::string ConsoleView::PerformStringInput() {
  std::cout << "Input a filename: ";
  getline(cin, data_.filename);
  return data_.filename;
}

void ConsoleView::LoadGraph() {
  data_.filename = PerformStringInput();
  controller_->LoadGraphFromFile(&data_);
  std::cout << termcolor::green << "File " << data_.filename
            << " loaded successfully" << termcolor::reset << std::endl;
};

void ConsoleView::ExportGraph() {
  data_.filename = PerformStringInput();
  controller_->ExportGraphToDot(&data_);
  std::cout << termcolor::green << "Graph successfully uploaded to file "
            << data_.filename
            // << " loaded successfully"
            << termcolor::reset << std::endl;
};

void ConsoleView::BreadthFirstSearch() {
  std::string prompt = "Input a Vertex number to start search (" +
                       std::to_string(GraphAlgorithms::kVertexStartNumber) +
                       "-" + std::to_string(Graph::kMaxSize) + "): ";
  if (controller_->IsModelLoaded()) {
    data_.point_a = PerformNumericInput(prompt);
    controller_->BreadthFirstSearch(&data_);
    // TODO: operator << for GraphAlgorithms::ResultArray
    //  std::cout << "result : " << controller_->GetResult() << std::endl;
    for (auto item : controller_->GetResult()) {
      std::cout << item;
      if (item != controller_->GetResult().back()) std::cout << ", ";
    }
    std::cout << std::endl
              << termcolor::green << "BreadthFirstSearch finished"
              << termcolor::reset << std::endl;
  } else {
    std::cout << termcolor::red << "Model is not loaded" << termcolor::reset
              << std::endl;
  }
};

void ConsoleView::DepthFirstSearch() {
  std::string prompt = "Input a Vertex number to start search (" +
                       std::to_string(GraphAlgorithms::kVertexStartNumber) +
                       "-" + std::to_string(Graph::kMaxSize) + "): ";
  if (controller_->IsModelLoaded()) {
    data_.point_a = PerformNumericInput(prompt);
    controller_->DepthFirstSearch(&data_);
    // TODO: operator << for GraphAlgorithms::ResultArray
    //  std::cout << "result : " << controller_->GetResult() << std::endl;
    for (auto item : controller_->GetResult()) {
      std::cout << item;
      if (item != controller_->GetResult().back()) std::cout << ", ";
    }
    std::cout << std::endl
              << termcolor::green << "DepthFirstSearch finished"
              << termcolor::reset << std::endl;
  } else {
    std::cout << termcolor::red << "Model is not loaded" << termcolor::reset
              << std::endl;
  }
};

void ConsoleView::ShortestPathBetweenVertices() {
  std::string prompt_start =
      "Input a START Vertex number(" +
      std::to_string(GraphAlgorithms::kVertexStartNumber) + "-" +
      std::to_string(Graph::kMaxSize) + "): ";
  std::string prompt_end = "Input a END Vertex number (" +
                           std::to_string(GraphAlgorithms::kVertexStartNumber) +
                           "-" + std::to_string(Graph::kMaxSize) + "): ";
  if (controller_->IsModelLoaded()) {
    data_.point_a = PerformNumericInput(prompt_start);
    data_.point_b = PerformNumericInput(prompt_end);
    controller_->GetShortestPathBetweenVertices(&data_);
    // TODO: operator << for GraphAlgorithms::ResultArray
    //  std::cout << "result : " << controller_->GetResult() << std::endl;
    for (auto item : controller_->GetResult()) {
      std::cout << item;
      if (item != controller_->GetResult().back()) std::cout << ", ";
    }
    std::cout << std::endl
              << termcolor::green << "ShortestPathBetweenVertices finished"
              << termcolor::reset << std::endl;
  } else {
    std::cout << termcolor::red << "Model is not loaded" << termcolor::reset
              << std::endl;
  }
};

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
