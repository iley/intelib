//   InteLib                                    http://www.intelib.org
//   The file genlisp/library/std/or.cpp
// 
//   Copyright (c) Andrey Vikt. Stolyarov, 2000-2009
// 
// 
//   This is free software, licensed under GNU LGPL v.2.1
//   See the file COPYING for further details.
// 
//   THERE IS NO WARRANTY OF ANY KIND, EXPRESSED, IMPLIED OR WHATEVER!
//   Please see the file WARRANTY for the detailed explanation.




#include "std_inc.h"

DECLARE_SPECFORM(SFunctionOr, "#<FORM OR>")

#ifdef INTELIB_GENLISP_LIBRARY_IMPLEMENTATION

static void DoPlace(const SReference &paramsv, IntelibContinuation& lf)
{
    if(paramsv.IsEmptyList()) {
        lf.PushTodo(IntelibContinuation::end_of_clauses);
        lf.PushTodo(IntelibContinuation::quote_parameter,
                    lf.False());
    } else {
        DoPlace(paramsv.Cdr(), lf);
        lf.PushTodo(IntelibContinuation::cond_clause, *PTheEmptyList);
        lf.PushTodo(IntelibContinuation::just_evaluate, paramsv.Car());
    }
}

void SFunctionOr::
Call(const SReference &paramsv, IntelibContinuation& lf) const
{
    DoPlace(paramsv, lf);
}
#endif
