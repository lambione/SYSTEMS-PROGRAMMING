#include <assert.h>

#include "../simplesets.h"

int main() {
    struct ss * s1;
    struct ss * s2;
    struct ss * s3;
    
    assert((s1 = ss_create_singleton()));
    assert((s2 = ss_create_singleton()));
    assert((s3 = ss_create_singleton()));

    assert(ss_disjoint(s1, s2));
    assert(ss_disjoint(s1, s3));
    assert(ss_disjoint(s3, s2));

    ss_merge(s2, s1);

    assert(!ss_disjoint(s1, s2));
    assert(ss_disjoint(s1, s3));
    assert(ss_disjoint(s3, s2));

    ss_merge(s2, s3);

    assert(!ss_disjoint(s1, s2));
    assert(!ss_disjoint(s1, s3));
    assert(!ss_disjoint(s3, s2));

    ss_merge(s1, s3);

    assert(!ss_disjoint(s1, s2));
    assert(!ss_disjoint(s1, s3));
    assert(!ss_disjoint(s3, s2));

    ss_destroy_all();
}
