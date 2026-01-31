# 1 "src/filli.h"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 423 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "src/filli.h" 2






# 1 "C:/msys64/clang64/include/stdio.h" 1 3








# 1 "C:/msys64/clang64/include/corecrt_stdio_config.h" 1 3
# 10 "C:/msys64/clang64/include/corecrt_stdio_config.h" 3
# 1 "C:/msys64/clang64/include/corecrt.h" 1 3
# 10 "C:/msys64/clang64/include/corecrt.h" 3
# 1 "C:/msys64/clang64/include/_mingw.h" 1 3
# 10 "C:/msys64/clang64/include/_mingw.h" 3
# 1 "C:/msys64/clang64/include/_mingw_mac.h" 1 3
# 11 "C:/msys64/clang64/include/_mingw.h" 2 3
# 1 "C:/msys64/clang64/include/_mingw_secapi.h" 1 3
# 12 "C:/msys64/clang64/include/_mingw.h" 2 3
# 306 "C:/msys64/clang64/include/_mingw.h" 3
# 1 "C:/msys64/clang64/lib/clang/21/include/vadefs.h" 1 3
# 12 "C:/msys64/clang64/lib/clang/21/include/vadefs.h" 3
# 1 "C:/msys64/clang64/include/vadefs.h" 1 3








# 1 "C:/msys64/clang64/include/_mingw.h" 1 3
# 685 "C:/msys64/clang64/include/_mingw.h" 3
# 1 "C:/msys64/clang64/include/sdks/_mingw_ddk.h" 1 3
# 686 "C:/msys64/clang64/include/_mingw.h" 2 3
# 10 "C:/msys64/clang64/include/vadefs.h" 2 3




#pragma pack(push,_CRT_PACKING)
# 24 "C:/msys64/clang64/include/vadefs.h" 3
  typedef __builtin_va_list __gnuc_va_list;






  typedef __gnuc_va_list va_list;
# 103 "C:/msys64/clang64/include/vadefs.h" 3
#pragma pack(pop)
# 13 "C:/msys64/clang64/lib/clang/21/include/vadefs.h" 2 3
# 307 "C:/msys64/clang64/include/_mingw.h" 2 3
# 604 "C:/msys64/clang64/include/_mingw.h" 3
void __attribute__((__cdecl__)) __debugbreak(void);
extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) void __attribute__((__cdecl__)) __debugbreak(void)
{



  __asm__ __volatile__("int {$}3":);





}
# 625 "C:/msys64/clang64/include/_mingw.h" 3
void __attribute__((__cdecl__)) __attribute__ ((__noreturn__)) __fastfail(unsigned int code);
extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) void __attribute__((__cdecl__)) __attribute__ ((__noreturn__)) __fastfail(unsigned int code)
{




  __asm__ __volatile__("int {$}0x29"::"c"(code));






  __builtin_unreachable();
}
# 665 "C:/msys64/clang64/include/_mingw.h" 3
const char *__mingw_get_crt_info (void);
# 11 "C:/msys64/clang64/include/corecrt.h" 2 3




#pragma pack(push,_CRT_PACKING)
# 35 "C:/msys64/clang64/include/corecrt.h" 3
__extension__ typedef unsigned long long size_t;
# 45 "C:/msys64/clang64/include/corecrt.h" 3
__extension__ typedef long long ssize_t;






typedef size_t rsize_t;
# 62 "C:/msys64/clang64/include/corecrt.h" 3
__extension__ typedef long long intptr_t;
# 75 "C:/msys64/clang64/include/corecrt.h" 3
__extension__ typedef unsigned long long uintptr_t;
# 88 "C:/msys64/clang64/include/corecrt.h" 3
__extension__ typedef long long ptrdiff_t;
# 98 "C:/msys64/clang64/include/corecrt.h" 3
typedef unsigned short wchar_t;







typedef unsigned short wint_t;
typedef unsigned short wctype_t;





typedef int errno_t;




typedef long __time32_t;




__extension__ typedef long long __time64_t;
# 138 "C:/msys64/clang64/include/corecrt.h" 3
typedef __time64_t time_t;
# 157 "C:/msys64/clang64/include/corecrt.h" 3
__attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _invalid_parameter_noinfo(void);
__attribute__ ((__dllimport__)) __attribute__ ((__noreturn__)) void __attribute__((__cdecl__)) _invalid_parameter_noinfo_noreturn(void);
__attribute__ ((__dllimport__)) __attribute__ ((__noreturn__)) void __attribute__((__cdecl__)) _invoke_watson(const wchar_t *expression, const wchar_t *function_name, const wchar_t *file_name, unsigned int line_number, uintptr_t reserved);
# 437 "C:/msys64/clang64/include/corecrt.h" 3
struct threadlocaleinfostruct;
struct threadmbcinfostruct;
typedef struct threadlocaleinfostruct *pthreadlocinfo;
typedef struct threadmbcinfostruct *pthreadmbcinfo;
struct __lc_time_data;

typedef struct localeinfo_struct {
  pthreadlocinfo locinfo;
  pthreadmbcinfo mbcinfo;
} _locale_tstruct,*_locale_t;



typedef struct tagLC_ID {
  unsigned short wLanguage;
  unsigned short wCountry;
  unsigned short wCodePage;
} LC_ID,*LPLC_ID;




typedef struct threadlocaleinfostruct {

  const unsigned short *_locale_pctype;
  int _locale_mb_cur_max;
  unsigned int _locale_lc_codepage;
# 489 "C:/msys64/clang64/include/corecrt.h" 3
} threadlocinfo;
# 508 "C:/msys64/clang64/include/corecrt.h" 3
#pragma pack(pop)
# 11 "C:/msys64/clang64/include/corecrt_stdio_config.h" 2 3





unsigned long long* __attribute__((__cdecl__)) __local_stdio_printf_options(void);
unsigned long long* __attribute__((__cdecl__)) __local_stdio_scanf_options(void);
# 10 "C:/msys64/clang64/include/stdio.h" 2 3

#pragma pack(push,_CRT_PACKING)
# 33 "C:/msys64/clang64/include/stdio.h" 3
  struct _iobuf {

    void *_Placeholder;
# 46 "C:/msys64/clang64/include/stdio.h" 3
  };
  typedef struct _iobuf FILE;
# 99 "C:/msys64/clang64/include/stdio.h" 3
# 1 "C:/msys64/clang64/include/_mingw_off_t.h" 1 3




  typedef long _off_t;

  typedef long off32_t;





  __extension__ typedef long long _off64_t;

  __extension__ typedef long long off64_t;
# 26 "C:/msys64/clang64/include/_mingw_off_t.h" 3
typedef off32_t off_t;
# 100 "C:/msys64/clang64/include/stdio.h" 2 3

__attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) __acrt_iob_func(unsigned index);

  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) __iob_func(void);
# 112 "C:/msys64/clang64/include/stdio.h" 3
  __extension__ typedef long long fpos_t;
