
void FUN_00425100(char *param_1,int param_2,undefined4 param_3,char *param_4)

{
  char cVar1;
  undefined4 uVar2;
  char *_Memory;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  int local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004c5252;
  local_10 = ExceptionList;
  local_14 = &stack0xffffffc4;
  ExceptionList = &local_10;
  CString::CString((CString *)&local_18);
  local_8 = 0;
  CString::operator=((CString *)&local_18,&DAT_0055146c);
  local_8 = CONCAT31(local_8._1_3_,1);
  if (param_1 != (char *)0x0) {
    CString::operator=((CString *)&local_18,param_1);
    uVar5 = *(int *)(local_18 + -8) + 1;
    _Memory = malloc(uVar5);
    if (_Memory != (char *)0x0) {
      pcVar3 = _Memory;
      for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        pcVar3[0] = '\0';
        pcVar3[1] = '\0';
        pcVar3[2] = '\0';
        pcVar3[3] = '\0';
        pcVar3 = pcVar3 + 4;
      }
      for (uVar4 = uVar5 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar3 = '\0';
        pcVar3 = pcVar3 + 1;
      }
      uVar2 = *(undefined4 *)(local_18 + -8);
      pcVar3 = CString::GetBuffer((CString *)&local_18,uVar5);
      if (param_2 == 1) {
        Ordinal_1(param_3,uVar2,pcVar3);
      }
      else {
        Ordinal_2(param_3,uVar2,pcVar3,_Memory);
      }
      uVar5 = 0xffffffff;
      pcVar3 = _Memory;
      do {
        pcVar6 = pcVar3;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar6 = pcVar3 + 1;
        cVar1 = *pcVar3;
        pcVar3 = pcVar6;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      pcVar3 = pcVar6 + -uVar5;
      for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)param_4 = *(undefined4 *)pcVar3;
        pcVar3 = pcVar3 + 4;
        param_4 = param_4 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *param_4 = *pcVar3;
        pcVar3 = pcVar3 + 1;
        param_4 = param_4 + 1;
      }
      free(_Memory);
    }
  }
  local_8 = 0xffffffff;
  CString::~CString((CString *)&local_18);
  ExceptionList = local_10;
  return;
}

