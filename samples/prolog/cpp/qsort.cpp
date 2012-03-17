#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <prolog/prolog.hpp>
#include <prolog/utils.hpp>

int main() {
    using namespace PlgStdLib;

    SListConstructor S;
    SReference &Nil = *PTheEmptyList;

    PlgAtom qsort("qsort"), split("split");
    PlgVariable H("H"), T("T"), R("R"), L("L"), X("X"), Res("Res"), LS("LS"), RS("RS");

    PlgDatabase db;

    db.Add( qsort(Nil, Nil) );
    db.Add( qsort(H^T, Res) <<= split(H, T, L, R) & qsort(L, LS) & qsort(R, RS) & append(LS, H ^ RS, Res) );

    db.Add( split(X, Nil, Nil, Nil) );
    db.Add( split(X, H^T, H^LS, RS) <<= (H <= X) & split(X, T, LS, RS) );
    db.Add( split(X, H^T, LS, H^RS) <<= (H >  X) & split(X, T, LS, RS) );

    srand(time(0));

    SReference list = Nil;
    for (int i = 0; i < 1000; ++i)
        list = SReference(rand()).MakeCons(list);
    //printf("Sorting %s...\n", Dump(list));

    PlgContinuation cont = db.Query(qsort(list, X));
    if (cont->Next()) {
        //printf("Result: %s\n", Dump(cont->GetValue(X)));
        printf("Done\n");
    }

    return 0;
}
