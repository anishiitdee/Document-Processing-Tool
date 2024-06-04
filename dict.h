
// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
#include <random>
using namespace std;
/*
class TreeNode{
public:
    string word;
    int book_no;
    int sentence_no;
    int pg;
    int para;
    int frequency;
    bool color;
    TreeNode* left;
    TreeNode* right;
    TreeNode* par;

    TreeNode(string s, int book, int pag, int par, int sentence) {
        word = s;
        book_no=book;
        pg=pag;
        para=par;
        sentence_no=sentence;
        left = NULL;
        right = NULL;
    }

    void recolor() {
        TreeNode* parent = this->par;
        TreeNode* grandpa = this->par->par;
        TreeNode* uncle;
        if (parent == grandpa->left) {
            uncle = grandpa->right;
        }
        else uncle = grandpa->left;
        parent->color = false;
        uncle->color = false;
        grandpa->color = true;
    }

    void llrotation() {
        TreeNode* parent = this->par;
        TreeNode* grandpa = this->par->par;
        TreeNode* uncle;
        if (parent == grandpa->left) {
            uncle = grandpa->right;
        }
        else uncle = grandpa->left;
        if (grandpa->par == NULL) {
            parent->par = NULL;
        }
        else {
            if (grandpa == grandpa->par->left) {
                grandpa->par->left = parent;
                parent->par = grandpa->par;
            }
            else {
                grandpa->par->right = parent;
                parent->par = grandpa->par;
            }
        }
        grandpa->left=parent->right;
        parent->color = false;
        parent->right = grandpa;
        grandpa->par = parent;
        grandpa->color = true;
    }

    void rrrotation() {
        TreeNode* parent = this->par;
        TreeNode* grandpa = this->par->par;
        TreeNode* uncle;
        if (parent == grandpa->left) {
            uncle = grandpa->right;
        }
        else uncle = grandpa->left;
        if (grandpa->par == NULL) {
            parent->par = NULL;
        }
        else {
            if (grandpa == grandpa->par->left) {
                grandpa->par->left = parent;
                parent->par = grandpa->par;
            }
            else {
                grandpa->par->right = parent;
                parent->par = grandpa->par;
            }
        }
        grandpa->right=parent->left;
        parent->color = false;
        parent->left = grandpa;
        grandpa->par = parent;
        grandpa->color = true;
    }

    void lrrotation() {
        TreeNode* parent = this->par;
        TreeNode* grandpa = this->par->par;
        TreeNode* uncle;
        if (parent == grandpa->left) {
            uncle = grandpa->right;
        }
        else uncle = grandpa->left;
        if (grandpa->par == NULL) {
            this->par = NULL;
        }
        else {
            if (grandpa == grandpa->par->left) {
                grandpa->par->left = this;
                this->par = grandpa->par;
            }
            else {
                grandpa->par->right = this;
                this->par = grandpa->par;
            }
        }
        this->color = false;
        this->right = grandpa;
        grandpa->par = this;
        this->left = parent;
        parent->par = this;
        grandpa->color = true;
        parent->color = true;
        parent->right=NULL;
        grandpa->left=NULL;
    }
    void rlrotation() {
        TreeNode* parent = this->par;
        TreeNode* grandpa = this->par->par;
        TreeNode* uncle;
        if (parent == grandpa->left) {
            uncle = grandpa->right;
        }
        else uncle = grandpa->left;
        if (grandpa->par == NULL) {
            this->par = NULL;
        }
        else {
            if (grandpa == grandpa->par->left) {
                grandpa->par->left = this;
                this->par = grandpa->par;
            }
            else {
                grandpa->par->right = this;
                this->par = grandpa->par;
            }
        }
        this->color = false;
        this->left = grandpa;
        grandpa->par = this;
        this->right = parent;
        parent->par = this;
        grandpa->color = true;
        parent->color = true;
        parent->left=NULL;
        grandpa->right=NULL;
    }

    void balance() {
        if (this->par!=NULL && this->par->par!=NULL) {
            TreeNode* parent = this->par;
            TreeNode* grandpa = this->par->par;
            TreeNode* uncle;
            if (parent == grandpa->left) {
                uncle = grandpa->right;
            }
            else uncle = grandpa->left;
            if (!(parent->color) || !(this->color) ) {
                
            }
            if (uncle!=NULL && parent->color == uncle->color)  {
                this->recolor();
                grandpa->balance();
            }
            else if (!(parent->color==false)) {
                bool g1, g2;
                if (grandpa->left == parent) {
                    g1 = true;
                }
                else g1 = false;
                if (parent->left == this) {
                    g2 = true;
                }
                else g2 = false;
                if (g1 && g2) {
                    this->llrotation();
                }
                else if (g1 && !g2) {
                    this->lrrotation();
                }
                else if (!g1 && g2) {
                    this->rlrotation();
                }
                else {
                    this->rrrotation();
                }
            }
        }
        TreeNode* rt=this;
        while(rt->par!=NULL){
            rt=rt->par;
        }
        rt->color = false;
    }
};

class RedBlackTrees {
private:
    int size = 0;
    TreeNode* root = NULL;
public:
    RedBlackTrees() {
        size = 0;
        root = NULL;
    }
    ~RedBlackTrees() {
        root = NULL;
    }
    void insert(int book_code, int page, int paragraph, int sentence_no, string k) {
        if (root == NULL) {
            root = new TreeNode(k, book_code, page, paragraph, sentence_no);
            root->frequency = 1;
            root->color = false;
            root->par = NULL;
            size++;
        }
        else {
            TreeNode* current = root;
            bool done = false;
            while (!done) {
                if (current->word == k) {
                    current->frequency += 1;
                    done = true;
                }
                else if (current->word > k) {
                    if (current->left == NULL) {
                        current->left = new TreeNode(k, book_code, page, paragraph, sentence_no);
                        current->left->color = true;
                        current->left->par = current;
                        current->left->frequency = 1;
                        done = true;
                        current->left->balance();
                        TreeNode* rt=current;
                        while(rt->par!=NULL){
                            rt=rt->par;
                        }
                        root=rt;
                        size++;
                    }
                    else current = current->left;
                }
                else {
                    if (current->right == NULL) {
                        current->right = new TreeNode(k, book_code, page, paragraph, sentence_no);
                        current->right->color = true;
                        current->right->par = current;
                        current->right->frequency = 1;
                        done = true;
                        current->right->balance();
                        TreeNode* rt=current;
                        while(rt->par!=NULL){
                            rt=rt->par;
                        }
                        root=rt;
                        size++;
                    }
                    else current = current->right;
                }
            }
        }
    }
    int search(string k) {
        TreeNode* current = root;
        while (current != NULL) {
            if (k > current->word) {
                current = current->right;
            }
            else if (k < current->word) {
                current = current->left;
            }
            else {
                return current->frequency;
            }
        }
        return 0;
    }
    int get_size() {
        return size;
    }
    TreeNode* get_root() {
        return root;
    }
};

class ListNode {
public:
    string key;
    int count;
    ListNode* below;
    ListNode* up;
    ListNode* next;
    
    ListNode() {
        
        next = NULL;
        below = NULL;
        up = NULL;
    }
    ListNode(string k) {
        key = k;
        count = 1;
        next = NULL;
        below = NULL;
        up = NULL;
    }
};

class SkipList {
private:
    vector <ListNode*> heads;
    int levels = 0;
public:
    SkipList() {
        ListNode* head1 = new ListNode();
        heads.push_back(head1);
        levels = 1;
    }
    void create_new_level(ListNode* ok) {
        ListNode* new_head = new ListNode();
        ListNode* top = heads.back();
        top->up = new_head;
        new_head->below = top;
        heads.push_back(new_head);
        ListNode* create = new ListNode(ok->key);
        new_head->next = create;
        create->below = ok;
        ok->up = create;
        levels++;
    }
    void insert(string s) {
        ListNode* current = heads.back();
        bool done = false;
        while (!done) {
            if (current->key == s) {
                current->count++;
                done = true;
            }
            else if (current->next==NULL || current->next->key>s) {
                if (current->below == NULL) {
                    ListNode* create = new ListNode(s);
                    current->next = create;
                    int level = 1;
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::bernoulli_distribution dist(0.5);
                    int random_variable;
                    do {
                        random_variable = dist(gen);
                        if (level == levels) {
                            this->create_new_level(create);
                            create = create->up;
                            level++;
                        }
                        else {
                            ListNode* h = heads[level];
                            while (h->next != NULL && h->next->key < s) {
                                h = h->next;
                            }
                            ListNode* n = new ListNode(s);
                            n->below = create;
                            create->up = n;
                            create = create->up;
                            level++;
                        }
                    } while (random_variable != 1);
                    done = true;
                }
                else {
                    current = current->below;
                }
            }
            else {
                current = current->next;
            }
        }
    }
    int search(string s) {
         ListNode* current = heads.back();
        bool done = false;
        while (!done) {
            if (current->key == s) {
                return current->count;
                done = true;
            }
            else if (current->next==NULL || current->next->key>s) {
                if (current->below == NULL) {
                    return 0;
                    done = true;
                }
                else {
                    current = current->below;
                }
            }
            else {
                current = current->next;
            }
        }
    }
    int get_levels() {
        return levels;
    }
};
*/
class Dict {
private:
    // You can add attributes/helper functions here
    struct WordNode {
        string word;
        int count;
        WordNode* next;
    int book_code;
    int page;
    int paragraph;
    int sentence_no;
        WordNode(const string& w) : word(w), count(0), next(nullptr) {}
    };

    static const int INITIAL_TABLE_SIZE = 20011;  
    static const double LOAD_FACTOR_THRESHOLD;  

    vector<WordNode*> hashTable;
    int currentTableSize;

    unsigned long hashFunction(const string& word);



    void resizeTable();
public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};
