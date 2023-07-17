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
const GraphAlgorithms::ResultArray &Controller::GetResult() { return result_; };
bool Controller::IsModelLoaded() {
  return (model_ != nullptr) && (model_->GetVertexCount() > 0);
};