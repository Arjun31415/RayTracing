#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>
#include <vector>
#include <set>
#include <unordered_set>
#include <queue>
#include <ostream>

namespace Geometry
{
    using namespace std;
#define ss second
#define ff first
#define pb push_back
#define mp make_pair
#define all(A) A.begin(), A.end()
#define trace(x) cerr << #x << ": " << x << " " << endl;
#define sign(x) (x > 0) - (x < 0)
#define epsilon 1e-9
    template <typename T>
    class Point
    {
    public:
        T x, y, z;

        Point() { x = y = z = 0; }
        Point(T x, T y, T z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        Point(T x, T y)
        {
            this->x = x;
            this->y = y;
            this->z = 0;
        }
        void setx(T x) { this->x = x; }
        void sety(T y) { this->y = y; }
        void setz(T z) { this->z = z; }
        void set(T x = 0, T y = 0, T z = 0)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        Point operator*(T value) { return Point(x * value, y * value, z * value); }
        Point operator/(T value) { return Point(x / value, y / value, z / value); }
        Point operator+(const Point<T> &b)
        {
            return Point(this->x + b.x, this->y + b.y, this->z + b.z);
        }
        Point operator-(const Point<T> &b)
        {
            return Point(this->x - b.x, this->y - b.y, this->z - b.z);
        }
        T distance(const Point<T> &p)
        {
            return sqrt((this->x - p.x) * (this->x - p.x) +
                        (this->y - p.y) * (this->y - p.y) +
                        (this->z - p.z) * (this->z - p.z));
        }
        T slope2D() { return (this->y) / (this->x); }
        T slope2D(const Point<T> &other)
        {
            return (this->y - other.y) / (this->x - other.x);
        }
        T angle2D() { return arctan(this->slope2D()); }
        void operator=(const Point<T> b)
        {
            this->x = b.x;
            this->y = b.y;
            this->z = b.z;
        }
        Point &operator+=(const Point<T> b) { return (*this = *this + b); }
        Point &operator-=(const Point<T> &b)
        {
            *this = *this - b;
            return *this;
        }
        Point &operator*=(T val)
        {
            *this = (*this) * val;
            return *this;
        }
        Point &operator/=(T val)
        {
            *this = (*this) / val;
            return *this;
        }
        bool operator==(const Point<T> &other)
        {
            if (std::is_floating_point<T>::value)
                return (abs(this->x - other.x) <= epsilon &&
                        abs(this->y - other.y) <= epsilon &&
                        abs(this->z - other.z) <= epsilon);
            return ((this->x == other.x) && (this->y == other.y) &&
                    (this->z == other.z));
        }
        bool operator!=(const Point<T> &other) { return (!(*this == other)); }
        T modulus() { return abs(sqrt(x * x + y * y + z * z)); }
        bool operator<(const Point<T> &b)
        {
            if (this->x == b.x)
                return this->y < b.y;
            else
                return this->x < b.x;
        }
        template <typename tt>
        friend std::ostream &operator<<(std::ostream &os, const Point<tt> &);
    };
    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Point<T> &a)
    {
        os << "( " << a.x << ", " << a.y << ", " << a.z << " )";
        return os;
    }
    /**
     * @brief calculates the inverse square root of a number,
     * using fast inverse square root algorithm found in Quake III
     *
     * @tparam T type of number
     * @tparam iterations  and integer denoting the
     *  number of iterations
     *  to run the algorithm
     * must lie in [1,5]
     * @param x the number
     * @return T inverse square root
     */

