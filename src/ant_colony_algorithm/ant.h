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
  struct Solution {
    double distance;
    std::vector<size_t> path;
    Matrix pheromones;
  };

  Ant(const Graph &graph, const Matrix &closeness, double pheromone_value,
      size_t starting_vetrex);
  void RunAnt();
  void SetPheromones(const Matrix &pheromones);
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
  static constexpr double kClosenessImpact = 5;

  size_t size_;
  size_t starting_vertex_;
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