// Implementation of quicksort https://en.wikipedia.org/wiki/Quicksort
#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <algorithm>

// Function prototypes
template<typename Iter>
void quickSort(Iter begin, Iter end);

template<typename Iter>
void qs(Iter begin, Iter end);

template <typename Iter>
Iter Partition(Iter begin, Iter end);

template <typename Iter>
Iter medianOf3(Iter begin, Iter end);

template<typename Iter>
void insertionSort(Iter begin, Iter end);

template <typename Iter>
void sort2(Iter begin, Iter end);

template <typename Iter>
void sort3(Iter begin, Iter end);


//Wrapper function to account for std::end returning past the end iterator
template<typename Iter>
void quickSort(Iter begin, Iter end)
{
	if(begin == end) return; // Empty vector
	qs(begin, std::prev(end));
}

// Sorts a range of elements using the Quick Sort algorithm.
template<typename Iter>
void qs(Iter begin, Iter end)
{
	while(std::distance(begin, end) > 0)
	{
		if (std::distance(begin, end) < 11)
		{
			if (std::distance(begin, end) == 2) // More efficient to manually sort 2 or 3 elements than recurse
			{
				sort3(begin, end);
				return;
			}
			else if (std::distance(begin, end) == 1)
			{
				sort2(begin, end);
				return;
			}
			else if (std::distance(begin, end) < 2) // Partitions of size less than 2 are sorted
			{ 
				return;
			}
			else
			{
				insertionSort(begin, end);
				return;
			}
		}
		Iter pi = Partition(begin, end); // pi is partition index
		if(std::distance(begin, pi) > std::distance(pi, end)) // recurse smaller partition first
		{
			qs(std::next(pi), end);
			end = std::prev(pi);
		}
		else
		{
			qs(begin, pi);
			begin = std::next(pi);
		}
	}
}

