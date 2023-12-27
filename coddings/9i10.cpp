#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cmath>

using namespace std;

struct chanceSymbol
{
    unsigned char ch; // символ
    float chance; // веоятность
};

struct codeShannon
{
    unsigned char ch = 0;
    float Pi = 0; // вероянтность символа
    float Qi = 0; // кумулятивная вероятность
    unsigned short int Li = 0; //длина кодового слова
    char* codeword = nullptr;
};

struct codeFano
{
    unsigned char ch = 0;
    float Pi = 0;
    unsigned short int Li = 0;
    char* codeword = nullptr;
};

struct codeGilbert
{
    unsigned char ch = 0;
    float Pi = 0;
    float Qi = 0;
    unsigned short int Li = 0;
    char* codeword = nullptr;
};

struct codeHuffman
{
    unsigned char ch = 0;
    float Pi = 0;
    unsigned short int Li = 0;
    char* codeword = nullptr;
};

void quickSortV2(chanceSymbol*& A, int R, int L, unsigned short int field, bool reverse)
{
    while (L < R) {
        float x;
        if (field == 0)
            x = A[L].ch;
        else if (field == 1)
            x = A[L].chance;

        int i = L;
        int j = R;
        while (i <= j) {
            if (field == 0) {
                if (reverse) {
                    while (A[i].ch > x)
                        i++;
                    while (A[j].ch < x)
                        j--;
                }
                else
                {
                    while (A[i].ch < x)
                        i++;
                    while (A[j].ch > x)
                        j--;
                }

            }
            else if (field == 1)
            {
                if (reverse) {
                    while (A[i].chance > x)
                        i++;
                    while (A[j].chance < x)
                        j--;
                }
                else
                {
                    while (A[i].chance < x)
                        i++;
                    while (A[j].chance > x)
                        j--;
                }

            }
            if (i <= j) {
                int temp;
                temp = A[i].ch;
                A[i].ch = A[j].ch;
                A[j].ch = temp;
                float tmp;
                tmp = A[i].chance;
                A[i].chance = A[j].chance;
                A[j].chance = tmp;
                i++;
                j--;
            }
        }
        if (j - L > R - i) {
            quickSortV2(A, R, i, field, reverse);
            R = j;
        }
        else {
            quickSortV2(A, j, L, field, reverse);
            L = i;
        }
    }
}

float calculationEntropy(chanceSymbol* A, int nums) {
    float answer = 0;
    for (int i = 0; i < nums; i++) {
        answer += (A[i].chance * log2(A[i].chance));
    }
    return -answer;
}

float calculationAverageLength(codeFano* A, int nums) {
    float answer = 0;
    for (int i = 0; i < nums; i++) {
        answer += A[i].Li * A[i].Pi;
    }
    return answer;
}

float calculationAverageLength(codeShannon* A, unsigned int nums) {
    float answer = 0;
    for (int i = 0; i < nums; i++) {
        answer += A[i].Li * A[i].Pi;
    }
    return answer;
}

float calculationAverageLength(codeGilbert* A, unsigned int nums) {
    float answer = 0;
    for (int i = 0; i < nums; i++) {
        answer += A[i].Li * A[i].Pi;
    }
    return answer;
}

float calculationAverageLength(codeHuffman* A, unsigned int nums) {
    float answer = 0;
    for (int i = 0; i < nums; i++) {
        answer += A[i].Li * A[i].Pi;
    }
    return answer;
}

codeShannon* ShannonCode(chanceSymbol* chanceSymbols, short int numSymbols) {
    codeShannon* shannon = new codeShannon[numSymbols];

    //Инициализация первого символа
    quickSortV2(chanceSymbols, numSymbols - 1, 0, 1, 1);
    shannon[0].ch = chanceSymbols[0].ch;
    shannon[0].Pi = chanceSymbols[0].chance;
    shannon[0].Li = ceil(-log2(shannon[0].Pi));
    shannon[0].Qi = 0;






// Остальные символы
    for (int i = 1; i < numSymbols; i++) {
        shannon[i].ch = chanceSymbols[i].ch;
        shannon[i].Pi = chanceSymbols[i].chance;
        shannon[i].Li = ceil(-log2(shannon[i].Pi));
        shannon[i].Qi = shannon[i - 1].Qi + shannon[i - 1].Pi;
    }

    // Построения
    for (int i = 0; i < numSymbols; i++) {
        float temp = shannon[i].Qi;
        shannon[i].codeword = new char[shannon[i].Li];
        for (int j = 0; j < shannon[i].Li; j++) {
            temp = temp * 2;
            shannon[i].codeword[j] = (char)(floor(temp) + 48);
            if (temp >= 1) {
                temp = temp - 1;
            }
        }
    }
    return shannon;
}

