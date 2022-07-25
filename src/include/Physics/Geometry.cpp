#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include "Geometry.hpp"

template <typename T, char iterations>

T Geometry::inv_sqrt(T x)
{
	static_assert(std::is_floating_point_v<T>, "T must be floating Point");
	static_assert(
		iterations >= 1 && iterations <= 5,
		"itarations must lie between [1 , 5] and must be integer values");
	typedef
		typename std::conditional_t<sizeof(T) == 8, std::int64_t, std::int32_t>
			Tint;
	T y = x;
	T x2 = y * 0.5;
	Tint i = *(Tint *)&y;
	i = (sizeof(T) == 8 ? 0x5fe6eb50c7b537a9 : 0x5f3759df) - (i >> 1);
	y = *(T *)&i;
	y = y * (1.5 - (x2 * y * y));
	if (iterations == 2) y = y * (1.5 - (x2 * y * y));
	if (iterations == 3) y = y * (1.5 - (x2 * y * y));
	if (iterations == 4) y = y * (1.5 - (x2 * y * y));
	if (iterations == 5) y = y * (1.5 - (x2 * y * y));
	return y;
}
template <typename T>
T Geometry::dot(Geometry::Point<T> a, Geometry::Point<T> b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
template <typename T>
float Geometry::ang(Geometry::Point<T> a, Geometry::Point<T> b, bool deg)
{
	return (acos(dot(a, b) * inv_sqrt(dot(a, a) * dot(b, b))) *
			(deg == true ? 180 / M_PI : 1));
}
template <typename T>
Geometry::Point<T> Geometry::cross(Geometry::Point<T> a, Geometry::Point<T> b)
{
	T x0 = a.x, y0 = a.y, z0 = a.z;
	T x1 = b.x, y1 = b.y, z1 = b.z;
	// adding 0.00 to avoid -0 output
	return Geometry::Point<T>(y0 * z1 - z0 * y1 + 0.00,
							  z0 * x1 - x0 * z1 + 0.00,
							  x0 * y1 - y0 * x1 + 0.00);
}
template <typename T>

int Geometry::intersection(Geometry::Point<T> p0, Geometry::Point<T> p1,
						   Geometry::Point<T> p2, Geometry::Point<T> p3,
						   Geometry::Point<T> &intx)
{
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
	double p0_x = p0.x, p0_y = p0.y;
	double p1_x = p1.x, p1_y = p1.y;
	double p2_x = p2.x, p2_y = p2.y;
	double p3_x = p3.x, p3_y = p3.y;
	double s1_x, s1_y, s2_x, s2_y;
	s1_x = p1_x - p0_x;
	s1_y = p1_y - p0_y;
	s2_x = p3_x - p2_x;
	s2_y = p3_y - p2_y;

	double s, t;
	double den = (-s2_x * s1_y + s1_x * s2_y);

	if (den == 0 || abs(den) <= epsilon)
	{

		// parallel or collinear lines
		// if they are collinear then their slope will be the same for any two
		// pair of Points
		if (p0.slope2D(p1) == p1.slope2D(p2) &&
			p2.slope2D(p3) == p3.slope2D(p0) &&
			p1.slope2D(p0) == p0.slope2D(p3))
			return 2;
		return 3;
	}
	s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / den;
	t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / den;

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		// Collision detected
		intx.x = p0_x + (t * s1_x);
		intx.y = p0_y + (t * s1_y);

		return 1;
	}
	return 0; // No collision
}
template <typename T>

int Geometry::ray_intersection(Geometry::Point<T> p0, Geometry::Point<T> p1,
							   Geometry::Point<T> p2, Geometry::Point<T> p3,
							   Geometry::Point<T> &intx)
{
	/**
	 *  @brief Return the intersection of a ray and a line segment .
	 *  @param  p0  Origin of the ray.
	 *  @param  p1  Direction of the ray.
	 *  @param  p2  Start of line segment.
	 *  @param  p3  End of line segment.
	 *  @param  intx  the intersection Point.
	 *  @return  Returns 1 if the lines intersect,2 if lines are collinear,3 if
	 * lines are parallel,otherwise 0 It is based on an algorithm in Andre
	 * LeMothe's "Tricks of the Windows Game Programming Gurus" the refrence
	 * Point will store null intx stores the intersection Point if it exists
	 * else will be intialized to null
	 */
	double p0_x = p0.x, p0_y = p0.y;
	double p1_x = p1.x, p1_y = p1.y;
	double p2_x = p2.x, p2_y = p2.y;
	double p3_x = p3.x, p3_y = p3.y;
	double s1_x, s1_y, s2_x, s2_y;
	s1_x = p1_x - p0_x;
	s1_y = p1_y - p0_y;
	s2_x = p3_x - p2_x;
	s2_y = p3_y - p2_y;

	double s, t;
	double den = (-s2_x * s1_y + s1_x * s2_y);

	if (den == 0 || abs(den) <= epsilon)
	{

		// parallel or collinear lines
		// if they are collinear then their slope will be the same for any two
		// pair of Points
		if (p0.slope2D(p1) == p1.slope2D(p2) &&
			p2.slope2D(p3) == p3.slope2D(p0) &&
			p1.slope2D(p0) == p0.slope2D(p3))
			return 2;
		return 3;
	}
	s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / den;
	t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / den;

	if (s >= 0 && s <= 1 && t >= 0)
	{
		// Collision detected
		intx.x = p0_x + (t * s1_x);
		intx.y = p0_y + (t * s1_y);

		return 1;
	}
	return 0; // No collision
}

