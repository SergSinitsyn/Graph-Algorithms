#include "ant.h"

#include <algorithm>
#include <map>
#include <random>
#include <set>

#include "../s21_graph.h"

using namespace s21;

Ant::Ant(const Graph& graph, const Matrix& closeness, double pheromone_value,
         size_t starting_vetrex)
    : graph_(graph),
      closeness_(closeness),
      pheromones_(graph.size()),
      new_pheromones_(graph.size()),
      size_(graph.size()),
      starting_vertex_(starting_vetrex),
      current_vertex_(0),
      distance_(0.0),
      pheromone_value_(pheromone_value),
      unvisited_vertices_(),
      possible_moves_(),
      probabilities_(),
      path_(),
      solution_(),
      random_number_generator_(std::random_device()()),
      random_number_distribution_(0.0, 1.0) {
  SetDefaultData();
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
  solution_ = {distance_, path_, new_pheromones_};
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
        powl(closeness_(current_vertex_, next_vertex), kClosenessImpact);

    probabilities_.insert({next_vertex, probability});
    sum += probability;
  }
  return sum;
}

void Ant::PlacePheromones(double value) {
  size_t size = path_.size();
  for (size_t i = 0; i < size - 1; ++i) {
    new_pheromones_(path_[i], path_[i + 1]) = value;
  }
  new_pheromones_(path_[size - 1], path_[0]) = value;
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
