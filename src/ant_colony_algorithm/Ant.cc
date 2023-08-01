#include "Ant.h"

#include <map>
#include <random>
#include <set>

#include "../s21_graph.h"

namespace s21 {

void Ant::RunAnt() {
  visited_vertices.insert(starting_vertex_);
  current_vertex_ = starting_vertex_;
  for (int i = 0; i < size_ - 1; ++i) {
    uint new_vertex = ChooseVertex();
    visited_vertices.insert(current_vertex_);
    path_.insert(current_vertex_, new_vertex);
    distance_ += graph_.GetEdge(current_vertex_, new_vertex);
    current_vertex_ = new_vertex;
  }
  path_.insert(current_vertex_, starting_vertex_);
  distance_ += graph_.GetEdge(current_vertex_, starting_vertex_);

  double deposited_pheromone = kPheromoneValue / distance_;
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
  s for (int vertex = 0; vertex < size_;) {
    if (graph_.GetEdge(current_vertex_, vertex) &&
        !visited_vertices_.count(vertex)) {
      possible_moves_.insert(vertex);
    }
  }

  // TODO if no moves?
}

double Ant::CalculateProbabilities() {
  double sum = 0;
  for (const auto& next_vertex : possible_moves_) {
    double probability =
        pow(closeness_.GetEdge(current_vertex_, next_vertex), kBeta) *
        pow(pheromones_.GetEdge(current_vertex_, next_vertex), kAlpha);
    probabilities_.insert(std::pair<uint, double>(next_vertex, probability));
    sum += probability;
  }
  return sum;
}

}  // namespace s21