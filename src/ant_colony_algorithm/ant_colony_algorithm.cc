#include "ant_colony_algorithm.h"

#include <algorithm>
#include <cmath>

#include "ant.h"

using namespace s21;

AntColonyAlgorithm::AntColonyAlgorithm(const Graph &graph)
    : graph_(graph),
      size_(graph.size()),
      ants_count_(graph.size()),
      closeness_(graph.size()),
      pheromones_(graph.size()),
      new_pheromones_(graph.size()),
      best_path_(graph.size()) {
  double sum_of_all_distances = 0;
  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j < size_; ++j) {
      size_t edge = graph_.GetEdge(i, j);
      if (edge) {
        sum_of_all_distances += edge;
      }
    }
  }

  average_distance_ = sum_of_all_distances / (size_);

  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j < size_; ++j) {
      size_t edge = graph_.GetEdge(i, j);
      if (edge) {
        pheromones_(i, j) = kInitialPheromoneValue;
        closeness_(i, j) = 1.0 / edge;
      }
    }
  }

  solution_ = {std::numeric_limits<double>::infinity(), {}};
  break_limit_ = size_;
  elite_ants_count_ = sqrt(size_);

  if (graph_.GraphOrientationCheck()) {
    undirected_graph_ = true;
  }

  for (size_t i = 0; i < ants_count_; ++i) {
    Ant ant(graph_, closeness_, average_distance_);
    ants_.push_back(ant);
  }
}

Ant::Solution AntColonyAlgorithm::GetResult() const { return solution_; }

void AntColonyAlgorithm::RunAlgorithm() {
  while (break_count_ < break_limit_) {
    Iteration();

    pheromones_.MultNumber(kVaporization);
    pheromones_.Add(new_pheromones_);
    pheromones_.Add(best_path_ * elite_ants_count_);

    if (undirected_graph_) {
      pheromones_.Add(new_pheromones_.Transpose());
      pheromones_.Add((best_path_ * elite_ants_count_).Transpose());
    }

    new_pheromones_.ZeroOut();
    ++break_count_;
  }
}

void AntColonyAlgorithm::Iteration() {
  for (size_t i = 0; i < ants_count_; ++i) {
    ants_.at(i).SetStartingVertex(i);
    ants_.at(i).SetPheromones(pheromones_);
    ants_.at(i).RunAnt();

    new_pheromones_.Add(ants_.at(i).GetNewPheromones());
    if (undirected_graph_) {
      new_pheromones_.Add(ants_.at(i).GetNewPheromones().Transpose());
    }

    if (ants_.at(i).GetSolution().first < solution_.first) {
      solution_ = ants_.at(i).GetSolution();
      break_count_ = 0;
      best_path_ = ants_.at(i).GetNewPheromones();
    }
  }
}

// void AntColonyAlgorithm::Iteration() {
//   for (size_t i = 0; i < ants_count_; ++i) {
//     Ant ant(graph_, closeness_, pheromones_, average_distance_);
//     ant.SetStartingVertex(i);
//     ant.RunAnt();
//     new_pheromones_.Add(ant.GetNewPheromones());

//     if (undirected_graph_) {
//       new_pheromones_.Add(ant.GetNewPheromones().Transpose());
//     }

//     if (ant.GetSolution().first < solution_.first) {
//       solution_ = ant.GetSolution();
//       break_count_ = 0;
//       best_path_ = ant.GetNewPheromones();
//     }
//   }
// }
