#include "aim.h"
/********************MAIN FUNCTIONS****************************/

/*Creates 3 bins with 0 bytes*/
void init_aim()
{
  FILE *fp1;
  FILE *fp2;
  FILE *fp3;

  fp1 = fopen("students.bin","wb");
  fp2 = fopen("courses.bin","wb");
  fp3 = fopen("student_course.bin","wb");

  fclose(fp1);
  fclose(fp2);
  fclose(fp3);
}

/*Register a student*/
void register_student()
{
  FILE *fp1;
  struct student_struct *tempStudent = NULL;
  struct student_struct newStudent;
  int maxId = 0;

  fp1 = fopen("students.bin","rb+");
  tempStudent = malloc(sizeof(struct student_struct));

  /*Calculate Max id*/
  while(!feof(fp1))
  {
    if(fread(tempStudent, sizeof(struct student_struct), 1 ,fp1) != 0)
    {
      if(tempStudent->id > maxId)
      {
        maxId = tempStudent->id;
      }
    }
  }

  /*Prompt user and record*/
  printf("Last Name: ");
  fgets(newStudent.last_name, 64, stdin);
  printf("First Name: ");
  fgets(newStudent.first_name, 64, stdin);
  printf("Middle Names: ");
  fgets(newStudent.middle_names, 64, stdin);
  printf("Major: ");
  fgets(newStudent.major, 64, stdin);

  newStudent.last_name[strlen(newStudent.last_name)-1] = '\0';
  newStudent.first_name[strlen(newStudent.first_name)-1] = '\0';
  newStudent.middle_names[strlen(newStudent.middle_names)-1] = '\0';
  newStudent.major[strlen(newStudent.major)-1] = '\0';
  newStudent.id = maxId + 1;

  /*Write in file*/
  fwrite(&newStudent , sizeof(struct student_struct), 1 ,fp1);
  fclose(fp1);
  free(tempStudent);
}

/*Sort students*/
void sort()
{
  FILE *fp1;

  struct student_struct * tempArray = NULL;
  int fileSize = 0;
  int numStudents = 0;

  fp1 = fopen("students.bin","rb+");

  /*Go to end of file and determine number of records*/
  fseek(fp1, 0, SEEK_END);
  fileSize = ftell(fp1);
  numStudents = fileSize/sizeof(struct student_struct);

  tempArray = (struct student_struct *) calloc(numStudents, sizeof(struct student_struct));

  /*Go to beginning of file to read,store and sort the records in an array*/
  fseek(fp1, 0, SEEK_SET);
  fread(tempArray, sizeof(struct student_struct), numStudents ,fp1);
  qsort(tempArray, numStudents, sizeof(struct student_struct), compar);

  /*Go to beginning of file so we can overwrite it with sorted records*/
  fseek(fp1, 0, SEEK_SET);
  fwrite(tempArray , sizeof(struct student_struct), numStudents ,fp1);

  fclose(fp1);
  free(tempArray);
}

/*Register a course*/
void schedule()
{
  FILE *fp1;
  struct course_struct newCourse;
  char temp[128];

  fp1 = fopen("courses.bin","ab+");

  /*Prompt user and record*/
  printf("Code: ");
  fgets(temp, 128, stdin);
  temp[strlen(temp)-1] = '\0';
  if(strlen(temp) > 9)
  {
    temp[9] = '\0';
  }
  strcpy(newCourse.code, temp);

  printf("Term: ");
  fgets(temp, 128, stdin);
  temp[strlen(temp)-1] = '\0';
  if(strlen(temp) > 5)
  {
    temp[5] = '\0';
  }
  strcpy(newCourse.term, temp);

  printf("Title: ");
  fgets(temp, 128, stdin);
  temp[strlen(temp)-1] = '\0';
  if(strlen(temp) > 127)
  {
    temp[127] = '\0';
  }
  strcpy(newCourse.title, temp);

  printf("Instructor: ");
  fgets(temp, 128, stdin);
  temp[strlen(temp)-1] = '\0';
  if(strlen(temp) > 63)
  {
    temp[63] = '\0';
  }
  strcpy(newCourse.instructor, temp);

  /*Write in file*/
  fwrite(&newCourse , sizeof(struct course_struct), 1 ,fp1);
  fclose(fp1);

}

