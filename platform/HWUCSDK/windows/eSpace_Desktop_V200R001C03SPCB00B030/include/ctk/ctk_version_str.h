/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_VERSION_STR_H_
#define _Z_CTK_VERSION_STR_H_

#include "ctk/ctk_version.h"

/*
 * 1.8.8-50[20130509] ����cui��ctk��1.8.8-00��������Ҫ�Ķ�����Ҫ���޸ġ�
 * 1.8.8-51[20130520] ���������߳��˳��ܿ�ʱ��joinҪ�ȴ��ܳ�ʱ�䡣
 *                    ���������Thread����clearHandle()����startHook()�����ã�ThreadControl.join()Ҫ�жϾ���Ƿ�Ϊ�ա�
 * 1.8.8-53[20130520] ȥ����_WIN32��Thread::Thread()�е�closed_��
 * 1.8.8-55[20130522] ȥ��ctk::Thread::clearHandle()��û�����塣
 * 1.8.8-61[20130524] swap�����ռ����������ʹ��memcpy�����ݽ�����
                      ����Ҫ���Զ���swap�������򵥣���Ч��  
                      Ϊ�����std::swap��ͻ��vs2008�������⣩����ctk::swap<T>(T&,T&)����Ϊctk::swap_��
 * 1.8.8-66[20130613] ����ctk::Thread::onBirth_i��m_living��ֵ˳��������onBirthû�н���ǰ�͹ر��̵߳Ļ��Ͳ����ٽ���onLoop��
 * 1.8.8-67[20130628] xml�������Ҫ�������ַ�ת�塣
 * 1.8.8-68[20130712] �ָ������ǵĴ��롣
 * 1.8.8-69[20130712] ctk::Base64::encode���Ӳ���_insertNewLines���Կ����Ƿ����ӻ��з�����ĳЩ�����²����л��з�����
 * 1.8.8-70[20130805] ctk::XmlInStream����ʱ���׳��쳣���������ʧ�ܿ����ж�isNull()��operator>>��
 * 1.8.8-71[20130805] ����ctk::XmlInStream����ʱ����ֵbool��void��ƥ������⣨�����ӡ�STL����
 * 1.8.8-72[20130805] д��־�ļ�ʧ��ʱ���׳��쳣�����Ժ��Ըô���
 * 1.8.8-73[20130806] _O_CREAT�ȵĶ���(CTK_MAC)
 * 1.8.8-75[20130823] ���MAC��������
 * 1.8.8-76[20130826] �޸�Stackwalker.cpp��printfΪCTK_OUTL
 * 1.8.8-77[20130827] ��ʱ���ص�onTimerʱ�Ƚ����������
 * 1.8.8-78[20130905] �޸�ctk::SimpleThread::stop()��bug: �ж�m_livingΪfalse�������˳����ܵ���on_thread_exit()��owner��Ч��ȥ�����ж�
 * 1.8.8-79[20130918] TQE����
 * 1.8.8-80[20130923] TQE����
 * 1.8.8-81[20130925] TQE����
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

