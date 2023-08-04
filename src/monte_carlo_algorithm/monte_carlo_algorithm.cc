#include "monte_carlo_algorithm.h"

#include <algorithm>
#include <random>
#include <vector>

#include "../s21_graph.h"

using namespace s21;

MonteCarloAlgorithm::MonteCarloAlgorithm(const Graph& graph)
    : graph_(graph), size_(graph.size()) {
  for (size_t i = 0; i < size_; ++i) {
    sequence_.push_back(i);
  }
  shuffled_sequence_ = sequence_;
}

void MonteCarloAlgorithm::RunAlgorithm() {
  std::random_device rd;
  std::mt19937 gen(rd());

  for (size_t i = 0; i < break_limit_; ++i) {
    ShuffleSequence(gen);
    size_t value = CalculateValue();
    if (value < best_solution_) {
      best_solution_ = value;
      result_ = {shuffled_sequence_, value};
    }
  }
}

void MonteCarloAlgorithm::ShuffleSequence(std::mt19937& gen) {
  shuffled_sequence_ = sequence_;

  for (size_t i = size_ - 1; i > 0; --i) {
    std::uniform_int_distribution<size_t> dist(0, i);
    size_t j = dist(gen);
    std::swap(shuffled_sequence_[i], shuffled_sequence_[j]);
  }
}

size_t MonteCarloAlgorithm::CalculateValue() {
  size_t value = 0;
  for (size_t i = 0; i < size_; ++i) {
    value += graph_.GetEdge(shuffled_sequence_[i],
                            shuffled_sequence_[(i + 1) % size_]);
  }
  return value;
}

MonteCarloAlgorithm::ResultTSP MonteCarloAlgorithm::GetResult() const {
  return result_;
}