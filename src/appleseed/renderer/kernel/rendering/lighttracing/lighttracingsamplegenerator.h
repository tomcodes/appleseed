
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

#ifndef APPLESEED_RENDERER_KERNEL_RENDERING_LIGHTTRACING_LIGHTTRACINGSAMPLEGENERATOR_H
#define APPLESEED_RENDERER_KERNEL_RENDERING_LIGHTTRACING_LIGHTTRACINGSAMPLEGENERATOR_H

// appleseed.renderer headers.
#include "renderer/kernel/rendering/isamplegenerator.h"

// appleseed.main headers.
#include "main/dllsymbol.h"

// Standard headers.
#include <cstddef>

// Forward declarations.
namespace renderer      { class Frame; }

namespace renderer
{

class DLLSYMBOL LightTracingSampleGeneratorFactory
  : public ISampleGeneratorFactory
{
  public:
    // Constructor.
    explicit LightTracingSampleGeneratorFactory(Frame& frame);

    // Delete this instance.
    virtual void release();

    // Return a new sample generator instance.
    virtual ISampleGenerator* create(
        const size_t    generator_index,
        const size_t    generator_count);

  private:
    Frame&  m_frame;
};

}       // namespace renderer

#endif  // !APPLESEED_RENDERER_KERNEL_RENDERING_LIGHTTRACING_LIGHTTRACINGSAMPLEGENERATOR_H