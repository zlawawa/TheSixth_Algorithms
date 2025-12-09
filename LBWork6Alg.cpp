#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
void QSort(double arr[], int L, int R) {
    int i = L, j = R;
    double w, x;
    x = arr[(L + R) / 2];
    do {
        while (arr[i] > x) i++;
        while (arr[j] < x) j--;
        if (i <= j) {
            w = arr[i]; arr[i] = arr[j]; arr[j] = w;
            i++; j--;
        }
    } while (i <= j);
    if (L < j) QSort(arr, L, j);
    if (i < R) QSort(arr, i, R);
}

void BucketSort(double arr[], int n) {
    double Min_Val = arr[0], Max_Val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < Min_Val) Min_Val = arr[i];
        if (arr[i] > Max_Val) Max_Val = arr[i];
    }
    std::cout << "Мин. эл-т: " << Min_Val << "\n" << "Макс. эл-т: " << Max_Val << "\n" <<  "Сумма: " << abs(Min_Val) + abs(Max_Val) << "\n" << "Шаг: (" << Max_Val << " + " << Min_Val << ") / 6 = " << ceil((Max_Val - Min_Val + 1) / 6)  << "\n";

    const int BUCK = 6;
    double buckets[BUCK][100];
    int sizes[BUCK] = {0};
    
    double k = ceil((Max_Val - Min_Val + 1) / BUCK); //шаг

    //распределение по блокам
    for (int i = 0; i < n; i++) {
        int bucket_num = (int)((arr[i] - Min_Val) / k); //номер бака
        buckets[bucket_num][sizes[bucket_num]] = arr[i];
        sizes[bucket_num]++;
    }

    std::cout << "Распределение по блокам:\n";
    for (int i = 0; i < BUCK; i++) {
        double lower = Min_Val + i * k;
        double upper = lower + k;
        std::cout << "Блок " << i + 1 << " [" << lower << ", " << upper << "): ";
        for (int j = 0; j < sizes[i]; j++) {
            std::cout << buckets[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    
    //сортируем блоки
    for (int i = 0; i < BUCK; i++) {
        if (sizes[i] > 1) QSort(buckets[i], 0, sizes[i] - 1);
    }
    
    //сливаем обратно
    int idx = 0;
    for (int i = BUCK - 1; i >= 0; i--) {
        for (int j = 0; j < sizes[i]; j++) {
            arr[idx] = buckets[i][j];
            idx++;
        }
    }
}

int main() {
    ifstream file("LBWork6Alg.txt");
    double arr[100];
    int n = 0;
    while (file >> arr[n] && n < 100) n++;
    file.close();
    std::cout << "Исходный массив (" << n << " элементов):\n";
    for (int i = 0; i < n; i++) { std::cout << arr[i] << " "; }
    std::cout << "\n\n";
    BucketSort(arr, n);
    std::cout << "Массив отсортированный по убыванию:\n";
    for (int i = 0; i < n; i++) { std::cout << arr[i] << " "; }
    return 0;
}
