#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <string>

struct true_type{ static constexpr bool value = true; };
struct false_type{ static constexpr bool value = false; };

template<typename T, typename U>
struct is_same : false_type{};

template<typename T>
struct is_addable : is_same<T,T>{};

template<typename T>
struct is_same<T, int> : true_type{};

template<typename T>
struct is_same<T, double> : true_type{};

template<typename it, typename T>
T my_sum(it begin, it end, T sum){
	using it_value = typename std::iterator_traits<it>::value_type;
	static_assert(is_addable<it_value>::value, "not addable type");
	static_assert(is_same<it_value, T>::value, "container type is not the same as sum type");

	while (begin < end){
		sum += *begin;
		++begin;
	}
	return sum;

}

int main()
{
	//static_assert(is_addable<int>::value, "not addable");
	std::vector<int> v1 = {1, 2, 3, 4};
	std::list<double> v2 = {1.1, 2.2, 3.3, 4.4};
	std::vector<std::string> v3 = {"Hello", "world", "Yes", "No"};
	int sum1 = 1;
	double sum2 = 1.2;
	int sum3 = 0;

	std::list<std::string> v4 = {"Yes", "No"};
	float wrong_init = 0.0;
	//std::cout << my_sum<std::list<std::string>::iterator, int>(v4.begin(), v4.end(), 0) << std::endl;
	std::cout << my_sum<std::vector<int>::iterator, int>(v1.begin(), v1.end(), wrong_init) << std::endl;
	
	return 0;
}