#include "ant.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <set>

#include "../s21_graph.h"

using namespace s21;

Ant::Ant(const Graph& graph, const Matrix& closeness, const Matrix& pheromones)
    : graph_(graph), closeness_(closeness), pheromones_(pheromones) {
  size_ = graph.size();
  new_pheromones_.SetSize(size_);
}

void Ant::SetStartingVertex(size_t starting_vertex) {
  starting_vertex_ = starting_vertex;
  if (starting_vertex >= size_) {
    starting_vertex_ = starting_vertex % size_;
  }
}

void Ant::RunAnt() {
  ClearData();

  path_.push_back(starting_vertex_);
  visited_vertices_.insert(starting_vertex_);
  current_vertex_ = starting_vertex_;

  for (size_t i = 0; i < size_ - 1; ++i) {
    size_t new_vertex = ChooseVertex();
    distance_ += graph_.GetEdge(current_vertex_, new_vertex);

    path_.push_back(new_vertex);
    visited_vertices_.insert(new_vertex);
    current_vertex_ = new_vertex;
  }

  path_.push_back(starting_vertex_);
  distance_ += graph_.GetEdge(current_vertex_, starting_vertex_);

  PlacePheromones(kPheromoneValue / distance_);
  solution_ = std::make_pair(distance_, path_);
}

size_t Ant::ChooseVertex() {
  FindPossibleMoves();
  double sum_of_probabilities = CalculateProbabilities();

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> distribution(0.0,
                                                      sum_of_probabilities);
  double random_number = distribution(gen);
  double result = 0;

  for (const auto& sector : probabilities_) {
    random_number -= sector.second;
    if (random_number <= 0.0) {
      result = sector.first;
    }
  }
  return result;
}

void Ant::FindPossibleMoves() {
  possible_moves_.clear();
  for (size_t vertex = 0; vertex < size_; ++vertex) {
    if (graph_.GetEdge(current_vertex_, vertex) &&
        !visited_vertices_.count(vertex)) {
      possible_moves_.insert(vertex);
    }
  }

  // TODO if no moves?
  // if (possible_moves_.empty()) {
  // }
}

double Ant::CalculateProbabilities() {
  probabilities_.clear();
  double sum = 0.0;
  for (const auto& next_vertex : possible_moves_) {
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

void Ant::ClearData() {
  current_vertex_ = starting_vertex_;
  distance_ = 0;
  visited_vertices_.clear();
  possible_moves_.clear();
  probabilities_.clear();
  path_.clear();
  solution_ = {};
}
