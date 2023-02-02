extern "C" {
#include "fp.h"
#include "mcl.h"
}
#include "mcl/bint.hpp"

const size_t N = 8;

extern void binary_inv(fp *x)
{
    fp u, v, r, s;
    
    fp_dec(&v.x, x);   // From Montgomery

    u = p; s.x = u512_1; r = fp_0;
    while (!(mcl::bint::cmpEqT<N>(u.x.c, u512_1.c)) && !(mcl::bint::cmpEqT<N>(v.x.c, u512_1.c))) {
        while ((u.x.c[0] & 1) == 0) {
            mcl::bint::shrT<N>(u.x.c, u.x.c, 1);        //u >>= 1;
            if ((r.x.c[0] & 1) == 1) 
                mcl::bint::addT<N>(r.x.c, r.x.c, p.x.c);    //r += p;
            mcl::bint::shrT<N>(r.x.c, r.x.c, 1);        //r >>= 1;
            
        }
        while ((v.x.c[0] & 1) == 0) {
            mcl::bint::shrT<N>(v.x.c, v.x.c, 1);        //v >>= 1;
            if ((s.x.c[0] & 1) == 1) 
                mcl::bint::addT<N>(s.x.c, s.x.c, p.x.c);    //s += p;
            mcl::bint::shrT<N>(s.x.c, s.x.c, 1);        //s >>= 1;    
        }
        if (mcl::bint::cmpGeT<N>(u.x.c, v.x.c)) {       //if (u >= v)
            mcl::bint::subT<N>(u.x.c, u.x.c, v.x.c);    //u -= v;
            mcl_sub(r.x.c, r.x.c, s.x.c);
        }
        else {
            mcl::bint::subT<N>(v.x.c, v.x.c, u.x.c);    //v -= u;
            mcl_sub(s.x.c, s.x.c, r.x.c);
        }
    }
    if (mcl::bint::cmpEqT<N>(u.x.c, u512_1.c))
        mcl_sub(x->x.c, r.x.c, p.x.c);
    else 
        mcl_sub(x->x.c, s.x.c, p.x.c);

    fp_enc(x, &x->x);   // To Montgomery
}