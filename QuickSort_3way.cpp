//Based on https://en.wikipedia.org/wiki/Quicksort#Repeated_elements
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>


// Function prototypes
template<typename T>
void quickSort(std::vector<T> &vec);

template<typename T>
void qs(std::vector<T> &vec, const typename std::vector<T>::size_type low, const typename std::vector<T>::size_type high);

template<typename T>
std::pair<typename std::vector<T>::size_type, typename std::vector<T>::size_type> partition(std::vector<T> &vec, const typename std::vector<T>::size_type low, const typename std::vector<T>::size_type high);

template<typename T>
T medianOf3(std::vector<T> &vec, const typename std::vector<T>::size_type low, const typename std::vector<T>::size_type high);

template<typename T>
void insertionSort(std::vector<T> &vec, const typename std::vector<T>::size_type low, const typename std::vector<T>::size_type high);

template <typename T>
void sort2(std::vector<T> &vec, const typename std::vector<T>::size_type low);

template <typename T>
void sort3(std::vector<T> &vec, const typename std::vector<T>::size_type low);


template<typename T>
void quickSort(std::vector<T> &vec)
{
	if(vec.size() > 0)
	{
		qs(vec, 0, vec.size() - 1);
	}
}

template<typename T>
void qs(std::vector<T> &vec, const typename std::vector<T>::size_type low, const typename std::vector<T>::size_type high)
{
	if(low >= 0 && low < high)
	{
		if(high - low == 1)
		{
			sort2(vec, low);
		}
		else if(high - low == 2)
		{
			sort3(vec, low);
		}
		else if(high - low < 10)
		{
			insertionSort(vec, low, high);
		}
		else
		{
			std::pair<typename std::vector<T>::size_type, typename std::vector<T>::size_type> partitionWalls = partition(vec, low, high);
			if(partitionWalls.first > 0)
			{
				qs(vec, low, partitionWalls.first - 1);
			}
			qs(vec, partitionWalls.second + 1, high);
		}
	}
}

template<typename T>
std::pair<typename std::vector<T>::size_type, typename std::vector<T>::size_type> partition(std::vector<T> &vec, const typename std::vector<T>::size_type low, const typename std::vector<T>::size_type high)
{
	assert(high < vec.size() && low >= 0);
	
	const auto pivot = medianOf3(vec, low, high);
	// Lesser, equal and grater indexes
	auto lt = low;
	auto eq = low;
	auto gt = high;
	
	// Iterate through elements and compare each with pivot
	while(eq <= gt)
	{
		if(vec.at(eq) < pivot)
		{
			std::swap(vec.at(eq), vec.at(lt));
			lt++;
			eq++;
		}
		else if(vec.at(eq) > pivot)
		{			std::swap(vec.at(eq), vec.at(gt));
			gt--;
		}
		else
		{
			eq++;
		}
	}
	return std::pair<typename std::vector<T>::size_type, typename std::vector<T>::size_type>(lt, gt);
}

// Sorts first, middle and last element into ascending order and return medium value
template<typename T>
T medianOf3(std::vector<T> &vec, const typename std::vector<T>::size_type low, const typename std::vector<T>::size_type high)
{
	if(high - low < 2)
	{
		return vec.at(low);
	}
	
	
	// Index of the middle element of the vector
	const typename std::vector<T>::size_type mid = low + (high - low) / 2;
	
	if(vec.at(low) > vec.at(high))
	{
		std::swap(vec.at(low), vec.at(high));
	}
	if(vec.at(low) > vec.at(mid))
	{
		std::swap(vec.at(low), vec.at(mid));
	}
	if(vec.at(mid) > vec.at(high))
	{
		std::swap(vec.at(mid), vec.at(high));
	}
	assert(vec.at(low) <= vec.at(mid) && vec.at(mid) <= vec.at(high));
	
	return vec.at(mid);
}

template<typename T>
void insertionSort(std::vector<T> &vec, const typename std::vector<T>::size_type low, const typename std::vector<T>::size_type high)
{
	assert(high - low > 2 && high - low < 11);
	for(auto it = vec.begin() + low + 1; it != vec.begin() + high + 1; std::advance(it, 1))
	{
		std::rotate(std::upper_bound(vec.begin() + low, it, *it), it, std::next(it));
	}
}

template<typename T>
void sort2(std::vector<T> &vec, const typename std::vector<T>::size_type low)
{
	if(vec.at(low) > vec.at(low + 1))
	{
		std::swap(vec.at(low), vec.at(low + 1));
	}
}

