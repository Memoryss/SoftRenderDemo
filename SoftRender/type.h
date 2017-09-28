#ifndef __TYPE_H__
#define __TYPE_H__

#include <cmath>
#include <string>

namespace SoftRenderer {

    //TODO 最好使用模版
    struct vec2i
    {
        union
        {
            struct { int x, y; };
            struct { int u, v; };
        };

        vec2i() {}
        ~vec2i() {}
        vec2i(int num) : x(num), y(num) {}
        vec2i(int x, int y) : x(x), y(y) {}
        vec2i(const vec2i &u) : x(u.x), y(u.y) {}
        vec2i& operator = (const vec2i &u) { x = u.x; y = u.y; return *this; }
        vec2i operator - () { return vec2i(-x, -y); }
        float* operator & () { return (float*)this; };
        vec2i& operator += (float num) { x += num; y += num; return *this; }
        vec2i& operator += (const vec2i &u) { x += u.x; y += u.y; return *this; }
        vec2i& operator -= (float num) { x -= num; y -= num; return *this; }
        vec2i& operator -= (const vec2i &u) { x -= u.x; y -= u.y; return *this; }
        vec2i& operator *= (float num) { x *= num; y *= num; return *this; }
        vec2i& operator *= (const vec2i &u) { x *= u.x; y *= u.y; return *this; }
        vec2i& operator /= (float num) { x /= num; y /= num; return *this; }
        vec2i& operator /= (const vec2i &u) { x /= u.x; y /= u.y; return *this; }
        friend vec2i operator + (const vec2i &u, int num) { return vec2i(u.x + num, u.y + num); }
        friend vec2i operator + (int num, const vec2i &u) { return vec2i(num + u.x, num + u.y); }
        friend vec2i operator + (const vec2i &u, const vec2i &v) { return vec2i(u.x + v.x, u.y + v.y); }
        friend vec2i operator - (const vec2i &u, int num) { return vec2i(u.x - num, u.y - num); }
        friend vec2i operator - (int num, const vec2i &u) { return vec2i(num - u.x, num - u.y); }
        friend vec2i operator - (const vec2i &u, const vec2i &v) { return vec2i(u.x - v.x, u.y - v.y); }
        friend vec2i operator * (const vec2i &u, int num) { return vec2i(u.x * num, u.y * num); }
        friend vec2i operator * (int num, const vec2i &u) { return vec2i(num * u.x, num * u.y); }
        friend vec2i operator * (const vec2i &u, const vec2i &v) { return vec2i(u.x * v.x, u.y * v.y); }
        friend vec2i operator / (const vec2i &u, int num) { return vec2i(u.x / num, u.y / num); }
        friend vec2i operator / (int num, const vec2i &u) { return vec2i(num / u.x, num / u.y); }
        friend vec2i operator / (const vec2i &u, const vec2i &v) { return vec2i(u.x / v.x, u.y / v.y); }
    };

    struct vec2
    {
        union
        {
            struct { float x, y; };
            struct { float s, t; };
            struct { float r, g; };
        };

        vec2() {}
        ~vec2() {}
        vec2(float num) : x(num), y(num) {}
        vec2(float x, float y) : x(x), y(y) {}
        vec2(const vec2 &u) : x(u.x), y(u.y) {}
        vec2& operator = (const vec2 &u) { x = u.x; y = u.y; return *this; }
        vec2 operator - () { return vec2(-x, -y); }
        float* operator & () { return (float*)this; };
        vec2& operator += (float num) { x += num; y += num; return *this; }
        vec2& operator += (const vec2 &u) { x += u.x; y += u.y; return *this; }
        vec2& operator -= (float num) { x -= num; y -= num; return *this; }
        vec2& operator -= (const vec2 &u) { x -= u.x; y -= u.y; return *this; }
        vec2& operator *= (float num) { x *= num; y *= num; return *this; }
        vec2& operator *= (const vec2 &u) { x *= u.x; y *= u.y; return *this; }
        vec2& operator /= (float num) { x /= num; y /= num; return *this; }
        vec2& operator /= (const vec2 &u) { x /= u.x; y /= u.y; return *this; }
        friend vec2 operator + (const vec2 &u, float num) { return vec2(u.x + num, u.y + num); }
        friend vec2 operator + (float num, const vec2 &u) { return vec2(num + u.x, num + u.y); }
        friend vec2 operator + (const vec2 &u, const vec2 &v) { return vec2(u.x + v.x, u.y + v.y); }
        friend vec2 operator - (const vec2 &u, float num) { return vec2(u.x - num, u.y - num); }
        friend vec2 operator - (float num, const vec2 &u) { return vec2(num - u.x, num - u.y); }
        friend vec2 operator - (const vec2 &u, const vec2 &v) { return vec2(u.x - v.x, u.y - v.y); }
        friend vec2 operator * (const vec2 &u, float num) { return vec2(u.x * num, u.y * num); }
        friend vec2 operator * (float num, const vec2 &u) { return vec2(num * u.x, num * u.y); }
        friend vec2 operator * (const vec2 &u, const vec2 &v) { return vec2(u.x * v.x, u.y * v.y); }
        friend vec2 operator / (const vec2 &u, float num) { return vec2(u.x / num, u.y / num); }
        friend vec2 operator / (float num, const vec2 &u) { return vec2(num / u.x, num / u.y); }
        friend vec2 operator / (const vec2 &u, const vec2 &v) { return vec2(u.x / v.x, u.y / v.y); }
    };

