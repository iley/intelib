#   InteLib                                    http://www.intelib.org
#   The file tests/common_tests.mk
#
#   Based on the file originally named tests/lisp/Makefile
#   Copyright (c) Andrey Vikt. Stolyarov, 2000-2009
#
#   Portions copyright (c) Vasiliy Kulikov, 2010
#
#
#   This is free software, licensed under GNU GPL v.2
#   See the file COPYING for further details.
#
#   THERE IS NO WARRANTY OF ANY KIND, EXPRESSED, IMPLIED OR WHATEVER!
#   Please see the file WARRANTY for the detailed explanation.


OPTIMIZATION = -O0

CXXFLAGS= -Wall -g -I.. -I../.. -Ibin_$(TARGETDIR)/intelib

# can be overriden
#LIB_OBJECTS = bin_$(TARGETDIR)/intelib/libilisp.a \
	#bin_$(TARGETDIR)/intelib/libintelibgenlisp.a \
	#bin_$(TARGETDIR)/intelib/libintelibtools.a \
	#bin_$(TARGETDIR)/intelib/libsexpr.a

#TESTS = t_lisp t_lsymb t_eval t_form t_leaks t_thread \
	#t_funstd t_funstr t_funrdr t_funhsh t_funm \
	#t_lextv t_bndset

TARGETDIRS = default
#TARGETDIRS = default longnumbers effective scheme

ifdef TARGETDIR
BINTESTS = $(patsubst %,bin_$(TARGETDIR)/%,$(TESTS))
-include bin_$(TARGETDIR)/intelib/defines.mk
endif


rund:
	$(MAKE) run TARGETDIRS=default

briefd:
	$(MAKE) brief TARGETDIRS=default


run:
	for D in $(TARGETDIRS) ; do \
		$(MAKE) run_dir TARGETDIR=$$D "TESTS=$(TESTS)" ; \
	done


run_dir: lib_rebuild $(BINTESTS)
	@echo "@@@ * @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo "@@@ * Processing directory bin_$(TARGETDIR)"
	@echo "@@@ * @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@for T in $(BINTESTS) ; do \
		$$T || echo "@@@ * $$T FAILED (AS A WHOLE) " '!!!' ; \
	done

brief:
	$(MAKE) run | grep '^@@@ \*'

log:
	$(MAKE) run > tests.log 2>&1

../tests.o:    ../tests.cpp ../tests.hpp
	cd .. && $(MAKE) tests.o

ifdef TARGETDIR



bin_$(TARGETDIR):
	mkdir -p $@/intelib

bin_$(TARGETDIR)/%:		%.cpp ../tests.o $(LIB_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(CONDDEFINES)

bin_$(TARGETDIR)/intelib/libsexpr.a:	bin_$(TARGETDIR)
	cd ../../sexpress && $(MAKE) all \
		TARGETDIR=$(CURDIR)/bin_$(TARGETDIR) \
		OPTIMIZATION=$(OPTIMIZATION)

bin_$(TARGETDIR)/intelib/libintelibtools.a:	bin_$(TARGETDIR)
	cd ../../tools && $(MAKE) all \
		TARGETDIR=$(CURDIR)/bin_$(TARGETDIR) \
		OPTIMIZATION=$(OPTIMIZATION)

bin_$(TARGETDIR)/intelib/libintelibgenlisp.a:	bin_$(TARGETDIR)
	cd ../../genlisp && $(MAKE) all \
		TARGETDIR=$(CURDIR)/bin_$(TARGETDIR) \
		OPTIMIZATION=$(OPTIMIZATION)

bin_$(TARGETDIR)/intelib/libilisp.a:	bin_$(TARGETDIR)
	cd ../../lisp && $(MAKE) all \
		TARGETDIR=$(CURDIR)/bin_$(TARGETDIR) \
		OPTIMIZATION=$(OPTIMIZATION)

bin_$(TARGETDIR)/intelib/libischeme.a:	bin_$(TARGETDIR) FORCE
	cd ../../scheme && $(MAKE) all \
		TARGETDIR=$(CURDIR)/bin_$(TARGETDIR) \
		OPTIMIZATION=$(OPTIMIZATION)

bin_$(TARGETDIR)/intelib/libiprolog.a:	bin_$(TARGETDIR) FORCE
	cd ../../prolog && $(MAKE) all \
		TARGETDIR=$(CURDIR)/bin_$(TARGETDIR) \
		OPTIMIZATION=$(OPTIMIZATION)

lib_rebuild:
	#rm -rf $(LIB_OBJECTS)
	$(MAKE) clean
	$(MAKE) $(LIB_OBJECTS)

bin_$(TARGETDIR)/intelib/defines.mk: bin_$(TARGETDIR) $(TARGETDIR)_defines.mk
	cp $(TARGETDIR)_defines.mk bin_$(TARGETDIR)/intelib/defines.mk

endif


clean:
	rm -f *.o tests.log
	for D in $(TARGETDIRS) ; do rm -rf bin_$$D ; done

FORCE:
	:
