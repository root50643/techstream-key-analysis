
undefined4 FUN_10010480(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  char cVar2;
  undefined4 uVar3;
  int extraout_ECX;
  uint uVar4;
  uint uVar5;
  int *this;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  undefined4 *puVar9;
  void *in_stack_0000406c;
  LPCSTR in_stack_0000407c;
  LPCSTR in_stack_00004080;
  LPCSTR in_stack_00004084;
  char *in_stack_00004090;
  char *local_c;
  undefined1 *local_8;
  uint local_4;
  
  local_4 = 0xffffffff;
  local_8 = &LAB_1005e27b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_10048500();
  local_c = PTR_DAT_1007c1f4;
  piVar1 = (int *)(extraout_ECX + 0x74);
  local_8 = (undefined1 *)extraout_ECX;
  FUN_10054e2c(piVar1,in_stack_0000407c);
  FUN_10054e2c((int *)(extraout_ECX + 0x78),in_stack_00004080);
  FUN_10054e2c((void *)(extraout_ECX + 0x7c),in_stack_00004084);
  if (((*(int *)(*piVar1 + -8) == 0) || (*(int *)(*(int *)(extraout_ECX + 0x78) + -8) == 0)) ||
     (in_stack_00004090 == (char *)0x0)) {
    *(undefined4 *)(extraout_ECX + 4) = 1;
    FUN_10054cef((int *)&local_c);
    uVar3 = 0;
  }
  else {
    FUN_10053f85(&local_c,&DAT_1007ab6c);
    local_4 = *(uint *)(local_c + -8);
    uVar4 = 0xffffffff;
    pcVar7 = local_c;
    do {
      pcVar8 = pcVar7;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar8 = pcVar7 + 1;
      cVar2 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar2 != '\0');
    uVar4 = ~uVar4;
    pcVar7 = pcVar8 + -uVar4;
    pcVar8 = &stack0x0000006c;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar8 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar8 = pcVar8 + 1;
    }
    iVar6 = 0;
    if (0 < *(int *)(local_c + -8)) {
      do {
        FUN_1005516a(&local_c,iVar6,0x20);
        iVar6 = iVar6 + 1;
      } while (iVar6 < *(int *)(local_c + -8));
    }
    FUN_10054c7a((int *)&local_c);
    FUN_10003860((undefined4 *)&stack0x00000014);
    FUN_10003890((int *)&stack0x00000014,(int *)&stack0x0000006c,local_4);
    FUN_10003990(&param_1,(int *)&stack0x00000014);
    this = (int *)(extraout_ECX + 0x80);
    FUN_10054c7a(this);
    uVar4 = 0;
    do {
      FUN_10053f85(&local_c,&DAT_1007ab64);
      FUN_100550bb(this,&local_c);
      uVar4 = uVar4 + 1;
    } while (uVar4 < 0x10);
    uVar4 = 0xffffffff;
    pcVar7 = (char *)*this;
    do {
      pcVar8 = pcVar7;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar8 = pcVar7 + 1;
      cVar2 = *pcVar7;
      pcVar7 = pcVar8;
    } while (cVar2 != '\0');
    uVar4 = ~uVar4;
    pcVar7 = pcVar8 + -uVar4;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)in_stack_00004090 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      in_stack_00004090 = in_stack_00004090 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *in_stack_00004090 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      in_stack_00004090 = in_stack_00004090 + 1;
    }
    iVar6 = 0;
    if (0 < *(int *)(*this + -8)) {
      do {
        FUN_1005516a(this,iVar6,0x20);
        iVar6 = iVar6 + 1;
      } while (iVar6 < *(int *)(*this + -8));
    }
    FUN_10054c7a(this);
    iVar6 = 0;
    if (0 < *(int *)(*piVar1 + -8)) {
      do {
        FUN_1005516a(piVar1,iVar6,0x20);
        iVar6 = iVar6 + 1;
      } while (iVar6 < *(int *)(*piVar1 + -8));
    }
    FUN_10054c7a(piVar1);
    iVar6 = 0;
    piVar1 = (int *)((int)local_8 + 0x78);
    if (0 < *(int *)(*(int *)((int)local_8 + 0x78) + -8)) {
      do {
        FUN_1005516a(piVar1,iVar6,0x20);
        iVar6 = iVar6 + 1;
      } while (iVar6 < *(int *)(*piVar1 + -8));
    }
    FUN_10054c7a(piVar1);
    iVar6 = 0;
    if (0 < *(int *)(local_c + -8)) {
      do {
        FUN_1005516a(&local_c,iVar6,0x20);
        iVar6 = iVar6 + 1;
      } while (iVar6 < *(int *)(local_c + -8));
    }
    FUN_10054c7a((int *)&local_c);
    puVar9 = (undefined4 *)&stack0x0000006c;
    for (iVar6 = 0x1000; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar9 = 0;
      puVar9 = puVar9 + 1;
    }
    param_1 = 0;
    param_2 = 0;
    param_3 = 0;
    puVar9 = (undefined4 *)&stack0x00000014;
    for (iVar6 = 0x16; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar9 = 0;
      puVar9 = puVar9 + 1;
    }
    param_4 = 0;
    *(undefined4 *)((int)local_8 + 4) = 0;
    FUN_10054cef((int *)&local_c);
    uVar3 = 1;
  }
  ExceptionList = in_stack_0000406c;
  return uVar3;
}

