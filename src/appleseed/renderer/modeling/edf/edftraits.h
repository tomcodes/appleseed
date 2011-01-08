
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

#ifndef APPLESEED_RENDERER_MODELING_EDF_EDFTRAITS_H
#define APPLESEED_RENDERER_MODELING_EDF_EDFTRAITS_H

// appleseed.renderer headers.
#include "renderer/global/global.h"
#include "renderer/modeling/entity/entitytraits.h"
#include "renderer/modeling/scene/containers.h"

// Forward declarations.
namespace renderer  { class EDF; }
namespace renderer  { class EDFFactoryRegistrar; }

namespace renderer
{

//
// EDF entity traits.
//

template <>
struct EntityTraits<renderer::EDF>
{
    typedef renderer::EDFContainer ContainerType;
    typedef renderer::EDFFactoryRegistrar FactoryRegistrarType;

    static const char* get_entity_type_name()                           { return "edf"; }
    static const char* get_human_readable_entity_type_name()            { return "EDF"; }
    static const char* get_human_readable_collection_type_name()        { return "EDFs"; }

    template <typename ParentEntity>
    static ContainerType& get_entity_container(ParentEntity& parent)    { return parent.edfs(); }
};

}       // namespace renderer

#endif  // !APPLESEED_RENDERER_MODELING_EDF_EDFTRAITS_H