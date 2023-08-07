#include "ant_colony_algorithm.h"

#include <algorithm>
#include <cmath>
#include <execution>
#include <map>
#include <vector>

#include "../s21_graph.h"
#include "ant.h"

using namespace s21;

AntColonyAlgorithm::AntColonyAlgorithm(const Graph& graph)
    : graph_(graph),
      size_(graph.size()),
      ants_number_(graph.size()),
      closeness_(graph.size()),
      pheromones_(graph.size()),
      probabilities_(graph.size()),
      elite_pheromones_(graph.size()) {
  if (graph_.GraphOrientationCheck()) {
    undirected_graph_ = true;
  }

  InitializeMatrices();
  InitializeAnts();

  best_solution_ = {std::numeric_limits<double>::infinity(), {}};
  break_limit_ = size_;
  break_count_ = 0;
}

void AntColonyAlgorithm::InitializeMatrices() {
  double sum_of_all_distances = 0.0;
  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j < size_; ++j) {
      size_t edge = graph_.GetEdge(i, j);
      if (edge) {
        closeness_(i, j) = powl(1.0 / edge, kClosenessImpact);
        pheromones_(i, j) = kInitialPheromoneValue;
        probabilities_(i, j) =
            powl(pheromones_(i, j), kPheromonesImpact) * closeness_(i, j);
        sum_of_all_distances += edge;
      }
    }
  }
  average_distance_ = sum_of_all_distances / (size_);
}

void AntColonyAlgorithm::InitializeAnts() {
  elite_ants_number_ = (size_ / 2) + 1;
  rank_ants_number_ = elite_ants_number_ - 1;
  if (rank_ants_number_ == 0) {
    rank_ants_number_++;
    elite_ants_number_++;
  }

  for (size_t i = 0; i < ants_number_; ++i) {
    Ant ant(graph_, i);
    ants_.push_back(ant);
  }
}

AntColonyAlgorithm::ResultTSP AntColonyAlgorithm::GetResult() const {
  ResultTSP result =
      std::make_pair(best_solution_.path, best_solution_.distance);
  return result;
}

void AntColonyAlgorithm::RunAlgorithm() {
  while (break_count_ <= break_limit_) {
    solutions_.clear();
    LaunchAnts();
    GetPaths();
    UpdatePheromones();
    UpdateProbabilities();
    ++break_count_;
  }
}

void AntColonyAlgorithm::LaunchAnts() {
  std::for_each(std::execution::par, ants_.begin(), ants_.end(),
                [&](Ant& ant) { ant.RunAnt(probabilities_); });
}

void AntColonyAlgorithm::GetPaths() {
  std::for_each(
      std::execution::seq, ants_.begin(), ants_.end(), [&](const Ant& ant) {
        solutions_.insert({ant.GetSolution().distance, ant.GetSolution()});

        if (ant.GetSolution().distance < best_solution_.distance) {
          best_solution_ = ant.GetSolution();
          elite_pheromones_ = CreatePheromones(
              best_solution_.path,
              ((average_distance_ * static_cast<double>(elite_ants_number_)) /
               best_solution_.distance));
          break_count_ = 0;
        }
      });
}

Matrix AntColonyAlgorithm::CreatePheromones(std::vector<size_t> path,
                                            double value) {
  size_t size = path.size();
  Matrix new_pheromones(size);

  for (size_t i = 0; i < size - 1; ++i) {
    new_pheromones(path.at(i), path.at(i + 1)) = value;
  }
  new_pheromones(path.at(size - 1), path.at(0)) = value;

  if (undirected_graph_) new_pheromones.Add(new_pheromones.Transpose());
  return new_pheromones;
}

void AntColonyAlgorithm::UpdatePheromones() {
  pheromones_.MultNumber(kVaporization);

  auto it = solutions_.begin();
  for (size_t i = 1; i < rank_ants_number_; ++i) {
    double rank = static_cast<double>(elite_ants_number_ - i);
    double value = average_distance_ * rank / it->second.distance;
    Matrix rank_pheromones = CreatePheromones(it->second.path, value);
    pheromones_.Add(rank_pheromones);
    ++it;
  }

  pheromones_.Add(elite_pheromones_);
}

void AntColonyAlgorithm::UpdateProbabilities() {
  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j < size_; ++j) {
      size_t edge = graph_.GetEdge(i, j);
      if (edge) {
        probabilities_(i, j) =
            powl(pheromones_(i, j), kPheromonesImpact) * closeness_(i, j);
      }
    }
  }
}
