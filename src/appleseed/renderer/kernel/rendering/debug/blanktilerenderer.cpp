
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

// Interface header.
#include "blanktilerenderer.h"

// appleseed.renderer headers.
#include "renderer/modeling/frame/frame.h"

// appleseed.foundation headers.
#include "foundation/image/canvasproperties.h"
#include "foundation/image/image.h"
#include "foundation/image/tile.h"

// Forward declarations.
namespace foundation    { class AbortSwitch; }

using namespace foundation;
using namespace std;

namespace renderer
{

namespace
{
    //
    // Blank tile renderer.
    //

    class BlankTileRenderer
      : public ITileRenderer
    {
      public:
        // Delete this instance.
        virtual void release()
        {
            delete this;
        }

        // Render a tile.
        virtual void render_tile(
            const Frame&    frame,
            const size_t    tile_x,
            const size_t    tile_y,
            AbortSwitch&    abort_switch)
        {
            Image& image = frame.image();

            assert(tile_x < image.properties().m_tile_count_x);
            assert(tile_y < image.properties().m_tile_count_y);

            Tile& tile = image.tile(tile_x, tile_y);

            // Set all pixels of the tile to opaque black.
            tile.clear(Color4f(0.0f, 0.0f, 0.0f, 1.0f));
        }
    };
}


//
// BlankTileRendererFactory class implementation.
//

void BlankTileRendererFactory::release()
{
    delete this;
}

ITileRenderer* BlankTileRendererFactory::create()
{
    return new BlankTileRenderer();
}

}   // namespace renderer
