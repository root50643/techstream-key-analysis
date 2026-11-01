
void FUN_10003890(int *param_1,int *param_2,uint param_3)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  
  piVar1 = param_1;
  uVar3 = param_1[4];
  uVar2 = uVar3 + param_3 * 8;
  param_1[4] = uVar2;
  if (uVar2 < uVar3) {
    param_1[5] = param_1[5] + 1;
  }
  uVar2 = uVar3 >> 3 & 0x3f;
  param_1[5] = param_1[5] + (param_3 >> 0x1d);
  if (uVar2 != 0) {
    piVar6 = (int *)(uVar2 + 0x18 + (int)param_1);
    uVar2 = 0x40 - uVar2;
    if (param_3 < uVar2) goto LAB_1000397a;
    piVar5 = param_2;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *piVar6 = *piVar5;
      piVar5 = piVar5 + 1;
      piVar6 = piVar6 + 1;
    }
    for (uVar3 = uVar2 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(char *)piVar6 = (char)*piVar5;
      piVar5 = (int *)((int)piVar5 + 1);
      piVar6 = (int *)((int)piVar6 + 1);
    }
    FUN_100042c0(param_1 + 6,0x10);
    FUN_10003a50(param_1,param_1 + 6);
    param_2 = (int *)((int)param_2 + uVar2);
    param_3 = param_3 - uVar2;
  }
  if (0x3f < param_3) {
    param_1 = (int *)(param_3 >> 6);
    do {
      piVar6 = param_2;
      piVar5 = piVar1 + 6;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *piVar5 = *piVar6;
        piVar6 = piVar6 + 1;
        piVar5 = piVar5 + 1;
      }
      FUN_100042c0(piVar1 + 6,0x10);
      FUN_10003a50(piVar1,piVar1 + 6);
      param_2 = param_2 + 0x10;
      param_3 = param_3 - 0x40;
      param_1 = (int *)((int)param_1 + -1);
    } while (param_1 != (int *)0x0);
  }
  piVar6 = piVar1 + 6;
LAB_1000397a:
  for (uVar2 = param_3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *piVar6 = *param_2;
    param_2 = param_2 + 1;
    piVar6 = piVar6 + 1;
  }
  for (uVar2 = param_3 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(char *)piVar6 = (char)*param_2;
    param_2 = (int *)((int)param_2 + 1);
    piVar6 = (int *)((int)piVar6 + 1);
  }
  return;
}

