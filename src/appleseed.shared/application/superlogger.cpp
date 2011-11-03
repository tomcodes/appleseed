
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2011 Francois Beaune
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

// Interface header.
#include "superlogger.h"

// Standard headers.
#include <cstddef>
#include <cstdio>

using namespace foundation;
using namespace std;

namespace appleseed {
namespace shared {

SuperLogger::SuperLogger()
  : m_log_target(create_open_file_log_target(stderr))
{
    add_target(m_log_target);
}

SuperLogger::~SuperLogger()
{
    delete m_log_target;
}

namespace
{
    void save_formatting_flags(const LogTargetBase& log_target, LogMessage::FormattingFlags flags[])
    {
        for (size_t i = 0; i < LogMessage::NumMessageCategories; ++i)
            flags[i] = log_target.get_formatting_flags(static_cast<LogMessage::Category>(i));
    }

    void restore_formatting_flags(LogTargetBase& log_target, const LogMessage::FormattingFlags flags[])
    {
        for (size_t i = 0; i < LogMessage::NumMessageCategories; ++i)
            log_target.set_formatting_flags(static_cast<LogMessage::Category>(i), flags[i]);
    }
}

void SuperLogger::enable_message_coloring()
{
    LogMessage::FormattingFlags flags[LogMessage::NumMessageCategories];
    save_formatting_flags(*m_log_target, flags);

    remove_target(m_log_target);
    delete m_log_target;

    m_log_target = create_console_log_target(stderr);
    add_target(m_log_target);

    restore_formatting_flags(*m_log_target, flags);
}

LogTargetBase& SuperLogger::get_log_target() const
{
    return *m_log_target;
}

}   // namespace shared
}   // namespace appleseed