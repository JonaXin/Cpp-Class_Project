#pragma once
#include <memory>

namespace nonstd {

    template <typename T>
    class MultiSet {
    public:
        class Node {
        private:
            T value_;
            int count_;
            //std::unique_ptr<Node> left_, right_;
            Node* left_, * right_;
            Node(const T& value) : value_(value), count_(1), left_(nullptr), right_(nullptr) {}
        public:
            ~Node() {
                delete left_;
                delete right_;
            }

            Node* left() {
                return left_;
            }
            Node* right() {
                return right_;
            }
            const T& value() const {
                return value_;
            }

            void insert(const T& value) {
                if (value == value_)
                    count_++;
                else if (value < value_)
                {
                    if (left_ == nullptr)
                        left_ = new Node(value);
                    else {
                        left_->insert(value);
                    }
                }
                else {
                    if (right_ == nullptr)
                        right_ = new Node(value);
                    else {
                        right_->insert(value);
                    }
                }
            }

            int count(const T& value)
            {
                if (value == value_)
                    return count_;
                else if (value < value_)
                {
                    if (left_ == nullptr)
                        return 0;
                    else {
                        return left_->count(value);
                    }
                }
                else {
                    if (right_ == nullptr)
                        return 0;
                    else {
                        return right_->count(value);
                    }
                }
            }

            bool contains(const T& value)
            {
                if (value == value_)
                    return true;
                else if (value < value_)
                {
                    if (left_ == nullptr)
                        return false;
                    else {
                        return left_->contains(value);
                    }
                }
                else {
                    if (right_ == nullptr)
                        return false;
                    else {
                        return right_->contains(value);
                    }
                }
            }

            friend class MultiSet<T>;
        };

    private:
        //std::unique_ptr<Node> root_;
        Node* root_;
        int size_;

    public:
        MultiSet() : root_(nullptr), size_(0) {}

        ~MultiSet() {
            delete root_;
        }

        void insert(const T& value) {
            if (root_ == nullptr) {
                root_ = new Node(value);
                size_++;
            }
            else {
                root_->insert(value);
                size_++;
            }
        }

        int count(const T& value) const {
            if (root_ == nullptr) {
                return 0;
            }
            else {
                return root_->count(value);
            }
        }

        bool contains(const T& value) const {
            if (root_ == nullptr) {
                return false;
            }
            else {
                return root_->contains(value);
            }
        }

        int size() const {
            return size_;
        }

        Node* root() {
            return root_;
        }
    };

}