#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "pnm_io.h"





/*
 *           Memory managment
 *
 */



#define MAX_DIM 10000



im_gray *alloc_im_gray(int xd,int yd) {
  im_gray *ret;


  if(xd<0 || xd>MAX_DIM || yd<0 || yd>MAX_DIM) {
    fprintf(stderr,"Weird image size: %d*%d\n",xd,yd);
    exit(1);    
  }

  ret=malloc(sizeof(im_gray));

  ret->xd=xd;
  ret->yd=yd;

  ret->data=malloc(xd*yd);

  if(!ret->data) {
    fprintf(stderr,"malloc %d bytes failed\n",xd*yd);
    exit(1);
  }
  
  return ret;
}


void dealloc_im_gray(im_gray *im) {
  free(im->data);
  free(im);
}

/*
 *  WARNING: this works only if  sizeof(struct {char a,b,c})==3
 *  this is normaly the case, because there is no risk of unaligned access on chars
 */

im_color *alloc_im_color(int xd,int yd) {
  im_color *ret;


  if(xd<0 || xd>MAX_DIM || yd<0 || yd>MAX_DIM) {
    fprintf(stderr,"Weird image size: %d*%d\n",xd,yd);
    exit(1);    
  }

  ret=malloc(sizeof(im_color));

  ret->xd=xd;
  ret->yd=yd;

  ret->data=malloc(xd*yd*3);

  if(!ret->data) {
    fprintf(stderr,"malloc %d bytes failed\n",xd*yd);
    exit(1);
  }
  
  return ret;
}


void dealloc_im_color(im_color *im) {
  free(im->data);
  free(im);
}



/*
 *           Common functions for all pnm files
 *
 */


static void get_line(FILE *f,char *buffer) {
  while(1) {
    char *c;
    c=fgets(buffer,79,f);
    if(!c) {
      fprintf(stderr,"EOF while reading header\n");
      exit(1);      
    }
    for(c=buffer;isspace(*c);c++);
    if(*c!='#') return ;
  }
}

/* consumes the header of the pnm file, returns a handle to the rest */
static FILE* open_pnm(char *filename,
		      int *pn,int *xd,int *yd,int *maxval) {
  FILE *f;
  char buffer[80];

  if(!(f=fopen(filename,"rb"))) {
    fprintf(stderr,"Could not open `%s'",filename);
    perror("");
    exit(1);
  }
  
  get_line(f,buffer);  
  if(sscanf(buffer,"P%d",pn)!=1) {
    fprintf(stderr,"`%s' does not have a Px header\n",filename);
    exit(1);
  }
  
  get_line(f,buffer);  
  if(sscanf(buffer,"%d %d ",xd,yd)!=2) {
    fprintf(stderr,"`%s' has invalid dimensions\n",filename);
    exit(1);
  }
  
  get_line(f,buffer);  
  if(sscanf(buffer,"%d ",maxval)!=1) {
    fprintf(stderr,"`%s' mentions invalid maxval\n",filename);
    exit(1);
  }

  return f;
}


/*
 *           PGM functions
 *
 */


im_gray *load_pgm(char *filename) {
  FILE *f;
  int pn,xd,yd,maxval;
  im_gray *ret;

  f=open_pnm(filename,&pn,&xd,&yd,&maxval);

  if(pn!=5 || maxval!=255) {
    fprintf(stderr,"load_pgm(`%s'): not a 8 bpp PGM raw file\n",filename);
    exit(1);
  }

  ret=alloc_im_gray(xd,yd);
  if(fread(ret->data,1,xd*yd,f)!=xd*yd)
    fprintf(stderr,"load_pgm(`%s'): warning, file truncated\n",filename);

  fclose(f);

  return ret;
}


void save_pgm(char *filename,im_gray *im) {
  FILE *f;
  if(!(f=fopen(filename,"wb"))) {
    fprintf(stderr,"Could not open `%s'",filename);
    perror("");
    exit(1);
  }

  fprintf(f,"P5\n%d %d\n255\n",im->xd,im->yd);
  fwrite(im->data,1,im->xd*im->yd,f);
  fclose(f);
}


/*
 *           PPM functions
 *
 */

im_color *load_ppm(char *filename) {
  FILE *f;
  int pn,xd,yd,maxval;
  im_color *ret;

  f=open_pnm(filename,&pn,&xd,&yd,&maxval);

  if(pn!=6 || maxval!=255) {
    fprintf(stderr,"load_ppm(`%s'): not a 8 bpp PPM raw file\n",filename);
    exit(1);
  }

  ret=alloc_im_color(xd,yd);
  if(fread(ret->data,3,xd*yd,f)!=xd*yd)
    fprintf(stderr,"load_ppm(`%s'): warning, file truncated\n",filename);

  fclose(f);

  return ret;
}

/* idem mais n'alloue pas l'image.
 * renvoie true ou false sans quitter 
 */
int load_ppm_pix (char * filename, unsigned char * data) {
	FILE *f;
	int pn,xd,yd,maxval;
	int res;
  
	f = open_pnm(filename,&pn,&xd,&yd,&maxval);

	if(pn!=6 || maxval!=255) {
		fprintf(stderr,"load_ppm(`%s'): not a 8 bpp PPM raw file\n",filename);
		res = 0;
	} else {
		if (fread (data,3,xd*yd,f) != xd*yd) {
			fprintf(stderr,"load_ppm(`%s'): warning, file truncated\n",filename);
			res = 0;
		} else {
			res = 1;
		}
	}
	fclose(f);
	return res;
}




void save_ppm(char *filename,im_color *im) {
  FILE *f;
  if(!(f=fopen(filename,"wb"))) {
    fprintf(stderr,"Could not open `%s'",filename);
    perror("");
    exit(1);
  }

  fprintf(f,"P6\n%d %d\n255\n",im->xd,im->yd);
  fwrite(im->data,1,im->xd*im->yd*3,f);
  fclose(f);
}


