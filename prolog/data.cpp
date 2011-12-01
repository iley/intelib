#include "data.hpp"
#include "engine.hpp"
#include "utils.hpp"

static SListConstructor S;

// Generic Prolog Expression

PlgReference PlgUnbound;

IntelibTypeId PlgExpression::TypeId(&SExpression::TypeId, true);

bool PlgExpression::Unify(const PlgReference &other, PlgContext &context) const {
    return this == other.GetPtr();
}

#if INTELIB_TEXT_REPRESENTATIONS == 1
SString PlgExpression::TextRepresentation() const { return "<PROLOG EXPRESSION>"; }
#endif

// Clause

IntelibTypeId PlgExpressionClause::TypeId(&PlgExpression::TypeId, true);

// Term

IntelibTypeId PlgExpressionTerm::TypeId(&PlgExpression::TypeId, false);

PlgExpressionTerm::PlgExpressionTerm(const PlgAtom &fn, const SReference &as) : PlgExpression(TypeId), functor(fn), args(as), arity(Length(as)) {}

bool PlgExpressionTerm::Unify(const PlgReference &other, PlgContext &context) const {
    if (other->TermType() != PlgExpressionTerm::TypeId)
        return false;

    PlgExpressionTerm *otherTerm = other.SimpleCastGetPtr<PlgExpressionTerm>();
    if (functor != otherTerm->functor)
        return false;

    context.CreateFrame();

    SReference ourArg = args, theirArg = otherTerm->args;
    bool result = true;
    while (!ourArg.IsEmptyList() && !theirArg.IsEmptyList()) {
        if (!PlgReference(ourArg)->Unify(theirArg, context)) {
            result = false;
            break;
        }

        ourArg = ourArg.Cdr();
        theirArg = theirArg.Cdr();
    }

    if (result)
        context.MergeDown();
    else
        context.DropFrame();

    return result;
}

#if INTELIB_TEXT_REPRESENTATIONS == 1
SString PlgExpressionTerm::TextRepresentation() const { 
    return functor->TextRepresentation() + "(" + Join(", ", args) + ")";
}
#endif

// Atom

IntelibTypeId PlgExpressionAtom::TypeId(&PlgExpression::TypeId, false);

PlgReference PlgAtom::operator() (const PlgReference &arg1) {
    return PlgTerm(*this, (S| arg1 ));
}

PlgReference PlgAtom::operator() (const PlgReference &arg1, const PlgReference &arg2) {
    return PlgTerm(*this, (S| arg1, arg2 ));
}

PlgReference PlgAtom::operator() (const PlgReference &arg1, const PlgReference &arg2, const PlgReference &arg3) {
    return PlgTerm(*this, (S| arg1, arg2, arg3 ));
}

// TODO more args

#if INTELIB_TEXT_REPRESENTATIONS == 1
SString PlgExpressionAtom::TextRepresentation() const { return label->TextRepresentation(); }
#endif

// Variable Name

IntelibTypeId PlgExpressionVariableName::TypeId(&PlgExpressionAtom::TypeId, false);

bool PlgExpressionVariableName::Unify(const PlgReference &other, PlgContext &context) const {
    //context.Set(label, other);
    // FIXME
    return false;
}

//

IntelibTypeId PlgExpressionList::TypeId(&PlgExpression::TypeId, false);

// Disjunction

IntelibTypeId PlgExpressionDisjunction::TypeId(&PlgExpressionList::TypeId, false);

#if INTELIB_TEXT_REPRESENTATIONS == 1
SString PlgExpressionDisjunction::TextRepresentation() const {
    return Join("; ", list);
}
#endif

PlgDisjunction operator | (const PlgReference &left, const PlgReference &right) {
    return PlgDisjunction((S| left, right ));
}

// Conjunction

IntelibTypeId PlgExpressionConjunction::TypeId(&PlgExpressionList::TypeId, false);

#if INTELIB_TEXT_REPRESENTATIONS == 1
SString PlgExpressionConjunction::TextRepresentation() const {
    return Join(", ", list);
}
#endif

PlgConjunction operator & (const PlgReference &left, const PlgReference &right) {
    return PlgConjunction((S| left, right ));
}