    float dot(const vec2 &u, const vec2 &v);
    float length(const vec2 &u);
    float length2(const vec2 &u);
    vec2 mix(const vec2 &u, const vec2 &v, float a);
    vec2 normalize(const vec2 &u);
    vec2 reflect(const vec2 &i, const vec2 &n);
    vec2 refract(const vec2 &i, const vec2 &n, float eta);
    vec2 rotate(const vec2 &u, float angle);

    class vec3
    {
    public:
        union {
            struct { float x, y, z; };
            struct { float s, t, p; };
            struct { float r, g, b; };
        };
        vec3() {}
        ~vec3() {}
        vec3(float num) : x(num), y(num), z(num) {}
        vec3(float x, float y, float z) : x(x), y(y), z(z) {}
        vec3(const vec2 &u, float z) : x(u.x), y(u.y), z(z) {}
        vec3(const vec3 &u) : x(u.x), y(u.y), z(u.z) {}
        vec3& operator = (const vec3 &u) { x = u.x; y = u.y; z = u.z; return *this; }
        vec3 operator - () { return vec3(-x, -y, -z); }
        float* operator & () { return (float*)this; }
        vec3& operator += (float num) { x += num; y += num; z += num; return *this; }
        vec3& operator += (const vec3 &u) { x += u.x; y += u.y; z += u.z; return *this; }
        vec3& operator -= (float num) { x -= num; y -= num; z -= num; return *this; }
        vec3& operator -= (const vec3 &u) { x -= u.x; y -= u.y; z -= u.z; return *this; }
        vec3& operator *= (float num) { x *= num; y *= num; z *= num; return *this; }
        vec3& operator *= (const vec3 &u) { x *= u.x; y *= u.y; z *= u.z; return *this; }
        vec3& operator /= (float num) { x /= num; y /= num; z /= num; return *this; }
        vec3& operator /= (const vec3 &u) { x /= u.x; y /= u.y; z /= u.z; return *this; }
        bool operator == (const vec3 &u) const { return x == u.x && y == u.y && z == u.z; }
        bool operator == (float num) const { return x == num && y == num && z == num; }
        friend vec3 operator + (const vec3 &u, float num) { return vec3(u.x + num, u.y + num, u.z + num); }
        friend vec3 operator + (float num, const vec3 &u) { return vec3(num + u.x, num + u.y, num + u.z); }
        friend vec3 operator + (const vec3 &u, const vec3 &v) { return vec3(u.x + v.x, u.y + v.y, u.z + v.z); }
        friend vec3 operator - (const vec3 &u, float num) { return vec3(u.x - num, u.y - num, u.z - num); }
        friend vec3 operator - (float num, const vec3 &u) { return vec3(num - u.x, num - u.y, num - u.z); }
        friend vec3 operator - (const vec3 &u, const vec3 &v) { return vec3(u.x - v.x, u.y - v.y, u.z - v.z); }
        friend vec3 operator * (const vec3 &u, float num) { return vec3(u.x * num, u.y * num, u.z * num); }
        friend vec3 operator * (float num, const vec3 &u) { return vec3(num * u.x, num * u.y, num * u.z); }
        friend vec3 operator * (const vec3 &u, const vec3 &v) { return vec3(u.x * v.x, u.y * v.y, u.z * v.z); }
        friend vec3 operator / (const vec3 &u, float num) { return vec3(u.x / num, u.y / num, u.z / num); }
        friend vec3 operator / (float num, const vec3 &u) { return vec3(num / u.x, num / u.y, num / u.z); }
        friend vec3 operator / (const vec3 &u, const vec3 &v) { return vec3(u.x / v.x, u.y / v.y, u.z / v.z); }
    };

