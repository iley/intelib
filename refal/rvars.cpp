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




// Modified by Igor Bronstein (<igor.bronstein_AT_gmail.com>)

#include <stdio.h>

#include "../sexpress/iexcept.hpp"
#include "../sexpress/sstring.hpp"

#include "rvars.hpp"


/*
    There is as for now no possibility to make derived types of variables
    except for 3 standard ones. So there is only one TypeId
    (for RfExpressionVariable) here.
*/
IntelibTypeId
RfExpressionVariable::TypeId(&SExpressionLabel::TypeId);


