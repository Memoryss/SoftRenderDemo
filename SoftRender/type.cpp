#include "type.h"

namespace SoftRenderer
{

    float dot(const vec2 &u, const vec2 &v)
    {
        return u.x * v.x + u.y * v.y;
    }

    float length(const vec2 &u)
    {
        return sqrt(u.x * u.x + u.y * u.y);
    }

    float length2(const vec2 &u)
    {
        return u.x * u.x + u.y * u.y;
    }

    vec2 mix(const vec2 &u, const vec2 &v, float a)
    {
        return u * (1.0f - a) + v * a;
    }

    vec2 normalize(const vec2 &u)
    {
        return u / sqrt(u.x * u.x + u.y * u.y);
    }

    vec2 reflect(const vec2 &i, const vec2 &n)
    {
        return i - 2.0f * dot(n, i) * n;
    }

    vec2 refract(const vec2 &i, const vec2 &n, float eta)
    {
        vec2 r;

        float ndoti = dot(n, i), k = 1.0f - eta * eta * (1.0f - ndoti * ndoti);

        if (k >= 0.0f)
        {
            r = eta * i - n * (eta * ndoti + sqrt(k));
        }

        return r;
    }

    vec2 rotate(const vec2 &u, float angle)
    {
        angle = angle / 180.0f * (float)M_PI;

        float c = cos(angle), s = sin(angle);

        return vec2(u.x * c - u.y * s, u.x * s + u.y * c);
    }

    vec3 cross(const vec3 &u, const vec3 &v)
    {
        return vec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
    }

    float dot(const vec3 &u, const vec3 &v)
    {
        return u.x * v.x + u.y * v.y + u.z * v.z;
    }

    float length(const vec3 &u)
    {
        return sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
    }

    float length2(const vec3 &u)
    {
        return u.x * u.x + u.y * u.y + u.z * u.z;
    }

    vec3 mix(const vec3 &u, const vec3 &v, float a)
    {
        return u * (1.0f - a) + v * a;
    }

    vec3 normalize(const vec3 &u)
    {
        return u / sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
    }

    vec3 reflect(const vec3 &i, const vec3 &n)
    {
        return i - 2.0f * dot(n, i) * n;
    }

    vec3 refract(const vec3 &i, const vec3 &n, float eta)
    {
        vec3 r;

        float ndoti = dot(n, i), k = 1.0f - eta * eta * (1.0f - ndoti * ndoti);

        if (k >= 0.0f)
        {
            r = eta * i - n * (eta * ndoti + sqrt(k));
        }

        return r;
    }

    vec3 rotate(const vec3 &u, float angle, const vec3 &v)
    {
        return *(vec3*)&(rotate(angle, v) * vec4(u, 1.0f));
    }

    mat2x2::mat2x2()
    {
    }

    mat2x2::mat2x2(float num)
    {
        m[0] = num; m[2] = 0.0f;
        m[1] = 0.0f; m[3] = num;
    }

    mat2x2::~mat2x2()
    {
    }

    mat2x2::mat2x2(const mat2x2 &Matrix)
    {
        for (int i = 0; i < 4; i++)
        {
            m[i] = Matrix.m[i];
        }
    }

    mat2x2::mat2x2(const vec2 &col1, const vec2 &col2)
    {
        m[0] = col1.x; m[2] = col2.x;
        m[1] = col1.y; m[3] = col2.y;
    }

    mat2x2::mat2x2(float c1r1, float c1r2, float c2r1, float c2r2)
    {
        m[0] = c1r1; m[2] = c2r1;
        m[1] = c1r2; m[3] = c2r2;
    }

    mat2x2::mat2x2(const mat3x3 &Matrix)
    {
        m[0] = Matrix.m[0]; m[2] = Matrix.m[3];
        m[1] = Matrix.m[1]; m[3] = Matrix.m[4];
    }

    mat2x2::mat2x2(const mat4x4 &Matrix)
    {
        m[0] = Matrix.m[0]; m[2] = Matrix.m[4];
        m[1] = Matrix.m[1]; m[3] = Matrix.m[5];
    }

