#pragma once
#include <sql.h>
#include <sqlext.h>


// these are defined here for lack of a better place

static SQLRETURN SQLAllocHandle_1p1(SQLSMALLINT HandleType, SQLHANDLE InputHandle, SQLHANDLE* OutputHandle)
{
	SQLRETURN(__stdcall * _SQLAllocHandle_1p1)(SQLSMALLINT HandleType, SQLHANDLE InputHandle, SQLHANDLE * OutputHandle) = ((SQLRETURN(__stdcall*)(SQLSMALLINT, SQLHANDLE, SQLHANDLE*))0x4A350C);

	return _SQLAllocHandle_1p1(HandleType, InputHandle, OutputHandle);
}

static SQLRETURN SQLExecDirect_1p1(SQLHSTMT StatementHandle, SQLCHAR* StatementText, SQLINTEGER TextLength)
{
	SQLRETURN(__stdcall * _SQLExecDirect_1p1)(SQLHSTMT StatementHandle, SQLCHAR * StatementText, SQLINTEGER TextLength) = ((SQLRETURN(__stdcall*)(SQLHSTMT, SQLCHAR*, SQLINTEGER))0x4A3506);

	return _SQLExecDirect_1p1(StatementHandle, StatementText, TextLength);
}

static SQLRETURN SQLFreeHandle_1p1(SQLSMALLINT HandleType, SQLHANDLE Handle)
{
	SQLRETURN(__stdcall * _SQLFreeHandle_1p1)(SQLSMALLINT HandleType, SQLHANDLE Handle) = ((SQLRETURN(__stdcall*)(SQLSMALLINT, SQLHANDLE))0x4A34FA);

	return _SQLFreeHandle_1p1(HandleType, Handle);
}

static SQLRETURN SQLFetch_1p1(SQLHSTMT StatementHandle)
{
	SQLRETURN(__stdcall * _SQLFetch_1p1)(SQLHSTMT StatementHandle) = ((SQLRETURN(__stdcall*)(SQLHSTMT))0x4A3512);

	return _SQLFetch_1p1(StatementHandle);
}

static SQLRETURN SQLGetData_1p1(SQLHSTMT StatementHandle, SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValue, SQLINTEGER BufferLength, SQLINTEGER* StrLen_or_Ind)
{
	SQLRETURN(__stdcall * _SQLGetData_1p1)(SQLHSTMT StatementHandle, SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValue, SQLINTEGER BufferLength, SQLINTEGER * StrLen_or_Ind) = ((SQLRETURN(__stdcall*)(SQLHSTMT, SQLUSMALLINT, SQLSMALLINT, SQLPOINTER, SQLINTEGER, SQLINTEGER* ))0x4A352A);

	return _SQLGetData_1p1(StatementHandle, ColumnNumber, TargetType, TargetValue, BufferLength, StrLen_or_Ind);
}


static SQLRETURN SQLBindParameter_1p1(SQLHSTMT hstmt, SQLUSMALLINT ipar, SQLSMALLINT fParamType, SQLSMALLINT fCType, SQLSMALLINT fSqlType, SQLUINTEGER cbColDef, SQLSMALLINT ibScale, SQLPOINTER rgbValue, SQLINTEGER cbValueMax, SQLINTEGER* pcbValue)
{
	SQLRETURN(__stdcall * _SQLBindParameter_1p1)(SQLHSTMT hstmt, SQLUSMALLINT ipar, SQLSMALLINT fParamType, SQLSMALLINT fCType, SQLSMALLINT fSqlType, SQLUINTEGER cbColDef, SQLSMALLINT ibScale, SQLPOINTER rgbValue, SQLINTEGER cbValueMax, SQLINTEGER * pcbValue) = ((SQLRETURN(__stdcall*)(SQLHSTMT, SQLUSMALLINT, SQLSMALLINT, SQLSMALLINT, SQLSMALLINT, SQLUINTEGER, SQLSMALLINT, SQLPOINTER, SQLINTEGER, SQLINTEGER *))0x4A351E);

	return _SQLBindParameter_1p1(hstmt, ipar, fParamType, fCType, fSqlType, cbColDef, ibScale, rgbValue, cbValueMax, pcbValue);
}


static SQLRETURN SQLParamData_1p1(SQLHSTMT StatementHandle, SQLPOINTER* Value)
{
	SQLRETURN(__stdcall * _SQLParamData_1p1)(SQLHSTMT StatementHandle, SQLPOINTER * Value) = ((SQLRETURN(__stdcall*)(SQLHSTMT, SQLPOINTER* ))0x4A3500);

	return _SQLParamData_1p1(StatementHandle, Value);
}

// OnePerOne.obj


static void COnePerOneDlg_DisplayErrorMsg(DWORD opoPtr, void* handle)
{
	void(__thiscall * _COnePerOneDlg_DisplayErrorMsg)(DWORD opoPtr, void* handle) = ((void(__thiscall*)(DWORD, void*))0x4283d0);

	_COnePerOneDlg_DisplayErrorMsg(opoPtr, handle);
}

// array_p.obj

//void __thiscall CPtrArray::SetSize(int, int) 4a75ff
static void CPtrArray_SetSize(DWORD cpaPtr, int a1, int a2)
{
	void(__thiscall * _CPtrArray_SetSize)(DWORD cpaPtr, int a1, int a2) = ((void(__thiscall*)(DWORD, int, int))0x4a75ff);

	_CPtrArray_SetSize(cpaPtr, a1, a2);
}