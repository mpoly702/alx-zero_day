#include <stdarg.h>
 #include <stdio.h>
 #include <string.h>
 #include <stdint.h>
 int _putchar(char c)
 {
     return putchar(c);
 }
 typedef int (*print_func_t)(va_list);
 int print_char(va_list ap)
 {
     int ch = va_arg(ap, int);
     _putchar(ch);
     return 1;
 }
 int print_string(va_list ap)
 {
     char* str = va_arg(ap, char*);
     int len = 0;
     for (; *str; ++str)
     {
         _putchar(*str);
         ++len;
     }
     return len;
 }
 int print_decimal(va_list ap)
 {
     int num = va_arg(ap, int);
     unsigned int abs_num = num < 0 ? -num : num;
     int len = 0;
     if (num < 0)
     {
         _putchar('-');
         ++len;
     }
     unsigned int divisor = 1;
     while (abs_num / divisor >= 10)
         divisor *= 10;
     while (divisor)
     {
         _putchar(abs_num / divisor + '0');
         ++len;
         abs_num %= divisor;
         divisor /= 10;
     }
     return len;
 }
 int print_unsigned_decimal(va_list ap)
 {
     unsigned int num = va_arg(ap, unsigned int);
     int len = 0;
     unsigned int divisor = 1;
     while (num / divisor >= 10)
         divisor *= 10;
     while (divisor)
     {
         _putchar(num / divisor + '0');
         ++len;
         num %= divisor;
         divisor /= 10;
     }
     return len;
 }
 int print_octal(va_list ap)
 {
     unsigned int num = va_arg(ap, unsigned int);
     int len = 0;
     char octal[12];
     int i = 0;
     if (num == 0)
     {
         _putchar('0');
         return 1;
     }
     while (num != 0)
     {
         octal[i++] = (num % 8) + '0';
         num /= 8;
     }
     for (int j = i - 1; j >= 0; j--)
     {
         _putchar(octal[j]);
         len++;
     }
     return len;
 }
 int print_hexadecimal(va_list ap)
 {
     unsigned int num = va_arg(ap, unsigned int);
     char hex[8]; // Assuming 32-bit integers
     int len = 0;
     int i = 0;
     if (num == 0)
     {
         _putchar('0');
         return 1;
     }
     while (num > 0)
     {
         int remainder = num % 16;
         if (remainder < 10)
             hex[i++] = remainder + '0';
         else
             hex[i++] = remainder - 10 + 'a';
         num /= 16;
     }
     for (int j = i - 1; j >= 0; j--)
     {
         _putchar(hex[j]);
         len++;
     }
     return len;
 }
 int print_pointer(va_list ap)
 {
     void* ptr = va_arg(ap, void*);
     uintptr_t addr = (uintptr_t)ptr;
     int len = 0;
     int digits = sizeof(uintptr_t) * 2; // Number of hex digits in a pointer
     _putchar('0');
     _putchar('x');
     len += 2;
     for (int i = digits - 1; i >= 0; i--)
     {
         int digit = (addr >> (i * 4)) & 0xF;
         if (len > 2 || digit != 0 || i == 0)
         {
             _putchar((digit < 10) ? (digit + '0') : (digit - 10 + 'a'));
             ++len;
         }
     }
     return len;
 }
 int my_printf(char* format, ...)
 {
     va_list ap;
     va_start(ap, format);
     int length = 0;
     while (*format)
     {
         if (*format == '%')
         {
             ++format;
             if (*format == '\0')
                 break;
             switch (*format)
             {
                 case 'c':
                     length += print_char(ap);
                     break;
                 case 's':
                     length += print_string(ap);
                     break;
                 case 'd':
                     length += print_decimal(ap);
                     break;
                 case 'u':
                     length += print_unsigned_decimal(ap);
                     break;
                 case 'o':
                     length += print_octal(ap);
                     break;
                 case 'x':
                     length += print_hexadecimal(ap);
                     break;
                 case 'X':
                     length += print_hexadecimal(ap);
                     break;
                 case 'p':
                     length += print_pointer(ap);
                     break;
                 default:
                     _putchar(*format);
                     ++length;
                     break;
             }
         }
         else
         {
             _putchar(*format);
             ++length;
         }
         ++format;
     }
     va_end(ap);
     return length;
 }
 int main(void)
 {
  int len;
  int ui;
  int len1;
  ui = 1024;
     len = my_printf("Let's try to print a simple sentence.\n");
     len1 = my_printf("%d\n", len);
     len = my_printf("%d\n", len1);
     len1 = my_printf("%d\n", -762534);
     len1 = my_printf("%u\n", ui);
     len1 = my_printf("%o\n", ui);
     len1 = my_printf("%x\n", ui);
     len1 = my_printf("%p\n", (void*)&ui);
     len1 = my_printf("%c\n", 'H');
     len1 = my_printf("%s\n", "I am a string !");
     return (0);
 }
