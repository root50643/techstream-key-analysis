
CString * FUN_00423330(CString *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                      char *param_5)

{
  int iVar1;
  CString *pCVar2;
  long lVar3;
  int local_24;
  undefined1 *local_20;
  CString local_1c [4];
  char *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_004c4df9;
  local_10 = ExceptionList;
  local_14 = &stack0xffffffc0;
  local_8 = 2;
  ExceptionList = &local_10;
  CString::CString(local_1c);
  local_8._0_1_ = 3;
  CString::CString((CString *)&local_18);
  local_8._0_1_ = 4;
  CString::operator=(local_1c,&DAT_0055146c);
  CString::operator=((CString *)&local_18,&DAT_0055146c);
  local_8._0_1_ = 5;
  iVar1 = _strcmpi(param_5,&DAT_005093e0);
  if (iVar1 == 0) {
    pCVar2 = (CString *)CString::Mid((CString *)&param_2,(int)&local_20,0x1f);
    local_8._0_1_ = 6;
    CString::operator=((CString *)&local_18,pCVar2);
    local_8._0_1_ = 5;
    CString::~CString((CString *)&local_20);
    pCVar2 = (CString *)CString::Mid((CString *)&param_2,(int)&local_20,0xe);
    local_8._0_1_ = 7;
    CString::operator+=((CString *)&local_18,pCVar2);
    local_8._0_1_ = 5;
    CString::~CString((CString *)&local_20);
    pCVar2 = (CString *)CString::Mid((CString *)&param_2,(int)&local_20,0x16);
    local_8._0_1_ = 8;
    CString::operator+=((CString *)&local_18,pCVar2);
  }
  else {
    pCVar2 = (CString *)CString::Mid((CString *)&param_2,(int)&local_20,0x20);
    local_8._0_1_ = 9;
    CString::operator=((CString *)&local_18,pCVar2);
  }
  local_8._0_1_ = 5;
  CString::~CString((CString *)&local_20);
  lVar3 = atol(local_18);
  local_20 = &stack0xffffffb4;
  local_24 = lVar3 * 0x15180;
  FUN_0041f4a0(&local_24);
  pCVar2 = (CString *)FUN_004238c0(&local_20);
  local_8._0_1_ = 10;
  CString::operator=(local_1c,pCVar2);
  local_8 = CONCAT31(local_8._1_3_,5);
  CString::~CString((CString *)&local_20);
  local_8 = 4;
  CString::CString(param_1,local_1c);
  local_8._0_1_ = 3;
  CString::~CString((CString *)&local_18);
  local_8._0_1_ = 2;
  CString::~CString(local_1c);
  local_8._0_1_ = 1;
  CString::~CString((CString *)&param_2);
  local_8 = (uint)local_8._1_3_ << 8;
  CString::~CString((CString *)&param_5);
  ExceptionList = local_10;
  return param_1;
}

