
int __thiscall
FUN_00420d80(int param_1,CString *param_2,CString *param_3,char *param_4,CWebService *param_5,
            int param_6,char *param_7)

{
  char cVar1;
  CString *pCVar2;
  undefined4 *puVar3;
  CString *pCVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  char local_34c [2];
  char acStack_34a [254];
  char local_24c [332];
  CMapStringToString local_100 [36];
  CString local_dc [4];
  CString local_d8 [8];
  CString local_d0 [4];
  CString local_cc [4];
  CString local_c8 [4];
  CString local_c4 [4];
  CString local_c0 [4];
  CString local_bc [4];
  CString local_b8 [4];
  CString local_b4 [4];
  undefined4 local_b0;
  char *local_ac;
  CString local_a8 [4];
  CString local_a4 [4];
  undefined4 local_a0;
  CString local_9c [4];
  CString local_98 [4];
  CString local_94 [4];
  CString local_90 [4];
  CString local_8c [4];
  CString local_88 [4];
  CString local_84 [4];
  CString local_80 [4];
  CString local_7c [4];
  CString local_78 [4];
  CString local_74 [4];
  undefined4 local_70;
  CString local_6c [4];
  undefined4 local_68;
  CString local_64 [4];
  undefined4 local_60;
  CString local_5c [4];
  CString local_58 [4];
  CString local_54 [4];
  CString local_50 [4];
  CString local_4c [4];
  CString local_48 [4];
  CString local_44 [4];
  CString local_40 [4];
  CString local_3c [4];
  CString local_38 [4];
  int local_34;
  char *local_30;
  CString local_2c [4];
  undefined4 local_28;
  CString local_24 [4];
  char *local_20;
  char *local_1c;
  char *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004c4814;
  local_10 = ExceptionList;
  local_14 = &stack0xfffffca8;
  ExceptionList = &local_10;
  CString::CString((CString *)&local_20);
  local_8 = 0;
  CString::CString((CString *)&local_28);
  local_8._0_1_ = 1;
  CString::CString((CString *)&local_1c);
  local_8._0_1_ = 2;
  CString::CString((CString *)&local_18);
  local_8._0_1_ = 3;
  CString::CString(local_2c);
  local_8._0_1_ = 4;
  CString::CString(local_24);
  local_8._0_1_ = 5;
  CString::CString(local_dc);
  local_8._0_1_ = 6;
  CString::CString(local_d0);
  local_8._0_1_ = 7;
  FUN_00424590();
  local_8._0_1_ = 8;
  CString::CString((CString *)&local_30);
  local_8._0_1_ = 9;
  CString::CString(local_cc);
  local_8._0_1_ = 10;
  CString::CString(local_c8);
  local_8._0_1_ = 0xb;
  CString::CString(local_c4);
  local_8._0_1_ = 0xc;
  CString::CString(local_c0);
  local_8._0_1_ = 0xd;
  CString::CString(local_bc);
  local_8._0_1_ = 0xe;
  CString::CString(local_b8);
  local_8._0_1_ = 0xf;
  CString::CString(local_b4);
  local_8._0_1_ = 0x10;
  CString::CString((CString *)&local_ac);
  local_8._0_1_ = 0x11;
  CString::CString(local_a8);
  local_8._0_1_ = 0x12;
  CString::CString(local_a4);
  local_8._0_1_ = 0x13;
  CString::CString(local_9c);
  local_8._0_1_ = 0x14;
  CString::CString(local_98);
  local_8._0_1_ = 0x15;
  CString::CString(local_94);
  local_8._0_1_ = 0x16;
  CString::CString(local_90);
  local_8._0_1_ = 0x17;
  CString::CString(local_8c);
  local_8._0_1_ = 0x18;
  CString::CString(local_88);
  local_8._0_1_ = 0x19;
  CString::CString(local_84);
  local_8._0_1_ = 0x1a;
  CString::CString(local_80);
  local_8._0_1_ = 0x1b;
  CString::CString(local_7c);
  local_8._0_1_ = 0x1c;
  CString::CString(local_78);
  local_8._0_1_ = 0x1d;
  CString::CString(local_74);
  local_8._0_1_ = 0x1e;
  CString::CString(local_6c);
  local_8._0_1_ = 0x1f;
  CString::CString(local_64);
  local_8._0_1_ = 0x20;
  CString::CString(local_5c);
  local_8._0_1_ = 0x21;
  CString::CString(local_58);
  local_8._0_1_ = 0x22;
  CString::CString(local_54);
  local_8._0_1_ = 0x23;
  CString::CString(local_50);
  local_8._0_1_ = 0x24;
  CString::CString(local_4c);
  local_8._0_1_ = 0x25;
  CString::CString(local_48);
  local_8._0_1_ = 0x26;
  CString::CString(local_44);
  local_8._0_1_ = 0x27;
  CString::CString(local_40);
  local_8._0_1_ = 0x28;
  CString::CString(local_3c);
  local_8._0_1_ = 0x29;
  CString::CString(local_38);
  local_8 = CONCAT31(local_8._1_3_,0x2a);
  CMapStringToString::CMapStringToString(local_100,10);
  pcVar9 = local_24c;
  for (iVar5 = 0x3f; iVar5 != 0; iVar5 = iVar5 + -1) {
    pcVar9[0] = '\0';
    pcVar9[1] = '\0';
    pcVar9[2] = '\0';
    pcVar9[3] = '\0';
    pcVar9 = pcVar9 + 4;
  }
  pcVar9[0] = '\0';
  pcVar9[1] = '\0';
  pcVar9[2] = '\0';
  local_8._0_1_ = 0x2b;
  pcVar9 = local_34c;
  for (iVar5 = 0x3f; iVar5 != 0; iVar5 = iVar5 + -1) {
    pcVar9[0] = '\0';
    pcVar9[1] = '\0';
    pcVar9[2] = '\0';
    pcVar9[3] = '\0';
    pcVar9 = pcVar9 + 4;
  }
  pcVar9[0] = '\0';
  pcVar9[1] = '\0';
  local_34 = 1;
  pcVar9[2] = '\0';
  CString::operator=((CString *)&local_20,&DAT_0055146c);
  CString::operator=((CString *)&local_28,&DAT_0055146c);
  CString::operator=((CString *)&local_1c,&DAT_0055146c);
  CString::operator=((CString *)&local_18,&DAT_0055146c);
  CString::operator=(local_2c,&DAT_0055146c);
  CString::operator=(local_24,&DAT_0055146c);
  CString::operator=((CString *)&local_30,&DAT_0055146c);
  local_8 = CONCAT31(local_8._1_3_,0x2c);
  if (param_3 == (CString *)0x0) {
    FUN_004194b0(local_cc);
  }
  else {
    CString::operator=(local_cc,param_3);
    CString::operator=(local_c8,param_3 + 4);
    CString::operator=(local_c4,param_3 + 8);
    CString::operator=(local_c0,param_3 + 0xc);
    CString::operator=(local_bc,param_3 + 0x10);
    CString::operator=(local_b8,param_3 + 0x14);
    CString::operator=(local_b4,param_3 + 0x18);
    local_b0 = *(undefined4 *)(param_3 + 0x1c);
    CString::operator=((CString *)&local_ac,param_3 + 0x20);
    CString::operator=(local_a8,param_3 + 0x24);
    CString::operator=(local_a4,param_3 + 0x28);
    local_a0 = *(undefined4 *)(param_3 + 0x2c);
    CString::operator=(local_9c,param_3 + 0x30);
    CString::operator=(local_98,param_3 + 0x34);
    CString::operator=(local_94,param_3 + 0x38);
    CString::operator=(local_90,param_3 + 0x3c);
    CString::operator=(local_8c,param_3 + 0x40);
    CString::operator=(local_88,param_3 + 0x44);
    CString::operator=(local_84,param_3 + 0x48);
    CString::operator=(local_80,param_3 + 0x4c);
    CString::operator=(local_7c,param_3 + 0x50);
    CString::operator=(local_78,param_3 + 0x54);
    CString::operator=(local_74,param_3 + 0x58);
    local_70 = *(undefined4 *)(param_3 + 0x5c);
    CString::operator=(local_6c,param_3 + 0x60);
    local_68 = *(undefined4 *)(param_3 + 100);
    CString::operator=(local_64,param_3 + 0x68);
    local_60 = *(undefined4 *)(param_3 + 0x6c);
    CString::operator=(local_5c,param_3 + 0x70);
    CString::operator=(local_58,param_3 + 0x74);
    CString::operator=(local_54,param_3 + 0x78);
    CString::operator=(local_50,param_3 + 0x7c);
    CString::operator=(local_4c,param_3 + 0x80);
    CString::operator=(local_48,param_3 + 0x84);
    CString::operator=(local_44,param_3 + 0x88);
    CString::operator=(local_40,param_3 + 0x8c);
    CString::operator=(local_3c,param_3 + 0x90);
    CString::operator=(local_38,param_3 + 0x94);
  }
  FUN_004203d0(local_100);
  pCVar2 = (CString *)CString::SpanExcluding(local_a8,(char *)local_d8);
  local_8._0_1_ = 0x2d;
  CString::operator=((CString *)&local_30,pCVar2);
  local_8 = CONCAT31(local_8._1_3_,0x2c);
  CString::~CString(local_d8);
  if (param_5 != (CWebService *)0x0) {
    CString::operator=(local_24,(char *)param_5);
  }
  if (param_4 != (char *)0x0) {
    CString::operator=(local_2c,param_4);
  }
  CoInitialize((LPVOID)0x0);
  iVar5 = _strcmpi(param_7,&DAT_005093e0);
  if (iVar5 == 0) {
    puVar3 = (undefined4 *)operator+((CString *)&param_4,(char *)local_2c);
    param_5 = (CWebService *)(param_1 + 0x10);
    local_8._0_1_ = 0x2e;
    iVar5 = CWebService::TisServiceRegistration
                      (param_5,(char *)*puVar3,local_ac,(char *)0x0,(char *)0x0,(char *)0x0,
                       local_24c);
    local_8 = CONCAT31(local_8._1_3_,0x2c);
    local_34 = iVar5;
    CString::~CString((CString *)&param_4);
  }
  else {
    param_5 = (CWebService *)(param_1 + 0x10);
    iVar5 = CWebService::TisServiceRegistration
                      (param_5,local_ac,local_30,(char *)0x0,(char *)0x0,(char *)0x0,local_24c);
    local_34 = iVar5;
  }
  CoUninitialize();
  uVar6 = 0xffffffff;
  pcVar9 = local_24c;
  do {
    pcVar8 = pcVar9;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar8 = pcVar9 + 1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar8;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pCVar2 = (CString *)(pcVar8 + -uVar6);
  pCVar4 = param_2;
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pCVar4 = *(undefined4 *)pCVar2;
    pCVar2 = pCVar2 + 4;
    pCVar4 = pCVar4 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pCVar4 = *pCVar2;
    pCVar2 = pCVar2 + 1;
    pCVar4 = pCVar4 + 1;
  }
  if (param_6 != 1) goto LAB_00421565;
  CString::Format((CString *)&local_20,(char *)&local_20);
  pcVar9 = param_7;
  if (param_7 == (char *)0x0) {
LAB_0042141d:
    pcVar9 = s_SharedSNA_Kbc9xctNA_00509588;
  }
  else {
    iVar5 = _strcmpi(param_7,&DAT_005095dc);
    if (iVar5 == 0) {
      pcVar9 = s_SharedSEU_Kbc9xctEU_005095c8;
    }
    else {
      iVar5 = _strcmpi(pcVar9,&DAT_005093e0);
      if (iVar5 == 0) {
        pcVar9 = s_SharedSJP_Kbc9xctJP_005095b4;
      }
      else {
        iVar5 = _strcmpi(pcVar9,&DAT_005095b0);
        if (iVar5 != 0) goto LAB_0042141d;
        pcVar9 = s_SharedSOT_Kbc9xctOT_0050959c;
      }
    }
  }
  CString::operator=((CString *)&local_18,pcVar9);
  CMapStringToString::Lookup(local_100,local_18,(CString *)&local_28);
  FUN_00425100(local_28,0,0xd,local_34c);
  CString::Empty((CString *)&local_28);
  CString::operator=((CString *)&local_18,local_34c);
  pcVar9 = local_34c;
  for (iVar5 = 0x3f; iVar5 != 0; iVar5 = iVar5 + -1) {
    pcVar9[0] = '\0';
    pcVar9[1] = '\0';
    pcVar9[2] = '\0';
    pcVar9[3] = '\0';
    pcVar9 = pcVar9 + 4;
  }
  pcVar9[0] = '\0';
  pcVar9[1] = '\0';
  pcVar9[2] = '\0';
  CoInitialize((LPVOID)0x0);
  iVar5 = _strcmpi(param_7,&DAT_005093e0);
  if (iVar5 == 0) {
    pCVar2 = (CString *)operator+((CString *)&param_7,(CString *)&local_18);
    local_8._0_1_ = 0x2f;
    CString::operator=((CString *)&local_1c,pCVar2);
    local_8 = CONCAT31(local_8._1_3_,0x2c);
    CString::~CString((CString *)&param_7);
    CString::operator+=((CString *)&local_20,(CString *)&local_30);
    pcVar9 = local_20;
    pCVar4 = (CString *)0x0;
    pCVar2 = param_2;
  }
  else {
    pCVar4 = (CString *)operator+((CString *)&param_4,(CString *)&local_18);
    pCVar2 = local_24;
    local_8._0_1_ = 0x30;
    pCVar4 = (CString *)operator+((CString *)&param_7,pCVar4);
    local_8._0_1_ = 0x31;
    CString::operator=((CString *)&local_1c,pCVar4);
    local_8._0_1_ = 0x30;
    CString::~CString((CString *)&param_7);
    local_8 = CONCAT31(local_8._1_3_,0x2c);
    CString::~CString((CString *)&param_4);
    pcVar9 = (char *)0x0;
    local_1c = local_20;
    pCVar4 = param_2;
  }
  iVar5 = CWebService::TisServiceRegistration
                    (param_5,local_1c,pcVar9,(char *)0x0,(char *)0x0,(char *)pCVar4,(char *)pCVar2);
  local_34 = iVar5;
  CoUninitialize();
  CString::Empty((CString *)&local_18);
  CString::Empty((CString *)&local_1c);
LAB_00421565:
  local_8 = 0x2a;
  CMapStringToString::~CMapStringToString(local_100);
  local_8._0_1_ = 0x53;
  CString::~CString(local_38);
  local_8._0_1_ = 0x52;
  CString::~CString(local_3c);
  local_8._0_1_ = 0x51;
  CString::~CString(local_40);
  local_8._0_1_ = 0x50;
  CString::~CString(local_44);
  local_8._0_1_ = 0x4f;
  CString::~CString(local_48);
  local_8._0_1_ = 0x4e;
  CString::~CString(local_4c);
  local_8._0_1_ = 0x4d;
  CString::~CString(local_50);
  local_8._0_1_ = 0x4c;
  CString::~CString(local_54);
  local_8._0_1_ = 0x4b;
  CString::~CString(local_58);
  local_8._0_1_ = 0x4a;
  CString::~CString(local_5c);
  local_8._0_1_ = 0x49;
  CString::~CString(local_64);
  local_8._0_1_ = 0x48;
  CString::~CString(local_6c);
  local_8._0_1_ = 0x47;
  CString::~CString(local_74);
  local_8._0_1_ = 0x46;
  CString::~CString(local_78);
  local_8._0_1_ = 0x45;
  CString::~CString(local_7c);
  local_8._0_1_ = 0x44;
  CString::~CString(local_80);
  local_8._0_1_ = 0x43;
  CString::~CString(local_84);
  local_8._0_1_ = 0x42;
  CString::~CString(local_88);
  local_8._0_1_ = 0x41;
  CString::~CString(local_8c);
  local_8._0_1_ = 0x40;
  CString::~CString(local_90);
  local_8._0_1_ = 0x3f;
  CString::~CString(local_94);
  local_8._0_1_ = 0x3e;
  CString::~CString(local_98);
  local_8._0_1_ = 0x3d;
  CString::~CString(local_9c);
  local_8._0_1_ = 0x3c;
  CString::~CString(local_a4);
  local_8._0_1_ = 0x3b;
  CString::~CString(local_a8);
  local_8._0_1_ = 0x3a;
  CString::~CString((CString *)&local_ac);
  local_8._0_1_ = 0x39;
  CString::~CString(local_b4);
  local_8._0_1_ = 0x38;
  CString::~CString(local_b8);
  local_8._0_1_ = 0x37;
  CString::~CString(local_bc);
  local_8._0_1_ = 0x36;
  CString::~CString(local_c0);
  local_8._0_1_ = 0x35;
  CString::~CString(local_c4);
  local_8._0_1_ = 0x34;
  CString::~CString(local_c8);
  local_8._0_1_ = 9;
  CString::~CString(local_cc);
  local_8._0_1_ = 8;
  CString::~CString((CString *)&local_30);
  local_8._0_1_ = 7;
  FUN_00424600();
  local_8._0_1_ = 6;
  CString::~CString(local_d0);
  local_8._0_1_ = 5;
  CString::~CString(local_dc);
  local_8._0_1_ = 4;
  CString::~CString(local_24);
  local_8._0_1_ = 3;
  CString::~CString(local_2c);
  local_8._0_1_ = 2;
  CString::~CString((CString *)&local_18);
  local_8._0_1_ = 1;
  CString::~CString((CString *)&local_1c);
  local_8 = (uint)local_8._1_3_ << 8;
  CString::~CString((CString *)&local_28);
  local_8 = 0xffffffff;
  CString::~CString((CString *)&local_20);
  ExceptionList = local_10;
  return iVar5;
}