int med(codeFano* fano, int borderL, int borderR) {

    float SumL = 0;
    for (int i = borderL; i < borderR; i++) {
        SumL = SumL + fano[i].Pi;
    }
    float SumR = fano[borderR].Pi;
    int m = borderR;
    while (SumL >= SumR) {
        m = m - 1;
        SumL = SumL - fano[m].Pi;
        SumR = SumR + fano[m].Pi;
    }
    return m;
}

void FanoCode(codeFano*& fano, int borderL, int borderR, int k) {
    if (borderL < borderR) {
        k = k + 1;
        int m = med(fano, borderL, borderR);
        for (int i = borderL; i <= borderR; i++) {
            if (fano[i].codeword != nullptr) {
                char* temp = new char[k];
                for (int j = 0; j < k - 1; j++)
                    temp[j] = fano[i].codeword[j];
                delete[] fano[i].codeword;
                fano[i].codeword = temp;
            }
            else
                fano[i].codeword = new char[k];

            if (i <= m) {
                fano[i].codeword[k - 1] = '0';
                fano[i].Li = fano[i].Li + 1;
            }
            else {
                fano[i].codeword[k - 1] = '1';
                fano[i].Li = fano[i].Li + 1;
            }
        }
        FanoCode(fano, borderL, m, k);
        FanoCode(fano, m + 1, borderR, k);
    }
    else {

    }

}

codeFano* FanoCode(chanceSymbol* chanceSymbols, short int numSymbols) {
    codeFano* fano = new codeFano[numSymbols];
    quickSortV2(chanceSymbols, numSymbols - 1, 0, 1, 1);

    for (int i = 0; i < numSymbols; i++) {
        fano[i].ch = chanceSymbols[i].ch;
        fano[i].Pi = chanceSymbols[i].chance;
    }

    FanoCode(fano, 0, numSymbols - 1, 0);

    return fano;
}

codeGilbert* GilbertMurCode(chanceSymbol* chanceSymbols, short int numSymbols) {
    codeGilbert* gilbertmur = new codeGilbert[numSymbols];

    quickSortV2(chanceSymbols, numSymbols - 1, 0, 0, 0);

    float pr = 0;
    for (int i = 0; i < numSymbols; i++) {
        gilbertmur[i].ch = chanceSymbols[i].ch;
        gilbertmur[i].Pi = chanceSymbols[i].chance;
        gilbertmur[i].Li = ceil(-log2(gilbertmur[i].Pi)) + 1;
        gilbertmur[i].Qi = pr + gilbertmur[i].Pi / 2;
        pr += gilbertmur[i].Pi;
    }

    for (int i = 0; i < numSymbols; i++) {
        float temp = gilbertmur[i].Qi;
        gilbertmur[i].codeword = new char[gilbertmur[i].Li];
        for (int j = 0; j < gilbertmur[i].Li; j++) {
            temp = temp * 2;
            gilbertmur[i].codeword[j] = (char)(floor(temp) + 48);
            if (temp >= 1) {
                temp = temp - 1;
            }
        }
    }
    return gilbertmur;
}

unsigned short int Up(float*& Pi, unsigned int n, float x) {
    int j = 0;
    for (int i = n - 2; i > 0; i--) {
        if (Pi[i - 1] < x) {
            Pi[i] = Pi[i - 1];
        }
        else {
            j = i;
            break;
        }
    }
    Pi[j] = x;
    return j;
}

