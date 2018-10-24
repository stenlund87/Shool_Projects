#include <iostream>
#include <zconf.h>
#include <cstring>
#include <sys/sysinfo.h>
#include <cmath>
#include <vector>
#include <syscall.h>
#include <cstdio>
#include <cstdlib>


void GetInfo()
{
    //Number of processors
    int processors = sysconf(_SC_NPROCESSORS_ONLN);
    std::cout << "Number of processors: " << processors << std::endl;

    //Hostname
    char hostname[HOST_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    //std::cout << "Hostname: %s" << hostname << std::endl;
    printf("Hostname: %s\n", hostname);

    //Hardware platform
    system("cat /proc/cpuinfo | grep 'model name' | uniq");

    struct sysinfo info;
    unsigned long bytes;

    sysinfo(&info);

    bytes = info.mem_unit * info.totalram;
    //std::cout << "Total ammount of memory %s" << bytes/1024/1024/1024 << std::endl;
    printf("Total ammount of memory: %i GB\n", (int)round(bytes/1024.0/1024.0/1024.0));

}

void ForkCalculations(int forks)
{
    pid_t pid;
    int k = 0;
    while(k<forks)
    {
        pid = fork();
        k++;
    }
    unsigned long sum = 0;
    for(int i = 1; i <= 50000; i++)
    {
        for(int j = 1; j<= i; j++)
        {

            sum += sqrt((i*j));

        }
    }
    if (pid == -1)
    {
        perror("Forking failed!!");
    }
    else if (pid == 0)
    {
        printf("Child PID %d", (int)getpid());
    }
    else
    {
        printf("Parent PID %d", (int)getpid());
    }
    std::cout << " returned sum: " << sum << std::endl;
}


void *ThreadCalculations(void* ptr = 0)
{
    unsigned long sum = 0;
    for(int i = 1; i <= 50000; i++)
    {
        for(int j = 1; j<= i; j++)
        {
            sum += sqrt((i*j));
        }
    }
    std::cout << "Thread: "<< (int)syscall(SYS_gettid) << ", returned sum: " << sum << std::endl;
    return 0;
}

void* ThreadTheThing(int numThreads)
{
    std::vector<pthread_t> threads;
    //Creating threads equals to numThreads
    for(int i = 0; i < numThreads; i++)
    {
        pthread_t thread;
        pthread_create(&thread, NULL, ThreadCalculations, NULL);
        threads.push_back(thread);
    }

    //Joining the threads
    for(int j = 0; j < numThreads; j++)
    {
        pthread_join(threads[j], NULL);
    }
    return 0;
}





int main(int args, char* argv[])
{
    int x = -1;
    std::string command;
    for (int i = 1; i < args; i++)
    {
        command = argv[i];

        if (command == "-i")
        {
            std::cout << "You entered -i" << std::endl;
            GetInfo();
            break;
        }
        else if (command == "-f")
        {
            if(argv[i+1] != NULL)
            {
                std::string temp = argv[i+1];
                x = stoi(temp);
                ForkCalculations(x);
            }
            else
            {
                std::cout << "Error!!! No numeric input detected!" << std::endl;
                break;
            }

            std::cout << "Entered -f" << std::endl;

        }
        else if (command == "-t")
        {
            if(argv[i+1] != NULL)
            {
                std::string temp = argv[i+1];
                x = stoi(temp);
                ThreadTheThing(x);
            }
            else
            {
                std::cout << "Error!!! No numeric input detected!" << std::endl;
                break;
            }

            break;

        }
        else
        {
            std::cout << "Invalid command!" << std::endl;
        }
        return 0;
    }
}
