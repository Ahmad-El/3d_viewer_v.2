.PHONY: clean test gcov_report uninstall dist_clean dvi launch style clean

TESTFLAGS = -lgtest -lpthread
GCCFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++ -pedantic
GCOVFLAGS = -fprofile-arcs -ftest-coverage

SRC = ./
TEST := $(wildcard $(SRC)/test.cc)
TEST += $(wildcard $(SRC)/controller/controller.cc)
TEST += $(wildcard $(SRC)/model/facade/facade.cc)
TEST += $(wildcard $(SRC)/model/figure/figure.cc)
TEST += $(wildcard $(SRC)/model/parser/parser.cc)

all: test install 

test:
	@gcc -o test $(TEST) $(TESTFLAGS) $(GCCFLAGS)
	leaks -atExit -- ./test

test_for_gcov: clean
	@gcc -o test $(TEST) $(TESTFLAGS) $(GCCFLAGS) $(GCOVFLAGS)
	leaks -atExit -- ./test

gcov_report: test_for_gcov
	@lcov -t "./gcov" -o report.info --no-external -c -d . --ignore-errors mismatch --rc geninfo_unexecuted_blocks=1
	@genhtml -o report report.info
	@open ./report/index.html

install: uninstall
	make clean
	mkdir build
	cd ui && qmake && make && make clean && rm Makefile && cd ../ && mv ui/ui.app build

uninstall:
	rm -rf build

dist: 
	tar -cvf CPP4_3DViewer_v2.tar.gz controller model ui Makefile

dist_clean: 
	rm -rf CPP4_3DViewer_v2.tar.gz

dvi:
	open ../README_RUS.md

launch:
	open build/ui.app

run:
	leaks -atExit -- ./build/ui.app/Contents/MacOS/ui

style:
	find . -name '*.h' -exec clang-format  --style=google -n {} \;
	find . -name '*.cc' -exec clang-format  --style=google -n {} \;
	find . -name '*.c'  -exec clang-format  --style=google -n {} \;
	find . -name '*.cpp' -exec clang-format  --style=google -n {} \;

clean:
	@rm -rf test 
	@rm -rf *.o *.a *.out *.gcno *.gcda *.info *.gch test report gcov_report
	@rm -rf *.o *.a test
	@rm -rf *.gcno *gcda *.gcov gcov
	@rm -rf report report.info
	@rm -rf *.dSYM
	@rm -rf *.a
