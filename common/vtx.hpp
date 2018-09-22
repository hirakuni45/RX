#pragma once
//=====================================================================//
/*!	@file
	@brief	各種頂点の定義 @n
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/glfw_app/blob/master/LICENSE
*/
//=====================================================================//
#include <vector>
#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <cmath>
#include <cfloat>
#include <cstdint>

namespace vtx {

	template <typename T>
	T get_pi() { return static_cast<T>(3.1415926535897932384626433832795); }

	const float  deg2rad_f_ = get_pi<float>() / 180.0f;		///< DEG -> RAD の変換定数(float)
	const float  radian_f_  = 2.0f * get_pi<float>();		///< RADIAN のπ変換定数(float)
	const double deg2rad_d_ = get_pi<double>() / 180.0;		///< DEG -> RAD の変換定数(double)
	const double radian_d_  = 2.0 * get_pi<double>();		///< RADIAN のπ変換定数(double)

	inline void min_level(int8_t& min) { min = 1; }
	inline void min_level(int16_t& min) { min = 1; }
	inline void min_level(int32_t& min) { min = 1; }
	inline void min_level(float& min) { min = FLT_MIN; }
	inline void min_level(double& min) { min = DBL_MIN; }

	inline void max_level(int8_t& min) { min = 0x7f; }
	inline void max_level(int16_t& min) { min = 0x7fff; }
	inline void max_level(int32_t& min) { min = 0x7fffffff; }
	inline void max_level(float& max) { max = FLT_MAX; }
	inline void max_level(double& max) { max = DBL_MAX; }

	template <typename T>
	T min_value() {
		T min;
		min_level(min);
		return min;
	}

	template <typename T>
	T max_value() {
		T max;
		max_level(max);
		return max;
	}

	template <typename T> struct vertex2;
	template <typename T> struct vertex3;
	template <typename T> struct vertex4;

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	8 ビット整数、二次元、位置情報
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	typedef vertex2<int8_t>	bpos;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	16 ビット整数、二次元、位置情報
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	typedef vertex2<int16_t> spos;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	32 ビット整数、二次元、位置情報
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	typedef vertex2<int32_t> ipos;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	32 ビット浮動小数点、二次元、位置情報
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	typedef vertex2<float>	fpos;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	64 ビット倍精度浮動小数点、二次元、位置情報
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	typedef vertex2<double>	dpos;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	8 ビット整数、三次元、位置情報
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	typedef vertex3<int8_t> bvtx;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	16 ビット整数、三次元、位置情報
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	typedef vertex3<int16_t> svtx;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	32 ビット整数、三次元、位置情報
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	typedef vertex3<int32_t> ivtx;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	32 ビット浮動小数点、三次元、位置情報
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	typedef vertex3<float> fvtx;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	64 ビット倍精度浮動小数点、三次元、位置情報
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	typedef vertex3<double> dvtx;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	8 ビット整数、四次元、位置情報
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	typedef vertex4<int8_t> bvtx4;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	16 ビット整数、四次元、位置情報
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	typedef vertex4<int16_t> svtx4;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	32 ビット整数、四次元、位置情報
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	typedef vertex4<int32_t> ivtx4;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	32 ビット浮動小数点、四次元、位置情報
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	typedef vertex4<float> fvtx4;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	64 ビット倍精度浮動小数点、四次元、位置情報
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	typedef vertex4<double> dvtx4;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	次元テンプレート共通クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <typename T, int NUM>
	struct vertex_base {
		typedef T   value_type;

		inline uint32_t dim() const { return NUM; }
		inline uint32_t size() const { return sizeof(T) * NUM; }
		static inline T get_min() { T v; min_level(v); return v; }
		static inline T get_max() { T v; max_level(v); return v; }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	二次元テンプレート
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <typename T>
	struct vertex2 : public vertex_base<T, 2> {
		T	x;
		T	y;

		inline vertex2() { }
		inline vertex2(const spos& v) : x(v.x), y(v.y) { }
		inline vertex2(const ipos& v) : x(v.x), y(v.y) { }
		inline vertex2(const fpos& v) : x(v.x), y(v.y) { }
		inline vertex2(const dpos& v) : x(v.x), y(v.y) { }
		explicit inline vertex2(T c) : x(c), y(c) { }
		inline vertex2(T xx, T yy) : x(xx), y(yy) { }

		inline const T* getXY() const { return &x; }

		inline T sqrX() const { return x * x; }
		inline T sqrY() const { return y * y; }
		inline T sqr() const { return sqrX() + sqrY(); }
		inline T len() const { return std::sqrt(sqr()); }

		inline T min() const { return x < y ? x : y; }
		inline T max() const { return x > y ? x : y; }

		inline void set(T c) { x = y = c; }
		inline void set(T xx, T yy) { x = xx; y = yy; }
		inline void set(const vertex2& v) { x = v.x; y = v.y; }

