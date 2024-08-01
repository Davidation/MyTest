#include <coroutine>
#include <iostream>
#include <thread>

class IntReader {
public:
    bool await_ready() {
        return false;
    }

    void await_suspend(std::coroutine_handle<> handle) {

        std::thread thread([this, handle]() {

            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            value_ = std::rand();

            handle.resume();
        });

        thread.detach();
    }

    int await_resume() {
        return value_;
    }

private:
    int value_{};
};

class Task {
public:
    class promise_type {
    public:
        Task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        void return_void() {}
    };
};

Task PrintInt() {

    IntReader reader1;
    int total = co_await reader1;

    IntReader reader2;
    total += co_await reader2;

    IntReader reader3;
    total += co_await reader3;

    std::cout << total << std::endl;
}

int main() {

    PrintInt();

    std::string line;
    while (std::cin >> line) { }
    return 0;
}
