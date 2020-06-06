typedef unsigned char   undefined;

typedef unsigned char    byte;
typedef unsigned char    dwfenc;
typedef unsigned int    dword;
typedef long long    longlong;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned char    undefined1;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined8;
typedef unsigned short    ushort;
typedef unsigned short    word;
typedef struct eh_frame_hdr eh_frame_hdr, *Peh_frame_hdr;

struct eh_frame_hdr {
    byte eh_frame_hdr_version; // Exception Handler Frame Header Version
    dwfenc eh_frame_pointer_encoding; // Exception Handler Frame Pointer Encoding
    dwfenc eh_frame_desc_entry_count_encoding; // Encoding of # of Exception Handler FDEs
    dwfenc eh_frame_table_encoding; // Exception Handler Table Encoding
};

typedef struct fde_table_entry fde_table_entry, *Pfde_table_entry;

struct fde_table_entry {
    dword initial_loc; // Initial Location
    dword data_loc; // Data location
};

typedef void _IO_lock_t;

typedef struct _IO_marker _IO_marker, *P_IO_marker;

typedef struct _IO_FILE _IO_FILE, *P_IO_FILE;

typedef long __off_t;

typedef longlong __quad_t;

typedef __quad_t __off64_t;

typedef ulong size_t;

struct _IO_FILE {
    int _flags;
    char * _IO_read_ptr;
    char * _IO_read_end;
    char * _IO_read_base;
    char * _IO_write_base;
    char * _IO_write_ptr;
    char * _IO_write_end;
    char * _IO_buf_base;
    char * _IO_buf_end;
    char * _IO_save_base;
    char * _IO_backup_base;
    char * _IO_save_end;
    struct _IO_marker * _markers;
    struct _IO_FILE * _chain;
    int _fileno;
    int _flags2;
    __off_t _old_offset;
    ushort _cur_column;
    char _vtable_offset;
    char _shortbuf[1];
    _IO_lock_t * _lock;
    __off64_t _offset;
    void * __pad1;
    void * __pad2;
    void * __pad3;
    void * __pad4;
    size_t __pad5;
    int _mode;
    char _unused2[15];
};

struct _IO_marker {
    struct _IO_marker * _next;
    struct _IO_FILE * _sbuf;
    int _pos;
};

typedef struct _IO_FILE FILE;

typedef struct Elf32_Shdr Elf32_Shdr, *PElf32_Shdr;

typedef enum Elf_SectionHeaderType_x86 {
    SHT_CHECKSUM=1879048184,
    SHT_DYNAMIC=6,
    SHT_DYNSYM=11,
    SHT_FINI_ARRAY=15,
    SHT_GNU_ATTRIBUTES=1879048181,
    SHT_GNU_HASH=1879048182,
    SHT_GNU_LIBLIST=1879048183,
    SHT_GNU_verdef=1879048189,
    SHT_GNU_verneed=1879048190,
    SHT_GNU_versym=1879048191,
    SHT_GROUP=17,
    SHT_HASH=5,
    SHT_INIT_ARRAY=14,
    SHT_NOBITS=8,
    SHT_NOTE=7,
    SHT_NULL=0,
    SHT_PREINIT_ARRAY=16,
    SHT_PROGBITS=1,
    SHT_REL=9,
    SHT_RELA=4,
    SHT_SHLIB=10,
    SHT_STRTAB=3,
    SHT_SUNW_COMDAT=1879048187,
    SHT_SUNW_move=1879048186,
    SHT_SUNW_syminfo=1879048188,
    SHT_SYMTAB=2,
    SHT_SYMTAB_SHNDX=18
} Elf_SectionHeaderType_x86;

struct Elf32_Shdr {
    dword sh_name;
    enum Elf_SectionHeaderType_x86 sh_type;
    dword sh_flags;
    dword sh_addr;
    dword sh_offset;
    dword sh_size;
    dword sh_link;
    dword sh_info;
    dword sh_addralign;
    dword sh_entsize;
};

