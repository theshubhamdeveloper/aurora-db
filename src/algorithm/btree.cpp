#include "algorithm/btree.hpp"

#include <iostream>
#include <ranges>

namespace aurora {
    BTree::BTree(const u16 order) : root(new BTreeNode{order, true}), order(order) {
    }

    BTree::~BTree() {
        delete root;
    }

    void BTree::insertIntoSubtree(BTreeNode *parentNode, BTreeNode &node, const string &key, const string &value) {
        if (node.isLeaf) {
            node.insertKeyValue(key, value);
        } else {
            auto currentChildNode = node.children[0];
            for (i32 i = node.size() - 1; i >= 0; --i) {
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
        const u16 splitIndex = minSize();
        const string promotedKey = node.keys.at(splitIndex);

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


    void BTree::insert(const string &key, const string &value) {
        insertIntoSubtree(nullptr, *root, key, value);
    }

    void BTree::print() const {
        printNode(*root);
    }

    void BTree::printNode(const BTreeNode &node,
                          const std::string &prefix,
                          const bool isLast) {
        cout << prefix;
        cout << (isLast ? "└─ " : "├─ ");

        // print keys
        cout << "[ ";
        for (size_t i = 0; i < node.keys.size(); ++i) {
            cout << node.keys[i];
            if (i + 1 < node.keys.size()) cout << ", ";
        }
        cout << " ]";

        // print values
        if (node.isLeaf) {
            cout << " -> { ";
            for (size_t i = 0; i < node.values.size(); ++i) {
                cout << node.values[i];
                if (i + 1 < node.values.size()) cout << ", ";
            }
            cout << " }";
        }

        cout << "\n";

        // recurse into children
        const string childPrefix = prefix + (isLast ? "   " : "│  ");
        for (size_t i = 0; i < node.children.size(); ++i) {
            const bool lastChild = i == node.children.size() - 1;
            printNode(*node.children[i], childPrefix, lastChild);
        }
    }

    u16 BTree::minSize() const {
        return (order - 1) / 2;
    }
}
