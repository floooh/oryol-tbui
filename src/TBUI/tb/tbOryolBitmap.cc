//------------------------------------------------------------------------------
//  tbOryolBitmap.cc
//------------------------------------------------------------------------------
#include "Pre.h"
#include "tbOryolBitmap.h"
#include "tbOryolBatchRenderer.h"
#include "tb_bitmap_fragment.h"
#include "TBUIShaders.h"

namespace Oryol {
namespace _priv {

//------------------------------------------------------------------------------
tbOryolBitmap::tbOryolBitmap(tbOryolBatchRenderer* rnd) :
renderer(rnd),
width(0),
height(0),
label(ResourceLabel::Invalid) {
    // empty
}

//------------------------------------------------------------------------------
tbOryolBitmap::~tbOryolBitmap() {
    if (this->texture.IsValid()) {
        this->destroyTexture();
    }
}

//------------------------------------------------------------------------------
bool
tbOryolBitmap::Init(int w, int h, tb::uint32* data) {
    o_assert_dbg(tb::TBGetNearestPowerOfTwo(w) == w);
    o_assert_dbg(tb::TBGetNearestPowerOfTwo(h) == h);
    this->width = w;
    this->height = h;
    this->createTexture(data);
    return true;
}

//------------------------------------------------------------------------------
void
tbOryolBitmap::SetData(uint32_t* data) {
    o_assert_dbg(this->texture.IsValid());
    this->destroyTexture();
    this->createTexture(data);
}

//------------------------------------------------------------------------------
void
tbOryolBitmap::createTexture(tb::uint32* data) {
    o_assert_dbg(!this->texture.IsValid());
    o_assert_dbg(this->renderer);

    const int byteSize = this->width * this->height * sizeof(tb::uint32);

    this->label = Gfx::PushResourceLabel();
    this->texture = Gfx::CreateTexture(TextureDesc()
        .Type(TextureType::Texture2D)
        .Width(this->width)
        .Height(this->height)
        .NumMipMaps(1)
        .Format(PixelFormat::RGBA8)
        .WrapU(TextureWrapMode::Repeat)
        .WrapV(TextureWrapMode::Repeat)
        .MinFilter(TextureFilterMode::Nearest)
        .MagFilter(TextureFilterMode::Nearest)
        .MipSize(0, 0, byteSize)
        .MipContent(0, 0, data));
    Gfx::PopResourceLabel();
}

//------------------------------------------------------------------------------
void
tbOryolBitmap::destroyTexture() {
    o_assert_dbg(this->texture.IsValid());
    this->renderer->deferDeleteTexture(this->label);
    this->texture.Invalidate();
    this->label = ResourceLabel::Invalid;
}

} // namespace _priv
} // namespace Oryol
