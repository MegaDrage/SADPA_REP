#include "generator.hpp"
#include <ctime>
int main() {
    srand(time(NULL));
    generate_random_ru_file("random.txt");
    return 0;
}