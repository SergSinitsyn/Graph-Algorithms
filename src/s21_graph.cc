#include "s21_graph.h"

#include <fstream>
using namespace s21;

void Graph::SetSize(size_t size) {
  size_ = size;
  adjacency_matrix_.resize(size);
  for (auto& row : adjacency_matrix_) row.resize(size);
}

void Graph::ReadLine(uint& line_number, const std::string& line) {
  size_t num_size = 0;
  size_t line_index = 0;
  for (uint col_index = 0; col_index < size_; ++col_index) {
    uint number = std::stoi(&line.at(line_index), &num_size);
    adjacency_matrix_.at(line_number).at(col_index) = number;
    line_index += num_size;
  }
}

size_t Graph::ReadSize(const std::string& line) {
  size_t pos = 0;
  size_t number = std::stoi(&line.at(pos), &pos);
  if (number < kMinSize || number > kMaxSize) {
    throw std::invalid_argument(
        "File read error. The dimensions are not correct.");
  }
  return number;
}

void Graph::LoadGraphFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file) {
    throw std::invalid_argument("File read error. The file is missing.");
  }
  if (file.peek() == std::ifstream::traits_type::eof()) {
    throw std::invalid_argument("File read error. The file is empty.");
  }
  std::string line;
  std::getline(file, line);
  SetSize(ReadSize(line));
  for (uint i = 0; i < size_; ++i) {
    std::getline(file, line);
    if (!line.empty()) {
      ReadLine(i, line);
    } else {
      --i;
    }
  }
  file.close();
}
