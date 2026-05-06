#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cstring>
using namespace std;

struct SortResult {
    string name;
    long long steps;
    long long timeNs;
};

// ============= BUBBLE SORT =============
SortResult bubbleSort(vector<int> arr) {
    auto start = chrono::high_resolution_clock::now();
    long long pasos = 0;
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            pasos++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    long long timeNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
    return {string("Bubble Sort"), pasos, timeNs};
}

// ============= SELECTION SORT =============
SortResult selectionSort(vector<int> arr) {
    auto start = chrono::high_resolution_clock::now();
    long long pasos = 0;
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            pasos++;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
    
    auto end = chrono::high_resolution_clock::now();
    long long timeNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
    return {string("Selection Sort"), pasos, timeNs};
}

// ============= INSERTION SORT =============
SortResult insertionSort(vector<int> arr) {
    auto start = chrono::high_resolution_clock::now();
    long long pasos = 0;
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            pasos++;
            arr[j + 1] = arr[j];
            j--;
        }
        pasos++;
        arr[j + 1] = key;
    }
    
    auto end = chrono::high_resolution_clock::now();
    long long timeNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
    return {string("Insertion Sort"), pasos, timeNs};
}

// ============= MERGE SORT =============
void mergeHelper(vector<int>& arr, int left, int mid, int right, long long& pasos) {
    vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);
    
    int i = 0, j = 0, k = left;
    while (i < leftArr.size() && j < rightArr.size()) {
        pasos++;
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }
    while (i < leftArr.size()) {
        pasos++;
        arr[k++] = leftArr[i++];
    }
    while (j < rightArr.size()) {
        pasos++;
        arr[k++] = rightArr[j++];
    }
}

void mergeSortHelper(vector<int>& arr, int left, int right, long long& pasos) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid, pasos);
        mergeSortHelper(arr, mid + 1, right, pasos);
        mergeHelper(arr, left, mid, right, pasos);
    }
}

SortResult mergeSort(vector<int> arr) {
    auto start = chrono::high_resolution_clock::now();
    long long pasos = 0;
    
    if (!arr.empty()) {
        mergeSortHelper(arr, 0, arr.size() - 1, pasos);
    }
    
    auto end = chrono::high_resolution_clock::now();
    long long timeNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
    return {string("Merge Sort"), pasos, timeNs};
}

// ============= QUICK SORT =============
int partitionQuick(vector<int>& arr, int low, int high, long long& pasos) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        pasos++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(vector<int>& arr, int low, int high, long long& pasos) {
    if (low < high) {
        int pi = partitionQuick(arr, low, high, pasos);
        quickSortHelper(arr, low, pi - 1, pasos);
        quickSortHelper(arr, pi + 1, high, pasos);
    }
}

SortResult quickSort(vector<int> arr) {
    auto start = chrono::high_resolution_clock::now();
    long long pasos = 0;
    
    if (!arr.empty()) {
        quickSortHelper(arr, 0, arr.size() - 1, pasos);
    }
    
    auto end = chrono::high_resolution_clock::now();
    long long timeNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
    return {string("Quick Sort"), pasos, timeNs};
}

// ============= HEAP SORT =============
void heapify(vector<int>& arr, int n, int i, long long& pasos) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    if (largest != i) {
        pasos++;
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest, pasos);
    }
}

SortResult heapSort(vector<int> arr) {
    auto start = chrono::high_resolution_clock::now();
    long long pasos = 0;
    int n = arr.size();
    
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, pasos);
    }
    
    for (int i = n - 1; i > 0; i--) {
        pasos++;
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, pasos);
    }
    
    auto end = chrono::high_resolution_clock::now();
    long long timeNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
    return {string("Heap Sort"), pasos, timeNs};
}

// ============= SHELL SORT =============
SortResult shellSort(vector<int> arr) {
    auto start = chrono::high_resolution_clock::now();
    long long pasos = 0;
    int n = arr.size();
    
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                pasos++;
                arr[j] = arr[j - gap];
            }
            pasos++;
            arr[j] = temp;
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    long long timeNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
    return {string("Shell Sort"), pasos, timeNs};
}

