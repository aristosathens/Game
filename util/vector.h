// Aristos Athens

/*
 *  Custom implementation of vector for doing math.
 */

//
// Compiler guard
//

#ifndef VECTOR_H
#define VECTOR_H

//
// Include
//

// #include <initializer_list>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <vector>

//
// Expression classes
//

// Base class for any lazy-evaluated expression containg vectors.
template <typename E>
class VecExpression
{
    public:
    double operator[](size_t i) const { return static_cast<E const&>(*this)[i]; }
    size_t size()               const { return static_cast<E const&>(*this).size(); }
};

// Lazily evaluated summation. To force evaluation, iterate over a VecSum object using [] operator.
template <typename E1, typename E2>
class VecSum : public VecExpression<VecSum<E1, E2>>
{
    //
    // Public
    //
    public:
    VecSum(E1 const& in_v1, E2 const& in_v2) : vec1(in_v1), vec2(in_v2)
    {
        if (in_v1.size() != in_v2.size()) {
            throw std::runtime_error("Adding vectors of different size.");
        }
    }

    double operator[](size_t i) const { return vec1[i] + vec2[i]; }
    size_t size()               const { return vec1.size(); }

    //
    // Private
    //
    E1 const& vec1;
    E2 const& vec2;
};
  
template <typename E1, typename E2>
VecSum<E1,E2>
operator+(E1 const& u, E2 const& v)
{
   return VecSum<E1, E2>(u, v);
}

//
// Vector class
//

// Vector class. When constructed from VecExpressions it forces evulation.
class Vector : public VecExpression<Vector>
{
    //
    // Public
    //
    public:
    Vector(size_t size) : elements(size, 0) {}
    Vector(std::initializer_list<double> init)
    {
        for (auto i : init) {
            elements.push_back(i);
        }
    }

    // Vector can be constructed from VecExpression, which forces evaluation.
    template <typename E>
    Vector(VecExpression<E> const& vec) : elements(vec.size())
    {
        for (size_t i = 0; i != vec.size(); ++i) {
            elements[i] = vec[i];
        }
    }

    size_t size() const                       { return elements.size(); }
    const std::vector<double>& data() const   { return elements; }
    double operator[](size_t i) const         { return elements[i]; }
    double &operator[](size_t i)              { return elements[i]; }

    // Add new element.
    void append(double val)
    {
        elements.push_back(val);
    }

    // Remove and return last element.
    double pop()
    {
        double value = elements.back();
        elements.pop_back();
        return value;
    }

    // In-place zero all elements.
    void zero()
    {
        for (auto& elem : elements) {
            elem = 0.0;
        }
    }

    // In-place scale all elements by scalar.
    void scale(double c)
    {
        for (auto& elem : elements) {
            elem *= c;
        }
    }

    // Vector 2norm.
    float magnitude() const
    {
        float sum = 0;
        for (auto& elem : elements) {
            sum += pow(elem, 2);
        }
        return pow(sum, 0.5);
    }

    // In-place vector addition.
    template<typename E>
    Vector& operator+=(const VecExpression<E>& vec_exp)
    {
        for (size_t i = 0; i < size(); ++i) {
            elements[i] += vec_exp[i];
        }
        return *this;
    }

    // Dot product.
    template<typename E>
    double operator*(const VecExpression<E>& vec_exp)
    {
        double sum = 0;
        for (size_t i = 0; i < size(); ++i) {
            sum += elements[i] * vec_exp[i];
        }
        return sum;
    }

    //
    // Private
    //
    private:
    std::vector<double> elements;
};

std::ostream& operator<<(std::ostream& stream, const Vector& vec)
{
    stream << "[ ";
    for (auto& elem : vec.data()) {
        stream << elem << " ";
    }
    stream << "]";
    return stream;
}

//
// 3D Vector class
//

// Specialized wrapper for Vector class. Provides easy set and step methods for x, y, and z.
class Vector3D
{
    //
    // Public
    //
    public:
    Vector3D() : 
        elements(3)
        {}
    Vector3D(double in_x, double in_y, double in_z = 0) :
        elements({in_x, in_y, in_z})
        {}

    double operator[] (size_t i) const        { return elements[i]; }
    double &operator[](size_t i)              { return elements[i]; }

    void scale(double value) { elements.scale(value); }

    double x() const         { return elements[0]; }
    double y() const         { return elements[1]; }
    double z() const         { return elements[2]; }
    void set_x(double in_x)  { elements[0] = in_x; }
    void set_y(double in_y)  { elements[1] = in_y; }
    void set_z(double in_z)  { elements[2] = in_z; }
    void step_x(double step) { set_x(x() + step); }
    void step_y(double step) { set_y(y() + step); }
    void step_z(double step) { set_z(z() + step); }

    void set(double in_x, double in_y, double in_z)
    {
        set_x(in_x);
        set_y(in_y);
        set_z(in_z);
    }

    void step(double x_step, double y_step, double z_step)
    {
        step_x(x_step);
        step_y(y_step);
        step_z(z_step);
    }
    void step(const Vector3D& step_vec)
    {
        step_x(step_vec.x());
        step_y(step_vec.y());
        step_z(step_vec.z());
    }

    //
    // Private
    //
    private:
    Vector elements;
};

#endif // VECTOR_H
