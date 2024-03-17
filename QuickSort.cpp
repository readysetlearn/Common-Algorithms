// Implementation of quicksort https://en.wikipedia.org/wiki/Quicksort
#include <iostream>
#include <vector>
#include <list>
#include <cassert>

// Sorts a range of elements using the Quick Sort algorithm.
template<class iterator>
void quickSort(iterator begin, iterator end) {
    // Implementation details go here...
}

// Test an empty vector
void testEmptyRange() {
    std::vector<int> vec;  // Empty vector
    quickSort(vec.begin(), vec.end());
    assert(vec.size() == 0);
}

// Test a range with only one element.
void testSingleElementRange() {
    std::vector<int> vec = {42};  // Single-element vector
    quickSort(vec.begin(), vec.end());
    assert(vec.size() == 1);
    assert(vec[0] == 42);
}

// Test a range where elements are already sorted.
void testSortedRange() {
    std::vector<int> vec = {1, 2, 3, 4, 5};  // Sorted vector
    quickSort(vec.begin(), vec.end());
    assert((vec == std::vector<int>{1, 2, 3, 4, 5}));
}

// Test a range where elements are sorted in descending order.
void testReverseSortedRange() {
    std::vector<int> vec = {5, 4, 3, 2, 1};  // Reverse-sorted vector
    quickSort(vec.begin(), vec.end());
    assert((vec == std::vector<int>{1, 2, 3, 4, 5}));
}

// Test a range with random ints.
void testRandomdRangeInt() {
    std::vector<int> vec = {3, 1, 4, -2, 5};  // Random vector
    quickSort(vec.begin(), vec.end());
    assert((vec == std::vector<int>{-2, 1, 3, 4, 5}));
}

// Test a range with random chars.
void testRandomRangeChar() {
    std::vector<char> vec = {'c', 'b', 'a', 'z', 'x', 'y'};  // Random vector
    quickSort(vec.begin(), vec.end());
    assert((vec == std::vector<char>{'a', 'b', 'c', 'x', 'y', 'z'}));
}

// Test a range with duplicate elements.
void testDuplicateElements() {
    std::vector<int> vec = {3, 1, 4, 2, 1, 5, 4};  // Vector with duplicates
    quickSort(vec.begin(), vec.end());
    assert((vec == std::vector<int>{1, 1, 2, 3, 4, 4, 5}));
}

// Test sorting a list with random elements
template <class Iterator>
void testRandomListSort() {
    std::list<int> randomList = {30, 10, 50, 20, 40}; // Random list
    quickSort(randomList.begin(), randomList.end());
    assert((randomList == std::list<int>{10, 20, 30, 40, 50}));
}








int main()
{
	return 0;
}