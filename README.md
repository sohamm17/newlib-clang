This is a version of newlib which is compiled with Clang 5.0.1 . This newlib is  compiled for our own Quest OS which will work on bare metal x86 (32-bit). Therefore, we also provide our own system calls in library files (inside `newlib/libc/sys/quest/`).

### Toolchain
Our toolchain is a little complicated because we have architecture (x86 and arm) dependent and independent files. At the same time, the toolchain might be helpful for other people who are trying to build newlib for their bare metal OS. Therefore, I am keeping the whole toolchain. We copy our system calls into newlib and configure (via patch) the toolchain to recognize our Quest OS and build the C files.

##### Changes:
To make it compatible for clang, I edited a few files:

###### newlib/libm/machine/i386/f_ldexp.S
###### newlib/libm/machine/i386/f_ldexpf.S
gcc accepts (and quitely makes assumptions) ambiguous assembly instructions, which clang doesn't I added such `fild` instructions to `filds`.

Additionally, `libgloss/libnosys/configure` seems to have different expectations for target. I had to edit that as well for our target. Other than those, most of the rest of the patch is according to [OS Dev's instruction for porting newlib for a custom OS](https://wiki.osdev.org/Porting_Newlib).

### Configuration

#### Changes you need to make to build newlib for your OS

- Open the `Makefile` and change variables as needed. For example, change your `target`. Our `target` is i586-pc-quest is of the format architecture-vendor-os. This can be confusing because mostly there is no standard. newlib also takes x86-elf as valid. Check whether target could be supported by running `config.sub`.
- Make sure to change `LLVM_BIN`. I have used my custom built LLVM. In your case, it can be as simple as `/usr/bin` if you have install llvm and clang in your host system.
- Follow the Makefile. I have written some importatn instructions there as well.
- Look at the newlib.patch file. It makes some important chanegs.

#### Porting newlib for your new custom OS
Follow [OS Dev's instruction for porting newlib for a custom OS](https://wiki.osdev.org/Porting_Newlib). Here's what we do briefly:

1. We write architecture dependent library functions (system calls, etc.) in a directory (`arch`) and architecture-independent in another directory (`quest-files`). 

2. When we are building newlib, we first create a new directory inside `newlib/libc/sys/`, named `quest` (name of our new custom OS).

3. We then copy the architecture indepedent and dependent files to newly created directory `newlib/libc/sys/quest`. We configure `sys` and `quest` directory after this using `autoconf`. Our architecture dependent and indepedent file directories also have their own configuration. You can make your own configurations for your custom OS. Follow the OS Dev tutorial and our code.

4. We then copy the C files (source and header files) of both architecture dependent and indepedent folders to the newly created folder `newlib/libc/sys/quest`.

5. We `make` newlib two times, one with vanilla-syscalls and another with syscalls, after copying them from our architecture indepedent and dependent folders respectively.

I am indebted to the following sources while I was modifying the toolchain:

- [build newlib for lm32 with clang](https://github.com/jpbonn/Newlib-build-scripts/blob/master/Makefile)
- clang modification source

The toolchain and infrastructure were built by the Quest OS team over a number of years. I have just changed it to be compiled with `clang`. This approach is free to be replicated. Please give credit where it is due.