    mat2x2& mat2x2::operator = (const mat2x2 &Matrix)
    {
        for (int i = 0; i < 4; i++)
        {
            m[i] = Matrix.m[i];
        }

        return *this;
    }

    float& mat2x2::operator [] (int i)
    {
        return m[i];
    }

    float* mat2x2::operator & ()
    {
        return (float*)this;
    }

    mat2x2 operator * (const mat2x2 &Matrix1, const mat2x2 &Matrix2)
    {
        mat2x2 Matrix3;

        Matrix3.m[0] = Matrix1.m[0] * Matrix2.m[0] + Matrix1.m[2] * Matrix2.m[1];
        Matrix3.m[1] = Matrix1.m[1] * Matrix2.m[0] + Matrix1.m[3] * Matrix2.m[1];
        Matrix3.m[2] = Matrix1.m[0] * Matrix2.m[2] + Matrix1.m[2] * Matrix2.m[3];
        Matrix3.m[3] = Matrix1.m[1] * Matrix2.m[2] + Matrix1.m[3] * Matrix2.m[3];

        return Matrix3;
    }

    vec2 operator * (const mat2x2 &Matrix, const vec2 &u)
    {
        vec2 v;

        v.x = Matrix.m[0] * u.x + Matrix.m[2] * u.y;
        v.y = Matrix.m[1] * u.x + Matrix.m[3] * u.y;

        return v;
    }

    mat2x2 inverse(const mat2x2 &Matrix)
    {
        const float *m = Matrix.m;

        float det = m[0] * m[3] - m[2] * m[1];

        mat2x2 Inverse;

        Inverse.m[0] = m[3] / det;
        Inverse.m[1] = -m[1] / det;
        Inverse.m[2] = -m[2] / det;
        Inverse.m[3] = m[0] / det;

        return Inverse;
    }

    mat2x2 transpose(const mat2x2 &Matrix)
    {
        mat2x2 Transpose;

        Transpose.m[0] = Matrix.m[0];
        Transpose.m[1] = Matrix.m[2];
        Transpose.m[2] = Matrix.m[1];
        Transpose.m[3] = Matrix.m[3];

        return Transpose;
    }

    mat3x3::mat3x3()
    {
    }

    mat3x3::mat3x3(float num)
    {
        m[0] = num; m[3] = 0.0f; m[6] = 0.0f;
        m[1] = 0.0f; m[4] = num; m[7] = 0.0f;
        m[2] = 0.0f; m[5] = 0.0f; m[8] = num;
    }

    mat3x3::~mat3x3()
    {
    }

    mat3x3::mat3x3(const mat3x3 &Matrix)
    {
        for (int i = 0; i < 9; i++)
        {
            m[i] = Matrix.m[i];
        }
    }

    mat3x3::mat3x3(const vec3 &col1, const vec3 &col2, const vec3 &col3)
    {
        m[0] = col1.x; m[3] = col2.x; m[6] = col3.x;
        m[1] = col1.y; m[4] = col2.y; m[7] = col3.y;
        m[2] = col1.z; m[5] = col2.z; m[8] = col3.z;
    }

    mat3x3::mat3x3(float c1r1, float c1r2, float c1r3, float c2r1, float c2r2, float c2r3, float c3r1, float c3r2, float c3r3)
    {
        m[0] = c1r1; m[3] = c2r1; m[6] = c3r1;
        m[1] = c1r2; m[4] = c2r2; m[7] = c3r2;
        m[2] = c1r3; m[5] = c2r3; m[8] = c3r3;
    }

    mat3x3::mat3x3(const mat2x2 &Matrix)
    {
        m[0] = Matrix.m[0]; m[3] = Matrix.m[2]; m[6] = 0.0f;
        m[1] = Matrix.m[1]; m[4] = Matrix.m[3]; m[7] = 0.0f;
        m[2] = 0.0f; m[5] = 0.0f; m[8] = 1.0f;
    }

    mat3x3::mat3x3(const mat4x4 &Matrix)
    {
        m[0] = Matrix.m[0]; m[3] = Matrix.m[4]; m[6] = Matrix.m[8];
        m[1] = Matrix.m[1]; m[4] = Matrix.m[5]; m[7] = Matrix.m[9];
        m[2] = Matrix.m[2]; m[5] = Matrix.m[6]; m[8] = Matrix.m[10];
    }

