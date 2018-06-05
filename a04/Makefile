all: init_aim register register2 sort schedule add class_schedule class_list grade report print_students print_schedule print_studentcourse

aim.o: aim.c aim.h
	gcc -Wall -ansi -pedantic -c aim.c -o aim.o

init_aim: init_aim.c aim.o
	gcc -Wall -ansi -pedantic -c init_aim.c -o init_aim.o
	gcc -Wall -ansi -pedantic aim.o init_aim.o -o init_aim

register: register.c aim.o
	gcc -Wall -ansi -pedantic -c register.c -o register.o
	gcc -Wall -ansi -pedantic aim.o register.o -o register

register2: register2.c aim.o
	gcc -Wall -ansi -pedantic -c register2.c -o register2.o
	gcc -Wall -ansi -pedantic aim.o register2.o -o register2

sort: sort.c aim.o
	gcc -Wall -ansi -pedantic -c sort.c -o sort.o
	gcc -Wall -ansi -pedantic aim.o sort.o -o sort

schedule: schedule.c aim.o
	gcc -Wall -ansi -pedantic -c schedule.c -o schedule.o
	gcc -Wall -ansi -pedantic aim.o schedule.o -o schedule

add: add.c aim.o
	gcc -Wall -ansi -pedantic -c add.c -o add.o
	gcc -Wall -ansi -pedantic aim.o add.o -o add

class_schedule: class_schedule.c aim.o
	gcc -Wall -ansi -pedantic -c class_schedule.c -o class_schedule.o
	gcc -Wall -ansi -pedantic aim.o class_schedule.o -o class_schedule

class_list: class_list.c aim.o
	gcc -Wall -ansi -pedantic -c class_list.c -o class_list.o
	gcc -Wall -ansi -pedantic aim.o class_list.o -o class_list

grade: grade.c aim.o
	gcc -Wall -ansi -pedantic -c grade.c -o grade.o
	gcc -Wall -ansi -pedantic aim.o grade.o -o grade

report: report.c aim.o
	gcc -Wall -ansi -pedantic -c report.c -o report.o
	gcc -Wall -ansi -pedantic aim.o report.o -o report

print_students: print_students.c aim.o
	gcc -Wall -ansi -pedantic -c print_students.c -o print_students.o
	gcc -Wall -ansi -pedantic aim.o print_students.o -o print_students

print_schedule: print_schedule.c aim.o
	gcc -Wall -ansi -pedantic -c print_schedule.c -o print_schedule.o
	gcc -Wall -ansi -pedantic aim.o print_schedule.o -o print_schedule

print_studentcourse: print_studentcourse.c aim.o
	gcc -Wall -ansi -pedantic -c print_studentcourse.c -o print_studentcourse.o
	gcc -Wall -ansi -pedantic aim.o print_studentcourse.o -o print_studentcourse
clean:
	rm *.o
	rm *.bin
	rm *.txt
	rm init_aim register register2 sort schedule add class_schedule class_list grade report print_students print_schedule print_studentcourse
