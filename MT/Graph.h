/* Graph.h */
#ifndef GRAPH_H
#define GRAPH_H
#include "FLH"

#define setdata(N, D, W) \
    static int set ## N (int D) { \
        return D > 0 ? W = D : 0; \
    }


class Choice : public Fl_Choice {
    static int w;
    static int h;
    static int f_s;
    static int font_color;

public:
    Choice(int x, int y, const char *lab = 0) : 
            Fl_Choice(x, y, w, h, lab) { textsize(f_s); }
    setdata(w, wid, w)
    setdata(h, hei, h)
    setdata(t, tex, f_s)

    virtual void apply() {}
};

class UnaryChoice : public Choice {
public:
    UnaryChoice(int x, int y) : Choice(x, y) { }

    void apply(const char **vec)
    {   
        clear();
        int i = 0;
        while(vec[i]) {
            add(vec[i]);
            i++;
        }
    }
};


enum { s_mat, s_vec, s_matvec };
class MatVecChoice : public Choice {
    static const char **mat;
    static const char **vec;
    friend class VecChoice;
    friend class MatChoice;
    int state;
    void addElems(const char **els);
public:
    MatVecChoice(int x, int y) : Choice(x, y) { matVec(); value(0); }
    int getState() { return state; }
    void matOnly();
  
    void vecOnly();

    void matVec();

    void apply();
};

class MatChoice : public UnaryChoice {
    static const char **mat;
public:
    MatChoice(int x, int y) : UnaryChoice(x, y) { apply(); }
    static void set(const char **m) { MatVecChoice::mat = mat = m; }
    void apply() { UnaryChoice::apply(mat); value(0); }
};

class VecChoice : public UnaryChoice {
    static const char **vec;
public:
    VecChoice(int x, int y) : UnaryChoice(x, y) { apply(); }
    static void set(const char **v) { MatVecChoice::vec = vec = v; }
    void apply() { UnaryChoice::apply(vec); value(0); }
};

class Input : public Fl_Input {
    static int w;
    static int h;
    static int f_s;
public:
    Input(int x, int y) : Fl_Input(x, y, w, h) { 
        textsize(f_s); value("0"); maximum_size(12); }
    setdata(w, wid, w)
    setdata(h, hei, h)
    setdata(t, tex, f_s)
};

class ConfButton : public Fl_Button {
    static int w;
    static int h;
    static int f_s;
public:
    ConfButton(int x, int y, const char *lab = "Confirm") : 
                                Fl_Button(x, y, w, h, lab) { labelsize(f_s); }
    setdata(w, wid, w)
    setdata(h, hei, h)
    setdata(t, tex, f_s)
};

class HelpBox : public Fl_Box {
    static int w;
    static int h;
    static int f_s;
public:
    HelpBox(int x, int y, const char *lab) : 
                    Fl_Box(x, y, w, h, lab) { labelsize(f_s); }
    setdata(w, wid, w)
    setdata(h, hei, h)
    setdata(t, tex, f_s)
};

#endif // GRAPH_H
