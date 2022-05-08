class CErrorMessage
{
  LPTSTR m_lpMsg;
  DWORD m_dwCode;
  HWND m_hWnd;

  //コピーコンストラクタと代入演算子は使用禁止
  CErrorMessage(const CErrorMessage& rhs){};
  CErrorMessage& operator=(const CErrorMessage& rhs){};

  void Initialize(void);

public:
  //コンストラクタ＆デストラクタ
  CErrorMessage();
  CErrorMessage(HWND hWnd);
  virtual ~CErrorMessage();

  //文字数を返す
  UINT length(void);

  //内部文字列をバッファにコピーする。
  UINT GetMessage(LPTSTR lpBuf,UINT cbBufLen);

  //エラーコードを返す
  DWORD GetErrorCode(void);
  
  //メッセージボックスで表示する。
  int MessageBox(UINT type,LPCTSTR lpcTitle);

  //内部文字列を表示する。
  virtual void Print(void);

};

