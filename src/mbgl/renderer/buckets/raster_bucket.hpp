#pragma once

#include <mbgl/gfx/index_buffer.hpp>
#include <mbgl/gfx/texture.hpp>
#include <mbgl/gfx/vertex_buffer.hpp>
#include <mbgl/programs/raster_program.hpp>
#include <mbgl/renderer/bucket.hpp>
#include <mbgl/renderer/tile_mask.hpp>
#include <mbgl/util/image.hpp>
#include <mbgl/util/mat4.hpp>

#include <optional>

namespace mbgl {

class RasterBucket final : public Bucket {
public:
    RasterBucket(PremultipliedImage&&);
    RasterBucket(std::shared_ptr<PremultipliedImage>);
    ~RasterBucket() override;

    void upload(gfx::UploadPass&) override;
    bool hasData() const override;

    void clear();
    void setImage(std::shared_ptr<PremultipliedImage>);
    void setMask(TileMask&&);

    std::shared_ptr<PremultipliedImage> image;
    std::optional<gfx::Texture> texture;
    TileMask mask{ { 0, 0, 0 } };

    // Bucket specific vertices are used for Image Sources only
    // Raster Tile Sources use the default buffers from Painter
    gfx::VertexVector<RasterLayoutVertex> vertices;
    gfx::IndexVector<gfx::Triangles> indices;
    SegmentVector<RasterAttributes> segments;

    std::optional<gfx::VertexBuffer<RasterLayoutVertex>> vertexBuffer;
    std::optional<gfx::IndexBuffer> indexBuffer;
};

} // namespace mbgl
