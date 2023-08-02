#ifndef NAVIGATOR_ANT_COLONY_ALGORITHM_H_
#define NAVIGATOR_ANT_COLONY_ALGORITHM_H_

#include <map>
#include <set>
#include <vector>

#include "../s21_graph.h"
#include "ant.h"

namespace s21 {

class AntColonyAlgorithm {
 public:
  AntColonyAlgorithm(const Graph &graph);
  void RunAlgorithm();
  Ant::Solution GetResult() const;

 private:
  void Itetation();

  Graph graph_;
  Graph closeness_;
  Graph pheromones_;

  static constexpr double kInitialPheromoneValue = 0.2;
  static constexpr double kMagicLength = 100;
  static constexpr double kVaporization = 0.5;
  static constexpr int kInetations = 10;
  uint ants_count_;
  uint size_;

  std::multimap<double, std::vector<uint>> solutions_;
};

}  // namespace s21

#endif  // NAVIGATOR_ANT_COLONY_ALGORITHM_H_
