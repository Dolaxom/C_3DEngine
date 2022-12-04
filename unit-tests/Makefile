DIR_LIBS = ../libs
DIR_ENGINE = ../src/engine
SOURCES_TEST = s21_tests_main.c s21_tests_lib.c s21_tests.h
SOURCES_MATRIX = $(DIR_LIBS)/matrix-lib/s21_matrix.c  $(DIR_LIBS)/matrix-lib/s21_matrix.h
SOURCES_ENGINE = $(DIR_ENGINE)/math/s21_matrix4x4.c $(DIR_ENGINE)/math/s21_matrix4x4.h $(DIR_ENGINE)/math/s21_engine_math.c $(DIR_ENGINE)/math/s21_engine_math.h $(DIR_ENGINE)/s21_engine.h $(DIR_ENGINE)/s21_mesh.c $(DIR_ENGINE)/s21_mesh.h

all: $(SOURCES_TEST) $(SOURCES_MATRIX) $(SOURCES_ENGINE)
	gcc $(SOURCES_TEST) $(SOURCES_MATRIX) $(SOURCES_ENGINE) -lm -lcheck -lsubunit -lrt -lm -lpthread -fprofile-arcs -o a.out

clear:
	rm -rf *.gcda
	clear