#pragma once
#include <optional>
#include <vector>

#include "library/data_type.hpp"

using namespace crush;
using namespace std;

namespace aurora {
    struct BTreeNode {
        vector<string> keys;
        vector<string> values;
        vector<BTreeNode *> children;
        bool isLeaf;

        BTreeNode(u16 order, bool isLeaf);

        BTreeNode(u16 order, bool isLeaf, std::optional<std::vector<string> > keysOpt,
                  std::optional<std::vector<BTreeNode *> > childrenOpt, std::optional<std::vector<string> > valuesOpt);

        ~BTreeNode();

        u16 insertKey(const string &key);

        void insertKeyValue(const string &key, const string &value);

        void insertChild(u16 at, BTreeNode *node);

        BTreeNode *split(u16 splitIndex);

        [[nodiscard]] bool isOverflowing() const;

        [[nodiscard]] u16 size() const;

        [[nodiscard]] u16 order() const;
    };
}
