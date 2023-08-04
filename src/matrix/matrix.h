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
    return matrix_.at(row).at(col);
  }

  double& operator()(size_t row, size_t col) { return matrix_.at(row).at(col); }

  Matrix operator*(const double number) const {
    Matrix result(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i) {
      for (size_t j = 0; j < cols_; ++j) {
        result.matrix_[i][j] = matrix_[i][j] * number;
      }
    }
    return result;
  }

  Matrix Transpose() const {
    size_t rows = GetCols();
    size_t cols = GetRows();
    Matrix result(cols, rows);
    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < cols; ++j) {
        result(j, i) = (*this)(i, j);
      }
    }
    return result;
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

  void ZeroOut() {
    for (auto& row : matrix_) {
      for (auto& element : row) {
        element = 0.0;
      }
    }
  }

 private:
  std::vector<std::vector<double>> matrix_;
  size_t rows_;
  size_t cols_;
};