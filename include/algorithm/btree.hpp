#pragma once
#include <string>

#include "btree_node.hpp"

using namespace std;

// Todo Add ==> Get, Remove
namespace aurora {
    class BTree {
        BTreeNode *root;
        u16 order;

        void insertIntoSubtree(BTreeNode *parentNode, BTreeNode &node, const string &key, const string &value);

        void handleOverflow(BTreeNode *parentNode, BTreeNode &node);

        static void printNode(const BTreeNode &node,
                              const std::string &prefix = "",
                              bool isLast = true);

    public:
        explicit BTree(u16 order);

        ~BTree();

        void insert(const string &key, const string &value);

        [[nodiscard]] u16 minSize() const;

        void print() const;
    };
}
