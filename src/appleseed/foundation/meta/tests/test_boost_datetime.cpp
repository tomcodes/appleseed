
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010 Francois Beaune
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

// appleseed.foundation headers.
#include "foundation/utility/string.h"
#include "foundation/utility/test.h"

// boost headers.
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

// Standard headers.
#include <string>

using namespace boost;
using namespace foundation;
using namespace std;

TEST_SUITE(Boost_DateTime)
{
    TEST_CASE(DateToString)
    {
        using namespace gregorian;

        const string result = to_string(date(2010, Jun, 22));

        EXPECT_EQ("2010-Jun-22", result);
    }

    TEST_CASE(TimeDurationToString)
    {
        using namespace posix_time;

        const string result = to_string(time_duration(17, 45, 31));

        EXPECT_EQ("17:45:31", result);
    }

#if 0

    //
    // The following test will crash or hang because of a bug in Visual C++ 2008
    // when _HAS_ITERATOR_DEBUGGING is set to 0 (iterator debugging is disabled).
    // This should be fixed in Visual C++ 2010.
    //
    // To work around this bug, include foundation/platform/datetime.h which
    // provides an overload of foundation::to_string() for boost::posix_time::ptime.
    //
    // References:
    //
    //   http://stackoverflow.com/questions/787288/problem-when-disabling-checked-iterators-in-vs2008-sp1-has-iterator-debugging0
    //   http://connect.microsoft.com/VisualStudio/feedback/details/435483/disabling-has-iterator-debugging-causes-memory-corruption-in-debug-mode-with-ostringstream
    //

    TEST_CASE(PTimeToString)
    {
        using namespace gregorian;
        using namespace posix_time;

        const ptime time(date(2010, Jun, 22), time_duration(17, 45, 31));
        const string result = to_string(time);

        EXPECT_EQ("2010-Jun-22", result);
    }

#endif
}