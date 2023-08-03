#include "ant_colony_algorithm.h"

#include <cmath>
#include <iostream>

#include "ant.h"

using namespace s21;

AntColonyAlgorithm::AntColonyAlgorithm(const Graph &graph)
    : graph_(graph),
      size_(graph.size()),
      ants_count_(graph.size()),
      closeness_(graph.size()),
      pheromones_(graph.size()) {
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

  const double INF = std::numeric_limits<double>::infinity();
  solution_ = {INF, {}};
}

Ant::Solution AntColonyAlgorithm::GetResult() const { return solution_; }

void AntColonyAlgorithm::RunAlgorithm() {
  for (int i = 0; i < kIterations; ++i) {
    std::cout << "Iteration: " << i << std::endl;
    Iteration();
  }
}

void AntColonyAlgorithm::Iteration() {
  Matrix new_pheromones(size_);

  for (size_t i = 0; i < ants_count_; ++i) {
    Ant ant(graph_, closeness_, pheromones_, average_distance_);
    ant.SetStartingVertex(i);
    ant.RunAnt();
    new_pheromones.Add(ant.GetNewPheromones());

    std::cout << ant.GetSolution().first << std::endl;

    if (ant.GetSolution().first < solution_.first) {
      solution_ = ant.GetSolution();
      std::cout << "find best solution " << solution_.first << std::endl;
    }
  }

  pheromones_.MultNumber(kVaporization);
  pheromones_.Add(new_pheromones);
}
