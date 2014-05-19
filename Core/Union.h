#ifndef UNION_H
#define UNION_H

template<typename Out, typename In>
inline Out union_cast( In i ) {
    union Union {
        In i;
        Out o;
    };

    Union u;
    u.i = i;
    return u.o;
}

#endif // UNION_H