#ifndef UNION_H
#define UNION_H

template<typename Out, typename In>
__forceinline Out union_cast( In i ) {
    union Union {
        In i;
        Out o;
    };

    Union u = { i };
    return u.o;
}

#endif // UNION_H