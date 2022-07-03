#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//declare
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);


int main(void)
{
    string s = get_string("Text: ");
    //printf("%i letters\n", count_letters(s));
    //printf("%i words\n", count_words(s));
    //printf("%i sentences\n", count_sentences(s));

    float L =  count_letters(s) * 100.0/ count_words(s);
    float S =  count_sentences(s) * 100.0 / count_words(s);
    //result
    //result is 16 or higher -> Grade 16+
    //index number is less than 1 -> Before Grade 1
    float res = 0.0588 * L - 0.296 * S - 15.8;
    int ret = (int) (res + 0.5);
    //printf("L %f\n", L);
    //printf("S %f\n", S);
    if (ret < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (ret >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", ret);
    }


}

//count letters
int count_letters(string text)
{
    int cnt = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isdigit(text[i]) == 0)//is not digit
        {
            if (isalnum(text[i]) != 0)//is letter
            {
                cnt++;
            }
        }
    }

    return cnt;
}

//count words: any sequence of characters separated by spaces
int count_words(string text)
{
    int cnt = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]) != 0)//is not space
        {
            cnt++;
        }
    }

    return cnt+1;
}

//count sentences:  any occurrence of a period, exclamation point, or question mark
int count_sentences(string text)
{
    int cnt = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')//is
        {
            cnt++;
        }
    }

    return cnt;
}
