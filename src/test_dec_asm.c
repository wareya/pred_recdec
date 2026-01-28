
int x asm("bar2") = 3;
int y asm("bar2");
int z asm("bar2"), w asm("bar3");
int z1, w1 asm("bar3");
int z2 asm("bar3"), w2;

int main()
{
    int x asm("bar2") = 3;
    int y asm("bar2");
    int z asm("bar2"), w asm("bar3");
    int z1, w1 asm("bar3");
    int z2 asm("bar3"), w2;
}