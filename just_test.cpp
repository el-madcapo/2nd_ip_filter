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
      

}

