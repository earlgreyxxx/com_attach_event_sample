/*
  Event Sink declation
*/
#ifndef __CEVENTSINKBASE__
 #include "CEventSinkBase.h"
 #define __CEVENTSINKBASE__
#endif

class CEventSink : public CEventSinkBase
{
  //event handler
  void onLoad();
    
public:
  virtual STDMETHODIMP Invoke(DISPID dispidMember, REFIID riid,LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult,EXCEPINFO* pexcepinfo, UINT* puArgErr);

};


