
#include <iostream>
#include <cstdio>
using namespace std;

const int MAX_LINES = 10;
const int MAX_CHARS = 40;

static char* masterText = nullptr;


int myStrlen(const char* s)
{
    if (!s) return 0;
    int n = 0;
    while (s[n]) 
        n++;
    return n;
}

void myStrcpy(char* dst, const char* src)
{
    int i = 0;
    while (src[i]) { dst[i] = src[i]; i++; }
    dst[i] = '\0';
}

void myStrcat(char* dst, const char* src)
{
    int d = myStrlen(dst);
    int i = 0;
    while (src[i]) dst[d++] = src[i++];
    dst[d] = '\0';
}

int myStrcmp(const char* a, const char* b)
{
    int i = 0;
    while (a[i] && b[i] && a[i] == b[i]) 
        i++;
    return (unsigned char)a[i] - (unsigned char)b[i];
}

char* intToStr(int n, char* buf)
{
    if (n == 0) { buf[0] = '0'; buf[1] = '\0'; return buf; }
    char tmp[20]; int i = 0;
    while (n > 0) { tmp[i++] = (char)('0' + n % 10); n /= 10; }
    for (int j = 0; j < i; j++) buf[j] = tmp[i - 1 - j];
    buf[i] = '\0';
    return buf;
}

void buildPageHeader(char* out, int pageNum)
{
    char nb[20];
    intToStr(pageNum, nb);
    out[0] = '\0';
    myStrcat(out, "---------- Page ");
    myStrcat(out, nb);
    myStrcat(out, " ----------\n");
}


int countwordords(const char* text)
{
    if (!text) return 0;
    int count = 0; bool inWord = false;
    for (int i = 0; text[i]; i++)
    {
        if (text[i] != ' ') { if (!inWord) { count++; inWord = true; } }
        else inWord = false;
    }
    return count;
}

void extractwordord(const char* text, int wordIndex, char* outwordord)
{
    int current = 0; bool inWord = false;
    for (int i = 0; text[i]; )
    {
        if (text[i] != ' ')
        {
            if (!inWord)
            {
                if (current == wordIndex)
                {
                    int w = 0;
                    while (text[i] && text[i] != ' ') outwordord[w++] = text[i++];
                    outwordord[w] = '\0'; return;
                }
                current++; inWord = true;
            }
            else i++;
        }
        else { inWord = false; i++; }
    }
    outwordord[0] = '\0';
}


char** createPage()
{
    char** page = new char* [MAX_LINES];
    for (int i = 0; i < MAX_LINES; i++)
    {
        page[i] = new char[MAX_CHARS + 1];
        page[i][0] = '\0';
    }
    return page;
}

void freePage(char** page)
{
    for (int l = 0; l < MAX_LINES; l++) delete[] page[l];
    delete[] page;
}

void freeBook(char***& book, int totalPages)
{
    if (!book) return;
    for (int p = 0; p < totalPages; p++) freePage(book[p]);
    delete[] book;
    book = nullptr;
}


void rebuildBook(char***& book, int& totalPages)
{
    if (!masterText) return;
    freeBook(book, totalPages);

    int capacity = 4;
    book = new char** [capacity];
    book[0] = createPage();
    totalPages = 1;

    int p = 0, l = 0;
    int total = countwordords(masterText);

    for (int i = 0; i < total; i++)
    {
        char word[201];
        extractwordord(masterText, i, word);

        int wordLen = myStrlen(word);
        int lineLen = myStrlen(book[p][l]);
        bool needSpc = (lineLen > 0);
        int  needed = wordLen + (needSpc ? 1 : 0);

        if (lineLen + needed > MAX_CHARS)
        {
            l++;
            if (l == MAX_LINES)
            {
                p++; l = 0;
                if (p == capacity)
                {
                    int newCap = capacity * 2;
                    char*** tmp = new char** [newCap];
                    for (int x = 0; x < capacity; x++) tmp[x] = book[x];
                    delete[] book; book = tmp; capacity = newCap;
                }
                book[p] = createPage();
                totalPages = p + 1;
            }
            needSpc = false;
        }
        if (needSpc) myStrcat(book[p][l], " ");
        myStrcat(book[p][l], word);
    }
}