typedef enum Elf32_DynTag_x86 {
    DT_AUDIT=1879047932,
    DT_AUXILIARY=2147483645,
    DT_BIND_NOW=24,
    DT_CHECKSUM=1879047672,
    DT_CONFIG=1879047930,
    DT_DEBUG=21,
    DT_DEPAUDIT=1879047931,
    DT_ENCODING=32,
    DT_FEATURE_1=1879047676,
    DT_FILTER=2147483647,
    DT_FINI=13,
    DT_FINI_ARRAY=26,
    DT_FINI_ARRAYSZ=28,
    DT_FLAGS=30,
    DT_FLAGS_1=1879048187,
    DT_GNU_CONFLICT=1879047928,
    DT_GNU_CONFLICTSZ=1879047670,
    DT_GNU_HASH=1879047925,
    DT_GNU_LIBLIST=1879047929,
    DT_GNU_LIBLISTSZ=1879047671,
    DT_GNU_PRELINKED=1879047669,
    DT_HASH=4,
    DT_INIT=12,
    DT_INIT_ARRAY=25,
    DT_INIT_ARRAYSZ=27,
    DT_JMPREL=23,
    DT_MOVEENT=1879047674,
    DT_MOVESZ=1879047675,
    DT_MOVETAB=1879047934,
    DT_NEEDED=1,
    DT_NULL=0,
    DT_PLTGOT=3,
    DT_PLTPAD=1879047933,
    DT_PLTPADSZ=1879047673,
    DT_PLTREL=20,
    DT_PLTRELSZ=2,
    DT_POSFLAG_1=1879047677,
    DT_PREINIT_ARRAYSZ=33,
    DT_REL=17,
    DT_RELA=7,
    DT_RELACOUNT=1879048185,
    DT_RELAENT=9,
    DT_RELASZ=8,
    DT_RELCOUNT=1879048186,
    DT_RELENT=19,
    DT_RELSZ=18,
    DT_RPATH=15,
    DT_RUNPATH=29,
    DT_SONAME=14,
    DT_STRSZ=10,
    DT_STRTAB=5,
    DT_SYMBOLIC=16,
    DT_SYMENT=11,
    DT_SYMINENT=1879047679,
    DT_SYMINFO=1879047935,
    DT_SYMINSZ=1879047678,
    DT_SYMTAB=6,
    DT_TEXTREL=22,
    DT_TLSDESC_GOT=1879047927,
    DT_TLSDESC_PLT=1879047926,
    DT_VERDEF=1879048188,
    DT_VERDEFNUM=1879048189,
    DT_VERNEED=1879048190,
    DT_VERNEEDNUM=1879048191,
    DT_VERSYM=1879048176
} Elf32_DynTag_x86;

typedef struct Elf32_Phdr Elf32_Phdr, *PElf32_Phdr;

typedef enum Elf_ProgramHeaderType_x86 {
    PT_DYNAMIC=2,
    PT_GNU_EH_FRAME=1685382480,
    PT_GNU_RELRO=1685382482,
    PT_GNU_STACK=1685382481,
    PT_INTERP=3,
    PT_LOAD=1,
    PT_NOTE=4,
    PT_NULL=0,
    PT_PHDR=6,
    PT_SHLIB=5,
    PT_TLS=7
} Elf_ProgramHeaderType_x86;

struct Elf32_Phdr {
    enum Elf_ProgramHeaderType_x86 p_type;
    dword p_offset;
    dword p_vaddr;
    dword p_paddr;
    dword p_filesz;
    dword p_memsz;
    dword p_flags;
    dword p_align;
};

typedef struct Elf32_Rel Elf32_Rel, *PElf32_Rel;

struct Elf32_Rel {
    dword r_offset; // location to apply the relocation action
    dword r_info; // the symbol table index and the type of relocation
};

typedef struct Elf32_Dyn_x86 Elf32_Dyn_x86, *PElf32_Dyn_x86;

struct Elf32_Dyn_x86 {
    enum Elf32_DynTag_x86 d_tag;
    dword d_val;
};

