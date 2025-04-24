#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

class HeapNode {
    int val;
    HeapNode *left, *right;
    int size;

public:
    HeapNode(int v) : val(v), left(nullptr), right(nullptr), size(1) {}
    HeapNode(const HeapNode &) = delete;
    ~HeapNode() { delete left; delete right; }

    string str() const { return to_string(val); }
    string edges() const;
    bool empty() const { return size == 1; }
    void valid() const;
    void push(int x);
    int pop();
    void heapify();
};

string HeapNode::edges() const {
    string r;
    if (left) r += str() + " --> " + left->str() + '\n';
    if (right) r += str() + " --> " + right->str() + '\n';
    if (left) r += left->edges();
    if (right) r += right->edges();
    return r;
}

void HeapNode::valid() const {
    if ((left && val > left->val) || (right && val > right->val))
        throw string("Heap invalid at node ") + to_string(val);
    if (left) left->valid();
    if (right) right->valid();
}

void HeapNode::heapify() {
    HeapNode* smallest = this;
    if (left && left->val < smallest->val) smallest = left;
    if (right && right->val < smallest->val) smallest = right;

    if (smallest != this) {
        swap(val, smallest->val);
        smallest->heapify();
    }
}

void HeapNode::push(int x) {
    ++size;

    if (!left) {
        left = new HeapNode(x);
    } else if (!right) {
        right = new HeapNode(x);
    } else {
        if (left->size <= right->size)
            left->push(x);
        else
            right->push(x);
    }

    heapify();
}

int HeapNode::pop() {
    if (!left && !right) {
        int res = val;
        size = 0;
        return res;
    }

    // Collect all nodes into a vector using BFS
    vector<HeapNode*> nodes;
    nodes.push_back(this);

    for (size_t i = 0; i < nodes.size(); ++i) {
        if (nodes[i]->left) nodes.push_back(nodes[i]->left);
        if (nodes[i]->right) nodes.push_back(nodes[i]->right);
    }

    HeapNode* last = nodes.back();
    int popped = val;
    val = last->val;

    // Remove last node from tree
    for (HeapNode* node : nodes) {
        if (node->left == last) {
            delete node->left;
            node->left = nullptr;
            break;
        }
        if (node->right == last) {
            delete node->right;
            node->right = nullptr;
            break;
        }
    }

    --size;
    heapify();
    return popped;
}

int main()
try {
    vector<int> v {1, 0, 5, 7, 9, 2, 4, 6, 8};
    HeapNode heap(3);

    auto prn = [](int x, const HeapNode & h, string a) {
        cout << "```mermaid\ngraph TD\n"
             << "A(\"" << a << ' ' << x << "\")\n"
             << "style A fill:#ded\n"
             << h.edges() << "```\n---\n";
    };

    for (auto x : v) {
        heap.push(x);
        prn(x, heap, "push");
        heap.valid();
    }

    while (!heap.empty()) {
        int x = heap.pop();
        prn(x, heap, "pop");
        if (!heap.empty()) heap.valid();
    }
}
catch (string s) { cout << "Error: " << s << '\n'; }
catch (...) { cout << "exception\n"; }
