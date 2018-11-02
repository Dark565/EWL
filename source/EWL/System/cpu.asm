
(
"rdtsc;"
"mov %%eax, %%ebx;"
"rdtsc;"
"sub %%ebx, %%eax;"
"shr $1, %%eax;"
"mov %%eax, %0;"

: "=a"(num)
);
