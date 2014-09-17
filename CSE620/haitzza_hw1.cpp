// Copyright 2014 Zach Haitz

#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>
#include <cmath>
#include <queue>
#include <map>

bool myIsPunct(const char& c) {
    return (c == '-' ? false : ispunct(c));
}

bool cleanAndCheckString(std::string& str, const bool convertLower) {
    if (convertLower) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }
    std::string res;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(res),
                        myIsPunct);
    str = res;
    return (str.substr(0, 4) == "http" ||
        std::any_of(str.begin(), str.end(), ::isdigit) ||
            str.size() == 0 || str == "-");
}

void addToMap(std::unordered_map<std::string, int>& currentMap,
              std::string& stringToAdd) {
    if (cleanAndCheckString(stringToAdd, true)) {
        return;
    }
    if (currentMap.find(stringToAdd) != currentMap.end()) {
        currentMap[stringToAdd]++;
    } else {
        currentMap[stringToAdd] = 1;
    }
}

void wordCount(std::unordered_map<std::string, int>& corpusMap,
          const std::string& currentCorpusFile) {
    std::unordered_map<std::string, int> currentMap;
    std::ifstream currentCorpus(currentCorpusFile);
    std::istream_iterator<std::string> cc_it(currentCorpus), eof;
    std::for_each(cc_it, eof, [&currentMap](std::string a) {
            addToMap(currentMap, a);
        });

    for (auto kv : currentMap) {
        bool found = corpusMap.find(kv.first) != corpusMap.end();
        corpusMap[kv.first] = found ?
            corpusMap[kv.first] + kv.second : kv.second;
    }
}

struct tfidfPair {
    std::string word;
    double value;
    tfidfPair(std::string word, double value) : word(word), value(value) {}

    bool operator<(const tfidfPair &o) const {
        return this->value > o.value;
    }
};

void countSigWords(const std::string searchFile,
                   const std::vector<tfidfPair> result) {
    std::ifstream search(searchFile);
    std::string line, currWord;
    int lineNumber = 1;
    while (std::getline(search, line)) {
        std::istringstream ss(line);
        std::set<std::string> wordSet;
        while (ss >> currWord != NULL) {
            if (!cleanAndCheckString(currWord, false)) {
                wordSet.insert(currWord);
            }
        }
        
        int count = std::count_if(result.begin(), result.end(),
                          [&wordSet](tfidfPair a) {
                              return (wordSet.find(a.word) != wordSet.end());
                          });
        if (count > 1) {
            std::cout << lineNumber << "[" << count << "]\t" << line
                      << std::endl;
        }
        lineNumber++;
    }
}

double twfid(double docCount, double fileCount, double corpCount) {
    return docCount * (log(fileCount / corpCount) / log(10.0));
}

void getTopN(const uint topN, const int fileCount, std::priority_queue<tfidfPair>& object,
             const std::unordered_map<std::string, int>& documentMap,
             const std::unordered_map<std::string, int>& corpusMap) {
    for (auto kv : documentMap) {
        double x = twfid(kv.second, fileCount, corpusMap.at(kv.first));
        if (object.size() == topN && x > object.top().value) {
            object.pop();
            object.push(tfidfPair(kv.first, x));
        } else if (object.size() < topN) {
            object.push(tfidfPair(kv.first, x));
        }
    }
}

void sortAndPrintTopN(std::vector<tfidfPair>& vec,
                      std::priority_queue<tfidfPair>& object) {
    for (uint i = 0; i < vec.size(); i++) {
        vec[i] = object.top();
        object.pop();
    }

    std::for_each(vec.rbegin(), vec.rend(), [](tfidfPair a) {
            std::cout << a.word << " " << a.value << std::endl;
        });
}

void loadCorpusAndSearchFiles(std::unordered_map<std::string, int>& corpMap,
                              std::unordered_map<std::string, int>& docMap,
                              std::string searchFile,
                              std::vector<std::string> fileList) {
    std::for_each(fileList.begin(), fileList.end(), [&](std::string currFile) {
            wordCount(corpMap, currFile);
        });
    wordCount(docMap, searchFile);
}

int main(int argc, char* argv[]) {
    std::string searchFile(argv[2]);
    uint topN(std::stoi(argv[3]));
    std::ifstream corpus(argv[1]);
    std::istream_iterator<std::string> corpus_it(corpus), eof;
    std::vector<std::string> fileList(corpus_it, eof);

    std::unordered_map<std::string, int> corpusMap, documentMap;
    std::cout << "Loading corpus using files listed in " << argv[1] << std::endl;
    loadCorpusAndSearchFiles(corpusMap, documentMap, searchFile, fileList);
    
    std::cout << "Loaded corpus of " << corpusMap.size() << " words from "
              << fileList.size() << " file(s)" << std::endl
              << "------[ Starting analysis ]------" << std::endl << "Top "
              << topN << " significant words..." << std::endl;
   
    std::priority_queue<tfidfPair> object;
    std::vector<tfidfPair> result(topN, tfidfPair("", 0));
    getTopN(topN, fileList.size(), object, documentMap, corpusMap);
    sortAndPrintTopN(result, object);
    
    std::cout << "lines with more than one sig word " << std::endl;
    countSigWords(searchFile, result);
    
    return 0;
}
