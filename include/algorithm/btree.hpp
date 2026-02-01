#pragma once
#include <string>
#include "btree_node.hpp"
#include "cosmos.hpp"

// Todo Add ==> Get, Remove
namespace aurora {
    class BTree {
        BTreeNode *root;
        cosmos::u16 order;

        void insertIntoSubtree(BTreeNode *parentNode, BTreeNode &node, const std::string &key, const std::string &value);

        void handleOverflow(BTreeNode *parentNode, BTreeNode &node);

        static void printNode(const BTreeNode &node,
                              const std::string &prefix = "",
                              bool isLast = true);

    public:
        explicit BTree(cosmos::u16 order);

        ~BTree();

        void insert(const std::string &key, const std::string &value);

        [[nodiscard]] cosmos::u16 minSize() const;

        void print() const;
    };
}