void insertIntoMaster(int wordIndex, const char* newText)
{
    if (!masterText) return;
    int total = countwordords(masterText);
    int extra = myStrlen(newText);
    int newSize = myStrlen(masterText) + extra + total + 20;

    char* result = new char[newSize];
    result[0] = '\0';
    bool inserted = false;

    for (int i = 0; i < total; i++)
    {
        if (i == wordIndex && extra > 0)
        {
            if (myStrlen(result) > 0) myStrcat(result, " ");
            myStrcat(result, newText);
            inserted = true;
        }
        char word[201];
        extractwordord(masterText, i, word);
        if (myStrlen(result) > 0) myStrcat(result, " ");
        myStrcat(result, word);
    }
    if (!inserted && extra > 0)
    {
        if (myStrlen(result) > 0) myStrcat(result, " ");
        myStrcat(result, newText);
    }
    delete[] masterText;
    masterText = result;
}

void removeWordsFromMaster(int start, int end)
{
    if (!masterText) return;
    int   total = countwordords(masterText);
    char* result = new char[myStrlen(masterText) + 5];
    result[0] = '\0';
    bool first = true;
    for (int i = 0; i < total; i++)
    {
        if (i < start || i > end)
        {
            char word[201];
            extractwordord(masterText, i, word);
            if (!first) myStrcat(result, " ");
            myStrcat(result, word);
            first = false;
        }
    }
    delete[] masterText;
    masterText = result;
}



int wordIndex(char***& book, int page, int line, int word)
{
    int index = 0;
    for (int p = 0; p < page; p++)
        for (int l = 0; l < MAX_LINES; l++)
            index += countwordords(book[p][l]);
    for (int l = 0; l < line; l++)
        index += countwordords(book[page][l]);
    return index + word;
}



void makeBook(char* text, char***& book, int& totalPages)
{
    if (masterText) 
        delete[] masterText;

    masterText = new char[myStrlen(text) + 1];
    myStrcpy(masterText, text);
    rebuildBook(book, totalPages);
}

void copy(char***& book, int& totalPages, int FromPage, int ToPage, int FromLine, int ToLine, int FromWord, int ToWord, char*& clipboard)
{
    (void)totalPages;
    int start = wordIndex(book, FromPage, FromLine, FromWord);
    int end = wordIndex(book, ToPage, ToLine, ToWord);

    if (clipboard) { delete[] clipboard; clipboard = nullptr; }
    clipboard = new char[myStrlen(masterText) + 5];
    clipboard[0] = '\0';

    for (int i = start; i <= end; i++)
    {
        char word[201];
        extractwordord(masterText, i, word);
        if (i != start) myStrcat(clipboard, " ");
        myStrcat(clipboard, word);
    }
}

void cut(char***& book, int& totalPages, int FromPage, int ToPage, int FromLine, int ToLine, int FromWord, int ToWord, char*& clipboard)
{
    int start = wordIndex(book, FromPage, FromLine, FromWord);
    int end = wordIndex(book, ToPage, ToLine, ToWord);

    copy(book, totalPages, FromPage, ToPage, FromLine, ToLine, FromWord, ToWord, clipboard);
    removeWordsFromMaster(start, end);
    rebuildBook(book, totalPages);
}

void paste(char***& book, int& totalPages, char* clipboard, int atpageage, int atlineine, int afterWord)
{
    if (!clipboard || myStrlen(clipboard) == 0)
        return;

    int index = wordIndex(book, atpageage, atlineine, afterWord + 1);
    insertIntoMaster(index, clipboard);
    rebuildBook(book, totalPages);
}

void Delete(char***& book, int& totalPages, int page)
{
    int start = 0;
    for (int p = 0; p < page; p++)
    {
        for (int l = 0; l < MAX_LINES; l++)
        {
            start += countwordords(book[p][l]);
        }
    }

    int wordsInPage = 0;
    for (int l = 0; l < MAX_LINES; l++)
    {
        wordsInPage += countwordords(book[page][l]);
    }

    if (wordsInPage > 0)
    {
        removeWordsFromMaster(start, start + wordsInPage - 1);
    }

    rebuildBook(book, totalPages);
}

