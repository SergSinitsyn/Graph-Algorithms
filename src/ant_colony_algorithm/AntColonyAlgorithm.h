#ifndef NAVIGATOR_ANT_COLONY_ALGORITHM_H_
#define NAVIGATOR_ANT_COLONY_ALGORITHM_H_

#include "../21_graph.h"

namespace s21 {

class AntColonyAlgorithm {
 public:
  struct TsmResult {
    std::vector<int> vertices;
    double distance;
  };
  AntColonyAlgorithm(const Graph &graph);
  void RunAlgorithm();
  TsmResult GetResult() const { return result_; };

 private:
  void Itetation();

  Graph graph_;
  Graph closeness_;
  Graph pheromones_;

  TsmResult result_;

  static const int kInitialPheromoneValue = 0.2;
  static const int kMagicLength = 100;
  static const float kVaporization = 0.5;
  static const int kInetations = 100;
  int ants_count_;
  int size_;
};

}  // namespace s21

#endif  // NAVIGATOR_ANT_COLONY_ALGORITHM_H_
