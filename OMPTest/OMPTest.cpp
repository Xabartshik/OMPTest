#include "utils.h"
#include <iostream>
#include <chrono>

//Сделал: Ошлаков Данил, ИВТ-22
//https://ivtipm.github.io/Programming/Glava20/index20.htm#z676 (а)
using namespace std;

int main() {
    const int rows = 1000;  // Большая матрица для наглядности замера времени
    const int cols = 1000;
    const int minVal = 0;
    const int maxVal = 100;

    // Генерация случайной матрицы
    vector<vector<int>> matrix = generateRandomMatrix(rows, cols, minVal, maxVal);

    // Копия матрицы для параллельной версии
    vector<vector<int>> matrixParallel = matrix;

    // Замер времени для последовательной версии
    auto startSeq = chrono::high_resolution_clock::now();
    reverseColumnsSequential(matrix);
    auto endSeq = chrono::high_resolution_clock::now();
    chrono::duration<double> durationSeq = endSeq - startSeq;

    // Замер времени для параллельной версии (OpenMP)
    auto startPar = chrono::high_resolution_clock::now();
    reverseColumnsParallel(matrixParallel);
    auto endPar = chrono::high_resolution_clock::now();
    chrono::duration<double> durationPar = endPar - startPar;

    // Вывод результатов
    cout << "Размер матрицы: " << rows << "x" << cols << "\n";
    cout << "Последовательная версия: " << durationSeq.count() << " сек.\n";
    cout << "Параллельная версия (OpenMP): " << durationPar.count() << " сек.\n";
    cout << "Ускорение: " << durationSeq.count() / durationPar.count() << "x\n";

    return 0;
}