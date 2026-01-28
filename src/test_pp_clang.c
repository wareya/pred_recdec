# 1 "src/test.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 423 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "src/test.c" 2

# 1 "C:/msys64/clang64/include/assert.h" 1 3
# 15 "C:/msys64/clang64/include/assert.h" 3
# 1 "C:/msys64/clang64/include/crtdefs.h" 1 3
# 10 "C:/msys64/clang64/include/crtdefs.h" 3
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
# 11 "C:/msys64/clang64/include/crtdefs.h" 2 3
# 16 "C:/msys64/clang64/include/assert.h" 2 3








__attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) __attribute__ ((__noreturn__)) _wassert(const wchar_t *_Message,const wchar_t *_File,unsigned _Line);
__attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) __attribute__ ((__noreturn__)) _assert (const char *_Message, const char *_File, unsigned _Line);
# 3 "src/test.c" 2
# 1 "C:/msys64/clang64/include/ctype.h" 1 3








# 1 "C:/msys64/clang64/include/corecrt_wctype.h" 1 3
# 31 "C:/msys64/clang64/include/corecrt_wctype.h" 3
  __attribute__ ((__dllimport__)) const unsigned short* __pctype_func(void);
# 45 "C:/msys64/clang64/include/corecrt_wctype.h" 3
  extern const unsigned short ** __imp__wctype;



  __attribute__ ((__dllimport__)) const wctype_t * __attribute__((__cdecl__)) __pwctype_func(void);
