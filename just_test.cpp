#include "ip_filter.cpp"
#include <boost/test/unit_test.hpp>

#define BOOST_TEST_MODULE TestIpFilter

BOOST_AUTO_TEST_SUITE(TesuIpFilter)

BOOST_AUTO_TEST_CASE( TestIpFilterCorrect )
{
      BOOST_CHECK( isIp4Adress("0.0.0.0	4	4") == true);
      BOOST_CHECK( isIp4Adress("22.99.83.10	55	68") == true);
      BOOST_CHECK( isIp4Adress("199.100.200.255	8	76") == true);
      BOOST_CHECK( isIp4Adress("0.0.0.0	4	4") == true);
      BOOST_CHECK( isIp4Adress("255.255.255.255	4	4") == true);
      BOOST_CHECK( isIp4Adress("8.8.8.8") == true);
      BOOST_CHECK( isIp4Adress("99.99.99.99 2 3") == true);
}

BOOST_AUTO_TEST_CASE(TestIpFilterNoncorrectIp)
{
      BOOST_CHECK( isIp4Adress("255.256.255.255	4	4") == false);
      BOOST_CHECK( isIp4Adress("256.255.255.255	4	4") == false);
      BOOST_CHECK( isIp4Adress("255.255.300.255	4	4") == false);
      BOOST_CHECK( isIp4Adress("255.255.255.400	4	4") == false);
      BOOST_CHECK( isIp4Adress("1.-1.255.255	4	4") == false);
      BOOST_CHECK( isIp4Adress("1.1.-1.3	4	4") == false);
      BOOST_CHECK( isIp4Adress("1.1.255.-1	4	4") == false);
}

BOOST_AUTO_TEST_SUITE_END()
