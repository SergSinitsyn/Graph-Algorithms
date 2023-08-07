#include "controller.h"

#include <chrono>

namespace s21 {

void Controller::BreadthFirstSearch(const GraphAppData *data) {
  array_result_ = GraphAlgorithms::BreadthFirstSearch(*model_, data->point_a);
}

void Controller::DepthFirstSearch(const GraphAppData *data) {
  array_result_ = GraphAlgorithms::DepthFirstSearch(*model_, data->point_a);
}

void Controller::ExportGraphToDot(const GraphAppData *data) {
  model_->ExportGraphToDot(data->filename);
}

void Controller::GetLeastSpanningTree() {
  adjacency_matrix_result_ = GraphAlgorithms::GetLeastSpanningTree(*model_);
}

void Controller::GetShortestPathBetweenVertices(const GraphAppData *data) {
  value_result_ = GraphAlgorithms::GetShortestPathBetweenVertices(
      *model_, data->point_a, data->point_b);
}

void Controller::GetShortestPathsBetweenAllVertices() {
  adjacency_matrix_result_ =
      GraphAlgorithms::GetShortestPathsBetweenAllVertices(*model_);
}

void Controller::SolveTravellingSalesmanProblem() {
  GraphAlgorithms algorithm;
  GraphAlgorithms::TsmResult result =
      algorithm.SolveTravelingSalesmanProblem(*model_);
  value_result_ = result.distance;
  array_result_ = result.vertices;
}

std::chrono::milliseconds Controller::RunMethodTimed(
    const GraphAppData *data, GraphAlgorithms *algorithm,
    GraphAlgorithms::TsmResult (GraphAlgorithms::*method)(const Graph &graph)) {
  auto begin = std::chrono::steady_clock::now();
  for (int i = 0; i < data->n_cycles; i++) {
    (algorithm->*method)(*model_);
  }
  auto end = std::chrono::steady_clock::now();
  auto elapsed_ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
  return elapsed_ms;
}
void Controller::PerformTSPMethodsCompare(const GraphAppData *data) {
  GraphAlgorithms algorithm;
  time_result_[0] = RunMethodTimed(
      data, &algorithm, &GraphAlgorithms::SolveTravelingSalesmanProblem);
  time_result_[1] = RunMethodTimed(
      data, &algorithm, &GraphAlgorithms::DynamicProgrammingMethod);
  time_result_[2] = RunMethodTimed(
      data, &algorithm, &GraphAlgorithms::MonteCarloMethod);
}

bool Controller::IsModelLoaded() {
  return (model_ != nullptr) && (model_->size() > 0);
}

void Controller::LoadGraphFromFile(const GraphAppData *data) {
  model_->LoadGraphFromFile(data->filename);
}

}  // namespace s21
