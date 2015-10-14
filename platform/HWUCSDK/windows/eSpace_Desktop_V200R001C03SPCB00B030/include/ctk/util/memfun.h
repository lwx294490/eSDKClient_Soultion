/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_MEMFUN_H_
#define _Z_CTK_UTIL_MEMFUN_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include <functional>

#define CTK_STATIC_CHECK(expr, msg) do { char ERROR_##msg[expr!=0]; (void)ERROR_##msg; } while(0)

namespace ctk
{
    template<class T>
    struct ClassTypeBase
    {
        typedef T class_type;
        typedef class_type *ptr_to_class_type;
        typedef const class_type *const_ptr_to_class_type;
    };
    template<class T>
    struct ClassType : public ClassTypeBase<T>
    {
    };
    template<class T>
    struct ClassType<T*> : public ClassTypeBase<T>
    {
    };
    template<class T>
    struct ClassType<T&> : public ClassTypeBase<T>
    {
    };
    template<class T>
    struct ClassType<const T*> : public ClassTypeBase<T>
    {
    };
    template<class T>
    struct ClassType<const T&> : public ClassTypeBase<T>
    {
    };

    template<class R>
    struct Function_0
    {
        typedef R result_type;
    };
    template<class T, class R>
    struct MemFunction_0 : public ClassType<T>, public Function_0<R>
    {
    };

    template<class P1, class R>
    struct Function_1 : public Function_0<R>
    {
        typedef P1 param_type_1;
    };
    template<class T, class P1, class R>
    struct MemFunction_1 : public ClassType<T>, public Function_1<P1, R>
    {
    };

    template<class P1, class P2, class R>
    struct Function_2 : public Function_1<P1, R>
    {
        typedef P2 param_type_2;
    };
    template<class T, class P1, class P2, class R>
    struct MemFunction_2 : public ClassType<T>, public Function_2<P1, P2, R>
    {
    };

    template<class P1, class P2, class P3, class R>
    struct Function_3 : public Function_2<P1, P2, R>
    {
        typedef P3 param_type_3;
    };
    template<class T, class P1, class P2, class P3, class R>
    struct MemFunction_3 : public ClassType<T>, public Function_3<P1, P2, P3, R>
    {
    };

    template<class P1, class P2, class P3, class P4, class R>
    struct Function_4 : public Function_3<P1, P2, P3, R>
    {
        typedef P4 param_type_4;
    };
    template<class T, class P1, class P2, class P3, class P4, class R>
    struct MemFunction_4 : public ClassType<T>, public Function_4<P1, P2, P3, P4, R>
    {
    };

    template<class P1, class P2, class P3, class P4, class P5, class R>
    struct Function_5 : public Function_4<P1, P2, P3, P4, R>
    {
        typedef P5 param_type_5;
    };
    template<class T, class P1, class P2, class P3, class P4, class P5, class R>
    struct MemFunction_5 : public ClassType<T>, public Function_5<P1, P2, P3, P4, P5, R>
    {
    };

    template<class P1, class P2, class P3, class P4, class P5, class P6, class R>
    struct Function_6 : public Function_5<P1, P2, P3, P4, P5, R>
    {
        typedef P6 param_type_6;
    };
    template<class T, class P1, class P2, class P3, class P4, class P5, class P6, class R>
    struct MemFunction_6 : public ClassType<T>, public Function_6<P1, P2, P3, P4, P5, P6, R>
    {
    };

    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class R>
    struct Function_7 : public Function_6<P1, P2, P3, P4, P5, P6, R>
    {
        typedef P7 param_type_7;
    };
    template<class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class R>
    struct MemFunction_7 : public ClassType<T>, public Function_7<P1, P2, P3, P4, P5, P6, P7, R>
    {
    };

    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class R>
    struct Function_8 : public Function_7<P1, P2, P3, P4, P5, P6, P7, R>
    {
        typedef P8 param_type_8;
    };
    template<class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class R>
    struct MemFunction_8 : public ClassType<T>, public Function_8<P1, P2, P3, P4, P5, P6, P7, P8, R>
    {
    };

    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class R>
    struct Function_9 : public Function_8<P1, P2, P3, P4, P5, P6, P7, P8, R>
    {
        typedef P9 param_type_9;
    };
    template<class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class R>
    struct MemFunction_9 : public ClassType<T>, public Function_9<P1, P2, P3, P4, P5, P6, P7, P8, P9, R>
    {
    };

    ////////////////////////////////////////////////////////////////////
    //
    // 0 : 0 构造和执行都没有参数
    //
    ////////////////////////////////////////////////////////////////////

    template<class R>
    struct PtrFun0_0 : public Function_0<R>
        {
            typedef R (*_Func)();
            PtrFun0_0(_Func _fn)
                : fn_(_fn)
            {
            }
            R operator()() const
            {
                return (*fn_)();
            }
        private:
            _Func fn_;
        };
    template<class R>
        inline PtrFun0_0<R>
        ptr_fun(R (*_fn)())
    {
        return PtrFun0_0<R>(_fn);
    }

    template<class C, class R>
        struct MemFun0_0 : public MemFunction_0<C, R>
        {
            typedef MemFunction_0<C, R> _Base;
            typedef typename _Base::ptr_to_class_type _This;
            typedef R (C::*_Func)();
            MemFun0_0(_Func _fn, _This _this=0)
                : fn_(_fn), this_(_this)
            {
            }
            R operator()()
            {
                return (this_->*fn_)();
            }
            R operator()(_This _this)
            {
                return (_this->*fn_)();
            }
        private:
            _Func fn_;
            _This this_;
        };
    template<class C, class R>
        inline MemFun0_0<C, R>
        mem_fun(R (C::*_fn)())
    {
        return MemFun0_0<C, R>(_fn);
    }
    template<class C, class R, class T>
        inline MemFun0_0<C, R>
        mem_fun(T* _this, R (C::*_fn)())
    {
        return MemFun0_0<C, R>(_fn, _this);
    }

    template<class C, class R>
        struct ConstMemFun0_0 : public MemFunction_0<C, R>
        {
            typedef MemFunction_0<C, R> _Base;
            typedef typename _Base::const_ptr_to_class_type _This;
            typedef R (C::*_Func)() const;
            ConstMemFun0_0(_Func _fn, _This _this=0)
                : fn_(_fn), this_(_this)
            {
            }
            R operator()() const
            {
                return (this_->*fn_)();
            }
            R operator()(_This _this) const
            {
                return (_this->*fn_)();
            }
        private:
            _Func fn_;
            _This this_;
        };
    template<class C, class R>
        inline ConstMemFun0_0<C, R>
        mem_fun(R (C::*_fn)() const)
    {
        return ConstMemFun0_0<C, R>(_fn);
    }
    template<class C, class R, class T>
        inline ConstMemFun0_0<C, R>
        mem_fun(const T* _this, R (C::*_fn)() const)
    {
        return ConstMemFun0_0<C, R>(_fn, _this);
    }

    ////////////////////////////////////////////////////////////////////
    //
    // 0 : 1..N 参数在执行时提供（绑定this，函数对象可以象普通函数一样调用）
    //
    ////////////////////////////////////////////////////////////////////

    // 1 paratemer

    template<class P1, class R>
    struct PtrFun0_1 : public Function_1<P1, R>
        {
            typedef R (*_Func)(P1);
            PtrFun0_1(_Func _fn)
                : fn_(_fn)
            {
            }
            R operator()(P1 _p1) const
            {
                return (*fn_)(_p1);
            }
        private:
            _Func fn_;
        };
    template<class P1, class R>
        inline PtrFun0_1<P1, R>
        ptr_fun(R (*_fn)(P1))
    {
        return PtrFun0_1<P1, R>(_fn);
    }

    template<class C, class P1, class R>
    struct MemFun0_1 : public MemFunction_1<C, P1, R>
        {
            typedef MemFunction_1<C, P1, R> _Base;
            typedef typename _Base::ptr_to_class_type _This;
            typedef R (C::*_Func)(P1);
            MemFun0_1(_Func _fn, _This _this=0)
                : fn_(_fn), this_(_this)
            {
            }
            R operator()(P1 _p1) 
            {
                return (this_->*fn_)(_p1);
            }
            R operator()(_This _this, P1 _p1) 
            {
                return (_this->*fn_)(_p1);
            }
        private:
            _Func fn_;
            _This this_;
        };
    template<class P1, class C, class R>
        inline MemFun0_1<C, P1, R>
        mem_fun(R (C::*_fn)(P1))
    {
        return MemFun0_1<C, P1, R>(_fn);
    }
    template<class P1, class C, class R, class T>
        inline MemFun0_1<C, P1, R>
        mem_fun(T* _this, R (C::*_fn)(P1))
    {
        return MemFun0_1<C, P1, R>(_fn, _this);
    }

    template<class C, class P1, class R>
    struct ConstMemFun0_1 : public MemFunction_1<C, P1, R>
        {
            typedef MemFunction_1<C, P1, R> _Base;
            typedef typename _Base::const_ptr_to_class_type _This;
            typedef R (C::*_Func)(P1) const;
            ConstMemFun0_1(_Func _fn, _This _this=0)
                : fn_(_fn), this_(_this)
            {
            }
            R operator()(P1 _p1) const
            {
                return (this_->*fn_)(_p1);
            }
            R operator()(_This _this, P1 _p1) const
            {
                return (_this->*fn_)(_p1);
            }
        private:
            _Func fn_;
            _This this_;
        };
    template<class P1, class C, class R>
        inline ConstMemFun0_1<C, P1, R>
        mem_fun(R (C::*_fn)(P1) const)
    {
        return ConstMemFun0_1<C, P1, R>(_fn);
    }
    template<class P1, class C, class R, class T>
        inline ConstMemFun0_1<C, P1, R>
        mem_fun(const T* _this, R (C::*_fn)(P1) const)
    {
        return ConstMemFun0_1<C, P1, R>(_fn, _this);
    }

    // 2 paratemers

    template<class P1, class P2, class R>
    struct PtrFun0_2 : public Function_2<P1, P2, R>
        {
            typedef R (*_Func)(P1, P2);
            PtrFun0_2(_Func _fn)
                : fn_(_fn)
            {
            }
            R operator()(P1 _p1, P2 _p2) const
            {
                return (*fn_)(_p1, _p2);
            }
        private:
            _Func fn_;
        };
    template<class P1, class P2, class R>
        inline PtrFun0_2<P1, P2, R>
        ptr_fun(R (*_fn)(P1, P2))
    {
        return PtrFun0_2<P1, P2, R>(_fn);
    }

