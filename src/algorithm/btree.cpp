#include "algorithm/btree.hpp"

#include <iostream>
#include <ranges>

namespace aurora {
    BTree::BTree(const u16 order) : root(nullptr), order(order) {
    }

    BTree::~BTree() {
        delete root;
    }

    string BTree::splitNodeAndPromoteKey(BTreeNode &leftNode, BTreeNode &rightNode) const {
        const u16 splitIndex = minSize();

        const string promotedKey = leftNode.keys.at(splitIndex);

        auto &currentKeys = leftNode.keys;
        auto &currentValues = leftNode.values;
        auto &currentChildren = leftNode.children;

        const auto splitKeyIt = currentKeys.begin() + splitIndex;
        const auto splitValueIt = currentValues.begin() + splitIndex;
        const auto splitChildrenIt = currentChildren.begin() + splitIndex + 1;

        if (leftNode.isLeaf) {
            rightNode.keys.insert(rightNode.keys.begin(), splitKeyIt, currentKeys.end());
            rightNode.values.insert(rightNode.values.begin(), splitValueIt, leftNode.values.end());
        } else {
            rightNode.keys.insert(rightNode.keys.begin(), splitKeyIt + 1, currentKeys.end());
            rightNode.children.insert(rightNode.children.begin(), splitChildrenIt, currentChildren.end());
        }

        leftNode.keys.erase(splitKeyIt, currentKeys.end());
        if (leftNode.isLeaf) {
            leftNode.values.erase(splitValueIt, currentValues.end());
        } else {
            leftNode.children.erase(splitChildrenIt, currentChildren.end());
        }

        return promotedKey;
    }

    void BTree::insertIntoSubtree(BTreeNode *parentNode, BTreeNode &node, const string &key, const string &value) {
        if (node.isLeaf) {
            node.insertKeyValue(key, value);
        } else {
            auto currentChildNode = node.children[0];
            for (i16 i = node.size() - 1; i >= 0; --i) {
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
        const auto rightNode = new BTreeNode(order, node.isLeaf);
        const string promotedKey = splitNodeAndPromoteKey(node, *rightNode);
        if (parentNode == nullptr) {
            parentNode = new BTreeNode(order, false);
            parentNode->insertKey(promotedKey);
            parentNode->children.push_back(&node);
            parentNode->children.push_back(rightNode);
            root = parentNode;
            return;
        }

        const auto pos = parentNode->insertKey(promotedKey);
        parentNode->insertChild(pos + 1, rightNode);
    }


    void BTree::insert(const string &key, const string &value) {
        if (root == nullptr) {
            root = new BTreeNode(order, true);
            root->insertKeyValue(key, value);
            return;
        }

        insertIntoSubtree(nullptr, *root, key, value);
    }

    u16 BTree::minSize() const {
        return (order - 1) / 2;
    }
}
