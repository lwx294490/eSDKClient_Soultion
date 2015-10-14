#ifndef _UC_COMMON_HEADEAR_
#define _UC_COMMON_HEADEAR_

/*
 *	判断指针是否为空 
 */
#define CHECK_POINTER( pPointer, retValue )			\
if ( NULL == ( pPointer ) )							\
{													\
	ERROR_LOG() << #pPointer << " is Null Point.";	\
	DEBUG_LOG() << "--- LEAVE";						\
    return (retValue);								\
}													\

/*
 *	判断指针是否为空,无返回值
 */
#define CHECK_POINTER_VOID( pPointer )				\
if ( NULL == ( pPointer ) )							\
{													\
	ERROR_LOG() << #pPointer << " is Null Point.";	\
	DEBUG_LOG() << "--- LEAVE";						\
    return ;										\
}

/*
 *  判断返回值
 */
#define CHECK_RETURN( iRet, iTarget, strDes )		\
if ( (iTarget) != (iRet) )							\
{													\
	ERROR_LOG() << (strDes) << " failed.";			\
	DEBUG_LOG() << "--- LEAVE";						\
	return (iRet);									\
}													\

/*
 *  判断返回值,无返回值
 */
#define CHECK_RETURN_VOID( iRet, iTarget, strDes )	\
if ( (iTarget) != (iRet) )							\
{													\
	ERROR_LOG() << (strDes) << " failed.";			\
	DEBUG_LOG() << "--- LEAVE";						\
}		

#endif
