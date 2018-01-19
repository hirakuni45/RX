#pragma once
//=====================================================================//
/*! @file
    @brief  アロケーター・クラス
	@copyright Copyright 2018 Kunihito Hiramatsu All Right Reserved.
    @author 平松邦仁 (hira@rvf-rc45.net)
*/
//=====================================================================//
#include <new>

template <class T>
struct allocator_map16 {
    // 要素の型
    using value_type = T;

    // 特殊関数
    // (デフォルトコンストラクタ、コピーコンストラクタ
    //  、ムーブコンストラクタ)
    allocator_map16() {}

    // 別な要素型のアロケータを受け取るコンストラクタ
    template <class U>
    allocator_map16(const allocator_map16<U>&) {}

    // メモリ確保
    T* allocate(std::size_t n)
    {
        return reinterpret_cast<T*>(std::malloc(sizeof(T) * n));
    }

    // メモリ解放
    void deallocate(T* p, std::size_t n)
    {
        static_cast<void>(n);
        std::free(p);
    }
};

// 比較演算子
template <class T, class U>
bool operator==(const allocator_map16<T>&, const allocator_map16<U>&)
{ return true; }

template <class T, class U>
bool operator!=(const allocator_map16<T>&, const allocator_map16<U>&)
{ return false; }
