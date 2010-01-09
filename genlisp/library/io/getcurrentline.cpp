//   InteLib                                    http://www.intelib.org
//   The file genlisp/library/io/getcurrentline.cpp
// 
//   Copyright (c) Andrey Vikt. Stolyarov, 2000-2009
// 
// 
//   This is free software, licensed under GNU LGPL v.2.1
//   See the file COPYING for further details.
// 
//   THERE IS NO WARRANTY OF ANY KIND, EXPRESSED, IMPLIED OR WHATEVER!
//   Please see the file WARRANTY for the detailed explanation.




#include "io_inc.h"

DECLARE_CFUNCTION(SFunctionGetcurrentline, 1, 1, "#<FUNCTION GETCURRENTLINE>")

#ifdef INTELIB_GENLISP_LIBRARY_IMPLEMENTATION

void SFunctionGetcurrentline::
DoApply(int paramsc, const SReference paramsv[], IntelibContinuation& lf) const
{ 
    SExpressionStream *stream = 
        paramsv[0].DynamicCastGetPtr<SExpressionStream>();
    INTELIB_ASSERT(stream, IntelibX_not_a_stream(paramsv[0]));
    SExpressionStreamTextInput *sti = 
        paramsv[0].DynamicCastGetPtr<SExpressionStreamTextInput>();
    intelib_integer_t res = sti ? sti->TellLine() : -1;
    lf.RegularReturn(res);
}

#endif

