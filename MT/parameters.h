/* parameters.h */
#ifndef PARAMETERS_H
#define PARAMETERS_H
#include "Matrix.h"
#include "Vector.h"
#include "RationalNumber.h"
#define co 1.1 // size coeficient

struct choice_data {
    static const char *vc[];
    static const char *mt[];
    static const int vcs;  // vectors size
    static const int mts;  // matrices size
    static const char *sz;
    static const char *op1;
    static const char *op2;
};



enum sizes { 
    cell_w = int(50*co),    // cell width
    cell_h = int(30*co),    // cell height
    cell_s = 7,             // spacing between cells
    ch_w = int(80*co),      // choice box width
    ch_h = int(30*co),      // choice box height
    spacing = 12,           // general spacing
    head_w = int(200*co),   // header width
    conf_w = int(75*co),   // confirm button   
    conf_h = int(30*co),    // confirm button
/////////////////////////////////////////////
    mes_w = int(400*co),    // message width
    mes_h = int(40*co),     // message height
    help_h = int(20*co),    // help height
    op_s = int(23*co),      // operation spacing
};

enum font_sizes {
    f_head = int(20*co),    // font head
    f_ch = int(18*co),      // font choice
    f_inp = int(15*co),     // font input
    f_conf = int(17*co),    // font confirm
    f_help = int(18*co),    // font help    
    f_mes = int(16*co)      // font message
};

struct win_data {
    Fl_Group *io;       // upper group
    Fl_Group *opers;    // down group
    Fl_Group *matinput; // group of input matrices
    Fl_Group *vecinput; // group of input vectors
    Choice *size;       // choice of matrices size
    MatChoice *mch;     // choice of matrix to edit
    VecChoice *vch;     // choice of vector to edit
    Fl_Multiline_Output *mes;   // field for messages
    TwoL<ConfButton*> confbuts; // confirm buttons
    TwoL<MatVecChoice*> matvecch;   // choice of matrix/vector
    TwoL<Choice*> vars;     // whe list of matrices or vectors variables changes
                            // there is need to refresh them 
    TwoL<Matrix<RationalNumber>> matrices;
    TwoL<Vector<RationalNumber>> vectors;

    
    Choice *oper1;  // first set of operators
    Choice *oper2;  // second set of operators
    Input *num;     // field of num input
    const char **mat_names;  // available matrices
    const char **vec_names;   // available vectors
    
    choice_data chd;
};
#endif // PARAMETERS_H
