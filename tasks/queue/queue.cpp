#include "queue.h"

Node::Node(int32_t value, Node* next) : value(value), next(next) {
}
Queue::Queue() : front_(nullptr), tail_(nullptr), size_(0) {
}
Queue::~Queue() {
    Clear();
}
int32_t Queue::Size() const {
    return size_;
}
void Queue::Pop() {
    if (Empty()) {
        return;
    }
    Node* next = front_->next;
    delete front_;
    front_ = next;
    if (size_ == 1) {
        tail_ = nullptr;
    }
    --size_;
}
void Queue::Clear() {
    while (!Empty()) {
        Pop();
    }
}
bool Queue::Empty() const {
    return size_ == 0;
}
int32_t Queue::Front() const {
    return front_->value;
}
void Queue::Push(int32_t value) {
    Node* prev_tail = tail_;
    tail_ = new Node(value, nullptr);
    if (!Empty()) {
        prev_tail->next = tail_;
    } else {
        front_ = tail_;
    }
    ++size_;
}