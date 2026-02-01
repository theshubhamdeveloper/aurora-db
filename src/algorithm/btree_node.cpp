#include "algorithm/btree_node.hpp"
#include <algorithm>
#include "utility/logger.hpp"

namespace aurora {
    BTreeNode::BTreeNode(
        const cosmos::u16 order,
        const bool isLeaf,
        std::optional<std::vector<std::string> > keysOpt,
        std::optional<std::vector<BTreeNode *> > childrenOpt,
        std::optional<std::vector<std::string> > valuesOpt
    )
        : isLeaf(isLeaf) {
        // Keys
        keys.reserve(order);
        if (keysOpt)
            keys.insert(keys.end(),
                        std::make_move_iterator(keysOpt->begin()),
                        std::make_move_iterator(keysOpt->end()));

        // Children
        children.reserve(order + 1);
        if (childrenOpt)
            children.insert(children.end(),
                            std::make_move_iterator(childrenOpt->begin()),
                            std::make_move_iterator(childrenOpt->end()));

        // Values
        if (isLeaf) {
            values.reserve(order);
            if (valuesOpt)
                values.insert(values.end(),
                              std::make_move_iterator(valuesOpt->begin()),
                              std::make_move_iterator(valuesOpt->end()));
        }
    }

    BTreeNode::BTreeNode(const cosmos::u16 order, const bool isLeaf) : BTreeNode(order, isLeaf, std::nullopt, std::nullopt, std::nullopt) {
    }

    BTreeNode::~BTreeNode() {
        for (const auto &child: children) {
            delete child;
        }
    }

    cosmos::u16 BTreeNode::insertKey(const std::string &key) {
        if (isOverflowing()) {
            Logger::error("Adding key and value in overflowing node");
            return -1;
        }
        const auto it = std::ranges::lower_bound(keys, key);
        keys.insert(it, key);
        return std::distance(keys.begin(), it);
    }

    void BTreeNode::insertKeyValue(const std::string &key, const std::string &value) {
        const cosmos::u16 index = insertKey(key);
        values.insert(values.begin() + index, value);
    }

    void BTreeNode::insertChild(const cosmos::u16 at, BTreeNode *node) {
        children.insert(children.begin() + at, node);
    }

    BTreeNode *BTreeNode::split(const cosmos::u16 splitIndex) {
        const auto rightNode = new BTreeNode(order(), isLeaf);

        if (isLeaf) {
            // Move keys & values
            rightNode->keys.assign(
                std::make_move_iterator(keys.begin() + splitIndex),
                std::make_move_iterator(keys.end())
            );

            rightNode->values.assign(
                std::make_move_iterator(values.begin() + splitIndex),
                std::make_move_iterator(values.end())
            );

            values.resize(splitIndex);
        } else {
            // Move keys & children after the middle key
            rightNode->keys.assign(
                std::make_move_iterator(keys.begin() + splitIndex + 1),
                std::make_move_iterator(keys.end())
            );

            rightNode->children.assign(
                std::make_move_iterator(children.begin() + splitIndex + 1),
                std::make_move_iterator(children.end())
            );

            children.resize(splitIndex + 1);
        }

        keys.resize(splitIndex);
        return rightNode;
    }

    bool BTreeNode::isOverflowing() const {
        return size() == keys.capacity();
    }

    cosmos::u16 BTreeNode::size() const {
        return keys.size();
    }

    cosmos::u16 BTreeNode::order() const {
        return keys.capacity();
    }
}
