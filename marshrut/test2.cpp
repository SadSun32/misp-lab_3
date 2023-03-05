#include <UnitTest++/UnitTest++.h>
#include "marshrut.h"
using namespace std;
SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("БАГВЕД", marshrut(2).transform("АБВГДЕ"));
    }
    TEST(KeyLargerThanString) {
        CHECK_EQUAL("ЕДГВБА", marshrut(7).transform("АБВГДЕ"));
    }
    TEST(NotNumberKey) {
        CHECK_THROW(marshrut marshrut("МАМАПРИЕЗЖАЙ"), invalid_argument);
    }
    TEST(NotIntegerKey) {
        CHECK_THROW(marshrut marshrut(1.6), invalid_argument);
    }
    TEST(LessThanZeroKey) {
        CHECK_THROW(marshrut marshrut(-5), invalid_argument);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(marshrut marshrut(7 1), invalid_argument);
    }
    TEST(EmptyKey) {
        CHECK_THROW(marshrut marshrut(), invalid_argument);
    }
}
SUITE(TransformTest)
{
    TEST(UpCaseString) {
        CHECK_EQUAL("БАУДАРМХНАБИОНЬЛАРИХМ",
                    marshrut(2).transform("АБДУРАХМАНИБНАЛЬРАХИМ"));
    }
    TEST(LowCaseString) {
        CHECK_EQUAL("БАУДАРМХНАБИОНЬЛАРИХМ",
                    marshrut(2).transform("абдурахманибнальрахим"));
    }
    TEST(StringWithWhitespaceAndPunct) {
        CHECK_EQUAL("БАУДАРМХНАБИОНЬЛАРИХМ",
                    marshrut(2).transform("Абдурахман Ибн Аль-Рахим"));
    }
    TEST(EmptyString) {
        CHECK_THROW(marshrut(2).transform(""), cipher_error);
    }
    TEST(NoAlphaString) {
        CHECK_THROW(marshrut(2).transform("1337"), cipher_error);
    }
    TEST(MinimumString) {
        CHECK_EQUAL("АБДУРАХМАНИБНАЛЬРАХИМ",
                    marshrut(1).transform("АБДУРАХМАНИБНАЛЬРАХИМ"));
    }
}
int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
