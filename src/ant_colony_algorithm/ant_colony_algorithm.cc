#include "ant_colony_algorithm.h"

#include <cmath>

#include "ant.h"

using namespace s21;

AntColonyAlgorithm::AntColonyAlgorithm(const Graph &graph, size_t size)
    : graph_(graph),
      size_(size),
      ants_count_(size_),
      closeness_(size_),
      pheromones_(size_) {
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      if (graph_.GetEdge(i, j)) {
        closeness_.SetEdge(i, j, kMagicLength / graph_.GetEdge(i, j));
        pheromones_.SetEdge(i, j, kInitialPheromoneValue);
      }
    }
  }
}

Ant::Solution AntColonyAlgorithm::GetResult() const {
  auto it = solutions_.begin();
  if (it != solutions_.end()) {
    Ant::Solution result = std::make_pair(it->first, it->second);
    return result;
  } else {
    return Ant::Solution();
  }
}

void AntColonyAlgorithm::RunAlgorithm() {
  for (int i = 0; i < kInetations; ++i) {
    Itetation();
  }
}

void AntColonyAlgorithm::Itetation() {
  Graph new_pheromones(size_);
  for (size_t i = 0; i < ants_count_; ++i) {
    Ant ant(graph_, closeness_, pheromones_);
    ant.SetStartingVertex(i);
    ant.RunAnt();
    solutions_.insert(
        std::make_pair(ant.GetSolution().first, ant.GetSolution().second));
    new_pheromones.AddGraph(ant.GetNewPheromones());
  }
  pheromones_.MultNumber(kVaporization);
  pheromones_.AddGraph(new_pheromones);
}
