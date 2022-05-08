#define WIN32_LEAN_AND_MEAN

#define DIALOG_TITLE TEXT("メッセージ")
#define MSG_FORMAT reinterpret_cast<LPCVOID>(TEXT("ErrCode:%1!d!\nErrMesg:%2"))


#include <windows.h>
#include <strsafe.h>
#include "CErrorMessage.h"

#include <iostream>

CErrorMessage::CErrorMessage()
{
  std::cout << "Call CErrorMessage()" << std::endl;
  Initialize();
}

CErrorMessage::CErrorMessage(HWND hWnd)
{
  std::cout << "Call CErrorMessage(HWND)" << std::endl;
  Initialize();
  m_hWnd = hWnd;
}

void CErrorMessage::Initialize(void)
{
  m_hWnd = NULL;
  m_lpMsg = NULL;
  m_dwCode = GetLastError();
  
  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                GetLastError(),
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 既定の言語
                reinterpret_cast<LPTSTR>(&m_lpMsg),
                0,
                NULL);
}

CErrorMessage::~CErrorMessage()
{
  std::cout << "Call ~CErrorMessage()" << std::endl;

  if(m_lpMsg)
    LocalFree(m_lpMsg);
}

UINT CErrorMessage::length(void)
{
  UINT cchLength = 0;

  StringCchLength(m_lpMsg,STRSAFE_MAX_CCH,&cchLength);

  return cchLength;
}


UINT CErrorMessage::GetMessage(LPTSTR lpBuf,UINT cbBufLen)
{
  UINT cbLength = 0;
  UINT cbCopySize = 0;

  if(SUCCEEDED(StringCbLength(m_lpMsg,STRSAFE_MAX_CCH * sizeof(TCHAR),&cbLength)))
    {
      cbCopySize = cbLength + sizeof(TCHAR);
      if(lpBuf != NULL)
        {
          if(cbCopySize <= cbBufLen)
            {
              SecureZeroMemory(reinterpret_cast<LPVOID>(lpBuf),cbCopySize);
              CopyMemory(lpBuf,m_lpMsg,cbCopySize);
            }
        }
    }
  
  return cbCopySize;
}

int CErrorMessage::MessageBox(UINT type,LPCTSTR lpcTitle = DIALOG_TITLE)
{
  int retVal = -1;
  LPVOID Arg[2] = {reinterpret_cast<LPVOID>(m_dwCode),reinterpret_cast<LPVOID>(m_lpMsg)};
  LPTSTR lpFormatted = NULL;

  
  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ARGUMENT_ARRAY,
                MSG_FORMAT,
                NULL,
                NULL,
                reinterpret_cast<LPTSTR>(&lpFormatted),
                0,
                reinterpret_cast<va_list*>(Arg));
  
  retVal = m_lpMsg != NULL ? ::MessageBox(m_hWnd,lpFormatted,lpcTitle,type) : -1;

  if(lpFormatted)
    LocalFree(lpFormatted);

  return retVal;
}


DWORD CErrorMessage::GetErrorCode(void)
{
  return m_dwCode;
}

//仮想関数
void CErrorMessage::Print(void)
{
  MessageBox(MB_OK);
}
