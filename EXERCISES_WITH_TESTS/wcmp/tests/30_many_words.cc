#include "basic_testing.h"

#include "../wcmp.h"

TEST(two_one1) {
    CHECK_CMP(wcmp("ab cd", "abcd"),==,-1);
    TEST_PASSED;
}

TEST(two_one2) {
    CHECK_CMP(wcmp("xyz", "x yz"),==,1);
    TEST_PASSED;
}

TEST(new_lines) {
    CHECK_CMP(wcmp("abc\nabc", "abc\nbcd"),==,-1);
    TEST_PASSED;
}

TEST(new_lines2) {
    CHECK_CMP(wcmp("abc\n\nbcd", "\n\nabc\nbcd\n"),==,0);
    TEST_PASSED;
}

TEST(new_lines3) {
    CHECK_CMP(wcmp("abc\n\nbcd-a", "\n\nabc\nbcd\n"),==,1);
    TEST_PASSED;
}

TEST(new_lines4) {
    CHECK_CMP(wcmp("abc\n\nbcd-a", "\n\nabc\nbcd\n"),==,1);
    TEST_PASSED;
}

TEST(misc_chars1) {
    CHECK_CMP(wcmp("/ciao/mamma-a", "  !!&ciao///-//mamma000000\n"),==,1);
    TEST_PASSED;
}

TEST(misc_chars2) {
    CHECK_CMP(wcmp("/ciao/mamma-a", "  !!&ciao///-//mamma000a000\n"),==,0);
    TEST_PASSED;
}

TEST(misc_chars3) {
    CHECK_CMP(wcmp("/ciao/mamma-a", "  !!&ciao///-//mamma000b000\n"),==,-1);
    TEST_PASSED;
}

TEST(same_concatenation_different_sequences1) {
    CHECK_CMP(wcmp("persona non grata", "personanongrata"),==,-1);
    TEST_PASSED;
}

TEST(same_concatenation_different_sequences2) {
    CHECK_CMP(wcmp("doit yourself", "do it yourself"),==,1);
    TEST_PASSED;
}

TEST(same_concatenation_different_sequences3) {
    CHECK_CMP(wcmp("Alpha Bravo Charlie", "Alpha Bravo C h a r l i e"),==,1);
    TEST_PASSED;
}

TEST(different_capitalization) {
    CHECK_CMP(wcmp("alpha bravo Charlie", "alpha bravO Charlie"),==,1);
    TEST_PASSED;
}

MAIN_TEST_DRIVER();
