#include "algorithm/btree_node.hpp"

#include "utility/logger.hpp"

namespace aurora {
    BTreeNode::BTreeNode(const u16 order, const bool isLeaf) : isLeaf(isLeaf) {
        keys.reserve(order);
        children.reserve(order + 1);

        values.reserve(isLeaf ? order : 0);
    }

    BTreeNode::~BTreeNode() {
        for (const auto &child: children) {
            delete child;
        }
    }

    u16 BTreeNode::insertKey(const string &key) {
        const auto it = ranges::lower_bound(keys, key);
        keys.insert(it, key);
        return std::distance(keys.begin(), it);
    }

    void BTreeNode::insertKeyValue(const string &key, const string &value) {
        if (isOverflowing()) {
            Logger::error("Adding key and value in overflowing node");
            return;
        }
        const u16 index = insertKey(key);
        values.insert(values.begin() + index, value);
    }

    void BTreeNode::insertChild(const u16 at, BTreeNode *node) {
        children.insert(children.begin() + at, node);
    }

    bool BTreeNode::isOverflowing() const {
        return keys.size() == keys.capacity();
    }

    u16 BTreeNode::size() const {
        return keys.size();
    }
}