		inline void add(T c) { x += c; y += c; }
		inline void add(T xx, T yy) { x += xx; y += yy; }
		inline void add(const vertex2<T>& v) { x += v.x; y += v.y; }
		inline void sub(T c) { x -= c; y -= c; }
		inline void sub(T xx, T yy) { x -= xx; y -= yy; }
		inline void sub(const vertex2<T>& v) { x -= v.x; y -= v.y; }
		inline void mul(T c) { x *= c; y *= c; }
		inline void mul(T xx, T yy) { x *= xx; y *= yy; }
		inline void mul(const vertex2<T>& v) { x *= v.x; y *= v.y; }
		inline void div(T c) { x /= c; y /= c; }
		inline void div(T xx, T yy) { x /= xx; y /= yy; }
		inline void div(const vertex2<T>& v) { x /= v.x; y /= v.y; }

		static inline T dot(const vertex2& a, const vertex2& b) { return a.x * b.x + a.y * b.y; }
		static inline T cross(const vertex2& a, const vertex2& b) { return a.x * b.y - a.y * b.x; }

		// Method necessary for using「boost/unordered_map」
		inline bool operator == (const vertex2<T>& v) const {
			if(x == v.x && y == v.y) return true;
			else return false;
		}

		inline bool operator != (const vertex2<T>& v) const {
			if(x == v.x && y == v.y) return false;
			else return true;
		}

		inline size_t hash() const {
			size_t h = 0;
			boost::hash_combine(h, x);
			boost::hash_combine(h, y);
			return h;
		}

		inline vertex2& operator = (T c) { set(c); return *this; }

		vertex2& operator = (const spos& v) {
			set(static_cast<T>(v.x), static_cast<T>(v.y)); return *this;
		}
		vertex2& operator = (const ipos& v) {
			set(static_cast<T>(v.x), static_cast<T>(v.y)); return *this;
		}
		vertex2& operator = (const fpos& v) {
			set(static_cast<T>(v.x), static_cast<T>(v.y)); return *this;
		}
		vertex2& operator = (const dpos& v) {
			set(static_cast<T>(v.x), static_cast<T>(v.y)); return *this;
		}

		inline vertex2& operator += (const vertex2& v) { add(v); return *this; }
		inline vertex2& operator += (T c) { add(c); return *this; }
		inline vertex2 operator + (T c) const {
			vertex2 t(x + c, y + c);
			return t;
		}
		inline vertex2 operator + (const vertex2& v) const {
			vertex2	t(x + v.x, y + v.y);
			return t;
		}

		inline vertex2& operator -= (const vertex2& v) { sub(v); return *this; }
		inline vertex2& operator -= (T c) { sub(c); return *this; }
		inline vertex2 operator - (T c) const {
			vertex2	t(x - c, y - c);
			return t;
		}
		inline vertex2 operator - (const vertex2& v) const {
			vertex2 t(x, y);
			t.sub(v);
			return t;
		}

		inline vertex2& operator *= (T c) { mul(c); return *this; }
		inline vertex2& operator *= (const vertex2& v) { mul(v);  return *this; }
		inline vertex2 operator * (const vertex2& v) const {
			vertex2	t(x * v.x, y * v.y);
			return t;
		}
		inline vertex2 operator * (T c) const {
			vertex2	t(x * c, y * c);
			return t;
		}

		inline vertex2& operator /= (T c) { div(c); return *this; }
		inline vertex2& operator /= (const vertex2& v) { div(v); return *this; }
		inline vertex2 operator / (T c) const {
			vertex2	t(x / c, y / c);
			return t;
		}
		inline vertex2 operator / (const vertex2& v) const {
			vertex2	t(x / v.x, y / v.y);
			return t;
		}
	};

	typedef std::vector<bpos>					bposs;
	typedef std::vector<bpos>::iterator			bposs_it;
	typedef std::vector<bpos>::const_iterator	bposs_cit;

	typedef std::vector<spos>					sposs;
	typedef std::vector<spos>::iterator			sposs_it;
	typedef std::vector<spos>::const_iterator	sposs_cit;

	typedef std::vector<ipos>					iposs;
	typedef std::vector<ipos>::iterator			iposs_it;
	typedef std::vector<ipos>::const_iterator	iposs_cit;

	typedef std::vector<fpos>					fposs;
	typedef std::vector<fpos>::iterator			fposs_it;
	typedef std::vector<fpos>::const_iterator	fposs_cit;

	typedef std::vector<dpos>					dposs;
	typedef std::vector<dpos>::iterator			dposs_it;
	typedef std::vector<dpos>::const_iterator	dposs_cit;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	三次元、位置情報テンプレート
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <typename T>
	struct vertex3 : public vertex_base<T, 3> {
		T	x;
		T	y;
		T	z;

