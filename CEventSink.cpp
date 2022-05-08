/*
  Event Sink implementation.

  �G���[�`�F�b�N�͂��Ă��܂���B
  ���K���T���v���B
  
*/

#include "common.h"
#include <iostream>

STDMETHODIMP CEventSink::Invoke(DISPID dispidMember, REFIID riid,LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult,EXCEPINFO* pexcepinfo, UINT* puArgErr)
{
  //�y�[�W�ǂݍ��݊����̃C�x���g��������AonLoad()���R�[���B
  if(dispidMember == DISPID_NAVIGATECOMPLETE2)
    onLoad();
  
  return S_OK;
}

void CEventSink::onLoad()
{
  std::cout << "�Ǎ����I�����܂����B" << std::endl;
}

