#include "controller.h"

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

void Controller::SolveTravellingSalesmanProblem1() {
  GraphAlgorithms algorithm;
  GraphAlgorithms::TsmResult result =
      algorithm.SolveTravelingSalesmanProblem1(*model_);
  value_result_ = result.distance;
  array_result_ = result.vertices;
}

bool Controller::IsModelLoaded() {
  return (model_ != nullptr) && (model_->size() > 0);
}

void Controller::LoadGraphFromFile(const GraphAppData *data) {
  model_->LoadGraphFromFile(data->filename);
}

}  // namespace s21
