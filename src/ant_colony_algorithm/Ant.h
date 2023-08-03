#ifndef NAVIGATOR_ANT_H_
#define NAVIGATOR_ANT_H_

#include <map>
#include <set>
#include <vector>

#include "../s21_graph.h"

using namespace s21;

class Ant {
 public:
  using Solution = std::pair<double, std::vector<size_t>>;

  Ant(const Graph &graph, const Matrix &closeness, const Matrix &pheromones);
  void SetStartingVertex(size_t starting_vertex);
  void RunAnt();
  Matrix GetNewPheromones() const { return new_pheromones_; };
  Solution GetSolution() const { return solution_; };

 private:
  size_t ChooseVertex();
  void VisitVertex(size_t vertex);
  double CalculateProbabilities();
  double GetRandom(double value);
  void PlacePheromones(double value);

  Graph graph_;
  Matrix closeness_;
  Matrix pheromones_;
  Matrix new_pheromones_;

  static constexpr double kAlpha = 1;
  static constexpr double kBeta = 1;

  size_t size_;
  size_t starting_vertex_;
  size_t current_vertex_;
  double distance_;
  double kPheromoneValue;

  std::set<size_t> unvisited_vertices_;
  std::set<size_t> possible_moves_;
  std::map<size_t, double> probabilities_;
  std::vector<size_t> path_;
  Solution solution_;
};

#endif  // NAVIGATOR_ANT_H_