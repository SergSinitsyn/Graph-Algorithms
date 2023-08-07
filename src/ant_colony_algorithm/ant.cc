#include "ant.h"

#include <algorithm>
#include <map>
#include <random>
#include <set>

#include "../s21_graph.h"

using namespace s21;

Ant::Ant(const Graph& graph, size_t starting_vetrex)
    : graph_(graph),
      size_(graph.size()),
      starting_vertex_(starting_vetrex),
      current_vertex_(0),
      distance_(0.0),
      unvisited_vertices_(),
      variants_(),
      path_(),
      solution_(),
      random_number_generator_(std::random_device()()),
      random_number_distribution_(0.0, 1.0) {
  SetDefaultData();
}

void Ant::SetProbabilities(const Matrix& probabilities) {
  probabilities_ = probabilities;
}

void Ant::RunAnt() {
  SetDefaultData();

  VisitVertex(starting_vertex_);

  while (!unvisited_vertices_.empty()) {
    size_t new_vertex = ChooseVertex();
    distance_ += graph_.GetEdge(current_vertex_, new_vertex);
    VisitVertex(new_vertex);
  }

  distance_ += graph_.GetEdge(current_vertex_, starting_vertex_);
  solution_ = {distance_, path_, new_pheromones_};
}

void Ant::VisitVertex(size_t vertex) {
  path_.push_back(vertex);
  unvisited_vertices_.erase(vertex);
  current_vertex_ = vertex;
}

size_t Ant::ChooseVertex() {
  double random_number = GetRandom(CalculateVariants());

  for (const auto& variant : variants_) {
    random_number -= variant.second;
    if (random_number <= 0.0) {
      return variant.first;
    }
  }

  return variants_.begin()->first;
}

double Ant::CalculateVariants() {
  variants_.clear();
  double sum = 0.0;
  for (const auto& next_vertex : unvisited_vertices_) {
    double value = probabilities_(current_vertex_, next_vertex);
    variants_.insert({next_vertex, value});
    sum += value;
  }
  return sum;
}

double Ant::GetRandom(double value) {
  return random_number_distribution_(random_number_generator_) * value;
}

void Ant::SetDefaultData() {
  unvisited_vertices_.clear();
  for (size_t i = 0; i < size_; ++i) {
    unvisited_vertices_.insert(i);
  }
  variants_.clear();
  distance_ = 0.0;
  path_.clear();
  solution_ = {};
}
