#include "Splay.h"
#include <iostream>

void SplayTree::pushDown(Node* x) {
    if (x == nullptr) {
        return;
    }
    if (x->reverse != 0) {
        if (x->leftSon != nullptr) {
            x->leftSon->reverse = x->reverse ^ x->leftSon->reverse;
        }
        if (x->rightSon != nullptr) {
            x->rightSon->reverse = x->reverse ^ x->rightSon->reverse;
        }
        std::swap(x->leftSon, x->rightSon);
        std::swap(x->prefLen, x->sufLen);
        std::swap(x->treeLeft, x->treeRight);
        x->reverse = 0;
    }
    if (x->leftSon != nullptr) {
        x->leftSon->addValue += x->addValue;
    }
    if (x->rightSon != nullptr) {
        x->rightSon->addValue += x->addValue;
    }
    x->val += x->addValue;
    x->subtreeSum += x->subtreeSize * x->addValue;
    x->addValue = 0;
}

SplayTree::Node* SplayTree::rotate(Node* x) {
    pushDown(x);
    x->addValue = x->parent->addValue;
    x->parent->val += x->parent->addValue;
    x->parent->addValue = 0;

    if (x->parent->leftSon == x) {
        Node* a = x->rightSon;
        Node* grandParent = x->parent->parent;
        if (grandParent == nullptr) {
            pushDown(x->rightSon);
            x->rightSon = x->parent;
            x->rightSon->leftSon = a;
            if (a != nullptr)
                x->rightSon->leftSon->parent = x->rightSon;
            x->rightSon->parent = x;
            x->parent = nullptr;
            pushDown(x->rightSon);
            update(x->rightSon);
            update(x);
            return x;
        }
        bool left = (grandParent->leftSon == x->parent);
        pushDown(x->rightSon);
        x->rightSon = x->parent;
        x->rightSon->leftSon = a;
        if (a != nullptr)
            x->rightSon->leftSon->parent = x->rightSon;
        x->rightSon->parent = x;
        x->parent = grandParent;
        if (left) {
            x->parent->leftSon = x;
        }
        else {
            x->parent->rightSon = x;
        }
        pushDown(x->rightSon);
        update(x->rightSon);
    }
    else{
        Node* a = x->leftSon;
        Node* grandParent = x->parent->parent;
        if (grandParent == nullptr) {
            pushDown(x->leftSon);
            x->leftSon = x->parent;
            x->leftSon->rightSon = a;
            if (a != nullptr)
                x->leftSon->rightSon->parent = x->leftSon;
            x->leftSon->parent = x;
            x->parent = nullptr;
            pushDown(x->leftSon);
            update(x->leftSon);
            update(x);
            return x;
        }
        bool left = (grandParent->leftSon == x->parent);
        pushDown(x->leftSon);
        x->leftSon = x->parent;
        x->leftSon->rightSon = a;
        if (a != nullptr)
            x->leftSon->rightSon->parent = x->leftSon;
        x->leftSon->parent = x;
        x->parent = grandParent;
        pushDown(x->leftSon);
        if (left) {
            x->parent->leftSon = x;
        }
        else {
            x->parent->rightSon = x;
        }
        update(x->leftSon);
    }
    update(x);
    update(x->parent);
    return x;
}

SplayTree::Node* SplayTree::zig(Node* x) {
    return rotate(x);
}

SplayTree::Node* SplayTree::zigzig(Node* x) {
    Node* y = rotate(x->parent);
    y->val = y->val;
    x = rotate(x);
    return x;
}

SplayTree::Node* SplayTree::zigzag(Node* x) {
    x = rotate(x);
    x = rotate(x);
    return x;
}

SplayTree::Node* SplayTree::splay(Node* x) {
    if (x == nullptr || x->parent == nullptr) {
        return x;
    }
    if (x->parent->parent == nullptr) {
        return splay(zig(x));
    }
    if (x->parent->leftSon == x && x->parent->parent->leftSon == x->parent) {
        return splay(zigzig(x));
    }
    if (x->parent->rightSon == x && x->parent->parent->rightSon == x->parent) {
        return splay(zigzig(x));
    }
    if (x->parent->leftSon == x && x->parent->parent->rightSon == x->parent) {
        return splay(zigzag(x));
    }
    if (x->parent->rightSon == x && x->parent->parent->leftSon == x->parent) {
        return splay(zigzag(x));
    }
    return nullptr;
}

SplayTree::Node* SplayTree::maxIndex(Node* x) {
    if (x == nullptr || x->rightSon == nullptr) {
        return x;
    }
    else {
        return maxIndex(x->rightSon);
    }
}

SplayTree::Node* SplayTree::copy(Node* root, Node* x) {
    if (x == nullptr) {
        root = nullptr;
        return root;
    }

    root = x;
    if (x->leftSon != nullptr) {
        x->leftSon->parent = root;
    }
    if (x->rightSon != nullptr) {
        x->rightSon->parent = root;
    }
    return root;
}