// ============= COUNTING SORT =============
SortResult countingSort(vector<int> arr) {
    auto start = chrono::high_resolution_clock::now();
    long long pasos = 0;
    
    if (arr.empty()) {
        auto end = chrono::high_resolution_clock::now();
        long long timeNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        return {string("Counting Sort"), pasos, timeNs};
    }
    
    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;
    
    vector<int> count(range, 0);
    
    for (int i = 0; i < arr.size(); i++) {
        pasos++;
        count[arr[i] - minVal]++;
    }
    
    for (int i = 1; i < range; i++) {
        pasos++;
        count[i] += count[i - 1];
    }
    
    vector<int> output(arr.size());
    for (int i = arr.size() - 1; i >= 0; i--) {
        pasos++;
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }
    
    for (int i = 0; i < arr.size(); i++) {
        pasos++;
        arr[i] = output[i];
    }
    
    auto end = chrono::high_resolution_clock::now();
    long long timeNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
    return {string("Counting Sort"), pasos, timeNs};
}

// ============= RADIX SORT =============
SortResult radixSort(vector<int> arr) {
    auto start = chrono::high_resolution_clock::now();
    long long pasos = 0;
    
    if (arr.empty()) {
        auto end = chrono::high_resolution_clock::now();
        long long timeNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        return {string("Radix Sort"), pasos, timeNs};
    }
    
    int maxVal = *max_element(arr.begin(), arr.end());
    
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        vector<int> output(arr.size());
        vector<int> count(10, 0);
        
        for (int i = 0; i < arr.size(); i++) {
            pasos++;
            count[(arr[i] / exp) % 10]++;
        }
        
        for (int i = 1; i < 10; i++) {
            pasos++;
            count[i] += count[i - 1];
        }
        
        for (int i = arr.size() - 1; i >= 0; i--) {
            pasos++;
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        
        for (int i = 0; i < arr.size(); i++) {
            pasos++;
            arr[i] = output[i];
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    long long timeNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
    return {string("Radix Sort"), pasos, timeNs};
}

// ============= BUCKET SORT =============
SortResult bucketSort(vector<int> arr) {
    auto start = chrono::high_resolution_clock::now();
    long long pasos = 0;
    
    if (arr.empty()) {
        auto end = chrono::high_resolution_clock::now();
        long long timeNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        return {string("Bucket Sort"), pasos, timeNs};
    }
    
    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());
    int bucketCount = min(10, (int)arr.size());
    
    vector<vector<int>> buckets(bucketCount);
    
    for (int i = 0; i < arr.size(); i++) {
        pasos++;
        int idx = (arr[i] - minVal) * bucketCount / (maxVal - minVal + 1);
        if (idx == bucketCount) idx--;
        buckets[idx].push_back(arr[i]);
    }
    
    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        sort(buckets[i].begin(), buckets[i].end());
        for (int j = 0; j < buckets[i].size(); j++) {
            pasos++;
            arr[index++] = buckets[i][j];
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    long long timeNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
    return {string("Bucket Sort"), pasos, timeNs};
}

// ============= COCKTAIL SORT (Bidirectional Bubble Sort) =============
SortResult cocktailSort(vector<int> arr) {
    auto start = chrono::high_resolution_clock::now();
    long long pasos = 0;
    int n = arr.size();
    bool swapped = true;
    int start_idx = 0;
    int end_idx = n - 1;
    
    while (swapped) {
        swapped = false;
        
        // Forward pass
        for (int i = start_idx; i < end_idx; i++) {
            pasos++;
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        
        if (!swapped) break;
        end_idx--;
        swapped = false;
        
        // Backward pass
        for (int i = end_idx; i > start_idx; i--) {
            pasos++;
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        start_idx++;
    }
    
    auto end = chrono::high_resolution_clock::now();
    long long timeNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
    return {string("Cocktail Sort"), pasos, timeNs};
}

// ============= TIM SORT (Simplified version) =============
void timSortInsertionSort(vector<int>& arr, int left, int right, long long& pasos) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            pasos++;
            arr[j + 1] = arr[j];
            j--;
        }
        pasos++;
        arr[j + 1] = key;
    }
}

void timSortMerge(vector<int>& arr, int left, int mid, int right, long long& pasos) {
    vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);
    
    int i = 0, j = 0, k = left;
    while (i < leftArr.size() && j < rightArr.size()) {
        pasos++;
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }
    while (i < leftArr.size()) {
        pasos++;
        arr[k++] = leftArr[i++];
    }
    while (j < rightArr.size()) {
        pasos++;
        arr[k++] = rightArr[j++];
    }
}

