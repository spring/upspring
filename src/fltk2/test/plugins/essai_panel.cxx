// generated by Fast Light User Interface Designer (fluid) version 2.0000

#include "essai_panel.h"

Fl_Group *Essai=(Fl_Group *)0;

Fl_Group* make_window() {
  Fl_Group* w;
  { Fl_Group* o = Essai = new Fl_Group(0, 0, 258, 74);
    w = o;
    { Fl_Slider* o = new Fl_Slider(20, 20, 225, 20, "Major tick precision");
      o->type(5);
      o->maximum(6);
      o->step(1);
      o->callback((Fl_Callback*)major_tick_precision_cb);
    }
    o->end();
  }
  return w;
}