		inline vertex3() { }
		inline vertex3(const svtx& v) : x(v.x), y(v.y), z(v.z) { }
		inline vertex3(const ivtx& v) : x(v.x), y(v.y), z(v.z) { }
		inline vertex3(const fvtx& v) : x(v.x), y(v.y), z(v.z) { }
		inline vertex3(const dvtx& v) : x(v.x), y(v.y), z(v.z) { }
		explicit inline vertex3(T c) : x(c), y(c), z(c) { }
		explicit inline vertex3(T xx, T yy, T zz = static_cast<T>(0)) : x(xx), y(yy), z(zz) { }

		inline const T* getXYZ() const { return &x; }

		inline T sqrX() const { return x * x; }
		inline T sqrY() const { return y * y; }
		inline T sqrZ() const { return z * z; }
		inline T sqr() const { return sqrX() + sqrY() + sqrZ(); }
		inline T len() const { return std::sqrt(sqr()); }

		inline T min() const {
			if(x < y) {
				if(x < z) return x;
			} else {
				if(y < z) return y;
			}
			return z;
		}
		inline T max() const {
			if(x > y) {
				if(x > z) return x;
			} else {
				if(y > z) return y;
			}
			return z;
		}

		inline void set(T c) { x = y = z = c; }
		inline void set(T xx, T yy, T zz = static_cast<T>(0)) { x = xx; y = yy; z = zz; }
		inline void set(const vertex2<T>& v) { x = v.x; y = v.y; z = static_cast<T>(0); }
		inline void set(const vertex3<T>& v) { x = v.x; y = v.y; z = v.z; }

		inline void add(T c) { x += c; y += c; z += c; }
		inline void add(T xx, T yy, T zz) { x += xx; y += yy; z += zz; }
		inline void add(const vertex3& v) { x += v.x; y += v.y; z += v.z; }
		inline void sub(T c) { x -= c; y -= c; z -= c; }
		inline void sub(T xx, T yy, T zz) { x -= xx; y -= yy; z -= zz; }
		inline void sub(const vertex3& v) { x -= v.x; y -= v.y; z -= v.z; }
		inline void mul(T c) { x *= c; y *= c; z *= c; }
		inline void mul(T xx, T yy, T zz) { x *= xx; y *= yy; z *= zz; }
		inline void mul(const vertex3& v) { x *= v.x; y *= v.y; z *= v.z; }
		inline void div(T c) { x /= c; y /= c; z /= c; }
		inline void div(T xx, T yy, T zz) { x /= xx; y /= yy; z /= zz; }
		inline void div(const vertex3& v) { x /= v.x; y /= v.y; z /= v.z; }

		static inline T dot(const vertex3& a, const vertex3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
		static inline void cross(const vertex3& a, const vertex3& b, vertex3& out) {
			out.x = a.y * b.z - a.z * b.y;
			out.y = a.z * b.x - a.x * b.z;
			out.z = a.x * b.y - a.y * b.x;
		}

		// Method necessary for using「boost/unordered_map」
		inline bool operator == (const vertex3& v) const {
			if(x == v.x && y == v.y && z == v.z) return true;
			else return false;
		}

		inline bool operator != (const vertex3& v) const {
			if(x == v.x && y == v.y && z == v.z) return false;
			else return true;
		}

		inline size_t hash() const {
			size_t h = 0;
			boost::hash_combine(h, x);
			boost::hash_combine(h, y);
			boost::hash_combine(h, z);
			return h;
		}

		inline vertex3& operator = (T c) { set(c); return *this; }
		inline vertex3& operator = (const vertex2<T>& v) { set(v); return *this; }

		vertex3& operator = (const svtx& v) {
			set(static_cast<T>(v.x), static_cast<T>(v.y), static_cast<T>(v.z));
			return *this;
		}
		vertex3& operator = (const ivtx& v) {
			set(static_cast<T>(v.x), static_cast<T>(v.y), static_cast<T>(v.z));
			return *this;
		}
		vertex3& operator = (const fvtx& v) {
			set(static_cast<T>(v.x), static_cast<T>(v.y), static_cast<T>(v.z));
			return *this;
		}
		vertex3& operator = (const dvtx& v) {
			set(static_cast<T>(v.x), static_cast<T>(v.y), static_cast<T>(v.z));
			return *this;
		}

		inline vertex3& operator += (T c) { add(c); return *this; }
		inline vertex3& operator += (const vertex3& v) { add(v); return *this; }
		inline vertex3 operator + (T c) const {
			vertex3	t(x + c, y + c, z + c);
			return t;
		}
		inline vertex3 operator + (const vertex3& v) const {
			vertex3	t(x + v.x, y + v.y, z + v.z);
			return t;
		}

		inline vertex3& operator -= (T c) { sub(c); return *this; }
		inline vertex3& operator -= (const vertex3& v) { sub(v); return *this; }
		inline vertex3 operator - (T c) const {
			vertex3	t(x - c, y - c, z - c);
			return t;
		}
		inline vertex3 operator - (const vertex3& v) const {
			vertex3	t(x - v.x, y - v.y, z - v.z);
			return t;
		}

		inline vertex3& operator *= (T c) { mul(c); return *this; }
		inline vertex3& operator *= (const vertex3& v) { mul(v); return *this; }
		inline vertex3 operator * (T c) const {
			vertex3	t(x * c, y * c, z * c);
			return t;
		}
		inline vertex3 operator * (const vertex3& v) const {
			vertex3	t(x * v.x, y * v.y, z * v.z);
			return t;
		}

		inline vertex3& operator /= (T c) { div(c); return *this; }
		inline vertex3& operator /= (const vertex3& v) { div(v); return *this; }
		inline vertex3 operator / (T c) const {
			vertex3	t(x / c, y / c, z / c);
			return t;
		}
		inline vertex3 operator / (const vertex3& v) const {
			vertex3	t(x / v.x, y / v.y, z / v.z);
			return t;
		}

	};

