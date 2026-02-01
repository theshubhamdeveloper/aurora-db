#pragma once
#include <optional>
#include <vector>
#include <string>
#include "cosmos.hpp"

namespace aurora {
    struct BTreeNode {
        std::vector<std::string> keys;
        std::vector<std::string> values;
        std::vector<BTreeNode *> children;
        bool isLeaf;

        BTreeNode(cosmos::u16 order, bool isLeaf);

        BTreeNode(cosmos::u16 order,
                  bool isLeaf,
                  std::optional<std::vector<std::string> > keysOpt,
                  std::optional<std::vector<BTreeNode *> > childrenOpt,
                  std::optional<std::vector<std::string> > valuesOpt);

        ~BTreeNode();

        cosmos::u16 insertKey(const std::string &key);

        void insertKeyValue(const std::string &key, const std::string &value);

        void insertChild(cosmos::u16 at, BTreeNode *node);

        BTreeNode *split(cosmos::u16 splitIndex);

        [[nodiscard]] bool isOverflowing() const;

        [[nodiscard]] cosmos::u16 size() const;

        [[nodiscard]] cosmos::u16 order() const;
    };
}
