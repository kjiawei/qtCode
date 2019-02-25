// Crypt.cpp: implementation of the CCrypt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "zhaoliang.h"
#include "Crypt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// ����
#define C1 52845
#define C2 22719

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCrypt::CCrypt()
{

}

CCrypt::~CCrypt()
{

}

CString CCrypt::Encrypt(CString S, WORD Key) // ���ܺ���
{
	CString Result,str;
	int i,j;

	Result=S; // ��ʼ������ַ���
	for(i=0; i<S.GetLength(); i++) // ���ζ��ַ����и��ַ����в���
	{
		Result.SetAt(i, S.GetAt(i)^(Key>>8)); // ����Կ��λ�����ַ����
		Key = ((BYTE)Result.GetAt(i)+Key)*C1+C2; // ������һ����Կ
	}
	S=Result; // ������
	Result.Empty(); // ������
	for(i=0; i<S.GetLength(); i++) // �Լ��ܽ������ת��
	{
		j=(BYTE)S.GetAt(i); // ��ȡ�ַ�
		// ���ַ�ת��Ϊ������ĸ����
		str="12"; // ����str����Ϊ2
		str.SetAt(0, 65+j/26);
		str.SetAt(1, 65+j%26);
		Result += str;
	}
	return Result;
}

CString CCrypt::Decrypt(CString S, WORD Key) // ���ܺ���
{
	CString Result,str;
	int i,j;

	Result.Empty(); // ������
	for(i=0; i < S.GetLength()/2; i++) // ���ַ���������ĸһ����д���
	{
		j = ((BYTE)S.GetAt(2*i)-65)*26;
		j += (BYTE)S.GetAt(2*i+1)-65;
		str="1"; // ����str����Ϊ1
		str.SetAt(0, j);
		Result+=str; // ׷���ַ�����ԭ�ַ���
	}
	S=Result; // �����м���
	for(i=0; i<S.GetLength(); i++) // ���ζ��ַ����и��ַ����в���
	{
		Result.SetAt(i, (BYTE)S.GetAt(i)^(Key>>8)); // ����Կ��λ�����ַ����
		Key = ((BYTE)S.GetAt(i)+Key)*C1+C2; // ������һ����Կ
	}
	return Result;
}