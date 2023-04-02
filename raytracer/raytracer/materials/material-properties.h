#pragma once

#include "imaging/color.h"


namespace raytracer
{
    struct MaterialProperties
    {
    private:
        MaterialProperties(
            const imaging::Color& ambient,
            const imaging::Color& diffuse,
            const imaging::Color& specular,
            const double& specular_exponent,
            const imaging::Color& light_filtering,
            const double& reflectivity,
            const double& translucency,
            const double& transparency,
            const double& refractive_index
        );

    public:
        const imaging::Color ambient;
        const imaging::Color diffuse;
        const imaging::Color specular;
        const double specular_exponent;
        const imaging::Color light_filtering;
        const double reflectivity;
        const double translucency;
        const double transparency;
        const double refractive_index;

        friend class MaterialPropertiesBuilder;
    };

    class MaterialPropertiesBuilder
    {
    public:
        MaterialPropertiesBuilder();

        MaterialPropertiesBuilder& ambient(const imaging::Color& color);
        MaterialPropertiesBuilder& diffuse(const imaging::Color& color);
        MaterialPropertiesBuilder& specular(const imaging::Color& color);
        MaterialPropertiesBuilder& specular_exponent(const double& integer);
        MaterialPropertiesBuilder& light_filtering(const imaging::Color& color);
        MaterialPropertiesBuilder& reflectivity(const double& integer);
        MaterialPropertiesBuilder& translucency(const double& integer);
        MaterialPropertiesBuilder& transparent(const double& transparency, const double& refractive_index);

        operator raytracer::MaterialProperties() const;

    private:
        imaging::Color m_ambient;
        imaging::Color m_diffuse;
        imaging::Color m_specular;
        double m_specular_exponent;
        imaging::Color m_light_filtering;
        double m_reflectivity;
        double m_translucency;
        double m_transparency;
        double m_refractive_index;
    };

    inline MaterialPropertiesBuilder create_material_properties_with()
    {
        return MaterialPropertiesBuilder();
    }
}