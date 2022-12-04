UNAME = $(shell uname -s)
PROJECTNAME = C_3DEngine
FLAGSS = "noflags"
CC = gcc -Wall -Werror -Wextra -std=c11 -g
LIBSDIR = libs
TMPDIR = tmp
TESTDIR = unit-tests
COVDIR = unit-tests/coverage
BUILDDIR_RELEASE = build/C_3DEngine-build-release
BUILDDIR_TESTS = build/C_3DEngine-tests
SOURCES_C = src/engine/s21_engine.h src/engine/s21_mesh.c src/engine/s21_mesh.h src/engine/math/s21_engine_math.c src/engine/math/s21_engine_math.h src/engine/math/s21_matrix4x4.c src/engine/math/s21_matrix4x4.h
SOURCES_CPP = src/main.cpp src/gui/mainwindow.cpp src/gui/mainwindow.h src/gui/openglwidget.cpp src/gui/openglwidget.h
SOURCES_UI = src/gui/mainwindow.ui
SOURCES_LIBS = $(LIBSDIR)/matrix-lib/s21_matrix.c $(LIBSDIR)/matrix-lib/s21_matrix.h
SOURCES_COMPILED = $(TMPDIR)/s21_tests_matrix4x4.o $(TMPDIR)/s21_tests_engine_math.o $(TMPDIR)/s21_tests_mesh.o
SOURCES_TESTS = $(TESTDIR)/s21_tests_main.c $(TESTDIR)/s21_tests_lib.c $(TESTDIR)/s21_tests.h
OUTNAME = $(PROJECTNAME)
OUTNAME_TESTS = $(PROJECTNAME)_tests
OUTNAME_TAR = $(PROJECTNAME)-build-release-v1.tar.gz
OUTNAME_MANUAL = "manual.html"

ifeq ($(UNAME),Darwin)
	FLAGSS = -lcheck -lm -lpthread -fprofile-arcs
	OUTNAME = $(PROJECTNAME).app
endif
ifeq ($(UNAME),Linux)
	FLAGSS = -lcheck -lsubunit -lrt -lm -lpthread -fprofile-arcs
endif

all: cleanall install dist dvi launch
.PHONY : all

build: $(SOURCES_C) $(SOURCES_CPP) $(SOURCES_UI)
	if [ ! -d "$(BUILDDIR_RELEASE)" ] && [ ! -f "build/$(OUTNAME)" ]; then cd build/ && cmake CMakeLists.txt && make; fi
.PHONY : build

rebuild: uninstall build
.PHONY : rebuild

install: build
	if ! [ -d "$(BUILDDIR_RELEASE)" ]; then mkdir $(BUILDDIR_RELEASE); fi
	mv build/$(OUTNAME) $(BUILDDIR_RELEASE)/$(OUTNAME)
.PHONY : install

dist: $(BUILDDIR_RELEASE)/$(OUTNAME)
	tar -zcvf build/$(OUTNAME_TAR) $(BUILDDIR_RELEASE)
.PHONY : dist

dvi: dvi_clean misc/$(PROJECTNAME)_manual.texi
	makeinfo misc/$(PROJECTNAME)_manual.texi --html
	mv manual/index.html $(OUTNAME_MANUAL)
	rm -rf manual
	open $(OUTNAME_MANUAL)
.PHONY : dvi

launch: $(BUILDDIR_RELEASE)/$(OUTNAME)
ifeq ($(UNAME),Darwin)
	open $(BUILDDIR_RELEASE)/$(OUTNAME)
endif
ifeq ($(UNAME),Linux)
	./$(BUILDDIR_RELEASE)/$(OUTNAME)
endif
.PHONY : launch

tests: clean $(SOURCES_TESTS) $(SOURCES_LIBS) $(SOURCES_C)
	if ! [ -d "$(TMPDIR)" ]; then mkdir $(TMPDIR); fi
	rm -rf $(TMPDIR)/s21_tests* $(TMPDIR)/*.gcda $(TMPDIR)/*.gcno
	if ! [ -d "$(BUILDDIR_TESTS)" ]; then mkdir $(BUILDDIR_TESTS); fi
	$(CC) -c --coverage src/engine/math/s21_engine_math.c -o $(TMPDIR)/s21_tests_engine_math.o
	$(CC) -c --coverage src/engine/s21_mesh.c -o $(TMPDIR)/s21_tests_mesh.o
	$(CC) -c --coverage src/engine/math/s21_matrix4x4.c -o $(TMPDIR)/s21_tests_matrix4x4.o
	gcc $(SOURCES_TESTS) $(SOURCES_LIBS) $(SOURCES_COMPILED) $(FLAGSS) -o $(BUILDDIR_TESTS)/$(OUTNAME_TESTS)
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

dvi_clean:
	rm -rf manual $(OUTNAME_MANUAL)
.PHONY : dvi_clean

clean:
	rm -rf *.o *.gcno *.gcda *.gcov *.dSYM a.out app src/app ".clang-format"
	rm -rf $(TMPDIR)
.PHONY : clean

cleanall: clean dvi_clean uninstall
	rm -rf .qt/ build/CMakeCache.txt build/cmake_install.cmake build/.qt/ build/CMakeFiles build/Makefile
	rm -rf build/build-release build/build-debug
	rm -rf $(OUTNAME) build/$(OUTNAME) build/$(OUTNAME)_autogen/ $(OUTNAME_TESTS) build/$(OUTNAME_TESTS) *.a *.so
	rm -rf build/$(OUTNAME_TAR)
	rm -rf $(BUILDDIR_TESTS)
	rm -rf $(COVDIR)
.PHONY : cleanall