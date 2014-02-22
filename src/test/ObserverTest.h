#include "gtest/gtest.h"

#include "react/Signal.h"

////////////////////////////////////////////////////////////////////////////////////////
namespace {

using namespace react;

////////////////////////////////////////////////////////////////////////////////////////
/// ObserverTest fixture
////////////////////////////////////////////////////////////////////////////////////////
template <typename TEngine>
class ObserverTest : public testing::Test
{
public:
	REACTIVE_DOMAIN(MyDomain, TEngine);
};

TYPED_TEST_CASE_P(ObserverTest);

////////////////////////////////////////////////////////////////////////////////////////
/// Detach test
////////////////////////////////////////////////////////////////////////////////////////
TYPED_TEST_P(ObserverTest, Detach)
{
	auto a1 = MyDomain::MakeVar(1);
	auto a2 = MyDomain::MakeVar(1);

	auto result = a1 + a2;

	int observeCount1 = 0;
	int observeCount2 = 0;
	int observeCount3 = 0;

	int phase;

	auto obs1 = Observe(result, [&] (int v)
	{
		observeCount1++;

		if (phase == 0)
			ASSERT_EQ(v,3);
		else if (phase == 1)
			ASSERT_EQ(v,4);
		else
			ASSERT_TRUE(false);
	});

	Observe(result, [&] (int v)
	{
		observeCount2++;

		if (phase == 0)
			ASSERT_EQ(v,3);
		else if (phase == 1)
			ASSERT_EQ(v,4);
		else
			ASSERT_TRUE(false);
	});

	Observe(result, [&] (int v)
	{
		observeCount3++;

		if (phase == 0)
			ASSERT_EQ(v,3);
		else if (phase == 1)
			ASSERT_EQ(v,4);
		else
			ASSERT_TRUE(false);
	});

	phase = 0;
	a1 <<= 2;
	ASSERT_EQ(observeCount1,1);
	ASSERT_EQ(observeCount2,1);
	ASSERT_EQ(observeCount3,1);

	phase = 1;
	obs1.Detach();
	a1 <<= 3;
	ASSERT_EQ(observeCount1,1);
	ASSERT_EQ(observeCount2,2);
	ASSERT_EQ(observeCount3,2);

	phase = 2;
	DetachAllObservers(result);
	a1 <<= 4;
	ASSERT_EQ(observeCount1,1);
	ASSERT_EQ(observeCount2,2);
	ASSERT_EQ(observeCount3,2);
}

////////////////////////////////////////////////////////////////////////////////////////
REGISTER_TYPED_TEST_CASE_P
(
	ObserverTest,
	Detach
);

// ---
}