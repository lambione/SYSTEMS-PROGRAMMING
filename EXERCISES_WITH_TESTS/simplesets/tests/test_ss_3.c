#include <assert.h>

#include "../simplesets.h"

int main() {
    const unsigned int N = 1024;
    struct ss * S[N];
    
    for (int i = 0; i < N; ++i) {
	S[i] = ss_create_singleton();
	assert(S[i]);
    }

    for (int i = 0; i < N; ++i)
	assert(!ss_disjoint(S[i], S[i]));

    for (int i = 0; i < N; ++i)
	for (int j = i + 1; j < N; ++j)
	    assert(ss_disjoint(S[i], S[j]));

    for (int i = N/2; i < N; ++i)
	ss_merge(S[i], S[i/2]);

    for (int i = N/2; i < N - 2; i += 2) {
	assert(!ss_disjoint(S[i], S[i+1]));
	assert(ss_disjoint(S[i], S[i+2]));
	assert(ss_disjoint(S[i+1], S[i+2]));
    }

    for (int i = 1; i < N/2; ++i) {
	assert(ss_disjoint(S[i],S[i/2]));
	ss_merge(S[i], S[i/2]);
    }
    
    for (int i = 0; i < N; ++i)
	for (int j = i + 1; j < N; ++j)
	    assert(!ss_disjoint(S[i], S[j]));

    ss_destroy_all();
}
