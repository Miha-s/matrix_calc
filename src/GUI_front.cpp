#include "../MT/GUI_front.h"

const int choice_data::vcs = 5;
const int choice_data::mts = 5;
const char *choice_data::sz = "2|3|4|5|6";
const char *choice_data::op1 = "+|-|*|-1|T|D";
const char *choice_data::op2 = "*|/";

const char *choice_data::vc[] = { "a", "b", "c", "d", "e", 0};
const char *choice_data::mt[] = { "A", "B", "C", "D", "E", 0 };

int launch(int argc, char **argv)
{
    win_data data;

    data.io = new Fl_Group(0, 0, 0, 0);
    data.opers = new Fl_Group(0, 0, 0, 0);

    Fl_Window *win = create_win(data);
    data.size->callback(size_callback, &data);

    win->show(argc, argv);
    return Fl::run();
}


Fl_Window *create_win(win_data &d)
{
    Fl_Window *win = new Fl_Window(0, 0, "Matrix");

    d.mat_names = d.chd.mt;
    d.vec_names = d.chd.vc;

    win->add(d.io);
    win->add(d.opers);

    Choice::setw(ch_w);
    Choice::seth(ch_h);
    Input::setw(cell_w);
    Input::seth(cell_h);
    ConfButton::setw(conf_w);
    ConfButton::seth(conf_h);
    HelpBox::setw(ch_w);
    HelpBox::seth(help_h);
    MatChoice::set(d.mat_names);
    VecChoice::set(d.vec_names);

    Choice::sett(f_ch);
    Input::sett(f_inp);
    ConfButton::sett(f_conf);
    HelpBox::sett(f_help);

    d.size = new Choice(0, 0);
    d.size->add(d.chd.sz);

    resize_win(win, 2, d);
    d.size->value(0);
    return win;
}


void apply_callbacks(win_data &data) 
{
    data.mch->callback(match_callback, &data);
    data.vch->callback(vecch_callback, &data);
    data.matvecch[0]->callback(var1_callback, &data);
    data.oper1->callback(oper_callback, &data);
    data.matvecch[1]->callback(var2_callback, &data);
    data.matvecch[3]->callback(var3_callback, &data);
    data.confbuts[0]->callback(conf1_callback, &data);
    data.confbuts[1]->callback(conf2_callback, &data);
    data.confbuts[2]->callback(conf3_callback, &data);
    

    data.matvecch[0]->do_callback();
    data.matvecch[3]->do_callback();
}
/*
    Fl_Group *io - this is group of matrix and vector input/output

    FL_Group *opers - this is group of mathimatical operations with.mat_names.vec_names
    plus here will be message about errors/actions
*/
void io_group(Fl_Window *win, int m_size, win_data &dat, Fl_Group *io, int io_w,
                int mt_gr_w, int mt_gr_h, int vc_gr_w);
void opers_group(Fl_Window *win, win_data &dat, Fl_Group *opers, int io_h);
void resize_win(Fl_Window *win, int m_size, win_data &dat)
{
    MatChoice::set(dat.mat_names);
    VecChoice::set(dat.vec_names);

    dat.confbuts.clear();
    dat.matvecch.clear();
    dat.vars.clear();
    dat.matrices.clear();
    dat.vectors.clear();
    for(int i = 0; i < dat.chd.mts; i++)
        dat.matrices.push(Matrix<RationalNumber>(m_size, m_size));
    for(int i = 0; i < dat.chd.vcs; i++) 
        dat.vectors.push(Vector<RationalNumber>(m_size));

    Fl_Group *io = dat.io;
    Fl_Group *opers = dat.opers;
    io->clear();
    opers->clear();

    int mt_gr_w = (m_size+1)*cell_s + m_size*cell_w;  // matrix group width
    int vc_gr_w = 2*cell_s + cell_w;                  // vector group width

    int mt_gr_h = (m_size+1)*cell_s + m_size*cell_h;
    int io_w = 6*spacing + mt_gr_w + vc_gr_w + 2*ch_w +conf_w;
    int io_h = 3*spacing + mt_gr_h + ch_h;

    int opers_w = spacing*2 + ch_w*4 + conf_w + 4*op_s;
    io_w = io_w > opers_w ? io_w : opers_w;

    io->resize(0, 0, io_w, io_h);

    int opers_h = 4*spacing + 2*ch_h + mes_h + help_h;
    opers->resize(0, io_h, io_w, opers_h);

    int win_w = io_w;
    int win_h = io_h + opers_h;

    win->resize(win->x_root(), win->y_root(), win_w, win_h);
    win->add(io);
    win->add(opers);

/*** input output group ***********************/
    io_group(win, m_size, dat, io, io_w, mt_gr_w, mt_gr_h, vc_gr_w);
/*** operations group *************************/
    opers_group(win, dat, opers, io_h);

    apply_callbacks(dat);
}

