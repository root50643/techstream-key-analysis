
void FUN_004b6110(char *param_1,undefined4 *param_2)

{
  int iVar1;
  ushort uVar2;
  ushort uVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  code *pcVar7;
  undefined4 uVar8;
  undefined4 local_38;
  int local_34;
  undefined4 local_30;
  uint local_2c;
  int local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004d8d32;
  local_10 = ExceptionList;
  local_14 = &stack0xffffffbc;
  ExceptionList = &local_10;
  CString::CString((CString *)&local_18);
  local_8 = 0;
  CString::operator=((CString *)&local_18,&DAT_0055146c);
  local_2c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_8 = CONCAT31(local_8._1_3_,1);
  CString::operator=((CString *)&local_18,param_1);
  if (param_2 == (undefined4 *)0x0) goto LAB_004b62ff;
  iVar1 = *(int *)(local_18 + -8);
  pcVar7 = atoi_exref;
  if (iVar1 < 8) {
LAB_004b624b:
    puVar4 = param_2;
    if (0xd < iVar1) {
      uVar8 = 2;
      puVar6 = (undefined4 *)CString::Mid((CString *)&local_18,(int)&param_2,8);
      uVar2 = (*pcVar7)(*puVar6,uVar8);
      CString::~CString((CString *)&param_2);
      if (uVar2 < 0x18) {
        uVar8 = 2;
        puVar6 = (undefined4 *)CString::Mid((CString *)&local_18,(int)&param_2,10);
        uVar3 = (*pcVar7)(*puVar6,uVar8);
        CString::~CString((CString *)&param_2);
        if (uVar3 < 0x3c) {
          uVar8 = 2;
          local_30 = CONCAT22(uVar3,uVar2);
          puVar6 = (undefined4 *)CString::Mid((CString *)&local_18,(int)&param_2,0xc);
          uVar2 = (*pcVar7)(*puVar6,uVar8);
          CString::~CString((CString *)&param_2);
          if (uVar2 < 0x3c) {
            local_2c = (uint)uVar2;
            goto LAB_004b62eb;
          }
        }
      }
      goto LAB_004b62e0;
    }
  }
  else {
    puVar4 = (undefined4 *)CString::Mid((CString *)&local_18,(int)&param_1,0);
    pcVar7 = atoi_exref;
    iVar5 = atoi((char *)*puVar4);
    CString::~CString((CString *)&param_1);
    uVar2 = (ushort)iVar5;
    puVar4 = param_2;
    if ((uVar2 < 0x7f6) && (0x7b1 < uVar2)) {
      puVar4 = (undefined4 *)CString::Mid((CString *)&local_18,(int)&param_1,4);
      iVar5 = atoi((char *)*puVar4);
      CString::~CString((CString *)&param_1);
      uVar3 = (ushort)iVar5;
      puVar4 = param_2;
      if ((uVar3 < 0xd) && (uVar3 != 0)) {
        local_38 = CONCAT22(uVar3,uVar2);
        puVar4 = (undefined4 *)CString::Mid((CString *)&local_18,(int)&param_1,6);
        local_34 = atoi((char *)*puVar4);
        CString::~CString((CString *)&param_1);
        puVar4 = param_2;
        if (((ushort)local_34 < 0x20) && ((ushort)local_34 != 0)) {
          local_34 = local_34 << 0x10;
          goto LAB_004b624b;
        }
      }
    }
LAB_004b62e0:
    local_2c = 0;
    local_38 = 0;
    local_34 = 0;
    local_30 = 0;
  }
LAB_004b62eb:
  *puVar4 = local_38;
  puVar4[1] = local_34;
  puVar4[2] = local_30;
  puVar4[3] = local_2c;
LAB_004b62ff:
  local_8 = 0xffffffff;
  CString::~CString((CString *)&local_18);
  ExceptionList = local_10;
  return;
}

