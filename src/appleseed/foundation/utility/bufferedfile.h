
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

#ifndef APPLESEED_FOUNDATION_UTILITY_BUFFEREDFILE_H
#define APPLESEED_FOUNDATION_UTILITY_BUFFEREDFILE_H

// appleseed.foundation headers.
#include "foundation/platform/types.h"

// Standard headers.
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <string>

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
// A thread-local buffered file providing high performance disk I/O.
//
// Notes:
//
//   - Buffered and unbuffered read/write may be mixed freely.
//
//   - For performance reasons, error checking is reduced to the minimum.
//
//   - After an error has been reported by any of the method of the class
//     except open(), the BufferedFile object is left in an unknown state
//     and no other method except close() may be called safely.
//

class FOUNDATIONDLL BufferedFile
{
  public:
    // File type.
    enum FileType
    {
        TextType = 0,
        BinaryType
    };

    // File access mode.
    enum FileMode
    {
        ReadMode = 0,
        WriteMode
    };

    // Default read/write buffer size, in bytes.
    enum
    {
        DefaultBufferSize = 32 * 1024
    };

    // Initial position for seek().
    enum SeekOrigin
    {
        SeekFromBeginning = 0,  // offset must be positive or null
        SeekFromCurrent,        // offset may be positive, negative or null
        SeekFromEnd             // offset must be negative or null
    };

    // Constructors.
    BufferedFile();
    BufferedFile(
        const char*             path,
        const FileType          type,
        const FileMode          mode,
        const size_t            buffer_size = DefaultBufferSize);

    // Destructor, closes the file if it is still open.
    ~BufferedFile();

    // Open a file.
    // Return true on success, false on error.
    bool open(
        const char*             path,
        const FileType          type,
        const FileMode          mode,
        const size_t            buffer_size = DefaultBufferSize);

    // Close the file.
    // Return true on success, false on error.
    bool close();

    // Return true if the file is open, false otherwise.
    bool is_open() const;

    // Read a contiguous sequence of bytes from the file.
    // The file must be open in read mode.
    // Return the number of bytes that were successfully read.
    size_t read(
        void*                   outbuf,
        const size_t            size);

    // Read one byte from the file.
    // The file must be open in read mode.
    // Return the number of bytes that were successfully read (0 or 1).
    size_t read(
        void*                   outbuf);

    // Read an object from the file.
    // The file must be open in read mode.
    // Return the number of bytes that were successfully read.
    template <typename T>
    size_t read(T&              object);

    // Same as read(), but without buffering.
    size_t read_unbuf(
        void*                   outbuf,
        const size_t            size);
    template <typename T>
    size_t read_unbuf(T&        object);

    // Write a contiguous sequence of bytes to the file.
    // The file must be open in write mode.
    // Return the number of bytes that were successfully written.
    size_t write(
        const void*             inbuf,
        const size_t            size);

    // Write one byte to the file.
    // The file must be open in write mode.
    // Return the number of bytes that were successfully written (0 or 1).
    size_t write(
        const void*             inbuf);

    // Write an object to the file.
    // The file must be open in write mode.
    // Return the number of bytes that were successfully written.
    template <typename T>
    size_t write(const T&       object);

    // Same as write(), but without buffering.
    size_t write_unbuf(
        const void*             inbuf,
        const size_t            size);
    template <typename T>
    size_t write_unbuf(const T& object);

    // Move the file pointer to a specified location.
    // The file must be binary, and open in read or write mode.
    // Return true on success, false on error.
    bool seek(
        const int64             offset,
        const SeekOrigin        origin);

    // Return the current position of the file pointer.
    // The file must be binary, and open in read or write mode.
    int64 tell() const;

  private:
    std::FILE*  m_file;
    FileMode    m_file_mode;
    int64       m_file_index;       // index in the file of the first byte of the I/O buffer
    uint8*      m_buffer;           // I/O buffer
    size_t      m_buffer_size;      // size of the I/O buffer
    size_t      m_buffer_end;       // one past the index of the last byte in the I/O buffer
    size_t      m_buffer_index;     // index of the next byte in the I/O buffer

    // Reset the internal state of the object.
    void reset();

    // Invalidate the I/O buffer (read mode only).
    void invalidate_buffer();

    // Fill the I/O buffer (read mode only).
    void fill_buffer();

    // Flush the I/O buffer to disk (write mode only).
    // Return true on success, false on error.
    bool flush_buffer();
};


//
// BufferedFile class implementation.
//

inline size_t BufferedFile::read(
    void*               outbuf)
{
    assert(m_file);
    assert(m_file_mode == ReadMode);
    assert(m_buffer);
    assert(outbuf);

    // If the I/O buffer is exhausted, refill it.
    if (m_buffer_index == m_buffer_end)
    {
        // Fill the I/O buffer.
        fill_buffer();

        // Stop if the end of the file has been reached.
        if (m_buffer_end == 0)
            return 0;
    }

    // Copy one byte from the I/O buffer to the output buffer.
    reinterpret_cast<uint8*>(outbuf)[0] = m_buffer[m_buffer_index++];

    // Return the number of bytes successfully read.
    return 1;
}

template <typename T>
inline size_t BufferedFile::read(T& object)
{
    return read(&object, sizeof(T));
}

template <typename T>
inline size_t BufferedFile::read_unbuf(T& object)
{
    return read_unbuf(&object, sizeof(T));
}

inline size_t BufferedFile::write(
    const void*         inbuf)
{
    assert(m_file);
    assert(m_file_mode == WriteMode);
    assert(m_buffer);
    assert(inbuf);

    // If the I/O buffer is full, flush it to disk.
    if (m_buffer_index == m_buffer_end)
    {
        // Flush the I/O buffer to disk.
        if (!flush_buffer())
            return 0;
    }

    // Copy one byte from the input buffer to the I/O buffer.
    m_buffer[m_buffer_index++] = reinterpret_cast<const uint8*>(inbuf)[0];

    // Return the number of bytes successfully written.
    return 1;
}

template <typename T>
inline size_t BufferedFile::write(const T& object)
{
    return write(&object, sizeof(T));
}

template <>
inline size_t BufferedFile::write(const std::string& s)
{
    return write(s.c_str(), s.size());
}

template <typename T>
inline size_t BufferedFile::write_unbuf(const T& object)
{
    return write_unbuf(&object, sizeof(T));
}

template <>
inline size_t BufferedFile::write_unbuf(const std::string& s)
{
    return write_unbuf(s.c_str(), s.size());
}

inline int64 BufferedFile::tell() const
{
    assert(m_file);
    assert(m_buffer);

    return m_file_index + static_cast<int64>(m_buffer_index);
}

inline void BufferedFile::invalidate_buffer()
{
    assert(m_file_mode == ReadMode);

    m_buffer_end = 0;
    m_buffer_index = 0;
}

}       // namespace foundation

#endif  // !APPLESEED_FOUNDATION_UTILITY_BUFFEREDFILE_H
