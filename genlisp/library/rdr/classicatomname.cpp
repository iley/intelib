//   InteLib                                    http://www.intelib.org
//   The file genlisp/library/rdr/classicatomname.cpp
// 
//   Copyright (c) Andrey Vikt. Stolyarov, 2000-2009
// 
// 
//   This is free software, licensed under GNU LGPL v.2.1
//   See the file COPYING for further details.
// 
//   THERE IS NO WARRANTY OF ANY KIND, EXPRESSED, IMPLIED OR WHATEVER!
//   Please see the file WARRANTY for the detailed explanation.




#include "rdr_inc.h"

DECLARE_CFUNCTION(SFunctionClassicatomname, 1, 1,"#<FUNCTION CLASSICATOMNAME>")

#ifdef INTELIB_GENLISP_LIBRARY_IMPLEMENTATION

void SFunctionClassicatomname::
DoApply(int paramsc, const SReference paramsv[], IntelibContinuation& lf) const
{
    SExpressionClassicAtom *ca =
        paramsv[0].DynamicCastGetPtr<SExpressionClassicAtom>();
    INTELIB_ASSERT(ca, IntelibX_not_a_string(paramsv[0]));
    lf.RegularReturn(SReference(new SExpressionString(ca->GetValue())));
}

#endif

