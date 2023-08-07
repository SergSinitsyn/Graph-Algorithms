#ifndef NAVIGATOR_MONTE_CARLO_ALGORITHM_H_
#define NAVIGATOR_MONTE_CARLO_ALGORITHM_H_

#include <random>
#include <vector>

#include "../s21_graph.h"

using namespace s21;

class MonteCarloAlgorithm {
 public:
  using ResultTSP = std::pair<std::vector<size_t>, double>;

  explicit MonteCarloAlgorithm(const Graph& graph);
  void RunAlgorithm();
  ResultTSP GetResult() const;

 private:
  void ShuffleSequence(std::mt19937& gen);
  size_t CalculateValue();

  Graph graph_;
  std::vector<size_t> sequence_;
  std::vector<size_t> shuffled_sequence_;
  size_t size_;

  size_t break_limit_;
  size_t best_solution_{SIZE_MAX};

  ResultTSP result_{};
};

#endif  // NAVIGATOR_MONTE_CARLO_ALGORITHM_H_
