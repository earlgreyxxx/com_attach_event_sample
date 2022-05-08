class CErrorMessage
{
  LPTSTR m_lpMsg;
  DWORD m_dwCode;
  HWND m_hWnd;

  //�R�s�[�R���X�g���N�^�Ƒ�����Z�q�͎g�p�֎~
  CErrorMessage(const CErrorMessage& rhs){};
  CErrorMessage& operator=(const CErrorMessage& rhs){};

  void Initialize(void);

public:
  //�R���X�g���N�^���f�X�g���N�^
  CErrorMessage();
  CErrorMessage(HWND hWnd);
  virtual ~CErrorMessage();

  //��������Ԃ�
  UINT length(void);

  //������������o�b�t�@�ɃR�s�[����B
  UINT GetMessage(LPTSTR lpBuf,UINT cbBufLen);

  //�G���[�R�[�h��Ԃ�
  DWORD GetErrorCode(void);
  
  //���b�Z�[�W�{�b�N�X�ŕ\������B
  int MessageBox(UINT type,LPCTSTR lpcTitle);

  //�����������\������B
  virtual void Print(void);

};

