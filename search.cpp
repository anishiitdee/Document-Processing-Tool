// Do NOT add any other includes
#include "search.h"
string toLowerCase(std::string& str) {
    string result = str;
    for (char& c : str) {
        c = tolower(c);
    }
    return result;
}
SearchEngine::SearchEngine(){
    // Implement your function here  
}

SearchEngine::~SearchEngine(){
    // Implement your function here  
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
     sentences.push_back({{book_code, page, paragraph, sentence_no}, sentence});
}

Node* SearchEngine::search(string pattern, int& n_matches){
    int m = pattern.length();
    Node* head = nullptr;  
    n_matches = 0; 
    pattern = toLowerCase(pattern);
    int p = 0;
    int h = 1;
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }
    for (int i = 0; i < m; i++) {
        pattern[i] = tolower(pattern[i]);
        p = (d * p + pattern[i]) % q;
    }

    for (size_t i = 0; i < sentences.size(); i++) {
        int n = sentences[i].second.length();
        int t = 0;
        for (int j = 0; j < m; j++) {
            sentences[i].second[j] = tolower(sentences[i].second[j]);
            t = (d * t + sentences[i].second[j]) % q;
        }
        for (int j = 0; j <= n - m; j++) {
            if (p == t) {
                bool match = true;
                for (int k = 0; k < m; k++) {
                    if (pattern[k] != sentences[i].second[j + k]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    
                     Node* newNode = new Node(sentences[i].first[0], sentences[i].first[1],
                                             sentences[i].first[2], sentences[i].first[3], j); 
                    newNode->right = head;
                    head = newNode;
                    n_matches++;
                }
            }
            if (j < n - m) {
                t = (d * (t - sentences[i].second[j] * h) + sentences[i].second[j + m]) % q;
                if (t < 0) {
                    t = (t + q);
                }
            }
        }
    }
    return head;
}

// int main() {
//     SearchEngine searchEngine;

//     // Insert sentences
//     searchEngine.insert_sentence(1, 1, 1, 1, "This02 is a. sample sentence for testing.");
//     searchEngine.insert_sentence(1, 1, 1, 2, "Another sentence for testing.");

//     // Search for a pattern
//     std::string pattern = "this02 is a. ";
//     int n_matches = 0;
//     Node* result = searchEngine.search(pattern, n_matches);
//     // Print the results
//     std::cout << "Pattern: " << pattern << std::endl;
//     std::cout << "Number of Matches: " << n_matches << std::endl;

//     // Iterate through the linked list and print the matching positions
//     Node* current = result;
//     while (current != nullptr) {
//         std::cout << "Match at Offset: " << current->offset << std::endl;
//         current = current->right;
//     }
//     // Cleanup: Free the memory used by the linked list
//     current = result;
//     while (current != nullptr) {
//         Node* temp = current;
//         current = current->right;
//         delete temp;
//     }

//     return 0;
// }