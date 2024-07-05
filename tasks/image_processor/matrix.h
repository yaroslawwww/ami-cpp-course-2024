//
// Created by msamo on 20.02.2024.
//

#ifndef MATRIX1_MATRIX_H
#define MATRIX1_MATRIX_H

#include <algorithm>
#include <cstddef>

// Представляет матрицу дабблов в соответствии с условиями основной задачи
template <typename T> class Matrix {
public:
  class Row {
    friend class Matrix;

  public:
    size_t GetNum() const { return num_; }

    size_t Size() const { return parent_->GetColsNum(); }

    // TODO: тоже для Matrix

    T &operator[](size_t j) { return parent_->At(num_, j); }

    T operator[](size_t j) const { return parent_->At(num_, j); }

  private:
    // Конструируем строку по её номеру и указателю на родителськую матрицу,
    // запрещаем это делать всем, кроме родительской матрицы, поэтому private
    Row(size_t num, Matrix *parent) : parent_(parent), num_(num) {}

  private:
    Matrix *parent_; // Указатель на родительскую матрицу: строка никогда не
    // бывает сама по себе.
    size_t num_; // Храним номер строки
  };

  // Константная версия класса Row, которая будет использоваться в константных
  // контекстах
  class ConstRow {
    friend class Matrix;

  public:
    size_t GetNum() const { return num_; }

    size_t Size() const { return parent_->GetColsNum(); }

    // TODO: тоже для Matrix

    // Нельзя предоставить неконстантных доступ к элементу константного объекта
    // T& operator[](size_t j) {

    T operator[](size_t j) {
      return parent_->At(num_, j); // Вызывается константная версия At
    }

    T operator[](size_t j) const {
      // Matrix::At const
      return parent_->At(num_, j); // Вызывается константная версия At
    }

  private:
    // Конструируем строку по её номеру и указателю на родителськую матрицу,
    // запрещаем это делать всем, кроме родительской матрицы, поэтому private
    ConstRow(size_t num, const Matrix *parent) : num_(num), parent_(parent) {}

  private:
    const Matrix *parent_; // Указатель на родительскую матрицу: строка никогда
    // не бывает сама по себе.
    size_t num_; // Храним номер строки
  };

public:
  /// конструктор по умолчанию (без параметров)
  Matrix() : ptr_(nullptr), rows_num_(0), cols_num_(0) {
    // в этом месте объекты ptr_, cols_num_, rows_num_ уже созданы и
    // проинициализированы, поэтому в следующих строчках мы не инициализируеем
    // поля, а переприсваиваем значения
    // ptr_ = nullptr; то есть работает оператор присваивания
    // rows_num_ = 0;
    // cols_num_ = 0;
  }

  /// конструктор получает на вход число столбцов и строк и обционально
  /// дефольный элемент матрицы распределяет память, заполняет элементы
  /// дефолтным значением так как конструктор будет большой и нетривиальный, то
  /// его код в заголовочном файле становится не по делу Не может быть ситуации,
  /// когда у нас только один размер равен 0. Это исключительная ситуация
  ///
  Matrix(size_t rows, size_t colms, T def_elem = T{});

  // Коструктор копирования, т.к. имеет вполне конкретный параметр
  Matrix(const Matrix &other);

  ~Matrix();

  // Реализуем операцию присваивания "влоб"
  // Это бинарный оператор, реализуемый только как функция-член, а
  // следовательно, левый операнд приходит через this.
  Matrix &operator=(/*Matrix& lhs,*/ const Matrix &rhs);

  // Реализуем оператор [], возвращающий i-ую строку матрицы.
  // Будет в двух перегрузках: константной и неконстантной.
  // Объект, представляющий строку, мог бы быть указателем на первый элемент
  // строки, но ему кое-чего не хватает: сколько элемнтов в строке, к какой
  // матрице относится эта строка. Реадизуем это в соответствии с пунктом 5
  // наших требований (см. main), реализовав легковесный объект "i-ая строка
  // конкретной матрицы" (инспирированная типом данных string_view).

  Row operator[](size_t num) {
    // Не выполняем проверку на выход за пределы диапазона в соответствии с
    // принципом подобия со стандартным контейнером вектор
    return Row(num, this); // Matrix* this
  }

  ConstRow operator[](size_t num) const {
    // return Row(num, this);
    return ConstRow(num, this); // const Matrix* this
  }

  class Column {
    friend class Matrix;

  public:
    size_t GetNum() const { return num_; }

    size_t Size() const { return parent_->GetRowsNum(); }

    T operator()(size_t i) { return parent_->At(i, num_); }

    T operator()(size_t i) const { return parent_->At(i, num_); }

  private:
    Column(size_t num, Matrix *parent) : parent_(parent), num_(num) {}

  private:
    Matrix *parent_;
    size_t num_;
  };

  class ConstColumn {
    friend class Matrix;

  public:
    size_t GetNum() const { return num_; }

    size_t Size() const { return parent_->GetRowsNum(); }

    T operator()(size_t j) { return parent_->At(num_, j); }

    T operator()(size_t j) const { return parent_->At(num_, j); }

  private:
    ConstColumn(size_t num, const Matrix *parent)
        : num_(num), parent_(parent) {}

  private:
    const Matrix *parent_;
    size_t num_;
  };

  Column operator()(size_t num) { return Column(num, this); }

  ConstColumn operator()(size_t num) const { return ConstColumn(num, this); }

  // возвращает i,j элемент матрицы проверяя что не выходит за границы
  // диапазонов нужен будет неконстантный перегруженный вариант функции
  T At(size_t i, size_t j) const;

  // Неконстантная перегрузка для возможности использования функции в лейвой
  // позиции для возможности изменения элемента матрицы. Абсолютно стандартный
  // подход.
  T &At(size_t i, size_t j);

  size_t GetColsNum() const { return cols_num_; }

  size_t GetRowsNum() const { return rows_num_; }

  bool IsEmpty() const { return rows_num_ == 0; }

private:
  // Вспомогательная функция, изолирующая арифметику смещения для конкретной
  // реализации. Будет развеёрнута как inline, поэтому никаких накладных
  // расходов.
  size_t CalcOffset(size_t i, size_t j) const { return i * cols_num_ + j; }

  // Вспомогательный приватный метод, распределяющий память для заданного
  // количества строки столбцов.
  T *AllocateMatrixStorage(size_t rows, size_t cols) {
    ptr_ = new T[rows * cols];
    return ptr_;
  }

  // В соответствии с правилом "destructors, finalizers, swap must never fail"
  static void Swap(Matrix &m1, Matrix &m2) noexcept {
    std::swap(m1.ptr_, m2.ptr_);
    std::swap(m1.rows_num_, m2.rows_num_);
    std::swap(m1.cols_num_, m2.cols_num_);
  }

public:
  T *ptr_;

private: ///< хранит указатель на начало последовательности элементов матрицы
  size_t rows_num_; ///< число строк
  size_t cols_num_;
};

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t colms, T def_elem)
    : rows_num_(rows), cols_num_(colms) {
  //    if ((rows == 0 && colms != 0) || (rows != 0 && colms == 0)) {
  //        throw std::invalid_argument("You are trying to create matrix with 0
  //        rows or 0 colums.");
  //    }
  // распределим динамическую память необходимого размера в куче
  // если запрошенную память не удастся распределить то полетит bad_alloc
  // exception ptr_ = new T[rows * colms];
  AllocateMatrixStorage(rows, colms);
  for (size_t i = 0; i < rows * colms; ++i) {
    ptr_[i] = def_elem;
  }
} // этот тип исключительных ситуаций нужен для реализации конструктора матрицы
// что ещё раз подчёркивает важность реализации в .cpp
#include <stdexcept>

