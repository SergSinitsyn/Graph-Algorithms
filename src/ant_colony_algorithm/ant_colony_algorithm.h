#ifndef NAVIGATOR_ANT_COLONY_ALGORITHM_ANT_COLONY_ALGORITHM_H_
#define NAVIGATOR_ANT_COLONY_ALGORITHM_ANT_COLONY_ALGORITHM_H_

#include <map>
#include <set>
#include <vector>

#include "../s21_graph.h"
#include "ant.h"

using namespace s21;

class AntColonyAlgorithm {
 public:
  using ResultTSP = std::pair<std::vector<size_t>, double>;

  explicit AntColonyAlgorithm(const Graph &graph);
  void RunAlgorithm();
  ResultTSP GetResult() const;

 private:
  void InitializeMatrices();
  void InitializeAnts();
  void LaunchAnts();
  void GetPaths();
  Matrix CreatePheromones(std::vector<size_t> path, double value);
  void UpdatePheromones();
  void UpdateProbabilities();

  std::vector<Ant> ants_;
  std::multimap<double, Ant::Solution> solutions_;

  Graph graph_;

  double average_distance_;
  size_t size_;
  size_t ants_number_;
  size_t break_count_;
  size_t break_limit_;
  size_t elite_ants_number_;
  size_t rank_ants_number_;
  bool undirected_graph_{false};

  Matrix closeness_;
  Matrix pheromones_;
  Matrix probabilities_;
  Matrix elite_pheromones_;

  static constexpr double kInitialPheromoneValue = 0.5;
  static constexpr double kVaporization = 0.5;
  static constexpr double kPheromonesImpact = 1;
  static constexpr double kClosenessImpact = 5;

  Ant::Solution best_solution_;
};

#endif  // NAVIGATOR_ANT_COLONY_ALGORITHM_ANT_COLONY_ALGORITHM_H_
