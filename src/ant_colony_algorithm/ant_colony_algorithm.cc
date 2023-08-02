#include "ant_colony_algorithm.h"

#include <cmath>

#include "ant.h"

namespace s21 {

AntColonyAlgorithm::AntColonyAlgorithm(const Graph &graph) {
  graph_(graph);
  size_ = graph.size();
  ants_count_ = size_, closeness_(size_);
  pheromones_(size_);
  for (uint i = 0; i < graph_.size(); ++i) {
    for (uint j = 0; j < graph_.size(); ++j) {
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
    Ant::Solution result = (it->second, it->first);
    return result;
    // return std::pair<double, std::vector<unsigned int>>(it->first,
    // it->second);
  } else {
    return {std::vector<uint>(), double};
  }
}

void AntColonyAlgorithm::RunAlgorithm() {
  for (int i = 0; i < kInetations; ++i) {
    Itetation();
  }
}

void AntColonyAlgorithm::Itetation() {
  Graph new_pheromones(size_);
  for (uint i = 0; i < ants_count_; ++i) {
    Ant ant(graph_, closeness_, pheromones_);
    ant.SetStartingVertex(i);
    ant.RunAnt();
    solutions_.insert(ant.GetSolution());
    new_pheromones.AddGraph(ant.GetNewPheromones());
  }
  pheromones_.MultNumber(kVaporization);
  pheromones_.AddGraph(new_pheromones);
}

}  // namespace s21