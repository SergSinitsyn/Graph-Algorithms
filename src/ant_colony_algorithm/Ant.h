#ifndef NAVIGATOR_ANT_H_
#define NAVIGATOR_ANT_H_

#include <map>
#include <random>
#include <set>
#include <vector>

#include "../s21_graph.h"

using namespace s21;

class Ant {
 public:
  using Solution = std::pair<double, std::vector<size_t>>;

  Ant(const Graph &graph, const Matrix &closeness, double pheromone_value);
  void SetStartingVertex(size_t starting_vertex);
  void RunAnt();
  void SetPheromones(const Matrix &pheromones);
  Matrix GetNewPheromones() const { return new_pheromones_; };
  Solution GetSolution() const { return solution_; };

 private:
  size_t ChooseVertex();
  void VisitVertex(size_t vertex);
  double CalculateProbabilities();
  double GetRandom(double value);
  void PlacePheromones(double value);
  void SetDefaultData();

  Graph graph_;
  Matrix closeness_;
  Matrix pheromones_;
  Matrix new_pheromones_;

  static constexpr double kPheromonesImpact = 1;
  static constexpr double KClosenessImpact = 1;

  size_t size_;
  size_t starting_vertex_{0};
  size_t current_vertex_{0};
  double distance_{0.0};
  double pheromone_value_;

  std::set<size_t> unvisited_vertices_;
  std::set<size_t> possible_moves_;
  std::map<size_t, double> probabilities_;
  std::vector<size_t> path_;
  Solution solution_{};

  std::mt19937 random_number_generator_;
  std::uniform_real_distribution<double> random_number_distribution_;
};

#endif  // NAVIGATOR_ANT_H_