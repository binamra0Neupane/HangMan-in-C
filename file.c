#include<stdio.h>

int main()
{
    FILE*fptr, *f_out;
    fptr = fopen("number.txt", "r");

    int f_input[200];
    while(fscanf(fptr, "%d",&f_input)!= EOF)
    {
        printf("%d\n",f_input);

    }

    fclose(fptr);
    f_out = fopen("output.txt", "w");
    for(int i = 0; i<100; i++)
    {
    fprintf(f_out, "%d", f_input[i]);

    }

    fclose(f_out);

    return 0;
}