#define BOOST_TEST_MAIN test_ctors_main
#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_tools.hpp>

//arrange

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
	BOOST_AUTO_TEST_CASE(test_matrix_addition)
	{
		int res = RubixMain::Prepare_Library();
		BOOST_CHECK(res == 1);

		double valtoadd = 4;

		std::vector<double> v0 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		std::unique_ptr<Matrix> m0 = std::make_unique<Matrix>("m0", 2, 5, v0);

		std::vector<double> v2 = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
		std::unique_ptr<Matrix> m2 = std::make_unique<Matrix>("m2", 2, 5, v2);

		std::unique_ptr<Matrix> m1 = *m0 + valtoadd;
		//std::cout << "[" << m0->Getstrides()[0] << ", " << m0->Getstrides()[1] << "]\n";
		//std::cout << "[" << m2->Getstrides()[0] << ", " << m2->Getstrides()[1] << "]\n";/**/
		int s = v0.size();
		
		
		/**/for (int i = 0; i < s; ++i)
		{
			std::cout << m1->GetEntries()[i] << "\n";
			BOOST_WARN_EQUAL(v0[i] + 1, m1->GetEntries()[i]);
		}/**/
	}
}