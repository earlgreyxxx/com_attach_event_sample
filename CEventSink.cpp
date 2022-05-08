/*
  Event Sink implementation.

  エラーチェックはしていません。
  超適当サンプル。
  
*/

#include "common.h"
#include <iostream>

STDMETHODIMP CEventSink::Invoke(DISPID dispidMember, REFIID riid,LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult,EXCEPINFO* pexcepinfo, UINT* puArgErr)
{
  //ページ読み込み完了のイベントだったら、onLoad()をコール。
  if(dispidMember == DISPID_NAVIGATECOMPLETE2)
    onLoad();
  
  return S_OK;
}

void CEventSink::onLoad()
{
  std::cout << "読込が終了しました。" << std::endl;
}

