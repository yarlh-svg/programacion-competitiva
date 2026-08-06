//Yarin Nilo Laqui Huilahuaña
//Anderson Leonardo Flores Macedo
//Gabriel Anderson Ramos Jahuira
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int swp = 0;



void bubbleSort(int arr[], int e_size) {
    int n = e_size;
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
                swp++;
            }
        }
        if (!swapped)
            break;
    }
}

int main() {
    ifstream file("GFG.txt");

    if (!file.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    int s_a;
    int data_set = 1;
    string final_output = "";

    while (file >> s_a && s_a != 0) {
        int r0[s_a];
        swp = 0;

        for (int n = 0; n < s_a; n++) {
            file >> r0[n];
        }

        bubbleSort(r0, s_a);


        final_output += "There are " + to_string(swp) + " swap maps for input data set " + to_string(data_set) + ".\n";

        data_set++;
    }

    cout << final_output;

    file.close();
    return 0;
}