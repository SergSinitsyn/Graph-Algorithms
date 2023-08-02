#include "ant.h"

#include <map>
#include <pair>
#include <random>
#include <set>

#include "../s21_graph.h"

namespace s21 {

Ant::Ant(const Graph& graph, const Graph& closeness, const Graph& pheromones)
    : graph_(graph), closeness_(closeness), pheromones_(pheromones) {
  size_ = static_cast<uint>(graph.size());
}

void Ant::SetStartingVertex(uint starting_vertex)
    : starting_vertex_(starting_vertex) {
  if (starting_vertex >= graph_.size()) {
    starting_vertex_ = starting_vertex % graph_.size();
  }
}

void Ant::RunAnt() {
  ClearAllData();

  path_.push(starting_vertex_);
  visited_vertices.insert(starting_vertex_);
  current_vertex_ = starting_vertex_;

  for (int i = 0; i < size_ - 1; ++i) {
    uint new_vertex = ChooseVertex();
    distance_ += graph_.GetEdge(current_vertex_, new_vertex);

    path_.push(new_vertex);
    visited_vertices.insert(new_vertex);
    current_vertex_ = new_vertex;
  }

  path_.push(starting_vertex_);
  distance_ += graph_.GetEdge(current_vertex_, starting_vertex_);

  PlacePheromones(kPheromoneValue / distance_);
  solution_ = std::make_pair{path_, distance_};
}

uint Ant::ChooseVertex() {
  FindPossibleMoves();
  double sum_of_probabilities = CalculateProbabilities();

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> distribution(0.0,
                                                      sum_of_probabilities);
  double random_number = distribution(gen);

  for (const auto& sector : probabilities_) {
    random_number -= sector.second;
    if (random_number <= 0.0) {
      return sector.first;
    }
  }
}

void Ant::FindPossibleMoves() {
  possible_moves_.clear();
  for (int vertex = 0; vertex < size_;) {
    if (graph_.GetEdge(current_vertex_, vertex) &&
        !visited_vertices_.count(vertex)) {
      possible_moves_.insert(vertex);
    }
  }

  // TODO if no moves?
  if (possible_moves_.empty()) {
  }
}

double Ant::CalculateProbabilities() {
  probabilities_.clear();
  double sum = 0;
  for (const auto& next_vertex : possible_moves_) {
    double probability =
        pow(closeness_.GetEdge(current_vertex_, next_vertex), kBeta) *
        pow(pheromones_.GetEdge(current_vertex_, next_vertex), kAlpha);
    probabilities_.insert({next_vertex, probability});
    sum += probability;
  }
  return sum;
}

void Ant::PlacePheromones(double value) {
  // for (int i = 0; i < path_.size() - 1; ++i) {
  //   new_pheromones_.SetEdge(path_.at(i), path_.at(i + 1), value);
  // }

  std::for_each(path_.begin(), path_.end() - 1, [&](const auto& node) {
    new_pheromones_.SetEdge(node, *(std::next(&node)), value);
  });
}

void Ant::ClearData() {
  current_vertex_ = starting_vertex_;
  distance_ = 0;
  visited_vertices_.clear();
  possible_moves_.clear();
  probabilities_.clear();
  path_.clear();
  solution_.clear();
}

}  // namespace s21