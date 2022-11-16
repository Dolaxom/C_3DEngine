UNAME = $(shell uname -s)
FLAGSS = "noflags"
CC = gcc -Wall -Werror -Wextra -std=c11 -g
SOURCES_C = src/engine/s21_engine.h src/engine/s21_mesh.c src/engine/s21_mesh.h src/engine/math/s21_engine_math.c src/engine/math/s21_engine_math.h src/engine/math/s21_matrix4x4.c src/engine/math/s21_matrix4x4.h
SOURCES_CPP = src/main.cpp src/gui/mainwindow.cpp src/gui/mainwindow.h src/gui/openglwidget.cpp src/gui/openglwidget.h
SOURCES_UI = src/gui/mainwindow.ui
SOURCES_COMPILED = "none"
SOURCES_TESTS = "none"
TMPDIR = tmp
COVDIR = unit-tests/coverage
BUILDDIR_RELEASE = build/C_3DEngine-build-release
BUILDDIR_TESTS = build/C_3DEngine-build-tests
OUTNAME = C_3DEngine
OUTNAME_TESTS = s21_tests
OUTNAME_TAR = C_3DEngine-build-release-v1.tar.gz
OUTNAME_MANUAL = "manual.html"

ifeq ($(UNAME),Darwin)
	FLAGSS = -lcheck -lm -lpthread -fprofile-arcs
endif
ifeq ($(UNAME),Linux)
	FLAGSS = -lcheck -lsubunit -lrt -lm -lpthread -fprofile-arcs
endif

all: cleanall install dist dvi launch
.PHONY : all

build: $(SOURCES_C) $(SOURCES_CPP) $(SOURCES_UI)
	if [ ! -d "$(BUILDDIR_RELEASE)" ] && [ ! -f "build/$(OUTNAME)" ]; then cd build/ && make; fi
.PHONY : build

rebuild: uninstall build
.PHONY : rebuild

install: build
	if ! [ -d "$(BUILDDIR_RELEASE)" ]; then mkdir $(BUILDDIR_RELEASE); fi
	mv build/$(OUTNAME) $(BUILDDIR_RELEASE)/$(OUTNAME)
.PHONY : install

launch: $(BUILDDIR_RELEASE)/$(OUTNAME)
	./$(BUILDDIR_RELEASE)/$(OUTNAME)
.PHONY : launch

dist: $(BUILDDIR_RELEASE)/$(OUTNAME)
	tar -zcvf build/$(OUTNAME_TAR) $(BUILDDIR_RELEASE)
.PHONY : dist

dvi: misc/$(OUTNAME)_manual.texi
	makeinfo misc/$(OUTNAME)_manual.texi --html
	mv manual/index.html $(OUTNAME_MANUAL)
	rm -rf manual
	open $(OUTNAME_MANUAL)
.PHONY : dvi

tests: clean $(SOURCES_TESTS) $(SOURCES_C)
	if ! [ -d "$(TMPDIR)" ]; then mkdir $(TMPDIR); fi
	rm -rf $(TMPDIR)/s21_tests*
	if ! [ -d "$(BUILDDIR_TESTS)" ]; then mkdir $(BUILDDIR_TESTS); fi
#	$(CC) -c --coverage src/s21_calc_core.c -o $(TMPDIR)/s21_tests_calc_core.o
#	$(CC) -c --coverage src/s21_calc_math.c -o $(TMPDIR)/s21_tests_calc_math.o
#	$(CC) -c --coverage src/s21_calc_graphs.c -o $(TMPDIR)/s21_tests_calc_graphs.o
#	$(CC) -c src/s21_calc_other.c -o $(TMPDIR)/s21_tests_calc_other.o
#	$(CC) -c src/s21_stack.c -o $(TMPDIR)/s21_tests_stack.o
	$(CC) $(SOURCES_TESTS) $(SOURCES_COMPILED) $(FLAGSS) -o $(BUILDDIR_TESTS)/$(OUTNAME_TESTS)
	@echo "-------------------------------------------------"
	./$(BUILDDIR_TESTS)/$(OUTNAME_TESTS)
	@echo "-------------------------------------------------"
	mv ./$(BUILDDIR_TESTS)/*gcda $(TMPDIR)
.PHONY : tests

gcov_report: $(BUILDDIR_TESTS)/$(OUTNAME_TESTS)
	rm -rf $(COVDIR) && mkdir $(COVDIR)
	@echo ""
	gcov -b -l -p -c $(TMPDIR)/*.gcno
	gcovr -g -k -r . --html --html-details -o $(COVDIR)/coverage_report.html
	mv *.gcov $(TMPDIR)
	open $(COVDIR)/coverage_report.html
.PHONY : gcov_report

style: $(SOURCES_C) $(SOURCES_CPP)
	cp utils/".clang-format" ".clang-format"
	clang-format -i src/*.cpp
	clang-format -i src/*.c
	clang-format -i src/*.h
	clang-format -n src/*.cpp
	clang-format -n src/*.c
	clang-format -n src/*.h
	rm -rf ".clang-format"
.PHONY : style

valgrind: $(BUILDDIR_RELEASE)/$(OUTNAME) $(BUILDDIR_TESTS)/$(OUTNAME_TESTS)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BUILDDIR_RELEASE)/$(OUTNAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BUILDDIR_TESTS)/$(OUTNAME_TESTS)
.PHONY : valgrind

uninstall:
	rm -rf $(BUILDDIR_RELEASE)
.PHONY : uninstall

clean:
	rm -rf *.o *.gcno *.gcda *.gcov *.dSYM a.out app src/app ".clang-format"
	rm -rf $(TMPDIR)
.PHONY : clean

cleanall: clean uninstall
	rm -rf .qt/ build/CMakeCache.txt build/cmake_install.cmake build/.qt/ build/CMakeFiles build/$(OUTNAME)_autogen/
	rm -rf $(OUTNAME) build/$(OUTNAME) $(OUTNAME_TESTS) build/$(OUTNAME_TESTS) *.a *.so
	rm -rf manual $(OUTNAME_MANUAL)
	rm -rf build/$(OUTNAME_TAR)
	rm -rf $(BUILDDIR_TESTS)
	rm -rf $(COVDIR)
.PHONY : cleanall