/*
  エラーチェックはしていません。
  超適当サンプル。
*/

#include "common.h"
#include "CErrorMessage.h"

#define SUCCESSMESG(b) (b ? "イベントハンドラの登録成功" : "イベントハンドラの解除成功")

bool CreateEventSinkInstance(const IID iid, LPVOID *ppvOut);
bool Advise(IUnknown *pUnk,const IID iid,IDispatch *pDisp,bool bConn);

static DWORD dwCookie = 0L;

//エントリポイント
int main(void)
{
  
  IWebBrowser2	*pIE = NULL;

  // COM初期化
  CoInitialize(NULL);


  if(CoCreateInstance(CLSID_InternetExplorer, NULL, CLSCTX_LOCAL_SERVER,IID_IWebBrowser2,reinterpret_cast<LPVOID*>(&pIE)) == S_OK )
    {
      int i = 0;
      _bstr_t url = _bstr_t("http://www.yahoo.co.jp/");
      _variant_t empty;
      VariantInit(&empty);

      IDispatch* pDisp = NULL;

      //イベントシンクのインスタンスを作成。
      CreateEventSinkInstance(IID_IDispatch,reinterpret_cast<LPVOID*>(&pDisp));

      //イベントシンクを接続
      Advise(pIE,DIID_DWebBrowserEvents2,pDisp,true);
      
      //ヤフーのHPへアクセスして、表示。
      pIE->Navigate(url,&empty,&empty,&empty,&empty);
      pIE->put_Visible(TRUE);

      //とりあえず、MessageBoxで実行をブロックします。
      //ここでIEのリンクをクリックする毎にコンソールに読み込み完了というメッセージがでます。
      MessageBox(NULL,"成功しました。\nOKを押すと終了します。","メッセージ",MB_OK);

      //イベントシンクを切断
      Advise(pIE,DIID_DWebBrowserEvents2,pDisp,false);

      pDisp->Release();
      pIE->Quit();

      // インターフェースを開放
      pIE-> Release();
    }
  else
    {
      CErrorMessage Er;//# = new CErrorMessage();
      Er.Print();
      //delete Er;
    }

  // COM終了処理
  CoUninitialize();

}

//イベントシンクの作成
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

//アドバイス接続
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
            MessageBox(NULL,SUCCESSMESG(bConn),"メッセージ",MB_OK);
          
          pCP->Release();
        }
      
      pCPC->Release();
    }

  return true;
}


