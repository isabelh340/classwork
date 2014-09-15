// Copyright 2014 Zach Haitz

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>
#include <regex>
#include <math.h>
#include <queue>
#include <map>

bool myIsPunct(char& c) {
    if (c == '-') {
        return false;
    }
    return ispunct(c);
}

bool cleanAndCheckString(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::string res;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(res), myIsPunct);
    str = res;
    return (str.substr(0,4) == "http" ||
            std::any_of(str.begin(), str.end(), ::isdigit)); 
}

void addToMap(std::unordered_map<std::string, int>& currentMap,
              std::string& stringToAdd) {
    if (cleanAndCheckString(stringToAdd)) {
        return;
    }
    
    if (currentMap.find(stringToAdd) != currentMap.end()) {
        currentMap[stringToAdd]++;
    } else {
        currentMap[stringToAdd] = 1;
    }
}

void tfid(const std::string& searchFile,
          std::unordered_map<std::string, int>& corpusMap,
          const std::string& currentCorpusFile,
          std::unordered_map<std::string, int>& documentMap) {
    std::unordered_map<std::string, int> currentMap;
    std::ifstream currentCorpus(currentCorpusFile);
    std::istream_iterator<std::string> cc_it(currentCorpus), eof;
    std::for_each(cc_it, eof, [&currentMap](std::string a) {
            addToMap(currentMap, a);
        }); 

    for (auto kv : currentMap) {
        bool found = corpusMap.find(kv.first) != corpusMap.end();
        corpusMap[kv.first] = found ? corpusMap[kv.first] + kv.second : kv.second;
    }
    if (currentCorpusFile == searchFile && documentMap.size() == 0) {
        for (auto kv : currentMap) {
            bool found = documentMap.find(kv.first) != documentMap.end();
            documentMap[kv.first] = found ? documentMap[kv.first] + kv.second : kv.second;
        }
    }
}

struct tfidfPair {
    std::string word;
    double value;
    tfidfPair(std::string word, double value) : word(word), value(value) {};

};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        return 1;
    }
    std::string a(argv[2]);
    std::ifstream corpus(argv[1]);    std::istream_iterator<std::string> corpus_it(corpus), eof;
    std::vector<std::string> fileList(corpus_it, eof);
    std::unordered_map<std::string, int> corpusMap, documentMap;
    for (uint i = 0; i < fileList.size(); i++) {
        tfid(a, corpusMap, fileList[i], documentMap);
    }
    std::vector<tfidfPair> result(documentMap.size(), tfidfPair("",0));
    int count = 0;
    for (auto kv : documentMap) {
        double x = (kv.second *
                    (log((double)fileList.size() /
                         corpusMap.at(kv.first)) / log(10.0)));
        if (x != 0.0) {
            result[count++] = tfidfPair(kv.first, x);
        }
    }
    std::sort(result.begin(), result.end(), [](tfidfPair a, tfidfPair b) {
            return a.value > b.value;
        });
    std::for_each(result.begin(), result.begin() + 10, [](tfidfPair a) {
            std::cout << a.word << " " << a.value << std::endl;
        });
    return 0;
}
