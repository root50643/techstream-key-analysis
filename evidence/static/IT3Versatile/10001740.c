
void EncryptByRotatShiftVariable(int param_1,int param_2,int param_3,undefined1 *param_4)

{
  int iVar1;
  int iVar2;
  
                    /* 0x1740  1  EncryptByRotatShiftVariable */
  if (-1 < param_2) {
    if ((param_1 < 0) || (0x49 < param_1)) {
      param_1 = 0xd;
    }
    if (0 < param_2) {
      iVar2 = param_3 - (int)param_4;
      do {
        iVar1 = (uint)(byte)param_4[iVar2] + param_1;
        if (0x7a < iVar1) {
          iVar1 = iVar1 + -0x4b;
        }
        *param_4 = (char)iVar1;
        param_4 = param_4 + 1;
        param_2 = param_2 + -1;
      } while (param_2 != 0);
    }
  }
  return;
}