	typedef std::vector<bvtx>					bvtxs;
	typedef std::vector<bvtx>::iterator			bvtxs_it;
	typedef std::vector<bvtx>::const_iterator	bvtxs_cit;

	typedef std::vector<svtx>					svtxs;
	typedef std::vector<svtx>::iterator			svtxs_it;
	typedef std::vector<svtx>::const_iterator	svtxs_cit;

	typedef std::vector<ivtx>					ivtxs;
	typedef std::vector<ivtx>::iterator			ivtxs_it;
	typedef std::vector<ivtx>::const_iterator	ivtxs_cit;

	typedef std::vector<fvtx>					fvtxs;
	typedef std::vector<fvtx>::iterator			fvtxs_it;
	typedef std::vector<fvtx>::const_iterator	fvtxs_cit;

	typedef std::vector<dvtx>					dvtxs;
	typedef std::vector<dvtx>::iterator			dvtxs_it;
	typedef std::vector<dvtx>::const_iterator	dvtxs_cit;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	四次元、位置情報テンプレート
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <typename T>
	struct vertex4 : public vertex_base<T, 4> {
		T	x;
		T	y;
		T	z;
		T	w;

		inline vertex4() { }
		explicit inline vertex4(T c) : x(c), y(c), z(c), w(c) { }
		explicit inline vertex4(T xx, T yy, T zz, T ww = static_cast<T>(1)) : x(xx), y(yy), z(zz), w(ww) { }
		inline vertex4(const vertex3<T>& v) : x(v.x), y(v.y), z(v.z), w(static_cast<T>(1)) { }
		inline vertex4(const vertex4& v) : x(v.x), y(v.y), z(v.z), w(v.w) { }

		inline const T* getXYZW() const { return &x; }

		inline T sqrX() const { return x * x; }
		inline T sqrY() const { return y * y; }
		inline T sqrZ() const { return z * z; }
		inline T sqrW() const { return w * w; }
		inline T sqr() const { return (sqrX() + sqrY() + sqrZ() + sqrW()); }
		inline T len() const { return std::sqrt(sqrX() + sqrY() + sqrZ() + sqrW()); }

		inline T min() const {
			if(x < y) {
				if(x < z) {
					if(x < w) return x;
				} else {
					if(z < w) return z;
				}
			} else {
				if(y < z) {
					if(y < w) return y;
				} else {
					if(z < w) return z;
				}
			}
			return w;
		}
		inline T max() const {
			if(x > y) {
				if(x > z) {
					if(x > w) return x;
				} else {
					if(z > w) return z;
				}
			} else {
				if(y > z) {
					if(y > w) return y;
				} else {
					if(z > w) return z;
				}
			}
			return w;
		}

		inline void set(T c) { x = y = z = w = c; }
		inline void set(T xx, T yy, T zz, T ww = static_cast<T>(1)) { x = xx; y = yy; z = zz; w = ww; }
		inline void set(const vertex2<T>& v) { x = v.x; y = v.y; z = static_cast<T>(0); w = static_cast<T>(1); }
		inline void set(const vertex3<T>& v) { x = v.x; y = v.y; z = v.z; w = static_cast<T>(1); }
		inline void set(const vertex4<T>& v) { x = v.x; y = v.y; z = v.z; w = v.w;}

		inline void add(T xx, T yy, T zz, T ww = static_cast<T>(1)) { x += xx; y += yy; z += zz; w += ww; }
		inline void sub(T xx, T yy, T zz, T ww = static_cast<T>(1)) { x -= xx; y -= yy; z -= zz; w -= ww; }
		inline void mul(T xx, T yy, T zz, T ww = static_cast<T>(1)) { x *= xx; y *= yy; z *= zz; w *= ww; }
		inline void div(T xx, T yy, T zz, T ww = static_cast<T>(1)) { x /= xx; y /= yy; z /= zz; w /= ww; }

		inline bool operator == (const vertex4& v) const {
			if(x == v.x && y == v.y && z == v.z && w == v.w) return true;
			else return false;
		}

		inline bool operator != (const vertex4& v) const {
			if(x == v.x && y == v.y && z == v.z && w == v.w) return false;
			else return true;
		}