void timSortHelper(vector<int>& arr, int left, int right, int minRun, long long& pasos) {
    if (right - left < minRun) {
        timSortInsertionSort(arr, left, right, pasos);
        return;
    }
    
    int mid = left + (right - left) / 2;
    timSortHelper(arr, left, mid, minRun, pasos);
    timSortHelper(arr, mid + 1, right, minRun, pasos);
    timSortMerge(arr, left, mid, right, pasos);
}

SortResult timSort(vector<int> arr) {
    auto start = chrono::high_resolution_clock::now();
    long long pasos = 0;
    
    if (arr.empty()) {
        auto end = chrono::high_resolution_clock::now();
        long long timeNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        return {string("Tim Sort"), pasos, timeNs};
    }
    
    int minRun = 32;
    timSortHelper(arr, 0, arr.size() - 1, minRun, pasos);
    
    auto end = chrono::high_resolution_clock::now();
    long long timeNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    
    return {string("Tim Sort"), pasos, timeNs};
}


// ============= MAIN =============
int main() {
    int n, min_val, max_val;
    
    cout << "=== COMPARADOR DE ALGORITMOS DE ORDENAMIENTO ===" << endl << endl;
    cout << "Ingrese la cantidad de numeros a generar: ";
    cin >> n;
    cout << "Ingrese el valor minimo del rango: ";
    cin >> min_val;
    cout << "Ingrese el valor maximo del rango: ";
    cin >> max_val;
    
    // Validate input
    if (n <= 0 || min_val > max_val) {
        cerr << "Entrada invalida" << endl;
        return 1;
    }
    
    // Generate random array once
    vector<int> original(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min_val, max_val);
    
    cout << "\nGenerando " << n << " numeros aleatorios entre " << min_val 
         << " y " << max_val << "..." << endl;
    
    for (int i = 0; i < n; i++) {
        original[i] = dis(gen);
    }
    
    // Display original array
    cout << "\nArray Original: ";
    if (n <= 50) {
        for (int i = 0; i < n; i++) {
            cout << original[i];
            if (i < n - 1) cout << ", ";
        }
    } else {
        for (int i = 0; i < 20; i++) cout << original[i] << ", ";
        cout << "... (" << n - 40 << " elementos mas) ..., ";
        for (int i = n - 20; i < n; i++) {
            cout << original[i];
            if (i < n - 1) cout << ", ";
        }
    }
    cout << "\n" << endl;
    
    vector<SortResult> results;
    
    // Execute all sorting algorithms
    cout << "Ejecutando algoritmos..." << endl;
    results.push_back(bubbleSort(original));
    results.push_back(selectionSort(original));
    results.push_back(insertionSort(original));
    results.push_back(mergeSort(original));
    results.push_back(quickSort(original));
    results.push_back(heapSort(original));
    results.push_back(shellSort(original));
    results.push_back(countingSort(original));
    results.push_back(radixSort(original));
    results.push_back(bucketSort(original));
    results.push_back(timSort(original));
    results.push_back(cocktailSort(original));
    
    // Sort results by execution time
    sort(results.begin(), results.end(), [](const SortResult& a, const SortResult& b) {
        return a.timeNs < b.timeNs;
    });
    
    // Display results
    cout << "\n=== RESULTADOS (Ordenados por Velocidad) ===" << endl;
    cout << left << setw(5) << "Pos" 
         << setw(18) << "Algoritmo" 
         << setw(18) << "Pasos" 
         << setw(20) << "Tiempo (ns)" << endl;
    cout << string(65, '-') << endl;
    
    for (int i = 0; i < results.size(); i++) {
        cout << left << setw(5) << (i + 1) 
             << setw(18) << results[i].name 
             << setw(18) << results[i].steps 
             << setw(20) << results[i].timeNs << endl;
    }
    
    cout << "\n=== RESUMEN ===" << endl;
    cout << "Algoritmo mas rapido: " << results[0].name << endl;
    cout << "Tiempo: " << results[0].timeNs << " ns" << endl;
    cout << "Pasos: " << results[0].steps << endl;
    cout << "\nAlgoritmo mas lento: " << results[results.size()-1].name << endl;
    cout << "Tiempo: " << results[results.size()-1].timeNs << " ns" << endl;
    cout << "Pasos: " << results[results.size()-1].steps << endl;
    
    return 0;
}