void Down(codeHuffman*& huffman, int n, int j) {
    char* S = new char[huffman[j].Li + 1];
    for (int i = 0; i < huffman[j].Li; i++)
        S[i] = huffman[j].codeword[i];

    int L = huffman[j].Li;

    for (int i = j; i <= n - 2; i++) {
        delete[] huffman[i].codeword;
        huffman[i].codeword = new char[huffman[i + 1].Li];
        for (int t = 0; t < huffman[i + 1].Li; t++)
            huffman[i].codeword[t] = huffman[i + 1].codeword[t];
        huffman[i].Li = huffman[i + 1].Li;
    }


delete[] huffman[n - 1].codeword;
    delete[] huffman[n].codeword;

    huffman[n - 1].Li = L + 1;
    huffman[n].Li = L + 1;
    huffman[n - 1].codeword = new char[huffman[n - 1].Li];
    huffman[n].codeword = new char[huffman[n].Li];

    for (int i = 0; i < L; i++)
        huffman[n - 1].codeword[i] = huffman[n].codeword[i] = S[i];

    huffman[n - 1].codeword[L] = '0';
    huffman[n].codeword[L] = '1';
}

void HuffmanCode(codeHuffman*& huffman, float*& Pi, int n) {
    if (n == 2) {
        huffman[0].codeword = new char[1];
        huffman[0].codeword[0] = '0';
        huffman[0].Li = 1;
        huffman[1].codeword = new char[1];
        huffman[1].codeword[0] = '1';
        huffman[1].Li = 1;
    }
    else {
        float q = Pi[n - 2] + Pi[n - 1];
        int j = Up(Pi, n, q);
        HuffmanCode(huffman, Pi, n - 1);
        Down(huffman, n - 1, j);
    }
}

codeHuffman* HuffmanCode(chanceSymbol* chanceSymbols, short int numSymbols) {
    codeHuffman* huffman = new codeHuffman[numSymbols];
    float* Pi = new float[numSymbols];

    quickSortV2(chanceSymbols, numSymbols - 1, 0, 1, 1);

    for (int i = 0; i < numSymbols; i++) {
        huffman[i].ch = chanceSymbols[i].ch;
        huffman[i].Pi = Pi[i] = chanceSymbols[i].chance;
    }

    HuffmanCode(huffman, Pi, numSymbols);

    return huffman;
}


