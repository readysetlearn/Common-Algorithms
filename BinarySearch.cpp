// Implementation of binary search https://en.wikipedia.org/wiki/Binary_search_algorithm
#include <iostream>
#include <vector>
#include <cassert>

// Return iterator pointing to the location where target was found. If target was not found, the location of where it would be is returned.
template <typename ForwardIt, typename T>
ForwardIt binary_search_position(ForwardIt first, ForwardIt last, const T target)
{
	// To implement
}

// Test 1: Odd length vector
void test_multiple_elements_odd()
{
	std::vector<int> odd = {2, 8, 13, 25, 30};
	const auto target = 13;
	auto result = binary_search_position(odd.begin(), odd.end(), target);
	if(*result == target)
	{
		std::cout << "Test 1 (odd length vector with multiple elements): Passed" << std::endl;
	}
	else
	{
		std::cout << "Test 1 (odd length vector with multiple elements): Failed. Expected " << target << ", Actual: " << *result << std::endl;
	}
}

// Test 2: Even length vector
void test_multiple_elements_even()
{
	std::vector<int> even = {0, 2, 8, 13, 25, 30};
	const auto target = 13;
	auto result = binary_search_position(even.begin(), even.end(), target);
	if(*result == target)
	{
		std::cout << "Test 2 (even length vector with multiple elements): Passed" << std::endl;
	}
	else
	{
		std::cout << "Test 2 (event length vector with multiple elements): Failed. Expected " << target << ", Actual: " << *result << std::endl;
	}
}

// Test 3: Vector with a single element
void test_single_element()
{
	std::vector<int> sorted_range = {5};
	const auto target = 5;
	auto result = binary_search_position(sorted_range.begin(), sorted_range.end(), target);
	if(*result == target)
	{
		std::cout << "Test 3 (vector with a single element): Passed" << std::endl;
	}
	else
	{
		std::cout << "Test 3 (vector with a single element): Failed. Expected " << target << ", Actual: " << *result << std::endl;
	}
}

// Test 4: Empty vector
void test_empty()
{
	std::vector<int> empty_vec = {};
	auto result = binary_search_position(empty_vec.begin(), empty_vec.end(), 5);
	if(result == empty_vec.begin())
	{
		std::cout << "Test 4 (empty vector): Passed" << std::endl;
	}
	else
	{
		std::cout << "Test 4 (empty vector): Failed." << std::endl;
	}
}

// Test 5: Value not present
void test_value_not_present()
{
	std::vector<int> vec = {2, 4, 6, 8, 9};
	const auto target = 5;
	auto result = binary_search_position(vec.begin(), vec.end(), target);
	if(result == vec.end())
	{
		std::cout << "Test 5 (Value not present): Passed" << std::endl;
	}
	else
	{
		std::cout << "Test 5 (Value not present): Failed" << std::endl;
	}
}

int main()
{
	std::cout << "Binary search tests started" << std::endl;
	
	return 0;
}