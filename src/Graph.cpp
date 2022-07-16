#include "../MT/Graph.h"

#define setdata(N, D, W) \
    static int set ## N (int D) { \
        return D > 0 ? W = D : 0; \
    }

void MatVecChoice::addElems(const char **els)
{
    int i = 0; 
    while(els[i]) {
        add(els[i]);
        i++;
    }
    value(0);
}

void MatVecChoice::matOnly()
{
    int idx = value();
    state = s_mat;
    clear();
    addElems(mat);
    value(idx);
}
void MatVecChoice::vecOnly()
{
    int idx = 0;
    if(state == s_matvec)
        idx = value();
    state = s_vec;
    clear();
    addElems(vec);
    value(idx);
}

void MatVecChoice::matVec()
{ 
    int idx = value();
    clear();
    addElems(mat);
    if(state == s_vec)
        idx += size() - 1;
    state = s_matvec;
    addElems(vec);
    value(idx);
}

void MatVecChoice::apply()
{
    switch(state) {
        case s_vec:
            vecOnly();
            break;
        case s_mat:
            matOnly();
            break;
        default:
            matVec();
            break;
    }
}

int Choice::w = 0;
int Choice::h = 0;
int Choice::f_s = 16;
int Choice::font_color = 0;

const char** MatVecChoice::mat = 0;
const char** MatVecChoice::vec = 0;

const char** MatChoice::mat = 0;

const char** VecChoice::vec = 0;

int Input::w = 0;
int Input::h = 0;
int Input::f_s = 16;

int ConfButton::w = 0;
int ConfButton::h = 0;
int ConfButton::f_s = 16;

int HelpBox::w = 0;
int HelpBox::h = 0;
int HelpBox::f_s = 16;


