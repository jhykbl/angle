//
// Copyright 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// VertexArray9.h: Defines the rx::VertexArray9 class which implements rx::VertexArrayImpl.

#ifndef LIBANGLE_RENDERER_D3D_D3D9_VERTEXARRAY9_H_
#define LIBANGLE_RENDERER_D3D_D3D9_VERTEXARRAY9_H_

#include "libANGLE/Context.h"
#include "libANGLE/renderer/VertexArrayImpl.h"
#include "libANGLE/renderer/d3d/d3d9/Context9.h"
#include "libANGLE/renderer/d3d/d3d9/Renderer9.h"

namespace rx
{
class Renderer9;

class VertexArray9 : public VertexArrayImpl
{
  public:
    VertexArray9(const gl::VertexArrayState &data) : VertexArrayImpl(data) {}

    gl::Error syncState(const gl::Context *context,
                        const gl::VertexArray::DirtyBits &dirtyBits,
                        const gl::VertexArray::DirtyAttribBitsArray &attribBits,
                        const gl::VertexArray::DirtyBindingBitsArray &bindingBits) override;

    ~VertexArray9() override {}

    Serial getCurrentStateSerial() const { return mCurrentStateSerial; }

  private:
    Serial mCurrentStateSerial;
};

inline gl::Error VertexArray9::syncState(const gl::Context *context,
                                         const gl::VertexArray::DirtyBits &dirtyBits,
                                         const gl::VertexArray::DirtyAttribBitsArray &attribBits,
                                         const gl::VertexArray::DirtyBindingBitsArray &bindingBits)
{
    ASSERT(dirtyBits.any());
    Renderer9 *renderer = GetImplAs<Context9>(context)->getRenderer();
    mCurrentStateSerial = renderer->generateSerial();
    return gl::NoError();
}
}  // namespace rx

#endif // LIBANGLE_RENDERER_D3D_D3D9_VERTEXARRAY9_H_
