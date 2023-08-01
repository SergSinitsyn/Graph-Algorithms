#include "AntColonyAlgorithm.h"

#include <cmath>

#include "Ant.h"

namespace s21 {

AntColonyAlgorithm::AntColonyAlgorithm(const Graph &graph)
    : graph_(graph), size_(graph.size()), ants_count_(graph_.size()) {
  for (uint i = 0; i < graph_.size(); ++i) {
    for (uint j = 0; j < graph_.size(); ++j) {
      if (graph_.GetEdge(i, j)) {
        closeness.SetEdge(i, j, kMagicLength / graph_.GetEdge(i, j));
        pheromones.SetEdge(i, j, kInitialPheromoneValue);
      }
    }
  }
}

void AntColonyAlgorithm::RunAlgorithm() {
  for (int i = 0; i < kInetations; ++i) {
    Itetation();
  }
}

void AntColonyAlgorithm::Itetation() {
  Ant ant(graph_, closeness_, pheromones_);

  for (uint i = 0; i < ants_count_; ++i) {
    ant.SetStartingVertex(i);
    ant.Run();
    solutions.insert(ant.GetSolution());
  }

  pheromones_.MultNumber(kVaporization);
  pheromones_.AddGraph(ant.GetNewPheromones());
}

};  // namespace s21