template<typename T>
void sort3(std::vector<T> &vec, const typename std::vector<T>::size_type low)
{
	if(vec.at(low) > vec.at(low + 2))
	{
		std::swap(vec.at(low), vec.at(low + 2));
	}
	if(vec.at(low) > vec.at(low + 1))
	{
		std::swap(vec.at(low), vec.at(low + 1));
	}
	if(vec.at(low + 1) > vec.at(low + 2))
	{
		std::swap(vec.at(low + 1), vec.at(low + 2));
	}
	assert(vec.at(low) <= vec.at(low + 1) && vec.at(low + 1) <= vec.at(low + 2));
}

// Functional test cases
// Quicksort tests
// Test case 1: empty vector
void testEmptyRange()
{
	std::vector<int> vec;  // Empty vector
	quickSort(vec);
	assert(vec.size() == 0);
}

// Test case 2: vector with only one element.
void testSingleElementRange()
{
	std::vector<int> vec = {23};  // Single-element vector
	quickSort(vec);
	assert(vec.size() == 1);
	assert(vec[0] == 23);
}

// Test case 3: vector where elements are already sorted
void testSortedRange()
{
	std::vector<int> vec = {1, 2, 3, 4, 5};  // Sorted vector
	quickSort(vec);
	assert((vec == std::vector<int>{1, 2, 3, 4, 5}));
}

// Test case 4: vector where elements are sorted in descending order.
void testReverseSortedRange()
{
	std::vector<int> vec = {5, 4, 3, 2, 1};  // Reverse-sorted vector
	quickSort(vec);
	assert((vec == std::vector<int>{1, 2, 3, 4, 5}));
}

// Test case 5: vector with random ints
void testRandomdRangeInt()
{
	std::vector<int> vec = {3, 1, 4, -2, 5};  // Random vector
	quickSort(vec);
	assert((vec == std::vector<int>{-2, 1, 3, 4, 5}));
}

// Test case 6: vector with random chars
void testRandomRangeChar()
{
	std::vector<char> vec = {'c', 'b', 'z', 'a', 'x', 'y'};  // Random vector
	quickSort(vec);
	assert((vec == std::vector<char>{'a', 'b', 'c', 'x', 'y', 'z'}));
}

// Test case 7: vector with random ints and duplicates
void testDuplicateElements()
{
	std::vector<int> vec = {3, 1, 4, 2, 1, 5, 4};  // Vector with duplicates
	quickSort(vec);
	assert((vec == std::vector<int>{1, 1, 2, 3, 4, 4, 5}));
}

// Test case 8: vector with all duplicates, odd length
void allDupsOdd()
{
	std::vector<int> vec(5, 10);  // Odd length vector of duplicates
	quickSort(vec);
	assert(vec == std::vector<int>(5, 10));
}

// Test case 9: vector with all duplicates, even length
void allDupsEven()
{
	std::vector<int> vec(6, 10);  // Even length vector of duplicates
	quickSort(vec);
	assert(vec == std::vector<int>(6, 10));
}

// Test case 10: vector with 12 random elements
void testRandomLongEvenLength()
{
	std::vector<float> vec = {5.6f, 1.1f, 12.3f, 7.8f, 4.5f, 9.0f, 2.3f, 11.2f, 3.4f, 6.7f, 0.2f, 10.1f, 8.9f};  // Even length vector of duplicates
	quickSort(vec);
	assert((vec == std::vector<float>{0.5f, 1.2f, 2.0f, 2.3f, 3.6f, 3.9f, 4.2f, 5.6f, 6.1f, 7.4f, 8.9f, 9.8f}));
}

// Test case 11: vector with 13 random elements
void testRandomLongOddLength()
{
	std::vector<float> vec = {5.6f, 1.1f, 12.3f, 7.8f, 4.5f, 9.0f, 2.3f, 11.2f, 3.4f, 6.7f, 0.2f, 10.1f, 8.9f};  // Even length vector of duplicates
	quickSort(vec);
assert((vec == std::vector<float>{0.2f, 1.1f, 2.3f, 3.4f, 4.5f, 5.6f, 6.7f, 7.8f, 8.9f, 9.0f, 10.1f, 11.2f, 12.3f}));
}


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
	
	quickSort(vec);	
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
	
	quickSort(vec);
	assert(std::is_sorted(vec.begin(), vec.end()));
}

// Test 3: large vector in ascending order
void testAscending()
{
	std::vector<int> ascendingVec;
    ascendingVec.reserve(10000000);

    for (size_t i = 1; i <= ascendingVec.capacity(); i++)
	{
        ascendingVec.push_back(i);
    }
	assert(std::is_sorted(ascendingVec.begin(), ascendingVec.end()));
	quickSort(ascendingVec);
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
	
	quickSort(descendingVec);
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
	
	quickSort(alternatingVec);
	assert(std::is_sorted(alternatingVec.begin(), alternatingVec.end()));
}

