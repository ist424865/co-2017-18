#=====================================================================
#==========      TWEAK THE 'ROOT' VARIABLE IF NECESSARY     ==========
#=====================================================================

# install in user's home directory
ROOT = ${HOME}/compiladores/root

# if installing in system dirs, use the following line instead
#ROOT= 

#=====================================================================
#==========      DO NOT CHANGE ANYTHING AFTER THIS LINE     ==========
#=====================================================================

LIBNAME=cdk

CXXFLAGS=-I. -ggdb -Wall -std=c++11 -pedantic
#CXXFLAGS=-O3 -I. -ggdb -Wall -std=c++11 -pedantic

INST_INC_DIR = $(ROOT)/usr/include/$(LIBNAME)
INST_BIN_DIR = $(ROOT)/usr/bin
INST_LIB_DIR = $(ROOT)/usr/lib
INST_DOC_DIR = $(ROOT)/usr/share/doc/packages/$(LIBNAME)

SRC_CPP = $(wildcard *.cpp) $(wildcard ast/*.cpp) \
					$(wildcard emitters/*.cpp)
	        
OFILES = $(SRC_CPP:%.cpp=%.o)

YACC=byacc
LEX=flex

%.o:: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: ast/all.h ast/visitor_decls.h link lib$(LIBNAME).a docs

# dirty hack
link:
	if [ ! -e cdk ]; then ln -s . cdk; fi

docs: doc/.docsdone

.PHONY: ./mk-node-decls.pl
ast/all.h: ./mk-node-decls.pl
	./mk-node-decls.pl cdk > ast/all.h

.PHONY: ./mk-visitor-decls.pl
ast/visitor_decls.h: ./mk-visitor-decls.pl
	./mk-visitor-decls.pl cdk > ast/visitor_decls.h

doc/.docsdone: $(LIBNAME).doxyfile
	$(RM) cdk
	doxygen $<
	touch $@
	if [ ! -e cdk ]; then ln -s . cdk; fi

$(LIBNAME).doxyfile: $(SRC_CPP)

lib$(LIBNAME).a: $(OFILES)
	ar crl $@ $^

clean:
	rm -f lib$(LIBNAME).a $(OFILES) ast/all.h ast/visitor_decls.h a.out core y.tab.[ch] lex.yy.c

install: all
	mkdir -p $(INST_LIB_DIR) $(INST_DOC_DIR) $(INST_BIN_DIR)
	mkdir -p $(INST_INC_DIR)/ast $(INST_INC_DIR)/emitters
	cp -a *.h $(INST_INC_DIR)
	cp -a ./mk-node-decls.pl ./mk-visitor-decls.pl ./mk-visitor-skel.pl $(INST_BIN_DIR)
	#don't forget to remove these!
	rm $(INST_INC_DIR)/basic_ast_visitor.h
	cp -a emitters/*.h $(INST_INC_DIR)/emitters
	cp -a ast/*.h $(INST_INC_DIR)/ast
	cp -a lib$(LIBNAME).a $(INST_LIB_DIR)
	#DOC cp -a doc/. $(INST_DOC_DIR)/

depend:
	$(CXX) $(CXXFLAGS) -MM $(SRC_CPP) > .makedeps

-include .makedeps

#=====================================================================
#==========             T  H  E         E  N  D             ==========
#=====================================================================
