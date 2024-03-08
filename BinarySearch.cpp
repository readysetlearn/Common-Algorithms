// Implementation of binary search https://en.wikipedia.org/wiki/Binary_search_algorithm
#include <iostream>

// Return iterator pointing to the location where target was found
template <typename ForwardIt, typename T>
ForwardIt binary_search_position(ForwardIt first, ForwardIt last, const T target);

int main()
{
	std::cout << "Binary search started" << std::endl;
	return 0;
}