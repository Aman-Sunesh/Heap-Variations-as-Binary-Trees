#include <string>
#include <stack>

class HeapNode
{
        int val;
        HeapNode * left, * right;
        int size; // number of nodes in this subtree

    public:

        HeapNode(int v) : val(v), left(nullptr), right(nullptr), size(1) {}

        HeapNode(const HeapNode &) = delete;
        ~HeapNode() { delete left; delete right; }

        std::string str() const { return std::to_string(val); }
        std::string edges() const;

        bool empty() const { return size == 1; }

        void valid() const;

        void push(int x);
        int pop();

        // helper function
        void heapify();

        int max_value();

        class HeapIterator
        {
            private:
                stack<HeapNode*> s;

            public:
                HeapIterator(HeapNode* root)
                {
                    while (root != nullptr)
                    {
                        s.push(root);
                        root = root->left;
                    }
                }

                HeapIterator& operator ++()
                {
                    HeapNode* current = s.top();
                    s.pop();

                    current = current->right;

                    while (current != nullptr) 
                    {
                        s.push(current);
                        current = current->left;
                    }

                    return *this;
                }

                bool operator !=(const HeapIterator& other)
                {
                    if (this->s != other.s)
                    {
                        return true;
                    }

                    else
                    {
                        return false;
                    }
                }

                HeapNode& operator *()
                {
                    return *s.top();
                }
        };

        HeapIterator begin()
        {
            return HeapIterator(this);
        }

        HeapIterator end()
        {
            return HeapIterator(nullptr);
        }
    };

inline std::string HeapNode::edges() const
{
    std::string r;

    if (left) r += str() + " --> " + left->str() + '\n';
    if (right) r += str() + " --> " + right->str() + '\n';

    if (left) r += left->edges();
    if (right) r += right->edges();

    return r;
}

inline void HeapNode::valid() const
{
    if ( left && val > left->val || right && val > right->val )
        throw "Heap invalid at node " + std::to_string(val);
    if (left) left->valid();
    if (right) right->valid();
}