void Delete(char***& book, int& totalPages, int page, int line)
{
    int start = wordIndex(book, page, line, 0);
    int words = countwordords(book[page][line]);
    if (words > 0)
        removeWordsFromMaster(start, start + words - 1);
    rebuildBook(book, totalPages);
}

void DeleteText(char***& book, int& totalPages, char* text)
{
    if (!masterText) 
        return;

    int   total = countwordords(masterText);
    char* result = new char[myStrlen(masterText) + 5];

    result[0] = '\0';
    bool first = true;
    for (int i = 0; i < total; i++)
    {
        char word[201];
        extractwordord(masterText, i, word);
        if (myStrcmp(word, text) != 0)
        {
            if (!first) myStrcat(result, " ");
            myStrcat(result, word);
            first = false;
        }
    }
    delete[] masterText;
    masterText = result;
    rebuildBook(book, totalPages);
}

void insert(char***& book, int& totalPages, int position)
{
    char*** temp = new char** [totalPages + 1];
    for (int p = 0; p <= position && p < totalPages; p++)
    {
        temp[p] = book[p];
    }
    temp[position + 1] = createPage();
    for (int p = position + 1; p < totalPages; p++)
    {
        temp[p + 1] = book[p];
    }
    delete[] book;
    book = temp;
    totalPages++;
}

void insert(char***& book, int& totalPages, int page, int position)
{
    (void)totalPages;
    for (int l = MAX_LINES - 1; l > position; l--)
    {
        myStrcpy(book[page][l], book[page][l - 1]);
    }
    book[page][position][0] = '\0';
}

void insertText(char***& book, int& totalPages, int page, int line, int word, char* text)
{
    int index = wordIndex(book, page, line, word + 1);
    insertIntoMaster(index, text);
    rebuildBook(book, totalPages);
}

void removeDoubleSpaces(char***& book, int& totalPages)
{
    if (!masterText) 
        return;

    int len = myStrlen(masterText);
    for (int i = 0; i < len - 1; i++)
    {
        if (masterText[i] == ' ' && masterText[i + 1] == ' ')
        {
            for (int j = i + 1; j < len; j++)
            {
                masterText[j - 1] = masterText[j];
            }
            masterText[--len] = '\0';
            i--;
        }
    }
    rebuildBook(book, totalPages);
}

void concatenateBooks(char***& book1, int totalPages1, char***& book2, int totalPages2, char***& newBook, int& newPages)
{
    (void)book1; (void)totalPages1;
    int extraSize = 0;
    for (int p = 0; p < totalPages2; p++)
    {
        for (int l = 0; l < MAX_LINES; l++)
        {
            extraSize += myStrlen(book2[p][l]) + 2;
        }
    }

    char* combined = new char[myStrlen(masterText) + extraSize + 10];
    combined[0] = '\0';
    if (masterText) 
        myStrcpy(combined, masterText);

    for (int p = 0; p < totalPages2; p++)
    {
        for (int l = 0; l < MAX_LINES; l++)
        {
            if (myStrlen(book2[p][l]) > 0)
            {
                if (myStrlen(combined) > 0) myStrcat(combined, " ");
                myStrcat(combined, book2[p][l]);
            }
        }
    }

    delete[] masterText;
    masterText = combined;
    rebuildBook(newBook, newPages);
}

char* toString(char***& book, int totalPages)
{
    int bufSize = totalPages * (60 + MAX_LINES * (MAX_CHARS + 2)) + 200;
    char* outpageut = new char[bufSize];
    outpageut[0] = '\0';
    for (int p = 0; p < totalPages; p++)
    {
        char header[60];
        buildPageHeader(header, p + 1);
        myStrcat(outpageut, header);
        for (int l = 0; l < MAX_LINES; l++)
            if (myStrlen(book[p][l]) > 0)
            {
                myStrcat(outpageut, book[p][l]);
                myStrcat(outpageut, "\n");
            }
    }
    return outpageut;
}


