#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>


char *encrypted_passwords = "$6$AS$6vw7kgh4GwcoH5vZCBFndkwKaeVW9urrs1cMGcDbjjiZi4Ttg7TCdHhx67WxoUpqFjTKcWVnFFMFkUqHRRQ7k/" ;


void substr(char *dest, char *src, int start, int length)
{
    memcpy(dest, src + start, length);
    *(dest + length) = '\0';
}

void passwordThread()
{
    int i;
    pthread_t ti, tii;

    void *kernelFuncionOne();
    void *kernelFuncionTwo();
    
    pthread_create(&ti, NULL, kernelFuncionOne, encrypted_passwords);
    pthread_create(&tii, NULL, kernelFuncionTwo, encrypted_passwords);

    pthread_join(ti, NULL);
    pthread_join(tii, NULL);
}

void *kernelFuncionOne(char *salt_and_encrypted)
{
    int s, a, g;	
    char salt[7];	 
    char plain[7];	
    char *enc;	
    int count = 0;	

    substr(salt, salt_and_encrypted, 0, 6);

    for (s = 'A'; s <= 'M'; s++)
    {
        for (a = 'A'; a <= 'Z'; a++)
        {
            for (g = 0; g <= 99; g++)
            {
                sprintf(plain, "%c%c%02d", s, a, g);
                enc = (char*) crypt(plain, salt);
                count++;
                if (strcmp(salt_and_encrypted, enc) == 0)
                {
                    printf("#%-8d%s %s\n", count, plain, enc);
                }
                else
                {
                    printf(" %-8d%s %s\n", count, plain, enc);
                }
            }
        }
    }
    printf("%d solutions explored\n", count);
}

void *kernelFuncionTwo(char *salt_and_encrypted)
{
    int t, m, g;	
    char salt[7];	
    char plain[7];	
    char *enc;	
    int count = 0;	

    substr(salt, salt_and_encrypted, 0, 6);

    for (t = 'N'; t <= 'Z'; t++)
    {
        for (m = 'A'; m <= 'Z'; m++)
        {
            for (g = 0; g <= 99; g++)
            {
                sprintf(plain, "%c%c%02d", t, m, g);
                enc = (char*) crypt(plain, salt);
                count++;
                if (strcmp(salt_and_encrypted, enc) == 0)
                {
                    printf("#%-8d%s %s\n", count, plain, enc);
                }
                else
                {
                    printf(" %-8d%s %s\n", count, plain, enc);
                }
            }
        }
    }
    printf("%d solutions explored\n", count);
}

//Calculating time

int time_difference(struct timespec *start, struct timespec *finish, long long int *difference)
{
    long long int ds = finish->tv_sec - start->tv_sec;
    long long int dn = finish->tv_nsec - start->tv_nsec;

    if (dn < 0)
    {
        ds--;
        dn += 1000000000;
    }
    *difference = ds *1000000000 + dn;
    return !(*difference > 0);
}
int main(int argc, char *argv[])
{

    struct timespec start, finish;
    long long int time_elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);

    passwordThread();

    clock_gettime(CLOCK_MONOTONIC, &finish);
    time_difference(&start, &finish, &time_elapsed);
    printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
        (time_elapsed / 1.0e9));
    return 0;
}
