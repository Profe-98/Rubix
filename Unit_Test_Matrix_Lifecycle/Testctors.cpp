#define BOOST_TEST_MAIN test_ctors_main
#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_tools.hpp>

//arrange act assert

#ifndef CL_TARGET_OPENCL_VERSION
#define CL_TARGET_OPENCL_VERSION 200
#endif // !CL_TARGET_OPENCL_VERSION

#include "CL/opencl.h"
#include "CL/cl.h"
#include <iostream>
#ifndef __CL_ENABLE_EXCEPTIONS
#define __CL_ENABLE_EXCEPTIONS
#endif // !__CL_ENABLE_EXCEPTIONS

#include "RubixMain.h"
#include "Matrix.h"
using namespace Rubix;

namespace
{
	using namespace boost::unit_test;
	BOOST_AUTO_TEST_CASE(test_matr_life)
	{
		int res = RubixMain::Prepare_Library(); // prep Rubix;
		BOOST_CHECK(res == 1);

		double d = -4.20;
		std::vector<int> strds = { 0, 0 };
		std::unique_ptr<Matrix> m0 = std::make_unique<Matrix>("m0", 3, 3, d);
		BOOST_CHECK(d == m0->GetEntries()[0]);
		BOOST_CHECK(3 == m0->Getrows());
		BOOST_CHECK(3 == m0->Getcols());
		BOOST_CHECK(9 == m0->size_logical());
		BOOST_CHECK(1 == m0->size_physical());
		BOOST_CHECK(strds == m0->Getstrides());
		BOOST_CHECK("m0" == m0->Getname());

		std::vector<double> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
		std::unique_ptr<Matrix> m1 = std::make_unique<Matrix>("m1", 2, 5, v1 );
		std::vector<int> strds1 = { 1, 5 };
		BOOST_CHECK(1.0 == m1->GetEntries()[0]);
		BOOST_CHECK(9.0 == m1->GetEntries()[8]);
		BOOST_CHECK(2 == m1->Getrows());
		BOOST_CHECK(5 == m1->Getcols());
		BOOST_CHECK(10 == m1->size_logical());
		BOOST_CHECK(10 == m1->size_physical());
		BOOST_CHECK(strds1 == m1->Getstrides());
		BOOST_CHECK("m1" == m1->Getname());

		std::unique_ptr<Matrix> m2 = std::make_unique<Matrix>(*m1);
		BOOST_CHECK(1.0 == m2->GetEntries()[0]);
		BOOST_CHECK(9.0 == m2->GetEntries()[8]);
		BOOST_CHECK(2 == m2->Getrows());
		BOOST_CHECK(5 == m2->Getcols());
		BOOST_CHECK(10 == m2->size_logical());
		BOOST_CHECK(10 == m2->size_physical());
		BOOST_CHECK(strds1 == m2->Getstrides());
		BOOST_CHECK("m1" == m2->Getname());

		std::vector<double> v3 = { 1, 2, 3, 4};
		std::unique_ptr<Matrix> m3 = std::make_unique<Matrix>("m3", 2, 2, v3);
		std::vector<int> strds3 = { 1, 2 };
		BOOST_CHECK(1.0 == m3->GetEntries()[0]);
		BOOST_CHECK(4 == m3->GetEntries()[3]);
		BOOST_CHECK(2 == m3->Getrows());
		BOOST_CHECK(2 == m3->Getcols());
		BOOST_CHECK(4 == m3->size_logical());
		BOOST_CHECK(4 == m3->size_physical());
		BOOST_CHECK(strds3 == m3->Getstrides());
		BOOST_CHECK("m3" == m3->Getname());



		*m3 = *m1;
		BOOST_CHECK(1.0 == m3->GetEntries()[0]);
		BOOST_CHECK(9.0 == m3->GetEntries()[8]);
		BOOST_CHECK(2 == m3->Getrows());
		BOOST_CHECK(5 == m3->Getcols());
		BOOST_CHECK(10 == m3->size_logical());
		BOOST_CHECK(10 == m3->size_physical());
		BOOST_CHECK(strds1 == m3->Getstrides());
		BOOST_CHECK("m1" == m3->Getname());

		std::vector<double> v4 = { 1, 2, 3, 4 };
		std::unique_ptr<Matrix> m4 = std::make_unique<Matrix>("m4", 2, 2, v3);
		std::vector<int> strds4 = { 1, 2 };

		std::unique_ptr<Matrix> m5 = std::make_unique<Matrix>(std::move(*m4));
		BOOST_CHECK(1.0 == m5->GetEntries()[0]);
		BOOST_CHECK(4 == m5->GetEntries()[3]);
		BOOST_CHECK(2 == m5->Getrows());
		BOOST_CHECK(2 == m5->Getcols());
		BOOST_CHECK(4 == m5->size_logical());
		BOOST_CHECK(4 == m5->size_physical());
		BOOST_CHECK(strds4 == m5->Getstrides());
		BOOST_CHECK("m4" == m5->Getname());


	}
}