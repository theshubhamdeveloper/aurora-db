#include "algorithm/btree.hpp"
#include <iostream>
#include <ranges>

namespace aurora {
    BTree::BTree(const cosmos::u16 order) : root(new BTreeNode{order, true}), order(order) {
    }

    BTree::~BTree() {
        delete root;
    }

    void BTree::insertIntoSubtree(BTreeNode *parentNode, BTreeNode &node, const std::string &key, const std::string &value) {
        if (node.isLeaf) {
            node.insertKeyValue(key, value);
        } else {
            auto currentChildNode = node.children[0];
            for (cosmos::i32 i = node.size() - 1; i >= 0; --i) {
                if (key > node.keys[i]) {
                    currentChildNode = node.children[i + 1];
                    break;
                }
            }
            insertIntoSubtree(&node, *currentChildNode, key, value);
        }

        if (node.isOverflowing()) {
            handleOverflow(parentNode, node);
        }
    }

    void BTree::handleOverflow(BTreeNode *parentNode, BTreeNode &node) {
        const cosmos::u16 splitIndex = minSize();
        const std::string promotedKey = node.keys.at(splitIndex);

        BTreeNode *rightNode = node.split(splitIndex);

        if (parentNode == nullptr) {
            root = new BTreeNode(
                order,
                false,
                std::make_optional(std::vector{promotedKey}),
                std::make_optional(std::vector{&node, rightNode}),
                std::nullopt
            );
            return;
        }

        const auto pos = parentNode->insertKey(promotedKey) + 1;
        parentNode->insertChild(pos, rightNode);
    }


    void BTree::insert(const std::string &key, const std::string &value) {
        insertIntoSubtree(nullptr, *root, key, value);
    }

    void BTree::print() const {
        printNode(*root);
    }

    void BTree::printNode(const BTreeNode &node,
                          const std::string &prefix,
                          const bool isLast) {
        std::cout << prefix;
        std::cout << (isLast ? "└─ " : "├─ ");

        // print keys
        std::cout << "[ ";
        for (size_t i = 0; i < node.keys.size(); ++i) {
            std::cout << node.keys[i];
            if (i + 1 < node.keys.size()) std::cout << ", ";
        }
        std::cout << " ]";

        // print values
        if (node.isLeaf) {
            std::cout << " -> { ";
            for (size_t i = 0; i < node.values.size(); ++i) {
                std::cout << node.values[i];
                if (i + 1 < node.values.size()) std::cout << ", ";
            }
            std::cout << " }";
        }

        std::cout << "\n";

        // recurse into children
        const std::string childPrefix = prefix + (isLast ? "   " : "│  ");
        for (size_t i = 0; i < node.children.size(); ++i) {
            const bool lastChild = i == node.children.size() - 1;
            printNode(*node.children[i], childPrefix, lastChild);
        }
    }

    cosmos::u16 BTree::minSize() const {
        return (order - 1) / 2;
    }
}
