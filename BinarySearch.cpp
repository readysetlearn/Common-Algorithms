// Implementation of binary search https://en.wikipedia.org/wiki/Binary_search_algorithm
#include <iostream>
#include <vector>
#include <set>
#include <list>

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

// Test 6: Vector of doubles
void test_vector_double()
{
	std::vector<double> vec = {-2.1, 1.1, 3.5, 3.7, 4.1};
	const auto target = 1.1;
	auto result = binary_search_position(vec.begin(), vec.end(), target);
	if(*result == target)
	{
		std::cout << "Test 6 (vector of doubles): Passed" << std::endl;
	}
	else
	{
		std::cout << "Test 6 (vector of doubles): Failed. Expected " << target << ", Actual: " << *result << std::endl;
	}
}

// Test 7: Set of strings
void test_set_string()
{
	std::set<std::string> testSet = {"apples", "oranges", "bananas", "onions"};
	const auto target = "onions";
	auto result = binary_search_position(testSet.begin(), testSet.end(), target);
	if(*result == target)
	{
		std::cout << "Test 7 (set of strings): Passed" << std::endl;
	}
	else
	{
		std::cout << "Test 7 (set of strings): Failed. Expected " << target << ", Actual: " << *result << std::endl;
	}
	
}

// Test 8: List of ints
void test_list_int()
{
	std::list<int> testList = {-10, 10, 20, 20, 30, 30, 40, 50};
	const auto target = 30;
	auto result = binary_search_position(testList.begin(), testList.end(), target);
	if(*result == target)
	{
		std::cout << "Test 8 (list of ints): Passed" << std::endl;
	}
	else
	{
		std::cout << "Test 8 (list of ints): Failed. Expected " << target << ", Actual: " << *result << std::endl;
	}
	
}

int main()
{
	std::cout << "Binary search tests started" << std::endl;
	
	return 0;
}