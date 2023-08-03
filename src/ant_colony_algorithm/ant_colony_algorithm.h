#ifndef NAVIGATOR_ANT_COLONY_ALGORITHM_H_
#define NAVIGATOR_ANT_COLONY_ALGORITHM_H_

#include <map>
#include <set>
#include <vector>

#include "../s21_graph.h"
#include "ant.h"

using namespace s21;

class AntColonyAlgorithm {
 public:
  AntColonyAlgorithm(const Graph &graph, size_t size);
  void RunAlgorithm();
  Ant::Solution GetResult() const;

 private:
  void Itetation();

  Graph graph_;
  size_t size_;
  size_t ants_count_;
  Matrix closeness_;
  Matrix pheromones_;

  static constexpr double kInitialPheromoneValue = 1;
  static constexpr double kMagicLength = 1;
  static constexpr double kVaporization = 0.8;

  static constexpr int kIterations = 1000;

  std::multimap<double, std::vector<size_t>> solutions_;
};

#endif  // NAVIGATOR_ANT_COLONY_ALGORITHM_H_
