#include <string>
using namespace std;

class Trie {
private:
    struct Node {
        Node* ch[26];
        bool end;                 // true if node represents end of a word
        Node() : end(false) {
            for (int i = 0; i < 26; i++) ch[i] = nullptr;
        }
    };
    Node* root;

public:
    // Constructor: initialize root node
    Trie() {
        root = new Node();
    }

    // Insert a word into the trie
    void insert(const string &s) {
        Node* p = root;
        for (char c : s) {
            int i = c - 'a';
            if (!p->ch[i]) {
                p->ch[i] = new Node();  // create node if missing
            }
            p = p->ch[i];
        }
        p->end = true;   // mark end of word
    }

    // Search for a full word in the trie
    bool search(const string &s) const {
        Node* p = root;
        for (char c : s) {
            int i = c - 'a';
            if (!p->ch[i]) return false;  // missing node means word not present
            p = p->ch[i];
        }
        return p->end;  // true if final node is end-of-word
    }

    // Check if any word in the trie starts with the given prefix
    bool startsWith(const string &prefix) const {
        Node* p = root;
        for (char c : prefix) {
            int i = c - 'a';
            if (!p->ch[i]) return false;  // missing node means prefix not present
            p = p->ch[i];
        }
        return true;  // all prefix chars found
    }
};
