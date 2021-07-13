#ifndef CHESSMULTIPLAYER_THREADSAFEQUEUE_H
#define CHESSMULTIPLAYER_THREADSAFEQUEUE_H

#include <queue>
#include <mutex>

namespace poler::net {
    template <typename T>
    class ThreadSafeQueue {
    public:
        ThreadSafeQueue() = default;
        ThreadSafeQueue(const ThreadSafeQueue& q) = delete;

        [[nodiscard]] bool isEmpty() {
            std::scoped_lock lock(mtx_);
            return q_.empty();
        };

        void push(const T& a) {
            std::scoped_lock lock(mtx_);
            q_.push(a);
        };

        void pop() {
            std::scoped_lock lock(mtx_);
            q_.pop();
        };

        [[nodiscard]] const T& front() {
            std::scoped_lock lock(mtx_);
            return q_.front();
        };

        [[nodiscard]] const T& back() const {
            std::scoped_lock lock(mtx_);
            return q_.back();
        };

        [[nodiscard]] size_t size() const {
            std::scoped_lock lock(mtx_);
            return q_.size();
        }

    private:
        std::queue<T> q_;
        std::mutex mtx_;
    };
}

#endif //CHESSMULTIPLAYER_THREADSAFEQUEUE_H