typedef struct Elf32_Sym Elf32_Sym, *PElf32_Sym;

struct Elf32_Sym {
    dword st_name;
    dword st_value;
    dword st_size;
    byte st_info;
    byte st_other;
    word st_shndx;
};

typedef struct Elf32_Ehdr Elf32_Ehdr, *PElf32_Ehdr;

struct Elf32_Ehdr {
    byte e_ident_magic_num;
    char e_ident_magic_str[3];
    byte e_ident_class;
    byte e_ident_data;
    byte e_ident_version;
    byte e_ident_pad[9];
    word e_type;
    word e_machine;
    dword e_version;
    dword e_entry;
    dword e_phoff;
    dword e_shoff;
    dword e_flags;
    word e_ehsize;
    word e_phentsize;
    word e_phnum;
    word e_shentsize;
    word e_shnum;
    word e_shstrndx;
};




// WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx

void _DT_INIT(void)

{
  __gmon_start__();
  return;
}



void FUN_08049020(void)

{
                    // WARNING: Treating indirect jump as call
  (*(code *)(undefined *)0x0)();
  return;
}



// WARNING: Unknown calling convention yet parameter storage is locked

void setbuf(FILE *__stream,char *__buf)

{
  setbuf(__stream,__buf);
  return;
}



// WARNING: Unknown calling convention yet parameter storage is locked

int printf(char *__format,...)

{
  int iVar1;
  
  iVar1 = printf(__format);
  return iVar1;
}



// WARNING: Unknown calling convention yet parameter storage is locked

int puts(char *__s)

{
  int iVar1;
  
  iVar1 = puts(__s);
  return iVar1;
}



// WARNING: Unknown calling convention yet parameter storage is locked

void exit(int __status)

{
                    // WARNING: Subroutine does not return
  exit(__status);
}



void __libc_start_main(void)

{
  __libc_start_main();
  return;
}



void __isoc99_scanf(void)

{
  __isoc99_scanf();
  return;
}



// WARNING: Unknown calling convention yet parameter storage is locked

int strncmp(char *__s1,char *__s2,size_t __n)

{
  int iVar1;
  
  iVar1 = strncmp(__s1,__s2,__n);
  return iVar1;
}



// WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx

void entry(void)

