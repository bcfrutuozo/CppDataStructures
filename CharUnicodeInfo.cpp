//
// Created by bcfrutuozo on 03/04/2022.
//
#include "CharUnicodeInfo.h"

unsigned short *CharUnicodeInfo::pCategoryLevel1Index = nullptr;
char *CharUnicodeInfo::pCategoriesValue = nullptr;
unsigned short *CharUnicodeInfo::pNumericLevel1Index = nullptr;
char *CharUnicodeInfo::pNumericValues = nullptr;
CharUnicodeInfo::DigitValues *CharUnicodeInfo::pDigitValues = nullptr;
const bool CharUnicodeInfo::IsInitialized = CharUnicodeInfo::InitTable();
