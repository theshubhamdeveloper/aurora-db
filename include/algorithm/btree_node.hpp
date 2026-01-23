#pragma once
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

        ~BTreeNode();

        u16 insertKey(const string &key);

        void insertKeyValue(const string &key, const string &value);

        void insertChild(u16 at, BTreeNode *node);

        bool isOverflowing() const;

        u16 size() const;
    };
}
