#ifndef AIM_H
#define AIM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student_struct {
     char last_name[64];
     char first_name[64];
     char middle_names[64];
     int id;
     char major[64];
};

struct course_struct {
     char code[10];
     char term[6];
     char title[128];
     char instructor[64];
};

struct student_course_struct {
     int student_id;
     char course_code[10];
     char term[6];
     char registration[4];
     int grade;
};

struct strlst_struct
{
  struct student_course_struct *studentCourse;
  struct strlst_struct *next;
};

struct course_strlst
{
  struct course_struct *course;
  struct course_strlst *next;
};

struct student_strlst
{
  struct student_struct *student;
  struct student_strlst *next;
};
void init_aim();
void register_student();
void sort();
void schedule();
void add();
void print_students();
int compar();
void register_student2();
void print_schedule();
void print_studentcourse();
void class_schedule(char **argv);
struct student_struct *get_student_info(int id);
struct strlst_struct *get_student_course_info(int id, char *term);
struct strlst_struct *new_item(struct student_course_struct *newStudentCourse);
void push(struct strlst_struct **list_ptr,  struct strlst_struct *item_ptr);
void printList(struct strlst_struct *head);
void class_list(char **argv);
struct course_struct *get_course_info(char *course_code, char *term);
struct course_strlst *new_item2(struct course_struct *newCourse);
void push2(struct course_strlst **list_ptr, struct course_strlst *item_ptr);
void printList2(struct course_strlst *head);
struct strlst_struct *get_student_course_info2(char *course_code, char *term);
struct student_strlst *new_item3( struct student_struct *newStudent);
void push3(struct student_strlst **list_ptr, struct student_strlst *item_ptr);
void printList3(struct student_strlst *head);
void grade(char **argv);
struct strlst_struct *get_student_course_info3();
void report(char **argv);

#endif
