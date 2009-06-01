#include "HvCoreDebugger.h"
#include <stdarg.h>
#include "hvm.h"

/**
 * Effects: Write info with format.
 * 带格式写String
 **/
NTSTATUS NTAPI DbgPrintInfo (PUCHAR fmt,...)
{
	va_list args;
	va_start (args, fmt);
	return WriteDbgInfo(fmt,(PUCHAR) fmt, args);
}

/**
 * Effects: Initialize SpinLock, must be called before invoke WriteDbgInfo function
 * 初始化写信息自旋锁,必须在调用WriteDbgInfo方法前调用
 **/
void NTAPI DbgInitComponent()
{
	WriteInfoInit();
}

void NTAPI DbgDisposeComponent()
{
	WriteInfoDispose();
}