    vec3 cross(const vec3 &u, const vec3 &v);
    float dot(const vec3 &u, const vec3 &v);
    float length(const vec3 &u);
    float length2(const vec3 &u);
    vec3 mix(const vec3 &u, const vec3 &v, float a);
    vec3 normalize(const vec3 &u);
    vec3 reflect(const vec3 &i, const vec3 &n);
    vec3 refract(const vec3 &i, const vec3 &n, float eta);
    vec3 rotate(const vec3 &u, float angle, const vec3 &v);

    class vec4
    {
    public:
        union {
            struct { float x, y, z, w; };
            struct { float s, t, p, q; };
            struct { float r, g, b, a; };
        };
        vec4() {}
        ~vec4() {}
        vec4(float num) : x(num), y(num), z(num), w(num) {}
        vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
        vec4(const vec2 &u, float z, float w) : x(u.x), y(u.y), z(z), w(w) {}
        vec4(const vec3 &u, float w) : x(u.x), y(u.y), z(u.z), w(w) {}
        vec4(const vec4 &u) : x(u.x), y(u.y), z(u.z), w(u.w) {}
        vec4& operator = (const vec4 &u) { x = u.x; y = u.y; z = u.z; w = u.w; return *this; }
        vec4& operator = (const vec3 &u) { x = u.x; y = u.y; z = u.z; w = 1.f; return *this; }
        vec4 operator - () { return vec4(-x, -y, -z, -w); }
        float* operator & () { return (float*)this; }
        vec4& operator += (float num) { x += num; y += num; z += num; w += num; return *this; }
        vec4& operator += (const vec4 &u) { x += u.x; y += u.y; z += u.z; w += u.w; return *this; }
        vec4& operator -= (float num) { x -= num; y -= num; z -= num; w -= num; return *this; }
        vec4& operator -= (const vec4 &u) { x -= u.x; y -= u.y; z -= u.z; w -= u.w; return *this; }
        vec4& operator *= (float num) { x *= num; y *= num; z *= num; w *= num; return *this; }
        vec4& operator *= (const vec4 &u) { x *= u.x; y *= u.y; z *= u.z; w *= u.w; return *this; }
        vec4& operator /= (float num) { x /= num; y /= num; z /= num; w /= num; return *this; }
        vec4& operator /= (const vec4 &u) { x /= u.x; y /= u.y; z /= u.z; w /= u.w; return *this; }
        friend vec4 operator + (const vec4 &u, float num) { return vec4(u.x + num, u.y + num, u.z + num, u.w + num); }
        friend vec4 operator + (float num, const vec4 &u) { return vec4(num + u.x, num + u.y, num + u.z, num + u.w); }
        friend vec4 operator + (const vec4 &u, const vec4 &v) { return vec4(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w); }
        friend vec4 operator - (const vec4 &u, float num) { return vec4(u.x - num, u.y - num, u.z - num, u.w - num); }
        friend vec4 operator - (float num, const vec4 &u) { return vec4(num - u.x, num - u.y, num - u.z, num - u.w); }
        friend vec4 operator - (const vec4 &u, const vec4 &v) { return vec4(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w); }
        friend vec4 operator * (const vec4 &u, float num) { return vec4(u.x * num, u.y * num, u.z * num, u.w * num); }
        friend vec4 operator * (float num, const vec4 &u) { return vec4(num * u.x, num * u.y, num * u.z, num * u.w); }
        friend vec4 operator * (const vec4 &u, const vec4 &v) { return vec4(u.x * v.x, u.y * v.y, u.z * v.z, u.w * v.w); }
        friend vec4 operator / (const vec4 &u, float num) { return vec4(u.x / num, u.y / num, u.z / num, u.w / num); }
        friend vec4 operator / (float num, const vec4 &u) { return vec4(num / u.x, num / u.y, num / u.z, num / u.w); }
        friend vec4 operator / (const vec4 &u, const vec4 &v) { return vec4(u.x / v.x, u.y / v.y, u.z / v.z, u.w / v.w); }
    };

