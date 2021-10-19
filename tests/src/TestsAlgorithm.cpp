#include "tests.hpp"

#include <vector>

#include "algorithm.hpp"
#include <algorithm>
#include <functional>

TEST_CASE( "cn::lexicographical_compare - default",
	"[algorithm][lexicographical_compare][default]" )
{
	std::vector<int> vec = {1,2,3,4,5};
	std::vector<int> vec_bis = {1,2,3,4,5};
	std::vector<int> vec2 = {10,2,3,4,5};

	CHECK( true ==  std::lexicographical_compare(vec.begin(), vec.end(), vec2.begin(), vec2.end()) );
	CHECK( false == std::lexicographical_compare(vec.begin(), vec.end(), vec_bis.begin(), vec_bis.end()) );
	CHECK( false == std::lexicographical_compare(vec2.begin(), vec2.end(), vec.begin(), vec.end()) );
	CHECK( false == std::lexicographical_compare(vec2.begin(), vec2.end(), vec2.begin(), vec2.end()) );
}

template <class _Tp>
struct ft_less
{
    bool operator()(const _Tp& x, const _Tp& y) const
        {return x < y;}
};

template <class _Tp>
struct more
{
    bool operator()(const _Tp& x, const _Tp& y) const
        {return x > y;}
};

TEST_CASE( "cn::lexicographical_compare - custom",
	"[algorithm][lexicographical_compare][custom]" )
{
	std::vector<int> vec = {1,2,3,4,5};
	std::vector<int> vec_bis = {1,2,3,4,5};
	std::vector<int> vec2 = {10,2,3,4,5};

	CHECK( true  == cn::lexicographical_compare(vec.begin(), vec.end(), vec2.begin(), vec2.end(), ft_less<int>()) );
	CHECK( false == cn::lexicographical_compare(vec.begin(), vec.end(), vec_bis.begin(), vec_bis.end(), ft_less<int>()) );
	CHECK( false == cn::lexicographical_compare(vec2.begin(), vec2.end(), vec.begin(), vec.end(), ft_less<int>()) );
	CHECK( false == cn::lexicographical_compare(vec2.begin(), vec2.end(), vec2.begin(), vec2.end(), ft_less<int>()) );

	CHECK( false == cn::lexicographical_compare(vec.begin(), vec.end(), vec2.begin(), vec2.end(), more<int>()) );
	CHECK( false == cn::lexicographical_compare(vec.begin(), vec.end(), vec_bis.begin(), vec_bis.end(), more<int>()) );
	CHECK( true  == cn::lexicographical_compare(vec2.begin(), vec2.end(), vec.begin(), vec.end(), more<int>()) );
	CHECK( false == cn::lexicographical_compare(vec2.begin(), vec2.end(), vec2.begin(), vec2.end(), more<int>()) );
}

TEST_CASE( "cn::equal - default",
	"[algorithm][equal][default]" )
{
	std::vector<int> vec = {1,2,3,4,5};
	std::vector<int> vec_bis = {1,2,3,4,5};
	std::vector<int> vec2 = {10,2,3,4,5};

	CHECK( true == std::equal(vec.begin(), vec.end(), vec_bis.begin()) );
	CHECK( false == cn::equal(vec.begin(), vec.end(), vec2.begin()) );
}

template <class _Tp>
struct ft_equal
{
	bool operator()(const _Tp& x, const _Tp& y)
	{
		return x == y;
	}
};
template <class _Tp>
struct ft_not_equal
{
	bool operator()(const _Tp& x, const _Tp& y)
	{
		return x != y;
	}
};

TEST_CASE( "cn::equal - custom",
	"[algorithm][equal][custom]" )
{
	std::vector<int> vec = {1,2,3,4,5};
	std::vector<int> vec_bis = {1,2,3,4,5};
	std::vector<int> vec2 = {10,2,3,4,5};
	std::vector<int> vec3 = {13,5,33,33,44};

	CHECK( true ==  cn::equal(vec.begin(), vec.end(), vec_bis.begin(), ft_equal<int>()) );
	CHECK( false == cn::equal(vec.begin(), vec.end(), vec2.begin(), ft_equal<int>()) );

	CHECK( false == cn::equal(vec.begin(), vec.end(), vec_bis.begin(), ft_not_equal<int>()) );
	CHECK( false == cn::equal(vec.begin(), vec.end(), vec2.begin(), ft_not_equal<int>()) );
	CHECK( true ==  cn::equal(vec.begin(), vec.end(), vec3.begin(), ft_not_equal<int>()) );
}
