#include <iostream>
#include <ctime>
using namespace std;
int main()
{
 srand(time(0));
 long long n = rand() % 9 + 2;
 //long long n = 100;
 long long array[n][n];
 cout<<"\tArray"<<endl;
 for (int i = 0; i < n; i++)
 {
  for (int j = 0; j < n; j++)
  {
   array[i][j] = rand() % 9 + 1;
   cout<<array[i][j]<<" ";
  }
  cout<<endl;
 }
 long long *ptr_array = &array[0][n-1];
 long long *begin_array = &array[0][0];
 long long *end_array = &array[n-1][n-1];

 if (n<=1)
 {
  cout<< "Bad array size!"<<endl;
  return -1;
 }
 asm(
 "mov %[ptr_array], %%rcx\n\t" //последний элемент первой строки
 "mov %[end_array], %%rbx\n\t"
 "mov %%rbx, %[ptr_array]\n\t" // конец текущего столбца
 "mov $8, %%rax\n\t"
 "mulq %[n]\n\t" // Умножили rax на n (получили сдвиг для перехода по строкам)
 "mov %%rcx, %%rbx\n\t"//Поместили в rbx начало столбца, для последующего сдвига на следующий столбец

 "p_start:\n\t"
 "push (%%rcx)\n\t" // поместили значение матрицы в стэк
 "cmp %%rbx, %[begin_array]\n\t" // проверяем достигнут ли последний столбец матрицы
 "je second_cond\n\t" // проверяем достигнут ли конец последнего столбца
 "jmp n_iter\n\t"

 "second_cond:\n\t"
 "cmp %%rcx, %[ptr_array]\n\t"
 "je p_end\n\t" // если оба условия достигнуты заканчиваем пушить
 "jmp n_iter\n\t"

 "n_iter:\n\t"
 "cmp %%rcx, %[ptr_array]\n\t" // проверяем достигнут ли конец столбца
 "je step\n\t" // если достигнут то перемещаемся на один столбец
 "jmp next_elem\n\t" // если не достигнуть продолжаем пушить

 "next_elem:\n\t"
 "add %%rax, %%rcx\n\t" // перемещаемся на следующий элемент
 "jmp p_start\n\t"

 "step:\n\t" //
 "sub $8, %%rbx\n\t" // перемещение начала нового столбца
 "sub $8, %[ptr_array]\n\t" // перемещение конца нового столбза
 "mov %%rbx, %%rcx\n\t" // перемещение текущей позиции на начало нового столбца
 "jmp p_start\n\t"

 "p_end:\n\t"
 "mov %[begin_array], %%rcx\n\t"
 "pop (%%rcx)\n\t"

 "loop_pop:\n\t"
 "cmp %%rcx, %[end_array]\n\t"
 "je end_asm\n\t"
 "add $8, %%rcx\n\t"
 "pop (%%rcx)\n\t"
 "jmp loop_pop\n\t"
 "end_asm:\n\t"
 :
 :[ptr_array]"m"(ptr_array), [begin_array]"m"(begin_array), [end_array]"m"(end_array), [n]"m"(n)
 :"%rax", "%rbx", "%rcx"
 );
 cout<<endl<<"--------------------------------"<<endl;
 cout<<"\tArray(T)"<<endl;
 for (int i = 0; i < n; i++)
 {
  for (int j = 0; j < n; j++)
  {
   cout<<array[i][j]<<" ";
  }
  cout<<endl;
 }
 return 0;
}

