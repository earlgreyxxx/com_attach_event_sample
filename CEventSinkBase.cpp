/*
 base class for Dispatch Interface.

  エラーチェックはしていません。
  超適当サンプル。
  
*/
#include "common.h"

CEventSinkBase::CEventSinkBase(void)
{
  RefCounter = 0;
}

CEventSinkBase::~CEventSinkBase()
{

}

//IUnknow Interface
STDMETHODIMP_(ULONG) CEventSinkBase::AddRef(void)
{
  return ++RefCounter;
}
  
STDMETHODIMP_(ULONG) CEventSinkBase::Release(void)
{
  if(--RefCounter == 0)
    delete this;
  
  return RefCounter;
}

STDMETHODIMP CEventSinkBase::QueryInterface(REFIID riid, void **ppvOut)
{
  HRESULT retVal = S_OK;
  
  if(IsEqualIID(riid,IID_IUnknown) || IsEqualIID(riid,IID_IDispatch))
    {
      *ppvOut = reinterpret_cast<IDispatch*>(this);
      this->AddRef();
    }
  else
    {
      *ppvOut = NULL;
      retVal = E_NOTIMPL;
    }
  
  return retVal;
}
  
//IDsipatch Interface
STDMETHODIMP CEventSinkBase::GetTypeInfoCount(UINT* pctinfo)
{
  return E_NOTIMPL;
/*
  if( pctinfo == NULL ) 
    return E_INVALIDARG;
  *pctinfo = 1;
  return S_OK;
  */
}
  
STDMETHODIMP CEventSinkBase::GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo** pptinfo)
{
  return E_NOTIMPL;
}

STDMETHODIMP CEventSinkBase::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames,LCID lcid, DISPID* rgdispid)
{
  return E_NOTIMPL;
}

