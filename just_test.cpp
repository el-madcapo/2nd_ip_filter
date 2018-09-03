#define BOOST_TEST_MODULE TestIpFilter


#include "ip_filter.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(TestIpFilter)
{
      IpFilter ipfilter;      
      BOOST_CHECK( ipfilter.isIp4Address("0.0.0.0	4	4") == true);
      BOOST_CHECK( ipfilter.isIp4Address("22.99.83.10	55	68") == true);
      BOOST_CHECK( ipfilter.isIp4Address("199.100.200.255	8	76") == true);
      BOOST_CHECK( ipfilter.isIp4Address("0.0.0.0	4	4") == true);
      BOOST_CHECK( ipfilter.isIp4Address("255.255.255.255	4	4") == true);
      BOOST_CHECK( ipfilter.isIp4Address("8.8.8.8") == true);
      BOOST_CHECK( ipfilter.isIp4Address("99.99.99.99 2 3") == true);
      BOOST_CHECK( ipfilter.isIp4Address("256.99.99.99 2 3") == false);
      BOOST_CHECK( ipfilter.isIp4Address("9.256.99 2 3") == false);
      BOOST_CHECK( ipfilter.isIp4Address("243.142.256.99 2 3") == false);
      BOOST_CHECK( ipfilter.isIp4Address("250.99.143.256 24 36") == false);
      BOOST_CHECK( ipfilter.isIp4Address("-1.99.99.99 2 3") == false);
      BOOST_CHECK( ipfilter.isIp4Address("1a.23.45.67 35 189") == false);
      BOOST_CHECK( ipfilter.isIp4Address("123.b4.99.99 2 3") == false);
      BOOST_CHECK( ipfilter.isIp4Address("123.4b.99.99 12 34") == false);
      BOOST_CHECK( ipfilter.isIp4Address("123.44.g9.99 12 34") == false);
      BOOST_CHECK( ipfilter.isIp4Address("123.44.9g.99 12 34") == false);
      BOOST_CHECK( ipfilter.isIp4Address("123.47.99.v9 45 66") == false);

      BOOST_CHECK( ipfilter.isIp4Address("123.4.99.9v 12 34") == true);
      BOOST_CHECK( ipfilter.isIp4Address("12.4.99.99") == true);
}