    class mat2x2;
    class mat3x3;
    class mat4x4;

    class mat2x2
    {
    public:
        float m[4];
        mat2x2();
        mat2x2(float num);
        ~mat2x2();
        mat2x2(const mat2x2 &Matrix);
        mat2x2(const vec2 &col1, const vec2 &col2);
        mat2x2(float c1r1, float c1r2, float c2r1, float c2r2);
        explicit mat2x2(const mat3x3 &Matrix);
        explicit mat2x2(const mat4x4 &Matrix);
        mat2x2& operator = (const mat2x2 &Matrix);
        float& operator [] (int i);
        float* operator & ();
        friend mat2x2 operator * (const mat2x2 &Matrix1, const mat2x2 &Matrix2);
        friend vec2 operator * (const mat2x2 &Matrix, const vec2 &u);
    };

    mat2x2 inverse(const mat2x2 &Matrix);
    mat2x2 transpose(const mat2x2 &Matrix);

    class mat3x3
    {
    public:
        float m[9];
        mat3x3();
        mat3x3(float num);
        ~mat3x3();
        mat3x3(const mat3x3 &Matrix);
        mat3x3(const vec3 &col1, const vec3 &col2, const vec3 &col3);
        mat3x3(float c1r1, float c1r2, float c1r3, float c2r1, float c2r2, float c2r3, float c3r1, float c3r2, float c3r3);
        explicit mat3x3(const mat2x2 &Matrix);
        explicit mat3x3(const mat4x4 &Matrix);
        mat3x3& operator = (const mat3x3 &Matrix);
        float& operator [] (int i);
        float* operator & ();
        friend mat3x3 operator * (const mat3x3 &Matrix1, const mat3x3 &Matrix2);
        friend vec3 operator * (const mat3x3 &Matrix, const vec3 &u);
    };

    mat3x3 inverse(const mat3x3 &Matrix);
    mat3x3 transpose(const mat3x3 &Matrix);

    class mat4x4
    {
    public:
        float m[16] = {0.f};
        mat4x4();
        mat4x4(float num);
        ~mat4x4();
        mat4x4(const mat4x4 &Matrix);
        mat4x4(float r1c1, float r1c2, float r1c3, float r1c4, float r2c1, float r2c2, float r2c3, float r2c4, float r3c1, float r3c2, float r3c3, float r3c4, float r4c1, float r4c2, float r4c3, float r4c4);
        explicit mat4x4(const mat2x2 &Matrix);
        explicit mat4x4(const mat3x3 &Matrix);
        mat4x4& operator = (const mat4x4 &Matrix);
        float& operator [] (int i);
        float* operator & ();
        friend mat4x4 operator * (const mat4x4 &Matrix1, const mat4x4 &Matrix2);
        friend vec4 operator * (const mat4x4 &Matrix, const vec4 &u);
        friend vec3 operator * (const mat4x4 &Matrix, const vec3 &u);
    };

    extern mat4x4 BiasMatrix;
    extern mat4x4 BiasMatrixInverse;

    mat4x4 inverse(const mat4x4 &Matrix);
    mat4x4 look(const vec3 &eye, const vec3 &center, const vec3 &up);
    mat4x4 ortho(float left, float right, float bottom, float top, float n, float f);
    mat4x4 perspective(float fovy, float aspect, float n, float f);
    mat4x4 rotate(float angle, const vec3 &u);
    mat4x4 scale(float x, float y, float z);
    mat4x4 translate(float x, float y, float z);
    mat4x4 transpose(const mat4x4 &Matrix);

    void GetXY(const vec3 &Z, vec3 &X, vec3 &Y);
    mat3x3 GetTBNMatrix(const vec3 &N);

    void StrToWstr(const std::string &src, std::wstring &dest);
    void WstrToStr(const std::wstring &src, std::string &dest);

#undef M_PI
    static const float M_PI = 3.14159265358979323846264338327950288f;
    static const float M_DEGTORAD = M_PI / 180.f;

    enum Intersection
    {
        OUTSIDE,
        INTERSECTS,
        INSIDE
    };

}

#endif
