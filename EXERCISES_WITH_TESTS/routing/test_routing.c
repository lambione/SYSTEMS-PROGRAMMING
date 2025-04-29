#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "routing.h"

#define assert_distance(p,d) check_distance((p),(d),__FILE__,__LINE__)

static void check_distance(const char * path, double expected,
			   const char * filename, int line) {
    double d = routing_total_distance(path);
    if (d != expected) {
	printf("%s:%d: error on path %s: computed=%lf expected=%lf\n",
	       filename, line, path, d, expected);
	abort();
    }
}

int main () {
    assert(routing_set_point("A", 1.0, 0.0));
    assert(routing_set_point("B", 2.0, 0.0));
    assert_distance("A,B", 1.0);
    assert_distance("A,B,A", 2.0);
    assert_distance("A,B,B,A,A,A,B,A", 4.0);
    assert_distance("A,A", 0.0);
    assert_distance("B,B", 0.0);
    assert_distance("B,C", -1.0);
    assert_distance("B", 0.0);
    assert_distance("A", 0.0);
    assert_distance("C", -1.0);

    routing_clear();

    assert_distance("A,B,B,A,A,A,B,A", -1.0);
    assert_distance("A,A", -1.0);
    assert_distance("B,B", -1.0);

    assert(routing_set_point("C", 1.0, 0.0));
    assert(routing_set_point("XYZ", 4.0, 0.0));
    assert(routing_set_point("ABC", 4.0, 4.0));
    assert(routing_set_point("IKJ", -4.0, 10.0));
    assert(routing_set_point("abcdefghi", 0.0, 0.0));

    assert_distance("A,A", -1.0);
    assert_distance("IKJ", 0.0);
    assert_distance("IKJ,IKJ", 0.0);
    assert_distance("IKJ,ABC,XYZ,C,ABC", 22.0);
    assert_distance("abcdefghi,C,ABC,IKJ", 16.0);

    routing_clear();
}
