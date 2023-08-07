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
  };

  Ant(const Graph &graph, size_t starting_vetrex);
  void RunAnt();
  void SetProbabilities(const Matrix &probabilities);
  Solution GetSolution() const { return solution_; };

 private:
  size_t ChooseVertex();
  void VisitVertex(size_t vertex);
  double CalculateVariants();
  double GetRandom(double value);
  void SetDefaultData();

  Graph graph_;
  Matrix probabilities_;

  size_t size_;
  size_t starting_vertex_;
  size_t current_vertex_{0};

  double distance_{0.0};

  std::set<size_t> unvisited_vertices_;
  std::map<size_t, double> variants_;
  std::vector<size_t> path_;
  Solution solution_{};

  std::mt19937 random_number_generator_;
  std::uniform_real_distribution<double> random_number_distribution_;
};

#endif  // NAVIGATOR_ANT_H_