{
  __libc_start_main(bankMenu);
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



// WARNING: This is an inlined function

void __i686_get_pc_thunk_bx(void)

{
  return;
}



void FUN_080490e0(void)

{
  return;
}



// WARNING: This is an inlined function

void __i686_get_pc_thunk_bx(void)

{
  return;
}



// WARNING: Removing unreachable block (ram,0x0804910c)
// WARNING: Removing unreachable block (ram,0x08049115)

void FUN_08049100(void)

{
  return;
}



// WARNING: Removing unreachable block (ram,0x08049158)
// WARNING: Removing unreachable block (ram,0x08049161)

void FUN_08049140(void)

{
  return;
}



void _FINI_0(void)

{
  if (DAT_0804c034 == '\0') {
    FUN_08049100();
    DAT_0804c034 = 1;
    return;
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x08049158)
// WARNING: Removing unreachable block (ram,0x08049161)

void _INIT_0(void)

{
  return;
}



// WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx

uint captcha(void)

{
  int result;
  undefined4 b3sT;
  undefined4 bAnK;
  undefined zero;
  char userCaptcha [1000];
  char *captchaImage;
  
  b3sT = 0x54733362;
  bAnK = 0x4b6e4162;
  zero = 0;
  captchaImage = 
  " _    _____    _____ _       _          _  __\n| |__|___ / __|_   _| |__   / \\   _ __ | |/ /\n| \'_ \\ |_ \\/ __|| | | \'_ \\ / _ \\ | \'_ \\| \' /\n| |_) |__) \\__ \\| | | |_) / ___ \\| | | | . \\\n|_.__/____/|___/|_| |_.__/_/   \\_\\_| |_|_|\\_\\\n"
  ;
  puts(
      " _    _____    _____ _       _          _  __\n| |__|___ / __|_   _| |__   / \\   _ __ | |/ /\n| \'_ \\ |_ \\/ __|| | | \'_ \\ / _ \\ | \'_ \\| \' /\n| |_) |__) \\__ \\| | | |_) / ___ \\| | | | . \\\n|_.__/____/|___/|_| |_.__/_/   \\_\\_| |_|_|\\_\\\n"
      );
  printf("Captcha: ");
  __isoc99_scanf(&DAT_0804a0f7,userCaptcha);
  result = strncmp(userCaptcha,(char *)&b3sT,8);
  if (result != 0) {
    puts("Incorrect!\n");
  }
  else {
    puts("Correct!\n");
  }
  return (uint)(result == 0);
}



// WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx

void withdraw(void)

{
  uint captchaResult;
  int withdrawAmount [2];
  
  captchaResult = captcha();
  if (captchaResult != 0) {
    printf("How much would you like to withdraw?: ");
    __isoc99_scanf(&DAT_0804a137,withdrawAmount);
    if (accountBalance < withdrawAmount[0]) {
      puts("You do not have enough money in your account!\n");
    }
    else {
      accountBalance = accountBalance - withdrawAmount[0];
      puts("Withdrawal successful!\n");
    }
  }
  return;
}



// WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx

void deposit(void)

{
  uint captchaResult;
  int depositAmount [2];
  
  captchaResult = captcha();
  if (captchaResult != 0) {
    printf("How much would you like to deposit?: ");
    __isoc99_scanf(&DAT_0804a137,depositAmount);
    accountBalance = depositAmount[0] + accountBalance;
    puts("Deposit successful!\n");
  }
                    // if captch == 0: invalid result; return
  return;
}



void checkBalance(void)

{
  int stackPointer;
  
  stackPointer = getStackPointer();
                    // 0xE41: location of "Your current balance is:" strings
                    // 0x2CB1: location of accountBalance
  printf((char *)(stackPointer + 0xe41),*(undefined4 *)(stackPointer + 0x2cb1));
  return;
}



void showOptions(void)

{
  int iVar1;
  
  iVar1 = getStackPointer();
  printf((char *)(iVar1 + 0xd46),iVar1 + 0xe2f);
  return;
}



// WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx

void bankMenu(undefined1 param_1)

{
  int selectedOption;
  undefined1 *puStack16;
  
  puStack16 = &param_1;
  setbuf(stdout,(char *)0x0);
  setbuf(stdin,(char *)0x0);
  setbuf(stderr,(char *)0x0);
  puts("Welcome to the Best Bank!");
  puts("Current balance: $500\n");
  do {
    while( true ) {
      while( true ) {
                    // If option != deposit then break
        showOptions();
        printf("Enter your choice: ");
        __isoc99_scanf(&DAT_0804a137,&selectedOption);
        if (selectedOption != 2) break;
        deposit();
      }
                    // if selectedOption > 2: break
      if (2 < selectedOption) break;
      if (selectedOption == 1) {
        withdraw();
      }
      else {
LAB_080494cb:
        puts("That is not a valid choice! Try again.\n");
      }
    }
    if (selectedOption != 3) {
      if (selectedOption == 4) {
                    // WARNING: Subroutine does not return
        exit(0);
      }
      goto LAB_080494cb;
    }
                    // selectedOption = 3
    checkBalance();
  } while( true );
}



undefined4 getStackPointer(void)

{
  undefined4 stackPointer;
  
  return stackPointer;
}



// WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx

void FUN_080494f0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  _DT_INIT();
  iVar1 = 0;
  do {
    (*(code *)(&__DT_INIT_ARRAY)[iVar1])(param_1,param_2,param_3);
    iVar1 = iVar1 + 1;
  } while (iVar1 != 1);
  return;
}



void justReturn(void)

{
  return;
}



// WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx

void _DT_FINI(void)

{
  return;
}


