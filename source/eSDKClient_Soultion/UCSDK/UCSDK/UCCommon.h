#ifndef _UC_COMMON_HEADEAR_
#define _UC_COMMON_HEADEAR_

/*
 *	�ж�ָ���Ƿ�Ϊ�� 
 */
#define CHECK_POINTER( pPointer, retValue )			\
if ( NULL == ( pPointer ) )							\
{													\
	ERROR_LOG() << #pPointer << " is Null Point.";	\
	DEBUG_LOG() << "--- LEAVE";						\
    return (retValue);								\
}													\

/*
 *	�ж�ָ���Ƿ�Ϊ��,�޷���ֵ
 */
#define CHECK_POINTER_VOID( pPointer )				\
if ( NULL == ( pPointer ) )							\
{													\
	ERROR_LOG() << #pPointer << " is Null Point.";	\
	DEBUG_LOG() << "--- LEAVE";						\
    return ;										\
}

/*
 *  �жϷ���ֵ
 */
#define CHECK_RETURN( iRet, iTarget, strDes )		\
if ( (iTarget) != (iRet) )							\
{													\
	ERROR_LOG() << (strDes) << " failed.";			\
	DEBUG_LOG() << "--- LEAVE";						\
	return (iRet);									\
}													\

/*
 *  �жϷ���ֵ,�޷���ֵ
 */
#define CHECK_RETURN_VOID( iRet, iTarget, strDes )	\
if ( (iTarget) != (iRet) )							\
{													\
	ERROR_LOG() << (strDes) << " failed.";			\
	DEBUG_LOG() << "--- LEAVE";						\
}		

#endif
