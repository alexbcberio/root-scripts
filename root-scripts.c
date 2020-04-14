#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define STDOUT 1
#define PATH_SEP "/"

int main(int argc, char *argv[]) {

    char *pathname = strtok(argv[0], PATH_SEP);
    char scriptName[strlen(argv[0])];

    while (pathname) {
        strcpy(scriptName, pathname);
        pathname = strtok(NULL, PATH_SEP);
    }

    strcat(scriptName, ".sh");

    if (access(scriptName, F_OK | R_OK | X_OK) == -1) {
        char *errorPre = "File \"";
        write(STDOUT, errorPre, strlen(errorPre));
        write(STDOUT, scriptName, strlen(scriptName));
        char *errorPost = "\" does not exist or has no correct permissions, read and execute.\n";
        write(STDOUT, errorPost, strlen(errorPost));

        return 1;
    }

    setuid(0);

    char *executing = "Executing file: ";
    write(STDOUT, executing, strlen(executing));
    write(STDOUT, scriptName, strlen(scriptName));
    write(STDOUT, "\n", strlen("\n"));

    char *newargv[] = {NULL};
    char *newenviron[] = {NULL};
    execve(scriptName, newargv, newenviron);

    write(STDOUT, "Error: ", strlen("Error: "));
    char *error;

    switch (errno) {
        case E2BIG:
            error = "The total number of bytes in the environment (envp) and argument list (argv) is too large.";
            break;
        case EACCES:
            error = "Check one of the following errors:\n - Search permission is denied on a component of the path prefix of filename or the name of a script interpreter.\n - The file or a script interpreter is not a regular file.\n - Execute permission is denied for the file or a script or ELF interpreter.\n - The file system is mounted noexec.";
            break;
        case EFAULT:
            error = "filename points outside your accessible address space.";
            break;
        case EINVAL:
            error = "An ELF executable had more than one PT_INTERP segment (i.e., tried to name more than one interpreter).";
            break;
        case EIO:
            error = "An I/O error occurred.";
            break;
        case EISDIR:
            error = "An ELF interpreter was a directory.";
            break;
        case ELIBBAD:
            error = "An ELF interpreter was not in a recognized format.";
            break;
        case ELOOP:
            error = "Too many symbolic links were encountered in resolving filename or the name of a script or ELF interpreter.";
            break;
        case EMFILE:
            error = "The process has the maximum number of files open.";
            break;
        case ENAMETOOLONG:
            error = "filename is too long.";
            break;
        case ENFILE:
            error = "The system limit on the total number of open files has been reached.";
            break;
        case ENOENT:
            error = "The file filename or a script or ELF interpreter does not exist, or a shared library needed for file or interpreter cannot be found.";
            break;
        case ENOEXEC:
            error = "An executable is not in a recognized format, is for the wrong architecture, or has some other format error that means it cannot be executed.";
            break;
        case ENOMEM:
            error = "Insufficient kernel memory was available.";
            break;
        case ENOTDIR:
            error = "A component of the path prefix of filename or a script or ELF interpreter is not a directory.";
            break;
        case EPERM:
            error = "Check one of the following errors:\n - The file system is mounted nosuid, the user is not the superuser, and the file has the set-user-ID or set-group-ID bit set.\n - The process is being traced, the user is not the superuser and the file has the set-user-ID or set-group-ID bit set.";
            break;
        case ETXTBSY:
            error = "Executable was open for writing by one or more processes.";
            break;
        default:
            error = "Unknown error ＞﹏＜";
    }

    write(STDOUT, error, strlen(error));
    write(STDOUT, "\n", strlen("\n"));

    return 0;
}
