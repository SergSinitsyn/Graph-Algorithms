#ifndef NAVIGATOR_ANT_H_
#define NAVIGATOR_ANT_H_

#include <map>
#include <set>
#include <vector>

#include "../s21_graph.h"

namespace s21 {

class Ant {
 public:
  using Solution = std::pair<std::vector<uint>, double>;

  Ant(const Graph &graph, const Graph &closeness, const Graph &pheromones);
  void SetStartingVertex(uint starting_vertex);
  void RunAnt();
  Graph GetNewPheromones() const { return new_pheromones_; };
  Solution GetSolution() const { return solution_; };

 private:
  uint ChooseVertex();
  void FindPossibleMoves();
  double CalculateProbabilities();
  void PlacePheromones(double value);
  void ClearData();

  Graph graph_;
  Graph closeness_;
  Graph pheromones_;
  Graph new_pheromones_;

  static constexpr double kAlpha = 1;
  static constexpr double kBeta = 1;
  static constexpr double kPheromoneValue = 100;

  uint size_;
  uint starting_vertex_;
  uint current_vertex_;
  double distance_;

  std::set<uint> visited_vertices_;
  std::set<uint> possible_moves_;
  std::map<uint, double> probabilities_;
  std::vector<uint> path_;
  Solution solution_;
};

}  // namespace s21

#endif  // NAVIGATOR_ANT_H_