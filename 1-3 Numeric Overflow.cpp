// NumericOverflows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits

/// <summary>
/// Template function to abstract away the logic of:
///   start + (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to add each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start + (increment * steps)</returns>
template <typename T>
T add_numbers(T const& start, T const& increment, unsigned long int const& steps)
{
    T result = start;

    for (unsigned long int i = 0; i < steps; ++i)
    {
        // Detect if an overflow would occur if result were to be incremented. If so, throw
        // an overflow error and stop the function's execution.
        if (increment > std::numeric_limits<T>::max() - result) {
            throw std::overflow_error("Overflow will occur");
        }

        result += increment;
    }

    return result;
}

/// <summary>
/// Template function to abstract away the logic of:
///   start - (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to subtract each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start - (increment * steps)</returns>

template <typename T>
T subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps)
{
    T result = start;

    for (unsigned long int i = 0; i < steps; ++i)
    {
        // Detect that an underflow is about to occur if we decrement result, and stop
        // execution by throwing an underflow error.
        if (decrement > result) {
            throw std::underflow_error("Underflow will occur");
        }
        result -= decrement;
    }

    return result;
}


//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{
    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we add each step (result should be: start + (increment * steps))
    const T increment = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";

    // Move the declaration of the `result` variable above the execution of add_numbers in case
    // the first call to that function fails.
    T result;

    // Try adding the numbers and catch an exception if an underflow occurs.
    try {
        // This will never trigger an overflow as we know the number of steps allowed to increment before
        // reaching the limit of the type.
        result = add_numbers<T>(start, increment, steps);

        // Report that an overflow did not occur and display the result of the addition operation.
        std::cout << "Overflow: False, Result: " << +result << std::endl;
    }
    catch (std::overflow_error& e) {
        // Report that an overflow occurred.
        std::cout << "Overflow: True" << std::endl;
    }

    std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";

    // Try adding the numbers and catch an exception if an underflow occurs.
    try {
        // This will trigger an overflow since we're purposely incrementing 1 step passed the type's limit.
        result = add_numbers<T>(start, increment, steps + 1);

        // Unlikely, but if an overflow did not occur here, report the overflow status and the result
        // of the addition operation.
        std::cout << "Overflow: False, Result: " << +result << std::endl;
    }
    catch (std::overflow_error& e) {
        // Report that an overflow occurred.
        std::cout << "Overflow: True" << std::endl;
    }

}

template <typename T>
void test_underflow()
{
    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we subtract each step (result should be: start - (increment * steps))
    const T decrement = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    std::cout << "\tSubtracting Numbers Without Underflow (" << +start << ", " << +decrement << ", " << steps << ") = ";

    // Move the declaration of the `result` variable above the execution of subtract_numbers in case
    // the first call to that function fails. Update the variable type as we know what subtract_numbers
    // will return.
    T result;

    // Try subtracting the numbers and catch an exception if an underflow occurs.
    try {
        // Subtract the numbers. This should never cause an underflow as we know the number of steps allowed.
        result = subtract_numbers<T>(start, decrement, steps);

        // Display that an underflow did not occur and display the result of the subtraction operation.
        std::cout << "Underflow: False, Result: " << +result << std::endl;
    }
    catch (std::underflow_error& e) {
        // Report that an underflow occurred.
        std::cout << "Underflow: True" << std::endl;
    }

    std::cout << "\tSubtracting Numbers With Underflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = ";

    // Try subtracting the numbers and catch an exception if an underflow occurs.
    try {
        // This should trigger an underflow since we're purposely going 1 step beyond the type's limit,
        // but for some reason if it didn't fail, display the result of the subtraction operation.
        result = subtract_numbers<T>(start, decrement, steps + 1);
        std::cout << "Underflow: False, Result: " << +result << std::endl;
    }
    catch (std::underflow_error& e) {
        // Report that an underflow occurred.
        std::cout << "Underflow: True" << std::endl;
    }
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    // unsigned integers
    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    // real numbers
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Undeflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    // unsigned integers
    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    // real numbers
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
    //  create a string of "*" to use in the console
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    // run the overflow tests
    do_overflow_tests(star_line);

    // run the underflow tests
    do_underflow_tests(star_line);

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
