#define BOOST_TEST_MODULE FilterTests
#include <boost/test/unit_test.hpp>
#include "Filter.h"

Filter filter;


BOOST_AUTO_TEST_SUITE(FilterTest)

// test threshold or filter
BOOST_AUTO_TEST_CASE(ThresholdOrFilt)
{
	BOOST_CHECK_EQUAL(0, filter.thresholdOrFilt(0));
}

// test integration with zero
BOOST_AUTO_TEST_CASE(IntegrateZero)
{
	BOOST_CHECK_EQUAL(0, filter.integrate(0, 0, 0));
}

// test integration with curr+prev=0
BOOST_AUTO_TEST_CASE(IntegrateNonZero)
{
	BOOST_CHECK_EQUAL(1, filter.integrate(1, 0, 0));
}

// test pass threshold
BOOST_AUTO_TEST_CASE(PassThresh)
{
	float value = 1;
	float prev = 1;
	filter.threshold(value, prev);
	BOOST_CHECK_EQUAL(1, value);
	BOOST_CHECK_EQUAL(1, prev);
}

// test threshold
BOOST_AUTO_TEST_CASE(Thresh)
{
	float value = 0;
	float prev = 0;
	filter.threshold(value, prev);
	BOOST_CHECK_EQUAL(0, value);
	BOOST_CHECK_EQUAL(0, prev);
}

// test counter
BOOST_AUTO_TEST_CASE(Counter)
{
	int count = 3;
	filter.counter(count, 0);
	BOOST_CHECK_EQUAL(4, count);
}

// test set velocity to zero
BOOST_AUTO_TEST_CASE(VelToZero)
{
	int count = 6;
	float vel = 0.5;
	float prevVel = 0.5;
	filter.setVel(count, vel, prevVel);
	BOOST_CHECK_EQUAL(0, count);
	BOOST_CHECK_EQUAL(0, vel);
	BOOST_CHECK_EQUAL(0, prevVel);
}

BOOST_AUTO_TEST_SUITE_END()
