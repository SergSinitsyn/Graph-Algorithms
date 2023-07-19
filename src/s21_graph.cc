#include "s21_graph.h"

#include <fstream>
#include <sstream>
using namespace s21;

size_t Graph::size() const { return size_; };

size_t Graph::GetVertexCount() const { return size_; };

uint Graph::GetEdge(uint from, uint to) const {
  return adjacency_matrix_.at(from).at(to);
};

const Graph::AdjacencyMatrix& Graph::GetMatrix() const {
  return adjacency_matrix_;
}

void Graph::SetSize(size_t size) {
  size_ = size;
  adjacency_matrix_.resize(size);
  for (auto& row : adjacency_matrix_) {
    row.resize(size, 0);
  }
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

size_t s21::Graph::CountVerticesGraph(const std::string& line) {
  size_t count = 0;
  std::istringstream iss(line);
  std::string word;
  while (iss >> word) {
    count++;
  }
  return count;
}

std::string Graph::GetNonEmptyLine(std::ifstream& file) {
  std::string line;
  std::getline(file, line);
  while (line.empty()) {
    std::getline(file, line);
  }
  return line;
}

bool Graph::GraphOrientationCheck() {
  for (uint i = 0; i < size_; ++i) {
    for (uint j = i; j < size_; ++j) {
      if (adjacency_matrix_.at(i).at(j) != adjacency_matrix_.at(j).at(i)) {
        return false;
      }
    }
  }
  return true;
}

size_t Graph::ReadSize(const std::string& line) {
  size_t position = 0;
  size_t size = std::stoi(&line.at(position), &position);
  if (size < kMinSize || size > kMaxSize) {
    throw std::invalid_argument(
        "File read error. The dimensions are not correct.");
  }
  return size;
}

void Graph::LoadGraphFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file) {
    throw std::invalid_argument("File read error. The file is missing.");
  }
  if (file.peek() == std::ifstream::traits_type::eof()) {
    throw std::invalid_argument("File read error. The file is empty.");
  }

  std::string line = GetNonEmptyLine(file);
  SetSize(ReadSize(line));

  for (uint i = 0; i < size_; ++i) {
    line = GetNonEmptyLine(file);
    if (CountVerticesGraph(line) < size_) {
      throw std::invalid_argument(
          "File read error. Number of vertices does not match graph size");
    }
    ReadLine(i, line);
    if (!line.empty()) {
      ReadLine(i, line);
    } else {
      --i;
    }
  }

  file.close();
}

void s21::Graph::ExportGraphToDot(const std::string& filename) {
  std::ofstream file(filename);
  if (!file) {
    throw std::invalid_argument("File write error. The file is missing.");
  }
  bool is_oriented = !GraphOrientationCheck();
  const std::string graph_type = (is_oriented ? "digraph" : "graph");
  file << graph_type << " Graph {" << std::endl;
  for (uint i = 0; i < size_; ++i) {
    for (uint j = (is_oriented ? 0 : i); j < size_; ++j) {
      if (adjacency_matrix_.at(i).at(j)) {
        file << "    " << i + 1 << (is_oriented ? "->" : "--") << j + 1
             << "[label=" << adjacency_matrix_.at(i).at(j) << "];" << std::endl;
      }
    }
  }
  file << "}" << std::endl;
}