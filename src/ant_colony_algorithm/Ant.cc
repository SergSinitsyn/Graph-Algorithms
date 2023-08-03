#include "ant.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <set>

#include "../s21_graph.h"

using namespace s21;

Ant::Ant(const Graph& graph, const Matrix& closeness, const Matrix& pheromones)
    : graph_(graph),
      closeness_(closeness),
      pheromones_(pheromones),
      new_pheromones_(graph.size()) {
  size_ = graph.size();
  new_pheromones_.SetSize(size_);
  kPheromoneValue = static_cast<double>(size_);
  unvisited_vertices_.clear();
  possible_moves_.clear();
  probabilities_.clear();
  path_.clear();
  solution_ = {};

  for (size_t i = 0; i < size_; ++i) {
    unvisited_vertices_.insert(i);
  }
}

void Ant::SetStartingVertex(size_t starting_vertex) {
  starting_vertex_ = starting_vertex;
  if (starting_vertex >= size_) {
    starting_vertex_ = starting_vertex % size_;
  }
  current_vertex_ = starting_vertex_;
}

void Ant::RunAnt() {
  distance_ = 0;
  VisitVertex(starting_vertex_);

  while (!unvisited_vertices_.empty()) {
    size_t new_vertex = ChooseVertex();
    distance_ += graph_.GetEdge(current_vertex_, new_vertex);
    VisitVertex(new_vertex);
  }

  distance_ += graph_.GetEdge(current_vertex_, starting_vertex_);
  // path_.push_back(starting_vertex_);  // нужен ли вывод посдлей точки (нача)

  PlacePheromones(kPheromoneValue / distance_);
  solution_ = std::make_pair(distance_, path_);
}

void Ant::VisitVertex(size_t vertex) {
  path_.push_back(vertex);
  unvisited_vertices_.erase(vertex);
  current_vertex_ = vertex;
}

size_t Ant::ChooseVertex() {
  double random_number = GetRandom(CalculateProbabilities());
  size_t result = 0;

  for (const auto& sector : probabilities_) {
    random_number -= sector.second;
    if (random_number <= 0.0) {
      result = sector.first;
      break;
    }
  }

  return result;
}

double Ant::GetRandom(double value) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> distribution(0.0, value);
  return distribution(gen);
}

double Ant::CalculateProbabilities() {
  probabilities_.clear();
  double sum = 0.0;
  for (const auto& next_vertex : unvisited_vertices_) {
    // double probability =
    //     powl(closeness_.GetEdge(current_vertex_, next_vertex), kBeta) *
    //     powl(pheromones_.GetEdge(current_vertex_, next_vertex), kAlpha);

    double probability = closeness_(current_vertex_, next_vertex) *
                         pheromones_(current_vertex_, next_vertex);

    probabilities_.insert({next_vertex, probability});
    sum += probability;
  }
  return sum;
}

void Ant::PlacePheromones(double value) {
  for (size_t i = 0; i < path_.size() - 1; ++i) {
    new_pheromones_(path_.at(i), path_.at(i + 1)) = value;
  }
}
