//========================================================================
// Fl_Gl_Slide V 0.1 For the Fast Light Tool Kit (FLTK) - www.fltk.org
//
// Copyrigth 2014 by Edmanuel Eduardo Torres Amaris
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
//========================================================================

// This is a very easy to use OpenGl class for FLTK...
// You will not have any dificults to use it... enjoy it.

#include "Fl_Gl_Slide.H"

const int Nx = 255;
const int Ny = 255;
const int Nz = 255;

float c[Nx*Ny*Nz];

#define  c(i,j,k)  c[ ((i)*Ny + (j))*Nz + (k) ]

#define ALPHA half_side
#define HAVE_GL 1

#if HAVE_GL
Fl_Gl_Slide::Fl_Gl_Slide(int x,int y,int w,int h,const char *l) : Fl_Gl_Window(x,y,w,h,l)
#else
Fl_Gl_Slide::Fl_Gl_Slide(int x,int y,int w,int h,const char *l) : Fl_Box(x,y,w,h,l)
#endif /* HAVE_GL */
{
    // just some defaults values...
    is_n_data = 0;
    // rotacion
    hang = 0.0;
    vang = 0.0;
    // zoom
    zoom=1.0;
    // position
    xshift=0.0;
    yshift=0.0;
    zshift=0.0;
    // Background colors
    bkred= 0.0;
    bkgreen= 0.0;
    bkblue= 0.5;
    alpha = 1.0;

#if !HAVE_GL
    label("OpenGL is required for this demo to operate.");
    align(FL_ALIGN_WRAP | FL_ALIGN_INSIDE);
#endif /* !HAVE_GL */
    
    // Initial SISMIC data
    int i, j, k;
    for(i=0;i<Nx;i++){
        for(j=0;j<Ny;j++){
            for(k=0;k<Nz;k++) c(i,j,k)=0.5*(float(j)/float(Ny))+0.5*(float(k)/float(Nz));//
            //for(k=0;k<Nz/3;k++) c(i,j,k)=0.5*(float(j)/float(Ny))+0.5*(float(k)/float(Nz));//
            //for(k=Nz/3;k<2*Nz/3;k++) c(i,j,k)=0.5*(float(j)/float(Ny))+0.5*(float(k)/float(Nz));//=1.0*(float(j)/float(Ny));
            //for(k=2*Nz/3;k<Nz;k++) c(i,j,k)=0.5*(float(j)/float(Ny))+0.5*(float(k)/float(Nz));//=1.0*(float(k)/float(Nz));
        }
    }
}

// OPENGL... here we can draw what we want... maybe a simple box...
void Fl_Gl_Slide::draw_gl_box(void){
    // You can guess what these functions do... don't you?
    glTranslatef(xshift, yshift, 0);
    glRotatef(hang,0,1,0);
    glRotatef(vang,1,0,0);
    glScalef(zoom,zoom,zoom);
    GLfloat half_side = 0.5;
    GLfloat data_step = 1.0/255.0;
    //
    // Display the data
    GLfloat posx = -half_side;
    GLfloat posy = -half_side;
    int i = 0;
    for (int j=0; j<255; j++)
    {
        //posx = -half_side;
        posy = -half_side;
        for (int k=0; k<255; k++)
        {
           
           glBegin(GL_POLYGON);
           glColor3f( c(i,0,j), c(0,k,j), c(i,k,0) );
           glVertex3f(  posx+data_step, posy, -half_side );            // P1
           glVertex3f(  posx+data_step,  posy+data_step, -half_side ); // P2
           glVertex3f( posx,  posy+data_step, -half_side );            // P3
           glVertex3f( posx, posy, -half_side );                       // P4
           glEnd();
           posy += data_step;
        }
        posx += data_step;
    }
    // Draw the box
    glBegin(GL_LINES);
    // Box color
    glColor3f(0.0,1.0,1.0);
    // top
    glVertex3f(-half_side,-half_side, half_side);
    glVertex3f( half_side,-half_side, half_side);
    glVertex3f(-half_side,-half_side, half_side);
    glVertex3f(-half_side, half_side, half_side);
    glVertex3f(-half_side, half_side, half_side);
    glVertex3f( half_side, half_side, half_side);
    glVertex3f( half_side,-half_side, half_side);
    glVertex3f( half_side, half_side, half_side);
    // bottom
    glVertex3f(-half_side,-half_side,-half_side);
    glVertex3f( half_side,-half_side,-half_side);
    glVertex3f(-half_side,-half_side,-half_side);
    glVertex3f(-half_side, half_side,-half_side);
    glVertex3f(-half_side, half_side,-half_side);
    glVertex3f( half_side, half_side,-half_side);
    glVertex3f( half_side,-half_side,-half_side);
    glVertex3f( half_side, half_side,-half_side);
    //vertex
    glVertex3f(-half_side,-half_side,-half_side);
    glVertex3f(-half_side,-half_side, half_side);
    glVertex3f( half_side, half_side,-half_side);
    glVertex3f( half_side, half_side, half_side);
    glVertex3f(-half_side, half_side,-half_side);
    glVertex3f(-half_side, half_side, half_side);
    glVertex3f( half_side,-half_side,-half_side);
    glVertex3f( half_side,-half_side, half_side);
    //
    glEnd();
    //}
#if _SHOW_MESSAGES
    printf("drawMesh();\n");
#endif /* !HAVE_GL */
}


#if HAVE_GL

void Fl_Gl_Slide::draw() {
    if (!valid()) {
        glClearColor(bkred,bkgreen,bkblue,alpha);
        glLoadIdentity();
        glViewport(0,0,w(),h());
        glOrtho(-1,1,-1,1,-100,100);
    }
    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    if(is_n_data)
      draw_gl_box();
    glPopMatrix();
    glFlush();
    redraw();
}

#endif /* HAVE_GL */

// HANDLE EVENTS... these you can add your own new handle function...
// send me a copy if you want I will add this here with your name and email...
int Fl_Gl_Slide::handle(int event) {
    static int last_x;
    static int last_y;
    int delta_x, delta_y;
    //... position in Fl::event_x() and Fl::event_y()
    // get current mouse position and process event
    int x = Fl::event_x();
    int y = Fl::event_y();

  switch(event) {
  case FL_PUSH:
    //... mouse down event ...
    // save mouse position to track drag events
    last_x = x;
    last_y = y;
    return 1;
  case FL_DRAG:
    delta_x = x - last_x;
    delta_y = y - last_y;
    last_x = x;
    last_y = y;
    hang += 0.2*delta_x;
    vang += 0.2*delta_y;
    redraw();
    return 1;
    /*case FL_RELEASE:
    ... mouse up event ...
    return 1;
    case FL_FOCUS :
    case FL_UNFOCUS :
    ... Return 1 if you want keyboard events, 0 otherwise
    return 1;
    case FL_KEYBOARD:
    ... keypress, key is in Fl::event_key(), ascii in Fl::event_text()
    ... Return 1 if you understand/use the keyboard event, 0 otherwise...
    return 1;
    case FL_SHORTCUT:
    ... shortcut, key is in Fl::event_key(), ascii in Fl::event_text()
    ... Return 1 if you understand/use the shortcut event, 0 otherwise...
    return 1;*/
  default:
    // pass other events to the base class...
    return Fl_Gl_Window::handle(event);
  }
}

// UTILS... please send me any other funtion and another people can use it... thanks
void Fl_Gl_Slide::bgColor(float r,float g,float b){
    bkred=r;
    bkgreen=g;
    bkblue=b;
}

// END