// дефолтное значение может быть представлено только один раз или в заголобочном
// файле, или в .cpp

template <typename T>
Matrix<T>::Matrix(const Matrix &other)
    : ptr_(other.rows_num_ == 0
               ? nullptr
               : AllocateMatrixStorage(other.rows_num_, other.cols_num_)),
      rows_num_(other.rows_num_), cols_num_(other.cols_num_)
//, ptr_(other.rows_num_ == 0 ? nullptr : new T[other.rows_num_ *
// other.cols_num_])

{
  if (!ptr_) {
    return;
  }
  for (size_t i = 0; i < rows_num_ * cols_num_; ++i) {
    ptr_[i] = other.ptr_[i];
  }
}

template <typename T> Matrix<T>::~Matrix() {
  if (ptr_) { // для delete нет необходимости в этой проверке
    delete[] ptr_;
    ptr_ = nullptr; // в деструкторе это необязательно
  }
}

// TODO: домашнее задание: проверить работоспособность этого метода и при
// необходимости отладить. НЕдостаток метода "влоб" заключается в:
// 1. Запутанная логика копирования. (условно)
// 2. Дублирование кода, всё, что связвно с распределением памяти, дублирует
// конструктор копирования.
// 3. В +10 строчке мы удаляем память, но после этого AllocateMatrixStorage
// может зафейлиться. Тогда исходная матрица повредилась, а новая не
// скопировалась. (исключение полетит от оператора new и объект в этот момент
// будет не консистентный). Постараемся этого избежать.
// template<typename T>
// Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
//     // Проверяем строго адреса, ни в коем случае не сами значения матрицы.
//     if (&rhs == this) {
//         return *this;
//     }
//     // С целью оптимизации можно избежать перераспределения памяти для равных
//     по размеру матриц.
//         if (rhs.cols_num_ != cols_num_ || rhs.rows_num_ !=
//     rows_num_) {
//         delete[] ptr_;
//         rows_num_ = rhs.rows_num_;
//         cols_num_ = rhs.cols_num_;
//         if (rhs.IsEmpty()) {
//             ptr_ = nullptr;
//             return *this;
//         }
//         AllocateMatrixStorage(rhs.rows_num_, rhs.cols_num_);
//     }
//     for (size_t i = 0; i < rows_num_ * cols_num_; ++i) {
//         ptr_[i] = rhs.ptr_[i];
//     }
//     return *this;
// }

// Реализуем оператор присваивания с использованием идиомы "copy and swap".
// 1. Будем переиспользовать конструктор копирования.
// 2. Сделаем исключение-безопасным.
// Для этого нам нужен вспомогательный метод swap, который будет обменивать
//// местами "хранителей ресурсов".
template <typename T> Matrix<T> &Matrix<T>::operator=(const Matrix &rhs) {
  if (this == &rhs) {
    return *this;
  }
  Matrix temp(rhs);
  Swap(*this, temp);
  return *this;
}

template <typename T> T Matrix<T>::At(size_t i, size_t j) const {
  if (i >= rows_num_ || j >= cols_num_) {
    throw std::out_of_range("Invalid matrix element's index.");
  }
  // return ptr_[cols_num_ * i + j];
  return ptr_[CalcOffset(i, j)];
}

template <typename T> T &Matrix<T>::At(size_t i, size_t j) {
  if (i >= rows_num_ || j >= cols_num_) {
    throw std::out_of_range("Invalid matrix element's index.");
  }
  return ptr_[CalcOffset(i, j)];
}

#endif // MATRIX1_MATRIX_H
