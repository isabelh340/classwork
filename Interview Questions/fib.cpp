#include <iostream>
#include <vector>

int fibCalc(std::vector<int>& vec, int sum, int count) {
    if (vec[0] >= 4000000) {
	return sum;
    }
    int next = vec[0] + vec[1];
    if ((next % 2) == 0) {
	sum += next;
    }
    vec[count] = next;
    return fibCalc(vec, sum, (count == 0 ? 1 : 0));
}

int fib() {
    std::vector<int> vec = {1,2};
    return fibCalc(vec, 2, 0);
}

int main() {
    std::cout << fib() << std::endl;
    return 0;
}