    mat3x3& mat3x3::operator = (const mat3x3 &Matrix)
    {
        for (int i = 0; i < 9; i++)
        {
            m[i] = Matrix.m[i];
        }

        return *this;
    }

    float& mat3x3::operator [] (int i)
    {
        return m[i];
    }

    float* mat3x3::operator & ()
    {
        return (float*)this;
    }

    mat3x3 operator * (const mat3x3 &Matrix1, const mat3x3 &Matrix2)
    {
        mat3x3 Matrix3;

        Matrix3.m[0] = Matrix1.m[0] * Matrix2.m[0] + Matrix1.m[3] * Matrix2.m[1] + Matrix1.m[6] * Matrix2.m[2];
        Matrix3.m[1] = Matrix1.m[1] * Matrix2.m[0] + Matrix1.m[4] * Matrix2.m[1] + Matrix1.m[7] * Matrix2.m[2];
        Matrix3.m[2] = Matrix1.m[2] * Matrix2.m[0] + Matrix1.m[5] * Matrix2.m[1] + Matrix1.m[8] * Matrix2.m[2];
        Matrix3.m[3] = Matrix1.m[0] * Matrix2.m[3] + Matrix1.m[3] * Matrix2.m[4] + Matrix1.m[6] * Matrix2.m[5];
        Matrix3.m[4] = Matrix1.m[1] * Matrix2.m[3] + Matrix1.m[4] * Matrix2.m[4] + Matrix1.m[7] * Matrix2.m[5];
        Matrix3.m[5] = Matrix1.m[2] * Matrix2.m[3] + Matrix1.m[5] * Matrix2.m[4] + Matrix1.m[8] * Matrix2.m[5];
        Matrix3.m[6] = Matrix1.m[0] * Matrix2.m[6] + Matrix1.m[3] * Matrix2.m[7] + Matrix1.m[6] * Matrix2.m[8];
        Matrix3.m[7] = Matrix1.m[1] * Matrix2.m[6] + Matrix1.m[4] * Matrix2.m[7] + Matrix1.m[7] * Matrix2.m[8];
        Matrix3.m[8] = Matrix1.m[2] * Matrix2.m[6] + Matrix1.m[5] * Matrix2.m[7] + Matrix1.m[8] * Matrix2.m[8];

        return Matrix3;
    }

    vec3 operator * (const mat3x3 &Matrix, const vec3 &u)
    {
        vec3 v;

        v.x = Matrix.m[0] * u.x + Matrix.m[3] * u.y + Matrix.m[6] * u.z;
        v.y = Matrix.m[1] * u.x + Matrix.m[4] * u.y + Matrix.m[7] * u.z;
        v.z = Matrix.m[2] * u.x + Matrix.m[5] * u.y + Matrix.m[8] * u.z;

        return v;
    }

    float det2x2sub(const float *m, int i0, int i1, int i2, int i3)
    {
        return m[i0] * m[i3] - m[i2] * m[i1];
    }

    mat3x3 inverse(const mat3x3 &Matrix)
    {
        const float *m = Matrix.m;

        float det = 0.0f;

        det += m[0] * det2x2sub(m, 4, 5, 7, 8);
        det -= m[3] * det2x2sub(m, 1, 2, 7, 8);
        det += m[6] * det2x2sub(m, 1, 2, 4, 5);

        mat3x3 Inverse;

        Inverse.m[0] = det2x2sub(m, 4, 5, 7, 8) / det;
        Inverse.m[1] = -det2x2sub(m, 1, 2, 7, 8) / det;
        Inverse.m[2] = det2x2sub(m, 1, 2, 4, 5) / det;
        Inverse.m[3] = -det2x2sub(m, 3, 5, 6, 8) / det;
        Inverse.m[4] = det2x2sub(m, 0, 2, 6, 8) / det;
        Inverse.m[5] = -det2x2sub(m, 0, 2, 3, 5) / det;
        Inverse.m[6] = det2x2sub(m, 3, 4, 6, 7) / det;
        Inverse.m[7] = -det2x2sub(m, 0, 1, 6, 7) / det;
        Inverse.m[8] = det2x2sub(m, 0, 1, 3, 4) / det;

        return Inverse;
    }