/*Register student in a course*/
void add()
{
  FILE *fp1;
  struct student_course_struct newStudentCourse;
  char temp[64];
  fp1 = fopen("student_course.bin","ab+");

  /*Prompt user and record*/
  printf("Student ID: ");
  fgets(temp, 64, stdin);
  temp[strlen(temp)-1] = '\0';
  newStudentCourse.student_id = atoi(temp);

  printf("Course Code: ");
  fgets(temp, 64, stdin);
  temp[strlen(temp)-1] = '\0';
  if(strlen(temp) > 9)
  {
    temp[9] = '\0';
  }
  strcpy(newStudentCourse.course_code, temp);

  printf("Term: ");
  fgets(temp, 64, stdin);
  temp[strlen(temp)-1] = '\0';
  if(strlen(temp) > 5)
  {
    temp[5] = '\0';
  }
  strcpy(newStudentCourse.term, temp);

  while(strcmp(newStudentCourse.registration, "CRD") != 0 && strcmp(newStudentCourse.registration, "AUD") != 0)
  {
    printf("Registration [CRD or AUD]: ");
    fgets(temp, 64, stdin);
    temp[strlen(temp)-1] = '\0';
    if(strcmp(temp, "CRD") == 0 || strcmp(temp, "AUD") == 0)
    {
      strcpy(newStudentCourse.registration, temp);
    }
  }
  newStudentCourse.grade = -1;

  /*Write in file*/
  fwrite(&newStudentCourse , sizeof(struct student_course_struct), 1 ,fp1);
  fclose(fp1);
}

/*Make a class schedule of a student given a term*/
void class_schedule(char ** argv)
{
  int id;
  char *term;
  struct student_struct *theStudent;
  struct strlst_struct *theStudentCourseList;
  struct course_struct *theCourseList;

  term = malloc(sizeof(strlen(argv[2])));
  id = atoi(argv[1]);
  strcpy(term, argv[2]);

  theStudent = get_student_info(id);
  printf("Name: %s %s %s\n", theStudent->first_name, theStudent->middle_names, theStudent->last_name);
  printf("ID: %07d\n", theStudent->id);
  theStudentCourseList = get_student_course_info(id, term);
  theCourseList = malloc(sizeof(struct course_struct));

  while(theStudentCourseList != NULL)
  {
    theCourseList = get_course_info(theStudentCourseList->studentCourse->course_code, term);
    printf("%s %s\n", theCourseList->code, theCourseList->title);
    printf("%s\n", theCourseList->instructor);
    theStudentCourseList = theStudentCourseList->next;
   }
}

/*Make a class list given a course and a term*/
void class_list(char ** argv)
{
  char *course_code;
  char *term;
  char *filename;
  FILE *fp1;

  struct strlst_struct *theStudentCourseList = NULL;
  struct student_struct *theStudent = NULL;
  struct student_strlst *theStudentList = NULL;
  struct student_strlst *item_ptr = NULL;
  struct course_struct *theCourseList = NULL;

  course_code = malloc(sizeof(strlen(argv[1])));
  term = malloc(sizeof(strlen(argv[2])));
  filename = malloc(sizeof(strlen(argv[3])));

  strcpy(course_code, argv[1]);
  strcpy(term, argv[2]);
  strcpy(filename, argv[3]);

  fp1 = fopen(filename, "w");

  theCourseList = get_course_info(course_code, term);

  printf("%s %s\n", theCourseList->code, theCourseList->title);
  fprintf(fp1, "%s %s\n",theCourseList->code, theCourseList->title);

  theStudentCourseList = get_student_course_info2(course_code, term);

  while(theStudentCourseList != NULL)
  {
    theStudent = get_student_info(theStudentCourseList->studentCourse->student_id);
    item_ptr = new_item3(theStudent);
    push3(&theStudentList, item_ptr);
    theStudentCourseList = theStudentCourseList->next;
  }

  while(theStudentList != NULL)
  {
    printf("%s, %s %s (%s)\n", theStudentList->student->last_name, theStudentList->student->first_name, theStudentList->student->middle_names, theStudentList->student->major);
    fprintf(fp1, "%s, %s %s (%s)\n", theStudentList->student->last_name, theStudentList->student->first_name, theStudentList->student->middle_names, theStudentList->student->major);
    theStudentList = theStudentList->next;
  }
  fclose(fp1);
}

