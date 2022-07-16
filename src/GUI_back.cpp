#include "../MT/GUI_back.h"

void size_callback(Fl_Widget *w, void *data)
{
    Choice *ch = (Choice*)w;
    int s = ch->value() + 2;

    resize_win(ch->window(), s, *(win_data*)(data));
}

void var1_callback(Fl_Widget *w, void *data)
{
    Choice *ch = (Choice*)w;
    int idx = ch->value();
    win_data *d = (win_data *)data;
    Fl_Menu_Item* it = const_cast<Fl_Menu_Item*>(d->oper1->menu());
    if(idx < d->chd.mts) {
        it[2].activate();
        it[3].activate();
        it[4].activate();
        it[5].activate();
        d->matvecch[1]->matVec();
        d->matvecch[2]->matVec();
    }
    else {
        it[2].deactivate();
        it[3].deactivate();
        it[4].deactivate();
        it[5].deactivate();
        d->oper1->value(0);
        d->matvecch[1]->vecOnly();
        d->matvecch[2]->vecOnly();
    }
    oper_callback(d->oper1, d);
}

void oper_callback(Fl_Widget *w, void* data)
{
    Choice *ch = (Choice*)w;
    win_data *d = (win_data *)data;
    int idx1 = d->matvecch[0]->value();
    int idx2 = ch->value();
    if(idx2 <= 2) {
        d->matvecch[1]->activate();
        d->matvecch[2]->activate();
    }

    if(idx1 < d->chd.mts) {
        if(idx2 < 2) {
            d->matvecch[1]->matOnly();
            d->matvecch[2]->activate();
            d->matvecch[2]->matOnly();
        } else if(idx2 == 5) {
            d->matvecch[1]->deactivate();
            d->matvecch[2]->deactivate();
        } else if(idx2 > 2) {
            d->matvecch[1]->deactivate();
            d->matvecch[2]->activate();
            d->matvecch[2]->matOnly();
        } else {
            d->matvecch[1]->matVec();
            d->matvecch[2]->activate();
            d->matvecch[2]->matVec();
        }
    }

}

void var2_callback(Fl_Widget *w, void* data)
{
    Choice *ch = (Choice*)w;
    win_data *d = (win_data *)data;
    int idx = ch->value();
    int idx1 = d->matvecch[0]->value();
    if(idx1 < d->chd.mts) {
        if(idx < d->chd.mts) {
            d->matvecch[2]->matOnly();
        } else {
            d->matvecch[2]->vecOnly();
        }
    }
}

void var3_callback(Fl_Widget *w, void* data)
{
    Choice *ch = (Choice*)w;
    win_data *d = (win_data*)data;
    int idx = ch->value();
    if(idx < d->chd.mts) {
        d->matvecch[4]->matOnly();
    }
    else {
        d->matvecch[4]->vecOnly();
    }
}

int mat_inp(Fl_Group *mats, Matrix<RationalNumber> &m)
{
    int size = m.gety();
    Input *inp;
    int i = 0;
    int j = 0;
    try {
        for(; i < size; i++) {
            for(j = 0; j < size; j++) {
                inp = (Input*)mats->child(i*size + j);
                m[i][j].set(inp->value());
            }
        }
    }
    catch(rn_excep e) {
        return i*size + j;
    }
    return -1;
}
int vec_inp(Fl_Group *vecs, Vector<RationalNumber> &v)
{
    int size = v.gets();
    Input *inp;
    int i = 0;

    try {
        for(; i < size; i++) {
            inp = (Input*)vecs->child(i);
            v[i].set(inp->value());
        }
    }
    catch(rn_excep e) {
        return i;
    }

    return -1;
}

void conf1_callback(Fl_Widget *w, void* data)
{
    win_data *d = (win_data*)data;
    int idx = ((Choice*)d->mch)->value();

    if(mat_inp(d->matinput, d->matrices[idx]) != -1) {
        d->mes->value("Incorrect input of matrix");
        return ;
    }
    idx = ((Choice*)d->vch)->value();
    if(vec_inp(d->vecinput, d->vectors[idx]) != -1) {
        d->mes->value("Incorrect input of vectors");
        return ;
    }
    
    d->mes->value("OK");
}