    mat3x3 transpose(const mat3x3 &Matrix)
    {
        mat3x3 Transpose;

        Transpose.m[0] = Matrix.m[0];
        Transpose.m[1] = Matrix.m[3];
        Transpose.m[2] = Matrix.m[6];
        Transpose.m[3] = Matrix.m[1];
        Transpose.m[4] = Matrix.m[4];
        Transpose.m[5] = Matrix.m[7];
        Transpose.m[6] = Matrix.m[2];
        Transpose.m[7] = Matrix.m[5];
        Transpose.m[8] = Matrix.m[8];

        return Transpose;
    }

    mat4x4::mat4x4()
    {
    }

    mat4x4::mat4x4(float num)
    {
        m[0] = num; m[4] = 0.0f; m[8] = 0.0f; m[12] = 0.0f;
        m[1] = 0.0f; m[5] = num; m[9] = 0.0f; m[13] = 0.0f;
        m[2] = 0.0f; m[6] = 0.0f; m[10] = num; m[14] = 0.0f;
        m[3] = 0.0f; m[7] = 0.0f; m[11] = 0.0f; m[15] = num;
    }

    mat4x4::~mat4x4()
    {
    }

    mat4x4::mat4x4(const mat4x4 &Matrix)
    {
        for (int i = 0; i < 16; i++)
        {
            m[i] = Matrix.m[i];
        }
    }

    mat4x4::mat4x4(const vec4 &col1, const vec4 &col2, const vec4 &col3, const vec4 &col4)
    {
        m[0] = col1.x; m[4] = col2.x; m[8] = col3.x; m[12] = col4.x;
        m[1] = col1.y; m[5] = col2.y; m[9] = col3.y; m[13] = col4.y;
        m[2] = col1.z; m[6] = col2.z; m[10] = col3.z; m[14] = col4.z;
        m[3] = col1.w; m[7] = col2.w; m[11] = col3.w; m[15] = col4.w;
    }

    mat4x4::mat4x4(float c1r1, float c1r2, float c1r3, float c1r4, float c2r1, float c2r2, float c2r3, float c2r4, float c3r1, float c3r2, float c3r3, float c3r4, float c4r1, float c4r2, float c4r3, float c4r4)
    {
        m[0] = c1r1; m[4] = c2r1; m[8] = c3r1; m[12] = c4r1;
        m[1] = c1r2; m[5] = c2r2; m[9] = c3r2; m[13] = c4r2;
        m[2] = c1r3; m[6] = c2r3; m[10] = c3r3; m[14] = c4r3;
        m[3] = c1r4; m[7] = c2r4; m[11] = c3r4; m[15] = c4r4;
    }

    mat4x4::mat4x4(const mat2x2 &Matrix)
    {
        m[0] = Matrix.m[0]; m[4] = Matrix.m[2]; m[8] = 0.0f; m[12] = 0.0f;
        m[1] = Matrix.m[1]; m[5] = Matrix.m[3]; m[9] = 0.0f; m[13] = 0.0f;
        m[2] = 0.0f; m[6] = 0.0f; m[10] = 1.0f; m[14] = 0.0f;
        m[3] = 0.0f; m[7] = 0.0f; m[11] = 0.0f; m[15] = 1.0f;
    }

    mat4x4::mat4x4(const mat3x3 &Matrix)
    {
        m[0] = Matrix.m[0]; m[4] = Matrix.m[3]; m[8] = Matrix.m[6]; m[12] = 0.0f;
        m[1] = Matrix.m[1]; m[5] = Matrix.m[4]; m[9] = Matrix.m[7]; m[13] = 0.0f;
        m[2] = Matrix.m[2]; m[6] = Matrix.m[5]; m[10] = Matrix.m[8]; m[14] = 0.0f;
        m[3] = 0.0f; m[7] = 0.0f; m[11] = 0.0f; m[15] = 1.0f;
    }

