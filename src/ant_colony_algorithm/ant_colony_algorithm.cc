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
      ants_count_(graph.size()),
      closeness_(graph.size()),
      pheromones_(graph.size()),
      elite_pheromones_(graph.size()),
{
  if (graph_.GraphOrientationCheck()) {
    undirected_graph_ = true;
  }

  InitializeMatrices();

  best_solution_ = {std::numeric_limits<double>::infinity(), {}, {}};
  break_limit_ = size_;

  elite_ants_count_ = size_ / 2;
  rank_ants_count_ = elite_ants_count_ - 1;
  if (rank_ants_count_ == 0) {
    rank_ants_count_++;
    elite_ants_count_++;
  }

  for (size_t i = 0; i < ants_count_; ++i) {
    Ant ant(graph_, closeness_, average_distance_, i);
    ants_.push_back(ant);
  }
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

void AntColonyAlgorithm::UpdateProbabilitiesMatrix() {
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

AntColonyAlgorithm::ResultTSP AntColonyAlgorithm::GetResult() const {
  ResultTSP result =
      std::make_pair(best_solution_.path, best_solution_.distance);
  return result;
}

void AntColonyAlgorithm::RunAlgorithm() {
  while (break_count_ < break_limit_) {
    Iteration();
    ++break_count_;
  }
}

void AntColonyAlgorithm::Iteration() {
  std::multimap<double, Ant::Solution> solutions;
  // запуск муравьев
  std::for_each(std::execution::par, ants_.begin(), ants_.end(), [&](Ant& ant) {
    ant.SetProbabilities(probabilities_);
    ant.RunAnt();
  });

  // получаем маршруты
  double elite_ants_count = static_cast<double>(elite_ants_count_);
  std::for_each(
      std::execution::seq, ants_.begin(), ants_.end(), [&](const Ant& ant) {
        solutions.insert({ant.GetSolution().distance, ant.GetSolution()});

        if (ant.GetSolution().distance < best_solution_.distance) {
          best_solution_ = ant.GetSolution();
          double value =
              average_distance_ * elite_ants_count / best_solution_.distance;
          elite_pheromones_ = CreatePheromones(best_solution_.path, value);
          break_count_ = 0;
        }
      });

  // испарение старых феромонов
  pheromones_.MultNumber(kVaporization);

  // добавление новых ранговых феромонов
  auto it = solutions.begin();
  for (size_t i = 1; i < rank_ants_count_; ++i) {
    double rank = static_cast<double>(elite_ants_count - i);
    double value = average_distance_ * rank / it->second.distance;
    Matrix rank_pheromones = CreatePheromones(it->second.path, value);
    pheromones_.Add(rank_pheromones);
    ++it;
  }

  // добавление новых элитных феромонов
  pheromones_.Add(elite_pheromones_);
}

Matrix AntColonyAlgorithm::CreatePheromones(std::vector<size_t> path,
                                            double value) {
  size_t size = path_.size();
  Matrix new_pheromones(size_);

  for (size_t i = 0; i < path.size() - 1; ++i) {
    new_pheromones(path[i], path[i + 1]) = value
  }
  new_pheromones(path_[size - 1], path_[0]) = value;

  if (undirected_graph_) new_pheromones.Add(new_pheromones.Transpose());
  return new_pheromones;
}