/*Update grades*/
void grade(char ** argv)
{
  char buffer[100];
  char buffer2[100];
  char nameProgram[100];
  char nameProgram2[100];
  char * filename;
  char * token;
  char * token2;
  char *course_code;
  int grade;
  FILE * fp1;
  FILE * fp2;
  FILE * fp3;
  struct student_struct *theStudent;
  struct strlst_struct *theStudentCourseList;
  struct strlst_struct **list_ptr;
  struct strlst_struct *current;

  filename = malloc(sizeof(strlen(argv[1])));
  theStudent = malloc(sizeof(struct student_struct));
  strcpy(filename, argv[1]);

  fp1 = fopen(filename, "r");

  /*Get first line and strtok to get course_code and term*/
  theStudentCourseList = get_student_course_info3();
  fgets(buffer, 100, fp1);
  course_code = strtok(buffer," ");

  while(fgets(buffer2, 100 , fp1) != NULL)
  {
    token2 = strtok(buffer2,")");
    strcpy(nameProgram, token2);
    nameProgram[strlen(nameProgram)] = '\0';

    fp2 = fopen("students.bin","rb+");
    while(!feof(fp2))
    {
      if(fread(theStudent, sizeof(struct student_struct), 1 ,fp2) != 0)
      {
        sprintf(nameProgram2, "%s, %s %s (%s", theStudent->last_name, theStudent->first_name, theStudent->middle_names, theStudent->major);
        nameProgram2[strlen(nameProgram2)] = '\0';

        if(strcmp(nameProgram, nameProgram2) == 0)
        {
          token = strtok(NULL, "\n");
          grade = atoi(token);

          list_ptr = &theStudentCourseList;
          current = *list_ptr;

          while(current != NULL)
          {

            if(strcmp(course_code, current->studentCourse->course_code) == 0 && theStudent->id == current->studentCourse->student_id)
            {
              current->studentCourse->grade = grade;
            }
            current = current->next;
          }
        }
      }
    }
    fclose(fp2);
  }
  fclose(fp1);

  fp3 = fopen("student_course.bin","wb+");
  while(theStudentCourseList != NULL)
  {
    fwrite(theStudentCourseList->studentCourse, sizeof(struct student_course_struct), 1, fp3);
    theStudentCourseList = theStudentCourseList->next;
  }
  fclose(fp3);

  free(filename);
  free(theStudent);
}

/*Make a grade report*/
void report(char **argv)
{
  int id;
  char *term;
  struct student_struct *theStudent;
  struct strlst_struct *theStudentCourseList;
  struct course_struct *theCourseList;

  term = malloc(sizeof(strlen(argv[2])));
  id = atoi(argv[1]);
  strcpy(term, argv[2]);

  theStudent = get_student_info(id);
  printf("Name: %s %s %s\n", theStudent->first_name, theStudent->middle_names, theStudent->last_name);
  printf("ID: %07d\n", theStudent->id);
  theStudentCourseList = get_student_course_info(id, term);

  while(theStudentCourseList != NULL)
  {
    theCourseList = get_course_info(theStudentCourseList->studentCourse->course_code, term);
    printf("%s %s %d\n", theCourseList->code, theCourseList->title, theStudentCourseList->studentCourse->grade);
    printf("%s\n", theCourseList->instructor);

    theStudentCourseList = theStudentCourseList->next;
  }
}

/********************Get info****************************/
struct student_struct * get_student_info(int id)
{
  struct student_struct * theStudent = NULL;
  FILE *fp1;
  int fileSize;
  int n1;
  int n2;
  int mid;
  int midFile;

  theStudent = malloc(sizeof(struct student_struct));

  fp1 = fopen("students.bin","rb+");

  fseek(fp1, 0, SEEK_END);
  fileSize = ftell(fp1);
  n1 = 0;
  n2 = fileSize/sizeof(struct student_struct);

  while(n1 <= n2)
  {
    mid = n1 + (n2-n1)/2;
    midFile = mid * sizeof(struct student_struct);
    fseek(fp1, midFile, SEEK_SET);
    fread(theStudent, sizeof(struct student_struct), 1, fp1);

    if(id == theStudent->id)
    {
      return theStudent;
    }
    else if(id < theStudent->id)
    {
      n2 = mid - 1;
    }
    else if(id > theStudent->id)
    {
      n1 = mid + 1;
    }
  }
  free(theStudent);
  theStudent = NULL;

  fclose(fp1);
  return NULL;
}

struct course_struct *get_course_info(char *course_code, char *term)
{
  struct course_struct *theCourse = NULL;
  FILE *fp1;

  theCourse = malloc(sizeof(struct course_struct));

  fp1 = fopen("courses.bin", "rb+");

  while(!feof(fp1))
  {
    if(fread(theCourse, sizeof(struct course_struct), 1 ,fp1) != 0)
    {
      if(strcmp(course_code, theCourse->code) == 0 && strcmp(term, theCourse->term) == 0)
      {
        return theCourse;
      }
    }
  }

  free(theCourse);
  theCourse = NULL;
  fclose(fp1);

  return NULL;
}

struct strlst_struct *get_student_course_info(int id, char *term)
{
  struct student_course_struct *theStudentCourse = NULL;
  struct strlst_struct *item_ptr, *list_ptr;
  FILE *fp1;

