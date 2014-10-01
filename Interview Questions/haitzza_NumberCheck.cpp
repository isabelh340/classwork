#include <cmath>
#include <vector>
#include <omp.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <iterator>

class NumberCheck {
    friend std::ostream &operator<<(std::ostream& os, const NumberCheck& nc);
public:
    NumberCheck(int min, int max);
    void calculate();
    bool isPrime(const int num) const;
    bool checkFactor(const std::vector<int>& primeFactors,
                     const int curr, const int num) const;
    bool isPrimeFactorable(const int num) const;
    bool isPalindromic(const int num) const;
    bool isFactorial(const int num) const; 
private:
    std::vector<int> numbers;
    std::vector<bool> results;
};

NumberCheck::NumberCheck(int min, int max) {
    numbers = std::vector<int>(max-min, 0);
    std::iota(std::begin(numbers), std::end(numbers), min);
}

bool NumberCheck::isPrime(const int num) const {
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

std::ostream &operator<<(std::ostream& os, const NumberCheck& nc) {
    for (size_t i = 0; i < nc.numbers.size(); i++) {
        os << nc.numbers[i] << ": " << (nc.results[i*4] == 1 ? " is " : " not ") << " prime, "
                  << (nc.results[i*4+1] == 1 ? " is " : " not ") << " factorable, "
                  << (nc.results[i*4+2] == 1 ? " is " : " not ") << " factorial, "
                  << (nc.results[i*4+3] == 1 ? " is " : " not ") << " palindrome\n";
    }
    return os;
}

bool NumberCheck::checkFactor(const std::vector<int>& primeFactors, const int curr,
                 const int num) const {
    for (size_t i = 0; i < primeFactors.size(); i++) {
        return (primeFactors[i]*curr) == num;
    }
    return false;
}

bool NumberCheck::isPrimeFactorable(const int num) const {    
    std::vector<int> primeFactors;
    int n = num, x = 2;

    while (x * x <= n) {
        if ((n % x) == 0) {
            if (checkFactor(primeFactors, x, num)) {
                return true;
            }
            primeFactors.push_back(x);
            n/=x;
        } else {
            x++;
        }
    }

    return ((n>1) ? checkFactor(primeFactors, n, num) : false);
}

bool NumberCheck::isPalindromic(const int num) const {
    if (num < 10) {
        return false;
    }
    // modifying the number
    int n = num;
    // build the number in reverse order
    int rev = 0;

    while (n > 0) {
        // get the last digit of the number
        int digit = n % 10;
        // start building the reverse #
        rev = rev * 10 + digit;
        // remove the last digit
        n /= 10;
    }

    return (rev == num);
}

bool NumberCheck::isFactorial(const int num) const {
    // starting at 1
    // keep track of the current number through
    int n = 1;
    int curr = 1;
    
    while(true) {
        // actually cacluate factorial from
        // bottom up 
        n = (n * (curr++));
        if (n > num) { // if the factorial val > num, return false
            return false;
        } else if (n == num) {
            return true;
        }
    }
}

void NumberCheck::calculate() {
    results = std::vector<bool>(numbers.size()*4, false);
    int index;
#pragma omp parallel
    {
#pragma omp for schedule(dynamic)
        for (size_t i = 0; i < numbers.size(); i++) {
            index = i * 4;
            results[index]   = isPrime(numbers[i]);
            results[index+3] = isPalindromic(numbers[i]);
            results[index+2] = isFactorial(numbers[i]);
            // if it is a prime then it only has two factors... 
            results[index+1] = (results[index] == false ?
                                isPrimeFactorable(numbers[i]) : false);
        }
    }
}

int main(int argc, char** argv) {
    NumberCheck nc(atoi(argv[1]), atoi(argv[2])+1);
    nc.calculate();
    std::cout << nc;
    
    return 0; 
}