void conf2_callback(Fl_Widget *w, void* data)
{
    win_data *d = (win_data*)data;
    MatVecChoice *fir = (MatVecChoice*)d->matvecch[0];
    MatVecChoice *sec = (MatVecChoice*)d->matvecch[1];
    MatVecChoice *res = (MatVecChoice*)d->matvecch[2];
    int idxf = fir->value();
    int idxs = sec->value();
    int idxr = res->value();
    int idxo = d->oper1->value();

    if(idxo > 2) {
        try {

        if(idxo == 3)
            d->matrices[idxr] = !d->matrices[idxf];
        else if(idxo == 4)
            d->matrices[idxr] = ~d->matrices[idxf];
        else {
            const char det_mes[] = {"Determinant is equal to: "};
            char det_mes2[sizeof(det_mes)+40];
            cpystr(det_mes, det_mes2);
            cpystr(d->matrices[idxf].determinant().getstr(), det_mes2 + sizeof(det_mes)-1);
            d->mes->value(det_mes2);
        }
        d->mch->do_callback();
        return ;

        }
        catch(mt_excep e) {
            if(e.what_type() == US)
                d->mes->value("Can't find inverse matrix\ndenterminant is equal to 0");
            return ;
        }
    }
    if(sec->getState() == s_vec) {
        int idxfv = idxf - d->chd.mts;
        if(idxo == 0) 
            d->vectors[idxr] = d->vectors[idxfv] + d->vectors[idxs];
        else 
            d->vectors[idxr] = d->vectors[idxfv] - d->vectors[idxs];
        d->vch->do_callback();
        return ;
    }
    if(sec->getState() == s_mat) {
        if(idxo == 0) 
            d->matrices[idxr] = d->matrices[idxf] + d->matrices[idxs];
        else 
            d->matrices[idxr] = d->matrices[idxf] - d->matrices[idxs];
        d->mch->do_callback();
        return ;
    }
    if(res->getState() == s_vec)
        d->vectors[idxr] = d->matrices[idxf] * d->vectors[idxs - d->chd.mts];
    else
        d->matrices[idxr] = d->matrices[idxf] * d->matrices[idxs]; 
    d->mch->do_callback();
    d->vch->do_callback();
}

void conf3_callback(Fl_Widget *w, void* data)
{
    win_data *d = (win_data*)data;
    MatVecChoice *fir = (MatVecChoice*)d->matvecch[3];
    MatVecChoice *res = (MatVecChoice*)d->matvecch[4];

    int idxf = fir->value();
    int idxr = res->value();
    int idxo = d->oper2->value();
    try {
        RationalNumber num;
        num.set(d->num->value());

        if(res->getState() == s_mat) {
            if(idxo == 0)
                d->matrices[idxr] = d->matrices[idxf] * num;
            else
                d->matrices[idxr] = d->matrices[idxf] / num;
            d->mch->do_callback();
        }
        else {
            if(idxo == 0)
                d->vectors[idxr] = d->vectors[idxf - d->chd.mts] * num;
            else
                d->vectors[idxr] = d->vectors[idxf - d->chd.mts] / num;
            d->vch->do_callback();
        }
    } 
    catch(rn_excep e) {
        if(e.what_type() == BS)
            d->mes->value("Incorrect input of number");
        else
            d->mes->value("Dividing by zero");
        return;
    }
    d->mes->value("Okkkk");
}

void mat_out(Fl_Group *mats, Matrix<RationalNumber> &m)
{
    Input *inp;
    int size = m.getx();
    for(int i = 0; i < size; i++) {
       for(int j = 0; j < size; j++) {
            inp = (Input*)mats->child(i*size + j);
            inp->value(m[i][j].getstr());
        }
    }
}

void match_callback(Fl_Widget *w, void* data)
{
    win_data *d = (win_data*)data;
    Choice *ch = (Choice*)w;
    int idx = ch->value();
    mat_out(d->matinput, d->matrices[idx]);
}

void vec_out(Fl_Group *vecs, Vector<RationalNumber> &v)
{
    Input *inp;
    int size = v.gets();
    for(int i = 0; i < size; i++) {
        inp = (Input*)vecs->child(i);
        inp->value(v[i].getstr());
    }
}

void vecch_callback(Fl_Widget *w, void* data)
{
    win_data *d = (win_data*)data;
    Choice *ch = (Choice*)w;
    int idx = ch->value();
    vec_out(d->vecinput, d->vectors[idx]);
}

void inpm_callback(Fl_Widget *w, void* data)
{
    Input *inp = (Input*)w;
    win_data *d = (win_data*)data;
    int idx = d->matinput->find(w);
    int s = d->matrices[0].getx();
    if(idx == s*s-1) {
        d->confbuts[0]->do_callback();
        d->confbuts[0]->take_focus();
    }
    else
        d->matinput->child(idx+1)->take_focus();
}

void inpv_callback(Fl_Widget *w, void* data)
{
    Input *inp = (Input*)w;
    win_data *d = (win_data*)data;
    int idx = d->vecinput->find(w);
    int s = d->matrices[0].getx();
    if(idx == s-1) {
        d->confbuts[0]->do_callback();
        d->confbuts[0]->take_focus();
    }
    else
        d->vecinput->child(idx+1)->take_focus();

}