    template<class C, class P1, class P2, class R>
    struct MemFun0_2 : public MemFunction_2<C, P1, P2, R>
        {
            typedef MemFunction_2<C, P1, P2, R> _Base;
            typedef typename _Base::ptr_to_class_type _This;
            typedef R (C::*_Func)(P1, P2);
            MemFun0_2(_Func _fn, _This _this=0)
                : fn_(_fn), this_(_this)
            {
            }
            R operator()(P1 _p1, P2 _p2) 
            {
                return (this_->*fn_)(_p1, _p2);
            }
            R operator()(_This _this, P1 _p1, P2 _p2) 
            {
                return (_this->*fn_)(_p1, _p2);
            }
        private:
            _Func fn_;
            _This this_;
        };
    template<class P1, class P2, class C, class R>
        inline MemFun0_2<C, P1, P2, R>
        mem_fun(R (C::*_fn)(P1, P2))
    {
        return MemFun0_2<C, P1, P2, R>(_fn);
    }
    template<class P1, class P2, class C, class R, class T>
        inline MemFun0_2<C, P1, P2, R>
        mem_fun(T* _this, R (C::*_fn)(P1, P2))
    {
        return MemFun0_2<C, P1, P2, R>(_fn, _this);
    }

    template<class C, class P1, class P2, class R>
    struct ConstMemFun0_2 : public MemFunction_2<C, P1, P2, R>
        {
            typedef MemFunction_2<C, P1, P2, R> _Base;
            typedef typename _Base::const_ptr_to_class_type _This;
            typedef R (C::*_Func)(P1, P2) const;
            ConstMemFun0_2(_Func _fn, _This _this=0)
                : fn_(_fn), this_(_this)
            {
            }
            R operator()(P1 _p1, P2 _p2) const
            {
                return (this_->*fn_)(_p1, _p2);
            }
            R operator()(_This _this, P1 _p1, P2 _p2) const
            {
                return (_this->*fn_)(_p1, _p2);
            }
        private:
            _Func fn_;
            _This this_;
        };
    template<class P1, class P2, class C, class R>
        inline ConstMemFun0_2<C, P1, P2, R>
        mem_fun(R (C::*_fn)(P1, P2) const)
    {
        return ConstMemFun0_2<C, P1, P2, R>(_fn);
    }
    template<class P1, class P2, class C, class R, class T>
        inline ConstMemFun0_2<C, P1, P2, R>
        mem_fun(const T* _this, R (C::*_fn)(P1, P2) const)
    {
        return ConstMemFun0_2<C, P1, P2, R>(_fn, _this);
    }

    // 3 paratemers

    template<class P1, class P2, class P3, class R>
    struct PtrFun0_3 : public Function_3<P1, P2, P3, R>
        {
            typedef R (*_Func)(P1, P2, P3);
            PtrFun0_3(_Func _fn)
                : fn_(_fn)
            {
            }
            R operator()(P1 _p1, P2 _p2, P3 _p3) const
            {
                return (*fn_)(_p1, _p2, _p3);
            }
        private:
            _Func fn_;
        };
    template<class P1, class P2, class P3, class R>
        inline PtrFun0_3<P1, P2, P3, R>
        ptr_fun(R (*_fn)(P1, P2, P3))
    {
        return PtrFun0_3<P1, P2, P3, R>(_fn);
    }

    template<class C, class P1, class P2, class P3, class R>
    struct MemFun0_3 : public MemFunction_3<C, P1, P2, P3, R>
        {
            typedef MemFunction_3<C, P1, P2, P3, R> _Base;
            typedef typename _Base::ptr_to_class_type _This;
            typedef R (C::*_Func)(P1, P2, P3);
            MemFun0_3(_Func _fn, _This _this=0)
                : fn_(_fn), this_(_this)
            {
            }
            R operator()(P1 _p1, P2 _p2, P3 _p3) 
            {
                return (this_->*fn_)(_p1, _p2, _p3);
            }
            R operator()(_This _this, P1 _p1, P2 _p2, P3 _p3) 
            {
                return (_this->*fn_)(_p1, _p2, _p3);
            }
        private:
            _Func fn_;
            _This this_;
        };
    template<class P1, class P2, class P3, class C, class R>
        inline MemFun0_3<C, P1, P2, P3, R>
        mem_fun(R (C::*_fn)(P1, P2, P3))
    {
        return MemFun0_3<C, P1, P2, P3, R>(_fn);
    }
    template<class P1, class P2, class P3, class C, class R, class T>
        inline MemFun0_3<C, P1, P2, P3, R>
        mem_fun(T* _this, R (C::*_fn)(P1, P2, P3))
    {
        return MemFun0_3<C, P1, P2, P3, R>(_fn, _this);
    }

    template<class C, class P1, class P2, class P3, class R>
    struct ConstMemFun0_3 : public MemFunction_3<C, P1, P2, P3, R>
        {
            typedef MemFunction_3<C, P1, P2, P3, R> _Base;
            typedef typename _Base::const_ptr_to_class_type _This;
            typedef R (C::*_Func)(P1, P2, P3) const;
            ConstMemFun0_3(_Func _fn, _This _this=0)
                : fn_(_fn), this_(_this)
            {
            }
            R operator()(P1 _p1, P2 _p2, P3 _p3) const
            {
                return (this_->*fn_)(_p1, _p2, _p3);
            }
            R operator()(_This _this, P1 _p1, P2 _p2, P3 _p3) const
            {
                return (_this->*fn_)(_p1, _p2, _p3);
            }
        private:
            _Func fn_;
            _This this_;
        };
    template<class P1, class P2, class P3, class C, class R>
        inline ConstMemFun0_3<C, P1, P2, P3, R>
        mem_fun(R (C::*_fn)(P1, P2, P3) const)
    {
        return ConstMemFun0_3<C, P1, P2, P3, R>(_fn);
    }
    template<class P1, class P2, class P3, class C, class R, class T>
        inline ConstMemFun0_3<C, P1, P2, P3, R>
        mem_fun(const T* _this, R (C::*_fn)(P1, P2, P3) const)
    {
        return ConstMemFun0_3<C, P1, P2, P3, R>(_fn, _this);
    }

    // 4 paratemers

    template<class P1, class P2, class P3, class P4, class R>
    struct PtrFun0_4 : public Function_4<P1, P2, P3, P4, R>
        {
            typedef R (*_Func)(P1, P2, P3, P4);
            PtrFun0_4(_Func _fn)
                : fn_(_fn)
            {
            }
            R operator()(P1 _p1, P2 _p2, P3 _p3, P4 _p4) const
            {
                return (*fn_)(_p1, _p2, _p3, _p4);
            }
        private:
            _Func fn_;
        };
    template<class P1, class P2, class P3, class P4, class R>
        inline PtrFun0_4<P1, P2, P3, P4, R>
        ptr_fun(R (*_fn)(P1, P2, P3, P4))
    {
        return PtrFun0_4<P1, P2, P3, P4, R>(_fn);
    }

    template<class C, class P1, class P2, class P3, class P4, class R>
    struct MemFun0_4 : public MemFunction_4<C, P1, P2, P3, P4, R>
        {
            typedef MemFunction_4<C, P1, P2, P3, P4, R> _Base;
            typedef typename _Base::ptr_to_class_type _This;
            typedef R (C::*_Func)(P1, P2, P3, P4);
            MemFun0_4(_Func _fn, _This _this=0)
                : fn_(_fn), this_(_this)
            {
            }
            R operator()(P1 _p1, P2 _p2, P3 _p3, P4 _p4) 
            {
                return (this_->*fn_)(_p1, _p2, _p3, _p4);
            }
            R operator()(_This _this, P1 _p1, P2 _p2, P3 _p3, P4 _p4) 
            {
                return (_this->*fn_)(_p1, _p2, _p3, _p4);
            }
        private:
            _Func fn_;
            _This this_;
        };
    template<class P1, class P2, class P3, class P4, class C, class R>
        inline MemFun0_4<C, P1, P2, P3, P4, R>
        mem_fun(R (C::*_fn)(P1, P2, P3, P4))
    {
        return MemFun0_4<C, P1, P2, P3, P4, R>(_fn);
    }
    template<class P1, class P2, class P3, class P4, class C, class R, class T>
        inline MemFun0_4<C, P1, P2, P3, P4, R>
        mem_fun(T* _this, R (C::*_fn)(P1, P2, P3, P4))
    {
        return MemFun0_4<C, P1, P2, P3, P4, R>(_fn, _this);
    }

    template<class C, class P1, class P2, class P3, class P4, class R>
    struct ConstMemFun0_4 : public MemFunction_4<C, P1, P2, P3, P4, R>
        {
            typedef MemFunction_4<C, P1, P2, P3, P4, R> _Base;
            typedef typename _Base::const_ptr_to_class_type _This;
            typedef R (C::*_Func)(P1, P2, P3, P4) const;
            ConstMemFun0_4(_Func _fn, _This _this=0)
                : fn_(_fn), this_(_this)
            {
            }
            R operator()(P1 _p1, P2 _p2, P3 _p3, P4 _p4) const
            {
                return (this_->*fn_)(_p1, _p2, _p3, _p4);
            }
            R operator()(_This _this, P1 _p1, P2 _p2, P3 _p3, P4 _p4) const
            {
                return (_this->*fn_)(_p1, _p2, _p3, _p4);
            }
        private:
            _Func fn_;
            _This this_;
        };
    template<class P1, class P2, class P3, class P4, class C, class R>
        inline ConstMemFun0_4<C, P1, P2, P3, P4, R>
        mem_fun(R (C::*_fn)(P1, P2, P3, P4) const)
    {
        return ConstMemFun0_4<C, P1, P2, P3, P4, R>(_fn);
    }
    template<class P1, class P2, class P3, class P4, class C, class R, class T>
        inline ConstMemFun0_4<C, P1, P2, P3, P4, R>
        mem_fun(const T* _this, R (C::*_fn)(P1, P2, P3, P4) const)
    {
        return ConstMemFun0_4<C, P1, P2, P3, P4, R>(_fn, _this);
    }

