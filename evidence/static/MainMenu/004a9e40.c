
uint FUN_004a9e40(char *param_1,char *param_2,LPCSTR param_3,CMapStringToString *param_4,int param_5
                 )

{
  HANDLE hFindFile;
  FARPROC pFVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  DWORD DVar5;
  CString *pCVar6;
  int extraout_ECX;
  int iVar7;
  char *unaff_ESI;
  CHAR *pCVar8;
  char *pcVar9;
  char acStackY_34de4 [155352];
  char local_ef0c [51204];
  CHAR local_2708 [2084];
  CHAR local_1ee4 [2084];
  char local_16c0 [3108];
  char local_a9c [1024];
  char local_69c [1024];
  _WIN32_FIND_DATAA local_29c;
  char local_15c [264];
  CString local_54 [8];
  FARPROC local_4c;
  uint local_44;
  uint local_40;
  CString local_3c [4];
  uint local_38;
  uint local_34;
  char *pcVar10;
  uint uVar11;
  uint uVar12;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004d7c0a;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_004be8a0();
  iVar2 = extraout_ECX;
  CString::CString((CString *)&stack0xffffffe4);
  local_8 = 0;
  CString::CString((CString *)&stack0xffffffd8);
  local_8._0_1_ = 1;
  CString::CString((CString *)&stack0xffffffdc);
  local_8._0_1_ = 2;
  CString::CString((CString *)&stack0xffffffd4);
  pcVar10 = &DAT_0055146c;
  pCVar8 = local_1ee4;
  for (iVar7 = 0x208; iVar7 != 0; iVar7 = iVar7 + -1) {
    pCVar8[0] = '\0';
    pCVar8[1] = '\0';
    pCVar8[2] = '\0';
    pCVar8[3] = '\0';
    pCVar8 = pCVar8 + 4;
  }
  pCVar8[0] = '\0';
  pCVar8[1] = '\0';
  pCVar8[2] = '\0';
  local_8 = CONCAT31(local_8._1_3_,3);
  pCVar8 = local_2708;
  for (iVar7 = 0x209; iVar7 != 0; iVar7 = iVar7 + -1) {
    pCVar8[0] = '\0';
    pCVar8[1] = '\0';
    pCVar8[2] = '\0';
    pCVar8[3] = '\0';
    pCVar8 = pCVar8 + 4;
  }
  pcVar9 = local_15c;
  for (iVar7 = 0x41; iVar7 != 0; iVar7 = iVar7 + -1) {
    pcVar9[0] = '\0';
    pcVar9[1] = '\0';
    pcVar9[2] = '\0';
    pcVar9[3] = '\0';
    pcVar9 = pcVar9 + 4;
  }
  pcVar9 = acStackY_34de4;
  for (iVar7 = 0x97b5; iVar7 != 0; iVar7 = iVar7 + -1) {
    pcVar9[0] = '\0';
    pcVar9[1] = '\0';
    pcVar9[2] = '\0';
    pcVar9[3] = '\0';
    pcVar9 = pcVar9 + 4;
  }
  pcVar9[0] = '\0';
  pcVar9[1] = '\0';
  pcVar9[2] = '\0';
  local_34 = 0;
  pcVar9 = local_16c0;
  for (iVar7 = 0x308; iVar7 != 0; iVar7 = iVar7 + -1) {
    pcVar9[0] = '\0';
    pcVar9[1] = '\0';
    pcVar9[2] = '\0';
    pcVar9[3] = '\0';
    pcVar9 = pcVar9 + 4;
  }
  pcVar9[0] = '\0';
  pcVar9[1] = '\0';
  pcVar9[2] = '\0';
  uVar11 = 0;
  pcVar9 = local_a9c;
  for (iVar7 = 0x100; iVar7 != 0; iVar7 = iVar7 + -1) {
    pcVar9[0] = '\0';
    pcVar9[1] = '\0';
    pcVar9[2] = '\0';
    pcVar9[3] = '\0';
    pcVar9 = pcVar9 + 4;
  }
  pcVar9 = local_ef0c;
  for (iVar7 = 0x3200; iVar7 != 0; iVar7 = iVar7 + -1) {
    pcVar9[0] = '\0';
    pcVar9[1] = '\0';
    pcVar9[2] = '\0';
    pcVar9[3] = '\0';
    pcVar9 = pcVar9 + 4;
  }
  *pcVar9 = '\0';
  pcVar9 = local_69c;
  for (iVar7 = 0x100; iVar7 != 0; iVar7 = iVar7 + -1) {
    pcVar9[0] = '\0';
    pcVar9[1] = '\0';
    pcVar9[2] = '\0';
    pcVar9[3] = '\0';
    pcVar9 = pcVar9 + 4;
  }
  CString::operator=((CString *)&stack0xffffffe4,pcVar10);
  CString::operator=((CString *)&stack0xffffffd8,&DAT_0055146c);
  CString::operator=((CString *)&stack0xffffffdc,&DAT_0055146c);
  CString::operator=((CString *)&stack0xffffffd4,&DAT_0055146c);
  local_8 = CONCAT31(local_8._1_3_,4);
  hFindFile = FindFirstFileA(param_3,&local_29c);
  if (hFindFile == (HANDLE)0xffffffff) {
    uVar12 = 0;
  }
  else {
    FindClose(hFindFile);
    if (((byte)local_29c.dwFileAttributes & 0x10) == 0) {
      iVar7 = FUN_004a9da0();
      if (iVar7 == 0) {
        pFVar1 = GetProcAddress(*(HMODULE *)(iVar2 + 0xc),s_TDRAuthorize_0051455c);
        if (pFVar1 == (FARPROC)0x0) {
          uVar12 = 0;
        }
        else {
          uVar12 = (*pFVar1)();
          uVar12 = uVar12 & 0xff;
          if (uVar12 == 1) {
            pFVar1 = GetProcAddress(*(HMODULE *)(iVar2 + 0xc),
                                    s_TDRGetPrivateProfileSectionNames_0051452c);
            if (pFVar1 == (FARPROC)0x0) {
              uVar12 = 0;
            }
            else {
              local_4c = GetProcAddress(*(HMODULE *)(iVar2 + 0xc),
                                        s_TDRGetPrivateProfileSection_00514510);
              if (local_4c == (FARPROC)0x0) {
                uVar12 = 0;
              }
              else {
                strncpy(local_15c,param_3,0x103);
                local_40 = (*pFVar1)();
                if (local_40 == 0) {
                  uVar12 = 0;
                }
                else {
                  local_38 = 0;
                  while (local_38 < local_40) {
                    pcVar10 = local_ef0c + local_38;
                    iVar2 = strncmp(pcVar10,&DAT_0055146c,1);
                    if (iVar2 == 0) {
                      if (uVar11 < 0x400) {
                        pcVar10 = acStackY_34de4;
                        for (iVar2 = 0x97b5; iVar2 != 0; iVar2 = iVar2 + -1) {
                          pcVar10[0] = '\0';
                          pcVar10[1] = '\0';
                          pcVar10[2] = '\0';
                          pcVar10[3] = '\0';
                          pcVar10 = pcVar10 + 4;
                        }
                        pcVar10[0] = '\0';
                        pcVar10[1] = '\0';
                        pcVar10[2] = '\0';
                        local_34 = 0x4aa0bc;
                        local_44 = (*local_4c)();
                        if (local_44 != 0) {
                          uVar11 = 0;
                          while (uVar4 = local_34, uVar11 < local_44) {
                            iVar2 = strncmp(acStackY_34de4 + uVar11,&DAT_0055146c,1);
                            if (iVar2 == 0) {
                              if ((uVar4 < 0xc23) &&
                                 (pcVar10 = strpbrk(local_16c0,&DAT_0051450c),
                                 pcVar10 != (char *)0x0)) {
                                uVar3 = (int)pcVar10 - (int)local_16c0;
                                if ((uVar3 != 0) &&
                                   (((uVar4 - uVar3 != 1 && (uVar3 < 0x400)) &&
                                    ((uVar4 - uVar3) - 1 < 0x823)))) {
                                  pcVar10 = &DAT_0055146c;
                                  pCVar8 = local_1ee4;
                                  for (iVar2 = 0x208; iVar2 != 0; iVar2 = iVar2 + -1) {
                                    pCVar8[0] = '\0';
                                    pCVar8[1] = '\0';
                                    pCVar8[2] = '\0';
                                    pCVar8[3] = '\0';
                                    pCVar8 = pCVar8 + 4;
                                  }
                                  pCVar8[0] = '\0';
                                  pCVar8[1] = '\0';
                                  pCVar8[2] = '\0';
                                  pCVar8 = local_2708;
                                  for (iVar2 = 0x209; iVar2 != 0; iVar2 = iVar2 + -1) {
                                    pCVar8[0] = '\0';
                                    pCVar8[1] = '\0';
                                    pCVar8[2] = '\0';
                                    pCVar8[3] = '\0';
                                    pCVar8 = pCVar8 + 4;
                                  }
                                  pcVar9 = local_a9c;
                                  for (iVar2 = 0x100; iVar2 != 0; iVar2 = iVar2 + -1) {
                                    pcVar9[0] = '\0';
                                    pcVar9[1] = '\0';
                                    pcVar9[2] = '\0';
                                    pcVar9[3] = '\0';
                                    pcVar9 = pcVar9 + 4;
                                  }
                                  iVar2 = 0;
                                  CString::operator=((CString *)&stack0xffffffe4,pcVar10);
                                  CString::operator=((CString *)&stack0xffffffd8,&DAT_0055146c);
                                  CString::operator=((CString *)&stack0xffffffdc,&DAT_0055146c);
                                  CString::operator=((CString *)&stack0xffffffd4,&DAT_0055146c);
                                  for (uVar4 = 0; uVar4 < uVar3; uVar4 = uVar4 + 1) {
                                    local_a9c[uVar4] = local_16c0[uVar4];
                                  }
                                  while (uVar3 + 1 < local_34) {
                                    local_1ee4[iVar2] = local_16c0[uVar3 + 1];
                                    iVar2 = iVar2 + 1;
                                    uVar3 = uVar3 + 1;
                                  }
                                  DVar5 = ExpandEnvironmentStringsA(local_1ee4,local_2708,0x824);
                                  if ((DVar5 != 0) && (DVar5 < 0x824)) {
                                    CString::operator=((CString *)&stack0xffffffd4,local_69c);
                                    CString::operator=((CString *)&stack0xffffffd8,local_a9c);
                                    pcVar10 = &DAT_00509280;
                                    pCVar6 = (CString *)operator+(local_3c,&stack0xffffffd4);
                                    local_8._0_1_ = 5;
                                    local_34 = 0x4aa267;
                                    pCVar6 = (CString *)operator+(local_54,pCVar6);
                                    local_8._0_1_ = 6;
                                    CString::operator=((CString *)&stack0xffffffdc,pCVar6);
                                    local_8._0_1_ = 5;
                                    CString::~CString(local_54);
                                    local_8 = CONCAT31(local_8._1_3_,4);
                                    CString::~CString(local_3c);
                                    CString::operator=((CString *)&stack0xffffffe4,local_2708);
                                    local_34 = 0x4aa2ac;
                                    CString::Replace((CString *)&stack0xffffffe4,&DAT_0050a0bc,
                                                     param_1);
                                    local_34 = 0x4aa2bd;
                                    CString::Replace((CString *)&stack0xffffffe4,&DAT_0050a0a0,
                                                     param_2);
                                    pCVar6 = CMapStringToString::operator[](param_4,pcVar10);
                                    CString::operator=(pCVar6,unaff_ESI);
                                  }
                                }
                              }
                              pcVar10 = local_16c0;
                              for (iVar2 = 0x308; iVar2 != 0; iVar2 = iVar2 + -1) {
                                pcVar10[0] = '\0';
                                pcVar10[1] = '\0';
                                pcVar10[2] = '\0';
                                pcVar10[3] = '\0';
                                pcVar10 = pcVar10 + 4;
                              }
                              pcVar10[0] = '\0';
                              pcVar10[1] = '\0';
                              pcVar10[2] = '\0';
                              uVar11 = uVar11 + 1;
                              local_34 = 0;
                            }
                            else {
                              if (uVar4 < 0xc22) {
                                local_16c0[uVar4] = acStackY_34de4[uVar11];
                              }
                              local_34 = uVar4 + 1;
                              uVar11 = uVar11 + 1;
                            }
                          }
                        }
                      }
                      uVar11 = 0;
                      pcVar10 = local_69c;
                      for (iVar2 = 0x100; iVar2 != 0; iVar2 = iVar2 + -1) {
                        pcVar10[0] = '\0';
                        pcVar10[1] = '\0';
                        pcVar10[2] = '\0';
                        pcVar10[3] = '\0';
                        pcVar10 = pcVar10 + 4;
                      }
                      local_38 = local_38 + 1;
                    }
                    else {
                      if (uVar11 < 0x3ff) {
                        local_69c[uVar11] = *pcVar10;
                      }
                      uVar11 = uVar11 + 1;
                      local_38 = local_38 + 1;
                    }
                  }
                }
                if (param_5 == 1) {
                  pCVar6 = CMapStringToString::operator[](param_4,s_SharedSNA_Kbc9xctNA_00509588);
                  CString::operator=(pCVar6,s_W_R__BTnx_a9_005144fc);
                  pCVar6 = CMapStringToString::operator[](param_4,s_SharedSEU_Kbc9xctEU_005095c8);
                  CString::operator=(pCVar6,s_Z__4>7Bv5_>pxEB_CB_005144e8);
                  pCVar6 = CMapStringToString::operator[](param_4,s_SharedSJP_Kbc9xctJP_005095b4);
                  CString::operator=(pCVar6,s__cpvn14yyrr66>>>E_005144d4);
                  pCVar6 = CMapStringToString::operator[](param_4,s_SharedSOT_Kbc9xctOT_0050959c);
                  CString::operator=(pCVar6,s__XRAE_005144cc);
                }
              }
            }
          }
        }
      }
      else {
        uVar12 = 0;
      }
    }
    else {
      uVar12 = 0;
    }
  }
  FUN_004a9e00();
  local_8 = 2;
  CString::~CString((CString *)&stack0xffffffd4);
  local_8._0_1_ = 1;
  CString::~CString((CString *)&stack0xffffffdc);
  local_8 = (uint)local_8._1_3_ << 8;
  CString::~CString((CString *)&stack0xffffffd8);
  local_8 = 0xffffffff;
  CString::~CString((CString *)&stack0xffffffe4);
  ExceptionList = local_10;
  return uVar12;
}

