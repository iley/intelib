//   InteLib                                    http://www.intelib.org
//   The file genlisp/library/hsh/makehashtable_eql.cpp
// 
//   Copyright (c) Andrey Vikt. Stolyarov, 2000-2009
// 
// 
//   This is free software, licensed under GNU LGPL v.2.1
//   See the file COPYING for further details.
// 
//   THERE IS NO WARRANTY OF ANY KIND, EXPRESSED, IMPLIED OR WHATEVER!
//   Please see the file WARRANTY for the detailed explanation.




#include "hsh_inc.h"

DECLARE_CFUNCTION(SFunctionMakehashtable_eql, 0, 0,
                  "#<FUNCTION MAKEHASHTABLE_EQL>")

#ifdef INTELIB_GENLISP_LIBRARY_IMPLEMENTATION

void SFunctionMakehashtable_eql::
DoApply(int paramsc, const SReference paramsv[], IntelibContinuation& lf) const
{
    lf.RegularReturn(SReference(new SExpressionHashTable(SExprsAreEql)));
}

#endif

