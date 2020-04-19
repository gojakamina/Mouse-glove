#define BOOST_TEST_MODULE FilterTests
#include <boost/test/unit_test.hpp>
#include "Filter.h"


Filter filter;


BOOST_AUTO_TEST_SUITE(FilterTest)


BOOST_AUTO_TEST_CASE( TestThresholdOrFiltZero )
{
	BOOST_TEST_MESSAGE( "Testing threshold on thresholdOrFilt :" );
	BOOST_CHECK_EQUAL( 0, filter.thresholdOrFilt(0) );
}


BOOST_AUTO_TEST_CASE( TestThresholdOrFiltNonZero )
{
	BOOST_TEST_MESSAGE( "Testing filter on thresholdOrFilt :" );
	if( 0 == filter.thresholdOrFilt(1) )
        BOOST_ERROR( "Check butterworht filter." );
}


BOOST_AUTO_TEST_CASE( TestIntegrateZero )
{
	BOOST_TEST_MESSAGE( "Testing integration with zero input :" );
	BOOST_CHECK_EQUAL( 0, filter.integrate(0, 0, 0) );
}


BOOST_AUTO_TEST_CASE( TestIntegrateNonZero )
{
	BOOST_TEST_MESSAGE( "Testing integration with initial value 1 :" );
	BOOST_CHECK_EQUAL(1, filter.integrate(1, 0, 0));
}


BOOST_AUTO_TEST_CASE( TestPassThresh )
{
	BOOST_TEST_MESSAGE( "Testing pass threshold on threshold :" );
	float value = 1;
	float prev = 1;
	filter.threshold(value, prev);
	BOOST_CHECK_EQUAL(1, value);
	BOOST_CHECK_EQUAL(1, prev);
}


BOOST_AUTO_TEST_CASE( TestPosThresh )
{
	BOOST_TEST_MESSAGE( "Testing positive threshold on threshold :" );
	float value = 0.0005;
	float prev = 0.0005;
	filter.threshold(value, prev);
	BOOST_CHECK_EQUAL(0, value);
	BOOST_CHECK_EQUAL(0, prev);
}


BOOST_AUTO_TEST_CASE( TestNegThresh )
{
	BOOST_TEST_MESSAGE( "Testing negative threshold on threshold :" );
	float value = -0.0005;
	float prev = 0.0005;
	filter.threshold(value, prev);
	BOOST_CHECK_EQUAL(0, value);
	BOOST_CHECK_EQUAL(0, prev);
}


BOOST_AUTO_TEST_CASE( TestCounter )
{
	BOOST_TEST_MESSAGE( "Testing counter :" );
	int count = 3;
	filter.counter(count, 0);
	BOOST_CHECK_EQUAL(4, count);
}


BOOST_AUTO_TEST_CASE( TestVelToZero )
{
	BOOST_TEST_MESSAGE( "Testing setVel :" );
	int count = 6;
	float vel = 0.5;
	float prevVel = 0.5;
	filter.setVel(count, vel, prevVel);
	BOOST_CHECK_EQUAL(0, count);
	BOOST_CHECK_EQUAL(0, vel);
	BOOST_CHECK_EQUAL(0, prevVel);
}


BOOST_AUTO_TEST_SUITE_END()
