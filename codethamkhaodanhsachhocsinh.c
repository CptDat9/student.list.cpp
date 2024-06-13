#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 50
#define MAX_STUDENTS 100

// Cấu trúc để lưu trữ thông tin của một học sinh
typedef struct {
    char name[MAX_LENGTH]; 
    char class[MAX_LENGTH];
    char phone[MAX_LENGTH];
    float average_grade;
} Student;

// Danh sách học sinh
Student student_list[MAX_STUDENTS];
int num_students = 0;

// Hàm nhập thông tin của một học sinh từ bàn phím
void input_student(Student *s) {
    printf("Nhap ten: ");
    scanf("%s", &s->name);
    printf("Nhap lop: ");
    scanf("%s", &s->class);
    printf("Nhap so dien thoai: ");
    scanf("%s", &s->phone);
    printf("Nhap diem trung binh: ");
    scanf("%f", &s->average_grade);
}

// Hàm in thông tin của một học sinh
void print_student(Student s) {
    printf("Ten: %s, Lop: %s, So dien thoai: %s, Diem TB: %.2f\n", s.name, s.class, s.phone, s.average_grade);
}

// Hàm in danh sách học sinh
void print_student_list() {
    printf("Danh sach hoc sinh:\n");
    for (int i = 0; i < num_students; i++) {
        print_student(student_list[i]);
    }
}

// Hàm xếp loại học sinh
void classify_students() {
    printf("Xep loai hoc sinh:\n");
    for (int i = 0; i < num_students; i++) {
        if (student_list[i].average_grade >= 8.5) {
            printf("%s: Xuat sac\n", student_list[i].name);
        } else if (student_list[i].average_grade >= 7) {
            printf("%s: Gioi\n", student_list[i].name);
        } else if (student_list[i].average_grade >= 5.5) {
            printf("%s: Kha\n", student_list[i].name);
        } else if (student_list[i].average_grade >= 4) {
            printf("%s: Trung binh\n", student_list[i].name);
        } else {
            printf("%s: Yeu\n", student_list[i].name);
        }
    }
}

// Hàm tìm học sinh trong một lớp
void find_student_in_class(char *name, char *class) {
    printf("Nhap ten hoc sinh can tim: ");
    char student_name[MAX_LENGTH];
    scanf("%s", student_name);
    printf("Nhap ten lop: ");
    char class_name[MAX_LENGTH];
    scanf("%s", class_name);

    int found = 0;
    for (int i = 0; i < num_students; i++) {
        if (strcmp(student_list[i].name, student_name) == 0 && strcmp(student_list[i].class, class_name) == 0) {
            printf("So dien thoai cua hoc sinh %s trong lop %s la: %s\n", student_name, class_name, student_list[i].phone);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay hoc sinh %s trong lop %s\n", student_name, class_name);
    }
}

// Hàm thêm một học sinh mới vào danh sách
void add_student(Student s) {
    if (num_students < MAX_STUDENTS) {
        student_list[num_students++] = s;
    } else {
        printf("Danh sach hoc sinh da day, khong the them vao.\n");
    }
}

// Hàm xóa tất cả học sinh trong một lớp
void remove_students_in_class(char *class) {
    int i = 0;
    while (i < num_students) {
        if (strcmp(student_list[i].class, class) == 0) {
            for (int j = i; j < num_students - 1; j++) {
                student_list[j] = student_list[j + 1];
            }
            num_students--;
        } else {
            i++;
        }
    }
}

// Hàm sắp xếp học sinh theo điểm trung bình giảm dần
void sort_students() {
    for (int i = 0; i < num_students - 1; i++) {
        for (int j = i + 1; j < num_students; j++) {
            if (student_list[i].average_grade < student_list[j].average_grade) {
                Student temp = student_list[i];
                student_list[i] = student_list[j];
                student_list[j] = temp;
            }
        }
    }
}

// Hàm chèn một học sinh mới vào danh sách mà không làm thay đổi thứ tự
void insert_student(Student s) {
    if (num_students < MAX_STUDENTS) {
        student_list[num_students++] = s;
        sort_students(); // Sắp xếp lại danh sách sau khi thêm mới để đảm bảo thứ tự giảm dần điểm trung bình
    } else {
        printf("Danh sach hoc sinh da day, khong the them vao.\n");
    }
}

// Hàm lưu trữ danh sách học sinh vào file
void save_student_list(char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong mo duoc file.\n");
        return;
    }

    for (int i = 0; i < num_students; i++) {
        fprintf(file, "%s %s %s %.2f\n", student_list[i].name, student_list[i].class, student_list[i].phone, student_list[i].average_grade);
    }

    fclose(file);
}

// Hàm đọc danh sách học sinh từ file
void load_student_list(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong mo duoc file.\n");
        return;
    }

    while (fscanf(file, "%s %s %s %f", student_list[num_students].name, student_list[num_students].class, student_list[num_students].phone, &student_list[num_students].average_grade) != EOF) {
        num_students++;
    }

    fclose(file);
}

int main() {
    char filename[] = "students.txt";

    load_student_list(codethamkhaodanhsachhocsinh.c);

    // Thực hiện các thao tác với danh sách học sinh
    // Ví dụ: thêm học sinh mới
    Student new_student;
    input_student(&new_student);
    add_student(new_student);

    // Lưu trữ danh sách học sinh vào file
    save_student_list(codethamkhaodanhsachhocsinh.c);

    return 0;
}
