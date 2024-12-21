#pragma once
//=========================================================================//
/*!	@file
	@brief	I/O ユーティリティー
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2013, 2024 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
//=========================================================================//
#include <cstdint>

namespace device {

	/// RX micro controller address type 
	typedef uint32_t address_type;

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ８ビット書き込み
		@param[in]	adr		書き込みアドレス
		@param[in]	data	書き込みデータ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	inline void wr8_(address_type adr, uint8_t data) noexcept {
		*reinterpret_cast<volatile uint8_t*>(adr) = data;
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ８ビット読み込み
		@param[in]	adr		読み込みアドレス
		@param[in]	data	読み込みデータ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	inline uint8_t rd8_(address_type adr) noexcept {
		return *reinterpret_cast<volatile uint8_t*>(adr);
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  １６ビット書き込み
		@param[in]	adr		書き込みアドレス
		@param[in]	data	書き込みデータ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	inline void wr16_(address_type adr, uint16_t data) noexcept {
		*reinterpret_cast<volatile uint16_t*>(adr) = data;
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  １６ビット読み込み
		@param[in]	adr		読み込みアドレス
		@param[in]	data	読み込みデータ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	inline uint16_t rd16_(address_type adr) noexcept {
		return *reinterpret_cast<volatile uint16_t*>(adr);
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ３２ビット書き込み
		@param[in]	adr		書き込みアドレス
		@param[in]	data	書き込みデータ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	inline void wr32_(address_type adr, uint32_t data) noexcept {
		*reinterpret_cast<volatile uint32_t*>(adr) = data;
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ３２ビット読み込み
		@param[in]	adr		読み込みアドレス
		@param[in]	data	読み込みデータ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	inline uint32_t rd32_(address_type adr) noexcept {
		return *reinterpret_cast<volatile uint32_t*>(adr);
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ６４ビット書き込み
		@param[in]	adr		書き込みアドレス
		@param[in]	data	書き込みデータ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	inline void wr64_(address_type adr, uint32_t data) noexcept {
		*reinterpret_cast<volatile uint64_t*>(adr) = data;
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ６４ビット読み込み
		@param[in]	adr		読み込みアドレス
		@param[in]	data	読み込みデータ
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	inline uint32_t rd64_(address_type adr) noexcept {
		return *reinterpret_cast<volatile uint64_t*>(adr);
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Read/Write 8 bits アクセス・テンプレート
		@param[in]	adr	アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <address_type adr>
	struct rw8_t {

		typedef uint8_t value_type;

		static constexpr auto address = adr;	///< アドレス定義
		static constexpr uint8_t bus = 8;		///< バス幅
		static constexpr bool rd = true;		///< 読出し
		static constexpr bool wr = true;		///< 書き込み

		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	data	書き込み値
		*/
		//-----------------------------------------------------------------//
		static void write(value_type data) noexcept {
			wr8_(adr, data);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief 読み出し
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		static value_type read() noexcept {
			return rd8_(adr);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief = オペレーター
			@param[in]	data	書き込み値
		*/
		//-----------------------------------------------------------------//
		void operator = (value_type data) noexcept { write(data); }


		//-----------------------------------------------------------------//
		/*!
			@brief () オペレーター
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		value_type operator () () noexcept { return read(); }


		//-----------------------------------------------------------------//
		/*!
			@brief |= オペレーター
			@param[in]	data	論理和値
		*/
		//-----------------------------------------------------------------//
		void operator |= (value_type data) noexcept { write(read() | data); }


		//-----------------------------------------------------------------//
		/*!
			@brief &= オペレーター
			@param[in]	data	論理積値
		*/
		//-----------------------------------------------------------------//
		void operator &= (value_type data) noexcept { write(read() & data); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Read/Write 8 bits NULL アクセス・テンプレート
		@param[in]	adr	アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <address_type adr>
	struct rw8_null_t {

		typedef uint8_t value_type;

		static constexpr auto address = adr;	///< アドレス定義
		static constexpr uint8_t bus = 8;		///< バス幅
		static constexpr bool rd = false;		///< 読出し
		static constexpr bool wr = false;		///< 書き込み

		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	data	書き込み値
		*/
		//-----------------------------------------------------------------//
		static void write(value_type data) noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief 読み出し
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		static value_type read() noexcept { return 0; }


		//-----------------------------------------------------------------//
		/*!
			@brief = オペレーター
			@param[in]	data	書き込み値
		*/
		//-----------------------------------------------------------------//
		void operator = (value_type data) noexcept { write(data); }


		//-----------------------------------------------------------------//
		/*!
			@brief () オペレーター
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		value_type operator () () noexcept { return read(); }


		//-----------------------------------------------------------------//
		/*!
			@brief |= オペレーター
			@param[in]	data	論理和値
		*/
		//-----------------------------------------------------------------//
		void operator |= (value_type data) noexcept { write(read() | data); }


		//-----------------------------------------------------------------//
		/*!
			@brief &= オペレーター
			@param[in]	data	論理積値
		*/
		//-----------------------------------------------------------------//
		void operator &= (value_type data) noexcept { write(read() & data); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Read/Write 8 bits アクセス・テンプレート、インデックス付
		@param[in]	adr	アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <address_type adr>
	struct rw8_index_t {

		typedef uint8_t value_type;

		static constexpr auto address = adr;	///< アドレス定義
		static constexpr uint8_t bus = 8;		///< バス幅
		static constexpr bool rd = true;		///< 読出し
		static constexpr bool wr = true;		///< 書き込み

		static inline uint32_t index;

		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	data	書き込み値
		*/
		//-----------------------------------------------------------------//
		static void write(value_type data) noexcept {
			wr8_(adr + index, data);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief 読み出し
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		static value_type read() noexcept {
			return rd8_(adr + index);
		}


		//-----------------------------------------------------------------//
		/*!
			@brief = オペレーター
			@param[in]	data	書き込み値
		*/
		//-----------------------------------------------------------------//
		void operator = (value_type data) noexcept { write(data); }


		//-----------------------------------------------------------------//
		/*!
			@brief () オペレーター
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		value_type operator () () noexcept { return read(); }


		//-----------------------------------------------------------------//
		/*!
			@brief |= オペレーター
			@param[in]	data	論理和値
		*/
		//-----------------------------------------------------------------//
		void operator |= (value_type data) noexcept { write(read() | data); }


		//-----------------------------------------------------------------//
		/*!
			@brief &= オペレーター
			@param[in]	data	論理積値
		*/
		//-----------------------------------------------------------------//
		void operator &= (value_type data) noexcept { write(read() & data); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Read Only 8 bits アクセス・テンプレート
		@param[in]	adr	アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <address_type adr>
	struct ro8_t {

		typedef uint8_t value_type;

		static constexpr auto address = adr;	///< アドレス定義
		static constexpr uint8_t bus = 8;		///< バス幅
		static constexpr bool rd = true;		///< 読出し
		static constexpr bool wr = false;		///< 書き込み

		//-----------------------------------------------------------------//
		/*!
			@brief 読み出し
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		static value_type read() noexcept { return rd8_(adr); }


		//-----------------------------------------------------------------//
		/*!
			@brief () オペレーター
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		value_type operator () () noexcept { return read(); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Write Only 8 bits アクセス・テンプレート
		@param[in]	adr	アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <address_type adr>
	struct wo8_t {

		typedef uint8_t value_type;

		static constexpr auto address = adr;	///< アドレス定義
		static constexpr uint8_t bus = 8;		///< バス幅
		static constexpr bool rd = false;		///< 読出し
		static constexpr bool wr = true;		///< 書き込み

		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	data	書き込み値
		*/
		//-----------------------------------------------------------------//
		static void write(value_type data) noexcept { wr8_(adr, data); }


		//-----------------------------------------------------------------//
		/*!
			@brief = オペレーター
			@return 書き込み値
		*/
		//-----------------------------------------------------------------//
		void operator = (value_type data) noexcept { write(data); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Read/Write 16 bits アクセス・テンプレート
		@param[in]	adr	アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <address_type adr>
	struct rw16_t {

		typedef uint16_t value_type;

		static constexpr auto address = adr;	///< アドレス定義
		static constexpr uint8_t bus = 16;		///< バス幅
		static constexpr bool rd = true;		///< 読出し
		static constexpr bool wr = true;		///< 書き込み

		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	data	書き込み値
		*/
		//-----------------------------------------------------------------//
		static void write(value_type data) noexcept { wr16_(adr, data); }


		//-----------------------------------------------------------------//
		/*!
			@brief 読み出し
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		static value_type read() noexcept { return rd16_(adr); }


		//-----------------------------------------------------------------//
		/*!
			@brief = オペレーター
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		void operator = (value_type data) noexcept { write(data); }


		//-----------------------------------------------------------------//
		/*!
			@brief () オペレーター
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		value_type operator () () noexcept { return read(); }


		//-----------------------------------------------------------------//
		/*!
			@brief |= オペレーター
			@return 論理和値
		*/
		//-----------------------------------------------------------------//
		void operator |= (value_type data) noexcept { write(read() | data); }


		//-----------------------------------------------------------------//
		/*!
			@brief &= オペレーター
			@return 論理積値
		*/
		//-----------------------------------------------------------------//
		void operator &= (value_type data) noexcept { write(read() & data); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Read/Write 16 bits NULL アクセス・テンプレート
		@param[in]	adr	アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <address_type adr>
	struct rw16_null_t {

		typedef uint16_t value_type;

		static constexpr auto address = adr;	///< アドレス定義
		static constexpr uint8_t bus = 16;		///< バス幅
		static constexpr bool rd = false;		///< 読出し
		static constexpr bool wr = false;		///< 書き込み

		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	data	書き込み値
		*/
		//-----------------------------------------------------------------//
		static void write(value_type data) noexcept { }


		//-----------------------------------------------------------------//
		/*!
			@brief 読み出し
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		static value_type read() noexcept { return 0; }


		//-----------------------------------------------------------------//
		/*!
			@brief = オペレーター
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		void operator = (value_type data) noexcept { write(data); }


		//-----------------------------------------------------------------//
		/*!
			@brief () オペレーター
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		value_type operator () () noexcept { return read(); }


		//-----------------------------------------------------------------//
		/*!
			@brief |= オペレーター
			@return 論理和値
		*/
		//-----------------------------------------------------------------//
		void operator |= (value_type data) noexcept { write(read() | data); }


		//-----------------------------------------------------------------//
		/*!
			@brief &= オペレーター
			@return 論理積値
		*/
		//-----------------------------------------------------------------//
		void operator &= (value_type data) noexcept { write(read() & data); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Read/Write 16 bits アクセス・テンプレート、インデックス付
		@param[in]	adr	アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <address_type adr>
	struct rw16_index_t {

		typedef uint16_t value_type;

		static constexpr auto address = adr;	///< アドレス定義
		static constexpr uint8_t bus = 16;		///< バス幅
		static constexpr bool rd = true;		///< 読出し
		static constexpr bool wr = true;		///< 書き込み

		static inline uint32_t index;

		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	data	書き込み値
		*/
		//-----------------------------------------------------------------//
		static void write(value_type data) noexcept { wr16_(adr + index, data); }


		//-----------------------------------------------------------------//
		/*!
			@brief 読み出し
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		static value_type read() noexcept { return rd16_(adr + index); }


		//-----------------------------------------------------------------//
		/*!
			@brief = オペレーター
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		void operator = (value_type data) noexcept { write(data); }


		//-----------------------------------------------------------------//
		/*!
			@brief () オペレーター
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		value_type operator () () noexcept { return read(); }


		//-----------------------------------------------------------------//
		/*!
			@brief |= オペレーター
			@return 論理和値
		*/
		//-----------------------------------------------------------------//
		void operator |= (value_type data) noexcept { write(read() | data); }


		//-----------------------------------------------------------------//
		/*!
			@brief &= オペレーター
			@return 論理積値
		*/
		//-----------------------------------------------------------------//
		void operator &= (value_type data) noexcept { write(read() & data); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Read Only 16 bits アクセス・テンプレート
		@param[in]	adr	アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <address_type adr>
	struct ro16_t {

		typedef uint16_t value_type;

		static constexpr auto address = adr;	///< アドレス定義
		static constexpr uint8_t bus = 16;		///< バス幅
		static constexpr bool rd = true;		///< 読出し
		static constexpr bool wr = false;		///< 書き込み

		//-----------------------------------------------------------------//
		/*!
			@brief 読み出し
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		static value_type read() noexcept { return rd16_(adr); }


		//-----------------------------------------------------------------//
		/*!
			@brief () オペレーター
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		value_type operator () () noexcept { return read(); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Write Only 16 bits アクセス・テンプレート
		@param[in]	adr	アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <address_type adr>
	struct wo16_t {

		typedef uint16_t value_type;

		static constexpr auto address = adr;	///< アドレス定義
		static constexpr uint8_t bus = 16;		///< バス幅
		static constexpr bool rd = false;		///< 読出し
		static constexpr bool wr = true;		///< 書き込み

		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	data	書き込み値
		*/
		//-----------------------------------------------------------------//
		static void write(value_type data) noexcept { wr16_(adr, data); }


		//-----------------------------------------------------------------//
		/*!
			@brief = オペレーター
			@return 書き込み値
		*/
		//-----------------------------------------------------------------//
		void operator = (value_type data) noexcept { write(data); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Read/Write 32 bits アクセス・テンプレート
		@param[in]	adr	アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <address_type adr>
	struct rw32_t {

		typedef uint32_t value_type;

		static constexpr auto address = adr;	///< アドレス定義
		static constexpr uint8_t bus = 32;		///< バス幅
		static constexpr bool rd = true;		///< 読出し
		static constexpr bool wr = true;		///< 書き込み

		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	data	書き込み値
		*/
		//-----------------------------------------------------------------//
		static void write(value_type data) noexcept { wr32_(adr, data); }


		//-----------------------------------------------------------------//
		/*!
			@brief 読み出し
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		static value_type read() noexcept { return rd32_(adr); }


		//-----------------------------------------------------------------//
		/*!
			@brief = オペレーター
			@return 書き込み値
		*/
		//-----------------------------------------------------------------//
		void operator = (value_type data) noexcept { write(data); }


		//-----------------------------------------------------------------//
		/*!
			@brief () オペレーター
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		value_type operator () () noexcept { return read(); }


		//-----------------------------------------------------------------//
		/*!
			@brief |= オペレーター
			@return 論理和値
		*/
		//-----------------------------------------------------------------//
		void operator |= (value_type data) noexcept { write(read() | data); }


		//-----------------------------------------------------------------//
		/*!
			@brief &= オペレーター
			@return 論理積値
		*/
		//-----------------------------------------------------------------//
		void operator &= (value_type data) noexcept { write(read() & data); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Read/Write 32 bits アクセス・テンプレート、インデックス付
		@param[in]	adr	アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <address_type adr>
	struct rw32_index_t {

		typedef uint32_t value_type;

		static constexpr auto address = adr;	///< アドレス定義
		static constexpr uint8_t bus = 32;		///< バス幅
		static constexpr bool rd = true;		///< 読出し
		static constexpr bool wr = true;		///< 書き込み

		static inline uint32_t index;

		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	data	書き込み値
		*/
		//-----------------------------------------------------------------//
		static void write(value_type data) noexcept { wr32_(adr + index, data); }


		//-----------------------------------------------------------------//
		/*!
			@brief 読み出し
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		static value_type read() noexcept { return rd32_(adr + index); }


		//-----------------------------------------------------------------//
		/*!
			@brief = オペレーター
			@return 書き込み値
		*/
		//-----------------------------------------------------------------//
		void operator = (value_type data) noexcept { write(data); }


		//-----------------------------------------------------------------//
		/*!
			@brief () オペレーター
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		value_type operator () () noexcept { return read(); }


		//-----------------------------------------------------------------//
		/*!
			@brief |= オペレーター
			@return 論理和値
		*/
		//-----------------------------------------------------------------//
		void operator |= (value_type data) noexcept { write(read() | data); }


		//-----------------------------------------------------------------//
		/*!
			@brief &= オペレーター
			@return 論理積値
		*/
		//-----------------------------------------------------------------//
		void operator &= (value_type data) noexcept { write(read() & data); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Temp Read/Write 32 bits アクセス・テンプレート
		@param[in]	adr	アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <address_type adr>
	struct trw32_t {

		typedef uint32_t value_type;

		static constexpr auto address = adr;	///< アドレス定義
		static constexpr uint8_t bus = 32;		///< バス幅
		static constexpr bool rd = true;		///< 読出し
		static constexpr bool wr = true;		///< 書き込み

		static inline uint32_t	tmp_;

		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	data	書き込み値
		*/
		//-----------------------------------------------------------------//
		static void write(value_type data) noexcept { tmp_ = data; wr32_(adr, data); }


		//-----------------------------------------------------------------//
		/*!
			@brief 読み出し（テンポラリー）
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		static value_type read() noexcept { return tmp_; }


		//-----------------------------------------------------------------//
		/*!
			@brief = オペレーター
			@return 書き込み値
		*/
		//-----------------------------------------------------------------//
		void operator = (value_type data) noexcept { write(data); }


		//-----------------------------------------------------------------//
		/*!
			@brief () オペレーター
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		value_type operator () () noexcept { return read(); }


		//-----------------------------------------------------------------//
		/*!
			@brief |= オペレーター
			@return 論理和値
		*/
		//-----------------------------------------------------------------//
		void operator |= (value_type data) noexcept { write(read() | data); }


		//-----------------------------------------------------------------//
		/*!
			@brief &= オペレーター
			@return 論理積値
		*/
		//-----------------------------------------------------------------//
		void operator &= (value_type data) noexcept { write(read() & data); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Read Only 32 bits アクセス・テンプレート
		@param[in]	adr	アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <address_type adr>
	struct ro32_t {

		typedef uint32_t value_type;

		static constexpr auto address = adr;	///< アドレス定義
		static constexpr uint8_t bus = 32;		///< バス幅
		static constexpr bool rd = true;		///< 読出し
		static constexpr bool wr = false;		///< 書き込み

		//-----------------------------------------------------------------//
		/*!
			@brief 読み出し
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		static value_type read() noexcept { return rd32_(adr); }


		//-----------------------------------------------------------------//
		/*!
			@brief () オペレーター
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		value_type operator () () noexcept { return read(); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Write Only 32 bits アクセス・テンプレート
		@param[in]	adr	アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <address_type adr>
	struct wo32_t {

		typedef uint32_t value_type;

		static constexpr auto address = adr;	///< アドレス定義
		static constexpr uint8_t bus = 32;		///< バス幅
		static constexpr bool rd = false;		///< 読出し
		static constexpr bool wr = true;		///< 書き込み

		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	data	書き込み値
		*/
		//-----------------------------------------------------------------//
		static void write(value_type data) noexcept { wr32_(adr, data); }


		//-----------------------------------------------------------------//
		/*!
			@brief = オペレーター
			@return 書き込み値
		*/
		//-----------------------------------------------------------------//
		void operator = (value_type data) noexcept { write(data); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Read/Write 64 bits アクセス・テンプレート
		@param[in]	adr	アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <address_type adr>
	struct rw64_t {

		typedef uint64_t value_type;

		static constexpr auto address = adr;	///< アドレス定義
		static constexpr uint8_t bus = 64;		///< バス幅
		static constexpr bool rd = true;		///< 読出し
		static constexpr bool wr = true;		///< 書き込み

		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	data	書き込み値
		*/
		//-----------------------------------------------------------------//
		static void write(value_type data) noexcept { wr64_(adr, data); }


		//-----------------------------------------------------------------//
		/*!
			@brief 読み出し
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		static value_type read() noexcept { return rd64_(adr); }


		//-----------------------------------------------------------------//
		/*!
			@brief = オペレーター
			@return 書き込み値
		*/
		//-----------------------------------------------------------------//
		void operator = (value_type data) noexcept { write(data); }


		//-----------------------------------------------------------------//
		/*!
			@brief () オペレーター
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		value_type operator () () noexcept { return read(); }


		//-----------------------------------------------------------------//
		/*!
			@brief |= オペレーター
			@return 論理和値
		*/
		//-----------------------------------------------------------------//
		void operator |= (value_type data) noexcept { write(read() | data); }


		//-----------------------------------------------------------------//
		/*!
			@brief &= オペレーター
			@return 論理積値
		*/
		//-----------------------------------------------------------------//
		void operator &= (value_type data) noexcept { write(read() & data); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Read Only 64 bits アクセス・テンプレート
		@param[in]	adr	アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <address_type adr>
	struct ro64_t {

		typedef uint64_t value_type;

		static constexpr auto address = adr;	///< アドレス定義
		static constexpr uint8_t bus = 64;		///< バス幅
		static constexpr bool rd = true;		///< 読出し
		static constexpr bool wr = false;		///< 書き込み

		//-----------------------------------------------------------------//
		/*!
			@brief 読み出し
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		static value_type read() noexcept { return rd64_(adr); }


		//-----------------------------------------------------------------//
		/*!
			@brief () オペレーター
			@return 読み出し値
		*/
		//-----------------------------------------------------------------//
		value_type operator () () noexcept { return read(); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Write Only 64 bits アクセス・テンプレート
		@param[in]	adr	アドレス
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <address_type adr>
	struct wo64_t {

		typedef uint64_t value_type;

		static constexpr auto address = adr;	///< アドレス定義
		static constexpr uint8_t bus = 64;		///< バス幅
		static constexpr bool rd = false;		///< 読出し
		static constexpr bool wr = true;		///< 書き込み

		//-----------------------------------------------------------------//
		/*!
			@brief  書き込み
			@param[in]	data	書き込み値
		*/
		//-----------------------------------------------------------------//
		static void write(value_type data) noexcept { wr64_(adr, data); }


		//-----------------------------------------------------------------//
		/*!
			@brief = オペレーター
			@return 書き込み値
		*/
		//-----------------------------------------------------------------//
		void operator = (value_type data) noexcept { write(data); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  ビット位置定義
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	enum class bitpos : uint8_t {
		B0,		///< ビット０
		B1,		///< ビット１
		B2,		///< ビット２
		B3,		///< ビット３
		B4,		///< ビット４
		B5,		///< ビット５
		B6,		///< ビット６
		B7,		///< ビット７
		B8,		///< ビット８
		B9,		///< ビット９
		B10,	///< ビット１０
		B11,	///< ビット１１
		B12,	///< ビット１２
		B13,	///< ビット１３
		B14,	///< ビット１４
		B15,	///< ビット１５
		B16,	///< ビット１６
		B17,	///< ビット１７
		B18,	///< ビット１８
		B19,	///< ビット１９
		B20,	///< ビット２０
		B21,	///< ビット２１
		B22,	///< ビット２２
		B23,	///< ビット２３
		B24,	///< ビット２４
		B25,	///< ビット２５
		B26,	///< ビット２６
		B27,	///< ビット２７
		B28,	///< ビット２８
		B29,	///< ビット２９
		B30,	///< ビット３０
		B31,	///< ビット３１
		NONE,	///< 無効ビット
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Read/Write ビット・アクセス・テンプレート
		@param[in]	T	アクセス・クラス
		@param[in]	pos	ビット位置
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class T, bitpos pos>
	struct bit_rw_t {

		typedef T value_type;

		static constexpr auto POS = pos;
		static constexpr uint8_t LEN = 1;

		static bool get() noexcept {
			return (T::read() >> static_cast<typename T::value_type>(pos)) & 1;
		}

		static void set(bool v) noexcept {
			if(v) {
				T::write(T::read() | (1 << static_cast<typename T::value_type>(pos)));
			} else {
				T::write(T::read() & ~(1 << static_cast<typename T::value_type>(pos)));
			}
		}

	    static typename T::value_type b(bool v = true) noexcept {
			return static_cast<typename T::value_type>(v) << static_cast<typename T::value_type>(pos);
		}

		void operator = (bool v) noexcept { set(v); }

		bool operator () () noexcept { return get(); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Read/Write ビット・アクセス・テンプレート
		@param[in]	T	アクセス・クラス
		@param[in]	pos	初期ビット位置
		@param[in]	len	ビット幅
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class T, bitpos pos, uint8_t len>
	struct bits_rw_t {

		typedef T value_type;

		static constexpr auto POS = pos;
		static constexpr auto LEN = len;

		static typename T::value_type get() noexcept {
			return (T::read() >> static_cast<typename T::value_type>(pos)) & ((1 << len) - 1);
		}

		static void set(typename T::value_type v) noexcept {
			auto m = static_cast<typename T::value_type>(((1 << len) - 1) << static_cast<typename T::value_type>(pos));
			T::write((T::read() & ~m) | (static_cast<typename T::value_type>(v) << static_cast<typename T::value_type>(pos)));
		}

	    static typename T::value_type b(typename T::value_type v) noexcept {
			return (((1 << len) - 1) & v) << static_cast<typename T::value_type>(pos);
		}

		void operator = (typename T::value_type v) noexcept { set(v); }

		auto operator () () noexcept { return get(); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Read ビット・アクセス・テンプレート
		@param[in]	T	アクセス・クラス
		@param[in]	pos	ビット位置
		@param[in]	len	ビット幅
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class T, bitpos pos>
	struct bit_ro_t {

		typedef T value_type;

		static constexpr auto POS = pos;
		static constexpr uint8_t LEN = 1;

		static bool get() noexcept {
			return (T::read() >> static_cast<typename T::value_type>(pos)) & 1;
		}

	    static typename T::value_type b() noexcept {
			return 1 << static_cast<typename T::value_type>(pos);
		}

		bool operator () () noexcept { return get(); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  Read ビット・アクセス・テンプレート
		@param[in]	T	アクセス・クラス
		@param[in]	pos	初期ビット位置
		@param[in]	len	ビット幅
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class T, bitpos pos, uint8_t len>
	struct bits_ro_t {

		typedef T value_type;

		static constexpr auto POS = pos;
		static constexpr auto LEN = len;

		static typename T::value_type get() noexcept {
			return (T::read() >> static_cast<typename T::value_type>(pos)) & ((1 << len) - 1);
		}

	    static typename T::value_type b(typename T::value_type v) noexcept {
			return (((1 << len) - 1) & v) << static_cast<typename T::value_type>(pos);
		}

		auto operator () () noexcept { return get(); }
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  標準バイト Read/Write アクセス・テンプレート @n
				ポートアクセス用
		@param[in]	T	アクセステンプレート
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class T>
	struct basic_rw_t : public T {

		typedef T value_type;

		using T::operator =;
		using T::operator ();
		using T::operator |=;
		using T::operator &=;

		typedef bit_rw_t<T, bitpos::B7> B7_;
		typedef bit_rw_t<T, bitpos::B6> B6_;
		typedef bit_rw_t<T, bitpos::B5> B5_;
		typedef bit_rw_t<T, bitpos::B4> B4_;
		typedef bit_rw_t<T, bitpos::B3> B3_;
		typedef bit_rw_t<T, bitpos::B2> B2_;
		typedef bit_rw_t<T, bitpos::B1> B1_;
		typedef bit_rw_t<T, bitpos::B0> B0_;
		static inline B7_ B7;	///< B7 アクセス
		static inline B6_ B6;	///< B6 アクセス
		static inline B5_ B5;	///< B5 アクセス
		static inline B4_ B4;	///< B4 アクセス
		static inline B3_ B3;	///< B3 アクセス
		static inline B2_ B2;	///< B2 アクセス
		static inline B1_ B1;	///< B1 アクセス
		static inline B0_ B0;	///< B0 アクセス
	};


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	/*!
		@brief  標準バイト Read アクセス・テンプレート @n
				ポートアクセス用
		@param[in]	T	アクセステンプレート
	*/
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
	template <class T>
	struct basic_ro_t : public T {

		typedef T value_type;

		using T::operator ();

		typedef bit_ro_t<T, bitpos::B7> B7_;
		typedef bit_ro_t<T, bitpos::B6> B6_;
		typedef bit_ro_t<T, bitpos::B5> B5_;
		typedef bit_ro_t<T, bitpos::B4> B4_;
		typedef bit_ro_t<T, bitpos::B3> B3_;
		typedef bit_ro_t<T, bitpos::B2> B2_;
		typedef bit_ro_t<T, bitpos::B1> B1_;
		typedef bit_ro_t<T, bitpos::B0> B0_;
		static inline B7_ B7;	///< B7 アクセス
		static inline B6_ B6;	///< B6 アクセス
		static inline B5_ B5;	///< B5 アクセス
		static inline B4_ B4;	///< B4 アクセス
		static inline B3_ B3;	///< B3 アクセス
		static inline B2_ B2;	///< B2 アクセス
		static inline B1_ B1;	///< B1 アクセス
		static inline B0_ B0;	///< B0 アクセス
	};
}
