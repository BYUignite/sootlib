# Sootlib Code Review - Bug Summary

**Date:** March 6, 2026  
**Repository:** BYUignite/sootlib  
**Branch:** master  
**Review Type:** Comprehensive source code audit

---

## Summary

A systematic code review of the sootlib soot modeling library identified 7 bugs across the source files in the `src/` directory. The issues range from critical errors affecting numerical accuracy to minor code quality concerns.

---

## Bug #1: Incorrect Mass Variable in FUCHS Coagulation Model

**File:** `src/coagulationModels/coagulationModel_FUCHS.cc`  
**Lines:** 32-33  
**Classification:** Critical - Produces incorrect numerical results

**Issue:** The diameter of particle 2 (`d2`) is calculated using the mass of particle 1 (`m1`) instead of particle 2 (`m2`).

**Current Code:**
```cpp
double d1 = pow(6.*m1/(M_PI*rhoSoot), onethird);
double d2 = pow(6.*m1/(M_PI*rhoSoot), onethird);  // Uses m1 instead of m2
```

**Expected Code:**
```cpp
double d1 = pow(6.*m1/(M_PI*rhoSoot), onethird);
double d2 = pow(6.*m2/(M_PI*rhoSoot), onethird);
```

---

## Bug #2: Incorrect Mass Variable in Harmonic Mean Coagulation Model

**File:** `src/coagulationModels/coagulationModel_HM.cc`  
**Lines:** 28-29  
**Classification:** Critical - Produces incorrect numerical results

**Issue:** Identical error to Bug #1. The diameter `d2` is calculated using `m1` instead of `m2`.

**Current Code:**
```cpp
double d1 = pow(6.*m1/(M_PI*rhoSoot), onethird);
double d2 = pow(6.*m1/(M_PI*rhoSoot), onethird);  // Uses m1 instead of m2
double ds = d1 + d2;
```

**Expected Code:**
```cpp
double d1 = pow(6.*m1/(M_PI*rhoSoot), onethird);
double d2 = pow(6.*m2/(M_PI*rhoSoot), onethird);
double ds = d1 + d2;
```

---

## Bug #3: Incorrect Condition in LOGN Harmonic Mean Calculation

**File:** `src/sootModel_LOGN.cc`  
**Lines:** 293-296  
**Classification:** Critical - Produces incorrect numerical results

**Issue:** The harmonic mean calculation checks whether `C0_fm` and `C0_c` are greater than zero. However, these are coagulation loss terms and are negative values. The condition `(C0_fm > 0 || C0_c > 0)` always evaluates to false, causing the harmonic mean to never be calculated. The values default to 0.0 instead of the correct harmonic mean.

**Supporting Context from Lines 270-280:**
```cpp
if (coag->mechType == coagulationMech::FM || 
        coag->mechType == coagulationMech::HM) {
    double Kfm = coag->getKfm(state);
    C0_fm =   -Kfm*bCoag*(M0*M16 + 2.*M26*Mn16 + M46*Mn36);  // Negative value
    C2_fm = 2.*Kfm*bCoag*(M1*M76 + 2.*M86*M56  + M106*M36);
}

if (coag->mechType == coagulationMech::CONTINUUM || 
        coag->mechType == coagulationMech::HM) {
    double Kc  = coag->getKc( state);
    double Kcp = coag->getKcp(state);
    C0_c =   -Kc*(M0*M0 + M26*Mn26 + Kcp*(M0*Mn26 + M26*Mn46));  // Negative value
    C2_c = 2.*Kc*(M1*M1 + M46*M86  + Kcp*(M1*M46  + M26*M86));
}
```

**Current Code:**
```cpp
else {      // harmonic mean
    C0 = (C0_fm > 0 || C0_c > 0) ? C0_fm*C0_c/(C0_fm + C0_c) : 0.0;
    C2 = (C2_fm > 0 || C2_c > 0) ? C2_fm*C2_c/(C2_fm + C2_c) : 0.0;
}
```

**Expected Code:**
```cpp
else {      // harmonic mean
    C0 = (C0_fm + C0_c != 0.0) ? C0_fm*C0_c/(C0_fm + C0_c) : 0.0;
    C2 = (C2_fm + C2_c != 0.0) ? C2_fm*C2_c/(C2_fm + C2_c) : 0.0;
}
```

---

## Bug #4: Unreachable Error Check in State Initialization

**File:** `src/state.cc`  
**Lines:** 66-74  
**Classification:** Moderate - Inconsistent logic flow

**Issue:** The code first sets negative soot variables to 0.0, then attempts to check for negative values and throw an error. The error check is unreachable because all negative values have already been corrected.

**Current Code:**
```cpp
for(int i=0; i<nsoot; i++)
    if(sootVar_[i] < 0)
        sootVar_[i] = 0.0;

nsoot = nsoot_;
for (double s : sootVar_)
    if (s < 0)
        throw domain_error("Unphysical state value input: negative soot moment(s)");
```

---

## Bug #5: Duplicate Code in PAH Nucleation Model

**File:** `src/nucleationModels/nucleationModel_PAH.cc`  
**Lines:** 108-114  
**Classification:** Moderate - Code duplication

**Issue:** The assignment `DIMER.mDimer = mDimer` appears twice with identical comments.

**Current Code:**
```cpp
//------------ populate mDimer in Dimer structure before calculating I_beta_DS

DIMER.mDimer = mDimer;

//------------ populate mDimer in Dimer structure before calculating I_beta_DS
    
DIMER.mDimer = mDimer;
```

**Expected Code:**
```cpp
//------------ populate mDimer in Dimer structure before calculating I_beta_DS

DIMER.mDimer = mDimer;
```

---

## Bug #6: Incorrect Doxygen Comment Marker

**File:** `src/state.h`  
**Line:** 41  
**Classification:** Minor - Documentation formatting

**Issue:** Doxygen comment uses `///>` instead of `///<`.

**Current Code:**
```cpp
std::vector<double> tarVar;        ///> tar variables
```

**Expected Code:**
```cpp
std::vector<double> tarVar;        ///< tar variables
```

---

## Bug #7: Unprotected Logarithm Operation

**File:** `src/sootModel_MOMIC.cc`  
**Line:** 625  
**Classification:** Minor - Potential numerical issue

**Issue:** The function takes `log10(M[k])` without checking if `M[k] > 0`, which could produce NaN values if moments are zero or negative.

**Current Code:**
```cpp
void sootModel_MOMIC::set_diffTable(const vector<double> &M) {
    //----------- set first column
    for (int k=0; k<Nmom; k++)
        diffTable[k][0] = log10(M[k]);
```

---

**Report Prepared:** March 6, 2026
