#include <string>
using namespace std;

/**
 * @class Trie
 * @brief Minimal Trie for lowercase 'a'..'z'.
 *
 * Stores words consisting of lowercase English letters.
 * Note: this simple version does not validate input characters
 * and does not free allocated nodes (no destructor).
 */
class Trie {
private:
    /**
     * @class Node
     * @brief Internal node type for the trie (private).
     *
     * Each node has 26 child pointers (for 'a'..'z') and an `end`
     * flag that marks whether a word finishes at this node.
     */
    class Node {
    public:
        Node* ch[26];
        bool end;
        Node() : end(false) { for (int i = 0; i < 26; ++i) ch[i] = nullptr; }
    };

    Node* root; ///< Root node (allocated at construction)

public:
    /** @brief Create an empty trie. */
    Trie() { root = new Node(); }

    /**
     * @brief Insert a word into the trie.
     * @param s Word to insert (expected lowercase 'a'..'z').
     */
    void insert(const string &s) {
        Node* p = root;
        for (char c : s) {
            int i = c - 'a';
            if (!p->ch[i]) p->ch[i] = new Node();
            p = p->ch[i];
        }
        p->end = true;
    }

    /**
     * @brief Check whether a full word exists in the trie.
     * @param s Word to search (expected lowercase 'a'..'z').
     * @return true if the exact word was inserted, false otherwise.
     */
    bool search(const string &s) const {
        Node* p = root;
        for (char c : s) {
            int i = c - 'a';
            if (!p->ch[i]) return false;
            p = p->ch[i];
        }
        return p->end;
    }

    /**
     * @brief Check whether any stored word starts with the given prefix.
     * @param prefix Prefix to test (expected lowercase 'a'..'z').
     * @return true if at least one inserted word has this prefix.
     */
    bool startsWith(const string &prefix) const {
        Node* p = root;
        for (char c : prefix) {
            int i = c - 'a';
            if (!p->ch[i]) return false;
            p = p->ch[i];
        }
        return true;
    }
};
