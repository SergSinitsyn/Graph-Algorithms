#include <exception>
#include <iostream>
#include <vector>

class Matrix {
 public:
  Matrix() : Matrix(1, 1) {}

  Matrix(size_t size) : Matrix(size, size) {}

  Matrix(size_t rows, size_t cols)
      : matrix_(rows, std::vector<double>(cols)), rows_(rows), cols_(cols) {}

  Matrix(size_t rows, size_t cols, double value)
      : matrix_(rows, std::vector<double>(cols, value)),
        rows_(rows),
        cols_(cols) {}

  size_t GetRows() const { return rows_; }

  size_t GetCols() const { return cols_; }

  void SetRows(size_t rows) {
    if (rows < 1) throw std::out_of_range("Matrix rows out of range");
    if (rows_ == rows) return;

    matrix_.resize(rows, std::vector<double>(cols_, 0.0));
    rows_ = rows;
  }

  void SetCols(size_t cols) {
    if (cols < 1) throw std::out_of_range("Matrix cols out of range");
    if (cols_ == cols) return;

    for (auto& row : matrix_) {
      row.resize(cols, 0.0);
    }
    cols_ = cols;
  }

  void SetSize(size_t size) {
    SetRows(size);
    SetCols(size);
  }

  double operator()(size_t row, size_t col) const {
    if (row >= rows_ || col >= cols_) {
      throw std::out_of_range("Matrix index out of range");
    }
    return matrix_[row][col];
  }

  double& operator()(size_t row, size_t col) {
    if (row >= rows_ || col >= cols_) {
      throw std::out_of_range("Matrix index out of range");
    }
    return matrix_[row][col];
  }

  void Add(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
      throw std::runtime_error("Matrix sizes are not compatible for addition");
    }
    for (size_t i = 0; i < rows_; ++i) {
      for (size_t j = 0; j < cols_; ++j) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }

  void MultNumber(const double number) {
    for (size_t i = 0; i < rows_; ++i) {
      for (size_t j = 0; j < cols_; ++j) {
        matrix_[i][j] *= number;
      }
    }
  }

  void PrintMatrix() const {
    for (const auto& row : matrix_) {
      for (const auto& element : row) {
        std::cout << element << " ";
      }
      std::cout << std::endl;
    }
  }

 private:
  std::vector<std::vector<double>> matrix_;
  size_t rows_;
  size_t cols_;
};