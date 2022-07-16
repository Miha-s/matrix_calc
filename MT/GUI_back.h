/* GUI_back.h */
#ifndef GUI_BACK_H
#define GUI_BACK_H
#include "FLH"
#include "TwoL/TwoL.h"
#include "Graph.h"
#include "parameters.h"
#include "RationalNumber.h"
#include "Matrix.h"
#include "Vector.h"

// resize function from GUI_front
void resize_win(Fl_Window *win, int m_size, win_data &dat);

// callback to resize function
void size_callback(Fl_Widget *w, void *data);

// callback to choose opetors
void oper_callback(Fl_Widget *w, void* data);

void var1_callback(Fl_Widget *w, void *data);

void var2_callback(Fl_Widget *w, void* data);
        
void var3_callback(Fl_Widget *w, void* data);

void conf1_callback(Fl_Widget *w, void* data);

void conf2_callback(Fl_Widget *w, void* data);

void conf3_callback(Fl_Widget *w, void* data);

void match_callback(Fl_Widget *w, void* data);

void vecch_callback(Fl_Widget *w, void* data);

void inpm_callback(Fl_Widget *w, void* data);

void inpv_callback(Fl_Widget *w, void* data);
#endif // GUI_BACK_H