		// Method necessary for using「boost/unordered_map」
		inline size_t hash() const {
			size_t h = 0;
			boost::hash_combine(h, x);
			boost::hash_combine(h, y);
			boost::hash_combine(h, z);
			boost::hash_combine(h, w);
			return h;
		}

		inline vertex4& operator = (T c) { set(c); return *this; }
		inline vertex4& operator = (const vertex2<T>& v) { set(v); return *this; }
		inline vertex4& operator = (const vertex3<T>& v) { set(v); return *this; }
		inline vertex4& operator = (const vertex4<T>& v) { set(v); return *this; }

		inline vertex4& operator += (T c) { add(c); return *this; }
		inline vertex4& operator += (const vertex4& v) { add(v); return *this; }
		inline vertex4 operator + (T c) const {
			vertex4	t(x + c, y + c, z + c, w + c);
			return t;
		}
		inline vertex4 operator + (const vertex4& v) const {
			vertex4 t(x + v.x, y + v.y, z + v.z, w + v.w);
			return t;
		}

		inline vertex4& operator -= (T c) { sub(c); return *this; }
		inline vertex4& operator -= (const vertex4& v) { sub(v); return *this; }
		inline vertex4 operator - (T c) const {
			vertex4 t(x - c, y - c, z - c, w - c);
			return t;
		}
		inline vertex4<T> operator - (const vertex4<T>& v) const {
			vertex4<T> t(x - v.x, y - v.y, z - v.z, w - v.w);
			return t;
		}

		inline vertex4<T>& operator *= (T c) { mul(c); return *this; }
		inline vertex4<T>& operator *= (const vertex4& v) { mul(v); return *this; }
		inline vertex4<T> operator * (T c) const {
			vertex4<T> t(x * c, y * c, z * c, w * c);
			return t;
		}
		inline vertex4<T> operator * (const vertex4<T>& v) const {
			vertex4<T> t(x * v.x, y * v.y, z * v.z, w * v.w);
			return t;
		}

		inline vertex4<T>& operator /= (T c) { div(c); return *this; }
		inline vertex4<T>& operator /= (const vertex4<T>& v) { div(v); return *this; }
		inline vertex4<T> operator / (T c) const {
			vertex4<T> t(x / c, y / c, z / c, w / c);
			return t;
		}
		inline vertex4<T> operator / (const vertex4<T>& v) const {
			vertex4<T> t(x / v.x, y / v.y, z / v.z, w / v.w);
			return t;
		}
	};

	typedef std::vector<bvtx4>					bvtxs4;
	typedef std::vector<bvtx4>::iterator		bvtxs4_it;
	typedef std::vector<bvtx4>::const_iterator	bvtxs4_cit;

	typedef std::vector<svtx4>					svtxs4;
	typedef std::vector<svtx4>::iterator		svtxs4_it;
	typedef std::vector<svtx4>::const_iterator	svtxs4_cit;

	typedef std::vector<ivtx4>					ivtxs4;
	typedef std::vector<ivtx4>::iterator		ivtxs4_it;
	typedef std::vector<ivtx4>::const_iterator	ivtxs4_cit;

	typedef std::vector<fvtx4>					fvtxs4;
	typedef std::vector<fvtx4>::iterator		fvtxs4_it;
	typedef std::vector<fvtx4>::const_iterator	fvtxs4_cit;

