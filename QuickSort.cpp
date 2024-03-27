// Implementation of quicksort https://en.wikipedia.org/wiki/Quicksort
#include <iostream>
#include <vector>
#include <list>
#include <cassert>

// Function prototypes
template<typename Iter>
void quickSort(Iter begin, Iter end);

template <typename Iter>
Iter Partition(Iter begin, Iter end);

template <typename Iter>
Iter medianOf3(Iter begin, Iter end);

template <typename Iter>
void sort2(Iter begin, Iter end);

template <typename Iter>
void sort3(Iter begin, Iter end);

// Sorts a range of elements using the Quick Sort algorithm.
template<typename Iter>
void quickSort(Iter begin, Iter end)
{
    if (std::distance(begin, end) < 4)
	{
		if (std::distance(begin, end) == 3){ sort3(begin, end);} // More efficient to manually sort 2 or 3 elements than recurse
		else if (std::distance(begin, end) == 2){ sort2(begin, end);}
		return; // Partitions of size less than 2 are sorted
	}

    Iter pi = Partition(begin, end); // pi is partition index
    quickSort(begin, pi);
    quickSort(std::next(pi), end);
}

// Partition function for Quicksort
template <typename Iter>
Iter Partition(Iter begin, Iter end)
{
    Iter lft = begin; // Initialize left index
    Iter rgt = std::prev(end); // Initialize right index
	auto pivot = *medianOf3(lft, rgt);

    while(true) 
	{
		while (*lft < pivot)
		{
			lft++;
		}

		while(*rgt > pivot)
		{
			rgt--;
		}

		if(std::distance(lft, rgt) <= 0)
		{
            return rgt;
        }
		
		// Check if left and right point to equal elements
		// This check isn't needed if input has no duplicates
		if(*lft == *rgt)
		{
			std::advance(lft, 1);
		}
		else
        {
			std::iter_swap(lft, rgt);
		}
    }
}

// @return Median value among the first, middle and last element
// @param end Points to the last element, not one after the last (which std::end() does)
template <typename Iter>
Iter medianOf3(Iter begin, Iter end)
{
	// General formula for mid point is [begin + (end - begin) / 2]
	Iter mid = std::next(begin, std::distance(begin, end) /2);
	
	if((*begin <= *mid && *mid <= *end) || (*begin >= *mid && *mid >= *end))
	{
		return mid;
	}
	else if((*mid <= *begin && *begin <= *end) || (*mid >= *begin && *begin >= *end))
	{
		return begin;
	}
	else
	{
		return end;
	}
}

// Manually sort 2 elements into ascending order
template <typename Iter>
void sort2(Iter begin, Iter end)
{
	std::advance(end, -1);
	if(*end < *begin)
	{
		std::iter_swap(begin, end);
	}
	assert(*begin <= *end);
}

// Manually sort 3 elements into ascending order
template <typename Iter>
void sort3(Iter begin, Iter end)
{
	std::advance(end, -1);
	auto mid = std::next(begin);
	assert(std::next(mid) == end);
	if(*begin > *end)
	{
		std::iter_swap(begin, end);
	}
	if(*begin > *mid)
	{
		std::iter_swap(begin, mid);
	}
	if(*mid > *end)
	{
		std::iter_swap(mid, end);
	}
	assert(*begin <= *mid && *mid <= *end);
}

// Quicksort tests
// Test case 1: empty vector
void testEmptyRange()
{
    std::vector<int> vec;  // Empty vector
    quickSort(vec.begin(), vec.end());
    assert(vec.size() == 0);
}

// Test case 2: vector with only one element.
void testSingleElementRange()
{
    std::vector<int> vec = {42};  // Single-element vector
    quickSort(vec.begin(), vec.end());
    assert(vec.size() == 1);
    assert(vec[0] == 42);
}

// Test case 3: vector where elements are already sorted
void testSortedRange()
{
    std::vector<int> vec = {1, 2, 3, 4, 5};  // Sorted vector
    quickSort(vec.begin(), vec.end());
    assert((vec == std::vector<int>{1, 2, 3, 4, 5}));
}

// Test case 4: vector where elements are sorted in descending order.
void testReverseSortedRange()
{
    std::vector<int> vec = {5, 4, 3, 2, 1};  // Reverse-sorted vector
    quickSort(vec.begin(), vec.end());
    assert((vec == std::vector<int>{1, 2, 3, 4, 5}));
}

// Test case 5: vector with random ints
void testRandomdRangeInt()
{
    std::vector<int> vec = {3, 1, 4, -2, 5};  // Random vector
    quickSort(vec.begin(), vec.end());
    assert((vec == std::vector<int>{-2, 1, 3, 4, 5}));
}