    // 5 paratemers

    template<class P1, class P2, class P3, class P4, class P5, class R>
    struct PtrFun0_5 : public Function_5<P1, P2, P3, P4, P5, R>
        {
            typedef R (*_Func)(P1, P2, P3, P4, P5);
            PtrFun0_5(_Func _fn)
                : fn_(_fn)
            {
            }
            R operator()(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5) const
            {
                return (*fn_)(_p1, _p2, _p3, _p4, _p5);
            }
        private:
            _Func fn_;
        };
    template<class P1, class P2, class P3, class P4, class P5, class R>
        inline PtrFun0_5<P1, P2, P3, P4, P5, R>
        ptr_fun(R (*_fn)(P1, P2, P3, P4, P5))
    {
        return PtrFun0_5<P1, P2, P3, P4, P5, R>(_fn);
    }

    template<class C, class P1, class P2, class P3, class P4, class P5, class R>
    struct MemFun0_5 : public MemFunction_5<C, P1, P2, P3, P4, P5, R>
        {
            typedef MemFunction_5<C, P1, P2, P3, P4, P5, R> _Base;
            typedef typename _Base::ptr_to_class_type _This;
            typedef R (C::*_Func)(P1, P2, P3, P4, P5);
            MemFun0_5(_Func _fn, _This _this=0)
                : fn_(_fn), this_(_this)
            {
            }
            R operator()(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5) 
            {
                return (this_->*fn_)(_p1, _p2, _p3, _p4, _p5);
            }
            R operator()(_This _this, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5) 
            {
                return (_this->*fn_)(_p1, _p2, _p3, _p4, _p5);
            }
        private:
            _Func fn_;
            _This this_;
        };
    template<class P1, class P2, class P3, class P4, class P5, class C, class R>
        inline MemFun0_5<C, P1, P2, P3, P4, P5, R>
        mem_fun(R (C::*_fn)(P1, P2, P3, P4, P5))
    {
        return MemFun0_5<C, P1, P2, P3, P4, P5, R>(_fn);
    }
    template<class P1, class P2, class P3, class P4, class P5, class C, class R, class T>
        inline MemFun0_5<C, P1, P2, P3, P4, P5, R>
        mem_fun(T* _this, R (C::*_fn)(P1, P2, P3, P4, P5))
    {
        return MemFun0_5<C, P1, P2, P3, P4, P5, R>(_fn, _this);
    }

    template<class C, class P1, class P2, class P3, class P4, class P5, class R>
    struct ConstMemFun0_5 : public MemFunction_5<C, P1, P2, P3, P4, P5, R>
        {
            typedef MemFunction_5<C, P1, P2, P3, P4, P5, R> _Base;
            typedef typename _Base::const_ptr_to_class_type _This;
            typedef R (C::*_Func)(P1, P2, P3, P4, P5) const;
            ConstMemFun0_5(_Func _fn, _This _this=0)
                : fn_(_fn), this_(_this)
            {
            }
            R operator()(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5) const
            {
                return (this_->*fn_)(_p1, _p2, _p3, _p4, _p5);
            }
            R operator()(_This _this, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5) const
            {
                return (_this->*fn_)(_p1, _p2, _p3, _p4, _p5);
            }
        private:
            _Func fn_;
            _This this_;
        };
    template<class P1, class P2, class P3, class P4, class P5, class C, class R>
        inline ConstMemFun0_5<C, P1, P2, P3, P4, P5, R>
        mem_fun(R (C::*_fn)(P1, P2, P3, P4, P5) const)
    {
        return ConstMemFun0_5<C, P1, P2, P3, P4, P5, R>(_fn);
    }
    template<class P1, class P2, class P3, class P4, class P5, class C, class R, class T>
        inline ConstMemFun0_5<C, P1, P2, P3, P4, P5, R>
        mem_fun(const T* _this, R (C::*_fn)(P1, P2, P3, P4, P5) const)
    {
        return ConstMemFun0_5<C, P1, P2, P3, P4, P5, R>(_fn, _this);
    }

    // 6 paratemers

    template<class P1, class P2, class P3, class P4, class P5, class P6, class R>
    struct PtrFun0_6 : public Function_6<P1, P2, P3, P4, P5, P6, R>
        {
            typedef R (*_Func)(P1, P2, P3, P4, P5, P6);
            PtrFun0_6(_Func _fn)
                : fn_(_fn)
            {
            }
            R operator()(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6) const
            {
                return (*fn_)(_p1, _p2, _p3, _p4, _p5, _p6);
            }
        private:
            _Func fn_;
        };
    template<class P1, class P2, class P3, class P4, class P5, class P6, class R>
        inline PtrFun0_6<P1, P2, P3, P4, P5, P6, R>
        ptr_fun(R (*_fn)(P1, P2, P3, P4, P5, P6))
    {
        return PtrFun0_6<P1, P2, P3, P4, P5, P6, R>(_fn);
    }

    template<class C, class P1, class P2, class P3, class P4, class P5, class P6, class R>
    struct MemFun0_6 : public MemFunction_6<C, P1, P2, P3, P4, P5, P6, R>
        {
            typedef MemFunction_6<C, P1, P2, P3, P4, P5, P6, R> _Base;
            typedef typename _Base::ptr_to_class_type _This;
            typedef R (C::*_Func)(P1, P2, P3, P4, P5, P6);
            MemFun0_6(_Func _fn, _This _this=0)
                : fn_(_fn), this_(_this)
            {
            }
            R operator()(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6) 
            {
                return (this_->*fn_)(_p1, _p2, _p3, _p4, _p5, _p6);
            }
            R operator()(_This _this, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6) 
            {
                return (_this->*fn_)(_p1, _p2, _p3, _p4, _p5, _p6);
            }
        private:
            _Func fn_;
            _This this_;
        };
    template<class P1, class P2, class P3, class P4, class P5, class P6, class C, class R>
        inline MemFun0_6<C, P1, P2, P3, P4, P5, P6, R>
        mem_fun(R (C::*_fn)(P1, P2, P3, P4, P5, P6))
    {
        return MemFun0_6<C, P1, P2, P3, P4, P5, P6, R>(_fn);
    }
    template<class P1, class P2, class P3, class P4, class P5, class P6, class C, class R, class T>
        inline MemFun0_6<C, P1, P2, P3, P4, P5, P6, R>
        mem_fun(T* _this, R (C::*_fn)(P1, P2, P3, P4, P5, P6))
    {
        return MemFun0_6<C, P1, P2, P3, P4, P5, P6, R>(_fn, _this);
    }

    template<class C, class P1, class P2, class P3, class P4, class P5, class P6, class R>
    struct ConstMemFun0_6 : public MemFunction_6<C, P1, P2, P3, P4, P5, P6, R>
        {
            typedef MemFunction_6<C, P1, P2, P3, P4, P5, P6, R> _Base;
            typedef typename _Base::const_ptr_to_class_type _This;
            typedef R (C::*_Func)(P1, P2, P3, P4, P5, P6) const;
            ConstMemFun0_6(_Func _fn, _This _this=0)
                : fn_(_fn), this_(_this)
            {
            }
            R operator()(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6) const
            {
                return (this_->*fn_)(_p1, _p2, _p3, _p4, _p5, _p6);
            }
            R operator()(_This _this, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6) const
            {
                return (_this->*fn_)(_p1, _p2, _p3, _p4, _p5, _p6);
            }
        private:
            _Func fn_;
            _This this_;
        };
    template<class P1, class P2, class P3, class P4, class P5, class P6, class C, class R>
        inline ConstMemFun0_6<C, P1, P2, P3, P4, P5, P6, R>
        mem_fun(R (C::*_fn)(P1, P2, P3, P4, P5, P6) const)
    {
        return ConstMemFun0_6<C, P1, P2, P3, P4, P5, P6, R>(_fn);
    }
    template<class P1, class P2, class P3, class P4, class P5, class P6, class C, class R, class T>
        inline ConstMemFun0_6<C, P1, P2, P3, P4, P5, P6, R>
        mem_fun(const T* _this, R (C::*_fn)(P1, P2, P3, P4, P5, P6) const)
    {
        return ConstMemFun0_6<C, P1, P2, P3, P4, P5, P6, R>(_fn, _this);
    }

    // 7 paratemers

    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class R>
    struct PtrFun0_7 : public Function_7<P1, P2, P3, P4, P5, P6, P7, R>
    {
        typedef R (*_Func)(P1, P2, P3, P4, P5, P6, P7);
        PtrFun0_7(_Func _fn)
            : fn_(_fn)
        {
        }
        R operator()(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7) const
        {
            return (*fn_)(_p1, _p2, _p3, _p4, _p5, _p6, _p7);
        }
    private:
        _Func fn_;
    };
    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class R>
        inline PtrFun0_7<P1, P2, P3, P4, P5, P6, P7, R>
        ptr_fun(R (*_fn)(P1, P2, P3, P4, P5, P6, P7))
    {
        return PtrFun0_7<P1, P2, P3, P4, P5, P6, P7, R>(_fn);
    }

    template<class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class R>
    struct MemFun0_7 : public MemFunction_7<C, P1, P2, P3, P4, P5, P6, P7, R>
    {
        typedef MemFunction_7<C, P1, P2, P3, P4, P5, P6, P7, R> _Base;
        typedef typename _Base::ptr_to_class_type _This;
        typedef R (C::*_Func)(P1, P2, P3, P4, P5, P6, P7);
        MemFun0_7(_Func _fn, _This _this=0)
            : fn_(_fn), this_(_this)
        {
        }
        R operator()(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7) 
        {
            return (this_->*fn_)(_p1, _p2, _p3, _p4, _p5, _p6, _p7);
        }
        R operator()(_This _this, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7) 
        {
            return (_this->*fn_)(_p1, _p2, _p3, _p4, _p5, _p6, _p7);
        }
    private:
        _Func fn_;
        _This this_;
    };
    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class C, class R>
        inline MemFun0_7<C, P1, P2, P3, P4, P5, P6, P7, R>
        mem_fun(R (C::*_fn)(P1, P2, P3, P4, P5, P6, P7))
    {
        return MemFun0_7<C, P1, P2, P3, P4, P5, P6, P7, R>(_fn);
    }
    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class C, class R, class T>
        inline MemFun0_7<C, P1, P2, P3, P4, P5, P6, P7, R>
        mem_fun(T* _this, R (C::*_fn)(P1, P2, P3, P4, P5, P6, P7))
    {
        return MemFun0_7<C, P1, P2, P3, P4, P5, P6, P7, R>(_fn, _this);
    }