# 72 "C:/msys64/clang64/include/corecrt_wctype.h" 3
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) iswalpha(wint_t _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) iswupper(wint_t _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) iswlower(wint_t _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) iswdigit(wint_t _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) iswxdigit(wint_t _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) iswspace(wint_t _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) iswpunct(wint_t _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) iswalnum(wint_t _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) iswprint(wint_t _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) iswgraph(wint_t _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) iswcntrl(wint_t _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) iswascii(wint_t _C);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) isleadbyte(int _C);

  __attribute__ ((__dllimport__)) wint_t __attribute__((__cdecl__)) towupper(wint_t _C);
  __attribute__ ((__dllimport__)) wint_t __attribute__((__cdecl__)) towlower(wint_t _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) iswctype(wint_t _C,wctype_t _Type);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) __iswcsymf(wint_t _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) __iswcsym(wint_t _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) iswblank(wint_t _C);



  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _iswalpha_l(wint_t _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _iswupper_l(wint_t _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _iswlower_l(wint_t _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _iswdigit_l(wint_t _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _iswxdigit_l(wint_t _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _iswspace_l(wint_t _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _iswpunct_l(wint_t _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _iswalnum_l(wint_t _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _iswprint_l(wint_t _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _iswgraph_l(wint_t _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _iswcntrl_l(wint_t _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) wint_t __attribute__((__cdecl__)) _towupper_l(wint_t _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) wint_t __attribute__((__cdecl__)) _towlower_l(wint_t _C,_locale_t _Locale);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _isleadbyte_l(int _C,_locale_t _Locale);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _iswctype_l(wint_t _C,wctype_t _Type,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _iswblank_l(wint_t _C,_locale_t _Locale);



  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _iswcsymf_l(wint_t _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _iswcsym_l(wint_t _C,_locale_t _Locale);


  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) is_wctype(wint_t _C,wctype_t _Type);
# 10 "C:/msys64/clang64/include/ctype.h" 2 3
# 21 "C:/msys64/clang64/include/ctype.h" 3
  extern const unsigned char __newclmap[];
  extern const unsigned char __newcumap[];
  extern pthreadlocinfo __ptlocinfo;
  extern pthreadmbcinfo __ptmbcinfo;
  extern int __globallocalestatus;
  extern int __locale_changed;
  extern struct threadlocaleinfostruct __initiallocinfo;
  extern _locale_tstruct __initiallocalestructinfo;
  pthreadlocinfo __attribute__((__cdecl__)) __updatetlocinfo(void);
  pthreadmbcinfo __attribute__((__cdecl__)) __updatetmbcinfo(void);





  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) isalpha(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) isupper(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) islower(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) isdigit(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) isxdigit(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) isspace(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) ispunct(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) isalnum(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) isprint(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) isgraph(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) iscntrl(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) toupper(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _toupper(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) tolower(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _tolower(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _tolower_l(int _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _isctype(int _C,int _Type);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) isblank(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _isalpha_l(int _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _isupper_l(int _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _islower_l(int _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _isdigit_l(int _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _isxdigit_l(int _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _isspace_l(int _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _ispunct_l(int _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _isalnum_l(int _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _isprint_l(int _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _isgraph_l(int _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _iscntrl_l(int _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _toupper_l(int _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _isctype_l(int _C,int _Type,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _isblank_l(int _C,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) __isascii(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) __toascii(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) __iscsymf(int _C);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) __iscsym(int _C);
# 81 "C:/msys64/clang64/include/ctype.h" 3
__attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) ___mb_cur_max_func(void);
# 4 "src/test.c" 2
# 1 "C:/msys64/clang64/include/errno.h" 1 3
# 17 "C:/msys64/clang64/include/errno.h" 3
__attribute__ ((__dllimport__)) extern int *__attribute__((__cdecl__)) _errno(void);


errno_t __attribute__((__cdecl__)) _set_errno(int _Value);
errno_t __attribute__((__cdecl__)) _get_errno(int *_Value);
# 5 "src/test.c" 2
# 1 "C:/msys64/clang64/lib/clang/21/include/float.h" 1 3
# 27 "C:/msys64/clang64/lib/clang/21/include/float.h" 3
# 1 "C:/msys64/clang64/include/float.h" 1 3
# 272 "C:/msys64/clang64/include/float.h" 3
__attribute__ ((__dllimport__)) unsigned int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _controlfp (unsigned int _NewValue, unsigned int _Mask) ;
__attribute__((dllimport)) errno_t __attribute__((__cdecl__)) _controlfp_s(unsigned int *_CurrentState, unsigned int _NewValue, unsigned int _Mask);
__attribute__ ((__dllimport__)) unsigned int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _control87 (unsigned int _NewValue, unsigned int _Mask);





__attribute__ ((__dllimport__)) unsigned int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _clearfp (void);
__attribute__ ((__dllimport__)) unsigned int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _statusfp (void);
# 295 "C:/msys64/clang64/include/float.h" 3
void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fpreset (void);





__attribute__ ((__dllimport__)) int * __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __fpecode(void);
# 311 "C:/msys64/clang64/include/float.h" 3
__attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _chgsign (double _X);
__attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _copysign (double _Number,double _Sign);
__attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _logb (double);
__attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _nextafter (double, double);
__attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _scalb (double, long);

__attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _finite (double);
__attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fpclass (double);
__attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _isnan (double);


extern long double __attribute__((__cdecl__)) _chgsignl (long double);
# 28 "C:/msys64/clang64/lib/clang/21/include/float.h" 2 3
# 6 "src/test.c" 2
# 1 "C:/msys64/clang64/lib/clang/21/include/limits.h" 1 3
# 25 "C:/msys64/clang64/lib/clang/21/include/limits.h" 3
# 1 "C:/msys64/clang64/include/limits.h" 1 3
# 26 "C:/msys64/clang64/lib/clang/21/include/limits.h" 2 3
# 7 "src/test.c" 2
# 1 "C:/msys64/clang64/include/locale.h" 1 3
# 15 "C:/msys64/clang64/include/locale.h" 3
#pragma pack(push,_CRT_PACKING)
# 45 "C:/msys64/clang64/include/locale.h" 3
  struct lconv {
    char *decimal_point;
    char *thousands_sep;
    char *grouping;
    char *int_curr_symbol;
    char *currency_symbol;
    char *mon_decimal_point;
    char *mon_thousands_sep;
    char *mon_grouping;
    char *positive_sign;
    char *negative_sign;
    char int_frac_digits;
    char frac_digits;
    char p_cs_precedes;
    char p_sep_by_space;
    char n_cs_precedes;
    char n_sep_by_space;
    char p_sign_posn;
    char n_sign_posn;

    wchar_t* _W_decimal_point;
    wchar_t* _W_thousands_sep;
    wchar_t* _W_int_curr_symbol;
    wchar_t* _W_currency_symbol;
    wchar_t* _W_mon_decimal_point;
    wchar_t* _W_mon_thousands_sep;
    wchar_t* _W_positive_sign;
    wchar_t* _W_negative_sign;

  };
# 89 "C:/msys64/clang64/include/locale.h" 3
  int __attribute__((__cdecl__)) _configthreadlocale(int _Flag);
  char *__attribute__((__cdecl__)) setlocale(int _Category,const char *_Locale);
  __attribute__ ((__dllimport__)) struct lconv *__attribute__((__cdecl__)) localeconv(void);
  __attribute__ ((__dllimport__)) _locale_t __attribute__((__cdecl__)) _get_current_locale(void);
  __attribute__ ((__dllimport__)) _locale_t __attribute__((__cdecl__)) _create_locale(int _Category,const char *_Locale);
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _free_locale(_locale_t _Locale);
  _locale_t __attribute__((__cdecl__)) __get_current_locale(void);
  _locale_t __attribute__((__cdecl__)) __create_locale(int _Category,const char *_Locale);
  void __attribute__((__cdecl__)) __free_locale(_locale_t _Locale);

  __attribute__ ((__dllimport__)) unsigned int __attribute__((__cdecl__)) ___lc_codepage_func(void);


  unsigned int __attribute__((__cdecl__)) __mingw_filename_cp(void);



  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wsetlocale(int _Category,const wchar_t *_Locale);



  __attribute__ ((__dllimport__)) _locale_t __attribute__((__cdecl__)) _wcreate_locale(int _Category, const wchar_t *_Locale);
# 123 "C:/msys64/clang64/include/locale.h" 3
#pragma pack(pop)
# 8 "src/test.c" 2
# 1 "C:/msys64/clang64/include/math.h" 1 3
# 11 "C:/msys64/clang64/include/math.h" 3




struct _exception;

#pragma pack(push,_CRT_PACKING)
# 117 "C:/msys64/clang64/include/math.h" 3
  typedef union __mingw_dbl_type_t {
    double x;
    unsigned long long val;
    __extension__ struct {
      unsigned int low, high;
    } lh;
  } __mingw_dbl_type_t;

  typedef union __mingw_flt_type_t {
    float x;
    unsigned int val;
  } __mingw_flt_type_t;

  typedef union __mingw_ldbl_type_t
  {
    long double x;
    __extension__ struct {
      unsigned int low, high;
      int sign_exponent : 16;
      int res1 : 16;
      int res0 : 32;
    } lh;
  } __mingw_ldbl_type_t;




  extern double * __imp__HUGE;
# 156 "C:/msys64/clang64/include/math.h" 3
  struct _exception {
    int type;
    const char *name;
    double arg1;
    double arg2;
    double retval;
  };

  void __mingw_raise_matherr (int typ, const char *name, double a1, double a2,
         double rslt);
  void __mingw_setusermatherr (int (__attribute__((__cdecl__)) *)(struct _exception *));
  __attribute__ ((__dllimport__)) void __setusermatherr(int (__attribute__((__cdecl__)) *)(struct _exception *));
# 182 "C:/msys64/clang64/include/math.h" 3
  double __attribute__((__cdecl__)) sin(double _X);
  double __attribute__((__cdecl__)) cos(double _X);
  double __attribute__((__cdecl__)) tan(double _X);
  double __attribute__((__cdecl__)) sinh(double _X);
  double __attribute__((__cdecl__)) cosh(double _X);
  double __attribute__((__cdecl__)) tanh(double _X);
  double __attribute__((__cdecl__)) asin(double _X);
  double __attribute__((__cdecl__)) acos(double _X);
  double __attribute__((__cdecl__)) atan(double _X);
  double __attribute__((__cdecl__)) atan2(double _Y,double _X);
  double __attribute__((__cdecl__)) exp(double _X);
  double __attribute__((__cdecl__)) log(double _X);
  double __attribute__((__cdecl__)) log10(double _X);
  double __attribute__((__cdecl__)) pow(double _X,double _Y);
  double __attribute__((__cdecl__)) sqrt(double _X);
  double __attribute__((__cdecl__)) ceil(double _X);
  double __attribute__((__cdecl__)) floor(double _X);


  extern float __attribute__((__cdecl__)) fabsf (float x);
  extern long double __attribute__((__cdecl__)) fabsl (long double);
  extern double __attribute__((__cdecl__)) fabs (double _X);
# 242 "C:/msys64/clang64/include/math.h" 3
  double __attribute__((__cdecl__)) ldexp(double _X,int _Y);
  double __attribute__((__cdecl__)) frexp(double _X,int *_Y);
  double __attribute__((__cdecl__)) modf(double _X,double *_Y);
  double __attribute__((__cdecl__)) fmod(double _X,double _Y);

  void __attribute__((__cdecl__)) sincos (double __x, double *p_sin, double *p_cos);
  void __attribute__((__cdecl__)) sincosl (long double __x, long double *p_sin, long double *p_cos);
  void __attribute__((__cdecl__)) sincosf (float __x, float *p_sin, float *p_cos);



  int __attribute__((__cdecl__)) abs(int _X);
  long __attribute__((__cdecl__)) labs(long _X);



  double __attribute__((__cdecl__)) atof(const char *_String);
  double __attribute__((__cdecl__)) _atof_l(const char *_String,_locale_t _Locale);







  struct _complex {
    double x;
    double y;
  };


  double __attribute__((__cdecl__)) _cabs(struct _complex _ComplexA);
  double __attribute__((__cdecl__)) _hypot(double _X,double _Y);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _j0(double _X);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _j1(double _X);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _jn(int _X,double _Y);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _y0(double _X);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _y1(double _X);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _yn(int _X,double _Y);


  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _matherr (struct _exception *);
# 370 "C:/msys64/clang64/include/math.h" 3
typedef float float_t;
typedef double double_t;
# 405 "C:/msys64/clang64/include/math.h" 3
  extern int __attribute__((__cdecl__)) __fpclassifyl (long double);
  extern int __attribute__((__cdecl__)) __fpclassifyf (float);
  extern int __attribute__((__cdecl__)) __fpclassify (double);
# 518 "C:/msys64/clang64/include/math.h" 3
  extern int __attribute__((__cdecl__)) __isnan (double);
  extern int __attribute__((__cdecl__)) __isnanf (float);
  extern int __attribute__((__cdecl__)) __isnanl (long double);
# 605 "C:/msys64/clang64/include/math.h" 3
  extern int __attribute__((__cdecl__)) __signbit (double);
  extern int __attribute__((__cdecl__)) __signbitf (float);
  extern int __attribute__((__cdecl__)) __signbitl (long double);
# 662 "C:/msys64/clang64/include/math.h" 3
  extern float __attribute__((__cdecl__)) sinf(float _X);
  extern long double __attribute__((__cdecl__)) sinl(long double);

  extern float __attribute__((__cdecl__)) cosf(float _X);
  extern long double __attribute__((__cdecl__)) cosl(long double);

  extern float __attribute__((__cdecl__)) tanf(float _X);
  extern long double __attribute__((__cdecl__)) tanl(long double);
  extern float __attribute__((__cdecl__)) asinf(float _X);
  extern long double __attribute__((__cdecl__)) asinl(long double);

  extern float __attribute__((__cdecl__)) acosf (float);
  extern long double __attribute__((__cdecl__)) acosl (long double);

  extern float __attribute__((__cdecl__)) atanf (float);
  extern long double __attribute__((__cdecl__)) atanl (long double);

  extern float __attribute__((__cdecl__)) atan2f (float, float);
  extern long double __attribute__((__cdecl__)) atan2l (long double, long double);


  extern float __attribute__((__cdecl__)) sinhf(float _X);



  extern long double __attribute__((__cdecl__)) sinhl(long double);

  extern float __attribute__((__cdecl__)) coshf(float _X);



  extern long double __attribute__((__cdecl__)) coshl(long double);

  extern float __attribute__((__cdecl__)) tanhf(float _X);



  extern long double __attribute__((__cdecl__)) tanhl(long double);



  extern double __attribute__((__cdecl__)) acosh (double);
  extern float __attribute__((__cdecl__)) acoshf (float);
  extern long double __attribute__((__cdecl__)) acoshl (long double);


  extern double __attribute__((__cdecl__)) asinh (double);
  extern float __attribute__((__cdecl__)) asinhf (float);
  extern long double __attribute__((__cdecl__)) asinhl (long double);


  extern double __attribute__((__cdecl__)) atanh (double);
  extern float __attribute__((__cdecl__)) atanhf (float);
  extern long double __attribute__((__cdecl__)) atanhl (long double);



  extern float __attribute__((__cdecl__)) expf(float _X);



  extern long double __attribute__((__cdecl__)) expl(long double);


  extern double __attribute__((__cdecl__)) exp2(double);
  extern float __attribute__((__cdecl__)) exp2f(float);
  extern long double __attribute__((__cdecl__)) exp2l(long double);



  extern double __attribute__((__cdecl__)) expm1(double);
  extern float __attribute__((__cdecl__)) expm1f(float);
  extern long double __attribute__((__cdecl__)) expm1l(long double);


  extern float frexpf(float _X,int *_Y);



  extern long double __attribute__((__cdecl__)) frexpl(long double,int *);




  extern int __attribute__((__cdecl__)) ilogb (double);
  extern int __attribute__((__cdecl__)) ilogbf (float);
  extern int __attribute__((__cdecl__)) ilogbl (long double);


  extern float __attribute__((__cdecl__)) ldexpf(float _X,int _Y);



  extern long double __attribute__((__cdecl__)) ldexpl (long double, int);


  extern float __attribute__((__cdecl__)) logf (float);
  extern long double __attribute__((__cdecl__)) logl(long double);


  extern float __attribute__((__cdecl__)) log10f (float);
  extern long double __attribute__((__cdecl__)) log10l(long double);


  extern double __attribute__((__cdecl__)) log1p(double);
  extern float __attribute__((__cdecl__)) log1pf(float);
  extern long double __attribute__((__cdecl__)) log1pl(long double);


  extern double __attribute__((__cdecl__)) log2 (double);
  extern float __attribute__((__cdecl__)) log2f (float);
  extern long double __attribute__((__cdecl__)) log2l (long double);


  extern double __attribute__((__cdecl__)) logb (double);
  extern float __attribute__((__cdecl__)) logbf (float);
  extern long double __attribute__((__cdecl__)) logbl (long double);


  extern float __attribute__((__cdecl__)) modff (float, float*);
  extern long double __attribute__((__cdecl__)) modfl (long double, long double*);


  extern double __attribute__((__cdecl__)) scalbn (double, int);
  extern float __attribute__((__cdecl__)) scalbnf (float, int);
  extern long double __attribute__((__cdecl__)) scalbnl (long double, int);

  extern double __attribute__((__cdecl__)) scalbln (double, long);
  extern float __attribute__((__cdecl__)) scalblnf (float, long);
  extern long double __attribute__((__cdecl__)) scalblnl (long double, long);



  extern double __attribute__((__cdecl__)) cbrt (double);
  extern float __attribute__((__cdecl__)) cbrtf (float);
  extern long double __attribute__((__cdecl__)) cbrtl (long double);


  extern double __attribute__((__cdecl__)) hypot (double, double) ;
  extern float __attribute__((__cdecl__)) hypotf (float x, float y);



  extern long double __attribute__((__cdecl__)) hypotl (long double, long double);


  extern float __attribute__((__cdecl__)) powf(float _X,float _Y);



  extern long double __attribute__((__cdecl__)) powl (long double, long double);


  extern float __attribute__((__cdecl__)) sqrtf (float);
  extern long double sqrtl(long double);


  extern double __attribute__((__cdecl__)) erf (double);
  extern float __attribute__((__cdecl__)) erff (float);
  extern long double __attribute__((__cdecl__)) erfl (long double);


  extern double __attribute__((__cdecl__)) erfc (double);
  extern float __attribute__((__cdecl__)) erfcf (float);
  extern long double __attribute__((__cdecl__)) erfcl (long double);


  extern double __attribute__((__cdecl__)) lgamma (double);
  extern float __attribute__((__cdecl__)) lgammaf (float);
  extern long double __attribute__((__cdecl__)) lgammal (long double);

  extern int signgam;


  extern double __attribute__((__cdecl__)) tgamma (double);
  extern float __attribute__((__cdecl__)) tgammaf (float);
  extern long double __attribute__((__cdecl__)) tgammal (long double);


  extern float __attribute__((__cdecl__)) ceilf (float);
  extern long double __attribute__((__cdecl__)) ceill (long double);


  extern float __attribute__((__cdecl__)) floorf (float);
  extern long double __attribute__((__cdecl__)) floorl (long double);


  extern double __attribute__((__cdecl__)) nearbyint ( double);
  extern float __attribute__((__cdecl__)) nearbyintf (float);
  extern long double __attribute__((__cdecl__)) nearbyintl (long double);



extern double __attribute__((__cdecl__)) rint (double);
extern float __attribute__((__cdecl__)) rintf (float);
extern long double __attribute__((__cdecl__)) rintl (long double);


extern long __attribute__((__cdecl__)) lrint (double);
extern long __attribute__((__cdecl__)) lrintf (float);
extern long __attribute__((__cdecl__)) lrintl (long double);

__extension__ long long __attribute__((__cdecl__)) llrint (double);
__extension__ long long __attribute__((__cdecl__)) llrintf (float);
__extension__ long long __attribute__((__cdecl__)) llrintl (long double);



  extern double __attribute__((__cdecl__)) round (double);
  extern float __attribute__((__cdecl__)) roundf (float);
  extern long double __attribute__((__cdecl__)) roundl (long double);


  extern long __attribute__((__cdecl__)) lround (double);
  extern long __attribute__((__cdecl__)) lroundf (float);
  extern long __attribute__((__cdecl__)) lroundl (long double);
  __extension__ long long __attribute__((__cdecl__)) llround (double);
  __extension__ long long __attribute__((__cdecl__)) llroundf (float);
  __extension__ long long __attribute__((__cdecl__)) llroundl (long double);



  extern double __attribute__((__cdecl__)) trunc (double);
  extern float __attribute__((__cdecl__)) truncf (float);
  extern long double __attribute__((__cdecl__)) truncl (long double);


  extern float __attribute__((__cdecl__)) fmodf (float, float);
  extern long double __attribute__((__cdecl__)) fmodl (long double, long double);


  extern double __attribute__((__cdecl__)) remainder (double, double);
  extern float __attribute__((__cdecl__)) remainderf (float, float);
  extern long double __attribute__((__cdecl__)) remainderl (long double, long double);


  extern double __attribute__((__cdecl__)) remquo(double, double, int *);
  extern float __attribute__((__cdecl__)) remquof(float, float, int *);
  extern long double __attribute__((__cdecl__)) remquol(long double, long double, int *);


  extern double __attribute__((__cdecl__)) copysign (double, double);
  extern float __attribute__((__cdecl__)) copysignf (float, float);
  extern long double __attribute__((__cdecl__)) copysignl (long double, long double);
# 927 "C:/msys64/clang64/include/math.h" 3
  extern double __attribute__((__cdecl__)) nan(const char *tagp);
  extern float __attribute__((__cdecl__)) nanf(const char *tagp);
  extern long double __attribute__((__cdecl__)) nanl(const char *tagp);
# 938 "C:/msys64/clang64/include/math.h" 3
  extern double __attribute__((__cdecl__)) nextafter (double, double);
  extern float __attribute__((__cdecl__)) nextafterf (float, float);
  extern long double __attribute__((__cdecl__)) nextafterl (long double, long double);


  extern double __attribute__((__cdecl__)) nexttoward (double, long double);
  extern float __attribute__((__cdecl__)) nexttowardf (float, long double);
  extern long double __attribute__((__cdecl__)) nexttowardl (long double, long double);



  extern double __attribute__((__cdecl__)) fdim (double x, double y);
  extern float __attribute__((__cdecl__)) fdimf (float x, float y);
  extern long double __attribute__((__cdecl__)) fdiml (long double x, long double y);







  extern double __attribute__((__cdecl__)) fmax (double, double);
  extern float __attribute__((__cdecl__)) fmaxf (float, float);
  extern long double __attribute__((__cdecl__)) fmaxl (long double, long double);


  extern double __attribute__((__cdecl__)) fmin (double, double);
  extern float __attribute__((__cdecl__)) fminf (float, float);
  extern long double __attribute__((__cdecl__)) fminl (long double, long double);



  extern double __attribute__((__cdecl__)) fma (double, double, double);
  extern float __attribute__((__cdecl__)) fmaf (float, float, float);
  extern long double __attribute__((__cdecl__)) fmal (long double, long double, long double);
# 1021 "C:/msys64/clang64/include/math.h" 3
   __attribute__ ((__dllimport__)) float __attribute__((__cdecl__)) _copysignf (float _Number,float _Sign);
   __attribute__ ((__dllimport__)) float __attribute__((__cdecl__)) _chgsignf (float _X);
   __attribute__ ((__dllimport__)) float __attribute__((__cdecl__)) _logbf(float _X);
   __attribute__ ((__dllimport__)) float __attribute__((__cdecl__)) _nextafterf(float _X,float _Y);
   __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _finitef(float _X);
   __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _isnanf(float _X);
   __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _fpclassf(float _X);



   extern long double __attribute__((__cdecl__)) _chgsignl (long double);
# 1421 "C:/msys64/clang64/include/math.h" 3
#pragma pack(pop)
# 9 "src/test.c" 2
# 1 "C:/msys64/clang64/include/setjmp.h" 1 3
# 11 "C:/msys64/clang64/include/setjmp.h" 3
#pragma pack(push,_CRT_PACKING)
# 113 "C:/msys64/clang64/include/setjmp.h" 3
  typedef __attribute__ ((__aligned__ (16))) struct _SETJMP_FLOAT128 {
    __extension__ unsigned long long Part[2];
  } SETJMP_FLOAT128;


  typedef SETJMP_FLOAT128 _JBTYPE;

  typedef struct _JUMP_BUFFER {
    __extension__ unsigned long long Frame;
    __extension__ unsigned long long Rbx;
    __extension__ unsigned long long Rsp;
    __extension__ unsigned long long Rbp;
    __extension__ unsigned long long Rsi;
    __extension__ unsigned long long Rdi;
    __extension__ unsigned long long R12;
    __extension__ unsigned long long R13;
    __extension__ unsigned long long R14;
    __extension__ unsigned long long R15;
    __extension__ unsigned long long Rip;
    unsigned long MxCsr;
    unsigned short FpCsr;
    unsigned short Spare;
    SETJMP_FLOAT128 Xmm6;
    SETJMP_FLOAT128 Xmm7;
    SETJMP_FLOAT128 Xmm8;
    SETJMP_FLOAT128 Xmm9;
    SETJMP_FLOAT128 Xmm10;
    SETJMP_FLOAT128 Xmm11;
    SETJMP_FLOAT128 Xmm12;
    SETJMP_FLOAT128 Xmm13;
    SETJMP_FLOAT128 Xmm14;
    SETJMP_FLOAT128 Xmm15;
  } _JUMP_BUFFER;
# 202 "C:/msys64/clang64/include/setjmp.h" 3
  typedef _JBTYPE jmp_buf[16];



__attribute__ ((__dllimport__)) __attribute__ ((__noreturn__)) __attribute__ ((__nothrow__)) void __attribute__((__cdecl__)) longjmp(jmp_buf _Buf, int _Value);
# 216 "C:/msys64/clang64/include/setjmp.h" 3
__attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) __attribute__ ((__nothrow__,__returns_twice__)) _setjmp(jmp_buf _Buf, void *_Frame);

__attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) __attribute__ ((__nothrow__,__returns_twice__)) _setjmpex(jmp_buf _Buf, void *_Frame);







void * __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) mingw_getsp (void);





#pragma pack(pop)
# 10 "src/test.c" 2
# 1 "C:/msys64/clang64/include/signal.h" 1 3
# 10 "C:/msys64/clang64/include/signal.h" 3
# 1 "C:/msys64/clang64/include/pthread_signal.h" 1 3
# 11 "C:/msys64/clang64/include/signal.h" 2 3







  typedef int sig_atomic_t;
# 48 "C:/msys64/clang64/include/signal.h" 3
  typedef void (*__p_sig_fn_t)(int);
# 57 "C:/msys64/clang64/include/signal.h" 3
  extern void **__attribute__((__cdecl__)) __pxcptinfoptrs(void);


  __p_sig_fn_t __attribute__((__cdecl__)) signal(int _SigNum,__p_sig_fn_t _Func);
  int __attribute__((__cdecl__)) raise(int _SigNum);