  list_ptr = NULL;

  theStudentCourse = malloc(sizeof(struct student_course_struct));

  fp1 = fopen("student_course.bin","rb+");

  while(!feof(fp1))
  {
    if(fread(theStudentCourse, sizeof(struct student_course_struct), 1 ,fp1) != 0)
    {
      if((id == theStudentCourse->student_id && strcmp(term, theStudentCourse->term) == 0))
      {
        item_ptr = new_item(theStudentCourse);
        push(&list_ptr, item_ptr);
      }
    }
  }
  return list_ptr;

  free(theStudentCourse);
  theStudentCourse = NULL;
}

struct strlst_struct *get_student_course_info2(char *course_code, char *term)
{
  struct student_course_struct * theStudentCourse = NULL;
  struct strlst_struct *item_ptr, *list_ptr;
  FILE *fp1;

  list_ptr = NULL;

  theStudentCourse = malloc(sizeof(struct student_course_struct));

  fp1 = fopen("student_course.bin","rb+");

  while(!feof(fp1))
  {
    if(fread(theStudentCourse, sizeof(struct student_course_struct), 1 ,fp1) != 0)
    {
      if((strcmp(course_code, theStudentCourse->course_code) == 0 && strcmp(term, theStudentCourse->term) == 0))
      {
        item_ptr = new_item(theStudentCourse);
        push(&list_ptr, item_ptr);
      }
    }
  }

  return list_ptr;
  free(theStudentCourse);
  theStudentCourse = NULL;
}

struct strlst_struct *get_student_course_info3()
{
  struct student_course_struct * theStudentCourse = NULL;
  struct strlst_struct *item_ptr, *list_ptr;
  FILE *fp1;

  list_ptr = NULL;

  theStudentCourse = malloc(sizeof(struct student_course_struct));

  fp1 = fopen("student_course.bin","rb+");

  while(!feof(fp1))
  {
    if(fread(theStudentCourse, sizeof(struct student_course_struct), 1 ,fp1) != 0)
    {
      item_ptr = new_item(theStudentCourse);
      push(&list_ptr, item_ptr);
    }
  }
  return list_ptr;
  free(theStudentCourse);
  theStudentCourse = NULL;
}

/**************LINKED LIST *****************************/
struct strlst_struct *new_item(struct student_course_struct *newStudentCourse)
{
    struct strlst_struct *item_ptr;

    item_ptr = malloc(sizeof(struct strlst_struct));
    item_ptr->studentCourse = malloc(sizeof(struct student_course_struct));
    memcpy(item_ptr->studentCourse, newStudentCourse, sizeof(struct student_course_struct));
    (*item_ptr).next = NULL;

    return item_ptr;
}

struct course_strlst *new_item2(struct course_struct *newCourse)
{
    struct course_strlst *item_ptr;

    item_ptr = malloc(sizeof(struct course_strlst));
    item_ptr->course = malloc(sizeof(struct course_struct));
    memcpy(item_ptr->course, newCourse, sizeof(struct course_struct));
    (*item_ptr).next = NULL;

    return item_ptr;
}

struct student_strlst *new_item3(struct student_struct *newStudent)
{
    struct student_strlst *item_ptr;

    item_ptr = malloc(sizeof(struct student_strlst));
    item_ptr->student = malloc(sizeof(struct student_struct));
    memcpy(item_ptr->student, newStudent, sizeof(struct student_struct));
    (*item_ptr).next = NULL;

    return item_ptr;
}

void push(struct strlst_struct **list_ptr,  struct strlst_struct *item_ptr)
{
  struct strlst_struct * current;

  if(*list_ptr == NULL || strcmp((*list_ptr)->studentCourse->course_code , item_ptr->studentCourse->course_code) >= 0)
  {
    item_ptr->next = *list_ptr;
    *list_ptr = item_ptr;
  }
  else
  {
    current = *list_ptr;

    while(current->next != NULL && strcmp(item_ptr->studentCourse->course_code , current->next->studentCourse->course_code) > 0)
    {
      current = current->next;
    }
    item_ptr->next = current->next;
    current->next = item_ptr;
  }
}

void push2(struct course_strlst **list_ptr,  struct course_strlst *item_ptr)
{
  item_ptr->next = *list_ptr;
  *list_ptr = item_ptr;
}