template <typename T>
double Geometry::signed_area_of_parallelogram(Geometry::Point<T> a,
											  Geometry::Point<T> b,
											  Geometry::Point<T> c)
{
	return (cross(b - a, c - b).z);
}
template <typename T>
double Geometry::area_of_triangle(Geometry::Point<T> a, Geometry::Point<T> b,
								  Geometry::Point<T> c)
{
	return abs(Geometry::signed_area_of_parallelogram(a, b, c) * 0.5);
}
template <typename T>
int Geometry::direction(Geometry::Point<T> a, Geometry::Point<T> b,
						Geometry::Point<T> c)
{
	long long t = Geometry::signed_area_of_parallelogram(a, b, c);
	return (sign(t));
}
template <typename T>
double area_of_polygon(Geometry::Point<T> a[], int n)
{
	double area = 0;
	for (int i = 0; i < n; i++)
	{
		area -= (a[(i + 1) % n].x - a[i].x) * (a[(i + 1) % n].y + a[i].y);
		// i= n-1, a(0)->a(n-1)
	}
	area /= 2;
	return abs(area);
}
template <typename T>
double Geometry::area_of_polygon(vector<Geometry::Point<T>> a, int n)
{
	assert(!a.empty(), "array cannot be empty");
	static_assert(n >= 0 && n <= a.size(),
				  "size must be less than the array size ");
	if (n == 0) n = a.size();
	double area = 0;
	for (int i = 0; i < n; i++)
	{
		area -=
			(a.at((i + 1) % n).x - a.at(i).x) * (a.at((i + 1) % n).y + a[i].y);
		// i= n-1, a(0)->a(n-1)
	}
	area /= 2;
	return abs(area);
}
template <typename T>
// counterclockwise direction of Points and must be convex polygon
bool Geometry::check_Point_in_polygon(Geometry::Point<T> a[], int n,
									  Geometry::Point<T> p)
{
	// query time O(log n)
	int l = 1, r = n - 2;
	while (l < r)
	{
		int x = (l + r) / 2;
		if (direction(a[0], a[x + 1], p) == 1) // counterclockwise turn
			l = x + 1;
		else if (direction(a[0], a[x], a[p]) == -1) r = x - 1;
		else
		{
			// the Point lies between the vectors l and r
			l = r = x;
		}
	}
	if (area_of_triangle(a[0], a[l], a[+1]) ==
			area_of_triangle(a[0], a[l], p) +
				area_of_triangle(a[l], a[l + 1], p) +
				area_of_triangle(a[l + 1]),
		a[0], a[p])
		return true;
	return false;
}
template <typename T>
std::vector<Geometry::Point<T>> minkowski_sum(std::vector<Geometry::Point<T>> a,
											  std::vector<Geometry::Point<T>> b,
											  bool remove_redundant)
{
	int l = 0;
	int n = a.size();
	int m = b.size();
	for (int i = 0; i < n; i++)
	{
		if (a[i].x < a[l].x || (a[i].x == a[l].x && a[i].y < a[l].y)) l = i;
	}
	int r = 0;
	for (int i = 0; i < n; i++)
	{
		if (b[i].x < b[l].x || (b[i].x == b[l].x && b[i].y < b[l].y)) r = i;
	}
	std::vector<Geometry::Point<T>> v;
	for (int i = 0; i < m + n; i++)
	{
		v.push_back(a[l] + b[r]);
		if (cross(a[(l + 1) % n] - a[l], b[(r + 1) % m] - b[r]).z > 0)
			l = (l + 1) % n;
		else r = (r + 1) % m;
	}
	if (!remove_redundant) return v;
	std::unordered_set<int> mark;

	for (int i = 0; i < n + m; i++)
	{
		if (direction(v[i], v[(i + 1) % (n + m)], v[(i + 2) % (n + m)]) == 0)
		{
			// redundant Point
			mark.insert((i + 1) % (n + m));
		}
	}

	std::vector<Geometry::Point<T>> vv;

	for (int i = 0; i < n + m; i++)
	{
		if (!mark.contains(i))
		{
			vv.push_back(v[i]);
		}
	}
	return vv;
}
template <typename T>
// remove the redundant Points present in a polygon represented by a
// vector<Geometry::Point<T>>

// give n as -1 if you do not wish to give the size of the vector
std::vector<Geometry::Point<T>>
remove_redundant(std::vector<Geometry::Point<T>> v, int n)
{
	static_assert(!v.empty(), "array cannot be empty");
	static_assert(
		n >= 0 && n <= v.size(),
		"n must be greater than 0 and less than the size of the array");
	std::unordered_set<int> mark;
	if (n == 0) n = v.size();

	for (int i = 0; i < n; i++)
	{
		if (direction(v[i], v[(i + 1) % n], v[(i + 2) % n]) == 0)
		{
			// redundant Point
			mark.insert((i + 1) % n);
		}
	}

	std::vector<Geometry::Point<T>> vv;

	for (int i = 0; i < n; i++)
	{
		if (!mark.contains(i))
		{
			vv.push_back(v[i]);
		}
	}
	return vv;
}
template Geometry::Point<double> Geometry::cross(Geometry::Point<double> a,
												 Geometry::Point<double> b);
template double Geometry::dot(Geometry::Point<double> a,
							  Geometry::Point<double> b);
template int Geometry::ray_intersection(Geometry::Point<double> p0,
										Geometry::Point<double> p1,
										Geometry::Point<double> p2,
										Geometry::Point<double> p3,
										Geometry::Point<double> &intx);
