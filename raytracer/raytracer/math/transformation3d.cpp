#include "math/transformation3d.h"
#include "math/transformation-matrices.h"
#include "easylogging++.h"

using namespace math;


math::Transformation3D::Transformation3D(const Matrix4x4& transformation_matrix, const Matrix4x4& inverse_transformation_matrix)
    : transformation_matrix(transformation_matrix), inverse_transformation_matrix(inverse_transformation_matrix)
{
    CHECK(transformation_matrix * inverse_transformation_matrix == approx(math::identity<4>())) << "Matrices are not each other's inverses";
}

Transformation3D math::transformations::translation(const Vector3D& v)
{
    Matrix4x4 tm = transformation_matrices::translation(v);
    Matrix4x4 itm = transformation_matrices::translation(-v);

    return Transformation3D(tm, itm);
}
