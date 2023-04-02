#pragma once

#include "imaging/bitmap.h"
#include "raytracers/scene.h"
#include "samplers/sampler.h"
#include "raytracers/ray-tracer.h"
#include "math/rasterizer.h"
#include "math/point.h"
#include "tasks/task-scheduler.h"

namespace raytracer
{
    namespace renderers
    {
        namespace _private_
        {
            /// <summary>
            /// Actual Renderer implementation.
            /// </summary>
            class RendererImplementation
            {
            public:
                /// <summary>
                /// Renders the given <paramref name="scene" /> and returns
                /// the resulting picture as a bitmap.
                /// </summary>
                virtual std::shared_ptr<imaging::Bitmap> render(const Scene& scene) const = 0;
            };
        }
    }

    /// <summary>
    /// Wrapper for renderers. Members are to be accessed using the -&gt; operator.
    /// Actual members are defined in RenderImplementation.
    /// </summary>
    class Renderer
    {
    public:
        explicit Renderer(std::shared_ptr<renderers::_private_::RendererImplementation> implementation = nullptr)
            : m_implementation(implementation) { }

        Renderer(const Renderer& r) = default;
        Renderer(Renderer&& r) = default;

        const renderers::_private_::RendererImplementation* operator ->() const { return m_implementation.get(); }

        operator bool() const { return m_implementation != nullptr; }

    private:
        std::shared_ptr<renderers::_private_::RendererImplementation> m_implementation;
    };
}