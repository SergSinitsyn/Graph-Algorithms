#include "ant_colony_algorithm.h"

#include <algorithm>
#include <cmath>
#include <execution>
#include <map>
#include <vector>

#include "../s21_graph.h"
#include "ant.h"

using namespace s21;

AntColonyAlgorithm::AntColonyAlgorithm(const Graph& graph)
    : graph_(graph),
      size_(graph.size()),
      ants_count_(graph.size()),
      closeness_(graph.size()),
      pheromones_(graph.size()) {
  if (graph_.GraphOrientationCheck()) {
    undirected_graph_ = true;
  }

  double sum_of_all_distances = 0.0;
  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j < size_; ++j) {
      size_t edge = graph_.GetEdge(i, j);
      if (edge) {
        pheromones_(i, j) = kInitialPheromoneValue;
        closeness_(i, j) = 1.0 / edge;
        sum_of_all_distances += edge;
      }
    }
  }

  average_distance_ = sum_of_all_distances / (size_);
  best_solution_ = {std::numeric_limits<double>::infinity(), {}, {}};
  break_limit_ = size_;

  elite_ants_count_ = size_ / 2;
  rank_ants_count_ = elite_ants_count_ - 1;
  if (rank_ants_count_ == 0) {
    rank_ants_count_++;
    elite_ants_count_++;
  }

  for (size_t i = 0; i < ants_count_; ++i) {
    Ant ant(graph_, closeness_, average_distance_, i);
    ants_.push_back(ant);
  }
}

AntColonyAlgorithm::ResultTSP AntColonyAlgorithm::GetResult() const {
  ResultTSP result =
      std::make_pair(best_solution_.path, best_solution_.distance);
  return result;
}

void AntColonyAlgorithm::RunAlgorithm() {
  while (break_count_ < break_limit_) {
    Iteration();
    ++break_count_;
  }
}

void AntColonyAlgorithm::Iteration() {
  std::multimap<double, Ant::Solution> solutions;

  std::for_each(std::execution::par, ants_.begin(), ants_.end(), [&](Ant& ant) {
    ant.SetPheromones(pheromones_);
    ant.RunAnt();
  });

  double elite_ants_count = static_cast<double>(elite_ants_count_);
  std::for_each(
      std::execution::seq, ants_.begin(), ants_.end(), [&](const Ant& ant) {
        solutions.insert({ant.GetSolution().distance, ant.GetSolution()});
        if (ant.GetSolution().distance < best_solution_.distance) {
          best_solution_ = ant.GetSolution();
          best_solution_.pheromones.MultNumber(elite_ants_count);
          break_count_ = 0;
        }
      });

  pheromones_.MultNumber(kVaporization);
  auto it = solutions.begin();
  for (size_t i = 1; i < rank_ants_count_; ++i) {
    Matrix rank_pheromones = it->second.pheromones;
    ++it;
    double rank = static_cast<double>(elite_ants_count_ - i);
    pheromones_.Add(rank_pheromones * rank);
    if (undirected_graph_) pheromones_.Add(rank_pheromones.Transpose() * rank);
  }

  pheromones_.Add(best_solution_.pheromones);
  if (undirected_graph_) pheromones_.Add(best_solution_.pheromones.Transpose());
}
