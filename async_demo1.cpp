#include <future>
#include <iostream>
/*
    A   B   C

    option a : one after the other. always complete one thing before starting the next task
    (single thread technique)

    option b : I will complete  all tasks in such a way that I practically start all of them at the same time but keep juggling them based on some criteria
    (multi thread technique)

    option c : map number of taks amongst number of available workers
    (parallel execution)

    option d : start a task, either delegate it to another worker or do it yourself after some time
    (asynchronous execution)
*/

/*
    2 tasks
    calculate factorial of 5
    calculate square of a number given by the user
*/

int square(std::future<int> &ft)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "hello from square, work started"
              << "\n";
    int number = ft.get();
    return number * number;
}

int factorial(int number)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    if (number < 0)
    {
        throw std::runtime_error("negative number error");
    }
    else if (number == 0 || number == 1)
    {
        return 1;
    }
    else
    {
        return number * factorial(number - 1);
    }
}

int main(){
    //step 1 : makes a promise
    std::promise<int> pr;

    //step 2 : a future linked to the promise
    std::future<int> ft = pr.get_future();
    /*
        OS : launch square(if possible as a new thread)
    */
    std::future<int> result_ft = std::async(std::launch::async, &square, std::ref(ft));
    std::cout << factorial(5) << "\n";
    int val = 0;
    std::cin >> val;
    pr.set_value(val);
    std::cout << "result of factorial is " << result_ft.get()
              << "\n";
}
