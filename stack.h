#pragma once

template <typename T>
struct Node {
    T data_;
    Node <T>* next_;

    Node(T data, Node <T>* next) {
        data_ = data;
        next_ = next;
    }
};

template <typename T>
class StackList {
public:
    StackList() : size_(0), top_(nullptr) {}

    ~StackList() {
        while (size())
            pop();
    }

    void push(const T el) {
        Node <T>* node = new Node <T>(el, top_);
        ++size_;
        top_ = node;
    }

    void pop() {
        --size_;
        Node <T>* node = top_;
        top_ = top_->next_;
        delete node;
    }

    T top() {
        return top_->data_;
    }

    unsigned int size() {
        return size_;
    }

    bool empty() {
        return size_ == 0;
    }

private:
    unsigned int size_;
    Node <T>* top_;
};