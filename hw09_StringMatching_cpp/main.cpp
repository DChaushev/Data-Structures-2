/* 
 * File:   main.cpp
 * Author: Dimitar
 *
 * Created on June 9, 2015, 10:52 AM
 */

#include <iostream>
#include <string.h>
#include "BoyerMoore.hpp"

using namespace std;

void boyer_moore_search(BoyerMoore * bm, const char* text, int text_length) {

    int j = 0;
    while (j <= text_length - bm->pattern_length) {

        int i = bm->pattern_length - 1;
        while (i >= 0 && bm->pattern[i] == text[i + j]) --i;
        if (i < 0) {
            cout << j << endl;
            j += bm->good_suffix_rule_table[0];
        } else {
            int good = bm->good_suffix_rule_table[i];
            int bad = bm->get_bad_char(text[i + j]) - bm->pattern_length + i + 1;
            j += max(good, bad);
        }
    }
}

/*
 * 
 */
int main(int argc, char** argv) {

    const char * text = "http://www.example.com/something/index.html\nhttps://example.com/somethingelse/\nftp://1.2.3.4/qweqweqweqwe/qweqweqweqwe/q\nftp://aaa:bbbbbb@example.com/1/2/3\nhttps://sub1.sub2.example.org/1/2/file.html\nhttp://blog.example.com/2015/very_important_stuff/";
    const char * textLorem = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";

    BoyerMoore * bm1 = new BoyerMoore("example.com");
    boyer_moore_search(bm1, text, strlen(text));
    delete bm1;

    cout << "---------------" << endl;

    BoyerMoore * bm2 = new BoyerMoore("Lorem");
    boyer_moore_search(bm2, textLorem, strlen(textLorem));
    delete bm2;

    cout << "---------------" << endl;

    BoyerMoore * bm3 = new BoyerMoore("Ipsum");
    boyer_moore_search(bm3, textLorem, strlen(textLorem));
    bm3->test();
    delete bm3;

    return 0;
}
