#include <iostream>
#include <string>
#include <vector>

// Short cut to list of strings
typedef std::vector<std::string*> StrList;

// Uncomment the following line for penultimate part of the exercise
#define EX_PART2

// Implement the following method to print each entry in the given
// list.
void print(const StrList* const list) {
    for (uint i = 0; i < list->size(); i++) {
        std::cout << "list[" << i << ", " << list->at(i) << "]: "
                  << (list->at(i) == 0 ? "0" : *(list->at(i))) << std::endl;
    }
}

// Generates numbers and stores them as strings.
void genNum(StrList* list, int count) {
    for (int i = 0; (i < count); i++) {
        std::string* word = new std::string(std::to_string(i));
        list->push_back(word);
    }
}

// Methd to free up memory (if any) allocated in getNum method
void freeList(StrList* list) {
    int size = list->size();
    for (int i = 0; i < size; i++) {
        delete list->at(i);
    }
}

//----------------------------------------------------------
//            DO NOT MODIFY CODE BELOW THIS LINE
//----------------------------------------------------------

int main(int argc, char *argv[]) {
    std::cout << "Creating and printing fixed list of entries:\n";
    std::string words[] = {"one", "two", "three"};
    StrList l1 = {words, words + 1, NULL, words + 2, NULL};
    print(&l1);

#ifdef EX_PART2
    std::cout << "Generating and printing list of entries:\n";    
    // Now call generate numbers and print them.
    StrList l2;
    genNum(&l2, std::stoi(argv[1]));
    print(&l2);
    freeList(&l2);
#endif
    
    return 0;
}

// End of source code
