#include "prolog.hpp"
#include "../sexpress/sstring.hpp"

static SListConstructor S;

IntelibX_not_a_prolog_object::IntelibX_not_a_prolog_object(SReference a_param) : IntelibX("Not a prolog object", a_param) {}


IntelibTypeId PlgExpressionImpl::TypeId(&SExpression::TypeId, false);

// Abstract Prolog Expression
PlgExpressionImpl::~PlgExpressionImpl() {}

//PlgResult PlgExpression::Solve() const 
//{ 
    //return (*this)->Solve(); 
//}

// Prolog Disjunction
IntelibTypeId PlgDisjunctionImpl::TypeId(&PlgExpressionImpl::TypeId, false);

// Prolog Conjunction
IntelibTypeId PlgConjunctionImpl::TypeId(&PlgDisjunctionImpl::TypeId, false);

// Prolog Clause
IntelibTypeId PlgClauseImpl::TypeId(&SExpression::TypeId, true);

PlgClause::PlgClause(const PlgCompoundTerm &head, const PlgDisjunction &body) : Super(new PlgClauseImpl(head, body)) {}

const PlgCompoundTerm &PlgClause::GetHead() const { return (*this)->GetHead(); }
const PlgDisjunction &PlgClause::GetBody() const { return (*this)->GetBody(); }

// Prolog Term
IntelibTypeId PlgTermImpl::TypeId(&PlgExpressionImpl::TypeId, false);

PlgTermImpl::~PlgTermImpl() {}

// Prolog Atom, immutable

IntelibTypeId PlgAtomImpl::TypeId(&PlgTermImpl::TypeId, false);

PlgAtom::PlgAtom(const char *name) : Super(new PlgAtomImpl(name)) {}

const char *PlgAtom::GetName() const { return (*this)->GetName(); }

PlgCompoundTerm PlgAtom::operator() (const PlgTerm &term1) {
    return PlgCompoundTerm(*this, (S|term1));
}


PlgCompoundTerm PlgAtom::operator() (const PlgTerm &term1, const PlgTerm &term2) {
    return PlgCompoundTerm(*this, (S| term1, term2));
}

// Prolog Compound Term, i.e. functor(arguments), immutable
IntelibTypeId PlgCompoundTermImpl::TypeId(&PlgTermImpl::TypeId, false);

PlgCompoundTerm::PlgCompoundTerm(const PlgAtom &functor, const SReference &args)
    : Super(new PlgCompoundTermImpl(functor, args)) {}


const PlgAtom &PlgCompoundTerm::GetFunctor() const { return (*this)->GetFunctor(); }
const SReference &PlgCompoundTerm::GetArguments() const { return (*this)->GetArguments(); }

