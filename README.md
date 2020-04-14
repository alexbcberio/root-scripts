# Root Scripts
Small C program to run any `.sh` script as root.

## Use
Compile the file running the `compile.sh` script this will automatically add root as the file owner and give the setuid permission to the compiled file.

The file will always try to execute a file with the same name as it appending the `.sh` extension, you can rename it to whatever you want.

For example rename it to `post-receive` and save it into the `hooks` folder of your git, then create a file called `post-receive.sh` and do anything you want in there.
