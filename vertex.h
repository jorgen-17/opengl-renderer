#ifndef VERTEX_H
#define VERTEX_H

#include "ogldev_math_3d.h"

struct Vertex
{
    Vector3f m_pos;
    Vector2f m_tex;
    Vector3f m_normal;

    Vertex() {}

    Vertex(const Vector3f& pos, const Vector2f& tex, const Vector3f& normal)
    {
        m_pos    = pos;
        m_tex    = tex;
        m_normal = normal;
    }

    Vertex(const Vector3f& pos, const Vector2f& tex)
    {
        m_pos    = pos;
        m_tex    = tex;
        m_normal = Vector3f(0.0f, 0.0f, 0.0f);
    }
};

#endif  /* VERTEX_H */
