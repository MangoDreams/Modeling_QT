#include "MatrixStack.h"

MatrixStack::MatrixStack(){
    Matrix4f m = Matrix4f::identity();
    m_matrices.push_back(m);

}

void MatrixStack::clear()
{
    m_matrices.clear();
    Matrix4f m = Matrix4f::identity();
    m_matrices.push_back(m);
}

Matrix4f MatrixStack::top()
{
    int idx = m_matrices.size()-1;
    return m_matrices[idx];
}

void MatrixStack::push(const Matrix4f& m )
{
    m_matrices.push_back(top()*m);
}

void MatrixStack::pop()
{
    m_matrices.pop_back();
}
