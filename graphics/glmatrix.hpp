#pragma once
//=====================================================================//
/*!	@file
	@brief	OpenGL マトリックス・エミュレーター
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017, 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include "common/vtx.hpp"
#include "common/mtx.hpp"
#include "common/fixed_stack.hpp"

namespace gl {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	OpenGL matrix エミュレータークラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <typename T>
	struct matrix {

		typedef T	value_type;
		typedef mtx::matrix4<T> matrix_type;

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		/*!
			@brief	マトリックス・モード
		*/
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
		enum class mode {
			modelview,
			projection,
			num_
		};

	private:
		static const uint32_t STACK_SIZE = 4;

		mode		mode_;

		matrix_type	acc_[mode::num_];
		typedef utils::fixed_stack<matrix_type, STACK_SIZE>	STACK;
		STACK		stack_;

		T			near_;
		T			far_;

		int			vp_x_;
		int			vp_y_;
		int			vp_w_;
		int			vp_h_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL 系マトリックス操作コンストラクター
		 */
		//-----------------------------------------------------------------//
		matrix() : mode_(mode::modelview),
				   near_(0.0f), far_(1.0f),
				   vp_x_(0), vp_y_(0), vp_w_(0), vp_h_(0)
		{ }


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL マトリックスモードを設定
			@param[in]	md	マトリックス・モード
		 */
		//-----------------------------------------------------------------//
		void set_mode(mode md) { mode_ = md; }


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL マトリックスモードを取得
			@return マトリックスモード
		 */
		//-----------------------------------------------------------------//
		mode get_mode() const { return mode_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL ビューポートを取り出す。
			@param[in]	x	X 軸の位置
			@param[in]	y	Y 軸の位置
			@param[in]	w	X 軸の幅
			@param[in]	h	Y 軸の高さ
		 */
		//-----------------------------------------------------------------//
		void get_viewport(int& x, int& y, int& w, int& h) const {
			x = vp_x_;
			y = vp_y_;
			w = vp_w_;
			h = vp_h_;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL ビューポートの設定
			@param[in]	x	X 軸の位置
			@param[in]	y	Y 軸の位置
			@param[in]	w	X 軸の幅
			@param[in]	h	Y 軸の高さ
		 */
		//-----------------------------------------------------------------//
		void set_viewport(int x, int y, int w, int h) {
			vp_x_ = x;
			vp_y_ = y;
			vp_w_ = w;
			vp_h_ = h;
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL カレント・マトリックスに単位行列をセット
		 */
		//-----------------------------------------------------------------//
		void identity() { acc_[mode_].identity(); }


		//-----------------------------------------------------------------//
		/*!
			@brief	カレント・マトリックスにロード
			@param[in]	m	マトリックスのポインター先頭（fmat4）
		 */
		//-----------------------------------------------------------------//
		void load(const value_type& m) { acc_[mode_] = m; }


		//-----------------------------------------------------------------//
		/*!
			@brief	カレント・マトリックスにロード
			@param[in]	m	マトリックスのポインター先頭（float）
		 */
		//-----------------------------------------------------------------//
		void load(const T* m) { acc_[mode_] = m; }


		//-----------------------------------------------------------------//
		/*!
			@brief	カレント・マトリックスにロード
			@param[in]	m	マトリックスのポインター先頭（double）
		 */
		//-----------------------------------------------------------------//
		void load(const double* m) { acc_[mode_] = m; }


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL 4 X 4 行列をカレント・マトリックスと積算
			@param[in]	m	4 X 4 マトリックス
		 */
		//-----------------------------------------------------------------//
		void mult(const mtx::matrix4<T>& m) {
			mtx::matmul4<T>(acc_[mode_].m, acc_[mode_].m, m.m);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL 4 X 4 行列をカレント・マトリックスと積算
			@param[in]	m	マトリックス列（float）
		 */
		//-----------------------------------------------------------------//
		void mult(const float* m) {
			mtx::matrix4<T> tm = m;
			mtx::matmul4<T>(acc_[mode_].m, acc_[mode_].m, tm.m);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL 4 X 4 行列をカレント・マトリックスと積算
			@param[in]	m	マトリックス列（double）
		 */
		//-----------------------------------------------------------------//
		void mult(const double* m) {
			mtx::matrix4<T> tm = m;
			mtx::matmul4<T>(acc_[mode_].m, acc_[mode_].m, tm.m);
		}

		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL カレント・マトリックスをスタックに退避
		 */
		//-----------------------------------------------------------------//
		void push() { stack_[mode_].push(acc_[mode_]); }


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL カレント・マトリックスをスタックから復帰
		 */
		//-----------------------------------------------------------------//
		void pop() { stack_[mode_].pop(); acc_[mode_] = stack_[mode_].top(); }


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL 視体積行列をカレント・マトリックスに合成する
			@param[in]	left	クリップ平面上の位置（左）
			@param[in]	right	クリップ平面上の位置（右）
			@param[in]	bottom	クリップ平面上の位置（下）
			@param[in]	top		クリップ平面上の位置（上）
			@param[in]	nearval	クリップ平面上の位置（手前）
			@param[in]	farval	クリップ平面上の位置（奥）
		 */
		//-----------------------------------------------------------------//
		void frustum(T left, T right, T bottom, T top, T nearval, T farval) {
			near_ = nearval;
			far_ = farval;
			acc_[mode_].frustum(left, right, bottom, top, nearval, farval);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL 正射影行列をカレント・マトリックスに合成する
			@param[in]	left	クリップ平面上の位置（左）
			@param[in]	right	クリップ平面上の位置（右）
			@param[in]	bottom	クリップ平面上の位置（下）
			@param[in]	top		クリップ平面上の位置（上）
			@param[in]	nearval	クリップ平面上の位置（手前）
			@param[in]	farval	クリップ平面上の位置（奥）
		 */
		//-----------------------------------------------------------------//
		void ortho(T left, T right, T bottom, T top, T nearval, T farval) {
			near_ = nearval;
			far_  = farval;
			acc_[mode_].ortho(left, right, bottom, top, nearval, farval);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL/GLU gluPerspective と同等な行列をカレント・マトリックスに合成する
			@param[in]	fovy	視野角度
			@param[in]	aspect	アスペクト比
			@param[in]	nearval	クリップ平面上の位置（手前）
			@param[in]	farval	クリップ平面上の位置（奥）
		 */
		//-----------------------------------------------------------------//
		void perspective(T fovy, T aspect, T nearval, T farval) {
			near_ = nearval;
			far_  = farval;
			acc_[mode_].perspective(fovy, aspect, nearval, farval);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL/GLU gluLookAt と同等な行列をカレント・マトリックスに合成する
			@param[in]	eye カメラの位置
			@param[in]	center 視線方向
			@param[in]	up カメラの上向き方向ベクトル
		 */
		//-----------------------------------------------------------------//
		void look_at(const vtx::vertex3<T>& eye, const vtx::vertex3<T>& center, const vtx::vertex3<T>& up) {
			acc_[mode_].look_at(eye, center, up);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL スケール
			@param[in]	v	スケール
		 */
		//-----------------------------------------------------------------//
		void scale(const vtx::vertex3<T>& v) { acc_[mode_].scale(v); }


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL スケール
			@param[in]	x	X スケール
			@param[in]	y	Y スケール
			@param[in]	z	Z スケール
		 */
		//-----------------------------------------------------------------//
		void scale(T x, T y, T z) { acc_[mode_].scale(vtx::vertex3<T>(x, y, z)); }
 

		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL 移動行列をカレント・マトリックスに合成する
			@param[in]	x	X 軸移動量
			@param[in]	y	Y 軸移動量
			@param[in]	z	Z 軸移動量
		 */
		//-----------------------------------------------------------------//
		void translate(T x, T y, T z) {
			acc_[mode_].translate(vtx::vertex3<T>(x, y, z));
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	OpenGL 回転行列をカレント・マトリックスに合成する
			@param[in]	angle	0 〜 360 度の(DEG)角度
			@param[in]	x	回転中心の X 要素
			@param[in]	y	回転中心の Y 要素
			@param[in]	z	回転中心の Z 要素
		 */
		//-----------------------------------------------------------------//
		void rotate(T angle, T x, T y, T z) {
			acc_[mode_].rotate(angle, vtx::vertex3<T>(x, y, z));
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	カレント・マトリックスを参照
			@return	OpenGL 並びの、ベースマトリックス
		 */
		//-----------------------------------------------------------------//
		matrix_type& at_current_matrix() { return acc_[mode_]; };


		//-----------------------------------------------------------------//
		/*!
			@brief	カレント・マトリックスを得る
			@return	OpenGL 並びの、ベースマトリックス
		 */
		//-----------------------------------------------------------------//
		const matrix_type& get_current_matrix() const { return acc_[mode_]; };


		//-----------------------------------------------------------------//
		/*!
			@brief	プロジェクション・マトリックスを得る
			@return	OpenGL 並びの、ベースマトリックス
		 */
		//-----------------------------------------------------------------//
		const matrix_type& get_projection_matrix() const {
			return acc_[mode::projection];
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	モデル・マトリックスを得る
			@return	OpenGL 並びの、ベースマトリックス
		 */
		//-----------------------------------------------------------------//
		const matrix_type& get_modelview_matrix() const {
			return acc_[mode::modelview];
		};


		//-----------------------------------------------------------------//
		/*!
			@brief	ワールド・マトリックス（最終）を計算する
			@return	OpenGL 並びの、ワールド・マトリックス
		 */
		//-----------------------------------------------------------------//
		void world_matrix(matrix_type& mat) const {
			mtx::matmul4(mat.m, acc_[mode::projection].m, acc_[mode::modelview].m);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	頂点から変換された座標を得る
			@param[in]	mat		ベース・マトリックス
			@param[in]	inv		頂点
			@param[out]	out		変換された座標
			@param[out]	scr		スクリーン座標
		 */
		//-----------------------------------------------------------------//
		void vertex(const matrix_type& mat, const vtx::vertex3<T>& inv, vtx::vertex3<T>& out, vtx::vertex3<T>& scr) const {
			vtx::vertex4<T> in = inv;
			T o[4];
			mtx::matmul1<T>(o, mat.m, in.getXYZW());
			out.set(o[0], o[1], o[2]);
			T invw = static_cast<T>(1) / o[3];
			T w = (far_ * near_) / (far_ - near_) * invw;
			scr.set(out.x * invw, out.y * invw, w);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	頂点から変換されたワールド座標を得る
			@param[in]	mat		ベース・マトリックス
			@param[in]	inv		頂点
			@param[out]	out		結果を受け取るベクター
		 */
		//-----------------------------------------------------------------//
		static void vertex_world(const matrix_type& mat, const vtx::vertex3<T>& inv, vtx::vertex4<T>& out) {
			vtx::vertex4<T> in = inv;
			T o[4];
			mtx::matmul1<T>(o, mat(), in.getXYZW());
			out.set(o[0], o[1], o[2], o[3]);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	頂点から正規化されたスクリーン座標を得る
			@param[in]	mat		ベース・マトリックス
			@param[in]	inv		頂点
			@param[out]	outv	結果を受け取るベクター
		 */
		//-----------------------------------------------------------------//
		void vertex_screen(const mtx::matrix4<T>& mat, const vtx::vertex3<T>& inv, vtx::vertex3<T>& outv) const {
			T out[4];
			vtx::vertex4<T> in = inv;
			mtx::matmul1<T>(out, mat.m, in.getXYZW());
			T invw = 1.0f / out[3];
			T w = (far_ * near_) / (far_ - near_) * invw;
			outv.set(out[0] * invw, out[1] * invw, w);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief	マウス座標を正規化する
			@param[in]	mspos	マウス位置（左上が0,0）
			@param[in]	rpos	正規化された位置
		 */
		//-----------------------------------------------------------------//
		void regularization_mouse_position(const vtx::spos& mspos, vtx::vertex2<T>& rpos) const {
			T fw = static_cast<T>(vp_w_) / static_cast<T>(2);
			T fh = static_cast<T>(vp_h_) / static_cast<T>(2);
			rpos.set((static_cast<float>(mspos.x) - fw) / fw, (fh - static_cast<float>(mspos.y)) / fh);
		}


#if 0
		//-----------------------------------------------------------------//
		/*!
			@brief	カレント・マトリックスの表示
		 */
		//-----------------------------------------------------------------//
		void print_matrix() {
			for(int i = 0; i < 4; ++i) {
				std::cout << utils::format("(%d) %-1.5f, %-1.5f, %-1.5f, %-1.5f\n")
					% i
					% acc_[mode_].m[0 * 4 + i]
					% acc_[mode_].m[1 * 4 + i]
					% acc_[mode_].m[2 * 4 + i]
					% acc_[mode_].m[3 * 4 + i];
			}
		}
#endif
	};

	typedef matrix<float>	matrixf;
	typedef matrix<double>	matrixd;	
}