// Test case 6: vector with random chars
void testRandomRangeChar()
{
    std::vector<char> vec = {'c', 'b', 'a', 'z', 'x', 'y'};  // Random vector
    quickSort(vec.begin(), vec.end());
    assert((vec == std::vector<char>{'a', 'b', 'c', 'x', 'y', 'z'}));
}

// Test case 7: vector with random ints and duplicates
void testDuplicateElements()
{
    std::vector<int> vec = {3, 1, 4, 2, 1, 5, 4};  // Vector with duplicates
    quickSort(vec.begin(), vec.end());
    assert((vec == std::vector<int>{1, 1, 2, 3, 4, 4, 5}));
}

// Test case 8: vector with all duplicates, odd length
void allDupsOdd()
{
    std::vector<int> vec(5, 10);  // Odd length vector of duplicates
    quickSort(vec.begin(), vec.end());
    assert(vec == std::vector<int>(5, 10));
}

// Test case 9: vector with all duplicates, even length
void allDupsEven()
{
    std::vector<int> vec(6, 10);  // Even length vector of duplicates
    quickSort(vec.begin(), vec.end());
    assert(vec == std::vector<int>(6, 10));
}

// Test case 10: list with random ints
void testRandomListSort()
{
    std::list<int> randomList = {30, 10, 50, 20, 40}; // Random list
    quickSort(randomList.begin(), randomList.end());
    assert((randomList == std::list<int>{10, 20, 30, 40, 50}));
}

// medianOf3 tests
// Test case 1: Three distinct elements
void test3Distinct() {
    std::vector<int> nums = {5, 2, 8};
    auto result = medianOf3(nums.begin(), std::prev(nums.end()));
    assert(*result == 5);
}

// Test case 2: Three equal elements
void test3Equal() {
    std::vector<int> nums = {4, 4, 4};
    auto result = medianOf3(nums.begin(), std::prev(nums.end()));
    assert(*result == 4);
}

// Test case 3: Ascending elements
void test3Ascending() {
    std::vector<int> nums = {1, 2, 3};
    auto result = medianOf3(nums.begin(), std::prev(nums.end()));
    assert(*result == 2);
}

// Test case 4: Descending elements
void test3Descending() {
    std::vector<int> nums = {6, 5, 4};
    auto result = medianOf3(nums.begin(), std::prev(nums.end()));
    assert(*result == 5);
}

// Test case 5: Six chars
void test6Chars() {
    std::vector<int> chars = {'x', 'y', 'z', 'a', 'b', 'c'};
    auto result = medianOf3(chars.begin(), std::prev(chars.end()));
    assert(*result == 'x');
}

// Test case 6: Descending negative elements
void test3DescNeg() {
    std::vector<int> nums = {-1, -2, -3};
    auto result = medianOf3(nums.begin(), std::prev(nums.end()));
    assert(*result == -2);
}

int main()
{
	std::cout << "Started" << std::endl;
	
	test3Distinct();
	std::cout << "Median of 3 test 1 passed" << std::endl;
	test3Equal();
	std::cout << "Median of 3 test 2 passed" << std::endl;
	test3Ascending();
	std::cout << "Median of 3 test 3 passed" << std::endl;
	test3Descending();
	std::cout << "Median of 3 test 4 passed" << std::endl;
	test6Chars();
	std::cout << "Median of 3 test 5 passed" << std::endl;
	test6Chars();
	std::cout << "Median of 3 test 5 passed" << std::endl;
	test3DescNeg();
	std::cout << "Median of 3 test 6 passed" << std::endl;
	
	testEmptyRange();
	std::cout << "Quicksort test 1 passed" << std::endl;
	testSingleElementRange();
	std::cout << "Quicksort test 2 passed" << std::endl;
	testSortedRange();
	std::cout << "Quicksort test 3 passed" << std::endl;
	testReverseSortedRange();
	std::cout << "Quicksort test 4 passed"	<< std::endl;
	testRandomdRangeInt();
	std::cout << "Quicksort test 5 passed" << std::endl;
	testRandomRangeChar();
	std::cout << "Quicksort test 6 passed" << std::endl;
	testDuplicateElements();
	std::cout << "Quicksort test 7 passed" << std::endl;
	void allDupsOdd();
	std::cout << "Quicksort test 8 passed" << std::endl;
	void allDupsEven();
	std::cout << "Quicksort test 9 passed" << std::endl;
	testRandomListSort();
	std::cout << "Quicksort test 10 passed" << std::endl;
	std::cout << "Completed" << std::endl;
	
	return 0;
}