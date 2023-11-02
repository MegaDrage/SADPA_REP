#include <cmath>
#include <iostream>
#include <string>
const int MAX_CHAR = 26;
void gilbertMooreAlg(double*& P, int* L, int**& C, int n);
// function to print string in sorted order
int sortString(std::string& str, double*& P, int& sum) {
    // Hash array to keep count of characters.
    // Initially count of all characters is
    // initialized to zero.
    int charCount[MAX_CHAR] = {0};

    // Traverse string and increment
    // count of characters
    for (std::size_t i = 0; i < str.length(); i++) {
        // 'a'-'a' will be 0, 'b'-'a' will be 1,
        // so for location of character in count
        // array we will do str[i]-'a'.
        charCount[str[i] - 'a']++;
    }
    int count = 0;
    sum = 0;
    for (int i = 0; i < MAX_CHAR; i++) {
        count += charCount[i] > 0;
        sum += charCount[i];
    }

    P = new double[count];
    int j = 0;
    for (int i = 0; i < MAX_CHAR; i++) {
        if (charCount[i] > 0) {
            P[j++] = charCount[i] / (double)sum;
        }
    }
    // Traverse the hash array and print
    // characters
    for (int i = 0; i < MAX_CHAR; i++)
        for (int j = 0; j < charCount[i]; j++) std::cout << (char)('a' + i);
    std::cout << std::endl;
    return count;
}

int main() {
    std::string text = "Huffman coding is a data compression algorithm";
    double* p;
    int len;
    int count = sortString(text, p, len);
    int L[count];
    int** C = new int*[count];
    for (int i = 0; i < count; i++) {
        C[i] = new int[count];
    }
    gilbertMooreAlg(p, L, C, count);
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < count; i++) {
        std::cout << L[i] << std::endl;
    }
    for (int i = 0; i < count; i++) {
        delete[] C[i];
    }
    delete[] C;
    delete[] p;
    return 0;
}

void gilbertMooreAlg(double*& P, int* L, int**& C, int n) {
    double pr = 0;
    double Q[n];
    for (int i = 0; i < n; i++) {
        Q[i] = pr + P[i] / 2.;
        pr += P[i];
        L[i] = -std::ceil(std::log2(P[i])) + 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < L[i]; j++) {
            Q[i] *= 2;
            C[i][j] = std::floor(Q[i]);
            if (Q[i] > 1) Q[i] -= 1;
        }
    }
}

// void getProbabilities(std::string& text) {}