// Test 6: large vector, mostly ascending except every 10th element is negative
void testAlternating10()
{
	std::vector<int> alternatingVec;
    alternatingVec.reserve(1000000);

    for (size_t i = 1; i <= alternatingVec.capacity(); i++) {
        int value = (i % 10 == 0) ? -i : i;
        alternatingVec.push_back(value);
    }
	
	quickSort(alternatingVec);
	assert(std::is_sorted(alternatingVec.begin(), alternatingVec.end()));
}


// medianOf3 tests
// Test case 1: Three distinct elements
void test3Distinct()
{
	std::vector<int> nums = {5, 2, 8};
	const auto result = medianOf3(nums, 0, nums.size() - 1);
	assert(result == 5);
}

// Test case 2: Three equal elements
void test3Equal()
{
	std::vector<int> nums = {4, 4, 4};
	const auto result = medianOf3(nums, 0, nums.size() - 1);
	assert(result == 4);
}

// Test case 3: Ascending elements
void test3Ascending()
{
	std::vector<int> nums = {1, 2, 3};
	const auto result = medianOf3(nums, 0, nums.size() - 1);
	assert(result == 2);
}

// Test case 4: Descending elements
void test3Descending()
{
	std::vector<int> nums = {6, 5, 4};
	const auto result = medianOf3(nums, 0, nums.size() - 1);
	assert(result == 5);
}

// Test case 5: Six chars
void test6Chars()
{
	std::vector<int> chars = {'x', 'y', 'z', 'a', 'b', 'c'};
	const auto result = medianOf3(chars, 0, chars.size() - 1);
	assert(result == 'x');
}

// Test case 6: Descending negative elements
void test3DescNeg()
{
	std::vector<int> nums = {-1, -2, -3};
	const auto result = medianOf3(nums, 0, nums.size() - 1);
	assert(result == -2);
}

// Test cases for insertion sort
// Test case 1: Test with an already sorted vector
void testSortedVector()
{
    std::vector<int> testVec = {1, 2, 3, 4, 5};
    insertionSort(testVec, 0, testVec.size() - 1);
    assert((testVec == std::vector<int>{1, 2, 3, 4, 5}));
}

// Test case 2: Test with a reverse sorted vector
void testReverseSortedVector()
{
    std::vector<int> testVec = {5, 4, 3, 2, 1};
    insertionSort(testVec, 0, testVec.size() - 1);
    assert((testVec == std::vector<int>{1, 2, 3, 4, 5}));
}

// Test case 3: Test with a random vector
void testRandomVector()
{
    std::vector<int> testVec = {3, 1, 4, 1, 5, 8, 2, 6, 5, 3, 5};
    insertionSort(testVec, 0, testVec.size() - 1);
    assert((testVec == std::vector<int>{1, 1, 2, 3, 3, 4, 5, 5, 5, 6, 8}));
}

// Test case 4: Test with doubles
void testDoubles()
{
    std::vector<double> doubles = {3.55, 1.0, 2.71, 0.4, 2.0};
    insertionSort(doubles, 0, doubles.size() - 1);
	for(auto i : doubles)
		std::cout << i << " ";
	std::cout << std::endl;
    assert((doubles == std::vector<double>{0.4, 1.0, 2.0, 2.71, 3.55}));
}

int main()
{
	std::cout << "Started" << std::endl;
	testSortedVector();
    std::cout << "Insertion sort test case 1 passed" << std::endl;
	testReverseSortedVector();
	std::cout << "Insertion sort test case 2 passed" << std::endl;
	testRandomVector();
	std::cout << "Insertion sort test case 3 passed" << std::endl;
	testDoubles();
	std::cout << "Insertion sort test case 4 passed" << std::endl;
	test3Distinct();
	std::cout << "Pivot test 1 passed" << std::endl;
	test3Equal();
	std::cout << "Pivot test 2 passed" << std::endl;
	test3Ascending();
	std::cout << "Pivot test 3 passed" << std::endl;
	test3Descending();
	std::cout << "Pivot test 4 passed" << std::endl;
	test6Chars();
	std::cout << "Pivot test 5 passed" << std::endl;
	test3DescNeg();
	std::cout << "Pivot test 6 passed" << std::endl;
	testEmptyRange();
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
	void allDupsOdd();
	std::cout << "Quicksort functional  test 8 passed" << std::endl;
	void allDupsEven();
	std::cout << "Quicksort functional test 9 passed" << std::endl;
	void testRandomLongEvenLength();
	std::cout << "Quicksort functional test 10 passed" << std::endl;
	testRandomLongOddLength();
	std::cout << "Quicksort functional test 11 passed" << std::endl;
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