    template <typename T, char iterations = 3>
    T inv_sqrt(T x);
    /**
     * @brief does what you think
     *
     * @param val angle in radians
     * @return double angle in degrees
     */
    inline double rad_to_deg(double val);
    /**
     * @brief does what you think
     *
     * @param val angle in degrees
     * @return double angle in radians
     */
    inline double deg_to_rad(double val);
    /**
     * @brief returns the dot product of two vectors
     *
     * @tparam T type
     * @param a first vector
     * @param b second vector
     * @return T dot product
     */
    template <typename T>
    T dot(Point<T> a, Point<T> b);
    /**
     * @brief find the angle between two vectors
     *
     * @tparam T
     * @param a first vector
     * @param b second vector
     * @param deg if 1 then output in degrees else in radians
     * @return float angle between the vectors
     */
    template <typename T>
    float ang(Point<T> a, Point<T> b, bool deg = true);
    /**
     * @brief find the cross product between two vectors
     *
     * @tparam T
     * @param a first vector
     * @param b second vector
     * @return Point<T> a x b
     */
    template <typename T>
    extern Point<T> cross(Point<T> a, Point<T> b);
    /**
     *  @brief Return the intersection of two line segments .
     *  @param  p0  Start of first line segment.
     *  @param  p1   End of first line segment.
     *  @param  p2  Start of second line segment.
     *  @param  p3   End of second line segment.
     *  @param  intx  the intersection Point.
     *  @return  Returns 1 if the lines intersect,2 if lines are collinear,3 if
     * lines are parallel,otherwise 0 It is based on an algorithm in Andre
     * LeMothe's "Tricks of the Windows Game Programming Gurus" the refrence
     * Point will store null intx stores the intersection Point if it exists
     * else will be intialized to null
     */
    template <typename T>
    int intersection(Point<T> p0, Point<T> p1, Point<T> p2, Point<T> p3,
                     Point<T> &intx);
    /**
     * @brief does what you think
     * (b-a) x (c-b)
     *
     * @tparam T
     * @param a first vertex
     * @param b second vertex
     * @param c third vertex
     * @return double
     */
    template <typename T>
    double signed_area_of_parallelogram(Point<T> a, Point<T> b, Point<T> c);
    /**
     * @brief does what you think
     * the vectors will be a to b, b to c
     * 0.5*[(b-a)x(c-b)]
     * @tparam T
     * @param a first vertex
     * @param b second vertex
     * @param c third vertex
     * @return double
     */
    template <typename T>
    double area_of_triangle(Point<T> a, Point<T> b, Point<T> c);
    /**
     * @brief gives the direction of c with respect to line ab.
     *  returns the sign of (b-a)x(c-b)
     * @tparam T
     * @param a first point
     * @param b second point
     * @param c third point
     * @return int the direction sign 1 if positive -1 if negative
     */
    template <typename T>
    int direction(Point<T> a, Point<T> b, Point<T> c);
    /**
     * @brief finds the area of polygon formed by the given points
     *
     * @tparam T
     * @param a array of points which form the vertices of the polygon
     * @param n length of the array
     * @return double
     */
    template <typename T>
    double area_of_polygon(Point<T> a[], int n);
    /**
     * @brief find the area of polygon formed by the given points
     *
     * @tparam T
     * @param a array of points which form the vertices of the polygon
     * @param n number of points to consider. must be less than a.size().
     * If 0 then the entire array is considered
     * @return double area of the polygon
     */
    template <typename T>
    double area_of_polygon(vector<Point<T>> a, int n = 0);
    /**
     * @brief  counterclockwise direction of Points and must be convex polygon
     *
     * @tparam T
     * @param a array of points which form the vertices of the convex polygon
     * @param n size of array
     * @param p the point which has to be checked
     * @return true
     * @return false
     */
    template <typename T>
    bool check_Point_in_polygon(Point<T> a[], int n, Point<T> p);
    /**
     * @brief find the minkowsi sum of the given two polygons
     *
     * @tparam T
     * @param a array of points denoting the vertices of the first polygon
     * @param b array of points denoting the verices of the second polygon
     * @param remove_redundant if true then redundant vertices are removed from the resultant polygon
     * @return vector<Point<T>>
     */
    template <typename T>
    vector<Point<T>> minkowski_sum(vector<Point<T>> a, vector<Point<T>> b,
                                   bool remove_redundant = true);

    /**
     * @brief remove the redundant Points present in a polygon
     *
     * @tparam T
     * @param v polygon represented by an array of vertices
     * @param n number of points to consider in the array
     * give n as 0 if you do not wish to give the size of the vector
     * @return vector<Point<T>>
     */
    template <typename T>
    vector<Point<T>> remove_redundant(vector<Point<T>> v, int n);

} // namespace Geometry
