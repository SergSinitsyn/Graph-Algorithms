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
  AntColonyAlgorithm(const Graph &graph);
  void RunAlgorithm();
  Ant::Solution GetResult() const;

 private:
  void Iteration();

  std::vector<Ant> ants_;

  Graph graph_;
  size_t size_;
  size_t ants_count_;
  Matrix closeness_;
  Matrix pheromones_;

  Matrix new_pheromones_;
  Matrix best_path_;

  static constexpr double kInitialPheromoneValue = 1;
  static constexpr double kVaporization = 0.5;

  double average_distance_;
  size_t break_count_{0};
  size_t break_limit_;
  size_t elite_ants_count_;
  bool undirected_graph_{false};

  Ant::Solution solution_;
};

#endif  // NAVIGATOR_ANT_COLONY_ALGORITHM_H_