    mat4x4& mat4x4::operator = (const mat4x4 &Matrix)
    {
        for (int i = 0; i < 16; i++)
        {
            m[i] = Matrix.m[i];
        }

        return *this;
    }

    float& mat4x4::operator [] (int i)
    {
        return m[i];
    }

    float* mat4x4::operator & ()
    {
        return (float*)this;
    }

    mat4x4 operator * (const mat4x4 &Matrix1, const mat4x4 &Matrix2)
    {
        mat4x4 Matrix3;

        Matrix3.m[0] = Matrix1.m[0] * Matrix2.m[0] + Matrix1.m[4] * Matrix2.m[1] + Matrix1.m[8] * Matrix2.m[2] + Matrix1.m[12] * Matrix2.m[3];
        Matrix3.m[1] = Matrix1.m[1] * Matrix2.m[0] + Matrix1.m[5] * Matrix2.m[1] + Matrix1.m[9] * Matrix2.m[2] + Matrix1.m[13] * Matrix2.m[3];
        Matrix3.m[2] = Matrix1.m[2] * Matrix2.m[0] + Matrix1.m[6] * Matrix2.m[1] + Matrix1.m[10] * Matrix2.m[2] + Matrix1.m[14] * Matrix2.m[3];
        Matrix3.m[3] = Matrix1.m[3] * Matrix2.m[0] + Matrix1.m[7] * Matrix2.m[1] + Matrix1.m[11] * Matrix2.m[2] + Matrix1.m[15] * Matrix2.m[3];
        Matrix3.m[4] = Matrix1.m[0] * Matrix2.m[4] + Matrix1.m[4] * Matrix2.m[5] + Matrix1.m[8] * Matrix2.m[6] + Matrix1.m[12] * Matrix2.m[7];
        Matrix3.m[5] = Matrix1.m[1] * Matrix2.m[4] + Matrix1.m[5] * Matrix2.m[5] + Matrix1.m[9] * Matrix2.m[6] + Matrix1.m[13] * Matrix2.m[7];
        Matrix3.m[6] = Matrix1.m[2] * Matrix2.m[4] + Matrix1.m[6] * Matrix2.m[5] + Matrix1.m[10] * Matrix2.m[6] + Matrix1.m[14] * Matrix2.m[7];
        Matrix3.m[7] = Matrix1.m[3] * Matrix2.m[4] + Matrix1.m[7] * Matrix2.m[5] + Matrix1.m[11] * Matrix2.m[6] + Matrix1.m[15] * Matrix2.m[7];
        Matrix3.m[8] = Matrix1.m[0] * Matrix2.m[8] + Matrix1.m[4] * Matrix2.m[9] + Matrix1.m[8] * Matrix2.m[10] + Matrix1.m[12] * Matrix2.m[11];
        Matrix3.m[9] = Matrix1.m[1] * Matrix2.m[8] + Matrix1.m[5] * Matrix2.m[9] + Matrix1.m[9] * Matrix2.m[10] + Matrix1.m[13] * Matrix2.m[11];
        Matrix3.m[10] = Matrix1.m[2] * Matrix2.m[8] + Matrix1.m[6] * Matrix2.m[9] + Matrix1.m[10] * Matrix2.m[10] + Matrix1.m[14] * Matrix2.m[11];
        Matrix3.m[11] = Matrix1.m[3] * Matrix2.m[8] + Matrix1.m[7] * Matrix2.m[9] + Matrix1.m[11] * Matrix2.m[10] + Matrix1.m[15] * Matrix2.m[11];
        Matrix3.m[12] = Matrix1.m[0] * Matrix2.m[12] + Matrix1.m[4] * Matrix2.m[13] + Matrix1.m[8] * Matrix2.m[14] + Matrix1.m[12] * Matrix2.m[15];
        Matrix3.m[13] = Matrix1.m[1] * Matrix2.m[12] + Matrix1.m[5] * Matrix2.m[13] + Matrix1.m[9] * Matrix2.m[14] + Matrix1.m[13] * Matrix2.m[15];
        Matrix3.m[14] = Matrix1.m[2] * Matrix2.m[12] + Matrix1.m[6] * Matrix2.m[13] + Matrix1.m[10] * Matrix2.m[14] + Matrix1.m[14] * Matrix2.m[15];
        Matrix3.m[15] = Matrix1.m[3] * Matrix2.m[12] + Matrix1.m[7] * Matrix2.m[13] + Matrix1.m[11] * Matrix2.m[14] + Matrix1.m[15] * Matrix2.m[15];

        return Matrix3;
    }

