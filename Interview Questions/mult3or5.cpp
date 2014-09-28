#include <iostream>

int main() {
    int sum = 0;
    const int THREE = 3, FIVE = 5;
    const int LIMIT = 1000;
    for (int i = 0; i < LIMIT; i++) {
	if (i % THREE == 0 || i % FIVE == 0) {
	    sum += i;
	}
    }
    std::cout << sum << std::endl;
}
