
(
"rdtsc;"
"mov %%eax, %%ebx;"
"rdtsc;"
"sub %%ebx, %%eax;"
"shl $1, %%eax;"
"mov %%eax, %0;"

: "=a"(num)
);