// Partition function for Quicksort
template <typename Iter>
Iter Partition(Iter begin, Iter end)
{
	Iter lft = begin; // Initialize left index
	Iter rgt = end; // Initialize right index
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

// @return Median value among the first, middle and last elements and sorts them into ascending order
// @param end Points to the last element, not one after the last (which std::end() does)
template <typename Iter>
Iter medianOf3(Iter begin, Iter end)
{
	// General formula for mid point is [begin + (end - begin) / 2]
	Iter mid = std::next(begin, std::distance(begin, end) / 2);
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
	return mid;
}

// Insertion sort is effective on small ranges
template<typename Iter>
void insertionSort(Iter begin, Iter end)
{
	assert(std::distance(begin, end) > 2 && std::distance(begin, end) < 11);
	for(auto i = std::next(begin); i != std::next(end); std::advance(i, 1))
	{
		std::rotate(std::upper_bound(begin, i, *i), i, std::next(i));
	}
}

// Manually sort 2 elements into ascending order
template <typename Iter>
void sort2(Iter begin, Iter end)
{
	//std::advance(end, -1);
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
// Functional test cases
// Test case 1: empty vector
void testEmptyRange()
{
	std::vector<int> vec;  // Empty vector
	quickSort(vec.begin(), (vec.end()));
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

// Quicksort tests
// Stress Test Cases
// Test 1: large vector with random longs
void testLongRand()
{
	std::vector<long> vec;
	vec.reserve(50010000); // Reserve memory for efficiency
	for(size_t i = -10000; i <= 50000000; i++)
	{
	  if(i % 5 == 0) vec.push_back(i - 20);
	  else if(i % 3 == 0) vec.push_back(i + 20);
	  else if(i % 7 == 0) vec.push_back(i + 1);
	  else vec.push_back(i);
	}
	
	quickSort(vec.begin(), vec.end());	
	assert(std::is_sorted(vec.begin(), vec.end()));
}

// Test 2: large vector of duplicates
void testLongDups()
{
	std::vector<long> vec;
	vec.reserve(100000);
	for(size_t i = 1; i <= vec.capacity(); i++)
	{
	  vec.push_back(321);
	}
	
	quickSort(vec.begin(), vec.end());
	assert(std::is_sorted(vec.begin(), vec.end()));
}

// Test 3: large vector in ascending order
void testAscending()
{
	std::vector<int> ascendingVec;
    ascendingVec.reserve(100000000);

    for (size_t i = 1; i <= ascendingVec.capacity(); i++)
	{
        ascendingVec.push_back(i);
    }
	
	quickSort(ascendingVec.begin(), ascendingVec.end());
	assert(std::is_sorted(ascendingVec.begin(), ascendingVec.end()));
}

// Test 4: large vector in descending order
void testDescending()
{
	std::vector<int> descendingVec;
    descendingVec.reserve(100000000);

    for (size_t i = descendingVec.capacity(); i <= 1; i--)
	{
        descendingVec.push_back(i);
    }
	
	quickSort(descendingVec.begin(), descendingVec.end());
	assert(std::is_sorted(descendingVec.begin(), descendingVec.end()));
}

// Test 5: large vector with adjacent elements alternating between positive and negative
void testAlternating2()
{
	std::vector<int> alternatingVec;
    alternatingVec.reserve(10000000);

    for (size_t i = 1; i <= alternatingVec.capacity(); i++)
	{
		int value = (i % 2 == 0) ? -i : i;
		alternatingVec.push_back(value);
    }
	
	quickSort(alternatingVec.begin(), alternatingVec.end());
	assert(std::is_sorted(alternatingVec.begin(), alternatingVec.end()));
}

// Test 6: large vector, mostly ascending except every 10th element is negative
void testAlternating10()
{
	std::vector<int> ascendingVec;
    ascendingVec.reserve(1000000);

    for (size_t i = 1; i <= ascendingVec.capacity(); i++) {
        int value = (i % 10 == 0) ? -i : i;
        ascendingVec.push_back(value);
    }
	
	quickSort(ascendingVec.begin(), ascendingVec.end());
	assert(std::is_sorted(ascendingVec.begin(), ascendingVec.end()));
}


// medianOf3 functional test cases
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
	// Test pivot selection
	test3Distinct();
	std::cout << "Pivot selection test 1 passed" << std::endl;
	test3Equal();
	std::cout << "Pivot selection test 2 passed" << std::endl;
	test3Ascending();
	std::cout << "Pivot selection test 3 passed" << std::endl;
	test3Descending();
	std::cout << "Pivot selection test 4 passed" << std::endl;
	test6Chars();
	std::cout << "Pivot selection test 5 passed" << std::endl;
	test3DescNeg();
	std::cout << "Pivot selection test 6 passed" << std::endl;
	testEmptyRange();
	// Test correctness of QuickSort implementation
	std::cout << "Quicksort functional test 1 passed" << std::endl;
	testSingleElementRange();
	std::cout << "Quicksort functional test 2 passed" << std::endl;
	testSortedRange();
	std::cout << "Quicksort functional test 3 passed" << std::endl;
	testReverseSortedRange();
	std::cout << "Quicksort functional test 4 passed"	<< std::endl;
	testRandomdRangeInt();
	std::cout << "Quicksort functional test 5 passed" << std::endl;
	testRandomRangeChar();
	std::cout << "Quicksort functional test 6 passed" << std::endl;
	testDuplicateElements();
	std::cout << "Quicksort functional test 7 passed" << std::endl;
	allDupsOdd();
	std::cout << "Quicksort functional  test 8 passed" << std::endl;
	allDupsEven();
	std::cout << "Quicksort functional test 9 passed" << std::endl;
	testRandomListSort();
	std::cout << "Quicksort functional  test 10 passed" << std::endl;
	// Test speed of QuickSort implementation
	testLongRand();
	std::cout << "Quicksort stress test 1 passed" << std::endl;
	testLongDups();
	std::cout << "Quicksort stress test 2 passed" << std::endl;
	testAscending();
	std::cout << "Quicksort stress test 3 passed" << std::endl;
	testDescending();
	std::cout << "Quicksort stress test 4 passed" << std::endl;
	testAlternating2();
	std::cout << "Quicksort stress test 5 passed" << std::endl;
	testAlternating10();
	std::cout << "Quicksort stress test 6 passed" << std::endl;

	
	std::cout << "Completed" << std::endl;
	
	return 0;
}