// Implementation of binary search https://en.wikipedia.org/wiki/Binary_search_algorithm
#include <iostream>
#include <vector>
#include <set>
#include <list>

// Return iterator pointing to the location where target was found. If target was not found, the location of where it would be is returned.
template <typename ForwardIt, typename T>
ForwardIt binary_search_position(ForwardIt first, ForwardIt last, const T target)
{
	// Container has 0 or 1 elements
	if(first == last || std::next(first) == last)
	{
		return first;
	}
	
	// Move iterator to point to last element
	last--;
		
	while(first != last)
	{
		// Calculate the mid point between first and last
		auto mid = first;
		std::advance(mid, std::distance(first, std::next(last)) / 2);// Calling next on last is to cause rounding up in the case the distance is odd
		std::cout << "first: " << *first << " mid: " << *mid << " last: " << *last << std::endl;
		if(*mid > target)
		{
			last = std::prev(mid);
		}
		else
		{
			first = mid;
		}
	}
	if(*last == target)
	{
		return last;
	}
	else
	{
		// Target not found, return iterator to position where target would go
		return std::next(last);
	}
}

// Test 1: Odd length vector
void test_multiple_elements_odd()
{
	std::vector<int> odd = {2, 8, 13, 25, 30};
	for(const auto target : odd)
	{
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
}

// Test 2: Even length vector
void test_multiple_elements_even()
{
	std::vector<int> even = {0, 2, 8, 13, 25, 30};
	for(const auto target : even)
	{
		auto result = binary_search_position(even.begin(), even.end(), target);
		if(*result == target)
		{
			std::cout << "Test 2 (even length vector with multiple elements): Passed" << std::endl;
		}
		else
		{
			std::cout << "Test 2 (even length vector with multiple elements): Failed. Expected " << target << ", Actual: " << *result << std::endl;
		}
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
	if(result == empty_vec.begin() && result == empty_vec.end())
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
	//first test
	std::vector<int> v1 = {2, 4, 6, 8, 9};
	const auto target = 7;
	auto result = binary_search_position(v1.begin(), v1.end(), target);
	if(*result == 8)
	{
		std::cout << "Test 5 (Value not present): Passed" << std::endl;
	}
	else
	{
		std::cout << "Test 5 (Value not present): Failed, Actual " << *result << std::endl;
	}
	
	//second test
	v1 = {0, 2, 4, 6, 8, 9};
	result = binary_search_position(v1.begin(), v1.end(), target);
	if(*result == 8)
	{
		std::cout << "Test 5 (Value not present): Passed" << std::endl;
	}
	else
	{
		std::cout << "Test 5 (Value not present): Failed. Expected 8, Actual " << *result << std::endl;
	}
	
	//third test
	std::vector<char> v2 = {'a', 'b', 'd', 'e', 'f'};
	const auto t2 = 'c';
	auto result2 = binary_search_position(v2.begin(), v2.end(), t2);
	if(*result2 == 'd')
	{
		std::cout << "Test 5 (Value not present): Passed" << std::endl;
	}
	else
	{
		std::cout << "Test 5 (Value not present): Failed. Expected 'd', Actual " << *result << std::endl;
	}
}

// Test 6: Vector of doubles
void test_vector_double()
{
	std::vector<double> vec = {-2.1, 1.1, 3.5, 3.7, 4.1};
	for(const auto target : vec)
	{
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
}

// Test 7: Set of strings
void test_set_string()
{
	std::set<std::string> testSet = {"apples", "bananas", "onions", "oranges"};
	for(const auto target : testSet)
	{
		auto lastElmenetIterator = testSet.end();
		lastElmenetIterator--;
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
}

// Test 8: List of ints
void test_list_int()
{
	std::list<int> testList = {-10, 10, 20, 20, 30, 30, 40, 50};
	for(const auto target : testList)
	{
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
}

int main()
{
	std::cout << "Binary search tests started" << std::endl;
	
	test_multiple_elements_odd();
	test_multiple_elements_even();
	test_single_element();
	test_empty();
	test_value_not_present();
	test_vector_double();
	test_set_string();
	test_list_int();
	
	return 0;
}