    template<class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class R>
    struct ConstMemFun0_7 : public MemFunction_7<C, P1, P2, P3, P4, P5, P6, P7, R>
    {
        typedef MemFunction_7<C, P1, P2, P3, P4, P5, P6, P7, R> _Base;
        typedef typename _Base::const_ptr_to_class_type _This;
        typedef R (C::*_Func)(P1, P2, P3, P4, P5, P6, P7) const;
        ConstMemFun0_7(_Func _fn, _This _this=0)
            : fn_(_fn), this_(_this)
        {
        }
        R operator()(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7) const
        {
            return (this_->*fn_)(_p1, _p2, _p3, _p4, _p5, _p6, _p7);
        }
        R operator()(_This _this, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7) const
        {
            return (_this->*fn_)(_p1, _p2, _p3, _p4, _p5, _p6, _p7);
        }
    private:
        _Func fn_;
        _This this_;
    };
    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class C, class R>
        inline ConstMemFun0_7<C, P1, P2, P3, P4, P5, P6, P7, R>
        mem_fun(R (C::*_fn)(P1, P2, P3, P4, P5, P6, P7) const)
    {
        return ConstMemFun0_7<C, P1, P2, P3, P4, P5, P6, P7, R>(_fn);
    }
    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class C, class R, class T>
        inline ConstMemFun0_7<C, P1, P2, P3, P4, P5, P6, P7, R>
        mem_fun(const T* _this, R (C::*_fn)(P1, P2, P3, P4, P5, P6, P7) const)
    {
        return ConstMemFun0_7<C, P1, P2, P3, P4, P5, P6, P7, R>(_fn, _this);
    }

