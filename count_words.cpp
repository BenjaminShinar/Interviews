#include <iostream>
#include <string>
#include <array>
#include <vector>
//read words(strings...)
//int getWordCount(string)

//only works with capital letters
struct TrieNode
{
    ~TrieNode()
    {
        for (auto *p : children)
        {
            if (p != nullptr)
                delete p;
            p = nullptr;
        }
    }
    static const std::size_t LETTERS = 26;
    std::array<TrieNode *, LETTERS> children{};
    std::size_t word_appearances = 0;
    bool hasChild(char c) const
    {
        return children[c - 'A'] != nullptr;
    }

    TrieNode *getChild(char c)
    {
        return children[c - 'A'];
    }

    TrieNode *addChild(char c)
    {
        auto child = new TrieNode(); //use smart pointer eventually
        children[c - 'A'] = child;
        return child;
    }
    //create a child at children[c].
    // allocate memory,etc...

    //when searching for a child. we iterate over each letter in the string, if there is a child, use it as 'current' and repeat with the next letter.
    // if we finished the word and we have a something, then check the appearances (shorter words are contained in larger words, be carefiull)
};

struct TrieTree
{
    TrieNode root;
    //assume we have part of the word
    //if string length is zero then this is the target node, return count
    //take first letter

    // check if exists,

    // if not, return zero
    // if exits, continue. with the next.
    std::size_t getWordAppearances(const std::string &s)
    {
        TrieNode *curr = &root;

        for (const char c : s)
        {
            if (curr->hasChild(c))
            {
                //child found, continue
                curr = curr->getChild(c);
            }
            else
            {
                //no child
                return 0;
            }
        }
        //finished iterating the word
        return curr->word_appearances;
    }

    void addWord(const std::string &word)
    {

        TrieNode *curr = &root;

        //iterate over characters in word,
        for (const char c : word)
        {
            // if child exists, take it, otherwise, create it
            if (curr->hasChild(c))
            {
                curr = curr->getChild(c);
            }
            else
            {
                curr = curr->addChild(c);
            }
        }
        // after the drilldown, add to the count
        ++curr->word_appearances;
    }
};

int main()
{
    std::vector<std::string> words = {"AB", "AC"};
    TrieTree tree;

    std::cout << tree.getWordAppearances("AB") << '\n';
    tree.addWord("AB");
    for (const auto &w : words)
    {
        tree.addWord(w);
    }
    std::cout << tree.getWordAppearances("AB") << '\n';
}