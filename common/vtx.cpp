//=====================================================================//
/*!	@file
	@brief	各種頂点の実装
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2017 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/glfw_app/blob/master/LICENSE
*/
//=====================================================================//
#include "utils/vtx.hpp"

namespace vtx {

	static fvtx get_vtx(const fvtxs& src, int pos)
	{
		if(pos < 0) return src[0];
		else if(pos < (int)src.size()) return src[pos];
		else return src[src.size() - 1];
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	クランプした B-Spline の生成
		@param[in]	src	ソース座標列
		@param[in]	lod	分割数
		@param[out]	dst	生成座標列
		@return	失敗した場合に「false」を返す
	*/
	//-----------------------------------------------------------------//
	bool clumped_bspline(const fvtxs& src, int lod, fvtxs& dst)
	{
		int size = (int)src.size();
		if(size < 4) return false;

		dst.clear();
		for(int n = -3; n < (size + 1); ++n) {
			for(int i = 0; i < lod; ++i) {
				float t = static_cast<float>(i) / static_cast<float>(lod);
				float it = 1.0f - t;

			// bezier
//				float b0 =     t * t  * t;
//				float b1 = 3 * t * t  * it;
//				float b2 = 3 * t * it * it;
//				float b3 =         it * it * it;

			// clumped bspline
				float b0 = it * it * it / 6.0f;
				float b1 = (3.0f * t * t * t - 6.0f * t * t + 4.0f) / 6.0f;
				float b2 = (-3.0f * t * t * t + 3.0f * t * t + 3.0f * t + 1.0f) / 6.0f;
				float b3 =  t * t * t / 6.0f;

				fvtx v0 = get_vtx(src, n + 0);
				fvtx v1 = get_vtx(src, n + 1);
				fvtx v2 = get_vtx(src, n + 2);
				fvtx v3 = get_vtx(src, n + 3);
				fvtx v;
				v.x = b0 * v0.x + b1 * v1.x + b2 * v2.x + b3 * v3.x;
				v.y = b0 * v0.y + b1 * v1.y + b2 * v2.y + b3 * v3.y;
				v.z = b0 * v0.z + b1 * v1.z + b2 * v2.z + b3 * v3.z;
				dst.push_back(v);
			}
		}

		return true;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	分割したベクトル列の生成（近似値となるので注意）
		@param[in]	src	ソース座標列
		@param[in]	lod	分割数
		@param[out]	dst	生成座標列
		@return	失敗した場合に「false」を返す
	*/
	//-----------------------------------------------------------------//
	bool division_lines(const fvtxs& src, int lod, fvtxs& dst)
	{
		int size = (int)src.size();
		if(src.size() == 0) return false;

		fvtx base = src[0];
		float r = 0.0f;
		for(int i = 1; i < size; ++i) {
			fvtx d = src[i] - base;
			base = src[i];
			r += sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
		}

		r /= (float)lod;

		dst.clear();
		base = src[0];
		float lim = 0.0f;
		dst.push_back(base);
		for(int i = 1; i < size; ++i) {
			fvtx d = src[i] - base;
			lim += sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
			if(lim >= r) {
				float n = 0.5f;
				fvtx v = (src[i] + base) * n;
				dst.push_back(v);
				lim = 0.0f;
			}
			base = src[i];
		}
		dst.push_back(src[size - 1]);

		return true;
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	直線の交点を求める(float)
		@param[in]	a	ベクトル A
		@param[in]	b	ベクトル B
		@param[out]	pos	交点
		@return	「解」が無い場合、「false」が返る。
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	bool intersection_line(const fpos_line& a, const fpos_line& b, fpos& pos)
	{
		fpos ad = a.t - a.s;
		fpos bd = b.t - b.s;

		float det = bd.x * ad.y - bd.y * ad.x;
		if(det <= FLT_MIN && det >= -FLT_MIN) return false;

		fpos d = b.s - a.s;
		float t1 = (bd.x * d.y - bd.y * d.x) / det;
		float t2 = (ad.x * d.y - ad.y * d.x) / det;

		// この範囲を超えた場合は、線分の延長線上にある。
		if(0.0f <= t1 && t1 <= 1.0f && 0.0f <= t2 && t2 <= 1.0f) ;
		else return false;

		pos = a.s + ad * t1;

		return true;
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	直線の交点を求める(double)
		@param[in]	a	ベクトル A
		@param[in]	b	ベクトル B
		@param[out]	pos	交点
		@return	「解」が無い場合、「false」が返る。
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	bool intersection_line(const dpos_line& a, const dpos_line& b, dpos& pos)
	{
		dpos ad = a.t - a.s;
		dpos bd = b.t - b.s;

		double det = bd.x * ad.y - bd.y * ad.x;
		if(det <= DBL_MIN && det >= -DBL_MIN) return false;

		dpos d = b.s - a.s;
		double t1 = (bd.x * d.y - bd.y * d.x) / det;
		double t2 = (ad.x * d.y - ad.y * d.x) / det;

		// この範囲を超えた場合は、線分の延長線上にある。
		if(0.0 <= t1 && t1 <= 1.0 && 0.0 <= t2 && t2 <= 1.0) ;
		else return false;

		pos = a.s + ad * t1;

		return true;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	最小値を設定
		@param[in]	src		ソース
		@param[out]	min		最小値
	*/
	//-----------------------------------------------------------------//
	void set_min(const fvtx& src, fvtx& min)
	{
		if(min.x > src.x) min.x = src.x;
		if(min.y > src.y) min.y = src.y;
		if(min.z > src.z) min.z = src.z;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	最大値を設定
		@param[in]	src		ソース
		@param[out]	max		最大値
	*/
	//-----------------------------------------------------------------//
	void set_max(const fvtx& src, fvtx& max)
	{
		if(max.x < src.x) max.x = src.x;
		if(max.y < src.y) max.y = src.y;
		if(max.z < src.z) max.z = src.z;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	最小値と最大値を設定
		@param[in]	src		ソース
		@param[out]	min		最小値
		@param[out]	max		最大値
	*/
	//-----------------------------------------------------------------//
	void set_min_max(const fvtx& src, fvtx& min, fvtx& max)
	{
		if(min.x > src.x) min.x = src.x;
		else if(max.x < src.x) max.x = src.x;
		if(min.y > src.y) min.y = src.y;
		else if(max.y < src.y) max.y = src.y;
		if(min.z > src.z) min.z = src.z;
		else if(max.z < src.z) max.z = src.z;
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	最小値と最大値を探す(fpos)
		@param[in]	src		ソース・リスト
		@param[out]	min		最小値
		@param[out]	max		最大値
	*/
	//-----------------------------------------------------------------//
	void scan_min_max(const fposs& src, fpos& min, fpos& max)
	{
		bool init = false;
		for(fposs_cit cit = src.begin(); cit != src.end(); cit++) {
			fpos pos = *cit;
			if(init == false) {
				min = pos;
				max = pos;
				init = true;
			} else {
				if(min.x > pos.x) min.x = pos.x;
				if(min.y > pos.y) min.y = pos.y;
				if(max.x < pos.x) max.x = pos.x;
				if(max.y < pos.y) max.y = pos.y;
			}
		}
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	最小値と最大値を探す(dpos)
		@param[in]	src		ソース・リスト
		@param[out]	min		最小値
		@param[out]	max		最大値
	*/
	//-----------------------------------------------------------------//
	void scan_min_max(const dposs& src, dpos& min, dpos& max)
	{
		bool init = false;
		for(dposs_cit cit = src.begin(); cit != src.end(); cit++) {
			dpos pos = *cit;
			if(init == false) {
				min = pos;
				max = pos;
				init = true;
			} else {
				if(min.x > pos.x) min.x = pos.x;
				if(min.y > pos.y) min.y = pos.y;
				if(max.x < pos.x) max.x = pos.x;
				if(max.y < pos.y) max.y = pos.y;
			}
		}
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	最小値と最大値を探す(fvtx)
		@param[in]	src		ソース・リスト
		@param[out]	min		最小値
		@param[out]	max		最大値
	*/
	//-----------------------------------------------------------------//
	void scan_min_max(const fvtxs& src, fvtx& min, fvtx& max)
	{
		bool init = false;
		for(fvtxs_cit cit = src.begin(); cit != src.end(); cit++) {
			fvtx pos = *cit;
			if(init == false) {
				min = pos;
				max = pos;
				init = true;
			} else {
				if(min.x > pos.x) min.x = pos.x;
				if(min.y > pos.y) min.y = pos.y;
				if(min.z > pos.z) min.z = pos.z;
				if(max.x < pos.x) max.x = pos.x;
				if(max.y < pos.y) max.y = pos.y;
				if(max.z < pos.z) max.z = pos.z;
			}
		}
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	最小値と最大値を探す(dvtx)
		@param[in]	src		ソース・リスト
		@param[out]	min		最小値
		@param[out]	max		最大値
	*/
	//-----------------------------------------------------------------//
	void scan_min_max(const dvtxs& src, dvtx& min, dvtx& max)
	{
		bool init = false;
		for(dvtxs_cit cit = src.begin(); cit != src.end(); cit++) {
			dvtx pos = *cit;
			if(init == false) {
				min = pos;
				max = pos;
				init = true;
			} else {
				if(min.x > pos.x) min.x = pos.x;
				if(min.y > pos.y) min.y = pos.y;
				if(min.z > pos.z) min.z = pos.z;
				if(max.x < pos.x) max.x = pos.x;
				if(max.y < pos.y) max.y = pos.y;
				if(max.z < pos.z) max.z = pos.z;
			}
		}
	}


	//-----------------------------------------------------------------//
	/*!
		@brief	二つの頂点配列(std::vector)から、共有「する」、@n
				「しない」頂点配列(std::vector)を生成
		@param[in]	src_a	配列 A
		@param[in]	src_b	配列 B
		@param[out]	dst		共有配列
		@param[in]	share	「true」なら共有頂点、「false」なら共有しない頂点
		@return 共有する頂点が無い場合「false」
	*/
	//-----------------------------------------------------------------//
	bool make_share_vertex(const fvtxs& src_a, const fvtxs& src_b, fvtxs& dst, bool share)
	{
		if(src_a.empty() == true || src_b.empty() == true) return false;

		fvtx_set db;
		for(fvtxs_cit cit = src_a.begin(); cit != src_a.end(); ++cit) {
			db.insert(*cit);
		}

		size_t s = dst.size();
		if(share) {
			for(fvtxs_cit cit = src_b.begin(); cit != src_b.end(); ++cit) {
				const fvtx& v = *cit;
				if(db.find(v) != db.end()) {
					dst.push_back(v);
				}
			}
		} else {
			for(fvtxs_cit cit = src_b.begin(); cit != src_b.end(); ++cit) {
				const fvtx& v = *cit;
				if(db.find(v) == db.end()) {
					dst.push_back(v);
				}
			}
		}
		return (s != dst.size());
	}

}
