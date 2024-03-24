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

// Sorts a range of elements using the Quick Sort algorithm.
template<typename Iter>
void quickSort(Iter begin, Iter end)
{
	// Containers of size less than 2 are sorted
    if (std::distance(begin, end) < 2)
	{
		return;
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
    Iter rgt = std::prev(end);     // Initialize right index
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

// Select median between 3 elements
template <typename Iter>
Iter medianOf3(Iter begin, Iter end)
{
	// General formula for mid point is [begin + (end - begin) / 2]
	Iter mid = std::next(begin, std::distance(begin, end) /2);
	
	if(*begin <= *mid && *mid <= *end)
	{
		return mid;
	}
	else if(*mid <= *begin && *begin <= *end)
	{
		return begin;
	}
	else
	{
		return end;
	}
}


// Test 1: empty vector
void testEmptyRange()
{
    std::vector<int> vec;  // Empty vector
    quickSort(vec.begin(), vec.end());
    assert(vec.size() == 0);
}

// Test 2: vector with only one element.
void testSingleElementRange()
{
    std::vector<int> vec = {42};  // Single-element vector
    quickSort(vec.begin(), vec.end());
    assert(vec.size() == 1);
    assert(vec[0] == 42);
}

// Test 3: vector where elements are already sorted
void testSortedRange()
{
    std::vector<int> vec = {1, 2, 3, 4, 5};  // Sorted vector
    quickSort(vec.begin(), vec.end());
    assert((vec == std::vector<int>{1, 2, 3, 4, 5}));
}

// Test 4: vector where elements are sorted in descending order.
void testReverseSortedRange()
{
    std::vector<int> vec = {5, 4, 3, 2, 1};  // Reverse-sorted vector
    quickSort(vec.begin(), vec.end());
    assert((vec == std::vector<int>{1, 2, 3, 4, 5}));
}

// Test 5: vector with random ints
void testRandomdRangeInt()
{
    std::vector<int> vec = {3, 1, 4, -2, 5};  // Random vector
    quickSort(vec.begin(), vec.end());
    assert((vec == std::vector<int>{-2, 1, 3, 4, 5}));
}

// Test 6: vector with random chars
void testRandomRangeChar()
{
    std::vector<char> vec = {'c', 'b', 'a', 'z', 'x', 'y'};  // Random vector
    quickSort(vec.begin(), vec.end());
    assert((vec == std::vector<char>{'a', 'b', 'c', 'x', 'y', 'z'}));
}

// Test 7: vector with random ints and duplicates
void testDuplicateElements()
{
    std::vector<int> vec = {3, 1, 4, 2, 1, 5, 4};  // Vector with duplicates
    quickSort(vec.begin(), vec.end());
    assert((vec == std::vector<int>{1, 1, 2, 3, 4, 4, 5}));
}

// Test 8: vector with all duplicates, odd length
void allDupsOdd()
{
    std::vector<int> vec(5, 10);  // Odd length vector of duplicates
    quickSort(vec.begin(), vec.end());
    assert(vec == std::vector<int>(5, 10));
}

// Test 9: vector with all duplicates, even length
void allDupsEven()
{
    std::vector<int> vec(6, 10);  // Even length vector of duplicates
    quickSort(vec.begin(), vec.end());
    assert(vec == std::vector<int>(6, 10));
}

// Test 10: list with random ints
void testRandomListSort()
{
    std::list<int> randomList = {30, 10, 50, 20, 40}; // Random list
    quickSort(randomList.begin(), randomList.end());
    assert((randomList == std::list<int>{10, 20, 30, 40, 50}));
}



int main()
{
	std::cout << "Started" << std::endl;
	testEmptyRange();
	std::cout << "Test 1 passed" << std::endl;
	testSingleElementRange();
	std::cout << "Test 2 passed" << std::endl;
	testSortedRange();
	std::cout << "Test 3 passed" << std::endl;
	testReverseSortedRange();
	std::cout << "Test 4 passed"	<< std::endl;
	testRandomdRangeInt();
	std::cout << "Test 5 passed" << std::endl;
	testRandomRangeChar();
	std::cout << "Test 6 passed" << std::endl;
	testDuplicateElements();
	std::cout << "Test 7 passed" << std::endl;
	void allDupsOdd();
	std::cout << "Test 8 passed" << std::endl;
	void allDupsEven();
	std::cout << "Test 9 passed" << std::endl;
	testRandomListSort();
	std::cout << "Test 10 passed" << std::endl;
	std::cout << "Completed" << std::endl;
	
	return 0;
}