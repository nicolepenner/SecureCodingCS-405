// 2-3 BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>

int main()
{
	std::cout << "Buffer Overflow Example" << std::endl;

	// TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
	//  even though it is a constant and the compiler buffer overflow checks are on.
	//  You need to modify this method to prevent buffer overflow without changing the account_order
	//  variable, and its position in the declaration. It must always be directly before the variable used for input.

	const std::string account_number = "CharlieBrown42";
	char user_input[20];
	std::cout << "Enter a value: ";
	
	//Unsafe, left room for overflow which is what we are trying to avoid
	// std::cin >> user_input;


	// Getline limits the amount of input using only one line of code
	// use cin.fail()  used to detect if there are more characters entered than
	// the 20 character limit we need to impose
	std::cin.getline(user_input, 20);
	if (std::cin.fail()) {
		std::cout << "Detected a potential overflow! The input has been limited to 20 characters!" << std::endl;
	}


	std::cout << "You entered: " << user_input << std::endl;
	std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
