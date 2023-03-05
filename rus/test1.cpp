#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"
using namespace std;
SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("БВГБВ", modAlphaCipher("БВГ").encrypt("ААААА"));
    }
    TEST(LongKey) {
        CHECK_EQUAL("БВГДЕ",modAlphaCipher("БВГДЕЖЗИЙК").encrypt("ААААА"));
    }
    TEST(LowCaseKey) {
        CHECK_EQUAL("БВГБВ", modAlphaCipher("бвг").encrypt("ААААА"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp("Б1"), cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("Б,В"), cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("Б В"), cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""), cipher_error);
    }
}
SUITE(EncryptTest)
{
    TEST(UpCaseString) {
        CHECK_EQUAL("БВЕФСБЦНБОЙВОБМЭСБЦЙН", modAlphaCipher("Б").encrypt("АБДУРАХМАНИБНАЛЬРАХИМ"));
    }
    TEST(LowCaseString) {
        CHECK_EQUAL("БВЕФСБЦНБОЙВОБМЭСБЦЙН", modAlphaCipher("Б").encrypt("абдурахманибнальрахим"));
    }
    TEST(StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("БВЕФСБЦНБОЙВОБМЭСБЦЙН", modAlphaCipher("Б").encrypt("Абдурахман Ибн Аль-Рахим"));
    }
    TEST(EmptyString) {
        CHECK_THROW(modAlphaCipher("Б").encrypt(""), cipher_error);
    }
    TEST(NoAlphaString) {
        CHECK_THROW(modAlphaCipher("Б").encrypt("1337"), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("ЯАГТПЯФЛЯМЗАМЯКЫПЯФЗЛ", modAlphaCipher("Я").encrypt("АБДУРАХМАНИБНАЛЬРАХИМ"));
    }
}
SUITE(DecryptText)
{
    TEST(UpCaseString) {
        CHECK_EQUAL("АБДУРАХМАНИБНАЛЬРАХИМ", modAlphaCipher("Б").decrypt("БВЕФСБЦНБОЙВОБМЭСБЦЙН"));
    }
    TEST(LowCaseString) {
        CHECK_EQUAL("АБДУРАХМАНИБНАЛЬРАХИМ", modAlphaCipher("Б").decrypt("бвефсбцнбойвобмэсбцйн"));
    }
    TEST(StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("АБДУРАХМАНИБНАЛЬРАХИМ", modAlphaCipher("Б").decrypt("Бвефсбцнбо Йво Бмэ-Сбцйн"));
    }
    TEST(EmptyString) {
        CHECK_THROW(modAlphaCipher("Б").decrypt(""), cipher_error);
    }
    TEST(NoAlphaString) {
        CHECK_THROW(modAlphaCipher("Б").decrypt("1337"), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("АБДУРАХМАНИБНАЛЬРАХИМ", modAlphaCipher("Я").decrypt("ЯАГТПЯФЛЯМЗАМЯКЫПЯФЗЛ"));
    }
}
int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
