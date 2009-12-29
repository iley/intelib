// +-------------------------------------------------------------------------+
// |               I__n__t__e__L__i__b           0.6.21 development          |
// | Copyright (c) Andrey Vikt. Stolyarov <crocodil_AT_croco.net> 2000-2008. |
// |                                                                         |
// | This is free software. The library part is available under              |
// |                               GNU LESSER GENERAL PUBLIC LICENSE v.2.1.  |
// | GNU LGPL v2.1 is found in docs/gnu_gpl2.txt,  or at  http://www.gnu.org |
// |     Please see also docs/readme.txt and visit http://www.intelib.org    |
// |                                                                         |
// | !!! THERE IS NO WARRANTY OF ANY KIND, NEITHER EXPRESSED NOR IMPLIED !!! |
// +-------------------------------------------------------------------------+




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
