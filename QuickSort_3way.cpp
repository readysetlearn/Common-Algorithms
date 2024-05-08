//Based on https://en.wikipedia.org/wiki/Quicksort#Repeated_elements
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>


// Function prototypes
template<typename T>
void quickSort(std::vector<T> &vec);

template<typename T>
void qs(std::vector<T> &vec, typename std::vector<T>::size_type low, const typename std::vector<T>::size_type high);

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
void qs(std::vector<T> &vec, typename std::vector<T>::size_type low, const typename std::vector<T>::size_type high)
{
	while(low < high)
	{
		if(high - low == 1)
		{
			sort2(vec, low);
			assert(std::is_sorted(vec.begin() + low , vec.begin() + high + 1)); // is_sorted(x, y) checks the interval [x, y) hence the '+ 1'
			low = high + 1;
		}
		else if(high - low == 2)
		{
			sort3(vec, low);
			assert(std::is_sorted(vec.begin() + low , vec.begin() + high + 1));
			low = high + 1;
		}
		else if(high - low < 10)
		{
			insertionSort(vec, low, high);
			assert(std::is_sorted(vec.begin() + low , vec.begin() + high + 1));
			low = high + 1;
		}
		else
		{
			std::pair<typename std::vector<T>::size_type, typename std::vector<T>::size_type> partitionWalls = partition(vec, low, high);
			qs(vec, low, partitionWalls.first);
			low = partitionWalls.second;
		}
	}
}

template<typename T>
std::pair<typename std::vector<T>::size_type, typename std::vector<T>::size_type> partition(std::vector<T> &vec, const typename std::vector<T>::size_type low, const typename std::vector<T>::size_type high)
{
	assert(high < vec.size() && low >= 0);
	
	const auto pivot = medianOf3(vec, low, high);
	// Lesser, equal and greater indexes
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
	assert(high - low > 2 && high - low < 10);
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
// Test 1: vector with few duplicates
void testFewDuplicates() {
    std::vector<int> vec;
    const int n = 100000;
	vec.reserve(n);
    for (int i = 0; i < n; ++i) {
        vec.push_back(i % (n / 2)); // Half the range will have duplicates
    }
    quickSort(vec);
    assert(std::is_sorted(vec.begin(), vec.end()));
}

// Test 2: vector with all duplicates
void testAllDuplicates() {
    std::vector<int> vec;
    const int n = 100000;
	vec.reserve(n);
    int val = 25; // Value to be repeated
    for (int i = 0; i < n; ++i) {
        vec.push_back(val); // All elements are same
    }
    quickSort(vec);
    assert(std::is_sorted(vec.begin(), vec.end()));
}

// Test 3: vector with random duplicates
void testRandomDuplicates() {
    std::vector<int> vec;
    const int n = 100000;
	vec.reserve(n);
    for (int i = 0; i < n; ++i) {
        vec.push_back(i % 10); // 10 different values with some repetitions
    }
    quickSort(vec);
    assert(std::is_sorted(vec.begin(), vec.end()));
}

// Test 4: vector with no duplicates
void testNoDuplicates() {
    std::vector<int> vec;
    const int n = 100000;
	vec.reserve(n);
    for (int i = 0; i < n; ++i) {
        vec.push_back(i); // All elements are unique
    }
    quickSort(vec);
    assert(std::is_sorted(vec.begin(), vec.end()));
}

// Test 5: vector with mostly duplicates
void testMostlyDuplicates() {
    std::vector<int> vec;
    const int n = 100000;
	vec.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (i < n / 2) {
            vec.push_back(26); // Half of the elements are same
        } else {
            vec.push_back(i); // Other half are unique
        }
    }
    quickSort(vec);
    assert(std::is_sorted(vec.begin(), vec.end()));
}

// Test 6: vector with alternating duplicates
void testAlternatingDuplicates() {
    std::vector<int> vec;
    const int n = 100000;
	vec.reserve(n);
    for (int i = 0; i < n; ++i) {
        vec.push_back(i % 2); // Alternating duplicates
    }
    quickSort(vec);
    assert(std::is_sorted(vec.begin(), vec.end()));
}


int main()
{
	std::cout << "Started" << std::endl;
	testFewDuplicates();
	std::cout << "Quicksort stress test 1 passed" << std::endl;
	testAllDuplicates();
	std::cout << "Quicksort stress test 2 passed" << std::endl;
	testRandomDuplicates();
	std::cout << "Quicksort stress test 3 passed" << std::endl;
	testNoDuplicates();
	std::cout << "Quicksort stress test 4 passed" << std::endl;
	testMostlyDuplicates();
	std::cout << "Quicksort stress test 5 passed" << std::endl;
	testAlternatingDuplicates();
	std::cout << "Quicksort stress test 6 passed" << std::endl;
	std::cout << "Completed" << std::endl;
	
	return 0;
}
