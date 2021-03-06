
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2012 Francois Beaune, Jupiter Jazz
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

#ifndef APPLESEED_FOUNDATION_UTILITY_LOG_FILELOGTARGET_H
#define APPLESEED_FOUNDATION_UTILITY_LOG_FILELOGTARGET_H

// appleseed.foundation headers.
#include "foundation/utility/log/filelogtargetbase.h"
#include "foundation/utility/log/logmessage.h"

// Standard headers.
#include <cstddef>
#include <cstdio>

//
// On Windows, define FOUNDATIONDLL to __declspec(dllexport) when building the DLL
// and to __declspec(dllimport) when building an application using the DLL.
// Other platforms don't use this export mechanism and the symbol FOUNDATIONDLL is
// defined to evaluate to nothing.
//

#ifndef FOUNDATIONDLL
#ifdef _WIN32
#ifdef APPLESEED_FOUNDATION_EXPORTS
#define FOUNDATIONDLL __declspec(dllexport)
#else
#define FOUNDATIONDLL __declspec(dllimport)
#endif
#else
#define FOUNDATIONDLL
#endif
#endif

namespace foundation
{

//
// A log target that outputs to a file.
//

class FOUNDATIONDLL FileLogTarget
  : public FileLogTargetBase
{
  public:
    // Delete this instance.
    virtual void release();

    // Write a message.
    virtual void write(
        const LogMessage::Category  category,
        const char*                 file,
        const size_t                line,
        const char*                 message);

    bool open(const char* filename);

    void close();

    bool is_open() const;

  private:
    friend FOUNDATIONDLL FileLogTarget* create_file_log_target();

    std::FILE*  m_file;

    // Constructor.
    FileLogTarget();

    // Destructor.
    ~FileLogTarget();
};

// Create an instance of a log target that outputs to a file.
FOUNDATIONDLL FileLogTarget* create_file_log_target();

}       // namespace foundation

#endif  // !APPLESEED_FOUNDATION_UTILITY_LOG_FILELOGTARGET_H
