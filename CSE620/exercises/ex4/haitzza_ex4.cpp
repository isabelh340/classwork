#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <set>

int main(int argc, char* argv[]) {
    std::ifstream dataFile(argv[1]);
    dataFile >> std::noskipws;
    std::istream_iterator<char> fileIt(dataFile), eof;
    std::string res(fileIt, eof);
 
    for (int i = 2; i < argc; i++) {
        auto tx = [&argv, &i](char c) {
            return (tolower(c) == argv[i][0] ?
                    (isupper(c) ? tolower(c) : toupper(c)) : c);
        };
        std::transform(res.begin(), res.end(), res.begin(), tx);
    }
    std::cout << res << std::endl;
    return 0;
}
