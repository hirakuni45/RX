#pragma once
//=====================================================================//
/*!	@file
	@brief	各種マトリックスの定義
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/glfw_app/blob/master/LICENSE
*/
//=====================================================================//
#include <cmath>
#include "common/vtx.hpp"

namespace mtx {

	static inline void deg_sin_cos_(float deg, float& si, float& co) {
		si = std::sin(deg * vtx::deg2rad_f_);
		co = std::cos(deg * vtx::deg2rad_f_);
	}

	static inline void deg_sin_cos_(double deg, double& si, double& co) {
		si = std::sin(deg * vtx::deg2rad_d_);
		co = std::cos(deg * vtx::deg2rad_d_);
	}

	template <typename T>
	const T& grc_(const T* p, uint32_t row, uint32_t col) {
		return p[(col << 2) + row];
	}

	template <typename T>
	T& prc_(T* p, uint32_t row, uint32_t col) {
		return p[(col << 2) + row];
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	マトリックスのコピー
		@param[in]	srd	コピー元
		@param[in]	dst	コピー先
	 */
	//-----------------------------------------------------------------//
	template <class T, int n>
	void matrix_copy(const T* src, T* dst) {
		for(uint32_t i = 0; i < n; ++i) { dst[i] = src[i]; }
	}

	//-----------------------------------------------------------------//
	/*!
		@brief	単位ユニットの設定
		@param[in]	m	出力マトリックス
	 */
	//-----------------------------------------------------------------//
	template <class T>
	void create_identity(T* m) {
		m[ 0] = static_cast<T>(1);
		m[ 1] = static_cast<T>(0);
		m[ 2] = static_cast<T>(0);
		m[ 3] = static_cast<T>(0);

		m[ 4] = static_cast<T>(0);
		m[ 5] = static_cast<T>(1);
		m[ 6] = static_cast<T>(0);
		m[ 7] = static_cast<T>(0);

		m[ 8] = static_cast<T>(0);
		m[ 9] = static_cast<T>(0);
		m[10] = static_cast<T>(1);
		m[11] = static_cast<T>(0);

		m[12] = static_cast<T>(0);
		m[13] = static_cast<T>(0);
		m[14] = static_cast<T>(0);
		m[15] = static_cast<T>(1);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	OpenGL ４×４マトリックス積
		@param[out]	out		出力マトリックス
		@param[in]	a		入力マトリックス
		@param[in]	b		入力マトリックス
	 */
	//-----------------------------------------------------------------//
	template <class T>
	void matmul4(T* out, const T* a, const T* b) {
		for(uint32_t i = 0; i < 4; ++i) {
			T ai0 = grc_(a,i,0);
			T ai1 = grc_(a,i,1);
			T ai2 = grc_(a,i,2);
			T ai3 = grc_(a,i,3);
			prc_(out,i,0) = ai0 * grc_(b,0,0) + ai1 * grc_(b,1,0) + ai2 * grc_(b,2,0) + ai3 * grc_(b,3,0);
			prc_(out,i,1) = ai0 * grc_(b,0,1) + ai1 * grc_(b,1,1) + ai2 * grc_(b,2,1) + ai3 * grc_(b,3,1);
			prc_(out,i,2) = ai0 * grc_(b,0,2) + ai1 * grc_(b,1,2) + ai2 * grc_(b,2,2) + ai3 * grc_(b,3,2);
			prc_(out,i,3) = ai0 * grc_(b,0,3) + ai1 * grc_(b,1,3) + ai2 * grc_(b,2,3) + ai3 * grc_(b,3,3);
		}
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	OpenGL ４×４マトリックスとベクターの積
		@param[out]	out		出力ベクター
		@param[in]	mat		入力マトリックス
		@param[in]	vec		入力ベクター
	 */
	//-----------------------------------------------------------------//
	template <class T>
	void matmul1(T* out, const T* mat, const T* vec) {
		out[0] = (mat[0] * vec[0]) + (mat[4] * vec[1]) + (mat[ 8] * vec[2]) + (mat[12] * vec[3]);
		out[1] = (mat[1] * vec[0]) + (mat[5] * vec[1]) + (mat[ 9] * vec[2]) + (mat[13] * vec[3]);
		out[2] = (mat[2] * vec[0]) + (mat[6] * vec[1]) + (mat[10] * vec[2]) + (mat[14] * vec[3]);
		out[3] = (mat[3] * vec[0]) + (mat[7] * vec[1]) + (mat[11] * vec[2]) + (mat[15] * vec[3]);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	OpenGL スケール（拡大／縮小）行列をベースマトリックスに合成する
		@param[out]	out		合成マトリックス
		@param[in]	x	X スケール
		@param[in]	y	Y スケール
		@param[in]	z	Z スケール
	 */
	//-----------------------------------------------------------------//
	template <class T>
	void mult_scale(T* out, T x, T y, T z) {
		out[0] *= x; out[4] *= y; out[8]  *= z;
		out[1] *= x; out[5] *= y; out[9]  *= z;
		out[2] *= x; out[6] *= y; out[10] *= z;
		out[3] *= x; out[7] *= y; out[11] *= z;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	並行移動
		@param[in]	v	移動距離
	 */
	//-----------------------------------------------------------------//
	template <class T>
	void mult_translate(T *out, T x, T y, T z) {
		vtx::vertex4<T> t(x, y, z);
		matmul1<T>(&out[12], out, t.getXYZW());
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	OpenGL 透視法による視体積行列をベースマトリックスを作成
		@param[out]	out		出力マトリックス
		@param[in]	left	クリップ平面上の位置（左）
		@param[in]	right	クリップ平面上の位置（右）
		@param[in]	bottom	クリップ平面上の位置（下）
		@param[in]	top		クリップ平面上の位置（上）
		@param[in]	nearval	クリップ平面上の位置（手前）
		@param[in]	farval	クリップ平面上の位置（奥）
	 */
	//-----------------------------------------------------------------//
	template <class T>
	void mult_frustum(T* out, T left, T right, T bottom, T top, T nearval, T farval) {
		T x = (static_cast<T>(2) * nearval) / (right - left);
		T y = (static_cast<T>(2) * nearval) / (top - bottom);
		T a = (right + left)   / (right - left);
		T b = (top + bottom)   / (top - bottom);
		T c = -(farval + nearval) / ( farval - nearval);
		T d = -(static_cast<T>(2) * farval * nearval) / (farval - nearval);  /* error? */

		T m[16];
		prc_(m,0,0) = x;
		prc_(m,0,1) = static_cast<T>(0);
		prc_(m,0,2) = a;
		prc_(m,0,3) = static_cast<T>(0);
		prc_(m,1,0) = static_cast<T>(0);
		prc_(m,1,1) = y;
		prc_(m,1,2) = b;
		prc_(m,1,3) = static_cast<T>(0);
		prc_(m,2,0) = static_cast<T>(0);
		prc_(m,2,1) = static_cast<T>(0);
		prc_(m,2,2) = c;
		prc_(m,2,3) = d;
		prc_(m,3,0) = static_cast<T>(0);
		prc_(m,3,1) = static_cast<T>(0);
		prc_(m,3,2) = static_cast<T>(-1);
		prc_(m,3,3) = static_cast<T>(0);
		matmul4<T>(out, out, m);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	OpenGL 正射影行列をベースマトリックスに合成する
		@param[out]	out		合成マトリックス
		@param[in]	left	クリップ平面上の位置（左）
		@param[in]	right	クリップ平面上の位置（右）
		@param[in]	bottom	クリップ平面上の位置（下）
		@param[in]	top		クリップ平面上の位置（上）
		@param[in]	nearval	クリップ平面上の位置（手前）
		@param[in]	farval	クリップ平面上の位置（奥）
	 */
	//-----------------------------------------------------------------//
	template <class T>
	void mult_ortho(T* out, T left, T right, T bottom, T top, T nearval, T farval) {
		T m[16];
		prc_(m,0,0) = static_cast<T>(2) / (right - left);
		prc_(m,0,1) = static_cast<T>(0);
		prc_(m,0,2) = static_cast<T>(0);
		prc_(m,0,3) = -(right + left) / (right - left);

		prc_(m,1,0) = static_cast<T>(0);
		prc_(m,1,1) = static_cast<T>(2) / (top - bottom);
		prc_(m,1,2) = static_cast<T>(0);
		prc_(m,1,3) = -(top + bottom) / (top - bottom);

		prc_(m,2,0) = static_cast<T>(0);
		prc_(m,2,1) = static_cast<T>(0);
		prc_(m,2,2) = static_cast<T>(-2) / (farval - nearval);
		prc_(m,2,3) = -(farval + nearval) / (farval - nearval);

		prc_(m,3,0) = static_cast<T>(0);
		prc_(m,3,1) = static_cast<T>(0);
		prc_(m,3,2) = static_cast<T>(0);
		prc_(m,3,3) = static_cast<T>(1);
		matmul4<T>(out, out, m);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	OpenGL gluPerspective と同等な行列をベースマトリックスに合成する
		@param[out]	out		出力マトリックス
		@param[in]	fovy	視野角度
		@param[in]	aspect	アスペクト比
		@param[in]	near	クリップ平面上の位置（手前）
		@param[in]	farv	クリップ平面上の位置（奥）
	 */
	//-----------------------------------------------------------------//
	template <class T>
	bool mult_perspective(T* out, T fovy, T aspect, T nearv, T farv) {
		T si, co;
		deg_sin_cos_(fovy * 0.5f, si, co);
		T delta = farv - nearv;
		if((delta == static_cast<T>(0)) ||
			(si == static_cast<T>(0)) || (aspect == static_cast<T>(0))) {
			return false;
		}

		T cotan = co / si;
		T m[4][4];
		m[0][0] = cotan / aspect;
		m[0][1] = static_cast<T>(0);
		m[0][2] = static_cast<T>(0);
		m[0][3] = static_cast<T>(0);

		m[1][0] = static_cast<T>(0);
		m[1][1] = cotan;
		m[1][2] = static_cast<T>(0);
		m[1][3] = static_cast<T>(0);

		m[2][0] = static_cast<T>(0);
		m[2][1] = static_cast<T>(0);
		m[2][2] = -(farv + nearv) / delta;
		m[2][3] = static_cast<T>(-1);

		m[3][0] = static_cast<T>(0);
		m[3][1] = static_cast<T>(0);
		m[3][2] = static_cast<T>(-2) * nearv * farv / delta;
		m[3][3] = static_cast<T>(0);

		matmul4<T>(out, out, &m[0][0]);
		return true;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	OpenGL gluLookAt と同等な行列をベースマトリックスに合成する
		@param[in]	eye カメラの位置
		@param[in]	center 視線座標
		@param[in]	up カメラの上向き方向ベクトル
	 */
	//-----------------------------------------------------------------//
	template <class T>
	void mult_look_at(T* out, const vtx::vertex3<T>& eye, const vtx::vertex3<T>& center, const vtx::vertex3<T>& up) {
		vtx::vertex3<T> forward;
		vtx::normalize((center - eye), forward);

		/// Side = forward x up
		vtx::vertex3<T> side;
		vtx::outer_product(forward, up, side);

	    /// Recompute t as: t = side x forward
		vtx::vertex3<T> t;
		vtx::vertex3<T>::cross(side, forward, t);
		T m[4][4];
		m[0][0] = side.x;
		m[1][0] = side.y;
		m[2][0] = side.z;
		m[3][0] = static_cast<T>(0);

		m[0][1] = t.x;
		m[1][1] = t.y;
		m[2][1] = t.z;
		m[3][1] = static_cast<T>(0);

		m[0][2] = -forward.x;
		m[1][2] = -forward.y;
		m[2][2] = -forward.z;
		m[3][2] = static_cast<T>(0);

		m[0][3] = static_cast<T>(0);
		m[1][3] = static_cast<T>(0);
		m[2][3] = static_cast<T>(0);
		m[3][3] = static_cast<T>(1);
		matmul4<T>(out, out, &m[0][0]);
		mult_translate<T>(out, -eye.x, -eye.y, -eye.z);
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	OpenGL 回転行列をベースマトリックスに合成する
		@param[in]	si  角度に対する正弦（sin）
		@param[in]	co	角度に対する余弦（cos）
		@param[in]	x	回転中心の X 要素
		@param[in]	y	回転中心の Y 要素
		@param[in]	z	回転中心の Z 要素
	 */
	//-----------------------------------------------------------------//
	template <class T>
	bool mult_rotate(T* out, T si, T co, T x, T y, T z) {
		T m[16];
		create_identity(m);
		bool optimized = false;

		if(x == static_cast<T>(0)) {
			if(y == static_cast<T>(0)) {
				if(z != static_cast<T>(0)) {
					optimized = true;
					// rotate only around z-axis
					prc_(m,0,0) = co;
					prc_(m,1,1) = co;
					if(z < 0.0f) {
						prc_(m,0,1) =  si;
						prc_(m,1,0) = -si;
					} else {
						prc_(m,0,1) = -si;
						prc_(m,1,0) =  si;
					}
				}
			} else if(z == static_cast<T>(0)) {
				optimized = true;
				// rotate only around y-axis
				prc_(m,0,0) = co;
				prc_(m,2,2) = co;
				if(y < 0.0f) {
					prc_(m,0,2) = -si;
					prc_(m,2,0) =  si;
				} else {
					prc_(m,0,2) =  si;
					prc_(m,2,0) = -si;
				}
			}
		} else if(y == static_cast<T>(0)) {
			if(z == 0.0f) {
				optimized = true;
				// rotate only around x-axis
				prc_(m,1,1) = co;
				prc_(m,2,2) = co;
				if(x < 0.0f) {
					prc_(m,1,2) =  si;
					prc_(m,2,1) = -si;
				} else {
					prc_(m,1,2) = -si;
					prc_(m,2,1) =  si;
				}
			}
		}

		if(!optimized) {
			const T mag = std::sqrt(x * x + y * y + z * z);
			if(mag <= vtx::min_value<T>()) {
				// 算術エラー（０除算と同一）
				return false;
			}

			x /= mag;
			y /= mag;
			z /= mag;

			T xx = x * x;
			T yy = y * y;
			T zz = z * z;
			T xy = x * y;
			T yz = y * z;
			T zx = z * x;
			T xs = x * si;
			T ys = y * si;
			T zs = z * si;
			T one_c = static_cast<T>(1) - co;

			// We already hold the identity-matrix so we can skip some statements
			prc_(m,0,0) = (one_c * xx) + co;
			prc_(m,0,1) = (one_c * xy) - zs;
			prc_(m,0,2) = (one_c * zx) + ys;
			prc_(m,0,3) = static_cast<T>(0);

			prc_(m,1,0) = (one_c * xy) + zs;
			prc_(m,1,1) = (one_c * yy) + co;
			prc_(m,1,2) = (one_c * yz) - xs;
			prc_(m,1,3) = static_cast<T>(0);

			prc_(m,2,0) = (one_c * zx) - ys;
			prc_(m,2,1) = (one_c * yz) + xs;
			prc_(m,2,2) = (one_c * zz) + co;
			prc_(m,2,3) = static_cast<T>(0);

			prc_(m,3,0) = static_cast<T>(0);
			prc_(m,3,1) = static_cast<T>(0);
			prc_(m,3,2) = static_cast<T>(0);
			prc_(m,3,3) = static_cast<T>(1);
		}
		matmul4<T>(out, out, m);
		return true;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	逆行列を求める（一般解の手法）
		@param[in]	src	ソースのマトリックス
		@param[in]	dst 計算された逆行列
		@return	演算が途中でストールした場合（解が求められない）「false」が返る。
	 */
	//-----------------------------------------------------------------//
	template <class T>
	bool invert_matrix(const T* src, T* dst)
	{
		const T* m = src;
		T wtmp[4][8];
		T* r0 = wtmp[0];
		T* r1 = wtmp[1];
		T* r2 = wtmp[2];
		T* r3 = wtmp[3];

		r0[0] = grc_(m,0,0);
		r0[1] = grc_(m,0,1);
		r0[2] = grc_(m,0,2);
		r0[3] = grc_(m,0,3);
		r0[4] = static_cast<T>(1);
		r0[5] = r0[6] = r0[7] = static_cast<T>(0);

		r1[0] = grc_(m,1,0);
		r1[1] = grc_(m,1,1);
		r1[2] = grc_(m,1,2);
		r1[3] = grc_(m,1,3);
		r1[5] = static_cast<T>(1);
		r1[4] = r1[6] = r1[7] = static_cast<T>(0);

		r2[0] = grc_(m,2,0);
		r2[1] = grc_(m,2,1);
		r2[2] = grc_(m,2,2);
		r2[3] = grc_(m,2,3);
		r2[6] = static_cast<T>(1);
		r2[4] = r2[5] = r2[7] = static_cast<T>(0);

		r3[0] = grc_(m,3,0);
		r3[1] = grc_(m,3,1);
		r3[2] = grc_(m,3,2);
		r3[3] = grc_(m,3,3);
		r3[7] = static_cast<T>(1);
		r3[4] = r3[5] = r3[6] = static_cast<T>(0);

		/// choose pivot - or die
		if(std::abs(r3[0]) > std::abs(r2[0])) std::swap(r3, r2);
		if(std::abs(r2[0]) > std::abs(r1[0])) std::swap(r2, r1);
		if(std::abs(r1[0]) > std::abs(r0[0])) std::swap(r1, r0);
		if(static_cast<T>(0) == r0[0])  return false;

		/// eliminate first variable
		T m1 = r1[0] / r0[0];
		T m2 = r2[0] / r0[0];
		T m3 = r3[0] / r0[0];
		T s;
		s = r0[1]; r1[1] -= m1 * s; r2[1] -= m2 * s; r3[1] -= m3 * s;
		s = r0[2]; r1[2] -= m1 * s; r2[2] -= m2 * s; r3[2] -= m3 * s;
		s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;
		s = r0[4];
		if(s != static_cast<T>(0)) { r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s; }
		s = r0[5];
		if(s != static_cast<T>(0)) { r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s; }
		s = r0[6];
		if(s != static_cast<T>(0)) { r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s; }
		s = r0[7];
		if(s != static_cast<T>(0)) { r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s; }

		/// choose pivot - or die
		if(std::abs(r3[1]) > std::abs(r2[1])) std::swap(r3, r2);
		if(std::abs(r2[1]) > std::abs(r1[1])) std::swap(r2, r1);
		if(static_cast<T>(0) == r1[1])  return false;

		/// eliminate second variable
		m2 = r2[1] / r1[1];
		m3 = r3[1] / r1[1];
		r2[2] -= m2 * r1[2]; r3[2] -= m3 * r1[2];
		r2[3] -= m2 * r1[3]; r3[3] -= m3 * r1[3];
		s = r1[4]; if(static_cast<T>(0) != s) { r2[4] -= m2 * s; r3[4] -= m3 * s; }
		s = r1[5]; if(static_cast<T>(0) != s) { r2[5] -= m2 * s; r3[5] -= m3 * s; }
		s = r1[6]; if(static_cast<T>(0) != s) { r2[6] -= m2 * s; r3[6] -= m3 * s; }
		s = r1[7]; if(static_cast<T>(0) != s) { r2[7] -= m2 * s; r3[7] -= m3 * s; }

		/// choose pivot - or die
		if(std::abs(r3[2]) > std::abs(r2[2])) std::swap(r3, r2);
		if(static_cast<T>(0) == r2[2])  return false;

		/// eliminate third variable
		m3 = r3[2] / r2[2];
		r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
		r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
		r3[7] -= m3 * r2[7];

		/// last check
		if(static_cast<T>(0) == r3[3]) return false;

		s = static_cast<T>(1) / r3[3];		///< now back substitute row 3
		r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

		m2 = r2[3];				///< now back substitute row 2
		s  = 1.0f / r2[2];
		r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
		r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
		m1 = r1[3];
		r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
		r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
		T m0 = r0[3];
		r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
		r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

		m1 = r1[2];                 /* now back substitute row 1 */
		s  = 1.0f / r1[1];
		r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
		r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
		m0 = r0[2];
		r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
		r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

		m0 = r0[1];                 /* now back substitute row 0 */
		s  = 1.0f / r0[0];
		r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
		r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

		prc_(dst,0,0) = r0[4]; prc_(dst,0,1) = r0[5], prc_(dst,0,2) = r0[6]; prc_(dst,0,3) = r0[7],
		prc_(dst,1,0) = r1[4]; prc_(dst,1,1) = r1[5], prc_(dst,1,2) = r1[6]; prc_(dst,1,3) = r1[7],
		prc_(dst,2,0) = r2[4]; prc_(dst,2,1) = r2[5], prc_(dst,2,2) = r2[6]; prc_(dst,2,3) = r2[7],
		prc_(dst,3,0) = r3[4]; prc_(dst,3,1) = r3[5], prc_(dst,3,2) = r3[6]; prc_(dst,3,3) = r3[7];

		return true;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	逆行列を求める（一般解の手法）
		@param[in]	src	ソースのマトリックス
		@param[in]	dst 計算された逆行列
		@return	演算が途中でストールした場合（解が求められない）「false」が返る。
	 */
	//-----------------------------------------------------------------//
	template <class T>
	bool invert_matrix_3d(const T* src, T* dst)
	{
		/* Calculate the determinant of upper left 3x3 submatrix and
		* determine if the matrix is singular.
		*/
		T pos = static_cast<T>(0);
		T neg = static_cast<T>(0);
		T t;
		t = grc_(src,0,0) * grc_(src,1,1) * grc_(src,2,2);
		if(t >= static_cast<T>(0)) pos += t; else neg += t;

		t = grc_(src,1,0) * grc_(src,2,1) * grc_(src,0,2);
		if(t >= static_cast<T>(0)) pos += t; else neg += t;

		t = grc_(src,2,0) * grc_(src,0,1) * grc_(src,1,2);
		if(t >= static_cast<T>(0)) pos += t; else neg += t;

		t = -grc_(src,2,0) * grc_(src,1,1) * grc_(src,0,2);
		if(t >= static_cast<T>(0)) pos += t; else neg += t;

		t = -grc_(src,1,0) * grc_(src,0,1) * grc_(src,2,2);
		if(t >= static_cast<T>(0)) pos += t; else neg += t;

		t = -grc_(src,0,0) * grc_(src,2,1) * grc_(src,1,2);
		if(t >= static_cast<T>(0)) pos += t; else neg += t;

		T det = pos + neg;

		if((det * det) < vtx::min_value<T>()) {
			return false;
		}

		det = static_cast<T>(1) / det;
		prc_(dst,0,0) =  (grc_(src,1,1) * grc_(src,2,2) - grc_(src,2,1) * grc_(src,1,2)) * det;
		prc_(dst,0,1) = -(grc_(src,0,1) * grc_(src,2,2) - grc_(src,2,1) * grc_(src,0,2)) * det;
		prc_(dst,0,2) =  (grc_(src,0,1) * grc_(src,1,2) - grc_(src,1,1) * grc_(src,0,2)) * det;
		prc_(dst,1,0) = -(grc_(src,1,0) * grc_(src,2,2) - grc_(src,2,0) * grc_(src,1,2)) * det;
		prc_(dst,1,1) =  (grc_(src,0,0) * grc_(src,2,2) - grc_(src,2,0) * grc_(src,0,2)) * det;
		prc_(dst,1,2) = -(grc_(src,0,0) * grc_(src,1,2) - grc_(src,1,0) * grc_(src,0,2)) * det;
		prc_(dst,2,0) =  (grc_(src,1,0) * grc_(src,2,1) - grc_(src,2,0) * grc_(src,1,1)) * det;
		prc_(dst,2,1) = -(grc_(src,0,0) * grc_(src,2,1) - grc_(src,2,0) * grc_(src,0,1)) * det;
		prc_(dst,2,2) =  (grc_(src,0,0) * grc_(src,1,1) - grc_(src,1,0) * grc_(src,0,1)) * det;

		/* Do the translation part */
		prc_(dst,0,3) = -(grc_(src,0,3) * grc_(dst,0,0) +
			grc_(src,1,3) * grc_(dst,0,1) +
			grc_(src,2,3) * grc_(dst,0,2));
		prc_(dst,1,3) = -(grc_(src,0,3) * grc_(dst,1,0) +
			grc_(src,1,3) * grc_(dst,1,1) +
			grc_(src,2,3) * grc_(dst,1,2));
		prc_(dst,2,3) = -(grc_(src,0,3) * grc_(dst,2,0) +
			grc_(src,1,3) * grc_(dst,2,1) +
			grc_(src,2,3) * grc_(dst,2,2) );
		return true;
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	４×４マトリックス・テンプレート
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <typename T>
	struct matrix4 {
		typedef T  value_type;

	private:
		T	m_[16] __attribute__((aligned(16)));

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
		 */
		//-----------------------------------------------------------------//
		matrix4() { }


		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	srcm	マトリックス
		 */
		//-----------------------------------------------------------------//
		matrix4(const matrix4<T>& srcm) { matrix_copy<T, 16>(srcm(), m_); }


		//-----------------------------------------------------------------//
		/*!
			@brief	コンストラクター
			@param[in]	srcm	基本型のポインター
		 */
		//-----------------------------------------------------------------//
		explicit matrix4(const T* srcm) { matrix_copy<T, 16>(srcm, m_); }


		//-----------------------------------------------------------------//
		/*!
			@brief	デストラクター
		 */
		//-----------------------------------------------------------------//
		~matrix4() { }


		//-----------------------------------------------------------------//
		/*!
			@brief	ゼロ・リセット
		 */
		//-----------------------------------------------------------------//
		void zero() {
			for(uint32_t i = 0; i < 16; ++i) {
				m_[i] = static_cast<T>(0);
			}
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	単位ユニットの設定
		 */
		//-----------------------------------------------------------------//
		void identity() { create_identity(m_); }


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL マトリックスのロード
			@param[in]	srcm	ソース・マトリックス配列
		 */
		//-----------------------------------------------------------------//
		void load(const T* srcm) { matrix_copy<T, 16>(srcm, m_); }


		//-----------------------------------------------------------------//
		/*!
			@brief	逆行列を求める
			@param[in]	srcm	ソース・マトリックス配列
			@return エラーなら「false」
		 */
		//-----------------------------------------------------------------//
		bool inverse(const T* srcm) { return invert_matrix<T>(srcm, m_); }


		//-----------------------------------------------------------------//
		/*!
			@brief	逆行列を求める(3D)
			@param[in]	srcm	ソース・マトリックス配列
			@return エラーなら「false」
		 */
		//-----------------------------------------------------------------//
		bool inverse_3d(const T* srcm) { return invert_matrix_3d<T>(srcm, m_); }


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL スケーリング
			@param[in]	v	スケールファクター
		 */
		//-----------------------------------------------------------------//
		void scale(const vtx::vertex3<T>& v) { mult_scale<T>(m_, v.x, v.y, v.z); }


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL 並行移動
			@param[in]	v	移動距離
		 */
		//-----------------------------------------------------------------//
		void translate(const vtx::vertex3<T>& v) { mult_translate<T>(m_, v.x, v.y, v.z); }


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL 回転行列をベースマトリックスに合成する@n
					※内部は、クオータニオンによる軸指定の回転となる。
			@param[in]	angle	0 〜 360 度の(DEG)角度
			@param[in]	v	回転中心座標
		 */
		//-----------------------------------------------------------------//
		void rotate(T angle, const vtx::vertex3<T>& v) {
			T si, co;
			deg_sin_cos_(angle, si, co);
			mult_rotate<T>(m_, si, co, v.x, v.y, v.z);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL 透視法による視体積行列をベースマトリックスに合成する
			@param[in]	left	クリップ平面上の位置（左）
			@param[in]	right	クリップ平面上の位置（右）
			@param[in]	bottom	クリップ平面上の位置（下）
			@param[in]	top		クリップ平面上の位置（上）
			@param[in]	nearval	クリップ平面上の位置（手前）
			@param[in]	farval	クリップ平面上の位置（奥）
		 */
		//-----------------------------------------------------------------//
		void frustum(T left, T right, T bottom, T top, T nearval, T farval) {
			mult_frustum<T>(m_, left, right, bottom, top, nearval, farval);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL 正射影行列をベースマトリックスに合成する
			@param[in]	left	クリップ平面上の位置（左）
			@param[in]	right	クリップ平面上の位置（右）
			@param[in]	bottom	クリップ平面上の位置（下）
			@param[in]	top		クリップ平面上の位置（上）
			@param[in]	nearval	クリップ平面上の位置（手前）
			@param[in]	farval	クリップ平面上の位置（奥）
		 */
		//-----------------------------------------------------------------//
		void ortho(T left, T right, T bottom, T top, T nearval, T farval) {
			mult_ortho<T>(m_, left, right, bottom, top, nearval, farval);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL gluPerspective と同等な行列をベースマトリックスに合成する
			@param[in]	fovy	視野角度
			@param[in]	aspect	アスペクト比
			@param[in]	zNear	クリップ平面上の位置（手前）
			@param[in]	zFar	クリップ平面上の位置（奥）
		 */
		//-----------------------------------------------------------------//
		void perspective(T fovy, T aspect, T zNear, T zFar) {
			mult_perspective<T>(m_, fovy, aspect, zNear, zFar);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL GLU gluLookAt と同等な行列をベースマトリックスに合成する
			@param[in]	eye カメラの位置
			@param[in]	center 視線座標
			@param[in]	up カメラの上向き方向ベクトル
		 */
		//-----------------------------------------------------------------//
		void look_at(const vtx::vertex3<T>& eye, const vtx::vertex3<T>& center, const vtx::vertex3<T>& up) {
			mult_look_at<T>(m_, eye, center, up);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	頂点座標のマトリックス変換を行う
			@param[in]	vin 入力ベクトル
			@param[out]	out	出力ベクトル(4)
		 */
		//-----------------------------------------------------------------//
		void vertex_mult(const vtx::vertex3<T>& vin, vtx::vertex4<T>& out) {
			vtx::vertex4<T> t(vin.x, vin.y, vin.z);
			matmul1<T>(out, m_, t.xyzw);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	頂点座標のマトリックス変換を行う
			@param[in]	vin 入力ベクトル
			@param[out]	out	出力ベクトル(3)
		 */
		//-----------------------------------------------------------------//
		void vertex_mult(const vtx::vertex3<T>& vin, vtx::vertex3<T>& out) {
			vtx::vertex4<T> t(vin.x, vin.y, vin.z);
			float o[4];
			matmul1<T>(o, m_, t.getXYZW());
			out.x = o[0];
			out.y = o[1];
			out.z = o[2];
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	= オペレーター 4x4（代入）
			@param[in]	srcm	ソースマトリックス(float*)
		 */
		//-----------------------------------------------------------------//
		matrix4<T>& operator = (const T* srcm) {
			matrix_copy<T, 16>(srcm, m_);
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	= オペレーター 4x4（代入）
			@param[in]	srcm	ソースマトリックス(float*)
		 */
		//-----------------------------------------------------------------//
		matrix4<T>& operator = (const matrix4<T>& srcm) {
			matrix_copy<T, 16>(srcm(), m_);
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	* オペレーター 4x4（マトリックスとの積）
			@param[in]	srcm	ソースマトリックス
		 */
		//-----------------------------------------------------------------//
		matrix4<T> operator * (const matrix4<T>& srcm) const {
			matrix4<T> t;
			matmul4(t(), m_, srcm.m);
			return t;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	*= オペレーター 4x4（マトリックスとの積）
			@param[in]	srcm	ソースマトリックス
		 */
		//-----------------------------------------------------------------//
		matrix4<T>& operator *= (const matrix4<T>& srcm) {
			matmul4(m_, m_, srcm());
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	* オペレーター 4（マトリックスとの積）
			@param[in]	srcv	ソースベクター
		 */
		//-----------------------------------------------------------------//
		matrix4<T> operator * (const vtx::vertex4<T>& srcv) const {
			matrix4 t;
			matmul1(t, m_, srcv);
			return t;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	*= オペレーター 4（マトリックスとの積）
			@param[in]	srcv	ソースベクター
		 */
		//-----------------------------------------------------------------//
		matrix4<T>& operator *= (const vtx::vertex4<T>& srcv) {
			matmul1(m_, m_, srcv);
			return *this;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	[] オペレーター
			@param[in]	n	配列の位置
			@return 値の参照
		 */
		//-----------------------------------------------------------------//
		T& operator[] (uint32_t n) { return m_[n]; }


		//-----------------------------------------------------------------//
		/*!
			@brief	() オペレーター
			@return 先頭ポインター
		 */
		//-----------------------------------------------------------------//
		const T* operator() () const { return &m_[0]; }
	};
	typedef matrix4<float>	fmat4;	///< 「float」型マトリックス
	typedef matrix4<double>	dmat4;	///< 「double」型マトリックス

}
