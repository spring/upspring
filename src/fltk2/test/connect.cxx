//
// "$Id: connect.cxx 4886 2006-03-30 09:55:32Z fabien $"
//
// PPP example program for the Fast Light Tool Kit (FLTK).
//
// Program to make a button to turn a ppp connection on/off.
// You must chmod +s /usr/sbin/pppd, and put all the options
// into /etc/ppp/options.
//
// Copyright 1998-2006 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to "fltk-bugs@fltk.org".
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include <fltk/Fl.h>
#include <fltk/Fl_Window.h>
#include <fltk/Fl_Toggle_Button.h>

int running;	// actually the pid
Fl_Toggle_Button *Button;

void sigchld(int) {
  waitpid(running, 0, 0);
  running = 0;
  Button->value(0);
}

void cb(Fl_Widget *o, void *) {
  if (((Fl_Toggle_Button*)o)->value()) {
    if (running) return;
    running = fork();
    if (!running) execl("/usr/sbin/pppd","pppd","-detach",0);
    else signal(SIGCHLD, sigchld);
  } else {
    if (!running) return;
    kill(running, SIGINT);
    waitpid(running, 0, 0);
    running = 0;
  }
}

int main(int argc, char ** argv) {
   Fl_Window window(100,50);
   Fl_Toggle_Button button(0,0,100,50,"Connect");
   Button = &button;
   button.color(1,2);
   button.callback(cb,0);
   window.show(argc,argv);
   return Fl::run();
}

//
// End of "$Id: connect.cxx 4886 2006-03-30 09:55:32Z fabien $".
//
