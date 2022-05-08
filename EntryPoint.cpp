/*
  �G���[�`�F�b�N�͂��Ă��܂���B
  ���K���T���v���B
*/

#include "common.h"
#include "CErrorMessage.h"

#define SUCCESSMESG(b) (b ? "�C�x���g�n���h���̓o�^����" : "�C�x���g�n���h���̉�������")

bool CreateEventSinkInstance(const IID iid, LPVOID *ppvOut);
bool Advise(IUnknown *pUnk,const IID iid,IDispatch *pDisp,bool bConn);

static DWORD dwCookie = 0L;

//�G���g���|�C���g
int main(void)
{
  
  IWebBrowser2	*pIE = NULL;

  // COM������
  CoInitialize(NULL);


  if(CoCreateInstance(CLSID_InternetExplorer, NULL, CLSCTX_LOCAL_SERVER,IID_IWebBrowser2,reinterpret_cast<LPVOID*>(&pIE)) == S_OK )
    {
      int i = 0;
      _bstr_t url = _bstr_t("http://www.yahoo.co.jp/");
      _variant_t empty;
      VariantInit(&empty);

      IDispatch* pDisp = NULL;

      //�C�x���g�V���N�̃C���X�^���X���쐬�B
      CreateEventSinkInstance(IID_IDispatch,reinterpret_cast<LPVOID*>(&pDisp));

      //�C�x���g�V���N��ڑ�
      Advise(pIE,DIID_DWebBrowserEvents2,pDisp,true);
      
      //���t�[��HP�փA�N�Z�X���āA�\���B
      pIE->Navigate(url,&empty,&empty,&empty,&empty);
      pIE->put_Visible(TRUE);

      //�Ƃ肠�����AMessageBox�Ŏ��s���u���b�N���܂��B
      //������IE�̃����N���N���b�N���閈�ɃR���\�[���ɓǂݍ��݊����Ƃ������b�Z�[�W���ł܂��B
      MessageBox(NULL,"�������܂����B\nOK�������ƏI�����܂��B","���b�Z�[�W",MB_OK);

      //�C�x���g�V���N��ؒf
      Advise(pIE,DIID_DWebBrowserEvents2,pDisp,false);

      pDisp->Release();
      pIE->Quit();

      // �C���^�[�t�F�[�X���J��
      pIE-> Release();
    }
  else
    {
      CErrorMessage Er;//# = new CErrorMessage();
      Er.Print();
      //delete Er;
    }

  // COM�I������
  CoUninitialize();

}

//�C�x���g�V���N�̍쐬
bool CreateEventSinkInstance(const IID iid, LPVOID *ppvOut)
{
  CEventSink *pSink = new CEventSink();
  if(!pSink)
    return false;

  if(SUCCEEDED(pSink->QueryInterface(iid,ppvOut)))
    return true;
  else
    delete pSink;

  return false;
}

//�A�h�o�C�X�ڑ�
bool Advise(IUnknown *pUnk,const IID iid,IDispatch *pDisp,bool bConn)
{
  bool bRet = false;
  HRESULT hr = NULL;
  IConnectionPointContainer *pCPC = NULL;
  IConnectionPoint *pCP = NULL;
  
  if(!pUnk)
    return false;
  
  hr = pUnk->QueryInterface(IID_IConnectionPointContainer,reinterpret_cast<LPVOID*>(&pCPC));
  if(SUCCEEDED(hr))
    {
      hr = pCPC->FindConnectionPoint(iid,&pCP);
      if(SUCCEEDED(hr))
        {
          hr = bConn ? pCP->Advise(reinterpret_cast<IUnknown*>(pDisp),&dwCookie) : pCP->Unadvise(dwCookie);
          if(SUCCEEDED(hr))
            MessageBox(NULL,SUCCESSMESG(bConn),"���b�Z�[�W",MB_OK);
          
          pCP->Release();
        }
      
      pCPC->Release();
    }

  return true;
}


