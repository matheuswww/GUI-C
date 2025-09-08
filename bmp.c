#include <bmp.h>
#include <omnistd.h>

extern rgb **globalColors;

bitmap *parsebmp(int8 *bmpfile, int16 x, int16 y) {
  bitmap *bm;
  int16 size, n;
  bitmapheader *hdr;
  infoheader *info;
  colortable *colors;
  int16 fd;
  int8 *filename;
  int8 *file, *p;

  if (!bmpfile)
    return (bitmap *)0;
  filename = addbmp(bmpfile);
  fd = open(filename, 0);
  if (!fd)
    return (bitmap *)0;

  file = (int8 *)alloc(128);
  if (!file) {
    close(fd);
    return (bitmap *)0;
  }
  
  zero($1 file, $2 128);
  for(n=BmpHdrSz, p=file; n; n--, p++) {
    *p = read(fd);
  }
  close(fd);

  hdr = (bitmapheader *)file;
  
  size = sizeof(struct s_bitmapheader);
  info = (infoheader *)(file+size); 
  size = sizeof(colortable);
  colors = (colortable *)alloc(size);
  if (!colors)
    return (bitmap *)0;

  n = sizeof(struct s_bitmapheader) + sizeof(struct s_infoheader);
  copy($1 colors, $1 (file+n), size);
  size = sizeof(struct s_bitmap);
  bm = (bitmap *)alloc(size);
  if (!bm)
    return (bitmap *)0;

  bm->x = x;
  bm->y = y;
  bm->hdr = hdr;
  bm->info = info;
  bm->colors = colors;
  bm->filename = filename;
  return bm; 
}

boolean drawbmp(bitmap *bm) {
  int16 size;
  int16 width;
  int8 byte, bithigh, bitlow;
  int16 n;
  point *pp;
  int16 line, cols;
  int16 fd;  
  int8 *file;

  if (!bm)
    return false;

  file = bm->filename;
  fd = open(file, bm->hdr->offset);
  if (!fd)
    return false;

  size = (bm->info->height*bm->info->width) / 2;
  if ((bm->info->height*bm->info->width)%2)
    size++;
  width = (bm->info->width) / 2;

  save();
  cols = 0;
  line = bm->info->height;
  for (n=size; n; n--) {
    if (!(n%width)) {
      line--;
      cols = 0;
    }
    byte = read(fd);
    bitlow = (byte & 0x0f);
    bithigh = ((byte & 0xf0) >> 4);

    pp = mkpoint((cols+bm->x), (line+bm->y), getclr(bm->colors, bithigh));
    if (pp){
      drawpoint(pp);
      cols++;
    }

    pp = mkpoint((cols+bm->x), (line+bm->y), getclr(bm->colors, bitlow));
    if (pp) {
      drawpoint(pp);
      cols++;
    }
    
    load();
  }
  close(fd);

  return true;
}

int8 getclr(colortable *colors, int8 input) {
  int8 red, green, blue;
  int8 ret;
  int16 n;
  videomode(x40x25xT);
  for (n=0; n<256; n++) {
    red = globalColors[n]->red;
    green = globalColors[n]->green;
    blue = globalColors[n]->blue;

    if ((red == colors[input]->red) && (green == colors[input]->green) && (blue == colors[input]->blue)) {
      ret = n;
      break;
    }
  }

  return ret;
}

int8 *addbmp(int8 *file) {
  int8 *ret, *p;
  int16 size;

  if (!file)
    return $1 0;

  size = stringlen(file);
  if (!size)
    return $1 0;
  ret = $1 alloc(16);
  if (!ret)
    return $1 0;
  zero($1 ret, 16);
  stringcopy($1 ret, $1 file, size);
  p = ret + size;
  stringcopy($1 p, $1 ".bmp", 4);

  return ret;
}