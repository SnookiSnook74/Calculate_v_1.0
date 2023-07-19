CC=gcc
WAY=./logic/
OS=$(shell uname)
WILD=$(wildcard *.c)
WILD_SORT=$(shell find . -name "*.c" ! -name "*test*")
SORT=$(shell find . -name "*.c")
FLAGS=-Wall -Werror -Wextra
VERSION = 1.0
PACKAGE = s21_calc-$(VERSION)
ifeq ($(OS), Linux)
  FLAGS_LCHECK = -lcheck -pthread -lsubunit -lrt -lm
  OPEN=xdg-open
else
  FLAGS_LCHECK = -lcheck
  OPEN=open
endif
FLAGS_GCOV = -coverage -fprofile-arcs -ftest-coverage


all: clean test

install: clean
	mkdir build
	cp logic/*.c gui && cp logic/*.h gui
	cd build/ && qmake ../gui/Calculate.pro && make
	open build/Calculate.app

uninstall: clean

dvi:
	open s21_calc_info.md

dist:
	mkdir $(PACKAGE)
	cp -r ./logic $(PACKAGE)
	cp -r ./gui $(PACKAGE)
	cp Makefile $(PACKAGE)
	tar -czf $(PACKAGE).tar.gz $(PACKAGE)
	rm -rf $(PACKAGE)

.PHONY: test
test: s21_calc.a
	$(CC) ./unit_test/test.c $(FLAGS) $(FLAGS_LCHECK) s21_calc.a

.PHONY: gcov_report
gcov_report: s21_calc.a
		$(CC) $(SORT) $(FLAGS)  \
		$(FLAGS_LCHECK) s21_calc.a $(FLAGS_GCOV) \
		$(WILD_REPORT) -o info
	./info
	lcov -t "info" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info
	$(OPEN) report/index.html

s21_calc.a:
	$(CC) -c $(WILD_SORT)
	ar -rcs $@ *.o
	ranlib $@
	rm -rf *.o

.PHONY: docker
docker:
	docker rmi -f string && docker build -t string . && docker run  --name unit string
	# docker cp unit:/hello/report .
	docker rm unit

.PHONY: cppcheck
cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

style:
	clang-format -i */*.c
	clang-format -i */*.h
	clang-format -i */*.cpp

clean_no_all:
	rm -rf *.o *.gcda *.gcno *.info
	rm -f info

clean:
	rm -rf build/
	rm -rf gui/*.c
	rm -rf gui/stack.h
	rm -rf gui/parser.h
	rm -rf gui/credit_calc.h
	rm -rf *.o *.gcda *.gcno *.info
	rm -f info
	rm -f *.a
	rm -rf report
	rm -f test

.PHONY: git
git: style
	rm -rf report
	git add .
	git commit -m "commit"
	git push

valgrind:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./test