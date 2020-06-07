#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>


int main()
{
  int32_t *a;
  int32_t *b;
  int32_t *c;

  a = malloc(6 * 4);
  b = malloc(12 * 4);
  c = calloc(6 + 12, 4);

  srand(time(0));
  for (int i = 0; i < 6; ++i) {
    a[i] = rand() % 1000;
  }
  for (int i = 0; i < 12; ++i) {
    b[i] = rand() % 1000;
  }

  __asm__ __volatile__(
    "   push %%esi\n\t"       //push esi Засылка операнда в регистр esi
    "   push %%ebx\n\t"       //PUSH  ebx Засылка операнда в регистр ebx (в младший бит bx )
    "   push %%edi\n\t"       //PUSH  edi Засылка операнда в регистр edi (в младший бит di )
    "   push %%ecx\n\t"       //PUSH  ecx Засылка операнда в регистр ecx (в младший бит cx )
    "   cld\n\t"              // cld сброс флага направления в цепочной команде
    "   rep movsl\n\t"        // переход в следующую строку
    "   mov %%edx, %%ecx\n\t" // перенос содержимого из регистра ecx в edx
    "   mov %%ebx, %%esi\n\t" // перенос содержимого из регистра esi в ebx
    "   rep movsl\n\t"        // переход в следующую строку
    "   pop %%ecx\n\t"        // извлечение данных из ecx
    "   pop %%edi\n\t"        // извлечение данных из edi
    "   pop %%ebx\n\t"        // извлечение данных из ebx
    "   pop %%esi\n\t"        // извлечение данных из esi
    :
    : "S"(a), "b"(b), "D"(c), "c"(6), "d"(12)
  );

  printf("Array A:");
  for (int i = 0; i < 6; ++i) {
    printf("%5d", a[i]);
  }

  printf("\nArray B:");
  for (int i = 0; i < 12; ++i) {
    printf("%5d", b[i]);
  }

  printf("\nArray C:");
  for (int i = 0; i < 6 + 12; ++i) {
    printf("%5d", c[i]);
  }

  printf("\n");

  return 0;
}