    // 8 paratemers

    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class R>
    struct PtrFun0_8 : public Function_8<P1, P2, P3, P4, P5, P6, P7, P8, R>
    {
        typedef R (*_Func)(P1, P2, P3, P4, P5, P6, P7, P8);
        PtrFun0_8(_Func _fn)
            : fn_(_fn)
        {
        }
        R operator()(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8) const
        {
            return (*fn_)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8);
        }
    private:
        _Func fn_;
    };
    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class R>
        inline PtrFun0_8<P1, P2, P3, P4, P5, P6, P7, P8, R>
        ptr_fun(R (*_fn)(P1, P2, P3, P4, P5, P6, P7, P8))
    {
        return PtrFun0_8<P1, P2, P3, P4, P5, P6, P7, P8, R>(_fn);
    }

    template<class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class R>
    struct MemFun0_8 : public MemFunction_8<C, P1, P2, P3, P4, P5, P6, P7, P8, R>
    {
        typedef MemFunction_8<C, P1, P2, P3, P4, P5, P6, P7, P8, R> _Base;
        typedef typename _Base::ptr_to_class_type _This;
        typedef R (C::*_Func)(P1, P2, P3, P4, P5, P6, P7, P8);
        MemFun0_8(_Func _fn, _This _this=0)
            : fn_(_fn), this_(_this)
        {
        }
        R operator()(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8) 
        {
            return (this_->*fn_)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8);
        }
        R operator()(_This _this, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8) 
        {
            return (_this->*fn_)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8);
        }
    private:
        _Func fn_;
        _This this_;
    };
    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class C, class R>
        inline MemFun0_8<C, P1, P2, P3, P4, P5, P6, P7, P8, R>
        mem_fun(R (C::*_fn)(P1, P2, P3, P4, P5, P6, P7, P8))
    {
        return MemFun0_8<C, P1, P2, P3, P4, P5, P6, P7, P8, R>(_fn);
    }
    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class C, class R, class T>
        inline MemFun0_8<C, P1, P2, P3, P4, P5, P6, P7, P8, R>
        mem_fun(T* _this, R (C::*_fn)(P1, P2, P3, P4, P5, P6, P7, P8))
    {
        return MemFun0_8<C, P1, P2, P3, P4, P5, P6, P7, P8, R>(_fn, _this);
    }

    template<class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class R>
    struct ConstMemFun0_8 : public MemFunction_8<C, P1, P2, P3, P4, P5, P6, P7, P8, R>
    {
        typedef MemFunction_8<C, P1, P2, P3, P4, P5, P6, P7, P8, R> _Base;
        typedef typename _Base::const_ptr_to_class_type _This;
        typedef R (C::*_Func)(P1, P2, P3, P4, P5, P6, P7, P8) const;
        ConstMemFun0_8(_Func _fn, _This _this=0)
            : fn_(_fn), this_(_this)
        {
        }
        R operator()(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8) const
        {
            return (this_->*fn_)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8);
        }
        R operator()(_This _this, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8) const
        {
            return (_this->*fn_)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8);
        }
    private:
        _Func fn_;
        _This this_;
    };
    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class C, class R>
        inline ConstMemFun0_8<C, P1, P2, P3, P4, P5, P6, P7, P8, R>
        mem_fun(R (C::*_fn)(P1, P2, P3, P4, P5, P6, P7, P8) const)
    {
        return ConstMemFun0_8<C, P1, P2, P3, P4, P5, P6, P7, P8, R>(_fn);
    }
    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class C, class R, class T>
        inline ConstMemFun0_8<C, P1, P2, P3, P4, P5, P6, P7, P8, R>
        mem_fun(const T* _this, R (C::*_fn)(P1, P2, P3, P4, P5, P6, P7, P8) const)
    {
        return ConstMemFun0_8<C, P1, P2, P3, P4, P5, P6, P7, P8, R>(_fn, _this);
    }

    // 9 paratemers

    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class R>
    struct PtrFun0_9 : public Function_9<P1, P2, P3, P4, P5, P6, P7, P8, P9, R>
    {
        typedef R (*_Func)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
        PtrFun0_9(_Func _fn)
            : fn_(_fn)
        {
        }
        R operator()(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9) const
        {
            return (*fn_)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9);
        }
    private:
        _Func fn_;
    };
    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class R>
        inline PtrFun0_9<P1, P2, P3, P4, P5, P6, P7, P8, P9, R>
        ptr_fun(R (*_fn)(P1, P2, P3, P4, P5, P6, P7, P8, P9))
    {
        return PtrFun0_9<P1, P2, P3, P4, P5, P6, P7, P8, P9, R>(_fn);
    }

    template<class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class R>
    struct MemFun0_9 : public MemFunction_9<C, P1, P2, P3, P4, P5, P6, P7, P8, P9, R>
    {
        typedef MemFunction_9<C, P1, P2, P3, P4, P5, P6, P7, P8, P9, R> _Base;
        typedef typename _Base::ptr_to_class_type _This;
        typedef R (C::*_Func)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
        MemFun0_9(_Func _fn, _This _this=0)
            : fn_(_fn), this_(_this)
        {
        }
        R operator()(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9) 
        {
            return (this_->*fn_)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9);
        }
        R operator()(_This _this, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9) 
        {
            return (_this->*fn_)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9);
        }
    private:
        _Func fn_;
        _This this_;
    };
    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class C, class R>
        inline MemFun0_9<C, P1, P2, P3, P4, P5, P6, P7, P8, P9, R>
        mem_fun(R (C::*_fn)(P1, P2, P3, P4, P5, P6, P7, P8, P9))
    {
        return MemFun0_9<C, P1, P2, P3, P4, P5, P6, P7, P8, P9, R>(_fn);
    }
    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class C, class R, class T>
        inline MemFun0_9<C, P1, P2, P3, P4, P5, P6, P7, P8, P9, R>
        mem_fun(T* _this, R (C::*_fn)(P1, P2, P3, P4, P5, P6, P7, P8, P9))
    {
        return MemFun0_9<C, P1, P2, P3, P4, P5, P6, P7, P8, P9, R>(_fn, _this);
    }

    template<class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class R>
    struct ConstMemFun0_9 : public MemFunction_9<C, P1, P2, P3, P4, P5, P6, P7, P8, P9, R>
    {
        typedef MemFunction_9<C, P1, P2, P3, P4, P5, P6, P7, P8, P9, R> _Base;
        typedef typename _Base::const_ptr_to_class_type _This;
        typedef R (C::*_Func)(P1, P2, P3, P4, P5, P6, P7, P8, P9) const;
        ConstMemFun0_9(_Func _fn, _This _this=0)
            : fn_(_fn), this_(_this)
        {
        }
        R operator()(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9) const
        {
            return (this_->*fn_)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9);
        }
        R operator()(_This _this, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9) const
        {
            return (_this->*fn_)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9);
        }
    private:
        _Func fn_;
        _This this_;
    };
    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class C, class R>
        inline ConstMemFun0_9<C, P1, P2, P3, P4, P5, P6, P7, P8, P9, R>
        mem_fun(R (C::*_fn)(P1, P2, P3, P4, P5, P6, P7, P8, P9) const)
    {
        return ConstMemFun0_9<C, P1, P2, P3, P4, P5, P6, P7, P8, P9, R>(_fn);
    }
    template<class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class C, class R, class T>
        inline ConstMemFun0_9<C, P1, P2, P3, P4, P5, P6, P7, P8, P9, R>
        mem_fun(const T* _this, R (C::*_fn)(P1, P2, P3, P4, P5, P6, P7, P8, P9) const)
    {
        return ConstMemFun0_9<C, P1, P2, P3, P4, P5, P6, P7, P8, P9, R>(_fn, _this);
    }

    ////////////////////////////////////////////////////////////////////
    //
    // 1..N : 0 执行时无参数，构造时提供所有参数
    //
    ////////////////////////////////////////////////////////////////////

    template<class Fo>
        struct Fun0_0
            : public Function_0<typename Fo::result_type>
        {
            typedef typename Fo::result_type _Result;
            Fun0_0(Fo _fo)
                : fo_(_fo)
            {
            }
            _Result operator()()
            {
                return fo_();
            }
            _Result operator()() const
            {
                return fo_();
            }
        private:
            Fo fo_;
        };
    template<class R>
        inline Fun0_0<PtrFun0_0<R> >
        bind_all(R (*_fn)())
    {
        return Fun0_0<PtrFun0_0<R> >(ptr_fun(_fn));
    }
    template<class T, class R
           , class S>
        inline Fun0_0<MemFun0_0<T, R> >
        bind_all(S* _this, R (T::*_mfn)())
    {
        return Fun0_0<MemFun0_0<T, R> >(mem_fun(_this, _mfn));
    }
    template<class T, class R
           , class S>
        inline Fun0_0<ConstMemFun0_0<T, R> >
        bind_all(const S* _this, R (T::*_cmfn)() const)
    {
        return Fun0_0<ConstMemFun0_0<T, R> >(mem_fun(_this, _cmfn));
    }
    //template<class Fo>
    //    inline Fun0_0<Fo>
    //    bind_all(Fo _fo)
    //{
    //    return Fun0_0<Fo>(_fo);
    //}

    template<class Fo, class P1>
        struct Fun1_0
            : public Function_0<typename Fo::result_type>
        {
            typedef typename Fo::result_type _Result;
            Fun1_0(Fo _fo, P1 _p1)
                : fo_(_fo), p1_(_p1)
            {
            }
            _Result operator()() 
            {
                return fo_(p1_);
            }
            _Result operator()() const
            {
                return fo_(p1_);
            }
        private:
            Fo fo_;
            typename MemberType<P1>::type p1_;
        };
    template<class Q1, class R
           , class P1>
        inline Fun1_0<PtrFun0_1<Q1, R>, P1>
        bind_all(R (*_fn)(Q1), P1 _p1)
    {
        return Fun1_0<PtrFun0_1<Q1, R>, P1>(ptr_fun(_fn), _p1);
    }
    template<class Q1, class T, class R
           , class P1, class S>
        inline Fun1_0<MemFun0_1<T, Q1, R>, P1>
        bind_all(S* _this, R (T::*_mfn)(Q1), P1 _p1)
    {
        return Fun1_0<MemFun0_1<T, Q1, R>, P1>(mem_fun(_this, _mfn), _p1);
    }
    template<class Q1, class T, class R
           , class P1, class S>
        inline Fun1_0<ConstMemFun0_1<T, Q1, R>, P1>
        bind_all(const S* _this, R (T::*_cmfn)(Q1) const, P1 _p1)
    {
        return Fun1_0<ConstMemFun0_1<T, Q1, R>, P1>(mem_fun(_this, _cmfn), _p1);
    }
    //template<class Fo, class P1>
    //    inline Fun1_0<Fo, P1>
    //    bind_all(Fo _fo, P1 _p1)
    //{
    //    return Fun1_0<Fo, P1>(_fo, _p1);
    //}

    template<class Fo, class P1, class P2>
        struct Fun2_0
            : public Function_0<typename Fo::result_type>
        {
            typedef typename Fo::result_type _Result;
            Fun2_0(Fo _fo, P1 _p1, P2 _p2)
                : fo_(_fo), p1_(_p1), p2_(_p2)
            {
            }
            _Result operator()() 
            {
                return fo_(p1_, p2_);
            }
            _Result operator()() const
            {
                return fo_(p1_, p2_);
            }
        private:
            Fo fo_;
            typename MemberType<P1>::type p1_;
            typename MemberType<P2>::type p2_;
        };
    template<class Q1, class Q2, class R
           , class P1, class P2>
        inline Fun2_0<PtrFun0_2<Q1, Q2, R>, P1, P2>
        bind_all(R (*_fn)(Q1, Q2), P1 _p1, P2 _p2)
    {
        return Fun2_0<PtrFun0_2<Q1, Q2, R>, P1, P2>(ptr_fun(_fn), _p1, _p2);
    }
    template<class Q1, class Q2, class T, class R
           , class P1, class P2, class S>
        inline Fun2_0<MemFun0_2<T, Q1, Q2, R>, P1, P2>
        bind_all(S* _this, R (T::*_mfn)(Q1, Q2), P1 _p1, P2 _p2)
    {
        return Fun2_0<MemFun0_2<T, Q1, Q2, R>, P1, P2>(mem_fun(_this, _mfn), _p1, _p2);
    }
    template<class Q1, class Q2, class T, class R
           , class P1, class P2, class S>
        inline Fun2_0<ConstMemFun0_2<T, Q1, Q2, R>, P1, P2>
        bind_all(const S* _this, R (T::*_cmfn)(Q1, Q2) const, P1 _p1, P2 _p2)
    {
        return Fun2_0<ConstMemFun0_2<T, Q1, Q2, R>, P1, P2>(mem_fun(_this, _cmfn), _p1, _p2);
    }
    //template<class Fo, class P1, class P2>
    //    inline Fun2_0<Fo, P1, P2>
    //    bind_all(Fo _fo, P1 _p1, P2 _p2)
    //{
    //    return Fun2_0<Fo, P1, P2>(_fo, _p1, _p2);
    //}

    template<class Fo, class P1, class P2, class P3>
        struct Fun3_0
            : public Function_0<typename Fo::result_type>
        {
            typedef typename Fo::result_type _Result;
            Fun3_0(Fo _fo, P1 _p1, P2 _p2, P3 _p3)
                : fo_(_fo), p1_(_p1), p2_(_p2), p3_(_p3)
            {
            }
            _Result operator()()
            {
                return fo_(p1_, p2_, p3_);
            }
            _Result operator()() const
            {
                return fo_(p1_, p2_, p3_);
            }
        private:
            Fo fo_;
            typename MemberType<P1>::type p1_;
            typename MemberType<P2>::type p2_;
            typename MemberType<P3>::type p3_;
        };
    template<class Q1, class Q2, class Q3, class R
           , class P1, class P2, class P3>
        inline Fun3_0<PtrFun0_3<Q1, Q2, Q3, R>, P1, P2, P3>
        bind_all(R (*_fn)(Q1, Q2, Q3), P1 _p1, P2 _p2, P3 _p3)
    {
        return Fun3_0<PtrFun0_3<Q1, Q2, Q3, R>, P1, P2, P3>(ptr_fun(_fn), _p1, _p2, _p3);
    }
    template<class Q1, class Q2, class Q3, class T, class R
           , class P1, class P2, class P3, class S>
        inline Fun3_0<MemFun0_3<T, Q1, Q2, Q3, R>, P1, P2, P3>
        bind_all(S* _this, R (T::*_mfn)(Q1, Q2, Q3), P1 _p1, P2 _p2, P3 _p3)
    {
        return Fun3_0<MemFun0_3<T, Q1, Q2, Q3, R>, P1, P2, P3>(mem_fun(_this, _mfn), _p1, _p2, _p3);
    }
    template<class Q1, class Q2, class Q3, class T, class R
           , class P1, class P2, class P3, class S>
        inline Fun3_0<ConstMemFun0_3<T, Q1, Q2, Q3, R>, P1, P2, P3>
        bind_all(const S* _this, R (T::*_cmfn)(Q1, Q2, Q3) const, P1 _p1, P2 _p2, P3 _p3)
    {
        return Fun3_0<ConstMemFun0_3<T, Q1, Q2, Q3, R>, P1, P2, P3>(mem_fun(_this, _cmfn), _p1, _p2, _p3);
    }
    //template<class Fo, class P1, class P2, class P3>
    //    inline Fun3_0<Fo, P1, P2, P3>
    //    bind_all(Fo _fo, P1 _p1, P2 _p2, P3 _p3)
    //{
    //    return Fun3_0<Fo, P1, P2, P3>(_fo, _p1, _p2, _p3);
    //}

    template<class Fo, class P1, class P2, class P3, class P4>
        struct Fun4_0
            : public Function_0<typename Fo::result_type>
        {
            typedef typename Fo::result_type _Result;
            Fun4_0(Fo _fo, P1 _p1, P2 _p2, P3 _p3, P4 _p4)
                : fo_(_fo), p1_(_p1), p2_(_p2), p3_(_p3), p4_(_p4)
            {
            }
            _Result operator()() 
            {
                return fo_(p1_, p2_, p3_, p4_);
            }
            _Result operator()() const
            {
                return fo_(p1_, p2_, p3_, p4_);
            }
        private:
            Fo fo_;
            typename MemberType<P1>::type p1_;
            typename MemberType<P2>::type p2_;
            typename MemberType<P3>::type p3_;
            typename MemberType<P4>::type p4_;
        };
    template<class Q1, class Q2, class Q3, class Q4, class R
           , class P1, class P2, class P3, class P4>
        inline Fun4_0<PtrFun0_4<Q1, Q2, Q3, Q4, R>, P1, P2, P3, P4>
        bind_all(R (*_fn)(Q1, Q2, Q3, Q4), P1 _p1, P2 _p2, P3 _p3, P4 _p4)
    {
        return Fun4_0<PtrFun0_4<Q1, Q2, Q3, Q4, R>, P1, P2, P3, P4>(ptr_fun(_fn), _p1, _p2, _p3, _p4);
    }
    template<class Q1, class Q2, class Q3, class Q4, class T, class R
           , class P1, class P2, class P3, class P4, class S>
        inline Fun4_0<MemFun0_4<T, Q1, Q2, Q3, Q4, R>, P1, P2, P3, P4>
        bind_all(S* _this, R (T::*_mfn)(Q1, Q2, Q3, Q4), P1 _p1, P2 _p2, P3 _p3, P4 _p4)
    {
        return Fun4_0<MemFun0_4<T, Q1, Q2, Q3, Q4, R>, P1, P2, P3, P4>(mem_fun(_this, _mfn), _p1, _p2, _p3, _p4);
    }
    template<class Q1, class Q2, class Q3, class Q4, class T, class R
           , class P1, class P2, class P3, class P4, class S>
        inline Fun4_0<ConstMemFun0_4<T, Q1, Q2, Q3, Q4, R>, P1, P2, P3, P4>
        bind_all(const S* _this, R (T::*_cmfn)(Q1, Q2, Q3, Q4) const, P1 _p1, P2 _p2, P3 _p3, P4 _p4)
    {
        return Fun4_0<ConstMemFun0_4<T, Q1, Q2, Q3, Q4, R>, P1, P2, P3, P4>(mem_fun(_this, _cmfn), _p1, _p2, _p3, _p4);
    }
    //template<class Fo, class P1, class P2, class P3, class P4>
    //    inline Fun4_0<Fo, P1, P2, P3, P4>
    //    bind_all(Fo _fo, P1 _p1, P2 _p2, P3 _p3, P4 _p4)
    //{
    //    return Fun4_0<Fo, P1, P2, P3, P4>(_fo, _p1, _p2, _p3, _p4);
    //}

    template<class Fo, class P1, class P2, class P3, class P4, class P5>
        struct Fun5_0
            : public Function_0<typename Fo::result_type>
        {
            typedef typename Fo::result_type _Result;
            Fun5_0(Fo _fo, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5)
                : fo_(_fo), p1_(_p1), p2_(_p2), p3_(_p3), p4_(_p4), p5_(_p5)
            {
            }
            _Result operator()()
            {
                return fo_(p1_, p2_, p3_, p4_, p5_);
            }
            _Result operator()() const
            {
                return fo_(p1_, p2_, p3_, p4_, p5_);
            }
        private:
            Fo fo_;
            typename MemberType<P1>::type p1_;
            typename MemberType<P2>::type p2_;
            typename MemberType<P3>::type p3_;
            typename MemberType<P4>::type p4_;
            typename MemberType<P5>::type p5_;
        };
    template<class Q1, class Q2, class Q3, class Q4, class Q5, class R
           , class P1, class P2, class P3, class P4, class P5>
        inline Fun5_0<PtrFun0_5<Q1, Q2, Q3, Q4, Q5, R>, P1, P2, P3, P4, P5>
        bind_all(R (*_fn)(Q1, Q2, Q3, Q4, Q5), P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5)
    {
        return Fun5_0<PtrFun0_5<Q1, Q2, Q3, Q4, Q5, R>, P1, P2, P3, P4, P5>(
            ptr_fun(_fn), _p1, _p2, _p3, _p4, _p5);
    }
    template<class Q1, class Q2, class Q3, class Q4, class Q5, class T, class R
           , class P1, class P2, class P3, class P4, class P5, class S>
        inline Fun5_0<MemFun0_5<T, Q1, Q2, Q3, Q4, Q5, R>, P1, P2, P3, P4, P5>
        bind_all(S* _this, R (T::*_mfn)(Q1, Q2, Q3, Q4, Q5), P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5)
    {
        return Fun5_0<MemFun0_5<T, Q1, Q2, Q3, Q4, Q5, R>, P1, P2, P3, P4, P5>(
            mem_fun(_this, _mfn), _p1, _p2, _p3, _p4, _p5);
    }
    template<class Q1, class Q2, class Q3, class Q4, class Q5, class T, class R
           , class P1, class P2, class P3, class P4, class P5, class S>
        inline Fun5_0<ConstMemFun0_5<T, Q1, Q2, Q3, Q4, Q5, R>, P1, P2, P3, P4, P5>
        bind_all(const S* _this, R (T::*_cmfn)(Q1, Q2, Q3, Q4, Q5) const, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5)
    {
        return Fun5_0<ConstMemFun0_5<T, Q1, Q2, Q3, Q4, Q5, R>, P1, P2, P3, P4, P5>(
            mem_fun(_this, _cmfn), _p1, _p2, _p3, _p4, _p5);
    }
    //template<class Fo, class P1, class P2, class P3, class P4, class P5>
    //    inline Fun5_0<Fo, P1, P2, P3, P4, P5>
    //    bind_all(Fo _fo, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5)
    //{
    //    return Fun5_0<Fo, P1, P2, P3, P4, P5>(
    //        _fo, _p1, _p2, _p3, _p4, _p5);
    //}

    template<class Fo, class P1, class P2, class P3, class P4, class P5, class P6>
        struct Fun6_0
            : public Function_0<typename Fo::result_type>
        {
            typedef typename Fo::result_type _Result;
            Fun6_0(Fo _fo, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6)
                : fo_(_fo), p1_(_p1), p2_(_p2), p3_(_p3), p4_(_p4), p5_(_p5), p6_(_p6)
            {
            }
            _Result operator()()
            {
                return fo_(p1_, p2_, p3_, p4_, p5_, p6_);
            }
            _Result operator()() const
            {
                return fo_(p1_, p2_, p3_, p4_, p5_, p6_);
            }
        private:
            Fo fo_;
            typename MemberType<P1>::type p1_;
            typename MemberType<P2>::type p2_;
            typename MemberType<P3>::type p3_;
            typename MemberType<P4>::type p4_;
            typename MemberType<P5>::type p5_;
            typename MemberType<P6>::type p6_;
        };
    template<class Q1, class Q2, class Q3, class Q4, class Q5, class Q6, class R
           , class P1, class P2, class P3, class P4, class P5, class P6>
        inline Fun6_0<PtrFun0_6<Q1, Q2, Q3, Q4, Q5, Q6, R>, P1, P2, P3, P4, P5, P6>
        bind_all(R (*_fn)(Q1, Q2, Q3, Q4, Q5, Q6), P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6)
    {
        return Fun6_0<PtrFun0_6<Q1, Q2, Q3, Q4, Q5, Q6, R>, P1, P2, P3, P4, P5, P6>(
            ptr_fun(_fn), _p1, _p2, _p3, _p4, _p5, _p6);
    }
    template<class Q1, class Q2, class Q3, class Q4, class Q5, class Q6, class T, class R
           , class P1, class P2, class P3, class P4, class P5, class P6, class S>
        inline Fun6_0<MemFun0_6<T, Q1, Q2, Q3, Q4, Q5, Q6, R>, P1, P2, P3, P4, P5, P6>
        bind_all(S* _this, R (T::*_mfn)(Q1, Q2, Q3, Q4, Q5, Q6), P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6)
    {
        return Fun6_0<MemFun0_6<T, Q1, Q2, Q3, Q4, Q5, Q6, R>, P1, P2, P3, P4, P5, P6>(
            mem_fun(_this, _mfn), _p1, _p2, _p3, _p4, _p5, _p6);
    }
    template<class Q1, class Q2, class Q3, class Q4, class Q5, class Q6, class T, class R
           , class P1, class P2, class P3, class P4, class P5, class P6, class S>
        inline Fun6_0<ConstMemFun0_6<T, Q1, Q2, Q3, Q4, Q5, Q6, R>, P1, P2, P3, P4, P5, P6>
        bind_all(const S* _this, R (T::*_cmfn)(Q1, Q2, Q3, Q4, Q5, Q6) const, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6)
    {
        return Fun6_0<ConstMemFun0_6<T, Q1, Q2, Q3, Q4, Q5, Q6, R>, P1, P2, P3, P4, P5, P6>(
            mem_fun(_this, _cmfn), _p1, _p2, _p3, _p4, _p5, _p6);
    }
    //template<class Fo, class P1, class P2, class P3, class P4, class P5, class P6>
    //    inline Fun6_0<Fo, P1, P2, P3, P4, P5, P6>
    //    bind_all(Fo _fo, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6)
    //{
    //    return Fun6_0<Fo, P1, P2, P3, P4, P5, P6>(
    //        _fo, _p1, _p2, _p3, _p4, _p5, _p6);
    //}

    template<class Fo, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
    struct Fun7_0
        : public Function_0<typename Fo::result_type>
    {
        typedef typename Fo::result_type _Result;
        Fun7_0(Fo _fo, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7)
            : fo_(_fo), p1_(_p1), p2_(_p2), p3_(_p3), p4_(_p4), p5_(_p5), p6_(_p6), p7_(_p7)
        {
        }
        _Result operator()()
        {
            return fo_(p1_, p2_, p3_, p4_, p5_, p6_, p7_);
        }
        _Result operator()() const
        {
            return fo_(p1_, p2_, p3_, p4_, p5_, p6_, p7_);
        }
    private:
        Fo fo_;
        typename MemberType<P1>::type p1_;
        typename MemberType<P2>::type p2_;
        typename MemberType<P3>::type p3_;
        typename MemberType<P4>::type p4_;
        typename MemberType<P5>::type p5_;
        typename MemberType<P6>::type p6_;
        typename MemberType<P7>::type p7_;
    };
    template<class Q1, class Q2, class Q3, class Q4, class Q5, class Q6, class Q7, class R
        , class P1, class P2, class P3, class P4, class P5, class P6, class P7>
        inline Fun7_0<PtrFun0_7<Q1, Q2, Q3, Q4, Q5, Q6, Q7, R>, P1, P2, P3, P4, P5, P6, P7>
        bind_all(R (*_fn)(Q1, Q2, Q3, Q4, Q5, Q6, Q7), P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7)
    {
        return Fun7_0<PtrFun0_7<Q1, Q2, Q3, Q4, Q5, Q6, Q7, R>, P1, P2, P3, P4, P5, P6, P7>(
            ptr_fun(_fn), _p1, _p2, _p3, _p4, _p5, _p6, _p7);
    }
    template<class Q1, class Q2, class Q3, class Q4, class Q5, class Q6, class Q7, class T, class R
        , class P1, class P2, class P3, class P4, class P5, class P6, class P7, class S>
        inline Fun7_0<MemFun0_7<T, Q1, Q2, Q3, Q4, Q5, Q6, Q7, R>, P1, P2, P3, P4, P5, P6, P7>
        bind_all(S* _this, R (T::*_mfn)(Q1, Q2, Q3, Q4, Q5, Q6, Q7), P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7)
    {
        return Fun7_0<MemFun0_7<T, Q1, Q2, Q3, Q4, Q5, Q6, Q7, R>, P1, P2, P3, P4, P5, P6, P7>(
            mem_fun(_this, _mfn), _p1, _p2, _p3, _p4, _p5, _p6, _p7);
    }
    template<class Q1, class Q2, class Q3, class Q4, class Q5, class Q6, class Q7, class T, class R
        , class P1, class P2, class P3, class P4, class P5, class P6, class P7, class S>
        inline Fun7_0<ConstMemFun0_7<T, Q1, Q2, Q3, Q4, Q5, Q6, Q7, R>, P1, P2, P3, P4, P5, P6, P7>
        bind_all(const S* _this, R (T::*_cmfn)(Q1, Q2, Q3, Q4, Q5, Q6, Q7) const, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7)
    {
        return Fun7_0<ConstMemFun0_7<T, Q1, Q2, Q3, Q4, Q5, Q6, Q7, R>, P1, P2, P3, P4, P5, P6, P7>(
            mem_fun(_this, _cmfn), _p1, _p2, _p3, _p4, _p5, _p6, _p7);
    }
    //template<class Fo, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
    //    inline Fun7_0<Fo, P1, P2, P3, P4, P5, P6, P7>
    //    bind_all(Fo _fo, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7)
    //{
    //    return Fun7_0<Fo, P1, P2, P3, P4, P5, P6, P7>(
    //        _fo, _p1, _p2, _p3, _p4, _p5, _p6, _p7);
    //}

    template<class Fo, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
    struct Fun8_0
        : public Function_0<typename Fo::result_type>
    {
        typedef typename Fo::result_type _Result;
        Fun8_0(Fo _fo, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8)
            : fo_(_fo), p1_(_p1), p2_(_p2), p3_(_p3), p4_(_p4), p5_(_p5), p6_(_p6), p7_(_p7), p8_(_p8)
        {
        }
        _Result operator()()
        {
            return fo_(p1_, p2_, p3_, p4_, p5_, p6_, p7_, p8_);
        }
        _Result operator()() const
        {
            return fo_(p1_, p2_, p3_, p4_, p5_, p6_, p7_, p8_);
        }
    private:
        Fo fo_;
        typename MemberType<P1>::type p1_;
        typename MemberType<P2>::type p2_;
        typename MemberType<P3>::type p3_;
        typename MemberType<P4>::type p4_;
        typename MemberType<P5>::type p5_;
        typename MemberType<P6>::type p6_;
        typename MemberType<P7>::type p7_;
        typename MemberType<P8>::type p8_;
    };
    template<class Q1, class Q2, class Q3, class Q4, class Q5, class Q6, class Q7, class Q8, class R
        , class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
        inline Fun8_0<PtrFun0_8<Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, R>, P1, P2, P3, P4, P5, P6, P7, P8>
        bind_all(R (*_fn)(Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8), P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8)
    {
        return Fun8_0<PtrFun0_8<Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, R>, P1, P2, P3, P4, P5, P6, P7, P8>(
            ptr_fun(_fn), _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8);
    }
    template<class Q1, class Q2, class Q3, class Q4, class Q5, class Q6, class Q7, class Q8, class T, class R
        , class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class S>
        inline Fun8_0<MemFun0_8<T, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, R>, P1, P2, P3, P4, P5, P6, P7, P8>
        bind_all(S* _this, R (T::*_mfn)(Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8), P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8)
    {
        return Fun8_0<MemFun0_8<T, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, R>, P1, P2, P3, P4, P5, P6, P7, P8>(
            mem_fun(_this, _mfn), _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8);
    }
    template<class Q1, class Q2, class Q3, class Q4, class Q5, class Q6, class Q7, class Q8, class T, class R
        , class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class S>
        inline Fun8_0<ConstMemFun0_8<T, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, R>, P1, P2, P3, P4, P5, P6, P7, P8>
        bind_all(const S* _this, R (T::*_cmfn)(Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8) const, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8)
    {
        return Fun8_0<ConstMemFun0_8<T, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, R>, P1, P2, P3, P4, P5, P6, P7, P8>(
            mem_fun(_this, _cmfn), _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8);
    }
    //template<class Fo, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
    //    inline Fun8_0<Fo, P1, P2, P3, P4, P5, P6, P7, P8>
    //    bind_all(Fo _fo, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8)
    //{
    //    return Fun8_0<Fo, P1, P2, P3, P4, P5, P6, P7, P8>(
    //        _fo, _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8);
    //}

    template<class Fo, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
    struct Fun9_0
        : public Function_0<typename Fo::result_type>
    {
        typedef typename Fo::result_type _Result;
        Fun9_0(Fo _fo, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9)
            : fo_(_fo), p1_(_p1), p2_(_p2), p3_(_p3), p4_(_p4), p5_(_p5), p6_(_p6), p7_(_p7), p8_(_p8), p9_(_p9)
        {
        }
        _Result operator()()
        {
            return fo_(p1_, p2_, p3_, p4_, p5_, p6_, p7_, p8_, p9_);
        }
        _Result operator()() const
        {
            return fo_(p1_, p2_, p3_, p4_, p5_, p6_, p7_, p8_, p9_);
        }
    private:
        Fo fo_;
        typename MemberType<P1>::type p1_;
        typename MemberType<P2>::type p2_;
        typename MemberType<P3>::type p3_;
        typename MemberType<P4>::type p4_;
        typename MemberType<P5>::type p5_;
        typename MemberType<P6>::type p6_;
        typename MemberType<P7>::type p7_;
        typename MemberType<P8>::type p8_;
        typename MemberType<P9>::type p9_;
    };
    template<class Q1, class Q2, class Q3, class Q4, class Q5, class Q6, class Q7, class Q8, class Q9, class R
        , class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
        inline Fun9_0<PtrFun0_9<Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, R>, P1, P2, P3, P4, P5, P6, P7, P8, P9>
        bind_all(R (*_fn)(Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9), P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9)
    {
        return Fun9_0<PtrFun0_9<Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, R>, P1, P2, P3, P4, P5, P6, P7, P8, P9>(
            ptr_fun(_fn), _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9);
    }
    template<class Q1, class Q2, class Q3, class Q4, class Q5, class Q6, class Q7, class Q8, class Q9, class T, class R
        , class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class S>
        inline Fun9_0<MemFun0_9<T, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, R>, P1, P2, P3, P4, P5, P6, P7, P8, P9>
        bind_all(S* _this, R (T::*_mfn)(Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9), P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9)
    {
        return Fun9_0<MemFun0_9<T, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, R>, P1, P2, P3, P4, P5, P6, P7, P8, P9>(
            mem_fun(_this, _mfn), _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9);
    }
    template<class Q1, class Q2, class Q3, class Q4, class Q5, class Q6, class Q7, class Q8, class Q9, class T, class R
        , class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class S>
        inline Fun9_0<ConstMemFun0_9<T, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, R>, P1, P2, P3, P4, P5, P6, P7, P8, P9>
        bind_all(const S* _this, R (T::*_cmfn)(Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9) const, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9)
    {
        return Fun9_0<ConstMemFun0_9<T, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, R>, P1, P2, P3, P4, P5, P6, P7, P8, P9>(
            mem_fun(_this, _cmfn), _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9);
    }
    //template<class Fo, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
    //    inline Fun9_0<Fo, P1, P2, P3, P4, P5, P6, P7, P8, P9>
    //    bind_all(Fo _fo, P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9)
    //{
    //    return Fun9_0<Fo, P1, P2, P3, P4, P5, P6, P7, P8, P9>(
    //        _fo, _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9);
    //}

    ////////////////////////////////////////////////////////////////////
    //
    // 0..N : 1 执行时有一个参数，其它参数在构造时提供（用于在容器中遍历）
    //
    ////////////////////////////////////////////////////////////////////

    template<class Fo>
        struct Fun0_1
            : public Function_1<typename Fo::param_type_1, typename Fo::result_type>
        {
            typedef typename Fo::param_type_1 P1;
            typedef typename Fo::result_type _Result;
            Fun0_1(Fo _fo)
                : fo_(_fo)
            {
            }
            _Result operator()(P1 _p1) 
            {
                return fo_(_p1);
            }
            _Result operator()(P1 _p1) const
            {
                return fo_(_p1);
            }
        private:
            Fo fo_;
        };
    template<class Q1, class R>
        inline Fun0_1<PtrFun0_1<Q1, R> >
        bind_after_1st(R (*_fn)(Q1))
    {
        return Fun0_1<PtrFun0_1<Q1, R> >(ptr_fun(_fn));
    }
    template<class Q1, class T, class R, class S>
        inline Fun0_1<MemFun0_1<T, Q1, R> >
        bind_after_1st(S* _this, R (T::*_mfn)(Q1))
    {
        return Fun0_1<MemFun0_1<T, Q1, R> >(mem_fun(_this, _mfn));
    }
    template<class Q1, class T, class R, class S>
        inline Fun0_1<ConstMemFun0_1<T, Q1, R> >
        bind_after_1st(const S* _this, R (T::*_cmfn)(Q1) const)
    {
        return Fun0_1<ConstMemFun0_1<T, Q1, R> >(mem_fun(_this, _cmfn));
    }
    template<class Fo>
        inline Fun0_1<Fo>
        bind_after_1st(Fo _fo)
    {
        return Fun0_1<Fo>(_fo);
    }

    template<class Fo, class P2>
        struct Fun1_1
            : public Function_1<typename Fo::param_type_1, typename Fo::result_type>
        {
            typedef typename Fo::param_type_1 P1;
            typedef typename Fo::result_type _Result;
            Fun1_1(Fo _fo, P2 _p2)
                : fo_(_fo), p2_(_p2)
            {
            }
            _Result operator()(P1 _p1) 
            {
                return fo_(_p1, p2_);
            }
            _Result operator()(P1 _p1) const
            {
                return fo_(_p1, p2_);
            }
        private:
            Fo fo_;
            typename MemberType<P2>::type p2_;
        };
    template<class Q1, class Q2, class R
                     , class P2>
        inline Fun1_1<PtrFun0_2<Q1, Q2, R>, P2>
        bind_after_1st(R (*_fn)(Q1, Q2), P2 _p2)
    {
        return Fun1_1<PtrFun0_2<Q1, Q2, R>, P2>(ptr_fun(_fn), _p2);
    }
    template<class Q1, class Q2, class T, class R
                     , class P2, class S>
        inline Fun1_1<MemFun0_2<T, Q1, Q2, R>, P2>
        bind_after_1st(S* _this, R (T::*_mfn)(Q1, Q2), P2 _p2)
    {
        return Fun1_1<MemFun0_2<T, Q1, Q2, R>, P2>(mem_fun(_this, _mfn), _p2);
    }
    template<class Q1, class Q2, class T, class R
                     , class P2, class S>
        inline Fun1_1<ConstMemFun0_2<T, Q1, Q2, R>, P2>
        bind_after_1st(const S* _this, R (T::*_cmfn)(Q1, Q2) const, P2 _p2)
    {
        return Fun1_1<ConstMemFun0_2<T, Q1, Q2, R>, P2>(mem_fun(_this, _cmfn), _p2);
    }
    template<class Fo, class P2>
        inline Fun1_1<Fo, P2>
        bind_after_1st(Fo _fo, P2 _p2)
    {
        return Fun1_1<Fo, P2>(_fo, _p2);
    }

    template<class Fo, class P2, class P3>
        struct Fun2_1
            : public Function_1<typename Fo::param_type_1, typename Fo::result_type>
        {
            typedef typename Fo::param_type_1 P1;
            typedef typename Fo::result_type _Result;
            Fun2_1(Fo _fo, P2 _p2, P3 _p3)
                : fo_(_fo), p2_(_p2), p3_(_p3)
            {
            }
            _Result operator()(P1 _p1) 
            {
                return fo_(_p1, p2_, p3_);
            }
            _Result operator()(P1 _p1) const
            {
                return fo_(_p1, p2_, p3_);
            }
        private:
            Fo fo_;
            typename MemberType<P2>::type p2_;
            typename MemberType<P3>::type p3_;
        };
    template<class Q1, class Q2, class Q3, class R
                     , class P2, class P3>
        inline Fun2_1<PtrFun0_3<Q1, Q2, Q3, R>, P2, P3>
        bind_after_1st(R (*_fn)(Q1, Q2, Q3), P2 _p2, P3 _p3)
    {
        return Fun2_1<PtrFun0_3<Q1, Q2, Q3, R>, P2, P3>(
            ptr_fun(_fn), _p2, _p3);
    }
    template<class Q1, class Q2, class Q3, class T, class R
                     , class P2, class P3, class S>
        inline Fun2_1<MemFun0_3<T, Q1, Q2, Q3, R>, P2, P3>
        bind_after_1st(S* _this, R (T::*_mfn)(Q1, Q2, Q3), P2 _p2, P3 _p3)
    {
        return Fun2_1<MemFun0_3<T, Q1, Q2, Q3, R>, P2, P3>(
            mem_fun(_this, _mfn), _p2, _p3);
    }
    template<class Q1, class Q2, class Q3, class T, class R
                     , class P2, class P3, class S>
        inline Fun2_1<ConstMemFun0_3<T, Q1, Q2, Q3, R>, P2, P3>
        bind_after_1st(const S* _this, R (T::*_cmfn)(Q1, Q2, Q3) const, P2 _p2, P3 _p3)
    {
        return Fun2_1<ConstMemFun0_3<T, Q1, Q2, Q3, R>, P2, P3>(
            mem_fun(_this, _cmfn), _p2, _p3);
    }
    template<class Fo, class P2, class P3>
        inline Fun2_1<Fo, P2, P3>
        bind_after_1st(Fo _fo, P2 _p2, P3 _p3)
    {
        return Fun2_1<Fo, P2, P3>(
            _fo, _p2, _p3);
    }

    template<class Fo, class P2, class P3, class P4>
        struct Fun3_1
            : public Function_1<typename Fo::param_type_1, typename Fo::result_type>
        {
            typedef typename Fo::param_type_1 P1;
            typedef typename Fo::result_type _Result;
            Fun3_1(Fo _fo, P2 _p2, P3 _p3, P4 _p4)
                : fo_(_fo), p2_(_p2), p3_(_p3), p4_(_p4)
            {
            }
            _Result operator()(P1 _p1)
            {
                return fo_(_p1, p2_, p3_, p4_);
            }
            _Result operator()(P1 _p1) const
            {
                return fo_(_p1, p2_, p3_, p4_);
            }
        private:
            Fo fo_;
            typename MemberType<P2>::type p2_;
            typename MemberType<P3>::type p3_;
            typename MemberType<P4>::type p4_;
        };
    template<class Q1, class Q2, class Q3, class Q4, class R
                     , class P2, class P3, class P4>
        inline Fun3_1<PtrFun0_4<Q1, Q2, Q3, Q4, R>, P2, P3, P4>
        bind_after_1st(R (*_fn)(Q1, Q2, Q3, Q4), P2 _p2, P3 _p3, P4 _p4)
    {
        return Fun3_1<PtrFun0_4<Q1, Q2, Q3, Q4, R>, P2, P3, P4>(
            ptr_fun(_fn), _p2, _p3, _p4);
    }
    template<class Q1, class Q2, class Q3, class Q4, class T, class R
                     , class P2, class P3, class P4, class S>
        inline Fun3_1<MemFun0_4<T, Q1, Q2, Q3, Q4, R>, P2, P3, P4>
        bind_after_1st(S* _this, R (T::*_mfn)(Q1, Q2, Q3, Q4), P2 _p2, P3 _p3, P4 _p4)
    {
        return Fun3_1<MemFun0_4<T, Q1, Q2, Q3, Q4, R>, P2, P3, P4>(
            mem_fun(_this, _mfn), _p2, _p3, _p4);
    }
    template<class Q1, class Q2, class Q3, class Q4, class T, class R
                     , class P2, class P3, class P4, class S>
        inline Fun3_1<ConstMemFun0_4<T, Q1, Q2, Q3, Q4, R>, P2, P3, P4>
        bind_after_1st(const S* _this, R (T::*_cmfn)(Q1, Q2, Q3, Q4) const, P2 _p2, P3 _p3, P4 _p4)
    {
        return Fun3_1<ConstMemFun0_4<T, Q1, Q2, Q3, Q4, R>, P2, P3, P4>(
            mem_fun(_this, _cmfn), _p2, _p3, _p4);
    }
    template<class Fo, class P2, class P3, class P4>
        inline Fun3_1<Fo, P2, P3, P4>
        bind_after_1st(Fo _fo, P2 _p2, P3 _p3, P4 _p4)
    {
        return Fun3_1<Fo, P2, P3, P4>(
            _fo, _p2, _p3, _p4);
    }

    template<class Fo, class P2, class P3, class P4, class P5>
        struct Fun4_1
            : public Function_1<typename Fo::param_type_1, typename Fo::result_type>
        {
            typedef typename Fo::param_type_1 P1;
            typedef typename Fo::result_type _Result;
            Fun4_1(Fo _fo, P2 _p2, P3 _p3, P4 _p4, P5 _p5)
                : fo_(_fo), p2_(_p2), p3_(_p3), p4_(_p4), p5_(_p5)
            {
            }
            _Result operator()(P1 _p1)
            {
                return fo_(_p1, p2_, p3_, p4_, p5_);
            }
            _Result operator()(P1 _p1) const
            {
                return fo_(_p1, p2_, p3_, p4_, p5_);
            }
        private:
            Fo fo_;
            typename MemberType<P2>::type p2_;
            typename MemberType<P3>::type p3_;
            typename MemberType<P4>::type p4_;
            typename MemberType<P5>::type p5_;
        };
    template<class Q1, class Q2, class Q3, class Q4, class Q5, class R
                     , class P2, class P3, class P4, class P5>
        inline Fun4_1<PtrFun0_5<Q1, Q2, Q3, Q4, Q5, R>, P2, P3, P4, P5>
        bind_after_1st(R (*_fn)(Q1, Q2, Q3, Q4, Q5), P2 _p2, P3 _p3, P4 _p4, P5 _p5)
    {
        return Fun4_1<PtrFun0_5<Q1, Q2, Q3, Q4, Q5, R>, P2, P3, P4, P5>(
            ptr_fun(_fn), _p2, _p3, _p4, _p5);
    }
    template<class Q1, class Q2, class Q3, class Q4, class Q5, class T, class R
                     , class P2, class P3, class P4, class P5, class S>
        inline Fun4_1<MemFun0_5<T, Q1, Q2, Q3, Q4, Q5, R>, P2, P3, P4, P5>
        bind_after_1st(S* _this, R (T::*_mfn)(Q1, Q2, Q3, Q4, Q5), P2 _p2, P3 _p3, P4 _p4, P5 _p5)
    {
        return Fun4_1<MemFun0_5<T, Q1, Q2, Q3, Q4, Q5, R>, P2, P3, P4, P5>(
            mem_fun(_this, _mfn), _p2, _p3, _p4, _p5);
    }
    template<class Q1, class Q2, class Q3, class Q4, class Q5, class T, class R
                     , class P2, class P3, class P4, class P5, class S>
        inline Fun4_1<ConstMemFun0_5<T, Q1, Q2, Q3, Q4, Q5, R>, P2, P3, P4, P5>
        bind_after_1st(const S* _this, R (T::*_cmfn)(Q1, Q2, Q3, Q4, Q5) const, P2 _p2, P3 _p3, P4 _p4, P5 _p5)
    {
        return Fun4_1<ConstMemFun0_5<T, Q1, Q2, Q3, Q4, Q5, R>, P2, P3, P4, P5>(
            mem_fun(_this, _cmfn), _p2, _p3, _p4, _p5);
    }
    template<class Fo, class P2, class P3, class P4, class P5>
        inline Fun4_1<Fo, P2, P3, P4, P5>
        bind_after_1st(Fo _fo, P2 _p2, P3 _p3, P4 _p4, P5 _p5)
    {
        return Fun4_1<Fo, P2, P3, P4, P5>(
            _fo, _p2, _p3, _p4, _p5);
    }

    template<class Fo, class P2, class P3, class P4, class P5, class P6>
        struct Fun5_1
            : public Function_1<typename Fo::param_type_1, typename Fo::result_type>
        {
            typedef typename Fo::param_type_1 P1;
            typedef typename Fo::result_type _Result;
            Fun5_1(Fo _fo, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6)
                : fo_(_fo), p2_(_p2), p3_(_p3), p4_(_p4), p5_(_p5), p6_(_p6)
            {
            }
            _Result operator()(P1 _p1)
            {
                return fo_(_p1, p2_, p3_, p4_, p5_, p6_);
            }
            _Result operator()(P1 _p1) const
            {
                return fo_(_p1, p2_, p3_, p4_, p5_, p6_);
            }
        private:
            Fo fo_;
            typename MemberType<P2>::type p2_;
            typename MemberType<P3>::type p3_;
            typename MemberType<P4>::type p4_;
            typename MemberType<P5>::type p5_;
            typename MemberType<P6>::type p6_;
        };
    template<class Fo, class P2, class P3, class P4, class P5, class P6>
        inline Fun5_1<Fo, P2, P3, P4, P5, P6>
        bind_after_1st(Fo _fo, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6)
    {
        return Fun5_1<Fo, P2, P3, P4, P5, P6>(
            _fo, _p2, _p3, _p4, _p5, _p6);
    }

}

#endif //_Z_CTK_UTIL_MEMFUN_H_

