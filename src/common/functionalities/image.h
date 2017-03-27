//
// Created by Colliot on 2016/9/6.
//

#ifndef PROJECT_IMAGE_H
#define PROJECT_IMAGE_H

typedef struct {
  void *HBITMAP;
  int width;
  int height;
} ACL_Image;

// Image
///
/// \param pImageFileName
/// \param pImage
void loadImage(const char *pImageFileName, ACL_Image *pImage);
///
/// \param pImage
void freeImage(ACL_Image *pImage);
///
/// \param pImage
/// \param x
/// \param y
void putImage(ACL_Image *pImage, int x, int y);
///
/// \param pImage
/// \param x
/// \param y
/// \param width
/// \param height
void putImageScale(ACL_Image *pImage, int x, int y, int width, int height);
///
/// \param pImage
/// \param x
/// \param y
/// \param width
/// \param height
/// \param bkColor
void putImageTransparent(ACL_Image *pImage, int x, int y, int width, int height, ACL_Color bkColor);


#endif //PROJECT_IMAGE_H
