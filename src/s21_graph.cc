#include "s21_graph.h"

#include <fstream>

void Graph::SetSize(unsigned int size) {
  adjacient_matrix_.resize(size);
  for (auto& row : adjacient_matrix_) row.resize(size);
};

void Graph::ReadLine(size_t& line_number, const std::string& line) {
  size_t num_size = 0;
  size_t line_index = 0;
  for (size_t col_index = 0; col_index < cols_; ++col_index) {
    bool number = std::stoi(&line.at(line_index), &num_size);
    adjacient_matrix_.at(line_number).at(col_index) = number;
    line_index += num_size;
  }
}

unsigned int Graph::ReadSize(const std::string& line) {
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
  for (size_t i = 0; i < lines_to_read_; ++i) {
    std::getline(file, line);
    if (!line.empty()) {
      ReadLine(i, line);
    } else {
      --i;
    }
  }
  file.close();
}
