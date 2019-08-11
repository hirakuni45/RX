#pragma once
//=====================================================================//
/*!	@file
	@brief	ファイル情報クラス @n
			ファイルの属性、容量、などの情報にアクセスする。
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2019 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=====================================================================//
#include <string>

namespace utils {

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief	ファイル入情報クラス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	class file_info {
		std::string		name_;
		bool			directory_;
		size_t			size_;
		time_t			time_;
		mode_t			mode_;
		bool			drive_;

	public:
		//-----------------------------------------------------------------//
		/*!
			@brief	標準コンストラクター
		*/
		//-----------------------------------------------------------------//
		file_info() : name_(), directory_(false), size_(0), time_(0), mode_(0), drive_(false) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	初期化コンストラクター
			@param[in]	name	ファイル名
			@param[in]	directory	ディレクトリーの場合に「true」
			@param[in]	size	ファイル・サイズ
			@param[in]	tm		時間
			@param[in]	mt		モード
			@param[in]	drv		ドライブ（省略すると「false」）
		*/
		//-----------------------------------------------------------------//
		file_info(const std::string& name, bool directory, size_t size, const time_t tm, const mode_t mt, bool drv = false) : name_(name), directory_(directory), size_(size), time_(tm), mode_(mt), drive_(drv) { }


		//-----------------------------------------------------------------//
		/*!
			@brief	初期化
			@param[in]	name	ファイル名
			@param[in]	directory	ディレクトリーの場合に「true」
			@param[in]	size	ファイル・サイズ
			@param[in]	tm		時間
			@param[in]	mt		モード
			@param[in]	drv		ドライブ（省略すると「false」）
		*/
		//-----------------------------------------------------------------//
		void initialize(const std::string& name, bool directory, size_t size, const time_t tm, const mode_t mt, bool drv = false) { file_info(name, directory, size, tm, mt, drv); }


		//-----------------------------------------------------------------//
		/*!
			@brief	ファイル名を得る
			@return ファイル名を返す
		*/
		//-----------------------------------------------------------------//
		const std::string& get_name() const { return name_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	デイレクトリーか検査
			@return ディレクトリーの場合は「true」
		*/
		//-----------------------------------------------------------------//
		bool is_directory() const { return directory_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ファイル・サイズを得る
			@return ファイルサイズを返す@n
					ディレクトリーの場合、常に０
		*/
		//-----------------------------------------------------------------//
		size_t get_size() const { return size_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	タイム・スタンプを得る
			@return ファイルサイズを返す
		*/
		//-----------------------------------------------------------------//
		time_t get_time() const { return time_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ファイルモード得る
			@return ファイルモードを返す
		*/
		//-----------------------------------------------------------------//
		mode_t get_mode() const { return mode_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	ドライブか検査
			@return ドライブの場合は「true」
		*/
		//-----------------------------------------------------------------//
		bool is_drive() const { return drive_; }


		//-----------------------------------------------------------------//
		/*!
			@brief	sort 用オペレーター
			@return 文字列の比較
		*/
		//-----------------------------------------------------------------//
		bool operator < (const file_info& right) const {
			return name_ < right.name_;
		}
	};
}