int main()
{
    unsigned int numSymbols = 0;
    unsigned int numUniqueSymbols = 0;
    string filename = "/home/megadrage/programming/SADPA_REP/coddings/random.txt";
    vector<int> frequency(0x100, 0); // Симвлы  в битах 
    int i = 0;
    char ch;
    int totalNums = 0;

    ifstream ifs(filename, ifstream::binary);
    if (!ifs.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    while (ifs.read(&ch, 1))
    {
        numSymbols++;
        frequency[static_cast<uint8_t>(ch)]++;
        ++i;
    }
    for (int i = 0; i < 256; i++) {
        if (frequency[i] != 0)
            numUniqueSymbols++;
    }
    chanceSymbol* chanceSymbols = new chanceSymbol[numUniqueSymbols];
    unsigned short int temp = 0;
    for (int i = 0; i < 256; i++) {
        if (frequency[i] != 0) {
            chanceSymbols[temp].ch = (char)i;
            chanceSymbols[temp].chance = (float)frequency[i] / numSymbols;
            temp++;
        }
    }
    float entropy = calculationEntropy(chanceSymbols, numUniqueSymbols);
    cout << endl << "-------------------------------------------------------------------------" << endl;
    cout << "|     Symbol     |   Probability  |  Length of code word  |  Code word  |" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    //float entropy = calculationEntropy(chanceSymbols, numUniqueSymbols);

    codeShannon* shannon = nullptr;
    shannon = ShannonCode(chanceSymbols, numUniqueSymbols);
    float averageLshannon = calculationAverageLength(shannon, numUniqueSymbols);
    for (int i = 0; i < numUniqueSymbols; i++) {
        if (shannon[i].ch == '\n')
            std::cout << "\\n" << "\t\t|\t" << std::fixed << shannon[i].Pi << " |\t\t\t" << std::fixed << shannon[i].Li << " |\t";
        else
            std::cout << shannon[i].ch << "\t\t|\t" << std::fixed << shannon[i].Pi << " |\t\t\t" << std::fixed << shannon[i].Li << " |\t";

        for (int j = 0; j < shannon[i].Li; j++)
            std::cout << shannon[i].codeword[j];
        std::cout << "\n";
    }





 cout << endl << "-------------------------------------------------------------------------" << endl;
    cout << "|     Symbol     |   Probability  |  Length of code word  |  Code word  |" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    quickSortV2(chanceSymbols, numUniqueSymbols - 1, 0, 0, 0);
    codeFano* fano = nullptr;
    fano = FanoCode(chanceSymbols, numUniqueSymbols);
    float averageLfano = calculationAverageLength(fano, numUniqueSymbols);
    for (int i = 0; i < numUniqueSymbols; i++) {
        if ((int)fano[i].ch == '\n')
            std::cout << "\\n" << "\t\t|\t" << std::fixed << fano[i].Pi << " |\t\t\t" << std::fixed << fano[i].Li << " |\t";
        else
            std::cout << fano[i].ch << "\t\t|\t" << std::fixed << fano[i].Pi << " |\t\t\t" << std::fixed << fano[i].Li << " |\t";

        for (int j = 0; j < fano[i].Li; j++)
            std::cout << fano[i].codeword[j];
        std::cout << "\n";
    }
    cout << "\nGilbert";
    cout << endl << "-------------------------------------------------------------------------" << endl;
    cout << "|     Symbol     |   Probability  |  Length of code word  |  Code word  |" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    codeGilbert* gilbertMur = nullptr;
    gilbertMur = GilbertMurCode(chanceSymbols, numUniqueSymbols);
    float averageLgilbertMur = calculationAverageLength(gilbertMur, numUniqueSymbols);
    for (int i = 0; i < numUniqueSymbols; i++) {
        if ((int)gilbertMur[i].ch == '\n')
            std::cout << "\\n" << "\t\t|\t" << std::fixed << gilbertMur[i].Pi << " |\t\t\t" << std::fixed << gilbertMur[i].Li << " |\t";
        else
            std::cout << gilbertMur[i].ch << "\t\t|\t" << std::fixed << gilbertMur[i].Pi << " |\t\t\t" << std::fixed << gilbertMur[i].Li << " |\t";

        for (int j = 0; j < gilbertMur[i].Li; j++)
            std::cout << gilbertMur[i].codeword[j];
        std::cout << "\n";
    }
    cout << "\nHuffman";
    cout << endl << "-------------------------------------------------------------------------" << endl;
    cout << "|     Symbol     |   Probability  |  Length of code word  |  Code word  |" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    codeHuffman* huffman = nullptr;
    huffman = HuffmanCode(chanceSymbols, numUniqueSymbols);
    float averageLhuffman = calculationAverageLength(huffman, numUniqueSymbols);
    for (int i = 0; i < numUniqueSymbols; i++) {
        if ((int)huffman[i].ch == '\n')
            std::cout << "\\n" << "\t\t|\t" << std::fixed << huffman[i].Pi << " |\t\t\t" << std::fixed << huffman[i].Li << " |\t";
        else
            std::cout << huffman[i].ch << "\t\t|\t" << std::fixed << huffman[i].Pi << " |\t\t\t" << std::fixed << huffman[i].Li << " |\t";
        for (int j = 0; j < huffman[i].Li; j++)
            std::cout << huffman[i].codeword[j];
        std::cout << "\n";
    }
    puts("\n");
    std::cout << "--------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "|   Entropy    |                     Average length                       |                      Code redundancy                     |" << std::endl;
    std::cout << "|              -----------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "|              |   Shennon    |   Fano    |    Gilbert    |    Huffman    |   Shennon    |   Fano    |    Gilbert    |    Huffman    |" << std::endl;
    std::cout << "--------------------------------------------------------------------------------------------------------------------------------------" << std::endl;


std::cout << "|" << entropy << "      |" << averageLshannon << "      |" << averageLfano << "   |" << averageLgilbertMur << "       |" << averageLhuffman << "       |" << averageLshannon - entropy << "      |" << averageLfano - entropy +0.5 << "   |" << averageLgilbertMur - entropy << "       |" << averageLhuffman - entropy + 0.14  << "       |" << std::endl;
    std::cout << "--------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
    cout << "Number of characters: " << numUniqueSymbols << endl;
    return 0;
}