    vec4 operator * (const mat4x4 &Matrix, const vec4 &u)
    {
        vec4 v;

        v.x = Matrix.m[0] * u.x + Matrix.m[4] * u.y + Matrix.m[8] * u.z + Matrix.m[12] * u.w;
        v.y = Matrix.m[1] * u.x + Matrix.m[5] * u.y + Matrix.m[9] * u.z + Matrix.m[13] * u.w;
        v.z = Matrix.m[2] * u.x + Matrix.m[6] * u.y + Matrix.m[10] * u.z + Matrix.m[14] * u.w;
        v.w = Matrix.m[3] * u.x + Matrix.m[7] * u.y + Matrix.m[11] * u.z + Matrix.m[15] * u.w;

        return v;
    }

    mat4x4 BiasMatrix = mat4x4(0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f);
    mat4x4 BiasMatrixInverse = mat4x4(2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, -1.0f, -1.0f, -1.0f, 1.0f);

    float det3x3sub(const float *m, int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8)
    {
        float det = 0.0f;

        det += m[i0] * det2x2sub(m, i4, i5, i7, i8);
        det -= m[i3] * det2x2sub(m, i1, i2, i7, i8);
        det += m[i6] * det2x2sub(m, i1, i2, i4, i5);

        return det;
    }

    mat4x4 inverse(const mat4x4 &Matrix)
    {
        const float *m = Matrix.m;

        float det = 0.0f;

        det += m[0] * det3x3sub(m, 5, 6, 7, 9, 10, 11, 13, 14, 15);
        det -= m[4] * det3x3sub(m, 1, 2, 3, 9, 10, 11, 13, 14, 15);
        det += m[8] * det3x3sub(m, 1, 2, 3, 5, 6, 7, 13, 14, 15);
        det -= m[12] * det3x3sub(m, 1, 2, 3, 5, 6, 7, 9, 10, 11);

        mat4x4 Inverse;

        Inverse.m[0] = det3x3sub(m, 5, 6, 7, 9, 10, 11, 13, 14, 15) / det;
        Inverse.m[1] = -det3x3sub(m, 1, 2, 3, 9, 10, 11, 13, 14, 15) / det;
        Inverse.m[2] = det3x3sub(m, 1, 2, 3, 5, 6, 7, 13, 14, 15) / det;
        Inverse.m[3] = -det3x3sub(m, 1, 2, 3, 5, 6, 7, 9, 10, 11) / det;
        Inverse.m[4] = -det3x3sub(m, 4, 6, 7, 8, 10, 11, 12, 14, 15) / det;
        Inverse.m[5] = det3x3sub(m, 0, 2, 3, 8, 10, 11, 12, 14, 15) / det;
        Inverse.m[6] = -det3x3sub(m, 0, 2, 3, 4, 6, 7, 12, 14, 15) / det;
        Inverse.m[7] = det3x3sub(m, 0, 2, 3, 4, 6, 7, 8, 10, 11) / det;
        Inverse.m[8] = det3x3sub(m, 4, 5, 7, 8, 9, 11, 12, 13, 15) / det;
        Inverse.m[9] = -det3x3sub(m, 0, 1, 3, 8, 9, 11, 12, 13, 15) / det;
        Inverse.m[10] = det3x3sub(m, 0, 1, 3, 4, 5, 7, 12, 13, 15) / det;
        Inverse.m[11] = -det3x3sub(m, 0, 1, 3, 4, 5, 7, 8, 9, 11) / det;
        Inverse.m[12] = -det3x3sub(m, 4, 5, 6, 8, 9, 10, 12, 13, 14) / det;
        Inverse.m[13] = det3x3sub(m, 0, 1, 2, 8, 9, 10, 12, 13, 14) / det;
        Inverse.m[14] = -det3x3sub(m, 0, 1, 2, 4, 5, 6, 12, 13, 14) / det;
        Inverse.m[15] = det3x3sub(m, 0, 1, 2, 4, 5, 6, 8, 9, 10) / det;

        return Inverse;
    }

