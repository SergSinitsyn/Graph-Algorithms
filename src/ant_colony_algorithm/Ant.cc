#include "ant.h"

#include <algorithm>
#include <map>
#include <random>
#include <set>

#include "../s21_graph.h"

using namespace s21;

Ant::Ant(const Graph& graph, const Matrix& closeness, double pheromone_value)
    : graph_(graph),
      closeness_(closeness),
      pheromones_(graph.size()),
      new_pheromones_(graph.size()) {
  size_ = graph.size();
  new_pheromones_.SetSize(size_);
  pheromone_value_ = pheromone_value;

  random_number_generator_.seed(std::random_device()());
  random_number_distribution_ =
      std::uniform_real_distribution<double>(0.0, 1.0);
}

void Ant::SetStartingVertex(size_t starting_vertex) {
  starting_vertex_ = starting_vertex % size_;
  current_vertex_ = starting_vertex_;
}

void Ant::SetPheromones(const Matrix& pheromones) { pheromones_ = pheromones; }

void Ant::RunAnt() {
  SetDefaultData();

  VisitVertex(starting_vertex_);

  while (!unvisited_vertices_.empty()) {
    size_t new_vertex = ChooseVertex();
    distance_ += graph_.GetEdge(current_vertex_, new_vertex);
    VisitVertex(new_vertex);
  }

  distance_ += graph_.GetEdge(current_vertex_, starting_vertex_);

  PlacePheromones(pheromone_value_ / distance_);
  solution_ = std::make_pair(distance_, path_);
}

void Ant::VisitVertex(size_t vertex) {
  path_.push_back(vertex);
  unvisited_vertices_.erase(vertex);
  current_vertex_ = vertex;
}

size_t Ant::ChooseVertex() {
  double random_number = GetRandom(CalculateProbabilities());

  for (const auto& sector : probabilities_) {
    random_number -= sector.second;
    if (random_number <= 0.0) {
      return sector.first;
    }
  }

  return probabilities_.begin()->first;
}

double Ant::GetRandom(double value) {
  return random_number_distribution_(random_number_generator_) * value;
}

double Ant::CalculateProbabilities() {
  probabilities_.clear();
  double sum = 0.0;
  for (const auto& next_vertex : unvisited_vertices_) {
    double probability =
        powl(pheromones_(current_vertex_, next_vertex), kPheromonesImpact) *
        powl(closeness_(current_vertex_, next_vertex), KClosenessImpact);

    probabilities_.insert({next_vertex, probability});
    sum += probability;
  }
  return sum;
}

void Ant::PlacePheromones(double value) {
  for (size_t i = 0; i < path_.size() - 1; ++i) {
    new_pheromones_(path_.at(i), path_.at(i + 1)) = value;
  }
  new_pheromones_(path_.back(), path_.front()) = value;
}

void Ant::SetDefaultData() {
  unvisited_vertices_.clear();
  for (size_t i = 0; i < size_; ++i) {
    unvisited_vertices_.insert(i);
  }

  distance_ = 0.0;
  possible_moves_.clear();
  probabilities_.clear();
  path_.clear();
  solution_ = {};
}
