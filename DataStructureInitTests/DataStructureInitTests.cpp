#define BOOST_TEST_MODULE test_init_main

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
	BOOST_AUTO_TEST_CASE(test_init)
	{
		int res = RubixMain::Prepare_Library();
		BOOST_CHECK(res == 1);

		std::vector<double> v0 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		std::vector<double> v1 = { 9, 8, 7 };

		std::unique_ptr<Matrix> m0 = std::make_unique<Matrix>("m0", 2, 5, v0);
		std::unique_ptr<Matrix> m1 = std::make_unique<Matrix>("m1", 1, 3, v1);
		std::unique_ptr<Matrix> m2 = std::make_unique<Matrix>("m2", 2, 2, 4);

		std::unique_ptr<Matrix> m2cpy = std::make_unique<Matrix>(*m2);

		BOOST_CHECK(m2 == m2);

		BOOST_CHECK(m0 != m1);
		BOOST_CHECK(m2cpy->Getname() == m2->Getname() && m2cpy->IsSquared() && m2cpy->IsPacked() == false && m2cpy->size_physical() == 1);

		
		BOOST_CHECK(m0->Getcols() == 5);
		BOOST_CHECK(m0->Getrows() == 2);

		BOOST_CHECK(m0->Getname() == "m0");
		BOOST_CHECK(m0->Getname() != "m1");

		BOOST_CHECK(m0->Getstrides().first == 1);
		BOOST_CHECK(m0->Getstrides().second == 5);

	    BOOST_CHECK(m1->IsEmpty() == false);

		BOOST_CHECK(m0->size_logical() == 10);

		BOOST_CHECK(m0->IsSquared() == false);
		BOOST_CHECK(m2->IsSquared() == true);

		BOOST_CHECK(m0->size_physical() != 1);

		BOOST_CHECK(m0->IsPacked() == true);
		BOOST_CHECK(m2->IsPacked() == false);

		BOOST_CHECK(m0->GetDType() == "double");

		BOOST_CHECK(m2->IsCompressed() == true);

		BOOST_CHECK(m0->Is_mutable() == true);
		BOOST_CHECK(m0->Is_resizable() == false);

		//TODO: make trace method compatible with 'compressed' matrices
		//BOOST_CHECK(m2->Trace() == 8);

		//add other operator and c'tor tests l8...
	}
}