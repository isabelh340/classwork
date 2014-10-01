#include <iostream>
#include <cmath>

using natural = unsigned long;
bool isPrime(natural n) {
    for (natural i = 2; i < sqrt(n) + 1; i++) {
	if (fmod(n,i) == 0) {
	    return false;
	}
    }
    return true;
}

int main() {
    natural num = 600851475143L;
    for (natural i = sqrt(num)+1; i >= 1; i--) {
	if (fmod(num,i) == 0 && isPrime(i)) {
	    std::cout << i << std::endl;
	    break;
	}
    }
    return 0;
}
