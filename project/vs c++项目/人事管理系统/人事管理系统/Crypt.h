// Crypt.h: interface for the CCrypt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPT_H__FEB16981_A853_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_CRYPT_H__FEB16981_A853_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCrypt  
{
public:
	CCrypt();
	virtual ~CCrypt();
public:
	static CString Encrypt(CString S, WORD Key); // ���ܺ���
	static CString Decrypt(CString S, WORD Key); // ���ܺ���
};

#endif // !defined(AFX_CRYPT_H__FEB16981_A853_11D6_8649_0088CC174723__INCLUDED_)
