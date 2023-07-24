#include "controller.h"
using namespace s21;
void Controller::LoadGraphFromFile(const GraphAppData *data) {
  model_->LoadGraphFromFile(data->filename);
};

void Controller::ExportGraphToDot(const GraphAppData *data) {
  model_->ExportGraphToDot(data->filename);
};
void Controller::BreadthFirstSearch(const GraphAppData *data) {
  result_ = GraphAlgorithms::BreadthFirstSearch(*model_, data->point_a);
};
void Controller::DepthFirstSearch(const GraphAppData *data) {
  result_ = GraphAlgorithms::DepthFirstSearch(*model_, data->point_a);
}
void Controller::GetShortestPathBetweenVertices(const GraphAppData *data) {
  value_result_ = GraphAlgorithms::GetShortestPathBetweenVertices(
      *model_, data->point_a, data->point_b);
}

void s21::Controller::GetShortestPathsBetweenAllVertices() {
  result_adjacency_matrix_ =
      GraphAlgorithms::GetShortestPathsBetweenAllVertices(*model_);
}

bool Controller::IsModelLoaded() {
  return (model_ != nullptr) && (model_->GetVertexCount() > 0);
};