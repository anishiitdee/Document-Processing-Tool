// Do NOT add any other includes

#include "dict.h"

const double Dict::LOAD_FACTOR_THRESHOLD = 0.7;
unsigned long Dict::hashFunction(const string& word) {
    unsigned long hash = 5381;
    for (char ch : word) {
        hash = ((hash << 5) + hash) + ch; // hash * 33 + ch
    }
    return hash % currentTableSize;
}
string toLowerCase(std::string& str) {
    string result = str;
    for (char& c : str) {
        c = tolower(c);
    }
    return result;
}
void Dict::resizeTable() {
    int newTableSize = (currentTableSize * 2)%(numeric_limits<int>::max());
    vector<WordNode*> newHashTable(newTableSize, nullptr);

    for (WordNode* node : hashTable) {
        while (node != nullptr) {
            WordNode* temp = node;
            node = node->next;

            int newIndex = hashFunction(temp->word);
            temp->next = newHashTable[newIndex];
            newHashTable[newIndex] = temp;
        }
    }

    hashTable = move(newHashTable);
    currentTableSize = newTableSize;
}
Dict::Dict() : currentTableSize(INITIAL_TABLE_SIZE) {
    hashTable.resize(currentTableSize, nullptr);
}

Dict::~Dict(){
    // Implement your function here   
    for (WordNode* node : hashTable) {
        while (node != nullptr) {
            WordNode* temp = node;
            node = node->next;
            delete temp;
        }
    }
    
}
int Dict::get_word_count(string word) {
    word = toLowerCase(word);

    int index = hashFunction(word);

    WordNode* current = hashTable[index];
    while (current != nullptr) {
        if (current->word == word) {
            return current->count;
        }
        current = current->next;
    }

    return 0;
}
bool isalnum1(char c) {
    string punctuationMarks = ".,-:! \"'()?—[]˙;@";
    return punctuationMarks.find(c) == string::npos;
}
void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence) {
    string word;
    size_t start = 0;
    size_t end = 0;

    while (end < sentence.length()) {
        while (end < sentence.length() && isalnum1(sentence[end])) {
            ++end;
        }

        word = sentence.substr(start, end - start);
        toLowerCase(word);
        int index = hashFunction(word);
        
        WordNode* current = hashTable[index];
        while (current != nullptr) {
            if (current->word == word) {
                // Word already exists in the hash table
                // Update the necessary information (e.g., count)
                // Assuming WordNode has book_code, page, paragraph, sentence_no attributes
                current->count++;
                current->book_code = book_code;
                current->page = page;
                current->paragraph = paragraph;
                current->sentence_no = sentence_no;
                break;
            }
            current = current->next;
        }

        if (current == nullptr) {
            // Word does not exist in the hash table
            WordNode* newNode = new WordNode(word);
            newNode->count = 1;
            newNode->book_code = book_code;
            newNode->page = page;
            newNode->paragraph = paragraph;
            newNode->sentence_no = sentence_no;

            // Insert the new node at the beginning of the linked list
            newNode->next = hashTable[index];
            hashTable[index] = newNode;
        }

        start = end + 1;
        while (start < sentence.length() && !isalnum1(sentence[start])) {
            ++start;
        }

        end = start;
    }
}

// void merge(vector<pair<string, int>>& arr, int left, int middle, int right) {
//     int n1 = middle - left + 1;
//     int n2 = right - middle;
//     vector<pair<string, int>> leftArr(n1);
//     vector<pair<string, int>> rightArr(n2);

//     for (int i = 0; i < n1; i++) {
//         leftArr[i] = arr[left + i];
//     }
//     for (int j = 0; j < n2; j++) {
//         rightArr[j] = arr[middle + 1 + j];
//     }
//     int i = 0, j = 0, k = left;
//     while (i < n1 && j < n2) {
//         if (leftArr[i].first <= rightArr[j].first) {
//             arr[k] = leftArr[i];
//             i++;
//         } else {
//             arr[k] = rightArr[j];
//             j++;
//         }
//         k++;
//     }
//     while (i < n1) {
//         arr[k] = leftArr[i];
//         i++;
//         k++;
//     }
//     while (j < n2) {
//         arr[k] = rightArr[j];
//         j++;
//         k++;
//     }
// }
// void mergeSort(vector<pair<string, int>>& arr, int left, int right) {
//     if (left < right) {
//         int middle = left + (right - left) / 2;

//         mergeSort(arr, left, middle);
//         mergeSort(arr, middle + 1, right);

//         merge(arr, left, middle, right);
//     }
// }
void Dict::dump_dictionary(string filename) {
    ofstream outfile(filename);
    vector<pair<string, int>> words;

    for (WordNode* node : hashTable) {
        while (node != nullptr) {
            if (node->word != "") {
                words.emplace_back(node->word, node->count);
            }
            node = node->next;
        }
    }
    // mergeSort(words, 0, words.size() - 1);
    for (const auto& wordPair : words) {
        outfile << wordPair.first << ", " << wordPair.second << endl;
    }

    outfile.close();
}



// int main() {
//     // Create a Dict instance
//     Dict myDict;

//     // Insert sentences
//     myDict.insert_sentence(1, 1, 1, 1, "See 12d4 100 son Kevalram 5, and if you fail in getting the pecuniary help and if you have no money, sell your furniture");
//     // myDict.insert_sentence(1, 1, 1, 2, "Another sentence for testing.");

//     // Get word counts
//     std::cout << "Word count for 'sentence': " << myDict.get_word_count("12d4") << std::endl;
//     std::cout << "Word count for 'sample': " << myDict.get_word_count("0000") << std::endl;

//     // Dump the dictionary to a file
//     myDict.dump_dictionary("dictionary.txt");

//     return 0;
// }