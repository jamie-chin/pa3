/**
 *
 * shifty quadtree (pa3)
 * sqtree.cpp
 * This file will be used for grading.
 *
 */

#include "sqtree.h"

// First Node constructor, given.
SQtree::Node::Node(pair<int,int> ul, int w, int h, RGBAPixel a, double v)
  :upLeft(ul),width(w),height(h),avg(a),var(v),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
{}

// Second Node constructor, given
SQtree::Node::Node(stats & s, pair<int,int> ul, int w, int h)
  :upLeft(ul),width(w),height(h),NW(NULL),NE(NULL),SE(NULL),SW(NULL) {
  avg = s.getAvg(ul,w,h);
  var = s.getVar(ul,w,h);
}

// SQtree destructor, given.
SQtree::~SQtree() {
  clear();
}

// SQtree copy constructor, given.
SQtree::SQtree(const SQtree & other) {
  copy(other);
}

// SQtree assignment operator, given.
SQtree & SQtree::operator=(const SQtree & rhs) {
  if (this != &rhs) {
    clear();
    copy(rhs);
  }
  return *this;
}

/**
 * SQtree constructor given tolerance for variance.
 */
SQtree::SQtree(PNG & imIn, double tol) {

  stats s(imIn);
  //unsure abt what the pair coordinates should be
  pair<int,int> ul(0,0);
  int w = imIn.width();
  int h = imIn.height();

  root = buildTree(s, ul, w, h, tol);
}

/**
 * Helper for the SQtree constructor.
 */
SQtree::Node * SQtree::buildTree(stats & s, pair<int,int> & ul,
				 int w, int h, double tol) {
  //use node constructor to construct node with stats, ul, w, h
  //1. Build Node with given stats, upperLeft, width, and height
  Node * node = new Node(s, ul, w, h);
  int ulX = ul.first;
  int ulY = ul.second;

  //2. If base case, then return the node
  //Base Case: if dimension is 1x1 OR node variance is less than or equal to tolerance threshold
  if (w * h == 1 || node->var <= tol) {
    return node;
  }
  if (w * h == 0) {
    return NULL;
  }

  //3. set up minimum variances as tolerance (trying to minimize this number)
  double minVar = tol; 
  pair<int,int> ulNW (-1,-1);
  pair<int,int> ulNE (-1,-1);
  pair<int,int> ulSW (-1,-1);
  pair<int,int> ulSE (-1,-1);
  int xSplit = 0;
  int ySplit = 0;
  //4. for every pixel in the in the node, create smaller partitions
  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
      bool setNW = false, setNE = false, setSW = false, setSE = false;

      if (x == 0 && y == 0) {
        continue;

      } else if (y == 0) { // NW and NE
        ulNW.first  = ulX;
        ulNW.second = ulY;

        ulNE.first  = ulX + x;
        ulNE.second = ulY;
        setNW = true; setNE = true;

      } else if (x == 0) { // NW and SW
        ulNW.first  = ulX;
        ulNW.second = ulY;

        ulSW.first  = ulX;
        ulSW.second = ulY + y;
        setNW = true; setSW = true;

      } else { // NW, NE, SW, SE
        ulNW.first  = ulX;
        ulNW.second = ulY;

        ulNE.first  = ulX + x;
        ulNE.second = ulY;

        ulSW.first  = ulX;
        ulSW.second = ulY + y;

        ulSE.first  = ulX + x;
        ulSE.second = ulY + y;
        setNW = true; setNE = true; setSW = true; setSE = true;
      }

      //get variances of all the partitions (-1 variance for no partition)
      double varNW = setNW ? s.getVar(ulNW, x, y) : -1;
      double varNE = setNE ? s.getVar(ulNE, w - x, y) : -1;
      double varSW = setSW ? s.getVar(ulSW, x, h - y) : -1;
      double varSE = setSE ? s.getVar(ulSE, w - x, h - y) : -1;

      //get the maximum of the 4 variances
      double maxVar = varNW;
      if (varNE > maxVar) maxVar = varNE;
      if (varSW > maxVar) maxVar = varSW;
      if (varSE > maxVar) maxVar = varSE;

      if (maxVar < minVar) {
        minVar = maxVar;
        xSplit = x;
        ySplit = y;
      }
      
      setNW = false; setNE = false; setSW = false; setSE = false;
    }
  }

  // 4. build all 4 children nodes of the current node recursively using the stored x and y
  //cout << "ulNW: " << ulNW.first << "," << ulNW.second << endl;
  //cout << "xSplit: " << xSplit << " ySplit: " << ySplit << endl;
  node->NW = buildTree(s, ulNW, xSplit,     ySplit, tol); // NW

  //cout << "ulNE: " << ulNE.first << "," << ulNE.second << endl;
  //cout << "w - xSplit: " << w - xSplit << " ySplit: " << ySplit << endl;
  // cout << "sir can i have a segfault pls" << endl;
  node->NE = buildTree(s, ulNE, w - xSplit, ySplit, tol); // NE
  // ^^^ segfault
  node->SW = buildTree(s, ulSW, xSplit,     h - ySplit, tol); // SW
  node->SE = buildTree(s, ulSE, w - xSplit, h - ySplit, tol); // SE

  return node;
}
  
/**
 * Render SQtree and return the resulting image.
 */
PNG SQtree::render() {
  // Your code here.
  PNG im;
  return im;
}

/**
 * Delete allocated memory.
 */
void SQtree::clear() {
  // Your code here.
}

void SQtree::copy(const SQtree & other) {
  // Your code here.
}

int SQtree::size() {
  // Your code here.
  return 0;
}

