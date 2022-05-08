/*
 base class for Dispatch Interface.
*/

class CEventSinkBase : public IDispatch
{
protected:
  ULONG RefCounter;

public:
  //constructor & destructor
  CEventSinkBase(void);
  virtual ~CEventSinkBase();

  //IUnknow Interface
  virtual STDMETHODIMP_(ULONG) AddRef(void);
  virtual STDMETHODIMP_(ULONG) Release(void);
  virtual STDMETHODIMP QueryInterface(REFIID riid, void **ppvOut);

  //IDsipatch Interface
  virtual STDMETHODIMP GetTypeInfoCount(UINT* pctinfo);
  virtual STDMETHODIMP GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo** pptinfo);
  virtual STDMETHODIMP GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames,LCID lcid, DISPID* rgdispid);
  virtual STDMETHODIMP Invoke(DISPID dispidMember, REFIID riid,LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult,EXCEPINFO* pexcepinfo, UINT* puArgErr) = 0;
};

