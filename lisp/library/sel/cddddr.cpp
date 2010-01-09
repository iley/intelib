//   InteLib                                    http://www.intelib.org
//   The file lisp/library/sel/cddddr.cpp
// 
//   Copyright (c) Andrey Vikt. Stolyarov, 2000-2009
// 
// 
//   This is free software, licensed under GNU LGPL v.2.1
//   See the file COPYING for further details.
// 
//   THERE IS NO WARRANTY OF ANY KIND, EXPRESSED, IMPLIED OR WHATEVER!
//   Please see the file WARRANTY for the detailed explanation.




#include "sel_inc.h"

DECLARE_CFUNCTION(LFunctionCddddr, 1, 1, "#<FUNCTION CDDDDR>", "CDDDDR")
#ifdef INTELIB_LISP_LIBRARY_IMPLEMENTATION
void LFunctionCddddr::
DoApply(int paramsc, const SReference paramsv[], IntelibContinuation& lf) const
{
    SReference *r = &(paramsv[0].CCdr().CCdr().CCdr().CCdr());
    if(r != PTheEmptyList) {
        lf.ReferenceReturn(*r, paramsv[0]);
    } else {
        lf.RegularReturn(*r);
    }
}
#endif

