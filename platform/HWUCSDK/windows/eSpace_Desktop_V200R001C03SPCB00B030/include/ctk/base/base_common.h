/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_COMMON_H_
#define _Z_CTK_BASE_COMMON_H_

#include "ctk/ctk_config.h"

#include <utility>

namespace ctk
{

    class CTK_API dumper;

    using std::swap;

    // 使用memcpy做任意类型的数据交换。
    // 不需要再自定义swap函数。
    //
    template<class T>
    inline void swap_(T& v1, T& v2)
    {
        char tmp[sizeof(T)];
        std::memcpy(tmp, &v1, sizeof(T));
        std::memcpy(&v1, &v2, sizeof(T));
        std::memcpy(&v2, tmp, sizeof(T));
    }

    // 对于基本类型，可以使用std::swap来交换值（赋值比memcpy快）。
    //
    inline void swap_(bool& _v1, bool& _v2) { std::swap(_v1, _v2); }
    inline void swap_(char& _v1, char& _v2) { std::swap(_v1, _v2); }
    inline void swap_(short& _v1, short& _v2) { std::swap(_v1, _v2); }
    inline void swap_(int& _v1, int& _v2) { std::swap(_v1, _v2); }
    inline void swap_(long& _v1, long& _v2) { std::swap(_v1, _v2); }
    inline void swap_(int64& _v1, int64& _v2) { std::swap(_v1, _v2); }
    inline void swap_(unsigned char& _v1, unsigned char& _v2) { std::swap(_v1, _v2); }
    inline void swap_(unsigned short& _v1, unsigned short& _v2) { std::swap(_v1, _v2); }
    inline void swap_(unsigned int& _v1, unsigned int& _v2) { std::swap(_v1, _v2); }
    inline void swap_(unsigned long& _v1, unsigned long& _v2) { std::swap(_v1, _v2); }
    inline void swap_(uint64& _v1, uint64& _v2) { std::swap(_v1, _v2); }
    inline void swap_(float& _v1, float& _v2) { std::swap(_v1, _v2); }
    inline void swap_(double& _v1, double& _v2) { std::swap(_v1, _v2); }
    template<class T>
    inline void swap_(T* &_v1, T* &_v2) { std::swap(_v1, _v2); }
    template<class T>
    inline void swap_(T const * &_v1, T const * &_v2) { std::swap(_v1, _v2); }

    template<class T>
    struct MemberTypeBase
    {
        typedef T type;
    };
    template<class T>
    struct MemberType : public MemberTypeBase<T>
    {
    };
    template<class T>
    struct MemberType<T&> : public MemberTypeBase<T>
    {
    };
    template<class T>
    struct MemberType<const T> : public MemberTypeBase<T>
    {
    };
    template<class T>
    struct MemberType<const T&> : public MemberTypeBase<T>
    {
    };
    template<class T>
    struct MemberType<volatile T> : public MemberTypeBase<T>
    {
    };
    template<class T>
    struct MemberType<volatile T&> : public MemberTypeBase<T>
    {
    };

} // namespace ctk

#endif //_Z_CTK_BASE_COMMON_H_