void push3(struct student_strlst **list_ptr,  struct student_strlst *item_ptr)
{
  struct student_strlst * current;

  if(*list_ptr == NULL || strcmp((*list_ptr)->student->last_name , item_ptr->student->last_name) >= 0)
  {
    item_ptr->next = *list_ptr;
    *list_ptr = item_ptr;
  }
  else
  {
    current = *list_ptr;

    while(current->next != NULL && strcmp(item_ptr->student->last_name , current->next->student->last_name) > 0)
    {
      current = current->next;
    }
    item_ptr->next = current->next;
    current->next = item_ptr;
  }
}

/*************Print List**************/
void printList(struct strlst_struct *head)
{
  struct strlst_struct *temp = head;

  if(temp == NULL)
  {
    printf("issa null\n");
  }
   while(temp != NULL)
    {
      printf("%s %s %d\n", temp->studentCourse->course_code, temp->studentCourse->term, temp->studentCourse->grade);
      temp = temp->next;
    }
}

void printList2(struct course_strlst *head)
{
  struct course_strlst *temp = head;

  while(temp != NULL)
  {
    printf("Course code: %s\n", temp->course->code);
    temp = temp->next;
  }
}

void printList3(struct student_strlst *head)
{
  struct student_strlst *temp = head;

  while(temp != NULL)
  {
    printf("%s, %s %s (%s)\n", temp->student->last_name, temp->student->first_name, temp->student->middle_names, temp->student->major);
    temp = temp->next;
  }
}

/*********************HELPER FUNCTIONS*****************************/
void register_student2()
{
  FILE *fp1;
  struct student_struct newStudent2;
  char id[64];

  fp1 = fopen("students.bin","rb+");

  fseek(fp1, 0, SEEK_END);

  printf("Last Name: ");
  fgets(newStudent2.last_name, 64, stdin);
  printf("First Name: ");
  fgets(newStudent2.first_name, 64, stdin);
  printf("Middle Names: ");
  fgets(newStudent2.middle_names, 64, stdin);
  printf("Major: ");
  fgets(newStudent2.major, 64, stdin);
  printf("Student ID: ");
  fgets(id, 64, stdin);
  id[strlen(id)-1] = '\0';
  newStudent2.id = atoi(id);

  newStudent2.last_name[strlen(newStudent2.last_name)-1] = '\0';
  newStudent2.first_name[strlen(newStudent2.first_name)-1] = '\0';
  newStudent2.middle_names[strlen(newStudent2.middle_names)-1] = '\0';
  newStudent2.major[strlen(newStudent2.major)-1] = '\0';

  /*Write in file*/
  fwrite(&newStudent2 , sizeof(struct student_struct), 1 ,fp1);
  fclose(fp1);
}

void print_students()
{
  FILE *fp1;
  struct student_struct * tempStudent;

  fp1 = fopen("students.bin","rb+");
  tempStudent = malloc(sizeof(struct student_struct));

  while(!feof(fp1))
  {
    if(fread(tempStudent, sizeof(struct student_struct), 1 ,fp1) != 0)
    {
      printf("Last Name: %s\n", tempStudent->last_name);
      printf("First Name: %s\n", tempStudent->first_name);
      printf("Middle Names: %s\n", tempStudent->middle_names);
      printf("Major: %s\n", tempStudent->major);
      printf("ID: %07d\n", tempStudent->id);
    }
  }
  fclose(fp1);
}

void print_schedule()
{
  FILE *fp1;
  struct course_struct * tempStruct;

  fp1 = fopen("courses.bin","rb+");
  tempStruct = malloc(sizeof(struct course_struct));

  while(!feof(fp1))
  {
    if(fread(tempStruct, sizeof(struct course_struct), 1 ,fp1) != 0)
    {
      printf("Code: %s\n", tempStruct->code);
      printf("Term: %s\n", tempStruct->term);
      printf("Title: %s\n", tempStruct->title);
      printf("Instructor: %s\n", tempStruct->instructor);

    }
  }
  fclose(fp1);
}

void print_studentcourse()
{
  FILE *fp1;
  struct student_course_struct * tempStudent;

  fp1 = fopen("student_course.bin","rb+");
  tempStudent = malloc(sizeof(struct student_course_struct));

  while(!feof(fp1))
  {
    if(fread(tempStudent, sizeof(struct student_course_struct), 1 ,fp1) != 0)
    {
      printf("Student ID: %d\n", tempStudent->student_id);
      printf("Course Code: %s\n", tempStudent->course_code);
      printf("Term: %s\n", tempStudent->term);
      printf("Registration: %s\n", tempStudent->registration);
      printf("Grade: %d\n", tempStudent->grade);
    }
  }
  fclose(fp1);
}

int compar(const void *a, const void *b)
{
  const struct student_struct *struct_a, *struct_b;

  struct_a = a;
  struct_b = b;

  return (struct_a->id)-(struct_b->id);
}
