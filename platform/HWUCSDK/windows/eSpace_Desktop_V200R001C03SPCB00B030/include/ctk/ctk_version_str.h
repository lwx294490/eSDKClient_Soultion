/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_VERSION_STR_H_
#define _Z_CTK_VERSION_STR_H_

#include "ctk/ctk_version.h"

/*
 * 1.8.8-50[20130509] 参照cui中ctk从1.8.8-00以来的主要改动做必要的修改。
 * 1.8.8-51[20130520] 问题现象：线程退出很快时，join要等待很长时间。
 *                    解决方法：Thread增加clearHandle()，在startHook()最后调用，ThreadControl.join()要判断句柄是否为空。
 * 1.8.8-53[20130520] 去掉非_WIN32版Thread::Thread()中的closed_。
 * 1.8.8-55[20130522] 去掉ctk::Thread::clearHandle()，没有意义。
 * 1.8.8-61[20130524] swap技术终极解决方案：使用memcpy做数据交换。
                      不需要再自定义swap函数。简单！高效！  
                      为避免和std::swap冲突（vs2008编译问题），将ctk::swap<T>(T&,T&)更名为ctk::swap_。
 * 1.8.8-66[20130613] 调整ctk::Thread::onBirth_i中m_living赋值顺序，这样在onBirth没有结束前就关闭线程的话就不会再进入onLoop。
 * 1.8.8-67[20130628] xml编码输出要对特殊字符转义。
 * 1.8.8-68[20130712] 恢复被覆盖的代码。
 * 1.8.8-69[20130712] ctk::Base64::encode增加参数_insertNewLines，以控制是否增加换行符（在某些场景下不能有换行符）。
 * 1.8.8-70[20130805] ctk::XmlInStream解析时不抛出异常，如果解析失败可以判断isNull()或operator>>。
 * 1.8.8-71[20130805] 纠正ctk::XmlInStream输入时返回值bool和void不匹配的问题（函数子、STL）。
 * 1.8.8-72[20130805] 写日志文件失败时不抛出异常，可以忽略该错误。
 * 1.8.8-73[20130806] _O_CREAT等的定义(CTK_MAC)
 * 1.8.8-75[20130823] 解决MAC编译问题
 * 1.8.8-76[20130826] 修改Stackwalker.cpp中printf为CTK_OUTL
 * 1.8.8-77[20130827] 定时器回调onTimer时先解锁，后加锁
 * 1.8.8-78[20130905] 修复ctk::SimpleThread::stop()的bug: 判断m_living为false就立即退出可能导致on_thread_exit()中owner无效，去掉此判断
 * 1.8.8-79[20130918] TQE整改
 * 1.8.8-80[20130923] TQE整改
 * 1.8.8-81[20130925] TQE整改
 * 
 */
#define CTK_VERSION_MINI_PATCH  81
#define CTK_VERSION_DATE_TIME   "20130925"

#define CTK_MINI_PATCH_STR     _CTK_STRINGIZE(CTK_VERSION_MINI_PATCH)"["CTK_VERSION_DATE_TIME"]"

#ifdef _DEBUG
#define CTK_DEBUG_STR           "(debug) "
#else
#define CTK_DEBUG_STR           ""
#endif

#define CTK_VERSION_STR        CTK_DEBUG_STR""_CTK_LIB_VERSION_STR"-"CTK_MINI_PATCH_STR 

#define CTK_COPYRIGHT           "CTK(Common Tool Kit) version " CTK_VERSION_STR "\n" \
                                "Author: luyunhai 117629(3664)/huawei\n" \
                                "Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.\n" \
                                "All rights reserved."

#define CTK_FULL_VERSION        CTK_MERGE(CTK_VERSION, CTK_VERSION_MINI_PATCH)

#define CTK_FULL_NAMESPACE(x)   CTK_MERGE(x##_, CTK_FULL_VERSION)

namespace CTK_FULL_NAMESPACE(ctk)
{
}

#endif //_Z_CTK_VERSION_STR_H_