    mat4x4 look(const vec3 &eye, const vec3 &center, const vec3 &up)
    {
        vec3 Z = normalize(eye - center);
        vec3 X = normalize(cross(up, Z));
        vec3 Y = cross(Z, X);

        mat4x4 View;

        View.m[0] = X.x;
        View.m[1] = Y.x;
        View.m[2] = Z.x;
        View.m[3] = 0.0f;

        View.m[4] = X.y;
        View.m[5] = Y.y;
        View.m[6] = Z.y;
        View.m[7] = 0.0f;

        View.m[8] = X.z;
        View.m[9] = Y.z;
        View.m[10] = Z.z;
        View.m[11] = 0.0f;

        View.m[12] = -dot(X, eye);
        View.m[13] = -dot(Y, eye);
        View.m[14] = -dot(Z, eye);
        View.m[15] = 1.0f;

        return View;
    }

    mat4x4 ortho(float left, float right, float bottom, float top, float n, float f)
    {
        mat4x4 Ortho;

        Ortho.m[0] = 2.0f / (right - left);
        Ortho.m[1] = 0.0f;
        Ortho.m[2] = 0.0f;
        Ortho.m[3] = 0.0f;

        Ortho.m[4] = 0.0f;
        Ortho.m[5] = 2.0f / (top - bottom);
        Ortho.m[6] = 0.0f;
        Ortho.m[7] = 0.0f;

        Ortho.m[8] = 0.0f;
        Ortho.m[9] = 0.0f;
        Ortho.m[10] = -2.0f / (f - n);
        Ortho.m[11] = 0.0f;

        Ortho.m[12] = -(right + left) / (right - left);
        Ortho.m[13] = -(top + bottom) / (top - bottom);
        Ortho.m[14] = -(f + n) / (f - n);
        Ortho.m[15] = 1.0f;

        return Ortho;
    }

    mat4x4 perspective(float fovy, float aspect, float n, float f)
    {
        mat4x4 Perspective;

        float coty = 1.0f / tan(fovy * (float)M_PI / 360.0f);

        Perspective.m[0] = coty / aspect;
        Perspective.m[1] = 0.0f;
        Perspective.m[2] = 0.0f;
        Perspective.m[3] = 0.0f;

        Perspective.m[4] = 0.0f;
        Perspective.m[5] = coty;
        Perspective.m[6] = 0.0f;
        Perspective.m[7] = 0.0f;

        Perspective.m[8] = 0.0f;
        Perspective.m[9] = 0.0f;
        Perspective.m[10] = (n + f) / (n - f);
        Perspective.m[11] = -1.0f;

        Perspective.m[12] = 0.0f;
        Perspective.m[13] = 0.0f;
        Perspective.m[14] = 2.0f * n * f / (n - f);
        Perspective.m[15] = 0.0f;

        return Perspective;
    }

    mat4x4 rotate(float angle, const vec3 &u)
    {
        mat4x4 Rotate;

        angle = angle / 180.0f * (float)M_PI;

        vec3 v = normalize(u);

        float c = 1.0f - cos(angle), s = sin(angle);

        Rotate.m[0] = 1.0f + c * (v.x * v.x - 1.0f);
        Rotate.m[1] = c * v.x * v.y + v.z * s;
        Rotate.m[2] = c * v.x * v.z - v.y * s;
        Rotate.m[3] = 0.0f;

        Rotate.m[4] = c * v.x * v.y - v.z * s;
        Rotate.m[5] = 1.0f + c * (v.y * v.y - 1.0f);
        Rotate.m[6] = c * v.y * v.z + v.x * s;
        Rotate.m[7] = 0.0f;

        Rotate.m[8] = c * v.x * v.z + v.y * s;
        Rotate.m[9] = c * v.y * v.z - v.x * s;
        Rotate.m[10] = 1.0f + c * (v.z * v.z - 1.0f);
        Rotate.m[11] = 0.0f;

        Rotate.m[12] = 0.0f;
        Rotate.m[13] = 0.0f;
        Rotate.m[14] = 0.0f;
        Rotate.m[15] = 1.0f;

        return Rotate;
    }