void io_group(Fl_Window *win, int m_size, win_data &dat, Fl_Group *io, int io_w,
                int mt_gr_w, int mt_gr_h, int vc_gr_w)
{
    // choice of size
    int head_x = (io_w-head_w-spacing-ch_w)/2;
    Choice *ch = dat.size;
    ch->resize(head_x+spacing+head_w, spacing, ch_w, ch_h);
    win->begin();

    // head text
    io->begin();

    Fl_Box *bx = new Fl_Box(head_x, spacing, head_w, ch_h, "MATRIX CALCULATOR");
    bx->labelsize(f_head);

    // chosing matrix
    int ch_y = 2*spacing+ch_h+(mt_gr_h-ch_h)/2;
    MatChoice *mch = new MatChoice(spacing, ch_y);
    mch->label("=");
    mch->align(FL_ALIGN_RIGHT);
    dat.mch = mch;

    // matrix input
    int mt_gr_y = 2*spacing + ch_h;
    int mt_gr_x = 2*spacing + ch_w;
    Fl_Group *mt_gr = new Fl_Group(mt_gr_x, mt_gr_y, mt_gr_w, mt_gr_h);
    int tmp_y = mt_gr_y + cell_s;
    for(int i = 0; i < m_size; i++) {
        int tmp_x = mt_gr_x + cell_s;
        for(int j = 0; j < m_size; j++) {
            Input *tmp1 = new Input(tmp_x, tmp_y);
            mt_gr->add(tmp1);
            tmp1->callback(inpm_callback, &dat);
            tmp1->when(FL_WHEN_ENTER_KEY);
            tmp_x += cell_w + cell_s;
        }
        tmp_y += cell_h + cell_s;
    }
    mt_gr->end();
    dat.matinput = mt_gr;

    // chosing vector
    int ch_x = 3*spacing + mt_gr_w + ch_w;
    VecChoice *vch = new VecChoice(ch_x, ch_y);
    vch->label("=");
    vch->align(FL_ALIGN_RIGHT);
    dat.vch = vch;

    // vector input
    int vc_gr_x = 4*spacing + 2*ch_w + mt_gr_w;
    int vc_gr_h = mt_gr_h;
    Fl_Group *vc_gr = new Fl_Group(vc_gr_x, mt_gr_y, vc_gr_w, vc_gr_h);
    tmp_y = mt_gr_y + cell_s;
    int tmp_x = vc_gr_x + cell_s;
    for(int i = 0; i < m_size; i++) {
        Input *vec1 = new Input(tmp_x, tmp_y);
        vc_gr->add(vec1);
        vec1->callback(inpv_callback, &dat);
        vec1->when(FL_WHEN_ENTER_KEY);
        tmp_y += cell_h + cell_s;
    }
    vc_gr->end();
    dat.vecinput = vc_gr;

    // confirm button
    int conf_x = vc_gr_x + vc_gr_w + spacing;
    int conf_y = (vc_gr_h - conf_h)/2 + spacing*2 + ch_h;
    ConfButton *cb = new ConfButton(conf_x, conf_y);
    dat.confbuts.push(cb);

    dat.vars += mch;
    dat.vars += vch;

    io->end();

}

void opers_group(Fl_Window *win, win_data &dat, Fl_Group *opers, int io_h)
{
    opers->begin();

    // message output
    Fl_Multiline_Output *mo = new Fl_Multiline_Output(spacing, io_h, mes_w, mes_h);
    mo->box(FL_FLAT_BOX);
    mo->value("Welcome my friend");
    mo->textsize(f_mes);
    mo->color(FL_BACKGROUND_COLOR);
    dat.mes = mo;

    // help messages
    int tmp_y = io_h + mes_h + spacing;
    int tmp_x = spacing;
    opers->add(new HelpBox(tmp_x, tmp_y, "Variable"));
    tmp_x += ch_w + op_s;
    opers->add(new HelpBox(tmp_x, tmp_y, "Operator"));
    tmp_x += ch_w + op_s;
    opers->add(new HelpBox(tmp_x, tmp_y, "Variable"));
    tmp_x += ch_w + op_s;
    opers->add(new HelpBox(tmp_x, tmp_y, "Result"));


    // choice of operations
    // first row
    tmp_y += help_h + spacing;
    tmp_x = spacing;
    MatVecChoice *mvch = new MatVecChoice(tmp_x, tmp_y);
    dat.matvecch.push(mvch);


    tmp_x += ch_w + op_s;
    Choice *ch = new Choice(tmp_x, tmp_y);
    ch->add(dat.chd.op1);
    ch->value(0);
    dat.oper1 = ch;

    tmp_x += ch_w + op_s;
    mvch = new MatVecChoice(tmp_x, tmp_y);
    mvch->label("=");
    mvch->align(FL_ALIGN_RIGHT);
    dat.matvecch.push(mvch);

    tmp_x += ch_w + op_s;
    mvch = new MatVecChoice(tmp_x, tmp_y);
    dat.matvecch.push(mvch);

    tmp_x += ch_w + op_s;
    ConfButton *cb = new ConfButton(tmp_x, tmp_y);
    dat.confbuts.push(cb);
    // second row
    tmp_y += ch_h + spacing;
    tmp_x = spacing;
    mvch = new MatVecChoice(tmp_x, tmp_y);
    dat.matvecch.push(mvch);

    tmp_x += ch_w + op_s;
    ch = new Choice(tmp_x, tmp_y);
    ch->add(dat.chd.op2);
    ch->value(0);
    dat.oper2 = ch;

    tmp_x += ch_w + op_s;
    Input *inp = new Input(tmp_x, tmp_y);
    inp->resize(tmp_x, tmp_y, ch_w, ch_h);
    dat.num = inp;
    inp->value("0");
    inp->label("=");
    inp->align(FL_ALIGN_RIGHT);

    tmp_x += ch_w + op_s;
    mvch = new MatVecChoice(tmp_x, tmp_y);
    dat.matvecch.push(mvch);

    tmp_x += ch_w + op_s;
    cb = new ConfButton(tmp_x, tmp_y);
    dat.confbuts.push(cb);


    for(int i = 0; i < dat.matvecch.get_size(); i++)
        dat.vars += dat.matvecch[i];
}
