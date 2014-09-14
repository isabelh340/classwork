// Copyright 2014 Zach Haitz

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>

void addToMap(std::unordered_map<std::string, int>& currentMap,
              const std::string stringToAdd) {
    if (currentMap.find(stringToAdd) != currentMap.end()) {
        currentMap[stringToAdd]++;
    } else {
        currentMap[stringToAdd] = 1;
    }
}

void tfid(const std::string& searchFile,
          std::unordered_map<std::string, int>& corpusMap,
          const std::string& currentCorpusFile) {
    std::unordered_map<std::string, int> currentMap;
    std::ifstream currentCorpus(currentCorpusFile);
    std::istream_iterator<std::string> cc_it(currentCorpus), eof;
    std::for_each(cc_it, eof, [&currentMap](std::string a) {
            addToMap(currentMap, a);
        }); 
    for (auto kv : currentMap) {
        std::cout << kv.first << " " << kv.second << std::endl;
        bool found = corpusMap.find(kv.first) != corpusMap.end();
        corpusMap[kv.first] = found ? corpusMap[kv.first] + kv.second : kv.second;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        return 1;
    }
    std::string a(argv[2]);
    std::ifstream corpus(argv[1]);
    std::istream_iterator<std::string> corpus_it(corpus), eof;
    std::vector<std::string> fileList(corpus_it, eof);
    std::unordered_map<std::string, int> corpusMap;
    for (uint i = 0; i < fileList.size(); i++) {
        tfid(a, corpusMap, fileList[i]);
    }
    
    
    return 0;
}
