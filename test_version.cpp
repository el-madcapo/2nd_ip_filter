#define BOOST_TEST_MODULE test_version

#include "ip_filter.cpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version)
{
	BOOST_CHECK( ip_sorting(const std::vector<std::vector<int> >& , std::vector<std::vector<int> >& , 
                      std::vector<unsigned int>& , 
                      std::vector<unsigned int>& , 
                      std::vector<unsigned int>& ).size() > 0);
}

BOOST_AUTO_TEST_SUITE_END()
