### Variables should be changed accordingly ###
ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
TARGET = i586-pc-quest
TOOLCHAIN_INSTALL_DIR = $(ROOT_DIR)/install-newlib-clang

LLVM_BIN = <LLVM BIN>
export PATH := $(LLVM_BIN):$(PATH)

INSTALL_CMD = cp
CC = $(LLVM_BIN)/clang
CXX = $(LLVM_BIN)/clang++
LD = $(LLVM_BIN)/llvm-ld.lld
AR = $(LLVM_BIN)/llvm-ar
RANLIB = $(LLVM_BIN)/llvm-ranlib
TARGET_DEST = $(TOOLCHAIN_INSTALL_DIR)/$(TARGET)
LIB_DEST = $(TARGET_DEST)/lib
INC_DEST = $(TARGET_DEST)/include

LIBC = newlib-1.18.0
LIBC_BUILD_DIR = build-linux
LIBC_WEB_LOCATION = ftp://sources.redhat.com/pub/newlib/$(LIBC).tar.gz

### Variables above this should be changed accordingly ###

### OS Specific files/folders ###
ARCH_INDEPENDENT_QUEST_FILES = quest-files
ARCH_INDEPENDENT_QUEST_LIBC_FILES = $(shell find $(ARCH_INDEPENDENT_QUEST_FILES) -type f)
ARCH_DEPENDENT_QUEST_FILES = arch/$(TARGET)
ARCH_DEPENDENT_QUEST_LIBC_FILES = $(shell find $(ARCH_DEPENDENT_QUEST_FILES) -type f)
### OS Specific files/folders ###

### newlib has specific requirements of certain versions of autoconf and automake ###
export PATH := /opt/autoconf-2.63/bin:$(PATH)
export PATH := /opt/automake-1.11/bin:$(PATH)
### autoconf automake ###

### You mostly don't need to change anything beyond this line except
### in the CC_FOR_TARGET line below you have to change the target again
### This is because the target format could be different what clang expects
### than what newlib is expecting

all: $(LIB_DEST)/libc.a

install:
	@echo "libc.a is installed via make all"

$(LIB_DEST)/libc.a: $(LIBC_BUILD_DIR)/Makefile $(ARCH_INDEPENDENT_QUEST_LIBC_FILES) $(ARCH_DEPENDENT_QUEST_LIBC_FILES)
	cd $(ARCH_INDEPENDENT_QUEST_FILES); \
		find . -type d -exec mkdir -p ../$(LIBC)/newlib/libc/sys/quest/{} \;
	cd $(ARCH_INDEPENDENT_QUEST_FILES); find . -type f -name "*.[ch]" \
		-exec cp {} ../$(LIBC)/newlib/libc/sys/quest/{} \;
	cd $(ARCH_DEPENDENT_QUEST_FILES); \
		find . -type d -exec mkdir -p ../../$(LIBC)/newlib/libc/sys/quest/{} \;
	cd $(ARCH_DEPENDENT_QUEST_FILES); find . -type f -name "*.[ch]" \
		-exec cp {} ../../$(LIBC)/newlib/libc/sys/quest/{} \;
	cp $(ARCH_INDEPENDENT_QUEST_FILES)/vanilla-syscalls.c $(LIBC)/newlib/libc/sys/quest/syscalls.c
	cd $(LIBC_BUILD_DIR); $(MAKE)
	cp $(ARCH_DEPENDENT_QUEST_FILES)/syscalls.c $(LIBC)/newlib/libc/sys/quest/syscalls.c
	cd $(LIBC_BUILD_DIR); $(MAKE)
# Install portion
	mkdir -p $(TOOLCHAIN_INSTALL_DIR)
	cd $(LIBC_BUILD_DIR); $(MAKE) install
	cd $(ARCH_INDEPENDENT_QUEST_FILES); find . -type d -exec mkdir -p $(INC_DEST)/{} \;
	cd $(ARCH_INDEPENDENT_QUEST_FILES); find . -type f -name "*.[h]" \
		-exec cp {} $(INC_DEST)/{} \;
	cd $(ARCH_DEPENDENT_QUEST_FILES); find . -type d -exec mkdir -p $(INC_DEST)/{} \;
	cd $(ARCH_DEPENDENT_QUEST_FILES); find . -type f -name "*.[h]" \
		-exec cp {} $(INC_DEST)/{} \;


$(LIBC_BUILD_DIR)/Makefile: newlib.patch \
                            #$(ARCH_INDEPENDENT_QUEST_FILES)/Makefile.am \
                            #$(ARCH_INDEPENDENT_QUEST_FILES)/Makefile.in \
                            #$(ARCH_INDEPENDENT_QUEST_FILES)/configure.in
	$(MAKE) clean
	$(MAKE) uninstall
	wget -c $(LIBC_WEB_LOCATION)
	mkdir -p $(LIBC_BUILD_DIR)
	tar zxf $(LIBC).tar.gz
	patch -p0 -d $(LIBC) < newlib.patch
	mkdir -p $(LIBC)/newlib/libc/sys/quest/
	cp -r $(ARCH_INDEPENDENT_QUEST_FILES)/* $(LIBC)/newlib/libc/sys/quest
	cp -r $(ARCH_DEPENDENT_QUEST_FILES)/* $(LIBC)/newlib/libc/sys/quest
	cd $(LIBC)/newlib/libc/sys; autoconf
	cd $(LIBC)/newlib/libc/sys/quest; autoreconf
	cd $(LIBC_BUILD_DIR); ../$(LIBC)/configure --target=$(TARGET) \
		--prefix=$(TOOLCHAIN_INSTALL_DIR) \
		CFLAGS_FOR_TARGET=" -O0 " \
		CC_FOR_TARGET="$(LLVM_BIN)/clang --target=i586-unknown-quest-elf -ffreestanding -Wl,-undefined,dynamic_lookup" \
		AR_FOR_TARGET=$(LLVM_BIN)/llvm-ar \
		RANLIB_FOR_TARGET=$(LLVM_BIN)/llvm-ranlib \
		LD_FOR_TARGET=$(LLVM_BIN)/llvm-ld.lld \
		NM_FOR_TARGET=$(LLVM_BIN)/llvm-nm

clean:
	-make -C $(LIBC_BUILD_DIR) clean
	rm -f $(LIB_DEST)/libc.a
	rm -f $(LIB_DEST)/libm.a
	find $(ARCH_INDEPENDENT_QUEST_FILES)/ -name "*~" -exec rm {} \;
	find $(ARCH_DEPENDENT_QUEST_FILES)/ -name "*~" -exec rm {} \;

uninstall:
	rm -rf $(LIBC_BUILD_DIR)
	rm -rf $(LIBC)
