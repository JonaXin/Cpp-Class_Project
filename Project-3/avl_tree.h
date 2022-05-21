#include <memory>
#include <cmath>

using namespace std;

template <typename Key, typename Value = Key>
class AVLTree {
public:
    class Node {
    private:
        Key key_;
        Value value_;
        int balance_factor_;
        int height_;
        Node *left_, *right_;
        Node(const Key& key) : key_(key), balance_factor_(0), height_(0), left_(nullptr), right_(nullptr) {}
        Node(const Key& key, const Value& value)
            : key_(key), value_(value), balance_factor_(0), height_(0), left_(nullptr), right_(nullptr) {}

    public:
        ~Node() {
            delete left_;
            delete right_;
        }
        // All these getter methods are O(1)
        Node* left() {
            return left_;
        }
        Node* right() {
            return right_;
        }
        const Key& key() const {
            return key_;
        }
        const Value& value() const {
            return value_;
        }
        const int balance_factor() const {
            return balance_factor_;
        }

        int height(Node* t) const
        {
            return t == nullptr ? -1 : t->height_;
        }

        Value& helper(const Key& k, int& size, Node*& node) {
            if (k == node->key_) {
                return value_;
            }
           
            if (k < node->key_) {  // Need to insert to the left
                if (node->left_ == nullptr) {
                    node->left_ = new Node(k);
                    size++;
                    return node->left_->value_;
                }
                else {
                    auto& result = helper(k, size, node->left_);
                    balance(node->left_);
                    node->left_->balance_factor_ = height(node->left_->right_) - height(node->left_->left_);
                    return result;
                }
            }
            else { // if (k > key)  Need to insert to the right
                if (node->right_ == nullptr) {
                    
                    node->right_ = new Node(k);
                    size++;
                    return node->right_->value_;
                }
                else {
                    auto& result = helper(k, size, node->right_);
                    balance(node->right_);
                    node->right_->balance_factor_ = height(node->right_->right_) - height(node->right_->left_);
                    return result;
                }
            }
        
        }

        void balance(Node*& t)
        {
            if (t == nullptr)
                return;

            if (height(t->left_) - height(t->right_) > 1)
                if (height(t->left_->left_) >= height(t->left_->right_)) {
                    rotateWithLeftChild(t);
                }
                else {
                    doubleWithLeftChild(t);
                }
            else if (height(t->right_) - height(t->left_) > 1) {
                if (height(t->right_->right_) >= height(t->right_->left_)) {
                    rotateWithRightChild(t);
                }
                else {                  
                    doubleWithRightChild(t);
                }
            }

            t->height_ = max(height(t->left_), height(t->right_)) + 1;
            t->balance_factor_ = height(t->right_) - height(t->left_);
        }

        void rotateWithLeftChild(Node*& k2)
        {
            Node* k1 = k2->left_;
            k2->left_ = k1->right_;
            k1->right_ = k2;
            k2->height_ = max(height(k2->left_), height(k2->right_)) + 1;
            k2->balance_factor_ = height(k2->right_) - height(k2->left_);
            k1->height_ = max(height(k1->left_), k2->height_) + 1;
            k1->balance_factor_ = height(k1->right_) - height(k1->left_);
            k2 = k1;
        }

        void rotateWithRightChild(Node*& k1)
        {
            Node* k2 = k1->right_;
            k1->right_ = k2->left_;
            k2->left_ = k1;
            k1->height_ = max(height(k1->left_), height(k1->right_)) + 1;
            k1->balance_factor_ = height(k1->right_) - height(k1->left_);
            k2->height_ = max(height(k2->right_), k1->height_) + 1;
            k2->balance_factor_ = height(k2->right_) - height(k2->left_);
            k1 = k2;
        }

        void doubleWithLeftChild(Node*& k3)
        {
            rotateWithRightChild(k3->left_);
            rotateWithLeftChild(k3);
        }

        void doubleWithRightChild(Node*& k1)
        {
            rotateWithLeftChild(k1->right_);
            rotateWithRightChild(k1);
        }

        friend class AVLTree<Key, Value>;
    };

private:
    Node* root_;
    int size_;

public:
    AVLTree() : root_(nullptr), size_(0) {}

    ~AVLTree()
    {
        delete root_;
    }

    Value& operator[](const Key& key) {
 
        if (root_ == nullptr) { 
            root_ = new Node(key);
            size_++;
            return root_->value_; 
        }
        else { 
            auto& value = root_->helper(key, size_, root_);
            root_->balance(root_);
            root_->balance_factor_ = root_->height(root_->right_) - root_->height(root_->left_);
            return value;
        }
    }

    int size() {
        return size_;
    }

    Node* root() {
        return root_;
    }
};