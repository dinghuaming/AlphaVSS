/* Copyright (c) 2008 Peter Palotas
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */
#pragma once


// 
// Macros used by other macros to create a standard const wchar_t* string
// from an arbritrary (unquoted) text .
//
#define CONCAT(x,y) x##y
#define WSTRINGIFY(x) CONCAT(L,#x)


//
// Macro to execute a COM API and to test its result. 
// It will execute the call given as a parameter. If the resulting HRESULT
// indicates an error, an exception will be thrown (via GenerateVssException in
// Utils.h) with the code forming the call as the message.
//
#define CheckCom( Call ) CheckComError( Call, #Call ) 

// 
// Utility macro assisting CheckCom, takes a HRESULT error code and a text
// describing the error. If the error code indicates an error,
// an appropriate exception will be thrown, using GenerateVssException,
// otherwise nothing will happen.
//
#define CheckComError( ErrorCode, Text )							\
{																	\
	HRESULT hrInternal = ErrorCode;									\
	if (FAILED(hrInternal))											\
	{																\
		ThrowException( ErrorCode, WSTRINGIFY(Text) );	\
	}																\
}	

// 
// Helper definitions for restricting strings managed by AutoPtr subclasses
// to not be allowed to be null.
//
#define NoNullAutoMStr(arg)  NoNullAutoStrImpl(arg, #arg, AutoMStr)
#define NoNullAutoMBStr(arg) NoNullAutoStrImpl(arg, #arg, AutoMBStr)
#define NoNullAutoStrImpl(arg, name, type) NoNull<type>(arg, L##name)