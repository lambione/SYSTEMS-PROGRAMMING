#include <assert.h>

#include "../simplesets.h"

int main() {
    struct ss * s1;
    struct ss * s2;
    
    assert((s1 = ss_create_singleton()));
    assert((s2 = ss_create_singleton()));

    assert(!ss_disjoint(s1, s1));
    assert(!ss_disjoint(s2, s2));

    assert(ss_disjoint(s1, s2));
    assert(ss_disjoint(s2, s1));

    ss_merge(s1, s2);

    assert(!ss_disjoint(s1, s2));
    assert(!ss_disjoint(s2, s1));

    ss_destroy_all();

    assert((s1 = ss_create_singleton()));
    assert((s2 = ss_create_singleton()));

    assert(!ss_disjoint(s1, s1));
    assert(!ss_disjoint(s2, s2));

    assert(ss_disjoint(s1, s2));
    assert(ss_disjoint(s2, s1));

    ss_merge(s2, s1);

    assert(!ss_disjoint(s1, s2));
    assert(!ss_disjoint(s2, s1));

    ss_merge(s2, s1);

    assert(!ss_disjoint(s1, s2));
    assert(!ss_disjoint(s2, s1));

    ss_merge(s1, s2);

    assert(!ss_disjoint(s1, s2));
    assert(!ss_disjoint(s2, s1));

    ss_destroy_all();
}