int main()
{
    char text[5000];
    cout << "Enter initial paragraph:\n";
    cin.getline(text, 5000);

    char*** book = nullptr;
    int totalPages = 0;
    makeBook(text, book, totalPages);

    char* clipboard = nullptr;
    int   choice = 0;

    do
    {
        cout << "           MENU\n";
        cout << "1.  Show Book\n";
        cout << "2.  Copy  (word range)\n";
        cout << "3.  Cut   (word range)\n";
        cout << "4.  Paste\n";
        cout << "5.  Insert Text\n";
        cout << "6.  Delete Specific Word\n";
        cout << "7.  Delete Page\n";
        cout << "8.  Delete Line\n";
        cout << "9.  Remove Double Spaces\n";
        cout << "10. Insert Empty Page\n";
        cout << "11. Insert Empty Line\n";
        cout << "12. Exit\n";
        cout << "\nChoice: ";
        cin >> choice;

        if (choice == 1)
        {
            char* out = toString(book, totalPages);
            cout << "\n" << out << "\n";
            delete[] out;
        }
        else if (choice == 2)
        {
            int fPage, fline, fword, tpage, tline, tword;
            cout << "From (Page Line Word) [0-based]: ";
            cin >> fPage >> fline >> fword;
            cout << "To   (Page Line Word) [0-based]: ";
            cin >> tpage >> tline >> tword;
            copy(book, totalPages, fPage, tpage, fline, tline, fword, tword, clipboard);
            if (clipboard) cout << "Copied: \"" << clipboard << "\"\n";
        }
        else if (choice == 3)
        {
            int fPage, fline, fword, tpage, tline, tword;
            cout << "From (Page Line Word) [0-based]: ";
            cin >> fPage >> fline >> fword;
            cout << "To   (Page Line Word) [0-based]: ";
            cin >> tpage >> tline >> tword;
            cut(book, totalPages, fPage, tpage, fline, tline, fword, tword, clipboard);
            if (clipboard) cout << "Cut done. Clipboard: \"" << clipboard << "\"\n";
        }
        else if (choice == 4)
        {
            int p, l, w;
            cout << "Paste at (Page Line AfterWord) [0-based]: ";
            cin >> p >> l >> w;
            paste(book, totalPages, clipboard, p, l, w);
            cout << "Pasted.\n";
        }
        else if (choice == 5)
        {
            int p, l, w;
            char newText[500];
            cout << "Position (Page Line AfterWord) [0-based]: ";
            cin >> p >> l >> w;
            cin.ignore();
            cout << "Text to insert: ";
            cin.getline(newText, 500);
            insertText(book, totalPages, p, l, w, newText);
            cout << "Inserted.\n";
        }
        else if (choice == 6)
        {
            char word[200];
            cin.ignore();
            cout << "Word to delete (all occurrences): ";
            cin.getline(word, 200);
            DeleteText(book, totalPages, word);
            cout << "Deleted.\n";
        }
        else if (choice == 7)
        {
            int p;
            cout << "Page index [0-based]: ";
            cin >> p;
            if (p >= 0 && p < totalPages) Delete(book, totalPages, p);
            else cout << "Invalid page.\n";
        }
        else if (choice == 8)
        {
            int p, l;
            cout << "Page Line [0-based]: ";
            cin >> p >> l;
            if (p >= 0 && p < totalPages && l >= 0 && l < MAX_LINES)
                Delete(book, totalPages, p, l);
            else cout << "Invalid page/line.\n";
        }
        else if (choice == 9)
        {
            removeDoubleSpaces(book, totalPages);
            cout << "Double spaces removed.\n";
        }
        else if (choice == 10)
        {
            int pos;
            cout << "Insert empty page after position [0-based]: ";
            cin >> pos;
            if (pos >= 0 && pos < totalPages) insert(book, totalPages, pos);
            else cout << "Invalid position.\n";
        }
        else if (choice == 11)
        {
            int p, pos;
            cout << "Page [0-based]: ";
            cin >> p;
            cout << "Insert empty line at position [0-based]: ";
            cin >> pos;
            if (p >= 0 && p < totalPages && pos >= 0 && pos < MAX_LINES)
                insert(book, totalPages, p, pos);
            else cout << "Invalid page/position.\n";
        }

    } while (choice != 12);

    freeBook(book, totalPages);
    if (clipboard)  delete[] clipboard;
    if (masterText) delete[] masterText;
    return 0;
}