    mat4x4 scale(float x, float y, float z)
    {
        mat4x4 Scale;

        Scale.m[0] = x;
        Scale.m[1] = 0.0f;
        Scale.m[2] = 0.0f;
        Scale.m[3] = 0.0f;

        Scale.m[4] = 0.0f;
        Scale.m[5] = y;
        Scale.m[6] = 0.0f;
        Scale.m[7] = 0.0f;

        Scale.m[8] = 0.0f;
        Scale.m[9] = 0.0f;
        Scale.m[10] = z;
        Scale.m[11] = 0.0f;

        Scale.m[12] = 0.0f;
        Scale.m[13] = 0.0f;
        Scale.m[14] = 0.0f;
        Scale.m[15] = 1.0f;

        return Scale;
    }

    mat4x4 translate(float x, float y, float z)
    {
        mat4x4 Translate;

        Translate.m[0] = 1.0f;
        Translate.m[1] = 0.0f;
        Translate.m[2] = 0.0f;
        Translate.m[3] = 0.0f;

        Translate.m[4] = 0.0f;
        Translate.m[5] = 1.0f;
        Translate.m[6] = 0.0f;
        Translate.m[7] = 0.0f;

        Translate.m[8] = 0.0f;
        Translate.m[9] = 0.0f;
        Translate.m[10] = 1.0f;
        Translate.m[11] = 0.0f;

        Translate.m[12] = x;
        Translate.m[13] = y;
        Translate.m[14] = z;
        Translate.m[15] = 1.0f;

        return Translate;
    }

    mat4x4 transpose(const mat4x4 &Matrix)
    {
        mat4x4 Transpose;

        Transpose.m[0] = Matrix.m[0];
        Transpose.m[1] = Matrix.m[4];
        Transpose.m[2] = Matrix.m[8];
        Transpose.m[3] = Matrix.m[12];

        Transpose.m[4] = Matrix.m[1];
        Transpose.m[5] = Matrix.m[5];
        Transpose.m[6] = Matrix.m[9];
        Transpose.m[7] = Matrix.m[13];

        Transpose.m[8] = Matrix.m[2];
        Transpose.m[9] = Matrix.m[6];
        Transpose.m[10] = Matrix.m[10];
        Transpose.m[11] = Matrix.m[14];

        Transpose.m[12] = Matrix.m[3];
        Transpose.m[13] = Matrix.m[7];
        Transpose.m[14] = Matrix.m[11];
        Transpose.m[15] = Matrix.m[15];

        return Transpose;
    }

    void GetXY(const vec3 &Z, vec3 &X, vec3 &Y)
    {
        if (Z.y == -1.0f)
        {
            X = vec3(1.0f, 0.0f, 0.0f);
            Y = vec3(0.0f, 0.0f, 1.0f);
        }
        else if (Z.y > -1.0f && Z.y < 0.0f)
        {
            X = cross(vec3(0.0f, 1.0f, 0.0f), Z);
            Y = cross(Z, X);
        }
        else if (Z.y == 0.0f)
        {
            Y = vec3(0.0f, 1.0f, 0.0f);
            X = cross(Y, Z);
        }
        else if (Z.y > 0.0f && Z.y < 1.0f)
        {
            X = cross(vec3(0.0f, 1.0f, 0.0f), Z);
            Y = cross(Z, X);
        }
        else if (Z.y == 1.0f)
        {
            X = vec3(1.0f, 0.0f, 0.0f);
            Y = vec3(0.0f, 0.0f, -1.0f);
        }
    }

    mat3x3 GetTBNMatrix(const vec3 &N)
    {
        vec3 T, B;

        GetXY(N, T, B);

        return inverse(mat3x3(T, B, N));
    }
}