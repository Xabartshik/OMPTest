#include "utils.h"
#include <iostream>
#include <chrono>

//Сделал: Ошлаков Данил, ИВТ-22
//https://ivtipm.github.io/Programming/Glava20/index20.htm#z676 (а)
using namespace std;

int main() {
    // Размеры матриц для тестирования
    const std::vector<std::pair<int, int>> matrixSizes = {
        {10000, 10000},
        {20000, 20000},
        {30000, 30000},
        {40000, 40000},
        {50000, 50000},
        {60000, 60000},
        {70000, 70000},
        {80000, 80000},
        {90000, 90000},
        {100000, 100000},
    };

    const int minVal = 0;
    const int maxVal = 100;

    // Векторы для хранения времени выполнения
    std::vector<double> sequentialTimes;
    std::vector<double> parallelTimes;

    int i = 0;

    for (const auto& [rows, cols] : matrixSizes) {
        // Генерация случайной матрицы
        auto matrix = generateRandomMatrix(rows, cols, minVal, maxVal);
        auto matrixParallel = matrix;  // Копия для параллельной версии

        // Замер времени для последовательной версии
        auto startSeq = std::chrono::high_resolution_clock::now();
        reverseColumnsSequential(matrix);
        auto endSeq = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationSeq = endSeq - startSeq;
        sequentialTimes.push_back(durationSeq.count());

        // Замер времени для параллельной версии
        auto startPar = std::chrono::high_resolution_clock::now();
        reverseColumnsParallel(matrixParallel);
        auto endPar = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationPar = endPar - startPar;
        parallelTimes.push_back(durationPar.count());

        // Вывод информации о текущем тесте
        std::cout << "Размер матрицы: " << rows << "x" << cols << "\n";
        std::cout << "Последовательная версия: " << durationSeq.count() << " сек.\n";
        std::cout << "Параллельная версия: " << durationPar.count() << " сек.\n";
        std::cout << "Ускорение: " << durationSeq.count() / durationPar.count() << "x\n\n";
    }

    // Вывод массивов времени
    std::cout << "Время последовательной работы: [";
    for (double time : sequentialTimes) {
        std::cout << time << ", ";
    }
    std::cout << "]\n";

    std::cout << "Время параллельной работы: [";
    for (double time : parallelTimes) {
        std::cout << time << ", ";
    }
    std::cout << "]\n";

    return 0;
}