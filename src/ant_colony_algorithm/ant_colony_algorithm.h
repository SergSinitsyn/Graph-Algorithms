#ifndef NAVIGATOR_ANT_COLONY_ALGORITHM_H_
#define NAVIGATOR_ANT_COLONY_ALGORITHM_H_

#include <map>
#include <set>
#include <vector>

#include "../s21_graph.h"
#include "Ant.h"

using namespace s21;

class AntColonyAlgorithm {
 public:
  using ResultTSP = std::pair<std::vector<size_t>, double>;

  explicit AntColonyAlgorithm(const Graph &graph);
  void RunAlgorithm();
  ResultTSP GetResult() const;

 private:
  void Iteration();

  std::vector<Ant> ants_;

  Graph graph_;
  size_t size_;
  size_t ants_count_;
  Matrix closeness_;
  Matrix pheromones_;

  static constexpr double kInitialPheromoneValue = 0.5;
  static constexpr double kVaporization = 0.5;

  double average_distance_;
  size_t break_count_{0};
  size_t break_limit_;
  size_t elite_ants_count_;
  size_t rank_ants_count_;

  bool undirected_graph_{false};

  Ant::Solution best_solution_;
};

#endif  // NAVIGATOR_ANT_COLONY_ALGORITHM_H_
