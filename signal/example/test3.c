#include <stdio.h>
#include <stdlib.h>
#include <sys/sysctl.h>
#include <linux/sysctl.h>

int main(int argc, char **argv)
{
        int name[] = {CTL_KERN, KERN_PRINTK};
        int namelen = 2;
        int oldval[8];  /* 4 would suffice */
        size_t len = sizeof(oldval);
        int i, error;


        error = sysctl (name, namelen, (void *)oldval, &len,
                NULL /* newval */, 0 /* newlen */);
        if (error) {
                fprintf(stderr,"%s: sysctl(): %s\n",
                        argv[0],strerror(error));
                exit(1);
        }
        printf("len is %i bytes\n", len);
        for (i = 0; i < len/(sizeof(int)); i++)
                printf("%i\t", oldval[i]);
        printf("\n");
        exit(0);
}

