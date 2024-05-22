#include <iostream>
#include <thread>
#include <future>
#include <random>

void thread_function(int n, const char* name, double* arr1, double* arr2) {
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(1.0, 10.0);

    for (int i = 0; i < n; ++i) {
        std::cout << name << ":" << std::endl;
        double num1 = arr1[i];
        double num2 = arr2[i];
        std::cout << "Operand 1: " << num1 << std::endl;
        std::cout << "Operand 2: " << num2 << std::endl;
        double result = num1 * num2;
        std::cout << "Result: " << result << std::endl;
        std::cout << std::endl;
    }
}

int main() {
    const int n1 = 2;
    const int n2 = 2;
    const int n3 = 2;

    double arr1[n1];
    double arr2[n1];

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(1.0, 10.0);

    for (int i = 0; i < n1; ++i) {
        arr1[i] = distribution(generator);
        arr2[i] = distribution(generator);
    }

    std::future<void> future1 = std::async(std::launch::async, thread_function, n1, "thread1", arr1, arr2);
    std::future<void> future2 = std::async(std::launch::async, thread_function, n2, "thread2", arr1, arr2);
    std::future<void> future3 = std::async(std::launch::async, [](int n) {
        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution(1.0, 10.0);

        for (int i = 0; i < n; ++i) {
            std::cout << "thread3:" << std::endl;
            double random_value = distribution(generator);
            std::cout << "Random value: " << random_value << std::endl;
            std::cout << std::endl;
        }
        }, n3);

    future1.get();
    future2.get();
    future3.get();

    std::cout << "Main thread has finished." << std::endl;

    return 0;
}
