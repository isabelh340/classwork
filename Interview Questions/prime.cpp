#include <iostream>
#include <cmath>

bool isPrime(long long n) {
    for (long long i = 2; i < sqrt(n) + 1; i++) {
	if ((n%i)==0) {
	    return false;
	}
    }

    return true;
}

int main() {
    long long num = 600851475143L;
    for (long long i = sqrt(num)+1; i >= 1; i--) {
	if ((num%i) == 0 && isPrime(i)) {
	    std::cout << i << std::endl;
	    break;
	}
    }
    return 0;
}
