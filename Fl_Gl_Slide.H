//=====================================================================
// Fl_Gl_Slide V 0.1 For the Fast Light Tool Kit (FLTK) - www.fltk.org
//
// Copyrigth 2014 by Edmanuel Torres
// eetorres@gmail.com
//
// Sent me any suggestion, modification or bugs. Don't hesitate to contact
// me for any question, I will be very grateful with your feedbacks.
// Get the latest version at https://github.com/eetorres/Fl_Gl_Slide
//
// This widget is  free  software;  you  can  redistribute  it and/or
// modify it  under  the  terms  of  the   GNU Library General Public
// License  as  published  by  the  Free  Software Foundation; either
// version 2 of the License,  or  (at your option)  any later version.
//
// This  library  is  distributed  in the hope that it will be useful,
// but  WITHOUT ANY WARRANTY;  without  even  the  implied warranty of
// MERCHANTABILITY  or FITNESS FOR A PARTICULAR PURPOSE.   See the GNU
// Library General Public License for more details.
//
// You should have  received a copy  of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
//=====================================================================


#ifndef _Fl_Gl_Slide_H_
#define _Fl_Gl_Slide_H_

#include <FL/Fl.H>

#define HAVE_GL 1

#if HAVE_GL
    #include <FL/Fl_Gl_Window.H>
    #include <FL/gl.h>
#else
    #include <FL/Fl_Box.H>
#endif /* HAVE_GL */

#include <stdlib.h>

#if HAVE_GL
class Fl_Gl_Slide : public Fl_Gl_Window{
#else
class Fl_Gl_Slide : public Fl_Box {
#endif /* HAVE_GL */

public:

    Fl_Gl_Slide(int x,int y,int w,int h,const char *l=0);

    void bgColor(float r,float g,float b);
    void Alpha(float a){alpha = a;};
    // Scale function
    //void scale(float _s){scl = _s;};
    void Zoom(float _z){zoom = _z;};
    // Set the rotation about the vertical (y ) axis
    void vAngle(float angle){vang=angle;};
    // Return the rotation about the vertical (y ) axis
    float vAngle(){return vang;};
    // Set the rotation about the horizontal (x ) axis
    void hAngle(float angle){hang=angle;};
    // the rotation about the horizontal (x ) axis
    float hAngle(){return hang;};
    void xShift(float x){xshift=x;};
    void yShift(float y){yshift=y;};

    void valid_data(int _vd){is_n_data=_vd;};

#if HAVE_GL
    void draw_gl_box(void);
#else
    void draw_gl_box(void){
      printf("Is not posible start any OpenGL device interface\n");
    }
#endif /* HAVE_GL */
#if HAVE_GL
    void draw();
#endif /* HAVE_GL */

protected:
    int handle(int);

private:

    int is_n_data;
    float alpha;
    float vang,hang, zoom;
    float xshift,yshift,zshift;
    float bkred, bkgreen, bkblue;
    //
};

#endif

