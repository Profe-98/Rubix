#define BOOST_TEST_MODULE test_ctors_main

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
//arrange

#include <iostream>

#include "../RubixMain.h"
#include "../RubixMatrix/Matrix.h"

using namespace Rubix;

namespace
{
	using namespace boost::unit_test;
	BOOST_AUTO_TEST_CASE(test_ctors_main)
	{
		int res = RubixMain::Prepare_Library();
		BOOST_CHECK(res == 1);

		double valtoadd = 4;

		std::vector<double> v0 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		std::unique_ptr<Matrix> m0 = std::make_unique<Matrix>("m0", 2, 5, v0);

		std::vector<double> v2 = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

	}
}