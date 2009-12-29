// +-------------------------------------------------------------------------+
// |               I__n__t__e__L__i__b           0.6.21 development          |
// | Copyright (c) Andrey Vikt. Stolyarov <crocodil_AT_croco.net> 2000-2008. |
// |                                                                         |
// | This is free software.  See GNU GENERAL PUBLIC LICENSE v.2 for details. |
// | GNU GPL v2  is  found  in docs/gnu_gpl2.txt,  or at  http://www.gnu.org |
// |     Please see also docs/readme.txt and visit http://www.intelib.org    |
// |                                                                         |
// | !!! THERE IS NO WARRANTY OF ANY KIND, NEITHER EXPRESSED NOR IMPLIED !!! |
// +-------------------------------------------------------------------------+




#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "tests.hpp"

static long totals;
static long passed;
static long failed;
static const char *currentsuite;

static void TestPassed(const char *name)
{
    printf("@@@ <passed> %s\n", name);
    totals++;
    passed++;
}

static void TestFailed(const char *name, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    printf("@@@ <FAILED> %s [", name);
    vprintf(format, ap);
    printf("]\n");
    va_end(ap);
    totals++;
    failed++;
}

void TestSection(const char *name)
{
    totals = 0;
    passed = 0;
    failed = 0;
    currentsuite = strdup(name);
    printf("@@@ @@@ @@@ %s @@@\n", name);
}

void TestSubsection(const char *name)
{
    printf("@@@ ---- %s ----\n", name);
}

static bool Test(const char *name, bool result)
{
    if(result) {
        TestPassed(name);
        return true;
    } else {
        TestFailed(name, "");
        return false;
    }
}

static bool Test(const char *name, const char *tst, const char *expected)
{
    if (tst == expected ||
       (tst && expected && 0 == strcmp(tst, expected))) {
        TestPassed(name);
        return true;
    } else {
        TestFailed(name, "result: \"%s\", expected: \"%s\"",
                   tst, expected);
        return false;
    }
}

static bool Test(const char *name, long tst, long expected)
{
    if(tst == expected) {
        TestPassed(name);
        return true;
    } else {
        TestFailed(name, "result: %d, expected: %d",
                   tst, expected);
        return false;
    }
}

bool Testfl(const char *name, const char *file, int line,
            bool result)
{
    if(!Test(name, result))
        fprintf(stderr, "\n%s:%d: %s test failed\n", file, line, name);
    else
        return true;
    return false;
}

bool Testfl(const char *name, const char *file, int line,
            const char *tst, const char *expected)
{
    if(!Test(name, tst, expected))
        fprintf(stderr, "\n%s:%d: %s test failed\n", file, line, name);
    else
        return true;
    return false;
}

bool Testfl(const char *name, const char *file, int line,
            long tst, long expected)
{
    if(!Test(name, tst, expected))
        fprintf(stderr, "\n%s:%d: %s test failed\n", file, line, name);
    else
        return true;
    return false;
}

void TestScore()
{
    printf("@@@ -----------------\n");
    printf("@@@ * Suite name: %s\n", currentsuite);
    printf("@@@ * Passed: %ld\n", passed);
    printf("@@@ * Failed: %ld\n", failed);
    printf("@@@ * Totals: %ld\n", totals);
    if(failed) {
	printf("@@@ ! SOME TESTS FAILED in the suite %s\n", currentsuite);
    }
    free((void*)currentsuite);
}
