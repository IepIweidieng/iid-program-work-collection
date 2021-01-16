/* sink.cpp
Demonstration of the pseudo-qualifier `sink` (`writeonly`),
   with the cv-qualification conversion rules in C++
*/

#undef sink
#if __ARMCC_VERSION
  #define sink  __writeonly
#elif defined __GNUC__
  #define sink  __attribute__((/* Empty */))
#else
  #define sink  /* For documentation only */
#endif

#if __cplusplus
extern "C" {
#endif

/* Some practical usages of `sink` */
/* Denotes `var` as an output pointer/reference parameter
`sink <T>* <var>`/`sink <T>& <var>`
*/
typedef struct Scr_data {int y; int x;} Scr_data;
void scr_getyx(const Scr_data* pscr, sink int* py, sink int* px)
{
    *py = pscr->y;
    *px = pscr->x;
}

/* Denotes `var` as a don't-care variable
`sink <T> <var>`; `<T> sink <var>`
*/
int src_vgety(const Scr_data* pscr)
{
    sink int x;
    int y;
    scr_getyx(pscr, &y, &x);
    return y;
}

/* Prevents an unused variable `var` from being used
`const sink <T> <var>`; `<T> const sink <var>`:
*/
extern int func(int x);
int func(const sink int x_unused)
{
    /* LARGE_CHUNK_OF_CODE */
    sizeof(x_unused);  // Prohibited
    /* ANOTHER_LARGE_CHUNK_OF_CODE */
    return 0;
}

int* f2(void)
{
    int i = 0;
    const int ci = 0;  // Writing is prohibited
    // ci = 42;  // Prohibited
    // ++ci;  // Prohibited
    sink int si = 0;  // Read is prohibited
    // i = si;  // Prohibited
    // ++si;  // Prohibited
    const sink int csi = 0;  // Both writing and read are prohibited
    // csi = 42;  // Prohibited
    // i = csi;  // Prohibited
    // ++csi;  // Prohibited

    int* p = &i;
    // p -> i
    int* const cp = &i;  // Writing is prohibited
    // [const] cp => i
    int* sink sp = &i;  // Read is prohibited
    // [sink] sp -/> i
    // *sp;  // Dereference is also prohibited
    int* const sink csp = &i;  // Both writing and read are prohibited
    // [const sink] csp =/> i

    const int* pc = &i;  // Allowed
    // pc -> [const] i
    sink int* ps = &i;  // Allowed
    // ps -> [sink] i
    ps[0] = 0;
    // i = ps[0];  // Read is prohibited
    const sink int* pcs = &i;  // Allowed
    // pcs -> [const sink] i
    // pcs[0] = 0;  // Writing is prohibited
    // i = pcs[0];  // Read is prohibited
    
    // p = &ci;  // Prohibited
    // p = &si;  // Prohibited
    // p = &csi;  // Prohibited
    pc = &ci;
    // pc = &si;  // Prohibited
    // pc = &csi;  // Prohibited
    // ps = &ci;  // Prohibited
    ps = &si;
    // ps = &csi;  // Prohibited
    pcs = &csi;
    pcs = &ci;  // Allowed
    pcs = &si;  // Allowed
 
    int** pp = &p;
    // pp -> p -> i

    int* sink* psp = &p;  // Allowed
    // psp -> [sink] p -/> i
    *psp = 0;
    // p = *psp;  // Read is prohibited
    // **psp;  // Dereference is also prohibited

    // sink int** pps = &p;  // Prohibited
    // pps -> p -> [sink] i, but p -> i
    // If allowed, `p` can be modified to point to `sink int` via `pps` without a cast:
    // `*pps = &si;`  // p == &si;
    // `i = *p;`  // Read via `p` is allowed
    sink int** pps = &ps;
    // pps -> ps -> [sink] i, and ps -> [sink] i
    **pps = 0;
    // i = **pps;  // Read is prohibited
    
    sink int* const* pcps = &p;  // Allowed
    // pcps -> [const] p => [sink] i, but p -> i
    // `p` cannot be modified via `pcps` without a cast

    // sink int* sink* psps = &p;  // Prohibited
    // psps -> [sink] p -/> [sink] i, but p -> i
    sink int* sink* psps = &ps;  // Allowed
    // psps -> [sink] ps -/> [sink] i, and ps -> [sink] i
    *psps = &i;
    // pcs = *psps;  // Read is prohibited
    // **psps;  // Dereference is also prohibited

    sink int* const sink* pcsps = &p;  // Allowed
    // pcsps -> [const sink] p =/> [sink] i
    // *pcsps = &i;  // Writing is prohibited
    // pcs = *pcsps;  // Read is prohibited
    // **pcsps;  // Dereference is also prohibited

    // return si;  // Returning is prohibited
    // return *ps;  // Returning is prohibited
    return ps;
}

#if __cplusplus
}  // extern "C"
#endif

int main(void)  { j}
