#include <assert.h>

#include "../simplesets.h"

int main() {
    struct ss * s1;
    struct ss * s2;
    
    assert((s1 = ss_create_singleton()));
    assert((s2 = ss_create_singleton()));
    ss_destroy_all();
}