SplayTree::Node* SplayTree::merge(Node* root, Node* x) {
    root = splay(maxIndex(root));
    if (root != nullptr) {
        root->rightSon = x;
        if (x != nullptr) {
            x->parent = root;
        }
    }
    else {
        root = copy(root, x);
    }
    pushDown(root);
    pushDown(root->leftSon);
    pushDown(root->rightSon);
    update(root);
    return root;
}

SplayTree::Node* SplayTree::findNode(int pos, Node* curNode) {
    if (curNode == nullptr) {
        return nullptr;
    }
    if (curNode->leftSon == nullptr) {
        if (pos == 0) {
            return curNode;
        }
        else {
            return findNode(pos - 1, curNode->rightSon);
        }
    }
    if (curNode->leftSon != nullptr && curNode->leftSon->subtreeSize - 1 >= pos) {
        return findNode(pos, curNode->leftSon);
    }
    else if (curNode->leftSon != nullptr && curNode->leftSon->subtreeSize == pos) {
        return curNode;
    }
    else if (curNode->leftSon != nullptr && curNode->leftSon->subtreeSize < pos) {
        return findNode(pos - curNode->leftSon->subtreeSize - 1, curNode->rightSon);
    }
    else{
        return nullptr;
    }
}

void SplayTree::update(Node* x) {
    if (x == nullptr) {
        return;
    }
    if (x->leftSon != nullptr && x->rightSon != nullptr) {
        x->subtreeSum = x->val + x->leftSon->subtreeSum + x->rightSon->subtreeSum;
        x->subtreeSize = 1 + x->leftSon->subtreeSize + x->rightSon->subtreeSize;
    }
    else if (x->leftSon == nullptr && x->rightSon != nullptr) {
        x->subtreeSum = x->val + x->rightSon->subtreeSum;
        x->subtreeSize = 1 + x->rightSon->subtreeSize;
    }
    else if (x->leftSon != nullptr && x->rightSon == nullptr) {
        x->subtreeSum = x->val + x->leftSon->subtreeSum;
        x->subtreeSize = 1 + x->leftSon->subtreeSize;
    }
    else{
        x->subtreeSum = x->val;
        x->subtreeSize = 1;
    }

    if (x->leftSon != nullptr && x->leftSon->subtreeSize == x->leftSon->prefLen) {
        if (x->leftSon->treeRight <= x->val) {
            if (x->rightSon != nullptr && x->rightSon->treeLeft >= x->val) {
                x->prefLen = x->leftSon->prefLen + 1 + x->rightSon->prefLen;
            }
            else {
                x->prefLen = x->leftSon->prefLen + 1;
            }
        }
        else {
            x->prefLen = x->leftSon->prefLen;
        }
        x->treeLeft = x->leftSon->treeLeft;
    }
    else if (x->leftSon != nullptr && x->leftSon->subtreeSize > x->leftSon->prefLen) {
        x->prefLen = x->leftSon->prefLen;
        x->treeLeft = x->leftSon->treeLeft;
    }
    else {
        x->treeLeft = x->val;
        if (x->rightSon != nullptr && x->rightSon->treeLeft >= x->val) {
            x->prefLen = x->rightSon->prefLen + 1;
        }
        else {
            x->prefLen = 1;
        }
    }

    if (x->rightSon != nullptr && x->rightSon->subtreeSize == x->rightSon->sufLen) {
        if (x->rightSon->treeLeft <= x->val) {
            if (x->leftSon != nullptr && x->leftSon->treeRight >= x->val) {
                x->sufLen = x->leftSon->sufLen + 1 + x->rightSon->sufLen;
            }
            else {
                x->sufLen = x->rightSon->sufLen + 1;
            }
        }
        else {
            x->sufLen = x->rightSon->sufLen;
        }
        x->treeRight = x->rightSon->treeRight;
    }
    else if (x->rightSon != nullptr && x->rightSon->subtreeSize > x->rightSon->sufLen) {
        x->sufLen = x->rightSon->sufLen;
        x->treeRight = x->rightSon->treeRight;
    }
    else {
        x->treeRight = x->val;
        if (x->leftSon != nullptr && x->leftSon->treeRight >= x->val) {
            x->sufLen = x->leftSon->sufLen + 1;
        }
        else {
            x->sufLen = 1;
        }
    }
}

void SplayTree::setElementh(int value, int pos) {
    Node* x = findNode(pos, root_);
    x->val = value;
    root_ = splay(x);
}

