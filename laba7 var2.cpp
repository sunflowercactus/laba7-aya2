#include <iostream>
#include <thread>
#include <random>
#include <mutex>
using namespace std;

void thread_function(int n, const char* name, double* arr1, double* arr2) {
    default_random_engine generator;
    uniform_real_distribution<double> distribution(1.0, 10.0);

    for (int i = 0; i < n; ++i) {
        cout << name << ":" << std::endl;
        double num1 = arr1[i];
        double num2 = arr2[i];
        cout << "Operand 1: " << num1 << std::endl;
        cout << "Operand 2: " << num2 << std::endl;
        double result = num1 + num2;
        cout << "Result: " << result << std::endl;
        cout << std::endl;
    }
}

int main() {
    const int n1 = 2;
    const int n2 = 2;
    const int n3 = 2;

    double arr1[n1];
    double arr2[n1];

    default_random_engine generator;
    uniform_real_distribution<double> distribution(1.0, 10.0);

    for (int i = 0; i < n1; ++i) {
        arr1[i] = distribution(generator);
        arr2[i] = distribution(generator);
    }

    thread thread1(thread_function, n1, "thread1", arr1, arr2);
    thread thread2(thread_function, n2, "thread2", arr1, arr2);

    default_random_engine generator2;
    uniform_real_distribution<double> distribution2(1.0, 10.0);

    thread thread3([n3]() {
        default_random_engine generator;
        uniform_real_distribution<double> distribution(1.0, 10.0);

        for (int i = 0; i < n3; ++i) {
            cout << "thread3:" << std::endl;
            double random_value = distribution(generator);
            cout << "Random value: " << random_value << std::endl;
            cout << std::endl;
        }
        });

    thread1.join();
    thread2.join();
    thread3.join();

    cout << "Main thread has finished." << std::endl;

    return 0;
}
