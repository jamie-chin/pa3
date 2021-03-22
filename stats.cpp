#include "stats.h"


#include "stats.h"

stats::stats(PNG & im){
    
    vector< vector< long >> sumRed(im.height(), vector<long> (im.width())); //[row][col]
    vector< vector< long >> sumGreen(im.height(), vector<long> (im.width()));
    vector< vector< long >> sumBlue(im.height(), vector<long> (im.width()));
    vector< vector< long >> sumsqRed(im.height(), vector<long> (im.width()));
    vector< vector< long >> sumsqGreen(im.height(), vector<long> (im.width()));
    vector< vector< long >> sumsqBlue(im.height(), vector<long> (im.width()));
    vector <long> firstTempRed;
    vector <long> firstTempGreen;
    vector <long> firstTempBlue;
    vector <long> firstTempRedSq;
    vector <long> firstTempGreenSq;
    vector <long> firstTempBlueSq;

    for(unsigned j=0; j < im.width(); j++) {
        RGBAPixel *pixel = im.getPixel(0,j);

        int tempRedSum = j==0 ? pixel->r: pixel->r + firstTempRed[j-1];
        firstTempRed.push_back(tempRedSum);

        int tempGreenSum = j==0 ? pixel->g: pixel->g + firstTempGreen[j-1];
        firstTempGreen.push_back(tempGreenSum);

        int tempBlueSum = j==0 ? pixel->b: pixel->b + firstTempBlue[j-1];
        firstTempBlue.push_back(tempBlueSum);
    }
    sumRed.push_back(firstTempRed);
    sumGreen.push_back(firstTempGreen);
    sumBlue.push_back(firstTempBlue);

    for(unsigned j=0; j < im.width(); j++) {
        RGBAPixel *pixel = im.getPixel(0,j);

        int tempRedSumSq = j==0 ? pow(pixel->r, 2): pow(pixel->r, 2) + firstTempRedSq[j-1];
        firstTempRedSq.push_back(tempRedSumSq);
            
        int tempGreenSumSq = j==0 ? pow(pixel->g, 2): pow(pixel->g, 2) + firstTempGreenSq[j-1];
        firstTempGreenSq.push_back(tempGreenSumSq);
            
        int tempBlueSumSq = j==0 ? pow(pixel->b, 2): pow(pixel->b, 2) + firstTempBlueSq[j-1];
        firstTempBlueSq.push_back(tempBlueSumSq);
    }
    sumsqRed.push_back(firstTempRedSq);
    sumsqGreen.push_back(firstTempGreenSq);
    sumsqBlue.push_back(firstTempBlueSq);
    

    for (unsigned i = 1; i < im.height(); i++) {
        vector <long> tempRed;
        vector <long> tempGreen;
        vector <long> tempBlue;
        vector <long> tempRedSq;
        vector <long> tempGreenSq;
        vector <long> tempBlueSq;
        for (unsigned j=0; j < im.width(); j++){ 
            RGBAPixel *pixel = im.getPixel(i,j);

            int tempRedSum = pixel->r + sumRed[i-1][j] + tempRed[j-1];
            tempRed.push_back(tempRedSum);
            
            int tempGreenSum = pixel->g + sumGreen[i-1][j] + tempGreen[j-1];
            tempGreen.push_back(tempGreenSum);
            
            int tempBlueSum = pixel->b + sumBlue[i-1][j] + tempBlue[j-1];
            tempBlue.push_back(tempBlueSum);

            int tempRedSumSq = pow(pixel->r, 2) + sumRed[i-1][j] + tempRedSq[j-1];
            tempRedSq.push_back(tempRedSumSq);
            
            int tempGreenSumSq = pow(pixel->g, 2) + sumGreen[i-1][j] + tempGreenSq[j-1];
            tempGreenSq.push_back(tempGreenSumSq);
            
            int tempBlueSumSq = pow(pixel->b, 2) + sumBlue[i-1][j] + tempBlueSq[j-1];
            tempBlueSq.push_back(tempBlueSumSq);
        }
        sumRed.push_back(tempRed);
        sumGreen.push_back(tempGreen);
        sumBlue.push_back(tempBlue);
        sumsqRed.push_back(tempRedSq);
        sumsqGreen.push_back(tempGreenSq);
        sumsqBlue.push_back(tempBlueSq);
    }
}


long stats::getSum(char channel, pair<int,int> ul, int w, int h){
/* Your code here!! */
}

long stats::getSumSq(char channel, pair<int,int> ul, int w, int h){
/* Your code here!! */
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int,int> ul, int w, int h){
/* Your code here!! */

}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int w, int h){
/* Your code here!! */

}