std::pair<SplayTree::Node*, SplayTree::Node*> SplayTree::split(Node* root, int pos) {  // Режем так, что в левом дереве (pos - 1) вершин
    if (root != nullptr) {
        if (pos == 0) {
            std::pair<Node*, Node*> result;
            result.first = nullptr;
            result.second = root;
            root = nullptr;
            return result;
        }
        Node* x = findNode(pos - 1, root);
        if (x == nullptr) {
            std::pair<Node*, Node*> result;
            result.first = root;
            result.second = x;
            return result;
        }
        root = splay(x);
        Node* y = root->rightSon;
        if (y != nullptr) {
            y->parent = nullptr;
        }
        root->rightSon = nullptr;
        pushDown(y);
        if (y != nullptr) {
            pushDown(y->leftSon);
            pushDown(y->rightSon);
        }
        pushDown(root);
        if (root != nullptr)
           pushDown(root->leftSon);

        update(root);
        update(y);
        std::pair<Node*, Node*> result;
        result.first = root;
        result.second = y;
        return result;
    }
    else {
        std::pair<Node*, Node*> result;
        result.first = nullptr;
        result.second = nullptr;
        return result;
    }
}

long long SplayTree::sumRange(int l, int r) {
    std::pair<Node*, Node*> pr1 = split(root_, r + 1);
    root_ = pr1.first;
    std::pair<Node*, Node*> pr2 = split(root_, l);
    root_ = pr2.first;
    long long answer = pr2.second->subtreeSum;
    root_ = merge(root_, pr2.second);
    root_ = merge(root_, pr1.second);
    return answer;
}

void SplayTree::insertElementh(int value, int pos) {
    std::pair<Node*, Node*> pr1 = split(root_, pos);
    root_ = pr1.first;
    Node* x = new Node;
    x->leftSon = nullptr;
    x->rightSon = nullptr;
    x->parent = nullptr;
    x->subtreeSize = 1;
    x->subtreeSum = value;
    x->val = value;
    x->prefLen = 1;
    x->reverse = 0;
    x->sufLen = 1;
    x->treeLeft = value;
    x->treeRight = value;
    root_ = merge(root_, x);
    root_ = merge(root_, pr1.second);
}

void SplayTree::addInRange(int value, int l, int r) {
    std::pair<Node*, Node*> pr1 = split(root_, r + 1);
    root_ = pr1.first;
    std::pair<Node*, Node*> pr2 = split(root_, l);
    root_ = pr2.first;
    pr2.second->addValue += value;
    root_ = merge(root_, pr2.second);
    root_ = merge(root_, pr1.second);
}

SplayTree::Node* SplayTree::findMin(long long val, Node* curNode) {
    if (curNode == nullptr) {
        return nullptr;
    }
    Node* v1 = findMin(val, curNode->rightSon);
    if (v1 != nullptr) {
        return v1;
    }
    if (curNode->val > val) {
        return curNode;
    }
    return findMin(val, curNode->leftSon);
}

std::pair<long long, SplayTree::Node*> SplayTree::newfindMin(Node* toSplay) {
    std::pair<long long, Node*> result;
    result.second = splay(toSplay);
    if (result.second->leftSon != nullptr) {
        result.first = result.second->leftSon->subtreeSize;
    }
    else {
        result.first = 0;
    }
    return result;
}

void SplayTree::nextPermutation(int l, int r) {
    std::pair<Node*, Node*> pr1 = split(root_, r + 1);
    root_ = pr1.first;
    std::pair<Node*, Node*> pr2 = split(root_, l);
    root_ = pr2.first;
    if (pr2.second->sufLen == pr2.second->subtreeSize) {
        pr2.second->reverse = !pr2.second->reverse;
    }
    else {
        std::pair<Node*, Node*> pr3 = split(pr2.second, pr2.second->subtreeSize - pr2.second->sufLen - 1);
        std::pair<Node*, Node*> pr4 = split(pr3.second, 1);
        std::pair<long long, Node*> result = newfindMin(findMin(pr4.first->val, pr4.second));
        long long change = result.first;
        std::pair<Node*, Node*> pr5 = split(result.second, change + 1);
        std::pair<Node*, Node*> pr6 = split(pr5.first, change);

        Node* v1 = merge(pr4.first, pr5.second);
        Node* v2 = merge(pr6.first, v1);
        v2->reverse = v2->reverse ^ 1;
        pushDown(v2);
        pushDown(v2->leftSon);
        pushDown(v2->rightSon);
        update(v2);
        Node* v3 = merge(pr6.second, v2);
        Node* v4 = merge(pr3.first, v3);
        Node* v5 = merge(pr2.first, v4);
        Node* v6 = merge(v5, pr1.second);
        root_ = v6;
    }
}

SplayTree::SplayTree() :
    root_(nullptr)
{}

void SplayTree::recursively_destruct(Node * v) {
    if (v == nullptr) {
        return;
    }
    recursively_destruct(v->leftSon);
    recursively_destruct(v->rightSon);
    delete v;
}

SplayTree::~SplayTree() {
    recursively_destruct(root_);
}
