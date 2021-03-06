//   InteLib                                    http://www.intelib.org
//   The file genlisp/library/rdr/saferead.cpp
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

DECLARE_CFUNCTION(SFunctionSaferead,  1,  4,  "#<FUNCTION SAFEREAD>")
DECLARE_CFUNCTION(SFunctionReaderror, 0, 0, "#<FUNCTION READERROR>")

#ifdef INTELIB_GENLISP_LIBRARY_IMPLEMENTATION

static SReference reader_error_param;
static int reader_error_line = -1;
static int reader_error_begline = -1;

void SFunctionSaferead::
DoApply(int paramsc, const SReference paramsv[], IntelibContinuation& lf) const
            // <stream> [<error-value> [<eof-value> [<package>]]]]
            //         *O*R*
            // <string> [<error-value> [<eof-value> [<package>]]]]
            //     <package> may be NIL, to force using dummy-package
{
    SListConstructor L;
    SExpressionStream *stream = 
        paramsv[0].DynamicCastGetPtr<SExpressionStream>();
    SReference keep_stream;
    if(!stream) {
        SExpressionString *the_string = 
            paramsv[0].DynamicCastGetPtr<SExpressionString>();
        stream = new SExpressionStreamCharbuf(the_string->GetValue());
        keep_stream = stream;
    }
    INTELIB_ASSERT(stream, IntelibX_not_a_stream(paramsv[0]));
    IntelibPackage *pkg = 0; 
    if(paramsc>=4) {
        if(paramsv[3].IsEmptyList()) {
            pkg = &TheDummyPackage;
        } else {
            pkg = paramsv[3].DynamicCastGetPtr<SExpressionHashPackage>();
            INTELIB_ASSERT(pkg, IntelibX_not_a_package(paramsv[3]));
        }
    }
    SReference ret;
    try {
        SReference res; 
        if(PTheIntelibReader) {
            IntelibPackage *p = 0;
            if(pkg)
                p = PTheIntelibReader->SetPackage(pkg);
            res = PTheIntelibReader->Read(stream);
            if(pkg)
                PTheIntelibReader->SetPackage(p);
        } else {
            IntelibReader reader;
            if(pkg) reader.SetPackage(pkg);
            res = reader.Read(stream);
        }

        if(res.GetPtr() == IntelibReader::EofMarker.GetPtr()) { 
            /* EOF */
            if(paramsc >= 3) ret = paramsv[2]; 
            else if(paramsc == 2) ret = paramsv[1];
            else ret = *PTheEmptyList;
        } else { 
            ret = res;
        }

        reader_error_param = SReference();
        reader_error_line = -1;
        reader_error_begline = -1;
    }
    catch(const IntelibX_reader_error &err) {
        ret = paramsc > 1 ? paramsv[1] : *PTheEmptyList;
        reader_error_param = err.Parameter();
        reader_error_line = err.Line();
        reader_error_begline = err.ExpBegLine();
    }
    lf.RegularReturn(ret);
}

void SFunctionReaderror::
DoApply(int paramsc, const SReference paramsv[], IntelibContinuation& lf) const
{
    SListConstructor L;
    lf.RegularReturn(
        reader_error_param.GetPtr() ? 
            (L|reader_error_param, reader_error_line, reader_error_begline)
            : lf.False() 
    );
}

#endif

