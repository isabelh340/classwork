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

typedef std::unordered_map<std::string, int> strIntMap;
typedef std::pair<std::string, int> strIntPair;

/*
  Returns true if a given character is a punctuation except for hypens
*/
bool myIsPunct(const char& c) {
    return (c == '-' ? false : ispunct(c));
}

/*
  Given a string, will strip punctuation from string and ignore words with
  digits or starting with http or are just hypens or are 0
  @param str - the string to clean
  @param converLower - whether or not we want to lower case the string
*/
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

/*
  Adds a string to a map keeping track of the amount of times it has been seen
  @param currentMap 
  @param stringToAdd
*/  
void addToMap(strIntMap& currentMap, std::string& stringToAdd) {
    if (cleanAndCheckString(stringToAdd, true)) {
        return;
    }

    currentMap[stringToAdd] = (currentMap.find(stringToAdd) != currentMap.end()
                               ? currentMap[stringToAdd] + 1 : 1);
}

/*
  Counts the words in the given file. Stores in the given hashmap
  @param corpusMap - the map for the word count
  @param currentCorpusFile - the current file we are examining
*/
void wordCount(strIntMap& corpusMap,
               const std::string& currentCorpusFile) {
    strIntMap currMap;
    std::ifstream currentCorpus(currentCorpusFile);
    std::istream_iterator<std::string> cc_it(currentCorpus), eof;
    // iterate through the words in the current file and add them to currmap
    std::for_each(cc_it, eof, [&currMap](std::string a) {
            addToMap(currMap, a);
        });

    // take the current document map and add it to the total for the corpus
    std::for_each(currMap.begin(), currMap.end(), [&corpusMap](strIntPair a) {
            corpusMap[a.first] = corpusMap.find(a.first) != corpusMap.end() ?
                corpusMap[a.first] + a.second : a.second;
        });
}

// a simple datastructure to store a word and its tfidf value
struct tfidfPair {
    std::string word;
    double value;
    tfidfPair(std::string word, double value) : word(word), value(value) {}

    // override this for use of priority queue
    bool operator<(const tfidfPair &o) const {
        return this->value > o.value;
    }
};

/*
  Counts the significant words per line in the given search file
*/
void countSigWords(const std::string searchFile,
                   const std::vector<tfidfPair> result) {
    std::ifstream search(searchFile);
    std::string line, currWord;
    int lineNumber = 1; // start at one, because logic
    // get line by line
    while (std::getline(search, line)) {
        std::istringstream ss(line);
        // store into set because dups ain't no thang
        std::set<std::string> wordSet;
        // store cleaned versions of words into set
        while (ss >> currWord != NULL) {
            if (!cleanAndCheckString(currWord, false)) {
                wordSet.insert(currWord);
            }
        }

        // get the count for the words in result that are also in wordset
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

// the twfid calculation
double twfid(double docCount, double fileCount, double corpCount) {
    return docCount * (log(fileCount / corpCount) / log(10.0));
}


// helper method to insert into a priority queue, keeping the size
// at size because why store stuff we don't care about
void insertToPriorityQueue(std::priority_queue<tfidfPair>& q,
                           const tfidfPair& toInsert, uint size, int value) {
    // storing the tfidf by reverse sorted order, so if we see something
    // that is greater than the lowest in q, we pop that bad boy off and
    // insert the new one
    if (q.size() == size && value > q.top().value) {
        q.pop();
    } else if (q.size() < size) {
        q.push(toInsert);
    }
}

// gets the topN significant words and stores them in a priority queue
void getTopN(const uint topN, const int fileCount,
             std::priority_queue<tfidfPair>& object,
             const strIntMap& documentMap, const strIntMap& corpusMap) {
    std::for_each(documentMap.begin(), documentMap.end(), [&](strIntPair a) {
            double x = twfid(a.second, fileCount, corpusMap.at(a.first));
            insertToPriorityQueue(object, tfidfPair(a.first, a.second), topN, x);
        });
}

// prints the values in the priority queue in reverse order
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

// method to load data for corpus and search files
void loadCorpusAndSearchFiles(strIntMap& corpMap, strIntMap& docMap,
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

    strIntMap corpusMap, documentMap;
    std::cout << "Loading corpus using files listed in " << argv[1]
              << std::endl;
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