# 156 "C:/msys64/clang64/include/stdio.h" 3
extern
  __attribute__((__format__(__scanf__, 2,3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_sscanf(const char * __restrict__ _Src,const char * __restrict__ _Format,...);
extern
  __attribute__((__format__(__scanf__, 2,0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vsscanf (const char * __restrict__ _Str,const char * __restrict__ Format,va_list argp);
extern
  __attribute__((__format__(__scanf__, 1,2))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_scanf(const char * __restrict__ _Format,...);
extern
  __attribute__((__format__(__scanf__, 1,0))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_vscanf(const char * __restrict__ Format, va_list argp);
extern
  __attribute__((__format__(__scanf__, 2,3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_fscanf(FILE * __restrict__ _File,const char * __restrict__ _Format,...);
extern
  __attribute__((__format__(__scanf__, 2,0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vfscanf (FILE * __restrict__ fp, const char * __restrict__ Format,va_list argp);

extern
  __attribute__((__format__(__printf__,3,0))) __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __mingw_vsnprintf(char * __restrict__ _DstBuf,size_t _MaxCount,const char * __restrict__ _Format,
                               va_list _ArgList);
extern
  __attribute__((__format__(__printf__,3,4))) __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __mingw_snprintf(char * __restrict__ s, size_t n, const char * __restrict__ format, ...);
extern
  __attribute__((__format__(__printf__,1,2))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_printf(const char * __restrict__ , ... ) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__printf__,1,0))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_vprintf (const char * __restrict__ , va_list) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__printf__,2,3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_fprintf (FILE * __restrict__ , const char * __restrict__ , ...) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__printf__,2,0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vfprintf (FILE * __restrict__ , const char * __restrict__ , va_list) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__printf__,2,3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_sprintf (char * __restrict__ , const char * __restrict__ , ...) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__printf__,2,0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vsprintf (char * __restrict__ , const char * __restrict__ , va_list) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__printf__,2,3))) __attribute__((nonnull (1,2)))
  int __attribute__((__cdecl__)) __mingw_asprintf(char ** __restrict__ , const char * __restrict__ , ...) __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__printf__,2,0))) __attribute__((nonnull (1,2)))
  int __attribute__((__cdecl__)) __mingw_vasprintf(char ** __restrict__ , const char * __restrict__ , va_list) __attribute__ ((__nothrow__));

extern
  __attribute__((__format__(__scanf__, 2,3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_sscanf(const char * __restrict__ _Src,const char * __restrict__ _Format,...)
  __asm__("sscanf");
extern
  __attribute__((__format__(__scanf__, 2,0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_vsscanf(const char * __restrict__ _Str,const char * __restrict__ _Format,va_list argp)
  __asm__("vsscanf");
extern
  __attribute__((__format__(__scanf__, 1,2))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_scanf(const char * __restrict__ _Format,...)
  __asm__("scanf");
extern
  __attribute__((__format__(__scanf__, 1,0))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_vscanf(const char * __restrict__ _Format,va_list argp)
  __asm__("vscanf");
extern
  __attribute__((__format__(__scanf__, 2,3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_fscanf(FILE * __restrict__ _File,const char * __restrict__ _Format,...)
  __asm__("fscanf");
extern
  __attribute__((__format__(__scanf__, 2,0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_vfscanf(FILE * __restrict__ _File,const char * __restrict__ _Format,va_list argp)
  __asm__("vfscanf");

extern
  __attribute__((__format__(__printf__, 1,2))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_printf(const char * __restrict__ , ... )
  __asm__("printf") __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__printf__, 1,0))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_vprintf (const char * __restrict__ , va_list)
  __asm__("vprintf") __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__printf__, 2,3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_fprintf (FILE * __restrict__ , const char * __restrict__ , ...)
  __asm__("fprintf") __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__printf__, 2,0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_vfprintf (FILE * __restrict__ , const char * __restrict__ , va_list)
  __asm__("vfprintf") __attribute__ ((__nothrow__))
;
extern
  __attribute__((__format__(__printf__, 2,3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_sprintf (char * __restrict__ , const char * __restrict__ , ...)
  __asm__("sprintf") __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__printf__, 2,0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_vsprintf (char * __restrict__ , const char * __restrict__ , va_list)
  __asm__("vsprintf") __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__printf__, 3,4))) __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __ms_snprintf (char * __restrict__ , size_t , const char * __restrict__ , ...)
  __asm__("snprintf") __attribute__ ((__nothrow__));
extern
  __attribute__((__format__(__printf__, 3,0))) __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __ms_vsnprintf (char * __restrict__ , size_t , const char * __restrict__ , va_list)
  __asm__("vsnprintf") __attribute__ ((__nothrow__));


  int __attribute__((__cdecl__)) __stdio_common_vsprintf(unsigned long long options, char *str, size_t len, const char *format, _locale_t locale, va_list valist);
  int __attribute__((__cdecl__)) __stdio_common_vfprintf(unsigned long long options, FILE *file, const char *format, _locale_t locale, va_list valist);
  int __attribute__((__cdecl__)) __stdio_common_vsscanf(unsigned long long options, const char *input, size_t length, const char *format, _locale_t locale, va_list valist);
  int __attribute__((__cdecl__)) __stdio_common_vfscanf(unsigned long long options, FILE *file, const char *format, _locale_t locale, va_list valist);
# 444 "C:/msys64/clang64/include/stdio.h" 3
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"

  __attribute__((__format__ (__printf__, 2, 3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) fprintf(FILE * __restrict__ _File,const char * __restrict__ _Format,...);
  __attribute__((__format__ (__printf__, 1, 2))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) printf(const char * __restrict__ _Format,...);
  __attribute__((__format__ (__printf__, 2, 3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) sprintf(char * __restrict__ _Dest,const char * __restrict__ _Format,...) ;

  __attribute__((__format__ (__printf__, 2, 0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) vfprintf(FILE * __restrict__ _File,const char * __restrict__ _Format,va_list _ArgList);
  __attribute__((__format__ (__printf__, 1, 0))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) vprintf(const char * __restrict__ _Format,va_list _ArgList);
  __attribute__((__format__ (__printf__, 2, 0))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) vsprintf(char * __restrict__ _Dest,const char * __restrict__ _Format,va_list _Args) ;


  __attribute__((__format__ (__scanf__, 2, 3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) fscanf(FILE * __restrict__ _File,const char * __restrict__ _Format,...);

  __attribute__((__format__ (__scanf__, 1, 2))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) scanf(const char * __restrict__ _Format,...);

  __attribute__((__format__ (__scanf__, 2, 3))) __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) sscanf(const char * __restrict__ _Src,const char * __restrict__ _Format,...);







  __attribute__((__format__ (__scanf__, 2, 0))) __attribute__ ((__nonnull__ (2)))
  int vfscanf (FILE *__stream, const char *__format, __builtin_va_list __local_argv);

  __attribute__((__format__ (__scanf__, 2, 0))) __attribute__ ((__nonnull__ (2)))
  int vsscanf (const char * __restrict__ __source, const char * __restrict__ __format, __builtin_va_list __local_argv);
  __attribute__((__format__ (__scanf__, 1, 0))) __attribute__ ((__nonnull__ (1)))
  int vscanf(const char *__format, __builtin_va_list __local_argv);


#pragma GCC diagnostic pop
# 535 "C:/msys64/clang64/include/stdio.h" 3
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _filbuf(FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _flsbuf(int _Ch,FILE *_File);



  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _fsopen(const char *_Filename,const char *_Mode,int _ShFlag);

  void __attribute__((__cdecl__)) clearerr(FILE *_File);
  int __attribute__((__cdecl__)) fclose(FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fcloseall(void);



  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _fdopen(int _FileHandle,const char *_Mode);

  int __attribute__((__cdecl__)) feof(FILE *_File);
  int __attribute__((__cdecl__)) ferror(FILE *_File);
  int __attribute__((__cdecl__)) fflush(FILE *_File);
  int __attribute__((__cdecl__)) fgetc(FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fgetchar(void);
  int __attribute__((__cdecl__)) fgetpos(FILE * __restrict__ _File ,fpos_t * __restrict__ _Pos);
  int __attribute__((__cdecl__)) fgetpos64(FILE * __restrict__ _File ,fpos_t * __restrict__ _Pos);
  char *__attribute__((__cdecl__)) fgets(char * __restrict__ _Buf,int _MaxCount,FILE * __restrict__ _File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fileno(FILE *_File);







  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _tempnam(const char *_DirName,const char *_FilePrefix);



  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _flushall(void);
  FILE *__attribute__((__cdecl__)) fopen(const char * __restrict__ _Filename,const char * __restrict__ _Mode) ;
  FILE *__attribute__((__cdecl__)) fopen64(const char * __restrict__ filename,const char * __restrict__ mode);
  int __attribute__((__cdecl__)) fputc(int _Ch,FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fputchar(int _Ch);
  int __attribute__((__cdecl__)) fputs(const char * __restrict__ _Str,FILE * __restrict__ _File);
  size_t __attribute__((__cdecl__)) fread(void * __restrict__ _DstBuf,size_t _ElementSize,size_t _Count,FILE * __restrict__ _File);
  FILE *__attribute__((__cdecl__)) freopen(const char * __restrict__ _Filename,const char * __restrict__ _Mode,FILE * __restrict__ _File) ;
  FILE *__attribute__((__cdecl__)) freopen64(const char * __restrict__ _Filename,const char * __restrict__ _Mode,FILE * __restrict__ _File);
  int __attribute__((__cdecl__)) fsetpos(FILE *_File,const fpos_t *_Pos);
  int __attribute__((__cdecl__)) fsetpos64(FILE *_File,const fpos_t *_Pos);
  int __attribute__((__cdecl__)) fseek(FILE *_File,long _Offset,int _Origin);
  long __attribute__((__cdecl__)) ftell(FILE *_File);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fseeki64(FILE *_File,long long _Offset,int _Origin);
  __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _ftelli64(FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) fseeko(FILE *_File, _off_t _Offset, int _Origin);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) fseeko64(FILE *_File, _off64_t _Offset, int _Origin);
  __attribute__ ((__dllimport__)) _off_t __attribute__((__cdecl__)) ftello(FILE *_File);
  __attribute__ ((__dllimport__)) _off64_t __attribute__((__cdecl__)) ftello64(FILE *_File);
# 605 "C:/msys64/clang64/include/stdio.h" 3
  size_t __attribute__((__cdecl__)) fwrite(const void * __restrict__ _Str,size_t _Size,size_t _Count,FILE * __restrict__ _File);
  int __attribute__((__cdecl__)) getc(FILE *_File);
  int __attribute__((__cdecl__)) getchar(void);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _getmaxstdio(void);
  char *__attribute__((__cdecl__)) gets(char *_Buffer)
    __attribute__((__warning__("Using gets() is always unsafe - use fgets() instead")));
  int __attribute__((__cdecl__)) _getw(FILE *_File);


  void __attribute__((__cdecl__)) perror(const char *_ErrMsg);


  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _pclose(FILE *_File);
  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _popen(const char *_Command,const char *_Mode);





  int __attribute__((__cdecl__)) putc(int _Ch,FILE *_File);
  int __attribute__((__cdecl__)) putchar(int _Ch);
  int __attribute__((__cdecl__)) puts(const char *_Str);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _putw(int _Word,FILE *_File);


  int __attribute__((__cdecl__)) remove(const char *_Filename);
  int __attribute__((__cdecl__)) rename(const char *_OldFilename,const char *_NewFilename);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _unlink(const char *_Filename);

  int __attribute__((__cdecl__)) unlink(const char *_Filename) ;


  void __attribute__((__cdecl__)) rewind(FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _rmtmp(void);
  void __attribute__((__cdecl__)) setbuf(FILE * __restrict__ _File,char * __restrict__ _Buffer) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _setmaxstdio(int _Max);
  __attribute__ ((__dllimport__)) unsigned int __attribute__((__cdecl__)) _set_output_format(unsigned int _Format);
  __attribute__ ((__dllimport__)) unsigned int __attribute__((__cdecl__)) _get_output_format(void);
  int __attribute__((__cdecl__)) setvbuf(FILE * __restrict__ _File,char * __restrict__ _Buf,int _Mode,size_t _Size);

  __attribute__ ((__pure__))
  __attribute__((__format__ (__printf__, 1, 2))) __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) _scprintf(const char * __restrict__ _Format,...);
  __attribute__((__format__ (__scanf__, 3, 4))) __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) _snscanf(const char * __restrict__ _Src,size_t _MaxCount,const char * __restrict__ _Format,...) ;







  __attribute__ ((__pure__))
  __attribute__((__format__(__printf__, 1,0))) __attribute__ ((__nonnull__ (1)))
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vscprintf(const char * __restrict__ _Format,va_list _ArgList);
  FILE *__attribute__((__cdecl__)) tmpfile(void) ;
  FILE *__attribute__((__cdecl__)) tmpfile64(void);
  char *__attribute__((__cdecl__)) tmpnam(char *_Buffer);
  int __attribute__((__cdecl__)) ungetc(int _Ch,FILE *_File);


  __attribute__((__format__ (__printf__, 3, 0))) __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) _vsnprintf(char * __restrict__ _Dest,size_t _Count,const char * __restrict__ _Format,va_list _Args) ;
  __attribute__((__format__ (__printf__, 3, 4))) __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) _snprintf(char * __restrict__ _Dest,size_t _Count,const char * __restrict__ _Format,...) ;
# 721 "C:/msys64/clang64/include/stdio.h" 3
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"

  __attribute__((__format__ (__printf__, 3, 0))) __attribute__ ((__nonnull__ (3)))
  int vsnprintf (char * __restrict__ __stream, size_t __n, const char * __restrict__ __format, va_list __local_argv);

  __attribute__((__format__ (__printf__, 3, 4))) __attribute__ ((__nonnull__ (3)))
  int snprintf (char * __restrict__ __stream, size_t __n, const char * __restrict__ __format, ...);
# 787 "C:/msys64/clang64/include/stdio.h" 3
#pragma GCC diagnostic pop
# 889 "C:/msys64/clang64/include/stdio.h" 3
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _set_printf_count_output(int _Value);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _get_printf_count_output(void);




                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_swscanf(const wchar_t * __restrict__ _Src,const wchar_t * __restrict__ _Format,...);
                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vswscanf (const wchar_t * __restrict__ _Str,const wchar_t * __restrict__ Format,va_list argp);
                                                     __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_wscanf(const wchar_t * __restrict__ _Format,...);
                                                     __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_vwscanf(const wchar_t * __restrict__ Format, va_list argp);
                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_fwscanf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,...);
                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vfwscanf (FILE * __restrict__ fp, const wchar_t * __restrict__ Format,va_list argp);

                                                      __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_fwprintf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,...);
                                                      __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_wprintf(const wchar_t * __restrict__ _Format,...);
                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __mingw_vfwprintf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,va_list _ArgList);
                                                     __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __mingw_vwprintf(const wchar_t * __restrict__ _Format,va_list _ArgList);
                                                      __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __mingw_snwprintf (wchar_t * __restrict__ s, size_t n, const wchar_t * __restrict__ format, ...);
                                                      __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __mingw_vsnwprintf (wchar_t * __restrict__ , size_t, const wchar_t * __restrict__ , va_list);
                                                      __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __mingw_swprintf(wchar_t * __restrict__ , size_t, const wchar_t * __restrict__ , ...);
                                                      __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __mingw_vswprintf(wchar_t * __restrict__ , size_t, const wchar_t * __restrict__ ,va_list);

                                                    __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_swscanf(const wchar_t * __restrict__ _Src,const wchar_t * __restrict__ _Format,...)
  __asm__("swscanf");
                                                    __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_vswscanf(const wchar_t * __restrict__ _Src,const wchar_t * __restrict__ _Format,va_list)
  __asm__("vswscanf");
                                                    __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_wscanf(const wchar_t * __restrict__ _Format,...)
  __asm__("wscanf");
                                                    __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_vwscanf(const wchar_t * __restrict__ _Format, va_list)
  __asm__("vwscanf");
                                                    __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_fwscanf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,...)
  __asm__("fwscanf");
                                                    __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_vfwscanf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,va_list)
  __asm__("vfwscanf");

                                                     __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_fwprintf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,...);


                                                     __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_wprintf(const wchar_t * __restrict__ _Format,...)
  __asm__("wprintf");
                                                    __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) __ms_vfwprintf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,va_list _ArgList)
  __asm__("vfwprintf");
                                                    __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) __ms_vwprintf(const wchar_t * __restrict__ _Format,va_list _ArgList)
  __asm__("vwprintf");
                                                     __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __ms_swprintf(wchar_t * __restrict__ , size_t, const wchar_t * __restrict__ , ...)
  __asm__("swprintf");
                                                     __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __ms_vswprintf(wchar_t * __restrict__ , size_t, const wchar_t * __restrict__ ,va_list)
  __asm__("vswprintf");
                                                     __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __ms_snwprintf(wchar_t * __restrict__ , size_t, const wchar_t * __restrict__ , ...)
  __asm__("snwprintf");
                                                     __attribute__ ((__nonnull__ (3)))
  int __attribute__((__cdecl__)) __ms_vsnwprintf(wchar_t * __restrict__ , size_t, const wchar_t * __restrict__ , va_list)
  __asm__("vsnwprintf");


  int __attribute__((__cdecl__)) __stdio_common_vswprintf(unsigned long long options, wchar_t *str, size_t len, const wchar_t *format, _locale_t locale, va_list valist);
  int __attribute__((__cdecl__)) __stdio_common_vfwprintf(unsigned long long options, FILE *file, const wchar_t *format, _locale_t locale, va_list valist);
  int __attribute__((__cdecl__)) __stdio_common_vswscanf(unsigned long long options, const wchar_t *input, size_t length, const wchar_t *format, _locale_t locale, va_list valist);
  int __attribute__((__cdecl__)) __stdio_common_vfwscanf(unsigned long long options, FILE *file, const wchar_t *format, _locale_t locale, va_list valist);
# 1084 "C:/msys64/clang64/include/stdio.h" 3
  int __attribute__((__cdecl__)) fwscanf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,...);


  int __attribute__((__cdecl__)) swscanf(const wchar_t * __restrict__ _Src,const wchar_t * __restrict__ _Format,...);


  int __attribute__((__cdecl__)) wscanf(const wchar_t * __restrict__ _Format,...);

  __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) vfwscanf(FILE *__stream, const wchar_t *__format, va_list __local_argv);

  __attribute__ ((__nonnull__ (2)))
  int __attribute__((__cdecl__)) vswscanf(const wchar_t * __restrict__ __source, const wchar_t * __restrict__ __format, va_list __local_argv);

  __attribute__ ((__nonnull__ (1)))
  int __attribute__((__cdecl__)) vwscanf(const wchar_t *__format, va_list __local_argv);

  int __attribute__((__cdecl__)) fwprintf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,...);
  int __attribute__((__cdecl__)) wprintf(const wchar_t * __restrict__ _Format,...);
  int __attribute__((__cdecl__)) vfwprintf(FILE * __restrict__ _File,const wchar_t * __restrict__ _Format,va_list _ArgList);
  int __attribute__((__cdecl__)) vwprintf(const wchar_t * __restrict__ _Format,va_list _ArgList);

  int __attribute__((__cdecl__)) swprintf(wchar_t * __restrict__ _Dest,size_t _Count,const wchar_t * __restrict__ _Format,...);
  int __attribute__((__cdecl__)) vswprintf(wchar_t * __restrict__ _Dest,size_t _Count,const wchar_t * __restrict__ _Format,va_list _Args);
  int __attribute__((__cdecl__)) snwprintf(wchar_t * __restrict__ s, size_t n, const wchar_t * __restrict__ format, ...);
  int __attribute__((__cdecl__)) vsnwprintf(wchar_t * __restrict__ s, size_t n, const wchar_t * __restrict__ format, va_list arg);
# 1119 "C:/msys64/clang64/include/stdio.h" 3
  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _wfsopen(const wchar_t *_Filename,const wchar_t *_Mode,int _ShFlag);


  wint_t __attribute__((__cdecl__)) fgetwc(FILE *_File);
  __attribute__ ((__dllimport__)) wint_t __attribute__((__cdecl__)) _fgetwchar(void);
  wint_t __attribute__((__cdecl__)) fputwc(wchar_t _Ch,FILE *_File);
  __attribute__ ((__dllimport__)) wint_t __attribute__((__cdecl__)) _fputwchar(wchar_t _Ch);
  wint_t __attribute__((__cdecl__)) getwc(FILE *_File);
  wint_t __attribute__((__cdecl__)) getwchar(void);
  wint_t __attribute__((__cdecl__)) putwc(wchar_t _Ch,FILE *_File);
  wint_t __attribute__((__cdecl__)) putwchar(wchar_t _Ch);
  wint_t __attribute__((__cdecl__)) ungetwc(wint_t _Ch,FILE *_File);
  wchar_t *__attribute__((__cdecl__)) fgetws(wchar_t * __restrict__ _Dst,int _SizeInWords,FILE * __restrict__ _File);
  int __attribute__((__cdecl__)) fputws(const wchar_t * __restrict__ _Str,FILE * __restrict__ _File);
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _getws(wchar_t *_String) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _putws(const wchar_t *_Str);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _scwprintf(const wchar_t * __restrict__ _Format,...);




  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snwprintf(wchar_t * __restrict__ _Dest,size_t _Count,const wchar_t * __restrict__ _Format,...) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vsnwprintf(wchar_t * __restrict__ _Dest,size_t _Count,const wchar_t * __restrict__ _Format,va_list _Args) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vscwprintf(const wchar_t * __restrict__ _Format,va_list _ArgList);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _swprintf(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Format,...);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _vswprintf(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Format,va_list _Args);


# 1 "C:/msys64/clang64/include/swprintf.inl" 1 3
# 1149 "C:/msys64/clang64/include/stdio.h" 2 3
# 1162 "C:/msys64/clang64/include/stdio.h" 3
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wtempnam(const wchar_t *_Directory,const wchar_t *_FilePrefix);



  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _snwscanf(const wchar_t * __restrict__ _Src,size_t _MaxCount,const wchar_t * __restrict__ _Format,...);
  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _wfdopen(int _FileHandle ,const wchar_t *_Mode);
  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _wfopen(const wchar_t * __restrict__ _Filename,const wchar_t *__restrict__ _Mode) ;
  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _wfreopen(const wchar_t * __restrict__ _Filename,const wchar_t * __restrict__ _Mode,FILE * __restrict__ _OldFile) ;



  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _wperror(const wchar_t *_ErrMsg);

  __attribute__ ((__dllimport__)) FILE *__attribute__((__cdecl__)) _wpopen(const wchar_t *_Command,const wchar_t *_Mode);




  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wremove(const wchar_t *_Filename);
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wtmpnam(wchar_t *_Buffer);

  __attribute__ ((__dllimport__)) wint_t __attribute__((__cdecl__)) _fgetwc_nolock(FILE *_File);
  __attribute__ ((__dllimport__)) wint_t __attribute__((__cdecl__)) _fputwc_nolock(wchar_t _Ch,FILE *_File);
  __attribute__ ((__dllimport__)) wint_t __attribute__((__cdecl__)) _ungetwc_nolock(wint_t _Ch,FILE *_File);
# 1210 "C:/msys64/clang64/include/stdio.h" 3
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fgetc_nolock(FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fputc_nolock(int _Char, FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _getc_nolock(FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _putc_nolock(int _Char, FILE *_File);
# 1225 "C:/msys64/clang64/include/stdio.h" 3
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _lock_file(FILE *_File);
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _unlock_file(FILE *_File);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fclose_nolock(FILE *_File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fflush_nolock(FILE *_File);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _fread_nolock(void * __restrict__ _DstBuf,size_t _ElementSize,size_t _Count,FILE * __restrict__ _File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fseek_nolock(FILE *_File,long _Offset,int _Origin);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _ftell_nolock(FILE *_File);
  __extension__ __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fseeki64_nolock(FILE *_File,long long _Offset,int _Origin);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _ftelli64_nolock(FILE *_File);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _fwrite_nolock(const void * __restrict__ _DstBuf,size_t _Size,size_t _Count,FILE * __restrict__ _File);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _ungetc_nolock(int _Ch,FILE *_File);
# 1247 "C:/msys64/clang64/include/stdio.h" 3
  char *__attribute__((__cdecl__)) tempnam(const char *_Directory,const char *_FilePrefix) ;



  int __attribute__((__cdecl__)) fcloseall(void) ;
  FILE *__attribute__((__cdecl__)) fdopen(int _FileHandle,const char *_Format) ;
  int __attribute__((__cdecl__)) fgetchar(void) ;
  int __attribute__((__cdecl__)) fileno(FILE *_File) ;
  int __attribute__((__cdecl__)) flushall(void) ;
  int __attribute__((__cdecl__)) fputchar(int _Ch) ;
  int __attribute__((__cdecl__)) getw(FILE *_File) ;
  int __attribute__((__cdecl__)) putw(int _Ch,FILE *_File) ;
  int __attribute__((__cdecl__)) rmtmp(void) ;
# 1276 "C:/msys64/clang64/include/stdio.h" 3
int __attribute__((__cdecl__)) __mingw_str_wide_utf8 (const wchar_t * const wptr, char **mbptr, size_t * buflen);
# 1290 "C:/msys64/clang64/include/stdio.h" 3
int __attribute__((__cdecl__)) __mingw_str_utf8_wide (const char *const mbptr, wchar_t ** wptr, size_t * buflen);
# 1299 "C:/msys64/clang64/include/stdio.h" 3
void __attribute__((__cdecl__)) __mingw_str_free(void *ptr);






  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnl(int _Mode,const wchar_t *_Filename,const wchar_t *_ArgList,...);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnle(int _Mode,const wchar_t *_Filename,const wchar_t *_ArgList,...);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnlp(int _Mode,const wchar_t *_Filename,const wchar_t *_ArgList,...);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnlpe(int _Mode,const wchar_t *_Filename,const wchar_t *_ArgList,...);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnv(int _Mode,const wchar_t *_Filename,const wchar_t *const *_ArgList);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnve(int _Mode,const wchar_t *_Filename,const wchar_t *const *_ArgList,const wchar_t *const *_Env);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnvp(int _Mode,const wchar_t *_Filename,const wchar_t *const *_ArgList);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _wspawnvpe(int _Mode,const wchar_t *_Filename,const wchar_t *const *_ArgList,const wchar_t *const *_Env);
# 1330 "C:/msys64/clang64/include/stdio.h" 3
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _spawnv(int _Mode,const char *_Filename,const char *const *_ArgList);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _spawnve(int _Mode,const char *_Filename,const char *const *_ArgList,const char *const *_Env);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _spawnvp(int _Mode,const char *_Filename,const char *const *_ArgList);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _spawnvpe(int _Mode,const char *_Filename,const char *const *_ArgList,const char *const *_Env);
# 1346 "C:/msys64/clang64/include/stdio.h" 3
#pragma pack(pop)

# 1 "C:/msys64/clang64/include/sec_api/stdio_s.h" 1 3








# 1 "C:/msys64/clang64/include/stdio.h" 1 3
# 10 "C:/msys64/clang64/include/sec_api/stdio_s.h" 2 3
# 29 "C:/msys64/clang64/include/sec_api/stdio_s.h" 3
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) clearerr_s(FILE *_File);

  size_t __attribute__((__cdecl__)) fread_s(void *_DstBuf,size_t _DstSize,size_t _ElementSize,size_t _Count,FILE *_File);


  int __attribute__((__cdecl__)) __stdio_common_vsprintf_s(unsigned long long _Options, char *_Str, size_t _Len, const char *_Format, _locale_t _Locale, va_list _ArgList);
  int __attribute__((__cdecl__)) __stdio_common_vsprintf_p(unsigned long long _Options, char *_Str, size_t _Len, const char *_Format, _locale_t _Locale, va_list _ArgList);
  int __attribute__((__cdecl__)) __stdio_common_vsnprintf_s(unsigned long long _Options, char *_Str, size_t _Len, size_t _MaxCount, const char *_Format, _locale_t _Locale, va_list _ArgList);
  int __attribute__((__cdecl__)) __stdio_common_vfprintf_s(unsigned long long _Options, FILE *_File, const char *_Format, _locale_t _Locale, va_list _ArgList);
  int __attribute__((__cdecl__)) __stdio_common_vfprintf_p(unsigned long long _Options, FILE *_File, const char *_Format, _locale_t _Locale, va_list _ArgList);

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vfscanf_s_l(FILE *_File, const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vfscanf(0x0001ULL, _File, _Format, _Locale, _ArgList);
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vfscanf_s(FILE *_File, const char *_Format, va_list _ArgList)
  {
    return _vfscanf_s_l(_File, _Format, ((void *)0), _ArgList);
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vscanf_s_l(const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return _vfscanf_s_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vscanf_s(const char *_Format, va_list _ArgList)
  {
    return _vfscanf_s_l((__acrt_iob_func(0)), _Format, ((void *)0), _ArgList);
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _fscanf_s_l(FILE *_File, const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vfscanf_s_l(_File, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) fscanf_s(FILE *_File, const char *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vfscanf_s_l(_File, _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _scanf_s_l(const char *_Format, _locale_t _Locale ,...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vfscanf_s_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) scanf_s(const char *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vfscanf_s_l((__acrt_iob_func(0)), _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vfscanf_l(FILE *_File, const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vfscanf(0, _File, _Format, _Locale, _ArgList);
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vscanf_l(const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return _vfscanf_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _fscanf_l(FILE *_File, const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vfscanf_l(_File, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _scanf_l(const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vfscanf_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsscanf_s_l(const char *_Src, const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vsscanf(0x0001ULL, _Src, (size_t)-1, _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vsscanf_s(const char *_Src, const char *_Format, va_list _ArgList)
  {
    return _vsscanf_s_l(_Src, _Format, ((void *)0), _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _sscanf_s_l(const char *_Src, const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vsscanf_s_l(_Src, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) sscanf_s(const char *_Src, const char *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vsscanf_s_l(_Src, _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsscanf_l(const char *_Src, const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vsscanf(0, _Src, (size_t)-1, _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _sscanf_l(const char *_Src, const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vsscanf_l(_Src, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }


  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snscanf_s_l(const char *_Src, size_t _MaxCount, const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = __stdio_common_vsscanf(0x0001ULL, _Src, _MaxCount, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snscanf_s(const char *_Src, size_t _MaxCount, const char *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = __stdio_common_vsscanf(0x0001ULL, _Src, _MaxCount, _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }


  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snscanf_l(const char *_Src, size_t _MaxCount, const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = __stdio_common_vsscanf(0, _Src, _MaxCount, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }


  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vfprintf_s_l(FILE *_File, const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vfprintf_s((*__local_stdio_printf_options()), _File, _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vfprintf_s(FILE *_File, const char *_Format, va_list _ArgList)
  {
    return _vfprintf_s_l(_File, _Format, ((void *)0), _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vprintf_s_l(const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return _vfprintf_s_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vprintf_s(const char *_Format, va_list _ArgList)
  {
    return _vfprintf_s_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _fprintf_s_l(FILE *_File, const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vfprintf_s_l(_File, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _printf_s_l(const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vfprintf_s_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) fprintf_s(FILE *_File, const char *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vfprintf_s_l(_File, _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) printf_s(const char *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vfprintf_s_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsnprintf_c_l(char *_DstBuf, size_t _MaxCount, const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vsprintf((*__local_stdio_printf_options()), _DstBuf, _MaxCount, _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsnprintf_c(char *_DstBuf, size_t _MaxCount, const char *_Format, va_list _ArgList)
  {
    return _vsnprintf_c_l(_DstBuf, _MaxCount, _Format, ((void *)0), _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snprintf_c_l(char *_DstBuf, size_t _MaxCount, const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vsnprintf_c_l(_DstBuf, _MaxCount, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snprintf_c(char *_DstBuf, size_t _MaxCount, const char *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vsnprintf_c_l(_DstBuf, _MaxCount, _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsnprintf_s_l(char *_DstBuf, size_t _DstSize, size_t _MaxCount, const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vsnprintf_s((*__local_stdio_printf_options()), _DstBuf, _DstSize, _MaxCount, _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vsnprintf_s(char *_DstBuf, size_t _DstSize, size_t _MaxCount, const char *_Format, va_list _ArgList)
  {
    return _vsnprintf_s_l(_DstBuf, _DstSize, _MaxCount, _Format, ((void *)0), _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsnprintf_s(char *_DstBuf, size_t _DstSize, size_t _MaxCount, const char *_Format, va_list _ArgList)
  {
    return _vsnprintf_s_l(_DstBuf, _DstSize, _MaxCount, _Format, ((void *)0), _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snprintf_s_l(char *_DstBuf, size_t _DstSize, size_t _MaxCount, const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vsnprintf_s_l(_DstBuf, _DstSize, _MaxCount, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snprintf_s(char *_DstBuf, size_t _DstSize, size_t _MaxCount, const char *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vsnprintf_s_l(_DstBuf, _DstSize, _MaxCount, _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsprintf_s_l(char *_DstBuf, size_t _DstSize, const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vsprintf_s((*__local_stdio_printf_options()), _DstBuf, _DstSize, _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vsprintf_s(char *_DstBuf, size_t _Size, const char *_Format, va_list _ArgList)
  {
    return _vsprintf_s_l(_DstBuf, _Size, _Format, ((void *)0), _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _sprintf_s_l(char *_DstBuf, size_t _DstSize, const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vsprintf_s_l(_DstBuf, _DstSize, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) sprintf_s(char *_DstBuf, size_t _DstSize, const char *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vsprintf_s_l(_DstBuf, _DstSize, _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vfprintf_p_l(FILE *_File, const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vfprintf_p((*__local_stdio_printf_options()), _File, _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vfprintf_p(FILE *_File, const char *_Format, va_list _ArgList)
  {
    return _vfprintf_p_l(_File, _Format, ((void *)0), _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vprintf_p_l(const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return _vfprintf_p_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vprintf_p(const char *_Format, va_list _ArgList)
  {
    return _vfprintf_p_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _fprintf_p_l(FILE *_File, const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = __stdio_common_vfprintf_p((*__local_stdio_printf_options()), _File, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _fprintf_p(FILE *_File, const char *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vfprintf_p_l(_File, _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _printf_p_l(const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vfprintf_p_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _printf_p(const char *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vfprintf_p_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsprintf_p_l(char *_DstBuf, size_t _MaxCount, const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vsprintf_p((*__local_stdio_printf_options()), _DstBuf, _MaxCount, _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsprintf_p(char *_Dst, size_t _MaxCount, const char *_Format, va_list _ArgList)
  {
    return _vsprintf_p_l(_Dst, _MaxCount, _Format, ((void *)0), _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _sprintf_p_l(char *_DstBuf, size_t _MaxCount, const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vsprintf_p_l(_DstBuf, _MaxCount, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _sprintf_p(char *_Dst, size_t _MaxCount, const char *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vsprintf_p_l(_Dst, _MaxCount, _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vscprintf_p_l(const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vsprintf_p(0x0002ULL, ((void *)0), 0, _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vscprintf_p(const char *_Format, va_list _ArgList)
  {
    return _vscprintf_p_l(_Format, ((void *)0), _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _scprintf_p_l(const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vscprintf_p_l(_Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _scprintf_p(const char *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vscprintf_p_l(_Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vfprintf_l(FILE *_File, const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vfprintf((*__local_stdio_printf_options()), _File, _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vprintf_l(const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return _vfprintf_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _fprintf_l(FILE *_File, const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vfprintf_l(_File, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _printf_l(const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vfprintf_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsnprintf_l(char *_DstBuf, size_t _MaxCount, const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vsprintf(0x0001ULL, _DstBuf, _MaxCount, _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snprintf_l(char *_DstBuf, size_t _MaxCount, const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vsnprintf_l(_DstBuf, _MaxCount, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsprintf_l(char *_DstBuf, const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return _vsnprintf_l(_DstBuf, (size_t)-1, _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _sprintf_l(char *_DstBuf, const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vsprintf_l(_DstBuf, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vscprintf_l(const char *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vsprintf(0x0002ULL, ((void *)0), 0, _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _scprintf_l(const char *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vscprintf_l(_Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
# 589 "C:/msys64/clang64/include/sec_api/stdio_s.h" 3
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) fopen_s(FILE **_File,const char *_Filename,const char *_Mode);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) freopen_s(FILE** _File, const char *_Filename, const char *_Mode, FILE *_Stream);

  __attribute__ ((__dllimport__)) char* __attribute__((__cdecl__)) gets_s(char*,rsize_t);


  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) tmpfile_s(FILE **_File);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) tmpnam_s(char*,rsize_t);





  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _getws_s(wchar_t *_Str,size_t _SizeInWords);



  int __attribute__((__cdecl__)) __stdio_common_vswprintf_s(unsigned long long _Options, wchar_t *_Str, size_t _Len, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList);
  int __attribute__((__cdecl__)) __stdio_common_vsnwprintf_s(unsigned long long _Options, wchar_t *_Str, size_t _Len, size_t _MaxCount, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList);
  int __attribute__((__cdecl__)) __stdio_common_vfwprintf_s(unsigned long long _Options, FILE *_File, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList);

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vfwscanf_s_l(FILE *_File, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vfwscanf((*__local_stdio_scanf_options()) | 0x0001ULL, _File, _Format, _Locale, _ArgList);
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vfwscanf_s(FILE* _File, const wchar_t *_Format, va_list _ArgList)
  {
    return _vfwscanf_s_l(_File, _Format, ((void *)0), _ArgList);
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vwscanf_s_l(const wchar_t *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return _vfwscanf_s_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vwscanf_s(const wchar_t *_Format, va_list _ArgList)
  {
    return _vfwscanf_s_l((__acrt_iob_func(0)), _Format, ((void *)0), _ArgList);
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _fwscanf_s_l(FILE *_File, const wchar_t *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vfwscanf_s_l(_File, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) fwscanf_s(FILE *_File, const wchar_t *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vfwscanf_s_l(_File, _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _wscanf_s_l(const wchar_t *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vfwscanf_s_l((__acrt_iob_func(0)), _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) wscanf_s(const wchar_t *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vfwscanf_s_l((__acrt_iob_func(0)), _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vswscanf_s_l(const wchar_t *_Src, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vswscanf((*__local_stdio_scanf_options()) | 0x0001ULL, _Src, (size_t)-1, _Format, _Locale, _ArgList);
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vswscanf_s(const wchar_t *_Src, const wchar_t *_Format, va_list _ArgList)
  {
    return _vswscanf_s_l(_Src, _Format, ((void *)0), _ArgList);
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _swscanf_s_l(const wchar_t *_Src, const wchar_t *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vswscanf_s_l(_Src, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) swscanf_s(const wchar_t *_Src, const wchar_t *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vswscanf_s_l(_Src, _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsnwscanf_s_l(const wchar_t *_Src, size_t _MaxCount, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vswscanf((*__local_stdio_scanf_options()) | 0x0001ULL, _Src, _MaxCount, _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snwscanf_s_l(const wchar_t *_Src, size_t _MaxCount, const wchar_t *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vsnwscanf_s_l(_Src, _MaxCount, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snwscanf_s(const wchar_t *_Src, size_t _MaxCount, const wchar_t *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vsnwscanf_s_l(_Src, _MaxCount, _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vfwprintf_s_l(FILE *_File, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vfwprintf_s((*__local_stdio_printf_options()), _File, _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vwprintf_s_l(const wchar_t *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return _vfwprintf_s_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vfwprintf_s(FILE *_File, const wchar_t *_Format, va_list _ArgList)
  {
    return _vfwprintf_s_l(_File, _Format, ((void *)0), _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vwprintf_s(const wchar_t *_Format, va_list _ArgList)
  {
    return _vfwprintf_s_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _fwprintf_s_l(FILE *_File, const wchar_t *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vfwprintf_s_l(_File, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _wprintf_s_l(const wchar_t *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vfwprintf_s_l((__acrt_iob_func(1)), _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) fwprintf_s(FILE *_File, const wchar_t *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vfwprintf_s_l(_File, _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) wprintf_s(const wchar_t *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vfwprintf_s_l((__acrt_iob_func(1)), _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vswprintf_s_l(wchar_t *_DstBuf, size_t _DstSize, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vswprintf_s((*__local_stdio_printf_options()), _DstBuf, _DstSize, _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) vswprintf_s(wchar_t *_DstBuf, size_t _DstSize, const wchar_t *_Format, va_list _ArgList)
  {
    return _vswprintf_s_l(_DstBuf, _DstSize, _Format, ((void *)0), _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _swprintf_s_l(wchar_t *_DstBuf, size_t _DstSize, const wchar_t *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vswprintf_s_l(_DstBuf, _DstSize, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) swprintf_s(wchar_t *_DstBuf, size_t _DstSize, const wchar_t *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vswprintf_s_l(_DstBuf, _DstSize, _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }

  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsnwprintf_s_l(wchar_t *_DstBuf, size_t _DstSize, size_t _MaxCount, const wchar_t *_Format, _locale_t _Locale, va_list _ArgList)
  {
    return __stdio_common_vsnwprintf_s((*__local_stdio_printf_options()), _DstBuf, _DstSize, _MaxCount, _Format, _Locale, _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _vsnwprintf_s(wchar_t *_DstBuf, size_t _DstSize, size_t _MaxCount, const wchar_t *_Format, va_list _ArgList)
  {
    return _vsnwprintf_s_l(_DstBuf, _DstSize, _MaxCount, _Format, ((void *)0), _ArgList);
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snwprintf_s_l(wchar_t *_DstBuf, size_t _DstSize, size_t _MaxCount, const wchar_t *_Format, _locale_t _Locale, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Locale);
    _Ret = _vsnwprintf_s_l(_DstBuf, _DstSize, _MaxCount, _Format, _Locale, _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
  static __attribute__ ((__unused__)) __inline__ __attribute__((__cdecl__)) int __attribute__((__cdecl__)) _snwprintf_s(wchar_t *_DstBuf, size_t _DstSize, size_t _MaxCount, const wchar_t *_Format, ...)
  {
    __builtin_va_list _ArgList;
    int _Ret;
    __builtin_va_start(_ArgList, _Format);
    _Ret = _vsnwprintf_s_l(_DstBuf, _DstSize, _MaxCount, _Format, ((void *)0), _ArgList);
    __builtin_va_end(_ArgList);
    return _Ret;
  }
# 867 "C:/msys64/clang64/include/sec_api/stdio_s.h" 3
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wfopen_s(FILE **_File,const wchar_t *_Filename,const wchar_t *_Mode);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wfreopen_s(FILE **_File,const wchar_t *_Filename,const wchar_t *_Mode,FILE *_OldFile);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wtmpnam_s(wchar_t *_DstBuf,size_t _SizeInWords);
# 912 "C:/msys64/clang64/include/sec_api/stdio_s.h" 3
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _fread_nolock_s(void *_DstBuf,size_t _DstSize,size_t _ElementSize,size_t _Count,FILE *_File);
# 1349 "C:/msys64/clang64/include/stdio.h" 2 3
# 8 "src/filli.h" 2
# 1 "C:/msys64/clang64/lib/clang/21/include/stdint.h" 1 3
# 56 "C:/msys64/clang64/lib/clang/21/include/stdint.h" 3
# 1 "C:/msys64/clang64/include/stdint.h" 1 3
# 28 "C:/msys64/clang64/include/stdint.h" 3
# 1 "C:/msys64/clang64/include/crtdefs.h" 1 3
# 29 "C:/msys64/clang64/include/stdint.h" 2 3



# 1 "C:/msys64/clang64/lib/clang/21/include/stddef.h" 1 3
# 103 "C:/msys64/clang64/lib/clang/21/include/stddef.h" 3
# 1 "C:/msys64/clang64/lib/clang/21/include/__stddef_wchar_t.h" 1 3
# 24 "C:/msys64/clang64/lib/clang/21/include/__stddef_wchar_t.h" 3
typedef unsigned short wchar_t;
# 104 "C:/msys64/clang64/lib/clang/21/include/stddef.h" 2 3
# 135 "C:/msys64/clang64/lib/clang/21/include/stddef.h" 3
# 1 "C:/msys64/clang64/lib/clang/21/include/__stddef_wint_t.h" 1 3
# 136 "C:/msys64/clang64/lib/clang/21/include/stddef.h" 2 3
# 33 "C:/msys64/clang64/include/stdint.h" 2 3


typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned uint32_t;
__extension__ typedef long long int64_t;
__extension__ typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;
typedef short int_least16_t;
typedef unsigned short uint_least16_t;
typedef int int_least32_t;
typedef unsigned uint_least32_t;
__extension__ typedef long long int_least64_t;
__extension__ typedef unsigned long long uint_least64_t;





typedef signed char int_fast8_t;
typedef unsigned char uint_fast8_t;
typedef short int_fast16_t;
typedef unsigned short uint_fast16_t;
typedef int int_fast32_t;
typedef unsigned int uint_fast32_t;
__extension__ typedef long long int_fast64_t;
__extension__ typedef unsigned long long uint_fast64_t;


__extension__ typedef long long intmax_t;
__extension__ typedef unsigned long long uintmax_t;
# 57 "C:/msys64/clang64/lib/clang/21/include/stdint.h" 2 3
# 9 "src/filli.h" 2
# 1 "C:/msys64/clang64/include/stdlib.h" 1 3
# 10 "C:/msys64/clang64/include/stdlib.h" 3
# 1 "C:/msys64/clang64/include/corecrt_wstdlib.h" 1 3
# 19 "C:/msys64/clang64/include/corecrt_wstdlib.h" 3
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wdupenv_s(wchar_t **_Buffer,size_t *_BufferSizeInWords,const wchar_t *_VarName);




  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _itow_s (int _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);


  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ltow_s (long _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);


  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ultow_s (unsigned long _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);


  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wgetenv_s(size_t *_ReturnSize,wchar_t *_DstBuf,size_t _DstSizeInWords,const wchar_t *_VarName);


  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _i64tow_s(long long _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ui64tow_s(unsigned long long _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wmakepath_s(wchar_t *_PathResult,size_t _SizeInWords,const wchar_t *_Drive,const wchar_t *_Dir,const wchar_t *_Filename,const wchar_t *_Ext);


  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wputenv_s(const wchar_t *_Name,const wchar_t *_Value);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wsearchenv_s(const wchar_t *_Filename,const wchar_t *_EnvVar,wchar_t *_ResultPath,size_t _SizeInWords);


  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wsplitpath_s(const wchar_t *_FullPath,wchar_t *_Drive,size_t _DriveSizeInWords,wchar_t *_Dir,size_t _DirSizeInWords,wchar_t *_Filename,size_t _FilenameSizeInWords,wchar_t *_Ext,size_t _ExtSizeInWords);
# 11 "C:/msys64/clang64/include/stdlib.h" 2 3
# 1 "C:/msys64/clang64/lib/clang/21/include/limits.h" 1 3
# 25 "C:/msys64/clang64/lib/clang/21/include/limits.h" 3
# 1 "C:/msys64/clang64/include/limits.h" 1 3
# 26 "C:/msys64/clang64/lib/clang/21/include/limits.h" 2 3
# 12 "C:/msys64/clang64/include/stdlib.h" 2 3
# 26 "C:/msys64/clang64/include/stdlib.h" 3
#pragma pack(push,_CRT_PACKING)
# 50 "C:/msys64/clang64/include/stdlib.h" 3
  typedef int (__attribute__((__cdecl__)) *_onexit_t)(void);
# 60 "C:/msys64/clang64/include/stdlib.h" 3
  typedef struct _div_t {
    int quot;
    int rem;
  } div_t;

  typedef struct _ldiv_t {
    long quot;
    long rem;
  } ldiv_t;





#pragma pack(4)
  typedef struct {
    unsigned char ld[10];
  } _LDOUBLE;
#pragma pack()



  typedef struct {
    double x;
  } _CRT_DOUBLE;

  typedef struct {
    float f;
  } _CRT_FLOAT;




  typedef struct {
    long double x;
  } _LONGDOUBLE;



#pragma pack(4)
  typedef struct {
    unsigned char ld12[12];
  } _LDBL12;
#pragma pack()
# 113 "C:/msys64/clang64/include/stdlib.h" 3
__attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) ___mb_cur_max_func(void);
# 135 "C:/msys64/clang64/include/stdlib.h" 3
  typedef void (__attribute__((__cdecl__)) *_purecall_handler)(void);

  __attribute__ ((__dllimport__)) _purecall_handler __attribute__((__cdecl__)) _set_purecall_handler(_purecall_handler _Handler);
  __attribute__ ((__dllimport__)) _purecall_handler __attribute__((__cdecl__)) _get_purecall_handler(void);

  typedef void (__attribute__((__cdecl__)) *_invalid_parameter_handler)(const wchar_t *,const wchar_t *,const wchar_t *,unsigned int,uintptr_t);
  __attribute__ ((__dllimport__)) _invalid_parameter_handler __attribute__((__cdecl__)) _set_invalid_parameter_handler(_invalid_parameter_handler _Handler);
  __attribute__ ((__dllimport__)) _invalid_parameter_handler __attribute__((__cdecl__)) _get_invalid_parameter_handler(void);



  __attribute__ ((__dllimport__)) extern int *__attribute__((__cdecl__)) _errno(void);

  errno_t __attribute__((__cdecl__)) _set_errno(int _Value);
  errno_t __attribute__((__cdecl__)) _get_errno(int *_Value);

  __attribute__ ((__dllimport__)) unsigned long *__attribute__((__cdecl__)) __doserrno(void);

  errno_t __attribute__((__cdecl__)) _set_doserrno(unsigned long _Value);
  errno_t __attribute__((__cdecl__)) _get_doserrno(unsigned long *_Value);
  __attribute__ ((__dllimport__)) char **__attribute__((__cdecl__)) __sys_errlist(void);
  __attribute__ ((__dllimport__)) int *__attribute__((__cdecl__)) __sys_nerr(void);



  __attribute__ ((__dllimport__)) char ***__attribute__((__cdecl__)) __p___argv(void);
  __attribute__ ((__dllimport__)) int *__attribute__((__cdecl__)) __p__fmode(void);
  __attribute__ ((__dllimport__)) int *__attribute__((__cdecl__)) __p___argc(void);
  __attribute__ ((__dllimport__)) wchar_t ***__attribute__((__cdecl__)) __p___wargv(void);
  __attribute__ ((__dllimport__)) char **__attribute__((__cdecl__)) __p__pgmptr(void);
  __attribute__ ((__dllimport__)) wchar_t **__attribute__((__cdecl__)) __p__wpgmptr(void);

  errno_t __attribute__((__cdecl__)) _get_pgmptr(char **_Value);
  errno_t __attribute__((__cdecl__)) _get_wpgmptr(wchar_t **_Value);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _set_fmode(int _Mode);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _get_fmode(int *_PMode);
# 221 "C:/msys64/clang64/include/stdlib.h" 3
  __attribute__ ((__dllimport__)) char ***__attribute__((__cdecl__)) __p__environ(void);
  __attribute__ ((__dllimport__)) wchar_t ***__attribute__((__cdecl__)) __p__wenviron(void);
# 234 "C:/msys64/clang64/include/stdlib.h" 3
  __attribute__ ((__dllimport__)) unsigned int *__attribute__((__cdecl__)) __p__osplatform(void);
  __attribute__ ((__dllimport__)) unsigned int *__attribute__((__cdecl__)) __p__osver(void);
  __attribute__ ((__dllimport__)) unsigned int *__attribute__((__cdecl__)) __p__winver(void);
  __attribute__ ((__dllimport__)) unsigned int *__attribute__((__cdecl__)) __p__winmajor(void);
  __attribute__ ((__dllimport__)) unsigned int *__attribute__((__cdecl__)) __p__winminor(void);
# 256 "C:/msys64/clang64/include/stdlib.h" 3
  errno_t __attribute__((__cdecl__)) _get_osplatform(unsigned int *_Value);
  errno_t __attribute__((__cdecl__)) _get_osver(unsigned int *_Value);
  errno_t __attribute__((__cdecl__)) _get_winver(unsigned int *_Value);
  errno_t __attribute__((__cdecl__)) _get_winmajor(unsigned int *_Value);
  errno_t __attribute__((__cdecl__)) _get_winminor(unsigned int *_Value);
# 274 "C:/msys64/clang64/include/stdlib.h" 3
  void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) exit(int _Code) __attribute__ ((__noreturn__));
  void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _exit(int _Code) __attribute__ ((__noreturn__));

  void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) quick_exit(int _Code) __attribute__ ((__noreturn__));




  void __attribute__((__cdecl__)) _Exit(int) __attribute__ ((__noreturn__));
# 291 "C:/msys64/clang64/include/stdlib.h" 3
  void __attribute__((__cdecl__)) __attribute__ ((__noreturn__)) abort(void);




  __attribute__ ((__dllimport__)) unsigned int __attribute__((__cdecl__)) _set_abort_behavior(unsigned int _Flags,unsigned int _Mask);



  int __attribute__((__cdecl__)) abs(int _X);
  long __attribute__((__cdecl__)) labs(long _X);


  __extension__ long long __attribute__((__cdecl__)) _abs64(long long);

  extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) long long __attribute__((__cdecl__)) _abs64(long long x) {
    return __builtin_llabs(x);
  }


  int __attribute__((__cdecl__)) atexit(void (__attribute__((__cdecl__)) *)(void));

  int __attribute__((__cdecl__)) at_quick_exit(void (__attribute__((__cdecl__)) *)(void));



  double __attribute__((__cdecl__)) atof(const char *_String);
  double __attribute__((__cdecl__)) _atof_l(const char *_String,_locale_t _Locale);

  int __attribute__((__cdecl__)) atoi(const char *_Str);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atoi_l(const char *_Str,_locale_t _Locale);
  long __attribute__((__cdecl__)) atol(const char *_Str);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _atol_l(const char *_Str,_locale_t _Locale);


  void *__attribute__((__cdecl__)) bsearch(const void *_Key,const void *_Base,size_t _NumOfElements,size_t _SizeOfElements,int (__attribute__((__cdecl__)) *_PtFuncCompare)(const void *,const void *));
  void __attribute__((__cdecl__)) qsort(void *_Base,size_t _NumOfElements,size_t _SizeOfElements,int (__attribute__((__cdecl__)) *_PtFuncCompare)(const void *,const void *));

  unsigned short __attribute__((__cdecl__)) _byteswap_ushort(unsigned short _Short);
  unsigned long __attribute__((__cdecl__)) _byteswap_ulong (unsigned long _Long);
  __extension__ unsigned long long __attribute__((__cdecl__)) _byteswap_uint64(unsigned long long _Int64);
  div_t __attribute__((__cdecl__)) div(int _Numerator,int _Denominator);
  char *__attribute__((__cdecl__)) getenv(const char *_VarName) ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _itoa(int _Value,char *_Dest,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _i64toa(long long _Val,char *_DstBuf,int _Radix) ;
  __extension__ __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _ui64toa(unsigned long long _Val,char *_DstBuf,int _Radix) ;
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _atoi64(const char *_String);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _atoi64_l(const char *_String,_locale_t _Locale);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _strtoi64(const char *_String,char **_EndPtr,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _strtoi64_l(const char *_String,char **_EndPtr,int _Radix,_locale_t _Locale);
  __extension__ __attribute__ ((__dllimport__)) unsigned long long __attribute__((__cdecl__)) _strtoui64(const char *_String,char **_EndPtr,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) unsigned long long __attribute__((__cdecl__)) _strtoui64_l(const char *_String,char **_EndPtr,int _Radix,_locale_t _Locale);
  ldiv_t __attribute__((__cdecl__)) ldiv(long _Numerator,long _Denominator);
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _ltoa(long _Value,char *_Dest,int _Radix) ;
  int __attribute__((__cdecl__)) mblen(const char *_Ch,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _mblen_l(const char *_Ch,size_t _MaxCount,_locale_t _Locale);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _mbstrlen(const char *_Str);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _mbstrlen_l(const char *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _mbstrnlen(const char *_Str,size_t _MaxCount);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _mbstrnlen_l(const char *_Str,size_t _MaxCount,_locale_t _Locale);
  int __attribute__((__cdecl__)) mbtowc(wchar_t * __restrict__ _DstCh,const char * __restrict__ _SrcCh,size_t _SrcSizeInBytes);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _mbtowc_l(wchar_t * __restrict__ _DstCh,const char * __restrict__ _SrcCh,size_t _SrcSizeInBytes,_locale_t _Locale);
  size_t __attribute__((__cdecl__)) mbstowcs(wchar_t * __restrict__ _Dest,const char * __restrict__ _Source,size_t _MaxCount);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _mbstowcs_l(wchar_t * __restrict__ _Dest,const char * __restrict__ _Source,size_t _MaxCount,_locale_t _Locale);
  int __attribute__((__cdecl__)) mkstemp(char *template_name);
  int __attribute__((__cdecl__)) rand(void);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _set_error_mode(int _Mode);
  void __attribute__((__cdecl__)) srand(unsigned int _Seed);
# 385 "C:/msys64/clang64/include/stdlib.h" 3
  double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtod(const char * __restrict__ _Str,char ** __restrict__ _EndPtr);
  float __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtof(const char * __restrict__ nptr, char ** __restrict__ endptr);

  long double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtold(const char * __restrict__ , char ** __restrict__ );


  extern double __attribute__((__cdecl__)) __attribute__ ((__nothrow__))
  __strtod (const char * __restrict__ , char ** __restrict__);







  float __attribute__((__cdecl__)) __mingw_strtof (const char * __restrict__, char ** __restrict__);
  double __attribute__((__cdecl__)) __mingw_strtod (const char * __restrict__, char ** __restrict__);
  long double __attribute__((__cdecl__)) __mingw_strtold(const char * __restrict__, char ** __restrict__);

  __attribute__ ((__dllimport__)) float __attribute__((__cdecl__)) _strtof_l(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,_locale_t _Locale);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _strtod_l(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,_locale_t _Locale);
  long __attribute__((__cdecl__)) strtol(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,int _Radix);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _strtol_l(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,int _Radix,_locale_t _Locale);
  unsigned long __attribute__((__cdecl__)) strtoul(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,int _Radix);
  __attribute__ ((__dllimport__)) unsigned long __attribute__((__cdecl__)) _strtoul_l(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,int _Radix,_locale_t _Locale);


  int __attribute__((__cdecl__)) system(const char *_Command);

  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _ultoa(unsigned long _Value,char *_Dest,int _Radix) ;
  int __attribute__((__cdecl__)) wctomb(char *_MbCh,wchar_t _WCh) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wctomb_l(char *_MbCh,wchar_t _WCh,_locale_t _Locale) ;
  size_t __attribute__((__cdecl__)) wcstombs(char * __restrict__ _Dest,const wchar_t * __restrict__ _Source,size_t _MaxCount) ;
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _wcstombs_l(char * __restrict__ _Dest,const wchar_t * __restrict__ _Source,size_t _MaxCount,_locale_t _Locale) ;
# 452 "C:/msys64/clang64/include/stdlib.h" 3
  void *__attribute__((__cdecl__)) calloc(size_t _NumOfElements,size_t _SizeOfElements);
  void __attribute__((__cdecl__)) free(void *_Memory);
  void *__attribute__((__cdecl__)) malloc(size_t _Size);
  void *__attribute__((__cdecl__)) realloc(void *_Memory,size_t _NewSize);
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _aligned_free(void *_Memory);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _aligned_malloc(size_t _Size,size_t _Alignment);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _aligned_offset_malloc(size_t _Size,size_t _Alignment,size_t _Offset);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _aligned_realloc(void *_Memory,size_t _Size,size_t _Alignment);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _aligned_offset_realloc(void *_Memory,size_t _Size,size_t _Alignment,size_t _Offset);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _recalloc(void *_Memory,size_t _Count,size_t _Size);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _aligned_recalloc(void *_Memory,size_t _Count,size_t _Size,size_t _Alignment);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _aligned_offset_recalloc(void *_Memory,size_t _Count,size_t _Size,size_t _Alignment,size_t _Offset);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _aligned_msize(void *_Memory,size_t _Alignment,size_t _Offset);
# 487 "C:/msys64/clang64/include/stdlib.h" 3
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _itow(int _Value,wchar_t *_Dest,int _Radix) ;
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _ltow(long _Value,wchar_t *_Dest,int _Radix) ;
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _ultow(unsigned long _Value,wchar_t *_Dest,int _Radix) ;

  double __attribute__((__cdecl__)) __mingw_wcstod(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr);
  float __attribute__((__cdecl__)) __mingw_wcstof(const wchar_t * __restrict__ nptr, wchar_t ** __restrict__ endptr);
  long double __attribute__((__cdecl__)) __mingw_wcstold(const wchar_t * __restrict__, wchar_t ** __restrict__);
# 506 "C:/msys64/clang64/include/stdlib.h" 3
  double __attribute__((__cdecl__)) wcstod(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr);
  float __attribute__((__cdecl__)) wcstof(const wchar_t * __restrict__ nptr, wchar_t ** __restrict__ endptr);


  long double __attribute__((__cdecl__)) wcstold(const wchar_t * __restrict__, wchar_t ** __restrict__);

  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _wcstod_l(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,_locale_t _Locale);
  __attribute__ ((__dllimport__)) float __attribute__((__cdecl__)) _wcstof_l(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,_locale_t _Locale);
  long __attribute__((__cdecl__)) wcstol(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,int _Radix);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _wcstol_l(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,int _Radix,_locale_t _Locale);
  unsigned long __attribute__((__cdecl__)) wcstoul(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,int _Radix);
  __attribute__ ((__dllimport__)) unsigned long __attribute__((__cdecl__)) _wcstoul_l(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,int _Radix,_locale_t _Locale);
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wgetenv(const wchar_t *_VarName) ;


  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wsystem(const wchar_t *_Command);

  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _wtof(const wchar_t *_Str);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _wtof_l(const wchar_t *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wtoi(const wchar_t *_Str);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wtoi_l(const wchar_t *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _wtol(const wchar_t *_Str);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _wtol_l(const wchar_t *_Str,_locale_t _Locale);

  __extension__ __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _i64tow(long long _Val,wchar_t *_DstBuf,int _Radix) ;
  __extension__ __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _ui64tow(unsigned long long _Val,wchar_t *_DstBuf,int _Radix) ;
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _wtoi64(const wchar_t *_Str);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _wtoi64_l(const wchar_t *_Str,_locale_t _Locale);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _wcstoi64(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _wcstoi64_l(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix,_locale_t _Locale);
  __extension__ __attribute__ ((__dllimport__)) unsigned long long __attribute__((__cdecl__)) _wcstoui64(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) unsigned long long __attribute__((__cdecl__)) _wcstoui64_l(const wchar_t *_Str ,wchar_t **_EndPtr,int _Radix,_locale_t _Locale);


  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _putenv(const char *_EnvString);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wputenv(const wchar_t *_EnvString);
# 550 "C:/msys64/clang64/include/stdlib.h" 3
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _fullpath(char *_FullPath,const char *_Path,size_t _SizeInBytes);




  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _ecvt(double _Val,int _NumOfDigits,int *_PtDec,int *_PtSign) ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _fcvt(double _Val,int _NumOfDec,int *_PtDec,int *_PtSign) ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _gcvt(double _Val,int _NumOfDigits,char *_DstBuf) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atodbl(_CRT_DOUBLE *_Result,char *_Str);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atoldbl(_LDOUBLE *_Result,char *_Str);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atoflt(_CRT_FLOAT *_Result,char *_Str);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atodbl_l(_CRT_DOUBLE *_Result,char *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atoldbl_l(_LDOUBLE *_Result,char *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atoflt_l(_CRT_FLOAT *_Result,char *_Str,_locale_t _Locale);
# 579 "C:/msys64/clang64/include/stdlib.h" 3
unsigned long __attribute__((__cdecl__)) _lrotl(unsigned long,int);
unsigned long __attribute__((__cdecl__)) _lrotr(unsigned long,int);





  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _makepath(char *_Path,const char *_Drive,const char *_Dir,const char *_Filename,const char *_Ext);
  _onexit_t __attribute__((__cdecl__)) _onexit(_onexit_t _Func);
# 597 "C:/msys64/clang64/include/stdlib.h" 3
  __extension__ unsigned long long __attribute__((__cdecl__)) _rotl64(unsigned long long _Val,int _Shift);
  __extension__ unsigned long long __attribute__((__cdecl__)) _rotr64(unsigned long long Value,int Shift);






  unsigned int __attribute__((__cdecl__)) _rotr(unsigned int _Val,int _Shift);
  unsigned int __attribute__((__cdecl__)) _rotl(unsigned int _Val,int _Shift);


  __extension__ unsigned long long __attribute__((__cdecl__)) _rotr64(unsigned long long _Val,int _Shift);
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _searchenv(const char *_Filename,const char *_EnvVar,char *_ResultPath) ;
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _splitpath(const char *_FullPath,char *_Drive,char *_Dir,char *_Filename,char *_Ext) ;
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _swab(char *_Buf1,char *_Buf2,int _SizeInBytes);







  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wfullpath(wchar_t *_FullPath,const wchar_t *_Path,size_t _SizeInWords);



  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _wmakepath(wchar_t *_ResultPath,const wchar_t *_Drive,const wchar_t *_Dir,const wchar_t *_Filename,const wchar_t *_Ext);




  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _wsearchenv(const wchar_t *_Filename,const wchar_t *_EnvVar,wchar_t *_ResultPath) ;
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _wsplitpath(const wchar_t *_FullPath,wchar_t *_Drive,wchar_t *_Dir,wchar_t *_Filename,wchar_t *_Ext) ;


  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _beep(unsigned _Frequency,unsigned _Duration) __attribute__ ((__deprecated__));

  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _seterrormode(int _Mode) __attribute__ ((__deprecated__));
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _sleep(unsigned long _Duration) __attribute__ ((__deprecated__));
# 657 "C:/msys64/clang64/include/stdlib.h" 3
  char *__attribute__((__cdecl__)) ecvt(double _Val,int _NumOfDigits,int *_PtDec,int *_PtSign) ;
  char *__attribute__((__cdecl__)) fcvt(double _Val,int _NumOfDec,int *_PtDec,int *_PtSign) ;
  char *__attribute__((__cdecl__)) gcvt(double _Val,int _NumOfDigits,char *_DstBuf) ;
  char *__attribute__((__cdecl__)) itoa(int _Val,char *_DstBuf,int _Radix) ;
  char *__attribute__((__cdecl__)) ltoa(long _Val,char *_DstBuf,int _Radix) ;
  int __attribute__((__cdecl__)) putenv(const char *_EnvString) ;



  void __attribute__((__cdecl__)) swab(char *_Buf1,char *_Buf2,int _SizeInBytes) ;


  char *__attribute__((__cdecl__)) ultoa(unsigned long _Val,char *_Dstbuf,int _Radix) ;
  _onexit_t __attribute__((__cdecl__)) onexit(_onexit_t _Func);





  typedef struct { __extension__ long long quot, rem; } lldiv_t;

  __extension__ lldiv_t __attribute__((__cdecl__)) lldiv(long long, long long);

  __extension__ long long __attribute__((__cdecl__)) llabs(long long);




  __extension__ long long __attribute__((__cdecl__)) strtoll(const char * __restrict__, char ** __restrict, int);
  __extension__ unsigned long long __attribute__((__cdecl__)) strtoull(const char * __restrict__, char ** __restrict__, int);


  __extension__ long long __attribute__((__cdecl__)) atoll (const char *);
# 714 "C:/msys64/clang64/include/stdlib.h" 3
#pragma pack(pop)

# 1 "C:/msys64/clang64/include/sec_api/stdlib_s.h" 1 3








# 1 "C:/msys64/clang64/include/stdlib.h" 1 3
# 10 "C:/msys64/clang64/include/sec_api/stdlib_s.h" 2 3
# 19 "C:/msys64/clang64/include/sec_api/stdlib_s.h" 3
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _dupenv_s(char **_PBuffer,size_t *_PBufferSizeInBytes,const char *_VarName);




  __attribute__ ((__dllimport__)) void * __attribute__((__cdecl__)) bsearch_s(const void *_Key,const void *_Base,rsize_t _NumOfElements,rsize_t _SizeOfElements,int (__attribute__((__cdecl__)) * _PtFuncCompare)(void *, const void *, const void *), void *_Context);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) getenv_s(size_t *_ReturnSize,char *_DstBuf,rsize_t _DstSize,const char *_VarName);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _itoa_s(int _Value,char *_DstBuf,size_t _Size,int _Radix);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _i64toa_s(long long _Val,char *_DstBuf,size_t _Size,int _Radix);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ui64toa_s(unsigned long long _Val,char *_DstBuf,size_t _Size,int _Radix);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ltoa_s(long _Val,char *_DstBuf,size_t _Size,int _Radix);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) mbstowcs_s(size_t *_PtNumOfCharConverted,wchar_t *_DstBuf,size_t _SizeInWords,const char *_SrcBuf,size_t _MaxCount);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _mbstowcs_s_l(size_t *_PtNumOfCharConverted,wchar_t *_DstBuf,size_t _SizeInWords,const char *_SrcBuf,size_t _MaxCount,_locale_t _Locale);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ultoa_s(unsigned long _Val,char *_DstBuf,size_t _Size,int _Radix);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) wctomb_s(int *_SizeConverted,char *_MbCh,rsize_t _SizeInBytes,wchar_t _WCh);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wctomb_s_l(int *_SizeConverted,char *_MbCh,size_t _SizeInBytes,wchar_t _WCh,_locale_t _Locale);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) wcstombs_s(size_t *_PtNumOfCharConverted,char *_Dst,size_t _DstSizeInBytes,const wchar_t *_Src,size_t _MaxCountInBytes);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcstombs_s_l(size_t *_PtNumOfCharConverted,char *_Dst,size_t _DstSizeInBytes,const wchar_t *_Src,size_t _MaxCountInBytes,_locale_t _Locale);



  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ecvt_s(char *_DstBuf,size_t _Size,double _Val,int _NumOfDights,int *_PtDec,int *_PtSign);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _fcvt_s(char *_DstBuf,size_t _Size,double _Val,int _NumOfDec,int *_PtDec,int *_PtSign);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _gcvt_s(char *_DstBuf,size_t _Size,double _Val,int _NumOfDigits);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _makepath_s(char *_PathResult,size_t _Size,const char *_Drive,const char *_Dir,const char *_Filename,const char *_Ext);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _putenv_s(const char *_Name,const char *_Value);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _searchenv_s(const char *_Filename,const char *_EnvVar,char *_ResultPath,size_t _SizeInBytes);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _splitpath_s(const char *_FullPath,char *_Drive,size_t _DriveSize,char *_Dir,size_t _DirSize,char *_Filename,size_t _FilenameSize,char *_Ext,size_t _ExtSize);




  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) qsort_s(void *_Base,size_t _NumOfElements,size_t _SizeOfElements,int (__attribute__((__cdecl__)) *_PtFuncCompare)(void *,const void *,const void *),void *_Context);
# 717 "C:/msys64/clang64/include/stdlib.h" 2 3
# 1 "C:/msys64/clang64/include/malloc.h" 1 3
# 11 "C:/msys64/clang64/include/malloc.h" 3
#pragma pack(push,_CRT_PACKING)
# 52 "C:/msys64/clang64/include/malloc.h" 3
  typedef struct _heapinfo {
    int *_pentry;
    size_t _size;
    int _useflag;
  } _HEAPINFO;



  __attribute__ ((__dllimport__)) unsigned int *__attribute__((__cdecl__)) __p__amblksiz(void);
# 129 "C:/msys64/clang64/include/malloc.h" 3
void * __mingw_aligned_malloc (size_t _Size, size_t _Alignment);
void __mingw_aligned_free (void *_Memory);
void * __mingw_aligned_offset_realloc (void *_Memory, size_t _Size, size_t _Alignment, size_t _Offset);
void * __mingw_aligned_offset_malloc (size_t, size_t, size_t);
void * __mingw_aligned_realloc (void *_Memory, size_t _Size, size_t _Offset);
size_t __mingw_aligned_msize (void *memblock, size_t alignment, size_t offset);



# 1 "C:/msys64/clang64/lib/clang/21/include/mm_malloc.h" 1 3
# 13 "C:/msys64/clang64/lib/clang/21/include/mm_malloc.h" 3
# 1 "C:/msys64/clang64/include/stdlib.h" 1 3
# 14 "C:/msys64/clang64/lib/clang/21/include/mm_malloc.h" 2 3


# 1 "C:/msys64/clang64/include/malloc.h" 1 3
# 17 "C:/msys64/clang64/lib/clang/21/include/mm_malloc.h" 2 3
# 30 "C:/msys64/clang64/lib/clang/21/include/mm_malloc.h" 3
static __inline__ void *__attribute__((__always_inline__, __nodebug__,
                                       __malloc__, __alloc_size__(1),
                                       __alloc_align__(2)))
_mm_malloc(size_t __size, size_t __align) {
  if (__align == 1) {
    return malloc(__size);
  }

  if (!(__align & (__align - 1)) && __align < sizeof(void *))
    __align = sizeof(void *);

  void *__mallocedMemory;

  __mallocedMemory = __mingw_aligned_malloc(__size, __align);







  return __mallocedMemory;
}

static __inline__ void __attribute__((__always_inline__, __nodebug__))
_mm_free(void *__p)
{

  __mingw_aligned_free(__p);





}
# 139 "C:/msys64/clang64/include/malloc.h" 2 3





  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _resetstkoflw (void);

  __attribute__ ((__dllimport__)) unsigned long __attribute__((__cdecl__)) _set_malloc_crt_max_wait(unsigned long _NewValue);







  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _expand(void *_Memory,size_t _NewSize);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _msize(void *_Memory);
# 167 "C:/msys64/clang64/include/malloc.h" 3
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _get_sbh_threshold(void);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _set_sbh_threshold(size_t _NewValue);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _set_amblksiz(size_t _Value);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _get_amblksiz(size_t *_Value);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _heapadd(void *_Memory,size_t _Size);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _heapchk(void);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _heapmin(void);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _heapset(unsigned int _Fill);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _heapwalk(_HEAPINFO *_EntryInfo);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _heapused(size_t *_Used,size_t *_Commit);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _get_heap_handle(void);
# 190 "C:/msys64/clang64/include/malloc.h" 3
  static __inline void *_MarkAllocaS(void *_Ptr,unsigned int _Marker) {
    if(_Ptr) {
      *((unsigned int*)_Ptr) = _Marker;
      _Ptr = (char*)_Ptr + 16;
    }
    return _Ptr;
  }
# 218 "C:/msys64/clang64/include/malloc.h" 3
  static __inline void __attribute__((__cdecl__)) _freea(void *_Memory) {
    unsigned int _Marker;
    if(_Memory) {
      _Memory = (char*)_Memory - 16;
      _Marker = *(unsigned int *)_Memory;
      if(_Marker==0xDDDD) {
 free(_Memory);
      }





    }
  }
# 264 "C:/msys64/clang64/include/malloc.h" 3
#pragma pack(pop)
# 718 "C:/msys64/clang64/include/stdlib.h" 2 3
# 10 "src/filli.h" 2
# 1 "C:/msys64/clang64/lib/clang/21/include/stddef.h" 1 3
# 84 "C:/msys64/clang64/lib/clang/21/include/stddef.h" 3
# 1 "C:/msys64/clang64/lib/clang/21/include/__stddef_header_macro.h" 1 3
# 85 "C:/msys64/clang64/lib/clang/21/include/stddef.h" 2 3



# 1 "C:/msys64/clang64/lib/clang/21/include/__stddef_ptrdiff_t.h" 1 3
# 18 "C:/msys64/clang64/lib/clang/21/include/__stddef_ptrdiff_t.h" 3
typedef long long int ptrdiff_t;
# 89 "C:/msys64/clang64/lib/clang/21/include/stddef.h" 2 3




# 1 "C:/msys64/clang64/lib/clang/21/include/__stddef_size_t.h" 1 3
# 18 "C:/msys64/clang64/lib/clang/21/include/__stddef_size_t.h" 3
typedef long long unsigned int size_t;
# 94 "C:/msys64/clang64/lib/clang/21/include/stddef.h" 2 3
# 103 "C:/msys64/clang64/lib/clang/21/include/stddef.h" 3
# 1 "C:/msys64/clang64/lib/clang/21/include/__stddef_wchar_t.h" 1 3
# 104 "C:/msys64/clang64/lib/clang/21/include/stddef.h" 2 3




# 1 "C:/msys64/clang64/lib/clang/21/include/__stddef_null.h" 1 3
# 109 "C:/msys64/clang64/lib/clang/21/include/stddef.h" 2 3
# 128 "C:/msys64/clang64/lib/clang/21/include/stddef.h" 3
# 1 "C:/msys64/clang64/lib/clang/21/include/__stddef_offsetof.h" 1 3
# 129 "C:/msys64/clang64/lib/clang/21/include/stddef.h" 2 3
# 11 "src/filli.h" 2
# 1 "C:/msys64/clang64/include/string.h" 1 3
# 45 "C:/msys64/clang64/include/string.h" 3
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _memccpy(void *_Dst,const void *_Src,int _Val,size_t _MaxCount);
                void *__attribute__((__cdecl__)) memchr(const void *_Buf ,int _Val,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _memicmp(const void *_Buf1,const void *_Buf2,size_t _Size);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _memicmp_l(const void *_Buf1,const void *_Buf2,size_t _Size,_locale_t _Locale);
  int __attribute__((__cdecl__)) memcmp(const void *_Buf1,const void *_Buf2,size_t _Size);
  void * __attribute__((__cdecl__)) memcpy(void * __restrict__ _Dst,const void * __restrict__ _Src,size_t _Size) ;
  __attribute__((dllimport)) errno_t __attribute__((__cdecl__)) memcpy_s (void *_dest,size_t _numberOfElements,const void *_src,size_t _count);
  void * __attribute__((__cdecl__)) mempcpy (void *_Dst, const void *_Src, size_t _Size);
  void * __attribute__((__cdecl__)) memset(void *_Dst,int _Val,size_t _Size);

  void * __attribute__((__cdecl__)) memccpy(void *_Dst,const void *_Src,int _Val,size_t _Size) ;
  int __attribute__((__cdecl__)) memicmp(const void *_Buf1,const void *_Buf2,size_t _Size) ;


  char * __attribute__((__cdecl__)) _strset(char *_Str,int _Val) ;
  char * __attribute__((__cdecl__)) _strset_l(char *_Str,int _Val,_locale_t _Locale) ;
  char * __attribute__((__cdecl__)) strcpy(char * __restrict__ _Dest,const char * __restrict__ _Source);
  char * __attribute__((__cdecl__)) strcat(char * __restrict__ _Dest,const char * __restrict__ _Source);
  int __attribute__((__cdecl__)) strcmp(const char *_Str1,const char *_Str2);
  size_t __attribute__((__cdecl__)) strlen(const char *_Str);
  size_t __attribute__((__cdecl__)) strnlen(const char *_Str,size_t _MaxCount);
  void *__attribute__((__cdecl__)) memmove(void *_Dst,const void *_Src,size_t _Size) ;




  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strdup(const char *_Src);



                char *__attribute__((__cdecl__)) strchr(const char *_Str,int _Val);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _stricmp(const char *_Str1,const char *_Str2);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _strcmpi(const char *_Str1,const char *_Str2);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _stricmp_l(const char *_Str1,const char *_Str2,_locale_t _Locale);
  int __attribute__((__cdecl__)) strcoll(const char *_Str1,const char *_Str2);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _strcoll_l(const char *_Str1,const char *_Str2,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _stricoll(const char *_Str1,const char *_Str2);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _stricoll_l(const char *_Str1,const char *_Str2,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _strncoll (const char *_Str1,const char *_Str2,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _strncoll_l(const char *_Str1,const char *_Str2,size_t _MaxCount,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _strnicoll (const char *_Str1,const char *_Str2,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _strnicoll_l(const char *_Str1,const char *_Str2,size_t _MaxCount,_locale_t _Locale);
  size_t __attribute__((__cdecl__)) strcspn(const char *_Str,const char *_Control);
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strerror(const char *_ErrMsg) ;
  char *__attribute__((__cdecl__)) strerror(int) ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strlwr(char *_String) ;
  char *strlwr_l(char *_String,_locale_t _Locale) ;
  char *__attribute__((__cdecl__)) strncat(char * __restrict__ _Dest,const char * __restrict__ _Source,size_t _Count) ;
  int __attribute__((__cdecl__)) strncmp(const char *_Str1,const char *_Str2,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _strnicmp(const char *_Str1,const char *_Str2,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _strnicmp_l(const char *_Str1,const char *_Str2,size_t _MaxCount,_locale_t _Locale);
  char *strncpy(char * __restrict__ _Dest,const char * __restrict__ _Source,size_t _Count) ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strnset(char *_Str,int _Val,size_t _MaxCount) ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strnset_l(char *str,int c,size_t count,_locale_t _Locale) ;
                char *__attribute__((__cdecl__)) strpbrk(const char *_Str,const char *_Control);
                char *__attribute__((__cdecl__)) strrchr(const char *_Str,int _Ch);
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strrev(char *_Str);
  size_t __attribute__((__cdecl__)) strspn(const char *_Str,const char *_Control);
                char *__attribute__((__cdecl__)) strstr(const char *_Str,const char *_SubStr);
  char *__attribute__((__cdecl__)) strtok(char * __restrict__ _Str,const char * __restrict__ _Delim) ;


  char *strtok_r(char * __restrict__ _Str, const char * __restrict__ _Delim, char ** __restrict__ __last);

  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strupr(char *_String) ;
  __attribute__ ((__dllimport__)) char *_strupr_l(char *_String,_locale_t _Locale) ;
  size_t __attribute__((__cdecl__)) strxfrm(char * __restrict__ _Dst,const char * __restrict__ _Src,size_t _MaxCount);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _strxfrm_l(char * __restrict__ _Dst,const char * __restrict__ _Src,size_t _MaxCount,_locale_t _Locale);






  char *__attribute__((__cdecl__)) strdup(const char *_Src) ;



  int __attribute__((__cdecl__)) strcmpi(const char *_Str1,const char *_Str2) ;
  int __attribute__((__cdecl__)) stricmp(const char *_Str1,const char *_Str2) ;
  char *__attribute__((__cdecl__)) strlwr(char *_Str) ;
  int __attribute__((__cdecl__)) strnicmp(const char *_Str1,const char *_Str,size_t _MaxCount) ;
  int __attribute__((__cdecl__)) strncasecmp (const char *, const char *, size_t);
  int __attribute__((__cdecl__)) strcasecmp (const char *, const char *);







  char *__attribute__((__cdecl__)) strnset(char *_Str,int _Val,size_t _MaxCount) ;
  char *__attribute__((__cdecl__)) strrev(char *_Str) ;
  char *__attribute__((__cdecl__)) strset(char *_Str,int _Val) ;
  char *__attribute__((__cdecl__)) strupr(char *_Str) ;
# 149 "C:/msys64/clang64/include/string.h" 3
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcsdup(const wchar_t *_Str);



  wchar_t *__attribute__((__cdecl__)) wcscat(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Source) ;
                wchar_t *__attribute__((__cdecl__)) wcschr(const wchar_t *_Str,wchar_t _Ch);
  int __attribute__((__cdecl__)) wcscmp(const wchar_t *_Str1,const wchar_t *_Str2);
  wchar_t *__attribute__((__cdecl__)) wcscpy(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Source) ;
  size_t __attribute__((__cdecl__)) wcscspn(const wchar_t *_Str,const wchar_t *_Control);
  size_t __attribute__((__cdecl__)) wcslen(const wchar_t *_Str);
  size_t __attribute__((__cdecl__)) wcsnlen(const wchar_t *_Src,size_t _MaxCount);
  wchar_t *wcsncat(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Source,size_t _Count) ;
  int __attribute__((__cdecl__)) wcsncmp(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount);
  wchar_t *wcsncpy(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Source,size_t _Count) ;
  wchar_t *__attribute__((__cdecl__)) _wcsncpy_l(wchar_t * __restrict__ _Dest,const wchar_t * __restrict__ _Source,size_t _Count,_locale_t _Locale) ;
                wchar_t *__attribute__((__cdecl__)) wcspbrk(const wchar_t *_Str,const wchar_t *_Control);
                wchar_t *__attribute__((__cdecl__)) wcsrchr(const wchar_t *_Str,wchar_t _Ch);
  size_t __attribute__((__cdecl__)) wcsspn(const wchar_t *_Str,const wchar_t *_Control);
                wchar_t *__attribute__((__cdecl__)) wcsstr(const wchar_t *_Str,const wchar_t *_SubStr);
  wchar_t *__attribute__((__cdecl__)) wcstok(wchar_t * __restrict__ _Str,const wchar_t * __restrict__ _Delim,wchar_t ** __restrict__ _Ptr) ;
  wchar_t *__attribute__((__cdecl__)) _wcstok(wchar_t * __restrict__ _Str,const wchar_t * __restrict__ _Delim) ;






  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcserror(int _ErrNum) ;
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) __wcserror(const wchar_t *_Str) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsicmp(const wchar_t *_Str1,const wchar_t *_Str2);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsicmp_l(const wchar_t *_Str1,const wchar_t *_Str2,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsnicmp(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsnicmp_l(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount,_locale_t _Locale);
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcsnset(wchar_t *_Str,wchar_t _Val,size_t _MaxCount) ;
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcsrev(wchar_t *_Str);
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcsset(wchar_t *_Str,wchar_t _Val) ;
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcslwr(wchar_t *_String) ;
  __attribute__ ((__dllimport__)) wchar_t *_wcslwr_l(wchar_t *_String,_locale_t _Locale) ;
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcsupr(wchar_t *_String) ;
  __attribute__ ((__dllimport__)) wchar_t *_wcsupr_l(wchar_t *_String,_locale_t _Locale) ;
  size_t __attribute__((__cdecl__)) wcsxfrm(wchar_t * __restrict__ _Dst,const wchar_t * __restrict__ _Src,size_t _MaxCount);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _wcsxfrm_l(wchar_t * __restrict__ _Dst,const wchar_t * __restrict__ _Src,size_t _MaxCount,_locale_t _Locale);
  int __attribute__((__cdecl__)) wcscoll(const wchar_t *_Str1,const wchar_t *_Str2);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcscoll_l(const wchar_t *_Str1,const wchar_t *_Str2,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsicoll(const wchar_t *_Str1,const wchar_t *_Str2);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsicoll_l(const wchar_t *_Str1,const wchar_t *_Str2,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsncoll(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsncoll_l(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsnicoll(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wcsnicoll_l(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount,_locale_t _Locale);






  wchar_t *__attribute__((__cdecl__)) wcsdup(const wchar_t *_Str) ;




  int __attribute__((__cdecl__)) wcsicmp(const wchar_t *_Str1,const wchar_t *_Str2) ;
  int __attribute__((__cdecl__)) wcsnicmp(const wchar_t *_Str1,const wchar_t *_Str2,size_t _MaxCount) ;
  wchar_t *__attribute__((__cdecl__)) wcsnset(wchar_t *_Str,wchar_t _Val,size_t _MaxCount) ;
  wchar_t *__attribute__((__cdecl__)) wcsrev(wchar_t *_Str) ;
  wchar_t *__attribute__((__cdecl__)) wcsset(wchar_t *_Str,wchar_t _Val) ;
  wchar_t *__attribute__((__cdecl__)) wcslwr(wchar_t *_Str) ;
  wchar_t *__attribute__((__cdecl__)) wcsupr(wchar_t *_Str) ;
  int __attribute__((__cdecl__)) wcsicoll(const wchar_t *_Str1,const wchar_t *_Str2) ;







# 1 "C:/msys64/clang64/include/sec_api/string_s.h" 1 3








# 1 "C:/msys64/clang64/include/string.h" 1 3
# 10 "C:/msys64/clang64/include/sec_api/string_s.h" 2 3
# 24 "C:/msys64/clang64/include/sec_api/string_s.h" 3
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _strset_s(char *_Dst,size_t _DstSize,int _Value);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _strerror_s(char *_Buf,size_t _SizeInBytes,const char *_ErrMsg);

  __attribute__((dllimport)) errno_t __attribute__((__cdecl__)) strerror_s(char *_Buf,size_t _SizeInBytes,int _ErrNum);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _strlwr_s(char *_Str,size_t _Size);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _strlwr_s_l(char *_Str,size_t _Size,_locale_t _Locale);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _strnset_s(char *_Str,size_t _Size,int _Val,size_t _MaxCount);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _strupr_s(char *_Str,size_t _Size);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _strupr_s_l(char *_Str,size_t _Size,_locale_t _Locale);


  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) strncat_s(char *_Dst,size_t _DstSizeInChars,const char *_Src,size_t _MaxCount);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _strncat_s_l(char *_Dst,size_t _DstSizeInChars,const char *_Src,size_t _MaxCount,_locale_t _Locale);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) strcpy_s(char *_Dst, rsize_t _SizeInBytes, const char *_Src);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) strncpy_s(char *_Dst, size_t _DstSizeInChars, const char *_Src, size_t _MaxCount);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _strncpy_s_l(char *_Dst, size_t _DstSizeInChars, const char *_Src, size_t _MaxCount, _locale_t _Locale);

  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) strtok_s(char *_Str,const char *_Delim,char **_Context);
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _strtok_s_l(char *_Str,const char *_Delim,char **_Context,_locale_t _Locale);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) strcat_s(char *_Dst, rsize_t _SizeInBytes, const char * _Src);


  extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) size_t __attribute__((__cdecl__)) strnlen_s(const char * _src, size_t _count) {
    return _src ? strnlen(_src, _count) : 0;
  }

  __attribute__((dllimport)) errno_t __attribute__((__cdecl__)) memmove_s(void *_dest,size_t _numberOfElements,const void *_src,size_t _count);


  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) wcstok_s(wchar_t *_Str,const wchar_t *_Delim,wchar_t **_Context);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcserror_s(wchar_t *_Buf,size_t _SizeInWords,int _ErrNum);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) __wcserror_s(wchar_t *_Buffer,size_t _SizeInWords,const wchar_t *_ErrMsg);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsnset_s(wchar_t *_Dst,size_t _DstSizeInWords,wchar_t _Val,size_t _MaxCount);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsset_s(wchar_t *_Str,size_t _SizeInWords,wchar_t _Val);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcslwr_s(wchar_t *_Str,size_t _SizeInWords);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcslwr_s_l(wchar_t *_Str,size_t _SizeInWords,_locale_t _Locale);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsupr_s(wchar_t *_Str,size_t _Size);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsupr_s_l(wchar_t *_Str,size_t _Size,_locale_t _Locale);


  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) wcscpy_s(wchar_t *_Dst, rsize_t _SizeInWords, const wchar_t *_Src);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) wcscat_s(wchar_t * _Dst, rsize_t _SizeInWords, const wchar_t *_Src);


  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) wcsncat_s(wchar_t *_Dst,size_t _DstSizeInChars,const wchar_t *_Src,size_t _MaxCount);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsncat_s_l(wchar_t *_Dst,size_t _DstSizeInChars,const wchar_t *_Src,size_t _MaxCount,_locale_t _Locale);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) wcsncpy_s(wchar_t *_Dst, size_t _DstSizeInChars, const wchar_t *_Src, size_t _MaxCount);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsncpy_s_l(wchar_t *_Dst, size_t _DstSizeInChars, const wchar_t *_Src, size_t _MaxCount, _locale_t _Locale);

  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wcstok_s_l(wchar_t *_Str,const wchar_t *_Delim,wchar_t **_Context,_locale_t _Locale);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsset_s_l(wchar_t *_Str,size_t _SizeInChars,wchar_t _Val,_locale_t _Locale);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcsnset_s_l(wchar_t *_Str,size_t _SizeInChars,wchar_t _Val, size_t _Count,_locale_t _Locale);


  extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) size_t __attribute__((__cdecl__)) wcsnlen_s(const wchar_t * _src, size_t _count) {
    return _src ? wcsnlen(_src, _count) : 0;
  }
# 226 "C:/msys64/clang64/include/string.h" 2 3
# 12 "src/filli.h" 2
# 49 "src/filli.h"
char * stringdupn(const char * s, size_t len)
{
    char * s2 = (char *)malloc(len+1);
    memset(s2, 0, len+1);

    size_t i = 0;
    while (*s && i < len) s2[i++] = *(s++);
    return s2;
}
char * stringdup(const char * s) { return stringdupn(s, strlen(s)); }

void prints(const char * s) { fputs(s, (__acrt_iob_func(1))); }
void eprints(const char * s) { fputs(s, (__acrt_iob_func(2))); }
void printu16hex(uint16_t x)
{
    char c[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char s[5] = { c[(x>>12)&15], c[(x>>8)&15], c[(x>>4)&15], c[x&15], 0 };
    prints(s);
}
void printsn(const char * s, size_t len) { char * s2 = stringdupn(s, len); prints(s2); free(s2); }

double badstrtod(const char * s)
{
    if ((s[0]&~32) == 'N' && (s[1]&~32) == 'A' && (s[0]&~32) == 'N') return 0.0/0.0;

    double sign = 1.0;
    if (*s == '-') { sign = -1.0; s += 1; }
    if (!s[0]) return 0.0 * sign;
    if ((s[0]&~32) == 'I' && (s[1]&~32) == 'N' && (s[0]&~32) == 'F') return sign/0.0;

    double ret = 0.0;
    while (*s != 0 && *s != '.' && *s >= '0' && *s <= '9') { ret = ret*10.0 + (*(s++) - '0'); }
    if (*(s++) != '.') return ret * sign;
    double f2 = 0.1;
    while (*s != 0 && *s >= '0' && *s <= '9') { ret += (*(s++) - '0') * f2; f2 *= 0.1; }

    return ret * sign;
}

const char * baddtostr(double f)
{
    if (f != f) return "nan";
    if (f != 0.0 && f+f == f) return "inf";
    if (f != 0.0 && f-f == f) return "-inf";

    char buf[50] = {};
    size_t i = 0;

    uint64_t pun;
    memcpy(&pun, &f, 8);
    if (pun & 0x8000000000000000) { buf[i++] = '-'; pun ^= 0x8000000000000000; }
    memcpy(&f, &pun, 8);

    size_t mag = 0; while (f != 0.0 && f < 1000000000.0 / (i ? 10.0 : 1.0)) { f *= 10.0; mag++; }

    uint64_t fi2 = f;
    uint8_t d = i;
    while (fi2) { d++; fi2 /= 10; }
    if (d == i) d += 1;
    if (f == 0.0) { mag = 9 - i; d = 10; }

    fi2 = f;
    for (size_t j = d; j > i;) { buf[--j] = '0' + (fi2 % 10); fi2 /= 10; }
    if (d >= mag)
    {
        for (size_t j = d; j > d - mag; j--) buf[j] = buf[j - 1];
        buf[d-mag] = '.';
    }

    return stringdup(buf);
}


const char * filli_err = 0;
# 143 "src/filli.h"
static inline void * zalloc(size_t s) { char * r = (char *)malloc(s); if (!r) ( prints("Assert:\n" "\"Out of memory\"" "\nat " "143" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ); memset(r, 0, s); return r; }

static inline uint32_t fi_mem_read_u32(void * from) { uint32_t n; memcpy(&n, from, 4); return n; }
static inline double fi_mem_read_f64(void * from) { double f; memcpy(&f, from, 8); return f; }



typedef struct _IdEntry { const char * where; uint16_t len; } IdEntry;

int16_t insert_or_lookup_id(const char * text, uint16_t len)
{

    static IdEntry ids[32000] = {};
    for (int16_t j = 1; j <= 32000; j++)
    {
        if (ids[j].len == 0) ids[j] = (IdEntry) { stringdupn(text, len), len };
        if (ids[j].len == len && strncmp(ids[j].where, text, len) == 0) return -j;
    }
    { if (!filli_err) filli_err = "\"Out of IDs\""; return 0; };
}

typedef struct _Token { uint32_t i; uint16_t len; int16_t kind; } Token;







int token_is(const char * source, Token * tokens, size_t count, size_t i, const char * text)
{
    if (i >= count) return 0;
    size_t len = strlen(text);
    if (tokens[i].len != len) return 0;
    return strncmp(source + tokens[i].i, text, len) == 0;
}

Token mk_token(uint32_t i, uint16_t len, int16_t kind) { Token t = {i, len, kind}; return t; }

void lex_init(void)
{

    const char * keywords[] = { "if", "else", "elif", "func", "while", "for", "break", "continue", "return", "let", "end", "lambda", "yield"};
    for (size_t j = 0; j < sizeof(keywords) / sizeof(keywords[0]); j++) insert_or_lookup_id(keywords[j], strlen(keywords[j]));
# 201 "src/filli.h"
}
int lex_ident_offset = 13;

Token * tokenize(const char * src, size_t * count)
{
    int newline_is_token = 1;

    const char * longpunc[] = { "==", "!=", ">=", "<=", "+=", "-=", "*=", "/=", "{}" };

    size_t len = strlen(src);

    Token * ret = (Token *)zalloc(sizeof(Token) * len);
    size_t t = 0;

    for (size_t i = 0; i < len; )
    {

        if (src[i] == '#') { while (src[i] != '\0' && src[i] != '\n') { i++; } continue; }
        if (src[i] == ' ' || src[i] == '\t' || src[i] == '\r') { i++; continue; }

        if (src[i] == '\n')
        {
            if (newline_is_token && t > 0 && token_is(src, ret, t, t-1, "\\")) { t -= 1; i++; }
            else if (newline_is_token) ret[t++] = mk_token(i++, 1, 3);
        }

        else if ((src[i] >= '0' && src[i] <= '9') || (src[i] == '-' && src[i+1] >= '0' && src[i+1] <= '9'))
        {
            size_t start_i = i;
            if (src[i] == '-') i += 1;
            uint8_t dok = 1;
            while ((src[i] >= '0' && src[i] <= '9') || (dok && src[i] == '.')) dok &= src[i++] != '.';
            ret[t++] = mk_token(start_i, i-start_i, 0);
        }

        else if ((src[i] >= 'a' && src[i] <= 'z') || (src[i] >= 'A' && src[i] <= 'Z') || src[i] == '_')
        {
            size_t start_i = i++;
            while ((src[i] >= 'a' && src[i] <= 'z') || (src[i] >= 'A' && src[i] <= 'Z')
                   || src[i] == '_' || (src[i] >= '0' && src[i] <= '9')) i++;

            ret[t++] = mk_token(start_i, i - start_i, insert_or_lookup_id(src + start_i, i - start_i));
        }

        else if (src[i] == '\'' || src[i] == '"')
        {
            size_t start_i = i++;
            while (src[i] != src[start_i] && src[i] != 0) i += (src[i] == '\\') ? 2 : 1;
            if (src[i] != 0) i += 1;
            ret[t++] = mk_token(start_i, i-start_i, 1);
        }
        else
        {

            for (size_t j = 0; j < sizeof(longpunc) / sizeof(longpunc[0]); j++)
            {
                if (strncmp(longpunc[j], src+i, strlen(longpunc[j])) == 0)
                {
                    ret[t++] = mk_token(i, strlen(longpunc[j]), 2);
                    i += strlen(longpunc[j]);
                    goto fullcontinue;
                }
            }

            ret[t++] = mk_token(i++, 1, 2);

            fullcontinue: {}
        }
    }

    *count = t;
    return ret;
}

enum { INST_INVALID = 0x000,

    INST_RETURN_VOID = 0x100,

    INST_RETURN_VAL = 0x210, INST_YIELD, PUSH_NULL, PUSH_DICT_EMPTY,
    INST_SET_LOC, INST_SET_LOC_ADD, INST_SET_LOC_SUB, INST_SET_LOC_MUL, INST_SET_LOC_DIV,
    INST_INDEX, INST_INDEX_LOC, INST_CMP_EQ, INST_CMP_NE, INST_CMP_GT, INST_CMP_LT, INST_CMP_GE, INST_CMP_LE,
    INST_ADD, INST_SUB, INST_MUL, INST_DIV, INST_CMP_AND, INST_CMP_OR, INST_BITAND, INST_BITOR, INST_BITXOR, INST_INTMOD,

    PUSH_FUNCNAME = 0x340, INST_FUNCCALL_REF, PUSH_STRING, INST_ARRAY_LITERAL, PUSH_INT,
    PUSH_LOCAL, PUSH_GLOBAL, PUSH_CAP, INST_SET, INST_SET_GLOBAL, INST_SET_CAP,
    INST_SET_ADD, INST_SET_GLOBAL_ADD, INST_SET_CAP_ADD, INST_SET_SUB, INST_SET_GLOBAL_SUB, INST_SET_CAP_SUB,
    INST_SET_MUL, INST_SET_GLOBAL_MUL, INST_SET_CAP_MUL, INST_SET_DIV, INST_SET_GLOBAL_DIV, INST_SET_CAP_DIV,

    INST_JMP, INST_FUNCDEF, INST_INDEX_INT, INST_INDEX_LOC_INT,

    INST_JMP_IF_FALSE = 0x470, INST_JMP_IF_TRUE, INST_FUNCCALL,




    INST_FOREND = 0x580,

    PUSH_NUM = 0x6a0, INST_LAMBDA, INST_FORSTART
};



typedef struct _Program { uint16_t * code; uint32_t capacity; uint32_t i; } Program;
Program prog = {0, 100000, 0};
void init_program() { prog.code = (uint16_t *)zalloc(sizeof(uint16_t) * prog.capacity); }

void prog_write(uint16_t a) { if (prog.i < 100000) prog.code[prog.i++] = a; else { if (!filli_err) filli_err = "\"Compiled program longer than PROGRAM_MAXLEN\""; return ; }; }
void prog_write2(uint16_t a, uint16_t b) { prog_write(a); prog_write(b); }
void prog_write3(uint16_t a, uint16_t b, uint16_t c) { prog_write2(a, b); prog_write(c); }
void prog_write4(uint16_t a, uint16_t b, uint16_t c, uint16_t d) { prog_write3(a, b, c); prog_write(d); }
void prog_write5(uint16_t a, uint16_t b, uint16_t c, uint16_t d, uint16_t e) { prog_write3(a, b, c); prog_write2(d, e); }
void prog_write6(uint16_t a, uint16_t b, uint16_t c, uint16_t d, uint16_t e, uint16_t f) { prog_write3(a, b, c); prog_write3(d, e, f); }

int tokenop_bindlevel(const char * source, Token * tokens, size_t count, size_t i)
{
    const char * ops[] = { "or", "\1", "and", "\1", "==", "\3", "!=", "\3", ">=", "\3", "<=", "\3", ">", "\3", "<", "\3",
                           "+", "\4", "-", "\4", "^", "\4", "*", "\5", "/", "\5", "%", "\5", "&", "\5", "|", "\5", "[", "\111", "(", "\111" };
    for (size_t j = 0; i < count && j < sizeof(ops) / sizeof(ops[0]); j += 2)
        if (token_is(source, tokens, count, i, ops[j])) return ops[j + 1][0];
    return -1;
}

struct _Value;

typedef struct _Funcdef {
    uint8_t exists, intrinsic, poolsafe;
    uint16_t argcount, id;
    uint16_t * args;
    uint16_t cap_count;
    uint32_t loc;
    int16_t * caps;
    struct _Value ** cap_data;
    uint16_t vars_len;
} Funcdef;

typedef struct _CompilerData {
    const char * compiled_strings[1<<16];
    uint16_t globals_reg[32000];
    Funcdef funcs_reg[32000 + 4096];

    uint32_t lambda_id, compiled_string_i, locals_reg_i, globals_n, locals_n, caps_reg_i, for_loop_index, func_depth, last_idx;

    uint16_t * locals_reg, * caps_reg, * locals_reg_stack[1024], * caps_reg_stack[1024];

    uint32_t loop_nesting, loop_cont_i, loop_break_i, loop_conts[1024], loop_breaks[1024], stackpos[1024];
} CompilerState;

CompilerState * cs;
void compiler_state_init(void)
{
    cs = (CompilerState *)zalloc(sizeof(CompilerState));
    *cs = (CompilerState) { {}, {}, {}, 32000, 0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, {}, {}, 0, 0, 0, {}, {}, {} };
}







size_t compile_value(const char * source, Token * tokens, size_t count, uint32_t i)
{
    if (i >= count) return 0;

    if (token_is(source, tokens, count, i, "{}")) return prog_write2(PUSH_DICT_EMPTY, ( (( (__builtin_expect(!(((void)"Stack exceeded limit.", cs->stackpos[cs->func_depth] < 1024)), 0)) ? ( (+0 && !filli_err) ? filli_err = "" : (!filli_err) ? filli_err = "((void)\"Stack exceeded limit.\", cs->stackpos[cs->func_depth] < 1024)" : "") : ""), (void) 0 ), (cs->stackpos[cs->func_depth] += (cs->stackpos[cs->func_depth] < 1024)) + 1024 - 1 )), 1;

    if (tokens[i].kind > 1) return 0;
    if (tokens[i].kind < 0 && tokens[i].kind >= -lex_ident_offset) return 0;

    cs->last_idx = prog.i;
    if (tokens[i].kind < 0)
    {
        uint16_t id = lex_ident_offset - tokens[i].kind;
        if (token_is(source, tokens, count, i, "true")) return prog_write3(PUSH_INT, 1, ( (( (__builtin_expect(!(((void)"Stack exceeded limit.", cs->stackpos[cs->func_depth] < 1024)), 0)) ? ( (+0 && !filli_err) ? filli_err = "" : (!filli_err) ? filli_err = "((void)\"Stack exceeded limit.\", cs->stackpos[cs->func_depth] < 1024)" : "") : ""), (void) 0 ), (cs->stackpos[cs->func_depth] += (cs->stackpos[cs->func_depth] < 1024)) + 1024 - 1 )), 1;
        else if (token_is(source, tokens, count, i, "false")) return prog_write3(PUSH_INT, 0, ( (( (__builtin_expect(!(((void)"Stack exceeded limit.", cs->stackpos[cs->func_depth] < 1024)), 0)) ? ( (+0 && !filli_err) ? filli_err = "" : (!filli_err) ? filli_err = "((void)\"Stack exceeded limit.\", cs->stackpos[cs->func_depth] < 1024)" : "") : ""), (void) 0 ), (cs->stackpos[cs->func_depth] += (cs->stackpos[cs->func_depth] < 1024)) + 1024 - 1 )), 1;
        else if (token_is(source, tokens, count, i, "null")) return prog_write2(PUSH_NULL, ( (( (__builtin_expect(!(((void)"Stack exceeded limit.", cs->stackpos[cs->func_depth] < 1024)), 0)) ? ( (+0 && !filli_err) ? filli_err = "" : (!filli_err) ? filli_err = "((void)\"Stack exceeded limit.\", cs->stackpos[cs->func_depth] < 1024)" : "") : ""), (void) 0 ), (cs->stackpos[cs->func_depth] += (cs->stackpos[cs->func_depth] < 1024)) + 1024 - 1 )), 1;
        else if (cs->func_depth > 0 && cs->locals_reg[id]) prog_write3(PUSH_LOCAL, cs->locals_reg[id] - 1, ( (( (__builtin_expect(!(((void)"Stack exceeded limit.", cs->stackpos[cs->func_depth] < 1024)), 0)) ? ( (+0 && !filli_err) ? filli_err = "" : (!filli_err) ? filli_err = "((void)\"Stack exceeded limit.\", cs->stackpos[cs->func_depth] < 1024)" : "") : ""), (void) 0 ), (cs->stackpos[cs->func_depth] += (cs->stackpos[cs->func_depth] < 1024)) + 1024 - 1 ));
        else if (cs->func_depth == 0 && cs->globals_reg[id]) prog_write3(PUSH_LOCAL, cs->globals_reg[id] - 1, ( (( (__builtin_expect(!(((void)"Stack exceeded limit.", cs->stackpos[cs->func_depth] < 1024)), 0)) ? ( (+0 && !filli_err) ? filli_err = "" : (!filli_err) ? filli_err = "((void)\"Stack exceeded limit.\", cs->stackpos[cs->func_depth] < 1024)" : "") : ""), (void) 0 ), (cs->stackpos[cs->func_depth] += (cs->stackpos[cs->func_depth] < 1024)) + 1024 - 1 ));
        else if (cs->func_depth > 0 && cs->caps_reg[id]) prog_write3(PUSH_CAP, cs->caps_reg[id] - 1, ( (( (__builtin_expect(!(((void)"Stack exceeded limit.", cs->stackpos[cs->func_depth] < 1024)), 0)) ? ( (+0 && !filli_err) ? filli_err = "" : (!filli_err) ? filli_err = "((void)\"Stack exceeded limit.\", cs->stackpos[cs->func_depth] < 1024)" : "") : ""), (void) 0 ), (cs->stackpos[cs->func_depth] += (cs->stackpos[cs->func_depth] < 1024)) + 1024 - 1 ));
        else if (cs->globals_reg[id]) prog_write3(PUSH_GLOBAL, cs->globals_reg[id] - 1, ( (( (__builtin_expect(!(((void)"Stack exceeded limit.", cs->stackpos[cs->func_depth] < 1024)), 0)) ? ( (+0 && !filli_err) ? filli_err = "" : (!filli_err) ? filli_err = "((void)\"Stack exceeded limit.\", cs->stackpos[cs->func_depth] < 1024)" : "") : ""), (void) 0 ), (cs->stackpos[cs->func_depth] += (cs->stackpos[cs->func_depth] < 1024)) + 1024 - 1 ));
        else if (cs->funcs_reg[id].exists) prog_write3(PUSH_FUNCNAME, id, ( (( (__builtin_expect(!(((void)"Stack exceeded limit.", cs->stackpos[cs->func_depth] < 1024)), 0)) ? ( (+0 && !filli_err) ? filli_err = "" : (!filli_err) ? filli_err = "((void)\"Stack exceeded limit.\", cs->stackpos[cs->func_depth] < 1024)" : "") : ""), (void) 0 ), (cs->stackpos[cs->func_depth] += (cs->stackpos[cs->func_depth] < 1024)) + 1024 - 1 ));
        else
        {
            printsn(source + tokens[i].i, tokens[i].len);
            prints("\n");
            { if (!filli_err) filli_err = "\"Unknown identifier\""; return 0; };
        }
    }
    else if (tokens[i].kind == 1)
    {
        { if (__builtin_expect(!(tokens[i].len >= 2), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Invalid string literal\""; else filli_err = "tokens[i].len >= 2"; } return 0; } };
        size_t l = tokens[i].len - 2;
        const char * sold = source + tokens[i].i + 1;
        char * s = stringdupn(sold, l);
        size_t j = 0;
        for (size_t i = 0; i < l; i++)
        {
            if (sold[i] == '\\' && sold[i+1] == '"' && ++i) s[j++] = '"';
            else if (sold[i] == '\\' && sold[i+1] == '\\' && ++i) s[j++] = '\\';
            else if (sold[i] == '\\' && sold[i+1] == 'r' && ++i) s[j++] = '\r';
            else if (sold[i] == '\\' && sold[i+1] == 'n' && ++i) s[j++] = '\n';
            else if (sold[i] == '\\' && sold[i+1] == 't' && ++i) s[j++] = '\t';
            else s[j++] = sold[i];
        }
        s[j] = 0;
        cs->compiled_strings[cs->compiled_string_i] = s;
        prog_write3(PUSH_STRING, cs->compiled_string_i++, ( (( (__builtin_expect(!(((void)"Stack exceeded limit.", cs->stackpos[cs->func_depth] < 1024)), 0)) ? ( (+0 && !filli_err) ? filli_err = "" : (!filli_err) ? filli_err = "((void)\"Stack exceeded limit.\", cs->stackpos[cs->func_depth] < 1024)" : "") : ""), (void) 0 ), (cs->stackpos[cs->func_depth] += (cs->stackpos[cs->func_depth] < 1024)) + 1024 - 1 ));
        { if (__builtin_expect(!(cs->compiled_string_i < (1<<16)), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Too many string literals used in prog.code, limit is 65k\""; else filli_err = "cs->compiled_string_i < (1<<16)"; } return 0; } };
    }
    else if (tokens[i].kind == 0)
    {
        char * s = stringdupn(source + tokens[i].i, tokens[i].len);
        double f = badstrtod(s);
        free(s);

        if (f == (uint16_t)f) prog_write3(PUSH_INT, (uint16_t)f, ( (( (__builtin_expect(!(((void)"Stack exceeded limit.", cs->stackpos[cs->func_depth] < 1024)), 0)) ? ( (+0 && !filli_err) ? filli_err = "" : (!filli_err) ? filli_err = "((void)\"Stack exceeded limit.\", cs->stackpos[cs->func_depth] < 1024)" : "") : ""), (void) 0 ), (cs->stackpos[cs->func_depth] += (cs->stackpos[cs->func_depth] < 1024)) + 1024 - 1 ));
        else { prog_write6(PUSH_NUM, 0, 0, 0, 0, ( (( (__builtin_expect(!(((void)"Stack exceeded limit.", cs->stackpos[cs->func_depth] < 1024)), 0)) ? ( (+0 && !filli_err) ? filli_err = "" : (!filli_err) ? filli_err = "((void)\"Stack exceeded limit.\", cs->stackpos[cs->func_depth] < 1024)" : "") : ""), (void) 0 ), (cs->stackpos[cs->func_depth] += (cs->stackpos[cs->func_depth] < 1024)) + 1024 - 1 )); memcpy(prog.code + (prog.i - 5), &f, 8); }
    }

    return 1;
}







size_t compile_expr(const char * source, Token * tokens, size_t count, size_t i, int right_bind_power);
size_t compile_binexpr(const char * source, Token * tokens, size_t count, size_t i);

void compile_func_start(void)
{
    cs->locals_reg_stack[cs->locals_reg_i++] = cs->locals_reg;
    cs->locals_reg = (uint16_t *)zalloc(sizeof(uint16_t) * 32000);
    cs->caps_reg_stack[cs->caps_reg_i++] = cs->caps_reg;
    cs->caps_reg = (uint16_t *)zalloc(sizeof(uint16_t) * 32000);
    { if (__builtin_expect(!(cs->caps_reg_i < 1024 && cs->locals_reg_i < 1024), 0)) { if (!filli_err) { if (+0) filli_err = ""; else filli_err = "cs->caps_reg_i < 1024 && cs->locals_reg_i < 1024"; } return ; } };
}
void compile_func_end(void)
{
    free(cs->locals_reg);
    cs->locals_reg = cs->locals_reg_stack[--cs->locals_reg_i];
    free(cs->caps_reg);
    cs->caps_reg = cs->caps_reg_stack[--cs->caps_reg_i];
}
size_t compile_lambda(const char * source, Token * tokens, size_t count, size_t i, int16_t * caps, uint16_t caps_count);

size_t compile_innerexpr(const char * source, Token * tokens, size_t count, size_t i)
{
    if (i >= count) return 0;
    if (token_is(source, tokens, count, i, "lambda"))
    {
        size_t orig_i = i++;

        if (!token_is(source, tokens, count, i++, "[")) return 0;
        int16_t * caps = (int16_t *)zalloc(sizeof(int16_t) * 255);
        uint16_t * caps_reg_next = (uint16_t *)zalloc(sizeof(uint16_t) * 32000);
        uint32_t j = 0; while (!token_is(source, tokens, count, i, "]")) { { if (__builtin_expect(!(j < 255), 0)) { if (!filli_err) { if (+0) filli_err = ""; else filli_err = "j < CAPTURELIMIT"; } return 0; } }; if (tokens[i].kind >= -lex_ident_offset) return 0; int16_t id = lex_ident_offset - tokens[i++].kind; int16_t accessor_id = 0; if (cs->func_depth > 0 && cs->locals_reg[id]) accessor_id = cs->locals_reg[id] - 1; else if (cs->func_depth > 0 && cs->caps_reg [id]) accessor_id = cs->caps_reg[id] - 1; else { printsn(source + tokens[i - 1].i, tokens[i - 1].len); prints("\n"); { if (!filli_err) filli_err = "\"Unable to capture identifier\""; return 0; }; } caps[j] = accessor_id; caps_reg_next[id] = j + 1;; j += 1; if (!(token_is(source, tokens, count, i, "]") || token_is(source, tokens, count, i, ","))) return 0; if (token_is(source, tokens, count, i, ",")) i++; } if (!token_is(source, tokens, count, i++, "]")) return 0;
# 476 "src/filli.h"
        uint32_t prev_locals_n = cs->locals_n;
        cs->locals_n = 0;
        compile_func_start();

        memcpy(cs->caps_reg, caps_reg_next, sizeof(uint16_t) * 32000);
        size_t r = compile_lambda(source, tokens, count, i, caps, j);
        { if (__builtin_expect(!(r != 0), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Lambda body is invalid\""; else filli_err = "r != 0"; } return 0; } };

        compile_func_end();
        cs->locals_n = prev_locals_n;

        return i + r - orig_i;
    }
    if (token_is(source, tokens, count, i, "("))
    {
        size_t start_prog_i = prog.i;
        size_t ret = compile_expr(source, tokens, count, i+1, 0) + 1;
        { if (__builtin_expect(!(token_is(source, tokens, count, i + ret, ")")), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Unclosed parens\""; else filli_err = "token_is(source, tokens, count, i + ret, \")\")"; } return 0; } };
        { if (__builtin_expect(!(prog.i != start_prog_i), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Paren expressions must not be empty\""; else filli_err = "prog.i != start_prog_i"; } return 0; } };
        return ret + 1;
    }
    if (token_is(source, tokens, count, i, "["))
    {
        size_t orig_i = i++;

        uint32_t j = 0; while (!token_is(source, tokens, count, i, "]")) { { if (__builtin_expect(!(j < 32000), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Too many values in array literal\""; else filli_err = "j < 32000"; } return 0; } }; size_t r = compile_expr(source, tokens, count, i, 0); if (r == 0) return 0; else i += r;; j += 1; if (!(token_is(source, tokens, count, i, "]") || token_is(source, tokens, count, i, ","))) return 0; if (token_is(source, tokens, count, i, ",")) i++; } if (!token_is(source, tokens, count, i++, "]")) return 0;



        for (size_t i = 0; i < j; i++) ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "505" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "505" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 );
        prog_write3(INST_ARRAY_LITERAL, j, ( (( (__builtin_expect(!(((void)"Stack exceeded limit.", cs->stackpos[cs->func_depth] < 1024)), 0)) ? ( (+0 && !filli_err) ? filli_err = "" : (!filli_err) ? filli_err = "((void)\"Stack exceeded limit.\", cs->stackpos[cs->func_depth] < 1024)" : "") : ""), (void) 0 ), (cs->stackpos[cs->func_depth] += (cs->stackpos[cs->func_depth] < 1024)) + 1024 - 1 ));

        return i - orig_i;
    }
    return compile_value(source, tokens, count, i++);
}

size_t compile_expr(const char * source, Token * tokens, size_t count, size_t i, int right_bind_power)
{
    size_t ret = compile_innerexpr(source, tokens, count, i);
    if (ret == 0) return 0; else i += ret;

    while (i < count && right_bind_power < tokenop_bindlevel(source, tokens, count, i))
    {
        size_t r = compile_binexpr(source, tokens, count, i);
        ret += r; if (r == 0) break; else i += r;
    }

    return ret;
}
size_t compile_binexpr(const char * source, Token * tokens, size_t count, size_t i)
{
    if (i >= count || filli_err) return 0;
    int binding_power = tokenop_bindlevel(source, tokens, count, i);
    if (binding_power < 0) return 0;


    if (token_is(source, tokens, count, i, "("))
    {
        size_t orig_i = i++;
        uint32_t j = 0; while (!token_is(source, tokens, count, i, ")")) { { if (__builtin_expect(!(j < 255), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Too many arguments to function\""; else filli_err = "j < ARGLIMIT"; } return 0; } }; size_t r = compile_expr(source, tokens, count, i, 0); if (r == 0) return 0; else i += r;; j += 1; if (!(token_is(source, tokens, count, i, ")") || token_is(source, tokens, count, i, ","))) return 0; if (token_is(source, tokens, count, i, ",")) i++; } if (!token_is(source, tokens, count, i++, ")")) return 0;



        for (size_t i = 0; i < j; i++) ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "540" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "540" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 );
        ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "541" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "541" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 );
        prog_write3(INST_FUNCCALL_REF, j, ( (( (__builtin_expect(!(((void)"Stack exceeded limit.", cs->stackpos[cs->func_depth] < 1024)), 0)) ? ( (+0 && !filli_err) ? filli_err = "" : (!filli_err) ? filli_err = "((void)\"Stack exceeded limit.\", cs->stackpos[cs->func_depth] < 1024)" : "") : ""), (void) 0 ), (cs->stackpos[cs->func_depth] += (cs->stackpos[cs->func_depth] < 1024)) + 1024 - 1 ));
        return i - orig_i;
    }

    size_t r = compile_expr(source, tokens, count, i + 1, binding_power < 50 ? binding_power : 0);
    if (r == 0) return 0;

    if (token_is(source, tokens, count, i, "["))
    {
        i += ++r;
        { if (__builtin_expect(!(token_is(source, tokens, count, i++, "]")), 0)) { if (!filli_err) { if (+0) filli_err = ""; else filli_err = "token_is(source, tokens, count, i++, \"]\")"; } return 0; } };
        ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "553" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "553" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 );
        ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "554" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "554" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 );
        uint32_t j = prog.i;
        prog_write2(INST_INDEX, ( (( (__builtin_expect(!(((void)"Stack exceeded limit.", cs->stackpos[cs->func_depth] < 1024)), 0)) ? ( (+0 && !filli_err) ? filli_err = "" : (!filli_err) ? filli_err = "((void)\"Stack exceeded limit.\", cs->stackpos[cs->func_depth] < 1024)" : "") : ""), (void) 0 ), (cs->stackpos[cs->func_depth] += (cs->stackpos[cs->func_depth] < 1024)) + 1024 - 1 ));
        if (cs->last_idx == prog.i - 5 && prog.code[cs->last_idx] == PUSH_INT)
        {
            uint16_t f = prog.code[cs->last_idx + 1];
            uint16_t sp = prog.code[prog.i - 1];
            prog.i -= 5;
            cs->last_idx = prog.i;
            prog_write3(INST_INDEX_INT, (uint16_t)f, sp);
        }
        else cs->last_idx = j;
        return r + 1;
    }

    const char * ops[] = {"-", "/", "+", "*", "%", "and", "or", "==", "!=", ">=", "<=", ">", "<", "&", "|", "^"};
    const uint16_t opcodes[] = {INST_SUB, INST_DIV, INST_ADD, INST_MUL, INST_INTMOD, INST_CMP_AND, INST_CMP_OR,
        INST_CMP_EQ, INST_CMP_NE, INST_CMP_GE, INST_CMP_LE, INST_CMP_GT, INST_CMP_LT, INST_BITAND, INST_BITOR, INST_BITXOR};

    uint16_t si = ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "573" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "573" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 ) - 1;
    if (cs->last_idx == prog.i - 2 && prog.code[cs->last_idx] == PUSH_LOCAL)
        { si = prog.code[cs->last_idx + 1]; cs->last_idx = 0; prog.i -= 2; }

    for (size_t j = 0; i < count && j < sizeof(ops) / sizeof(ops[0]); j++)
        if (token_is(source, tokens, count, i, ops[j])) { prog_write2(opcodes[j], si); return r + 1; }

    printsn(source + tokens[i].i, tokens[i].len);
    prints("\n");
    { if (!filli_err) filli_err = "\"Unknown infix operator\""; return 0; };
}


size_t compile_statementlist(const char * source, Token * tokens, size_t count, size_t i);

size_t compile_statement(const char * source, Token * tokens, size_t count, size_t i)
{
    { if (filli_err) return 0; }
    if (i >= count) return 0;
    size_t orig_i = i;
    if (tokens[i].kind == -1)
    {
        size_t r = compile_expr(source, tokens, count, i + 1, 0);
        i += r + 1;
        { if (__builtin_expect(!(token_is(source, tokens, count, i++, ":") && r != 0), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Conditions must not be empty\""; else filli_err = "token_is(source, tokens, count, i++, \":\") && r != 0"; } return 0; } };
        prog_write4(INST_JMP_IF_FALSE, 0, 0, ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "598" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "598" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 ));
        size_t jump_at = prog.i - 3;

        i += compile_statementlist(source, tokens, count, i);

        uint32_t end = prog.i + ((tokens[i].kind == -3 || tokens[i].kind == -2) ? 3 : 0);
        memcpy(prog.code + jump_at, &end, 4);

        uint32_t skips[255] = {};
        size_t skip_i = 0;

        while (tokens[i].kind == -3 || tokens[i].kind == -2)
        {

            prog_write3(INST_JMP, 0, 0);
            skips[skip_i++] = prog.i - 2;
            { if (__builtin_expect(!(skip_i < 255 -1), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Too many elifs in if-else chain\""; else filli_err = "skip_i < ELIFLIMIT-1"; } return 0; } };

            if (tokens[i].kind == -3)
            {
                size_t r = compile_expr(source, tokens, count, i + 1, 0);
                i += r + 1;
                { if (__builtin_expect(!(token_is(source, tokens, count, i++, ":") && r != 0), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Conditions must not be empty\""; else filli_err = "token_is(source, tokens, count, i++, \":\") && r != 0"; } return 0; } };
                prog_write4(INST_JMP_IF_FALSE, 0, 0, ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "621" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "621" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 ));
                size_t jump_at = prog.i - 3;

                i += compile_statementlist(source, tokens, count, i);

                uint32_t end = prog.i + ((tokens[i].kind == -3 || tokens[i].kind == -2) ? 3 : 0);
                memcpy(prog.code + jump_at, &end, 4);
            }
            else
            {
                { if (__builtin_expect(!(token_is(source, tokens, count, ++i, ":")), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Expected ':'\""; else filli_err = "token_is(source, tokens, count, ++i, \":\")"; } return 0; } };
                i += compile_statementlist(source, tokens, count, i + 1) + 1;
            }
        }
        { if (__builtin_expect(!(tokens[i].kind == -11), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Expected 'end'\""; else filli_err = "tokens[i].kind == -11"; } return 0; } };
        uint32_t real_end = prog.i;
        while (skip_i > 0) memcpy(prog.code + skips[--skip_i], &real_end, 4);
        return i + 1 - orig_i;
    }
    if (tokens[i].kind == -5)
    {
        cs->loop_nesting++;
        size_t loop_cont_base = cs->loop_cont_i;
        size_t loop_break_base = cs->loop_break_i;

        size_t expr_i = i + 1;
        size_t r = compile_expr(source, tokens, count, expr_i, 0);
        i += r + 1;
        { if (__builtin_expect(!(token_is(source, tokens, count, i++, ":") && r != 0), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Conditions must not be empty\""; else filli_err = "token_is(source, tokens, count, i++, \":\") && r != 0"; } return 0; } };
        prog_write4(INST_JMP_IF_FALSE, 0, 0, ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "650" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "650" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 ));
        size_t skip_at = prog.i - 3;
        uint32_t loop_at = prog.i;

        i += compile_statementlist(source, tokens, count, i);
        { if (__builtin_expect(!(i < count && tokens[i].kind == -11), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Expected 'end'\""; else filli_err = "i < count && tokens[i].kind == -11"; } return 0; } };

        uint32_t cont_to = prog.i;
        compile_expr(source, tokens, count, expr_i, 0);
        prog_write4(INST_JMP_IF_TRUE, 0, 0, ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "659" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "659" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 ));
        memcpy(prog.code + (prog.i - 3), &loop_at, 4);

        uint32_t end = prog.i;
        memcpy(prog.code + skip_at, &end, 4);

        uint32_t break_to = prog.i;
        while (cs->loop_break_i > loop_break_base) memcpy(prog.code + cs->loop_breaks[--cs->loop_break_i], &break_to, 4);
        while (cs->loop_cont_i > loop_cont_base ) memcpy(prog.code + cs->loop_conts [--cs->loop_cont_i ], &cont_to , 4);
        cs->loop_nesting--;

        return i + 1- orig_i;
    }
    else if (token_is(source, tokens, count, i, "let"))
    {
        if (++i >= count) return 0;
        int16_t id = lex_ident_offset - tokens[i++].kind;

        if (cs->func_depth == 0) cs->globals_reg[id] = ++cs->globals_n;
        else cs->locals_reg [id] = ++cs->locals_n;
        { if (__builtin_expect(!(cs->globals_n < 1024 && cs->locals_n < 1024), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Too many variables\""; else filli_err = "cs->globals_n < FRAME_VARCOUNT && cs->locals_n < FRAME_VARCOUNT"; } return 0; } };

        if (token_is(source, tokens, count, i, "="))
        {
            size_t r = compile_expr(source, tokens, count, i + 1, 0);
            if (!r) return i - orig_i;
            i += r + 1;
            prog_write3(INST_SET + (cs->func_depth == 0), (cs->func_depth == 0) ? cs->globals_n - 1 : cs->locals_n - 1, ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "686" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "686" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 ));
        }
        return i - orig_i;
    }
    else if (token_is(source, tokens, count, i, "for"))
    {
        if (++i >= count) return 0;

        cs->loop_nesting++;
        size_t loop_cont_base = cs->loop_cont_i;
        size_t loop_break_base = cs->loop_break_i;

        int16_t id = lex_ident_offset - tokens[i++].kind;
        if (cs->func_depth == 0) cs->globals_reg[id] = ++cs->globals_n;
        else cs->locals_reg [id] = ++cs->locals_n;
        uint16_t idnum = (cs->func_depth == 0) ? cs->globals_n - 1 : cs->locals_n - 1;
        { if (__builtin_expect(!(cs->globals_n < 1024 && cs->locals_n < 1024), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Too many variables\""; else filli_err = "cs->globals_n < FRAME_VARCOUNT && cs->locals_n < FRAME_VARCOUNT"; } return 0; } };
        { if (__builtin_expect(!(token_is(source, tokens, count, i++, "in")), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Expected 'in'\""; else filli_err = "token_is(source, tokens, count, i++, \"in\")"; } return 0; } };
        uint16_t idx = cs->for_loop_index++;
        { if (__builtin_expect(!(idx < 255), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Too many for loops\""; else filli_err = "idx < FORLOOP_COUNT_LIMIT"; } return 0; } };

        size_t r = compile_expr(source, tokens, count, i, 0);
        i += r;
        { if (__builtin_expect(!(token_is(source, tokens, count, i++, ":") && r > 0), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"For loop requires valid expression\""; else filli_err = "token_is(source, tokens, count, i++, \":\") && r > 0"; } return 0; } };

        prog_write6(INST_FORSTART, idnum, idx, 0, 0, ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "711" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "711" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 ));

        uint32_t head = prog.i;

        i += compile_statementlist(source, tokens, count, i);
        { if (__builtin_expect(!(tokens[i++].kind == -11), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Expected 'end'\""; else filli_err = "tokens[i++].kind == -11"; } return 0; } };

        uint32_t cont_to = prog.i;
        prog_write5(INST_FOREND, idnum, idx, 0, 0);
        memcpy(prog.code + (prog.i - 2), &head, 4);

        uint32_t end = prog.i;
        memcpy(prog.code + (head - 3), &end, 4);

        uint32_t break_to = prog.i;
        while (cs->loop_break_i > loop_break_base) memcpy(prog.code + cs->loop_breaks[--cs->loop_break_i], &break_to, 4);
        while (cs->loop_cont_i > loop_cont_base ) memcpy(prog.code + cs->loop_conts [--cs->loop_cont_i ], &cont_to , 4);
        cs->loop_nesting--;

        return i - orig_i;
    }
    else if (i + 2 < count && tokens[i].kind < -lex_ident_offset
        && (token_is(source, tokens, count, i+1, "=")
            || token_is(source, tokens, count, i+1, "+=") || token_is(source, tokens, count, i+1, "-=")
            || token_is(source, tokens, count, i+1, "*=") || token_is(source, tokens, count, i+1, "/=")))
    {
        int16_t id = lex_ident_offset - tokens[i++].kind;

        const char * opstr = stringdupn(source + tokens[i].i, tokens[i].len);
        size_t oplen = tokens[i++].len;

        size_t ret = compile_expr(source, tokens, count, i, 0);
        { if (__builtin_expect(!(ret > 0), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Assignment requires valid expression\""; else filli_err = "ret > 0"; } return 0; } };
        i += ret;

        uint8_t mode = 10;
        if (cs->func_depth > 0 && cs->locals_reg[id]) mode = 0;
        else if (cs->func_depth > 0 && cs->caps_reg[id]) mode = 2;
        else if (cs->globals_reg[id]) mode = 1;
        else { if (!filli_err) filli_err = "\"Unknown variable\""; return 0; };

        if (strncmp(opstr, "=", oplen) == 0) prog_write(INST_SET + mode);
        else if (strncmp(opstr, "+=", oplen) == 0) prog_write(INST_SET_ADD + mode);
        else if (strncmp(opstr, "-=", oplen) == 0) prog_write(INST_SET_SUB + mode);
        else if (strncmp(opstr, "*=", oplen) == 0) prog_write(INST_SET_MUL + mode);
        else if (strncmp(opstr, "/=", oplen) == 0) prog_write(INST_SET_DIV + mode);

        prog_write2((mode == 0 ? cs->locals_reg[id] : mode == 1 ? cs->globals_reg[id] : cs->caps_reg[id]) - 1, ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "758" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "758" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 ));

        return i - orig_i;
    }
    else if (i + 2 < count && tokens[i].kind < -lex_ident_offset
             && token_is(source, tokens, count, i+1, "(")
             && cs->funcs_reg[lex_ident_offset - tokens[i].kind].exists)
    {
        uint16_t id = lex_ident_offset - tokens[i++].kind;
        i += 1;

        uint32_t j = 0; while (!token_is(source, tokens, count, i, ")")) { { if (__builtin_expect(!(j < 255), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Too many arguments to function\""; else filli_err = "j < ARGLIMIT"; } return 0; } }; size_t r = compile_expr(source, tokens, count, i, 0); if (r == 0) return 0; else i += r;; j += 1; if (!(token_is(source, tokens, count, i, ")") || token_is(source, tokens, count, i, ","))) return 0; if (token_is(source, tokens, count, i, ",")) i++; } if (!token_is(source, tokens, count, i++, ")")) return 0;




        for (size_t i = 0; i < j; i++) (void)( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "774" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "774" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 );
        prog_write4(INST_FUNCCALL, id, j, (cs->stackpos[cs->func_depth] + 1024));

        return i - orig_i;
    }
    else if (tokens[i].kind == -11 || tokens[i].kind == -3 || tokens[i].kind == -2)
        return i - orig_i;
    else if (token_is(source, tokens, count, i, "\n") || token_is(source, tokens, count, i, ";"))
        return 1;
    else if (token_is(source, tokens, count, i, "continue") || token_is(source, tokens, count, i, "break"))
    {
        { if (__builtin_expect(!(cs->loop_nesting > 0), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Tried to use break/continue outside of loop\""; else filli_err = "cs->loop_nesting > 0"; } return 0; } };
        prog_write3(INST_JMP, 0, 0);
        if (token_is(source, tokens, count, i, "continue")) cs->loop_conts[cs->loop_cont_i++] = prog.i - 2;
        else { cs->loop_breaks[cs->loop_break_i++] = prog.i - 2; }
        return 1;
    }
    else if (token_is(source, tokens, count, i, "return"))
    {
        size_t r = compile_expr(source, tokens, count, ++i, 0);
        if (r == 0) prog_write(INST_RETURN_VOID);
        else prog_write2(INST_RETURN_VAL, ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "795" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "795" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 ));
        return r + 1;
    }
    else if (token_is(source, tokens, count, i, "yield"))
    {
        size_t r = compile_expr(source, tokens, count, ++i, 0);
        if (r == 0) prog_write3(PUSH_NULL, INST_YIELD, (cs->stackpos[cs->func_depth] + 1024));
        else prog_write2(INST_YIELD, ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "802" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "802" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 ));
        return r + 1;
    }
    else
    {
        size_t r = compile_expr(source, tokens, count, i, 0);
        if (r == 0)
        {
            printsn(source + tokens[i].i, tokens[i].len);
            prints("\n");
            { if (!filli_err) filli_err = "\"Unrecognized expression or statement\""; return 0; };
        }
        i += r;

        uint32_t ok_idx = 0;
        if (cs->last_idx == prog.i - 2 && prog.code[prog.i - 2] == INST_INDEX) ok_idx = 2;
        if (cs->last_idx == prog.i - 3 && prog.code[prog.i - 3] == INST_INDEX_INT) ok_idx = 3;

        if (ok_idx && (token_is(source, tokens, count, i, "=")
             || token_is(source, tokens, count, i, "+=") || token_is(source, tokens, count, i, "-=")
             || token_is(source, tokens, count, i, "*=") || token_is(source, tokens, count, i, "/=")))
        {
            size_t old_i = i;
            uint32_t checkpoint = prog.i - ok_idx;
            size_t r2 = compile_expr(source, tokens, count, i + 1, 0);
            if (!r2) { ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "827" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "827" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 ); return r; }
            r += r2 + 1;
            prog.code[checkpoint] = ok_idx == 2 ? INST_INDEX_LOC : INST_INDEX_LOC_INT;
            if (token_is(source, tokens, count, old_i, "=" )) prog_write2(INST_SET_LOC, ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "830" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "830" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 ));
            if (token_is(source, tokens, count, old_i, "+=")) prog_write2(INST_SET_LOC_ADD, ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "831" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "831" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 ));
            if (token_is(source, tokens, count, old_i, "-=")) prog_write2(INST_SET_LOC_SUB, ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "832" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "832" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 ));
            if (token_is(source, tokens, count, old_i, "*=")) prog_write2(INST_SET_LOC_MUL, ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "833" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "833" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 ));
            if (token_is(source, tokens, count, old_i, "/=")) prog_write2(INST_SET_LOC_DIV, ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "834" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "834" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 ));
            ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "835" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "835" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 );
        }
        else { ( ( (!(cs->stackpos[cs->func_depth] != 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "837" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth] != 0" "\nat " "837" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 ), (--cs->stackpos[cs->func_depth]) + 1024 ); }
        return r;
    }
}
size_t compile_statementlist(const char * source, Token * tokens, size_t count, size_t i)
{
    size_t orig_i = i;
    while (1)
    {
        if (i >= count) return i - orig_i;
        size_t r = compile_statement(source, tokens, count, i);
        if (r == 0) return i - orig_i; else i += r;
    }
}

size_t closure_count = 0;

size_t compile_register_func(const char * source, Token * tokens, size_t count, uint16_t id, uint32_t i)
{
    cs->func_depth++;
    cs->stackpos[cs->func_depth] = 0;

    size_t orig_i = i;

    if (!token_is(source, tokens, count, i++, "(")) { if (!filli_err) filli_err = "\"Invalid funcdef\""; return 0; };
    uint16_t args[255];
    uint32_t j = 0; while (!token_is(source, tokens, count, i, ")")) { { if (__builtin_expect(!(j < 255), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Too many arguments to function\""; else filli_err = "j < ARGLIMIT"; } return 0; } }; if (tokens[i].kind >= -lex_ident_offset) { if (!filli_err) filli_err = "\"Invalid funcdef\""; return 0; }; args[j] = lex_ident_offset - tokens[i++].kind; cs->locals_reg[args[j]] = ++cs->locals_n;; j += 1; if (!(token_is(source, tokens, count, i, ")") || token_is(source, tokens, count, i, ","))) { if (!filli_err) filli_err = "\"Invalid funcdef\""; return 0; }; if (token_is(source, tokens, count, i, ",")) i++; } if (!token_is(source, tokens, count, i++, ")")) { if (!filli_err) filli_err = "\"Invalid funcdef\""; return 0; };





    if (!token_is(source, tokens, count, i++, ":")) { if (!filli_err) filli_err = "\"Invalid funcdef\""; return 0; };

    cs->funcs_reg[id] = (Funcdef) {1, 0, 0, (uint16_t)j, id, 0, 0, prog.i, 0, 0, 0};
    if (j > 0)
    {
        cs->funcs_reg[id].args = (uint16_t *)zalloc(sizeof(uint16_t)*j);
        memcpy(cs->funcs_reg[id].args, args, j * sizeof(uint16_t));
    }

    size_t closure_count_start = closure_count;

    i += compile_statementlist(source, tokens, count, i);
    prog_write(INST_RETURN_VOID);
    cs->func_depth--;
    { if (__builtin_expect(!(tokens[i++].kind == -11), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Expected 'end'\""; else filli_err = "tokens[i++].kind == -11"; } return 0; } };
    ( (!(cs->stackpos[cs->func_depth + 1] == 0)) ? ( (+0) ? ( prints("Assert:\n" "\"\"" "\nat " "884" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) : ( prints("Assert:\n" "cs->stackpos[cs->func_depth + 1] == 0" "\nat " "884" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ) ) : (void)0 );

    if (closure_count == closure_count_start) cs->funcs_reg[id].poolsafe = 1;
    cs->funcs_reg[id].vars_len = cs->locals_n;

    return i - orig_i;
}

size_t compile_func(const char * source, Token * tokens, size_t count, size_t i)
{
    size_t orig_i = i;
    if (i >= count) return 0;
    if (tokens[i].kind >= -lex_ident_offset) return 0;
    int16_t id = lex_ident_offset - tokens[i++].kind;

    prog_write3(INST_FUNCDEF, 0, 0);
    size_t len_offs = prog.i - 2;

    size_t r = compile_register_func(source, tokens, count, id, i);
    if (!r) return 0; i += r;

    memcpy(prog.code + len_offs, &prog.i, 4);

    return i - orig_i;
}
size_t compile_lambda(const char * source, Token * tokens, size_t count, size_t i, int16_t * caps, uint16_t caps_count)
{
    size_t orig_i = i;
    if (i >= count) return 0;
    uint32_t id = cs->lambda_id++;

    prog_write6(INST_LAMBDA, 0, 0, 0, 0, ( (( (__builtin_expect(!(((void)"Stack exceeded limit.", cs->stackpos[cs->func_depth] < 1024)), 0)) ? ( (+0 && !filli_err) ? filli_err = "" : (!filli_err) ? filli_err = "((void)\"Stack exceeded limit.\", cs->stackpos[cs->func_depth] < 1024)" : "") : ""), (void) 0 ), (cs->stackpos[cs->func_depth] += (cs->stackpos[cs->func_depth] < 1024)) + 1024 - 1 ));
    size_t id_offs = prog.i - 5;
    memcpy(prog.code + id_offs, &id, 4);

    size_t r = compile_register_func(source, tokens, count, id, i);
    if (!r) return 0; i += r;

    cs->funcs_reg[id].caps = caps;
    cs->funcs_reg[id].cap_count = caps_count;

    if (caps_count > 0) closure_count += 1;

    memcpy(prog.code + id_offs + 2, &prog.i, 4);

    return i - orig_i;
}
size_t compile(const char * source, Token * tokens, size_t count, size_t i)
{
    size_t r, orig_i = i;
    while (i < count)
    {
        { if (filli_err) return 0; }
        if (tokens[i].kind == -4)
        {
            cs->locals_n = 0;
            compile_func_start();
            r = compile_func(source, tokens, count, i+1);
            { if (__builtin_expect(!(r != 0), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Incomplete function\""; else filli_err = "r != 0"; } return 0; } };
            compile_func_end();
            i += r + 1;
        }
        else if ((r = compile_statement(source, tokens, count, i))) i += r;
        else
        {
            prints("AT: "); printsn(source + tokens[i].i, tokens[i].len); prints("\n"); { if (!filli_err) filli_err = "\"Expected function or statement\""; return 0; };
            break;
        }
    }
    prog_write(INST_RETURN_VOID);
    return i - orig_i;
}

struct _BiValue;
typedef struct _Array { struct _Value * buf; size_t len; size_t cap; } Array;
typedef struct _Dict { struct _BiValue * buf; size_t len; size_t cap; size_t tombs; } Dict;

struct _Frame;


enum { VALUE_NULL=0, VALUE_INVALID=1, VALUE_FLOAT=3, VALUE_ARRAY=7, VALUE_DICT=15, VALUE_STRING=31, VALUE_FUNC=40, VALUE_STATE=63, VALUE_TOMBSTONE=127, };



static inline int types_same_match(int a, int b, int c) { return (a+b)==(c+c); }


typedef struct _Value {
    union { double f; Array * a; Dict * d; char ** s; Funcdef * fn; struct _FState * fs; } u;
    uint8_t tag;

    uint32_t _unused_opt_killer;
} Value;
typedef struct _BiValue { struct _Value l; struct _Value r; } BiValue;

Value val_tagged(uint8_t tag) { Value v; memset(&v, 0, sizeof(Value)); v.tag = tag; return v; }
Value val_float(double f) { Value v = val_tagged(VALUE_FLOAT); v.u.f = f; return v; }
Value val_string(char * s) { Value v = val_tagged(VALUE_STRING); v.u.s = (char **)zalloc(sizeof(char *)); *v.u.s = s; return v; }
Value val_func(uint16_t id) { Value v = val_tagged(VALUE_FUNC); v.u.fn = &cs->funcs_reg[id]; return v; }

typedef struct _FState { Funcdef * fn; struct _Frame * frame; } FState;
FState * new_fstate(Funcdef * fn) { FState * r = (FState *)zalloc(sizeof(FState)); r->fn = fn; return r; }
Value val_funcstate(Funcdef * fn, struct _Frame * frame) { Value v = val_tagged(VALUE_STATE); v.u.fs = new_fstate(fn); v.u.fs->frame = frame; return v; }

Value val_array(size_t n) { Value v = val_tagged(VALUE_ARRAY); v.u.a = (Array *)zalloc(sizeof(Array));
    *v.u.a = (Array) { (Value *)zalloc(sizeof(Value) * n), n, n }; return v; }

Value * array_get(Array * a, size_t i) { { if (__builtin_expect(!(i < a->len), 0)) { if (!filli_err) { if (+0) filli_err = ""; else filli_err = "i < a->len"; } return 0; } }; return a->buf + i; }

int8_t val_cmp(Value v1, Value v2)
{




    if (v2.tag != v1.tag || (v1.tag == VALUE_FLOAT && (v1.u.f != v1.u.f || v2.u.f != v2.u.f))) return 2;
    else if (v1.tag == VALUE_FLOAT && v1.u.f < v2.u.f) return -1;
    else if (v1.tag == VALUE_FLOAT && v1.u.f > v2.u.f) return 1;
    else if (v1.tag == VALUE_STRING) return v1.u.s == v2.u.s ? 0 : strcmp(*v1.u.s, *v2.u.s);
    else if ((v1.tag == VALUE_ARRAY && v1.u.a != v2.u.a) || (v1.tag == VALUE_DICT && v1.u.d != v2.u.d)) return 2;
    else if ((v1.tag == VALUE_FUNC && v1.u.fn != v2.u.fn) || (v1.tag == VALUE_STATE && v1.u.fs != v2.u.fs)) return 2;
    return 0;
}


uint64_t double_bits_safe(double f) { if (f == 0.0) return 0; uint64_t n = 0; memcpy(&n, &f, 8); return n; }
uint64_t val_hash(Value * v)
{
    { if (__builtin_expect(!(v->tag == VALUE_STRING || v->tag == VALUE_FLOAT || v->tag == VALUE_FUNC || v->tag == VALUE_NULL), 0)) { if (!filli_err) { if (1 +0) filli_err = "\"Tried to use an unhashable type (dict or array) as a dict key\""; else filli_err = "v->tag == VALUE_STRING || v->tag == VALUE_FLOAT || v->tag == VALUE_FUNC || v->tag == VALUE_NULL"; } return 0; } };

    uint64_t hash = 0; uint64_t hv = 0xf6f1029eab913ac5;

    hash = (hash + v->tag) * hv;
    if (v->tag == VALUE_FLOAT) hash = (hash + double_bits_safe(v->u.f)) * hv;
    else if (v->tag == VALUE_STRING) for (size_t i = 0; (*v->u.s)[i] != 0; i++) hash = (hash + (*v->u.s)[i]) * hv;
    else if (v->tag == VALUE_FUNC) hash = (hash + v->u.fn->id) * hv;

    return hash ^ (hash >> 6);
}


void dict_reallocate(Dict * d, size_t newcap)
{
    BiValue * newbuf = (BiValue *)zalloc(sizeof(BiValue) * newcap);
    for (size_t i = 0; i < newcap; i++)
        newbuf[i] = (BiValue) { val_tagged(VALUE_INVALID), val_tagged(VALUE_INVALID) };
    for (size_t i = 0; i < d->cap; i++)
    {
        if (d->buf[i].l.tag == VALUE_TOMBSTONE || d->buf[i].l.tag == VALUE_INVALID) continue;
        uint64_t hash = val_hash(&d->buf[i].l) & (newcap - 1);
        while (newbuf[hash].l.tag != VALUE_INVALID && val_cmp(d->buf[i].l, newbuf[hash].l) != 0) hash = (hash + 1) & (d->cap - 1);
        newbuf[hash] = (BiValue) { d->buf[i].l, d->buf[i].r };
    }
    d->tombs = 0;
    d->cap = newcap;
    d->buf = newbuf;
}

BiValue * dict_get_or_insert(Dict * d, Value v)
{
    if (d->cap == 0) dict_reallocate(d, 8);

    if ((d->len + 1 + d->tombs) * 2 > d->cap) dict_reallocate(d, d->cap * 2);

    uint64_t hash = val_hash(&v) & (d->cap - 1);
    while (d->buf[hash].l.tag != VALUE_INVALID && val_cmp(v, d->buf[hash].l) != 0) hash = (hash + 1) & (d->cap - 1);
    if (d->buf[hash].l.tag == VALUE_INVALID)
    {
        d->len++;
        d->buf[hash] = (BiValue) { v, val_tagged(VALUE_NULL) };
    }
    return &d->buf[hash];
}

uint8_t val_truthy(Value v)
{
    if (v.tag == VALUE_FLOAT) return v.u.f != 0.0;
    if (v.tag == VALUE_STRING) return (*v.u.s)[0] != 0;
    if (v.tag == VALUE_ARRAY) return v.u.a->len > 0;
    if (v.tag == VALUE_DICT) return v.u.d->len > 0;
    if (v.tag == VALUE_FUNC) return 1;
    return 0;
}


__attribute__((always_inline)) static inline void value_store(Value * p, Value v) { p->tag = v.tag; p->u = v.u; }

typedef struct _LoopPair { uint64_t l; uint64_t r; } LoopPair;

typedef struct _Frame {
    uint32_t pc, return_slot;
    struct _Frame * return_to;
    Value * set_tgt_agg; char * set_tgt_char;
    Value vars[1024 + 1024];
    LoopPair forloops[255];
    Value ** caps; Funcdef * fn;
} Frame;

void print_op_and_panic(uint16_t op) { prints("---\n"); printu16hex(op); prints("\n---\n"); { if (!filli_err) filli_err = "\"Unknown operation\""; return ; }; }

void handle_intrinsic_func(uint16_t id, size_t argcount, Frame * frame, size_t stackpos, size_t return_slot);

Frame * framepool = 0;
Frame * framepoolpop(void) { Frame * ret = framepool; framepool = framepool->return_to; ret->return_to = 0; return ret; }
void framepoolpush(Frame * frame) { memset(frame, 0, 32); memset(frame->vars, 0, frame->fn->vars_len * sizeof(Value)); frame->return_to = framepool; framepool = frame; }



size_t __attribute__((preserve_none)) _handler_INST_INVALID(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_PUSH_NULL(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_PUSH_DICT_EMPTY(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_RETURN_VAL(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_RETURN_VOID(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_YIELD(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_ADD(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SUB(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_MUL(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_DIV(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_CMP_AND(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_CMP_OR(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_LOC(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_LOC_ADD(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_LOC_SUB(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_LOC_MUL(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_LOC_DIV(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_INDEX(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_INDEX_LOC(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_CMP_EQ(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_CMP_NE(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_CMP_GT(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_CMP_LT(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_CMP_GE(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_CMP_LE(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_PUSH_FUNCNAME(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_FUNCCALL_REF(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_PUSH_STRING(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_ARRAY_LITERAL(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_PUSH_LOCAL(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_PUSH_GLOBAL(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_PUSH_CAP(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_GLOBAL(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_CAP(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_ADD(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_GLOBAL_ADD(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_CAP_ADD(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_SUB(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_GLOBAL_SUB(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_CAP_SUB(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_MUL(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_GLOBAL_MUL(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_CAP_MUL(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_DIV(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_GLOBAL_DIV(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_SET_CAP_DIV(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_JMP(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_JMP_IF_FALSE(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_JMP_IF_TRUE(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_FUNCDEF(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_FUNCCALL(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_PUSH_NUM(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_FOREND(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_FORSTART(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_LAMBDA(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_BITAND(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_BITOR(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_BITXOR(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_INTMOD(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_INDEX_INT(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_INST_INDEX_LOC_INT(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *); size_t __attribute__((preserve_none)) _handler_PUSH_INT(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *);



typedef size_t (*__attribute__((preserve_none)) handler)(Program *, size_t, uint16_t *, size_t *, Frame *, Frame *);
static handler ops[0x100] = {};

size_t interpret(size_t from_pc)
{
    Frame * frame = (Frame *)zalloc(sizeof(Frame));
    Frame * global_frame = frame;

    frame->pc = from_pc;
# 1117 "src/filli.h"
    for (size_t i = 0; i < 0x100; i++) ops[i] = _handler_INST_INVALID;





    ops[(INST_INVALID&0xFF)] = _handler_INST_INVALID; ops[(PUSH_NULL&0xFF)] = _handler_PUSH_NULL; ops[(PUSH_DICT_EMPTY&0xFF)] = _handler_PUSH_DICT_EMPTY; ops[(INST_RETURN_VAL&0xFF)] = _handler_INST_RETURN_VAL; ops[(INST_RETURN_VOID&0xFF)] = _handler_INST_RETURN_VOID; ops[(INST_YIELD&0xFF)] = _handler_INST_YIELD; ops[(INST_ADD&0xFF)] = _handler_INST_ADD; ops[(INST_SUB&0xFF)] = _handler_INST_SUB; ops[(INST_MUL&0xFF)] = _handler_INST_MUL; ops[(INST_DIV&0xFF)] = _handler_INST_DIV; ops[(INST_CMP_AND&0xFF)] = _handler_INST_CMP_AND; ops[(INST_CMP_OR&0xFF)] = _handler_INST_CMP_OR; ops[(INST_SET_LOC&0xFF)] = _handler_INST_SET_LOC; ops[(INST_SET_LOC_ADD&0xFF)] = _handler_INST_SET_LOC_ADD; ops[(INST_SET_LOC_SUB&0xFF)] = _handler_INST_SET_LOC_SUB; ops[(INST_SET_LOC_MUL&0xFF)] = _handler_INST_SET_LOC_MUL; ops[(INST_SET_LOC_DIV&0xFF)] = _handler_INST_SET_LOC_DIV; ops[(INST_INDEX&0xFF)] = _handler_INST_INDEX; ops[(INST_INDEX_LOC&0xFF)] = _handler_INST_INDEX_LOC; ops[(INST_CMP_EQ&0xFF)] = _handler_INST_CMP_EQ; ops[(INST_CMP_NE&0xFF)] = _handler_INST_CMP_NE; ops[(INST_CMP_GT&0xFF)] = _handler_INST_CMP_GT; ops[(INST_CMP_LT&0xFF)] = _handler_INST_CMP_LT; ops[(INST_CMP_GE&0xFF)] = _handler_INST_CMP_GE; ops[(INST_CMP_LE&0xFF)] = _handler_INST_CMP_LE; ops[(PUSH_FUNCNAME&0xFF)] = _handler_PUSH_FUNCNAME; ops[(INST_FUNCCALL_REF&0xFF)] = _handler_INST_FUNCCALL_REF; ops[(PUSH_STRING&0xFF)] = _handler_PUSH_STRING; ops[(INST_ARRAY_LITERAL&0xFF)] = _handler_INST_ARRAY_LITERAL; ops[(PUSH_LOCAL&0xFF)] = _handler_PUSH_LOCAL; ops[(PUSH_GLOBAL&0xFF)] = _handler_PUSH_GLOBAL; ops[(PUSH_CAP&0xFF)] = _handler_PUSH_CAP; ops[(INST_SET&0xFF)] = _handler_INST_SET; ops[(INST_SET_GLOBAL&0xFF)] = _handler_INST_SET_GLOBAL; ops[(INST_SET_CAP&0xFF)] = _handler_INST_SET_CAP; ops[(INST_SET_ADD&0xFF)] = _handler_INST_SET_ADD; ops[(INST_SET_GLOBAL_ADD&0xFF)] = _handler_INST_SET_GLOBAL_ADD; ops[(INST_SET_CAP_ADD&0xFF)] = _handler_INST_SET_CAP_ADD; ops[(INST_SET_SUB&0xFF)] = _handler_INST_SET_SUB; ops[(INST_SET_GLOBAL_SUB&0xFF)] = _handler_INST_SET_GLOBAL_SUB; ops[(INST_SET_CAP_SUB&0xFF)] = _handler_INST_SET_CAP_SUB; ops[(INST_SET_MUL&0xFF)] = _handler_INST_SET_MUL; ops[(INST_SET_GLOBAL_MUL&0xFF)] = _handler_INST_SET_GLOBAL_MUL; ops[(INST_SET_CAP_MUL&0xFF)] = _handler_INST_SET_CAP_MUL; ops[(INST_SET_DIV&0xFF)] = _handler_INST_SET_DIV; ops[(INST_SET_GLOBAL_DIV&0xFF)] = _handler_INST_SET_GLOBAL_DIV; ops[(INST_SET_CAP_DIV&0xFF)] = _handler_INST_SET_CAP_DIV; ops[(INST_JMP&0xFF)] = _handler_INST_JMP; ops[(INST_JMP_IF_FALSE&0xFF)] = _handler_INST_JMP_IF_FALSE; ops[(INST_JMP_IF_TRUE&0xFF)] = _handler_INST_JMP_IF_TRUE; ops[(INST_FUNCDEF&0xFF)] = _handler_INST_FUNCDEF; ops[(INST_FUNCCALL&0xFF)] = _handler_INST_FUNCCALL; ops[(PUSH_NUM&0xFF)] = _handler_PUSH_NUM; ops[(INST_FOREND&0xFF)] = _handler_INST_FOREND; ops[(INST_FORSTART&0xFF)] = _handler_INST_FORSTART; ops[(INST_LAMBDA&0xFF)] = _handler_INST_LAMBDA; ops[(INST_BITAND&0xFF)] = _handler_INST_BITAND; ops[(INST_BITOR&0xFF)] = _handler_INST_BITOR; ops[(INST_BITXOR&0xFF)] = _handler_INST_BITXOR; ops[(INST_INTMOD&0xFF)] = _handler_INST_INTMOD; ops[(INST_INDEX_INT&0xFF)] = _handler_INST_INDEX_INT; ops[(INST_INDEX_LOC_INT&0xFF)] = _handler_INST_INDEX_LOC_INT; ops[(PUSH_INT&0xFF)] = _handler_PUSH_INT;
    size_t * cache = (size_t *)malloc(sizeof(size_t) * prog.i);
    for (size_t j = 0; j < prog.i; j++) cache[j] = (size_t)(ops[prog.code[j] & 0xFF]);
# 1155 "src/filli.h"
    size_t ret = ((handler)(cache[frame->pc]))(&prog, frame->pc, prog.code, cache, frame, global_frame); free(cache); return ret;



        } __attribute__((preserve_none)) size_t _handler_INST_INVALID (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_INVALID; { ( prints("Assert:\n" "\"sdfakarwiu\"" "\nat " "1159" " in " "src/filli.h" "\n"), fflush((__acrt_iob_func(1))), abort() ); }
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_FUNCDEF (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_FUNCDEF; { uint32_t target = fi_mem_read_u32(code + (pc + 1)); frame->pc = target; pc = target; op = code[pc]; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame);; }





        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_ARRAY_LITERAL (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_ARRAY_LITERAL;
            uint16_t itemcount = code[pc + (1)];
            Value v = val_array(itemcount);
            for (size_t i = 0; i < itemcount; i++) v.u.a->buf[i] = frame->vars[code[pc + (2)] + (i)];
            { value_store(&frame->vars[code[pc + (2)] + (0)], (v)); }
# 1187 "src/filli.h"
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_FUNCCALL (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_FUNCCALL;
            uint16_t argcount = code[pc + (2)];
            Funcdef * fn = &cs->funcs_reg[code[pc + (1)]];
            uint32_t idx = (code[pc + (3)]); uint32_t return_slot = (code[pc + (3)]); { if (__builtin_expect(!(fn->exists), 0)) { { if (1 +0) filli_err = "\"Function does not exist\""; else filli_err = "fn->exists"; } return 0; } }; if (!fn->intrinsic) { pc += op >> 8; op = code[pc];; frame->pc = pc; Frame * prev = frame; Frame * next = (0) ? (0) : (fn->poolsafe && framepool) ? framepoolpop() : (Frame *)zalloc(sizeof(Frame)); next->fn = fn; next->return_to = frame; frame->return_slot = return_slot; frame = next; pc = frame->pc; { if (__builtin_expect(!(argcount == fn->argcount), 0)) { { if (1 +0) filli_err = "\"Function arg count doesn't match\""; else filli_err = "argcount == fn->argcount"; } return 0; } }; if (!(0)) for (size_t i = 0; i < fn->argcount; i++) { frame->vars[i] = prev->vars[idx + i]; Value * v = &frame->vars[i]; if (v->tag == VALUE_STRING) { char ** ss = (char **)zalloc(sizeof(char *)); *ss = *v->u.s; v->u.s = ss; } } if (!(0)) { frame->pc = fn->loc; pc = fn->loc; if (fn->cap_data) frame->caps = fn->cap_data; } op = code[pc]; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame);; } handle_intrinsic_func(fn->id, argcount, frame, idx, return_slot);

        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_FUNCCALL_REF (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_FUNCCALL_REF;
            uint16_t argcount = code[pc + (1)];
            Value v_func = frame->vars[code[pc + (2)] + (0)];
            { if (__builtin_expect(!(v_func.tag == VALUE_FUNC || v_func.tag == VALUE_STATE), 0)) { { if (1 +0) filli_err = "\"Tried to call a non-function\""; else filli_err = "v_func.tag == VALUE_FUNC || v_func.tag == VALUE_STATE"; } return 0; } };
            Funcdef * fn = v_func.tag == VALUE_FUNC ? v_func.u.fn : v_func.u.fs->fn;
            uint32_t idx = (code[pc + (2)] + 1); uint32_t return_slot = (code[pc + (2)]); { if (__builtin_expect(!(fn->exists), 0)) { { if (1 +0) filli_err = "\"Function does not exist\""; else filli_err = "fn->exists"; } return 0; } }; if (!fn->intrinsic) { pc += op >> 8; op = code[pc];; frame->pc = pc; Frame * prev = frame; Frame * next = (v_func.tag == VALUE_FUNC ? 0 : v_func.u.fs->frame) ? (v_func.tag == VALUE_FUNC ? 0 : v_func.u.fs->frame) : (fn->poolsafe && framepool) ? framepoolpop() : (Frame *)zalloc(sizeof(Frame)); next->fn = fn; next->return_to = frame; frame->return_slot = return_slot; frame = next; pc = frame->pc; { if (__builtin_expect(!(argcount == fn->argcount), 0)) { { if (1 +0) filli_err = "\"Function arg count doesn't match\""; else filli_err = "argcount == fn->argcount"; } return 0; } }; if (!(v_func.tag == VALUE_FUNC ? 0 : v_func.u.fs->frame)) for (size_t i = 0; i < fn->argcount; i++) { frame->vars[i] = prev->vars[idx + i]; Value * v = &frame->vars[i]; if (v->tag == VALUE_STRING) { char ** ss = (char **)zalloc(sizeof(char *)); *ss = *v->u.s; v->u.s = ss; } } if (!(v_func.tag == VALUE_FUNC ? 0 : v_func.u.fs->frame)) { frame->pc = fn->loc; pc = fn->loc; if (fn->cap_data) frame->caps = fn->cap_data; } op = code[pc]; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame);; } handle_intrinsic_func(fn->id, argcount, frame, idx, return_slot);






        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_YIELD (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_YIELD;
            if (!frame->return_to) { if (!filli_err) filli_err = "\"Attempted to yield from not inside of a function\""; return 0; };

            pc += op >> 8; op = code[pc];; frame->pc = pc;

            Value v = frame->vars[code[pc + (1)] + (0)];
            Value v2 = val_array(2);
            v2.u.a->buf[0] = v;
            v2.u.a->buf[1] = val_funcstate(frame->fn, frame);

            if (!frame->return_to) { pc += op >> 8; op = code[pc];; return pc; } Frame * oldframe = frame; Value retval = (v2); frame = frame->return_to; pc = frame->pc; value_store(&frame->vars[frame->return_slot], retval); if (0 && oldframe->fn && oldframe->fn->poolsafe) framepoolpush(oldframe); op = code[pc]; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame);;;

        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_RETURN_VAL (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_RETURN_VAL; if (!frame->return_to) { pc += op >> 8; op = code[pc];; return pc; } Frame * oldframe = frame; Value retval = (frame->vars[code[pc + (1)] + (0)]); frame = frame->return_to; pc = frame->pc; value_store(&frame->vars[frame->return_slot], retval); if (1 && oldframe->fn && oldframe->fn->poolsafe) framepoolpush(oldframe); op = code[pc]; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame);;;
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_RETURN_VOID (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_RETURN_VOID; if (!frame->return_to) { pc += op >> 8; op = code[pc];; return pc; } Frame * oldframe = frame; Value retval = (val_tagged(VALUE_NULL)); frame = frame->return_to; pc = frame->pc; value_store(&frame->vars[frame->return_slot], retval); if (1 && oldframe->fn && oldframe->fn->poolsafe) framepoolpush(oldframe); op = code[pc]; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame);;;
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_PUSH_NULL (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = PUSH_NULL; { value_store(&frame->vars[code[pc + (1)] + (0)], (val_tagged(VALUE_NULL))); }

        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_PUSH_DICT_EMPTY (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = PUSH_DICT_EMPTY;
            Value v = val_tagged(VALUE_DICT);
            v.u.d = (Dict *)zalloc(sizeof(Dict));
            { value_store(&frame->vars[code[pc + (1)] + (0)], (v)); }

        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_PUSH_INT (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = PUSH_INT; { value_store(&frame->vars[code[pc + (2)] + (0)], (val_float(code[pc + (1)]))); }
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_PUSH_NUM (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = PUSH_NUM; { value_store(&frame->vars[code[pc + (5)] + (0)], (val_float(fi_mem_read_f64(code + pc + 1)))); }

        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_PUSH_GLOBAL (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = PUSH_GLOBAL; { value_store(&frame->vars[code[pc + (2)] + (0)], (global_frame->vars[code[pc + (1)]])); }

        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_GLOBAL (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_GLOBAL; Value v2 = frame->vars[code[pc + (2)] + (0)];
            value_store(&global_frame->vars[code[pc + (1)]], v2);
            Value * v = &frame->vars[code[pc + (1)]];
            if (v->tag == VALUE_STRING) { char ** ss = (char **)zalloc(sizeof(char *)); *ss = *v->u.s; v->u.s = ss; }

        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_PUSH_CAP (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = PUSH_CAP; { value_store(&frame->vars[code[pc + (2)] + (0)], (*frame->caps[code[pc + (1)]])); }
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_CAP (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_CAP; Value v2 = frame->vars[code[pc + (2)] + (0)];
            value_store(frame->caps[code[pc + (1)]], v2);
            Value * v = &frame->vars[code[pc + (1)]];
            if (v->tag == VALUE_STRING) { char ** ss = (char **)zalloc(sizeof(char *)); *ss = *v->u.s; v->u.s = ss; }






        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_GLOBAL_ADD (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_GLOBAL_ADD; Value v2 = frame->vars[code[pc + (2)] + (0)]; uint16_t id = code[pc + (1)]; Value v1 = global_frame->vars[id]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"+\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; global_frame->vars[id].u.f = v1.u.f + v2.u.f; pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_GLOBAL_SUB (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_GLOBAL_SUB; Value v2 = frame->vars[code[pc + (2)] + (0)]; uint16_t id = code[pc + (1)]; Value v1 = global_frame->vars[id]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"-\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; global_frame->vars[id].u.f = v1.u.f - v2.u.f;
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_GLOBAL_MUL (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_GLOBAL_MUL; Value v2 = frame->vars[code[pc + (2)] + (0)]; uint16_t id = code[pc + (1)]; Value v1 = global_frame->vars[id]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"*\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; global_frame->vars[id].u.f = v1.u.f * v2.u.f; pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_GLOBAL_DIV (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_GLOBAL_DIV; Value v2 = frame->vars[code[pc + (2)] + (0)]; uint16_t id = code[pc + (1)]; Value v1 = global_frame->vars[id]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"/\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; global_frame->vars[id].u.f = v1.u.f / v2.u.f;
# 1256 "src/filli.h"
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_CAP_ADD (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_CAP_ADD; Value v2 = frame->vars[code[pc + (2)] + (0)]; uint16_t id = code[pc + (1)]; Value v1 = *frame->caps[id]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"+\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->caps[id]->u.f = v1.u.f + v2.u.f; pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_CAP_SUB (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_CAP_SUB; Value v2 = frame->vars[code[pc + (2)] + (0)]; uint16_t id = code[pc + (1)]; Value v1 = *frame->caps[id]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"-\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->caps[id]->u.f = v1.u.f - v2.u.f;
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_CAP_MUL (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_CAP_MUL; Value v2 = frame->vars[code[pc + (2)] + (0)]; uint16_t id = code[pc + (1)]; Value v1 = *frame->caps[id]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"*\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->caps[id]->u.f = v1.u.f * v2.u.f; pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_CAP_DIV (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_CAP_DIV; Value v2 = frame->vars[code[pc + (2)] + (0)]; uint16_t id = code[pc + (1)]; Value v1 = *frame->caps[id]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"/\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->caps[id]->u.f = v1.u.f / v2.u.f;





        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_ADD (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_ADD; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (1)] + (1)]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"+\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->vars[code[pc + (1)] + (0)].u.f = ( v1.u.f) + ( v2.u.f); pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SUB (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SUB; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (1)] + (1)]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"-\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->vars[code[pc + (1)] + (0)].u.f = ( v1.u.f) - ( v2.u.f);
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_MUL (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_MUL; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (1)] + (1)]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"*\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->vars[code[pc + (1)] + (0)].u.f = ( v1.u.f) * ( v2.u.f); pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_DIV (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_DIV; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (1)] + (1)]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"/\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->vars[code[pc + (1)] + (0)].u.f = ( v1.u.f) / ( v2.u.f);
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_BITAND (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_BITAND; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (1)] + (1)]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"&\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->vars[code[pc + (1)] + (0)].u.f = ((unsigned int) v1.u.f) & ((unsigned int) v2.u.f);
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_BITOR (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_BITOR; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (1)] + (1)]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"|\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->vars[code[pc + (1)] + (0)].u.f = ((unsigned int) v1.u.f) | ((unsigned int) v2.u.f);
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_BITXOR (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_BITXOR; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (1)] + (1)]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"^\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->vars[code[pc + (1)] + (0)].u.f = ((unsigned int) v1.u.f) ^ ((unsigned int) v2.u.f);
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_INTMOD (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_INTMOD; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (1)] + (1)]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"%\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->vars[code[pc + (1)] + (0)].u.f = ((long long int) v1.u.f) % (((long long int) v2.u.f) == 0 ? 1 : (long long int) v2.u.f);





        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_CMP_AND (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_CMP_AND; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (1)] + (1)]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Boolean comparison only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->vars[code[pc + (1)] + (0)].u.f = !!(v1.u.f) && !!(v2.u.f);
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_CMP_OR (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_CMP_OR; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (1)] + (1)]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Boolean comparison only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->vars[code[pc + (1)] + (0)].u.f = !!(v1.u.f) || !!(v2.u.f);





        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_ADD (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_ADD; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (2)] + (0)]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"+\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->vars[code[pc + (1)] + (0)].u.f = v1.u.f + v2.u.f; pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_SUB (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_SUB; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (2)] + (0)]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"-\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->vars[code[pc + (1)] + (0)].u.f = v1.u.f - v2.u.f;
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_MUL (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_MUL; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (2)] + (0)]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"*\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->vars[code[pc + (1)] + (0)].u.f = v1.u.f * v2.u.f; pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_DIV (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_DIV; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (2)] + (0)]; { if (__builtin_expect(!(types_same_match(v1.tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"/\" \" only works on numbers\""; else filli_err = "types_same_match(v1.tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->vars[code[pc + (1)] + (0)].u.f = v1.u.f / v2.u.f;







        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_LOC_ADD (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_LOC_ADD; Value v2 = frame->vars[code[pc + (1)] + (0)]; Value * v1p = frame->set_tgt_agg; { if (__builtin_expect(!(types_same_match(v1p->tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"+\" \" only works on numbers\""; else filli_err = "types_same_match(v1p->tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->set_tgt_agg = 0; v1p->u.f = v1p->u.f + v2.u.f; pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_LOC_SUB (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_LOC_SUB; Value v2 = frame->vars[code[pc + (1)] + (0)]; Value * v1p = frame->set_tgt_agg; { if (__builtin_expect(!(types_same_match(v1p->tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"-\" \" only works on numbers\""; else filli_err = "types_same_match(v1p->tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->set_tgt_agg = 0; v1p->u.f = v1p->u.f - v2.u.f;
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_LOC_MUL (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_LOC_MUL; Value v2 = frame->vars[code[pc + (1)] + (0)]; Value * v1p = frame->set_tgt_agg; { if (__builtin_expect(!(types_same_match(v1p->tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"*\" \" only works on numbers\""; else filli_err = "types_same_match(v1p->tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->set_tgt_agg = 0; v1p->u.f = v1p->u.f * v2.u.f; pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_LOC_DIV (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_LOC_DIV; Value v2 = frame->vars[code[pc + (1)] + (0)]; Value * v1p = frame->set_tgt_agg; { if (__builtin_expect(!(types_same_match(v1p->tag, v2.tag, VALUE_FLOAT)), 0)) { { if (1 +0) filli_err = "\"Operator \" \"/\" \" only works on numbers\""; else filli_err = "types_same_match(v1p->tag, v2.tag, VALUE_FLOAT)"; } return 0; } }; frame->set_tgt_agg = 0; v1p->u.f = v1p->u.f / v2.u.f;




        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_CMP_EQ (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_CMP_EQ; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (1)] + (1)]; int8_t equality = val_cmp(v1, v2); value_store(&frame->vars[code[pc + (1)] + (0)], val_float(equality == 0)); pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_CMP_NE (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_CMP_NE; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (1)] + (1)]; int8_t equality = val_cmp(v1, v2); value_store(&frame->vars[code[pc + (1)] + (0)], val_float(equality != 0));
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_CMP_LE (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_CMP_LE; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (1)] + (1)]; int8_t equality = val_cmp(v1, v2); value_store(&frame->vars[code[pc + (1)] + (0)], val_float(equality == 0 || equality == -1));
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_CMP_GE (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_CMP_GE; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (1)] + (1)]; int8_t equality = val_cmp(v1, v2); value_store(&frame->vars[code[pc + (1)] + (0)], val_float(equality == 0 || equality == 1));
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_CMP_LT (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_CMP_LT; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (1)] + (1)]; int8_t equality = val_cmp(v1, v2); value_store(&frame->vars[code[pc + (1)] + (0)], val_float(equality == -1)); pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_CMP_GT (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_CMP_GT; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (1)] + (1)]; int8_t equality = val_cmp(v1, v2); value_store(&frame->vars[code[pc + (1)] + (0)], val_float(equality == 1));

        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_FORSTART (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_FORSTART;
            Value v = frame->vars[code[pc + (5)] + (0)];
            { if (__builtin_expect(!(v.tag == VALUE_FLOAT), 0)) { { if (1 +0) filli_err = "\"For loops can only operate on numbers\""; else filli_err = "v.tag == VALUE_FLOAT"; } return 0; } };
            uint16_t id = code[pc + (1)]; uint16_t idx = code[pc + (2)];
            frame->vars[id] = val_float(0.0);
            if ((uint64_t)v.u.f < 1) { uint32_t target = fi_mem_read_u32(code + (pc + 3)); frame->pc = target; pc = target; op = code[pc]; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame);; }
            frame->forloops[idx].l = 0;
            frame->forloops[idx].r = v.u.f;
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_FOREND (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_FOREND;
            uint16_t id = code[pc + (1)]; uint16_t idx = code[pc + (2)];
            frame->forloops[idx].l += 1;
            value_store(&frame->vars[id], val_float(frame->forloops[idx].l));
            if (frame->forloops[idx].l < frame->forloops[idx].r) { uint32_t target = fi_mem_read_u32(code + (pc + 3)); frame->pc = target; pc = target; op = code[pc]; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame);; }

        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_JMP (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_JMP; { uint32_t target = fi_mem_read_u32(code + (pc + 1)); frame->pc = target; pc = target; op = code[pc]; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame);; }
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_JMP_IF_FALSE (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_JMP_IF_FALSE; if (!val_truthy(frame->vars[code[pc + (3)] + (0)])) { uint32_t target = fi_mem_read_u32(code + (pc + 1)); frame->pc = target; pc = target; op = code[pc]; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame);; }
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_JMP_IF_TRUE (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_JMP_IF_TRUE; if ( val_truthy(frame->vars[code[pc + (3)] + (0)])) { uint32_t target = fi_mem_read_u32(code + (pc + 1)); frame->pc = target; pc = target; op = code[pc]; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame);; }

        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_PUSH_STRING (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = PUSH_STRING; { value_store(&frame->vars[code[pc + (2)] + (0)], (val_string(stringdup(cs->compiled_strings[code[pc + (1)]])))); }

        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_PUSH_LOCAL (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = PUSH_LOCAL; { value_store(&frame->vars[code[pc + (2)] + (0)], (frame->vars[code[pc + (1)]])); }
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_PUSH_FUNCNAME (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = PUSH_FUNCNAME; { value_store(&frame->vars[code[pc + (2)] + (0)], (val_func(code[pc + (1)]))); }

        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET;
            value_store(&frame->vars[code[pc + (1)]], frame->vars[code[pc + (2)] + (0)]);
            Value * v = &frame->vars[code[pc + (1)]];
            if (__builtin_expect(v->tag == VALUE_STRING, 0)) { char ** ss = (char **)zalloc(sizeof(char *)); *ss = *v->u.s; v->u.s = ss; }

        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_SET_LOC (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_SET_LOC;
            Value v2 = frame->vars[code[pc + (1)] + (0)];
            if (__builtin_expect(!!frame->set_tgt_agg, 1)) { value_store(frame->set_tgt_agg, v2); frame->set_tgt_agg = 0; }
            else { { if (__builtin_expect(!(frame->set_tgt_char && v2.tag == VALUE_STRING), 0)) { { if (1 +0) filli_err = "\"Invalid assignment\""; else filli_err = "frame->set_tgt_char && v2.tag == VALUE_STRING"; } return 0; } };
                *frame->set_tgt_char = **v2.u.s; frame->set_tgt_char = 0; }
# 1357 "src/filli.h"
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_INDEX (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_INDEX; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (1)] + (1)]; { if (__builtin_expect(!(v1.tag == VALUE_STRING || v1.tag == VALUE_ARRAY || v1.tag == VALUE_DICT), 0)) { { if (+0) filli_err = ""; else filli_err = "v1.tag == VALUE_STRING || v1.tag == VALUE_ARRAY || v1.tag == VALUE_DICT"; } return 0; } }; if (v1.tag == VALUE_STRING || v1.tag == VALUE_ARRAY) { if (__builtin_expect(!(v2.tag == VALUE_FLOAT), 0)) { { if (1 +0) filli_err = "\"Unsupported index\""; else filli_err = "v2.tag == VALUE_FLOAT"; } return 0; } }; if (v1.tag == VALUE_DICT) { if (__builtin_expect(!(v2.tag == VALUE_FLOAT || v2.tag == VALUE_STRING || v2.tag == VALUE_FUNC || v2.tag == VALUE_NULL), 0)) { { if (1 +0) filli_err = "\"Unsupported dict key\""; else filli_err = "v2.tag == VALUE_FLOAT || v2.tag == VALUE_STRING || v2.tag == VALUE_FUNC || v2.tag == VALUE_NULL"; } return 0; } }; if (v1.tag == VALUE_STRING) { if (__builtin_expect(!(((size_t)v2.u.f) <= strlen(*v1.u.s)), 0)) { { if (1 +0) filli_err = "\"Index out of bounds\""; else filli_err = "((size_t)v2.u.f) <= strlen(*v1.u.s)"; } return 0; } }; if (v1.tag == VALUE_STRING) { char ** ss = (char **)zalloc(sizeof(char *)); *ss = stringdupn(*v1.u.s + (size_t)v2.u.f, 1); v1.u.s = ss; } else if (v1.tag == VALUE_ARRAY) { Value * vp = array_get(v1.u.a, v2.u.f); if (!vp) return 0; v1 = *vp; } else if (v1.tag == VALUE_DICT) v1 = dict_get_or_insert(v1.u.d, v2)->r; frame->vars[code[pc + (1)] + (0)] = v1;
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_INDEX_LOC (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_INDEX_LOC; Value v1 = frame->vars[code[pc + (1)] + (0)]; Value v2 = frame->vars[code[pc + (1)] + (1)]; { if (__builtin_expect(!(v1.tag == VALUE_STRING || v1.tag == VALUE_ARRAY || v1.tag == VALUE_DICT), 0)) { { if (+0) filli_err = ""; else filli_err = "v1.tag == VALUE_STRING || v1.tag == VALUE_ARRAY || v1.tag == VALUE_DICT"; } return 0; } }; if (v1.tag == VALUE_STRING || v1.tag == VALUE_ARRAY) { if (__builtin_expect(!(v2.tag == VALUE_FLOAT), 0)) { { if (1 +0) filli_err = "\"Unsupported index\""; else filli_err = "v2.tag == VALUE_FLOAT"; } return 0; } }; if (v1.tag == VALUE_DICT) { if (__builtin_expect(!(v2.tag == VALUE_FLOAT || v2.tag == VALUE_STRING || v2.tag == VALUE_FUNC || v2.tag == VALUE_NULL), 0)) { { if (1 +0) filli_err = "\"Unsupported dict key\""; else filli_err = "v2.tag == VALUE_FLOAT || v2.tag == VALUE_STRING || v2.tag == VALUE_FUNC || v2.tag == VALUE_NULL"; } return 0; } }; if (v1.tag == VALUE_STRING) { if (__builtin_expect(!(((size_t)v2.u.f) < strlen(*v1.u.s)), 0)) { { if (1 +0) filli_err = "\"Index out of bounds\""; else filli_err = "((size_t)v2.u.f) < strlen(*v1.u.s)"; } return 0; } }; if (v1.tag == VALUE_STRING) { { if (__builtin_expect(!((size_t)v2.u.f <= strlen(*v1.u.s)), 0)) { { if (1 +0) filli_err = "\"Index past end of string\""; else filli_err = "(size_t)v2.u.f <= strlen(*v1.u.s)"; } return 0; } }; *v1.u.s = stringdupn(*v1.u.s, strlen(*v1.u.s) + 1); frame->set_tgt_char = *v1.u.s + (size_t)v2.u.f; } else if (v1.tag == VALUE_ARRAY) frame->set_tgt_agg = array_get(v1.u.a, v2.u.f); else if (v1.tag == VALUE_DICT) frame->set_tgt_agg = &(dict_get_or_insert(v1.u.d, v2)->r);

        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_INDEX_INT (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_INDEX_INT; Value v1 = frame->vars[code[pc + (2)] + (0)]; Value v2 = val_float(code[pc + (1)]); { if (__builtin_expect(!(v1.tag == VALUE_STRING || v1.tag == VALUE_ARRAY || v1.tag == VALUE_DICT), 0)) { { if (+0) filli_err = ""; else filli_err = "v1.tag == VALUE_STRING || v1.tag == VALUE_ARRAY || v1.tag == VALUE_DICT"; } return 0; } }; if (v1.tag == VALUE_STRING || v1.tag == VALUE_ARRAY) { if (__builtin_expect(!(v2.tag == VALUE_FLOAT), 0)) { { if (1 +0) filli_err = "\"Unsupported index\""; else filli_err = "v2.tag == VALUE_FLOAT"; } return 0; } }; if (v1.tag == VALUE_DICT) { if (__builtin_expect(!(v2.tag == VALUE_FLOAT || v2.tag == VALUE_STRING || v2.tag == VALUE_FUNC || v2.tag == VALUE_NULL), 0)) { { if (1 +0) filli_err = "\"Unsupported dict key\""; else filli_err = "v2.tag == VALUE_FLOAT || v2.tag == VALUE_STRING || v2.tag == VALUE_FUNC || v2.tag == VALUE_NULL"; } return 0; } }; if (v1.tag == VALUE_STRING) { if (__builtin_expect(!(((size_t)v2.u.f) <= strlen(*v1.u.s)), 0)) { { if (1 +0) filli_err = "\"Index out of bounds\""; else filli_err = "((size_t)v2.u.f) <= strlen(*v1.u.s)"; } return 0; } }; if (v1.tag == VALUE_STRING) { char ** ss = (char **)zalloc(sizeof(char *)); *ss = stringdupn(*v1.u.s + (size_t)v2.u.f, 1); v1.u.s = ss; } else if (v1.tag == VALUE_ARRAY) { Value * vp = array_get(v1.u.a, v2.u.f); if (!vp) return 0; v1 = *vp; } else if (v1.tag == VALUE_DICT) v1 = dict_get_or_insert(v1.u.d, v2)->r; frame->vars[code[pc + (2)] + (0)] = v1;
        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_INDEX_LOC_INT (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_INDEX_LOC_INT; Value v1 = frame->vars[code[pc + (2)] + (0)]; Value v2 = val_float(code[pc + (1)]); { if (__builtin_expect(!(v1.tag == VALUE_STRING || v1.tag == VALUE_ARRAY || v1.tag == VALUE_DICT), 0)) { { if (+0) filli_err = ""; else filli_err = "v1.tag == VALUE_STRING || v1.tag == VALUE_ARRAY || v1.tag == VALUE_DICT"; } return 0; } }; if (v1.tag == VALUE_STRING || v1.tag == VALUE_ARRAY) { if (__builtin_expect(!(v2.tag == VALUE_FLOAT), 0)) { { if (1 +0) filli_err = "\"Unsupported index\""; else filli_err = "v2.tag == VALUE_FLOAT"; } return 0; } }; if (v1.tag == VALUE_DICT) { if (__builtin_expect(!(v2.tag == VALUE_FLOAT || v2.tag == VALUE_STRING || v2.tag == VALUE_FUNC || v2.tag == VALUE_NULL), 0)) { { if (1 +0) filli_err = "\"Unsupported dict key\""; else filli_err = "v2.tag == VALUE_FLOAT || v2.tag == VALUE_STRING || v2.tag == VALUE_FUNC || v2.tag == VALUE_NULL"; } return 0; } }; if (v1.tag == VALUE_STRING) { if (__builtin_expect(!(((size_t)v2.u.f) < strlen(*v1.u.s)), 0)) { { if (1 +0) filli_err = "\"Index out of bounds\""; else filli_err = "((size_t)v2.u.f) < strlen(*v1.u.s)"; } return 0; } }; if (v1.tag == VALUE_STRING) { { if (__builtin_expect(!((size_t)v2.u.f <= strlen(*v1.u.s)), 0)) { { if (1 +0) filli_err = "\"Index past end of string\""; else filli_err = "(size_t)v2.u.f <= strlen(*v1.u.s)"; } return 0; } }; *v1.u.s = stringdupn(*v1.u.s, strlen(*v1.u.s) + 1); frame->set_tgt_char = *v1.u.s + (size_t)v2.u.f; } else if (v1.tag == VALUE_ARRAY) frame->set_tgt_agg = array_get(v1.u.a, v2.u.f); else if (v1.tag == VALUE_DICT) frame->set_tgt_agg = &(dict_get_or_insert(v1.u.d, v2)->r);

        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame); } __attribute__((preserve_none)) size_t _handler_INST_LAMBDA (Program * prog, size_t pc, uint16_t * code, size_t * cache, Frame * frame, Frame * global_frame) { uint16_t op = INST_LAMBDA;
            Value v = val_func(code[pc + (1)]);
            Funcdef * f = (Funcdef *)zalloc(sizeof(Funcdef));
            *f = *v.u.fn;

            if (f->cap_count) f->cap_data = (Value **)zalloc(sizeof(Value *) * f->cap_count);
            for (size_t j = 0; j < f->cap_count; j++)
                f->cap_data[j] = (f->caps[j] < 0) ? frame->caps[-f->caps[j]] : &frame->vars[f->caps[j]];
            v.u.fn = f; { value_store(&frame->vars[code[pc + (5)] + (0)], (v)); } { uint32_t target = fi_mem_read_u32(code + (pc + 3)); frame->pc = target; pc = target; op = code[pc]; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame);; }

        pc += op >> 8; op = code[pc];; __attribute__((musttail)) return ((handler)(cache[pc]))(prog, pc, code, cache, frame, global_frame);


}

void register_intrinsic_func(const char * s)
{
    int16_t id = lex_ident_offset - insert_or_lookup_id(s, strlen(s));
    cs->funcs_reg[id] = (Funcdef) {1, 1, 0, 0, (uint16_t)id, 0, 0, prog.i, 0, 0, 0};
}
