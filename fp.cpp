#include "fp.h"
#include "mcl.h"
#include "mcl/bint.hpp"
#include<iostream>

const size_t N = 8;
fp fpone;


void printttt(u512 const *x)
{
    for (size_t i = 63; i < 64; --i)
        printf("%02hhx", i[(unsigned char *) x->c]);
}

extern void binary_inv(fp *x)
{
    fp u, v, r, s;
    fpone.x.c[0]=1;
    u512 ppp={0x1b81b90533c6c87b, 0xc2721bf457aca835, 0x516730cc1f0b4f25, 0xa7aac6c567f35507, 0x5afbfcc69322c9cd, 0xb42d083aedc88c42, 0xfc8ab0d15e3e4c4a, 0x65b48e8f740f89bf};
    u.x = ppp; v = *x; s = fpone; r.x={};
    while (!(mcl::bint::cmpEqT<N>(u.x.c, fpone.x.c)) && !(mcl::bint::cmpEqT<N>(v.x.c, fpone.x.c))) {
        while ((u.x.c[0] & 1) == 0) {
            mcl::bint::shrT<N>(u.x.c, u.x.c, 1);        //u >>= 1;
            
            //std::cout<< r.x.c[7] <<std::endl;
            if ((r.x.c[0] & 1) == 1) {
                mcl::bint::addT<N>(r.x.c, r.x.c, ppp.c);    //r += p;
            }
            mcl::bint::shrT<N>(r.x.c, r.x.c, 1);        //r >>= 1;
             printttt(&r.x); printf("\n");
            
        }
        while ((v.x.c[0] & 1) == 0) {
            mcl::bint::shrT<N>(v.x.c, v.x.c, 1);        //v >>= 1;
            if ((s.x.c[0] & 1) == 1) {
                mcl::bint::addT<N>(s.x.c, s.x.c, ppp.c);    //s += p;
            }
            mcl::bint::shrT<N>(s.x.c, s.x.c, 1);        //s >>= 1;
            
        }
        if (mcl::bint::cmpGeT<N>(u.x.c, v.x.c)) {       //if (u >= v)
            mcl::bint::subT<N>(u.x.c, u.x.c, v.x.c);    //u -= v;
            
            if (mcl::bint::subT<N>(r.x.c, r.x.c, s.x.c))//r -= s;
                        mcl::bint::addT<N>(r.x.c, r.x.c, ppp.c);
            

        }
        else {
            mcl::bint::subT<N>(v.x.c, v.x.c, u.x.c);    //v -= u;
            if (mcl::bint::subT<N>(s.x.c, s.x.c, r.x.c))    //s -= r;
                    mcl::bint::addT<N>(s.x.c, s.x.c, ppp.c);
        }

    }
    if (mcl::bint::cmpEqT<N>(u.x.c, fpone.x.c)) {
        if (mcl::bint::subT<N>(x->x.c, r.x.c, ppp.c))    //s -= r;
                    mcl::bint::addT<N>(x->x.c, x->x.c, ppp.c);
    }
    else {
        if (mcl::bint::subT<N>(x->x.c, s.x.c, ppp.c))    //s -= r;
                    mcl::bint::addT<N>(x->x.c, x->x.c, ppp.c);
    }
}