#include <functional> 
#include <iostream>

double addSub(double x, double y, std::function<double(double l, double r)> op) {
    return op(x,y);
}

int main() {
    std::cout << addSub(2.4,56.0,std::plus<double>())
              << std::endl << addSub(5.2, 1.2, std::minus<double>());
    return 0;
}
