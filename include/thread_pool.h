#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <functional>
#include <memory>
#include <atomic>
#include <condition_variable>


namespace lrrp
{
    template <typename T>
    class thread_pool {
    private:
        std::queue<T> tasks;
        std::function<void(T&&)> worker;

        std::vector<std::thread> threads;
        std::atomic<bool> should_stop;
        std::mutex task_mutex;
        std::condition_variable condition;

        void run_thread() {
            while (!should_stop) {
                std::unique_lock<std::mutex> lock(task_mutex);
                condition.wait(lock, [this] { return !tasks.empty() || should_stop; });

                if (should_stop) {
                    break;
                }

                T task = std::move(tasks.front());
                tasks.pop();
                lock.unlock();

                worker(std::move(task));
            }
        }
    public:
        thread_pool(int num_threads) {
            should_stop = false;
            for (int i = 0; i < num_threads; i++) {
                threads.push_back(std::thread(&thread_pool::run_thread, this));
            }
        }

        void set_worker(std::function<void(T&&)> worker) {
            this->worker = worker;
        }

        void enqueue(T&& task_param) {
            {
                std::unique_lock<std::mutex> lock(task_mutex);
                tasks.push(std::move(task_param));
            }
            condition.notify_one();
        }

        void stop() {
            should_stop = true;
            condition.notify_all();
        }

        int workers_count() {
            return threads.size();
        }

        int tasks_count() {
            return tasks.size();
        }

        bool is_full() {
            return tasks_count() >= threads.size();
        }
    };
}
