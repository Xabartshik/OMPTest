#include <iostream>
#include <random>
#include <omp.h>
#include <iomanip>

using namespace std;

// Вывод матрицы (с ограничением на размер для удобства)
void printMatrix(const vector<vector<int>>& matrix) {
    const size_t maxDisplayRows = 10;    // Макс. строк для вывода
    const size_t maxDisplayCols = 10;    // Макс. столбцов для вывода

    size_t rows = matrix.size();
    if (rows == 0) {
        cout << "Матрица пуста!\n";
        return;
    }
    size_t cols = matrix[0].size();

    cout << "Матрица [" << rows << "x" << cols << "]:\n";

    // Выводим только часть матрицы, если она слишком большая
    bool isTruncated = (rows > maxDisplayRows) || (cols > maxDisplayCols);
    if (isTruncated) {
        cout << "(Выводятся первые " << maxDisplayRows << "x" << maxDisplayCols << " элементов)\n";
    }

    for (size_t i = 0; i < min(rows, maxDisplayRows); ++i) {
        for (size_t j = 0; j < min(cols, maxDisplayCols); ++j) {
            cout << setw(4) << matrix[i][j] << " ";  // Форматирование
        }
        if (cols > maxDisplayCols) {
            cout << "...";  // Обозначаем, что есть ещё столбцы
        }
        cout << endl;
    }
    if (rows > maxDisplayRows) {
        cout << "   ...\n";  // Обозначаем, что есть ещё строки
    }
    cout << endl;
}

// Генерация случайной матрицы
vector<vector<int>> generateRandomMatrix(int rows, int cols, int minVal, int maxVal) {
    vector<vector<int>> matrix(rows, vector<int>(cols));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(minVal, maxVal);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = dist(gen);
        }
    }
    return matrix;
}

// Последовательная перестановка столбцов
void reverseColumnsSequential(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    if (rows == 0) return;
    int cols = matrix[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols / 2; ++j) {
            swap(matrix[i][j], matrix[i][cols - 1 - j]);
        }
    }
}

// Параллельная перестановка столбцов (OpenMP)
void reverseColumnsParallel(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    if (rows == 0) return;
    int cols = matrix[0].size();

#pragma omp parallel for shared(matrix)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols / 2; ++j) {
            swap(matrix[i][j], matrix[i][cols - 1 - j]);
        }
    }
}
