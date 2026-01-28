typedef struct parserdestroyer { int x; } parserdestroyer;
typedef struct parserdestroyer (__attribute__((__cdecl__)) *_onexit_t)(void);

typedef void (*_badfptrtype)(int);
typedef int foobarred;
void x()
{
    static foobarred volatile foobarred;
    foobarred = 5;
}
typedef struct foo { int asdf; } foo;
void asdfasdf { { int foo; } }
void blah(foo x, int foo);
void blah(foo x, int foo) { }
void blah2(int foo) { foo = 5; }

void blah(int foo) {
  foo = 1;
  //int foo; // error
  for (int foo;;)
  {
    int foo;
    {
      foo = 5;
      typedef int foo;
      foo x;
      {
        int foo;
        foo = 5;
      }
    }
  }
  {
    typedef struct foo foo;
  }
}
foo x;

typedef int Q;
typedef int T;
void foo2(
    int T
    //, void(*fptr)(const T x) // mandatory error
)
{
  T = 5;
  *&T = 5;
  *&*&*&*&*&*&*&*&*&*&T = 5;
  Q Q;
}


T f(T (*T)(T x));


T f(T (*T)(T x))
{
    int q = (T)(5);
}

T f3(x)
    T (*x)(T x); // invalid: previous T was a type, not a name
{
    // ...
}
