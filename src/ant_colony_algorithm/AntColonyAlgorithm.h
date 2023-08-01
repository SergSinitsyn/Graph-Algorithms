#ifndef NAVIGATOR_ANT_COLONY_ALGORITHM_H_
#define NAVIGATOR_ANT_COLONY_ALGORITHM_H_

#include <map>
#include <set>
#include <vector>

#include "../s21_graph.h"

namespace s21 {

class AntColonyAlgorithm {
 public:
  AntColonyAlgorithm(const Graph &graph);
  void RunAlgorithm();
  std::pair<double, std::vector<uint>> GetResult() const {
    auto it = solutions_.begin();
    if (it != solutions_.end()) {
      return std::pair<double, std::vector<unsigned int>>(it->first,
                                                          it->second);
    } else {
      return {0.0, std::vector<uint>()};
    }
  };

 private:
  void Itetation();

  Graph graph_;
  Graph closeness_;
  Graph pheromones_;

  static constexpr const double kInitialPheromoneValue = 0.2;
  static constexpr const double kMagicLength = 100;
  static constexpr const double kVaporization = 0.5;
  static constexpr const int kInetations = 10;
  int ants_count_;
  int size_;

  std::multimap<double, std::vector<uint>> solutions_;
};

}  // namespace s21

#endif  // NAVIGATOR_ANT_COLONY_ALGORITHM_H_
