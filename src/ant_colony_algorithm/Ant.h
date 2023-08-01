#ifndef NAVIGATOR_ANT_H_
#define NAVIGATOR_ANT_H_

#include <map>
#include <set>
#include <vector>

#include "../s21_graph.h"

namespace s21 {

class Ant {
 public:
  Ant(const Graph &graph, const Graph &closeness, const Graph &pheromones)
      : graph_(graph),
        closeness_(closeness),
        pheromones_(pheromones),
        size_(graph.size()){};

  void SetStartingVertex(uint starting_vertex)
      starting_vertex_(starting_vertex){};

  void Run(){};

  Graph GetNewPheromones() const { return new_pheromones_; };
  std::pair<double, std::vector> GetResult() const { return solution_; };

 private:
  void RunAnt();
  uint ChooseVertex();
  void FindPossibleMoves();
  double CalculateProbabilities();
  void PlacePheromones(double value);

  Graph graph_;
  Graph closeness_;
  Graph pheromones_;
  Graph new_pheromones_;

  static const double kAlpha = 1;
  static const double kBeta = 1;
  static const double kPheromoneValue = 100;

  uint size_;
  uint starting_vertex_;
  uint current_vertex_;
  double distance_;

  std::set<uint> visited_vertices_;
  std::set<uint> possible_moves_;
  std::map<uint, double> probabilities_;
  std::vector<uint> path_;
  std::pair<double, std::vector<uint>> solution_;
};

}  // namespace s21

#endif  // NAVIGATOR_ANT_H_