	typedef std::vector<dvtx4>					dvtxs4;
	typedef std::vector<dvtx4>::iterator		dvtxs4_it;
	typedef std::vector<dvtx4>::const_iterator	dvtxs4_cit;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	「boost/unordered_set, unordered_map」用ハッシュ値計算
		@param[in]	v	ハッシュ・ソース座標
		@return		ハッシュ値を返す
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class T>
	inline size_t hash_value(const T& v) { return v.hash(); }


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ベクトルの距離を求める
		@param[in]	a	ベクトル A
		@param[in]	b	ベクトル B
		@return	ベクトルの距離
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class T>
	inline typename T::value_type distance(const T& a, const T& b) {
		T d = b - a;
		return d.len();
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ベクトルの内積
		@param[in]	a	ベクトル A
		@param[in]	b	ベクトル B
		@return	内積結果
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class T>
	inline typename T::value_type dot(const T& a, const T& b)
	{
		return T::dot(a, b);
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	二次元ベクトルの外積
		@param[in]	a	ベクトル A
		@param[in]	b	ベクトル B
		@return 外積結果（スカラー）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class T>
	inline typename T::value_type cross(const T& a, const T& b)
	{
		return T::cross(a, b);
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	三次元ベクトルの外積
		@param[in]	a	ベクトル A
		@param[in]	b	ベクトル B
		@param[out]	out	外積結果を受け取るベクトル（正規化されていない）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class T>
	inline void cross(const T& a, const T& b, T& out)
	{
		T::cross(a, b, out);
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ベクトルの内積、正規化
		@param[in]	a	ベクトル A
		@param[in]	b	ベクトル B
		@return	内積結果（COS θ)
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class T>
	inline typename T::value_type inner_product(const T& a, const T& b)
	{
		typename T::value_type c = a.len() * b.len();
		if(c <= T::get_min()) return T::get_max();
		return T::dot(a, b) / c;
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ベクトルの外積、正規化
		@param[in]	a	ベクトル A
		@param[in]	b	ベクトル B
		@param[out]	n	外積結果を受け取るベクトル
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class T>
	void outer_product(const T& a, const T& b, T& n)
	{
		T t;
		T::cross(a, b, t);
		typename T::value_type l = t.len();
		if(l <= T::get_min()) {
			n = static_cast<T>(0);
		} else {
			n = t / l;
		}
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	二次元ベクトルの回転(CW: 時計廻り)@n
				X' =  X COS(s) + Y SIN(s)@n
				Y' =  Y COS(s) - X SIN(s)
		@param[in]	src	ソース・ベクトル
		@param[in]	si	サイン
		@param[in]	co	コサイン
		@param[in]	dst	出力・ベクトル
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class T>
	void rotate_cw(const T& src, typename T::value_type si, typename T::value_type co, T& dst)
	{
		dst.set(src.x * co + src.y * si, src.y * co - src.x * si);
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	二次元ベクトルの回転(CCW: 反時計廻り)@n
				X' =  X COS(s) - Y SIN(s)@n
				Y' =  Y COS(s) + X SIN(s)
		@param[in]	src	ソース・ベクトル
		@param[in]	si	サイン
		@param[in]	co	コサイン
		@param[in]	dst	出力・ベクトル
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class T>
	void rotate_ccw(const T& src, typename T::value_type si, typename T::value_type co, T& dst)
	{
		dst.set(src.x * co - src.y * si, src.y * co + src.x * si);
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ライン（対の値を扱う）
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <typename T>
	class line {
	public:
		T	s;
		T	t;

		line() { }
		line(const T& ss, const T& tt) { s = ss; t = tt; }
		void set(const T& ss, const T& tt) { s = ss; t = tt; }
		void first(const T& ss) { s = ss; }
		void second(const T& tt) { t = tt; }
		T center() const { return (s + t) / static_cast<T>(2); }
		static T center(const T& ss, const T& tt) { return (ss + tt) / static_cast<T>(2); }
	};

	typedef line<fpos>	fpos_line;
	typedef line<dpos>	dpos_line;

	typedef line<fvtx>	fvtx_line;
	typedef line<dvtx>	dvtx_line;

	typedef std::vector<fpos_line>				fpos_lines;
	typedef std::vector<fpos_line>::iterator	fpos_lines_it;
	typedef std::vector<dpos_line>				dpos_lines;
	typedef std::vector<dpos_line>::iterator	dpos_lines_it;

	typedef std::vector<fvtx_line>				fvtx_lines;
	typedef std::vector<fvtx_line>::iterator	fvtx_lines_it;
	typedef std::vector<dvtx_line>				dvtx_lines;
	typedef std::vector<dvtx_line>::iterator	dvtx_lines_it;


	//-----------------------------------------------------------------//
	/*!
		@brief	vertex を正規化するテンプレート
		@param[in]	src	ソース座標列
		@param[out]	dst	生成座標列
		@return	失敗した場合に「false」を返す
	*/
	//-----------------------------------------------------------------//
	template <class T>
	bool normalize(const T& src, T& dst) {
		typename T::value_type a = src.len();
		if(a < src.get_min()) return false;
		dst = src / a;
		return true;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	vertex を正規化するテンプレート
		@param[in]	src	ソース座標列
		@return	正規化されたベクトル
	*/
	//-----------------------------------------------------------------//
	template <class T>
	T normalize(const T& src) {
		T dst;
		if(normalize(src, dst)) {
			return dst;
		} else {
			return src;
		}
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ortho_normalize
		@param[in]	a	ベクトル A
		@param[in]	b	ベクトル B
		@param[out]	dst	結果を受け取るベクトル
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    template <typename T>
    inline void ortho_normalize(const vertex3<T>& a, const vertex3<T>& b, vertex3<T>& dst)
	{
		normalize(a - b * dot(b, a), dst);
    }


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	二次元領域テンプレート・クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <typename T>
	class rectangle {
	public:
		typedef T	value_type;

		vertex2<T>		org;	///< 開始点
		vertex2<T>		size;	///< サイズ

		rectangle() { }
		rectangle(T v) : org(v), size(v) { }
		rectangle(T x, T y, T w, T h) : org(x, y), size(w, h) { }
		rectangle(const vertex2<T>& org_, const vertex2<T>& size_) : org(org_), size(size_) { }
		rectangle(const rectangle<T>& r) : org(r.org), size(r.size) { }

		bool is_focus(const vertex2<T>& p) const {
			if(size.x <= 0 || size.y <= 0) return false;
			if(org.x <= p.x && p.x < (org.x + size.x) && org.y <= p.y && p.y < (org.y + size.y)) {
				return true;
			} else {
				return false;
			}
		}
 
		void center(vertex2<T>& c) const { c = (org + size) / static_cast<T>(2); }
		vertex2<T> center() const { return (org + size) / static_cast<T>(2); }
		void end(vertex2<T>& e) const { e = org + size; }
		vertex2<T> end() const { return org + size; }

		T center_x() const { return org.x + size.x / 2; }
		T center_y() const { return org.y + size.y / 2; }
		T end_x() const { return org.x + size.x; }
		T end_y() const { return org.y + size.y; }

		// クリップ領域の構築
		bool clip(const rectangle& r) {
			vertex2<T> e = end();
			vertex2<T> re = r.end();
			if(r.org.x <= org.x && org.x < re.x) {
				if(re.x < e.x) {
					size.x = re.x - org.x;
				} 
			} else if(re.x <= org.x) {
				size.x = 0;
				return false;
			} else if(org.x < r.org.x) {
				if(e.x < r.org.x) {
					size.x = 0;
					return false;
				} else {
					org.x = r.org.x;
					if(re.x < e.x) {
						size.x = re.x - org.x;
					}
				}
			}

			if(r.org.y <= org.y && org.y < re.y) {
				if(re.y < e.y) {
					size.y = re.y - org.y;
				} 
			} else if(re.y <= org.y) {
				size.y = 0;
				return false;
			} else if(org.y < r.org.y) {
				if(e.y < r.org.y) {
					size.y = 0;
					return false;
				} else {
					org.y = r.org.y;
					if(re.y < e.y) {
						size.y = re.y - org.y;
					}
				}
			}

			return true;
		}
	};

	typedef rectangle<int16_t> srect;
	typedef rectangle<int32_t> irect;
	typedef rectangle<float>   frect;
	typedef rectangle<double>  drect;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	サークル
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <typename T>
	class circle {
		T				radius_;
		T				radius_sqr_;
	public:
		vertex2<T>		center;
		circle() { }
		circle(const vertex2<T>& cen, T r) : center(cen), radius_(r), radius_sqr_(r * r) { }
		circle(T x, T y, T r) : center(x, y), radius_(r), radius_sqr_(r * r) { }

		T get_radius() const { return radius_; }
		void set_radius(T r) { radius_ = r; radius_sqr_ = r * r; }

		bool is_focus(const vertex2<T>& p) {
			vertex2<T> d = center - p;
			if((d.x * d.x + d.y * d.y) <= radius_sqr_) return true;
			else return false;
		}
	};

	typedef circle<int>		icircle;
	typedef circle<float>	fcircle;
	typedef circle<double>	dcircle;


	//-----------------------------------------------------------------//
	/*!
		@brief	クランプした B-Spline の生成
		@param[in]	src	ソース座標列
		@param[in]	lod	分割数
		@param[out]	dst	生成座標列
		@return	失敗した場合に「false」を返す
	*/
	//-----------------------------------------------------------------//
	bool clumped_bspline(const fvtxs& src, int lod, fvtxs& dst);


	//-----------------------------------------------------------------//
	/*!
		@brief	分割したベクトル列の生成
		@param[in]	src	ソース座標列
		@param[in]	lod	分割数
		@param[out]	dst	生成座標列
		@return	失敗した場合に「false」を返す
	*/
	//-----------------------------------------------------------------//
	bool division_lines(const fvtxs& src, int lod, fvtxs& dst);


	//-----------------------------------------------------------------//
	/*!
		@brief	直線の交点を求める(float)
		@param[in]	a	ベクトル A
		@param[in]	b	ベクトル B
		@param[out]	pos	交点
		@return	「解」が無い場合、「false」が返る。
	*/
	//-----------------------------------------------------------------//
	bool intersection_line(const fpos_line& a, const fpos_line& b, fpos& pos);


	//-----------------------------------------------------------------//
	/*!
		@brief	直線の交点を求める(double)
		@param[in]	a	ベクトル A
		@param[in]	b	ベクトル B
		@param[out]	pos	交点
		@return	「解」が無い場合、「false」が返る。
	*/
	//-----------------------------------------------------------------//
	bool intersection_line(const dpos_line& a, const dpos_line& b, dpos& pos);


	//-----------------------------------------------------------------//
	/*!
		@brief	最小値を設定
		@param[in]	src		ソース
		@param[out]	min		最小値
	*/
	//-----------------------------------------------------------------//
	void set_min(const fvtx& src, fvtx& min);


	//-----------------------------------------------------------------//
	/*!
		@brief	最大値を設定
		@param[in]	src		ソース
		@param[out]	max		最大値
	*/
	//-----------------------------------------------------------------//
	void set_max(const fvtx& src, fvtx& max);


	//-----------------------------------------------------------------//
	/*!
		@brief	最小値と最大値を設定
		@param[in]	src		ソース
		@param[out]	min		最小値
		@param[out]	max		最大値
	*/
	//-----------------------------------------------------------------//
	void set_min_max(const fvtx& src, fvtx& min, fvtx& max);


	//-----------------------------------------------------------------//
	/*!
		@brief	最小値と最大値を探す (fpos)
		@param[in]	src		ソース列
		@param[out]	min		最小値
		@param[out]	max		最大値
	*/
	//-----------------------------------------------------------------//
	void scan_min_max(const fposs& src, fpos& min, fpos& max);


	//-----------------------------------------------------------------//
	/*!
		@brief	最小値と最大値を探す (dpos)
		@param[in]	src		ソース列
		@param[out]	min		最小値
		@param[out]	max		最大値
	*/
	//-----------------------------------------------------------------//
	void scan_min_max(const dposs& src, dpos& min, dpos& max);


	//-----------------------------------------------------------------//
	/*!
		@brief	最小値と最大値を探す (fvtx)
		@param[in]	src		ソース列
		@param[out]	min		最小値
		@param[out]	max		最大値
	*/
	//-----------------------------------------------------------------//
	void scan_min_max(const fvtxs& src, fvtx& min, fvtx& max);


	//-----------------------------------------------------------------//
	/*!
		@brief	最小値と最大値を探す (dvtx)
		@param[in]	src		ソース列
		@param[out]	min		最小値
		@param[out]	max		最大値
	*/
	//-----------------------------------------------------------------//
	void scan_min_max(const dvtxs& src, dvtx& min, dvtx& max);


	//-----------------------------------------------------------------//
	/*!
		@brief	ベクトルの中心位置（fpos)
		@param[in]	a	a 点
		@param[in]	b	b 点
		@param[out]	cen	中心位置
	*/
	//-----------------------------------------------------------------//
	inline void center_line(const fpos& a, const fpos& b, fpos& out) {
		out = fpos_line::center(a, b);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	ベクトルの中心位置（dpos)
		@param[in]	a	a 点
		@param[in]	b	b 点
		@param[out]	cen	中心位置
	*/
	//-----------------------------------------------------------------//
	inline void center_line(const dpos& a, const dpos& b, dpos& out) {
		out = dpos_line::center(a, b);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	ベクトルの中心位置（fvtx)
		@param[in]	a	a 点
		@param[in]	b	b 点
		@param[out]	cen	中心位置
	*/
	//-----------------------------------------------------------------//
	inline void center_line(const fvtx& a, const fvtx& b, fvtx& out) {
		out = fvtx_line::center(a, b);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	ベクトルの中心位置（dvtx)
		@param[in]	a	a 点
		@param[in]	b	b 点
		@param[out]	cen	中心位置
	*/
	//-----------------------------------------------------------------//
	inline void center_line(const dvtx& a, const dvtx& b, dvtx& out) {
		out = dvtx_line::center(a, b);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	ベクター比（fvtx)
		@param[in]	a		a 点
		@param[in]	factor	比率
		@param[in]	b		b 点
		@param[out]	out		答え
	*/
	//-----------------------------------------------------------------//
	inline void factor_line(const fvtx& a, float factor, const fvtx& b, fvtx& out) {
		out = a + (b - a) * factor;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	ベクトル列の平均（fpos)
		@param[in]	list	ベクトル列
		@param[out]	out		平均値
	*/
	//-----------------------------------------------------------------//
	inline void average(const fposs& list, fpos& out) {
		out.set(0.0f, 0.0f);
		for(fposs_cit cit = list.begin(); cit != list.end(); ++cit) {
			out += *cit;
		}
		out *= 1.0f / static_cast<float>(list.size());
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	ベクトル列の平均（fvtx)
		@param[in]	list	ベクトル列
		@param[out]	out		平均値
	*/
	//-----------------------------------------------------------------//
	inline void average(const fvtxs& list, fvtx& out) {
		out.set(0.0f, 0.0f, 0.0f);
		for(fvtxs_cit cit = list.begin(); cit != list.end(); ++cit) {
			out += *cit;
		}
		out *= 1.0f / static_cast<float>(list.size());
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	二つの頂点配列(std::vector)から、共有「する」、@n
				「しない」頂点配列(std::vector)を生成
		@param[in]	src_a	配列 A
		@param[in]	src_b	配列 B
		@param[out]	dst		共有配列
		@param[in]	share	「false」なら共有しない頂点を生成
		@return 共有する頂点が無い場合「false」
	*/
	//-----------------------------------------------------------------//
	bool make_share_vertex(const fvtxs& src_a, const fvtxs& src_b, fvtxs& dst, bool share = true);

	typedef boost::unordered_set<fvtx>					fvtx_set;
	typedef boost::unordered_set<fvtx>::iterator		fvtx_set_it;
	typedef boost::unordered_set<fvtx>::const_iterator	fvtx_set_cit;

	typedef boost::unordered_set<dvtx>					dvtx_set;
	typedef boost::unordered_set<dvtx>::iterator		dvtx_set_it;
	typedef boost::unordered_set<dvtx>::const_iterator	dvtx_set_cit;

}	// namespace vtx
