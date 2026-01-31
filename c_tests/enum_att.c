
enum E {
    A __attribute__((asdf)) = 5,
    B,
    C __attribute__((asdf)),
};

enum E2 {
    A2 __attribute__((asdf)),
    B2,
    C2 __attribute__((asdf))
};

__attribute__((asdf)) enum __attribute__((asdf)) E3 {
    Q
} j;

