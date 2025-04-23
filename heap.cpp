#include <algorithm> // std::swap
#include "heap.h"

using std::swap;

void HeapNode::push(int x)
{
    size = size + 1;

    // Apply "percolate down" on the new value 'x' if x < val
    if (x < val)
        swap(x, val);

    if (left == nullptr)
    {
        left = new HeapNode(x);
    }
    else if (right == nullptr)
    {
        right = new HeapNode(x);
    }
    
    else if (left->size <= right->size)
    {
        left->push(x);
    }

    else
    {
        right->push(x);
    }

    // Since left-child <= right-child
    if (left!=nullptr && right!=nullptr && left->val > right->val)
    {
        swap(left->val, right->val);
    }
}

int HeapNode::pop() {
    int result = val;

    // If it's a leaf node
    if (!left && !right) {
        size = 0;
        return result;
    }

    // Pick the heavier subtree to find the last node
    if (left && (!right || left->size >= right->size)) {
        val = left->pop();
        if (left->size == 0) {
            delete left;
            left = nullptr;
        }
    } else {
        val = right->pop();
        if (right->size == 0) {
            delete right;
            right = nullptr;
        }
    }

    size--;
    heapify();
    return result;
}




void HeapNode::heapify()
{
    HeapNode *min = this;


    if (left != nullptr && left->val < min->val)
    {
        min = left;
    }

    if (right != nullptr && right->val < min->val)
    {
        min = right;
    }

    if (min->val != this->val)
    {
        swap(min->val, val);
        min->heapify();
    }
}