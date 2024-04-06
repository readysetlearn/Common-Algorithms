// Implementation of insertion sort https://en.wikipedia.org/wiki/Insertion_sort
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm> // For std::rotate

template<typename Iter>
void insertionSort(Iter begin, Iter end)
{
	if(begin == end) return;// Empty containers are considered sorted
	for(auto i = std::next(begin); i != end; std::advance(i, 1))
	{
		std::rotate(std::upper_bound(begin, i, *i), i, std::next(i));
	}
}

// Tests cases for insertionSort
void testEmpty()
{
    std::vector<int> emptyVec;
    insertionSort(emptyVec.begin(), emptyVec.end());
    assert(emptyVec.empty());
}

void testSingle()
{
    std::vector<short> singleVec = {-5};
    insertionSort(singleVec.begin(), singleVec.end());
    assert((singleVec == std::vector<short>{-5}));
}

void testAscendingSorted()
{
    std::vector<int> sortedVec = {1, 2, 3, 4, 5};
    insertionSort(sortedVec.begin(), sortedVec.end());
    assert((sortedVec == std::vector<int>{1, 2, 3, 4, 5}));
}

void testReverseSorted()
{
    std::vector<int> reverseVec = {6, 5, 4, 3, 2, 1};
    insertionSort(reverseVec.begin(), reverseVec.end());
	for(auto i : reverseVec) std::cout << i << ", ";
    assert((reverseVec == std::vector<int>{1, 2, 3, 4, 5, 6}));
}

void testRandomUnsorted()
{
    std::vector<int> randomVec = {3, 1, 4, 2, 5};
    insertionSort(randomVec.begin(), randomVec.end());
    assert((randomVec == std::vector<int>{1, 2, 3, 4, 5}));
}

void testWithDuplicates()
{
    std::vector<int> dupVec = {2, 4, 1, 3, 2, 5, 4};
    insertionSort(dupVec.begin(), dupVec.end());
    assert((dupVec == std::vector<int>{1, 2, 2, 3, 4, 4, 5}));
}

void testAllDuplicates()
{
    std::vector<char> dupVec(6, 'c');
    insertionSort(dupVec.begin(), dupVec.end());
    assert(dupVec == std::vector<char>(6, 'c'));
}

int main()
{
	std::cout << "Now testing..." << std::endl;
	testEmpty();
	std::cout << "Empty input passed." << std::endl;
	testSingle();
	std:: cout << "Single elment passed." << std::endl;
	testAscendingSorted();
	std::cout << "Sorted input passed." << std::endl;
	testReverseSorted();
	std::cout << "Reverse sorted input passed." << std::endl;
	testRandomUnsorted();
	std::cout << "Random input with no duplicates passed." << std::endl;
	testWithDuplicates();
	std::cout << "Random input with duplicates passed." << std::endl;
	testAllDuplicates();
	std::cout << "All duplicates passed." << std::endl;
	std::cout << "Completed." << std::endl;
	
	return 0;
}