#include "stats.h"


#include "stats.h"

stats::stats(PNG & im){
    vector <long> firstTempRed;
    vector <long> firstTempGreen;
    vector <long> firstTempBlue;
    vector <long> firstTempRedSq;
    vector <long> firstTempGreenSq;
    vector <long> firstTempBlueSq;

    for(unsigned j=0; j < im.height(); j++) {
        RGBAPixel *pixel = im.getPixel(0,j);

        if (j == 0) {
            firstTempRed.push_back(pixel->r);
            firstTempGreen.push_back(pixel->g);
            firstTempBlue.push_back(pixel->b);
            firstTempRedSq.push_back((pixel->r)*(pixel->r));
            firstTempGreenSq.push_back((pixel->g)*(pixel->g));
            firstTempBlueSq.push_back((pixel->b)*(pixel->b));
        } else {
            firstTempRed.push_back(pixel->r + firstTempRed[j-1]);
            firstTempGreen.push_back(pixel->g + firstTempGreen[j-1]);
            firstTempBlue.push_back(pixel->b + firstTempBlue[j-1]);
            firstTempRedSq.push_back((pixel->r)*(pixel->r) + firstTempRedSq[j-1]);
            firstTempGreenSq.push_back((pixel->g)*(pixel->g) + firstTempGreenSq[j-1]);
            firstTempBlueSq.push_back((pixel->b)*(pixel->b) + firstTempBlueSq[j-1]);
        }
    }
    sumRed.push_back(firstTempRed);
    sumGreen.push_back(firstTempGreen);
    sumBlue.push_back(firstTempBlue);
    sumsqRed.push_back(firstTempRedSq);
    sumsqGreen.push_back(firstTempGreenSq);
    sumsqBlue.push_back(firstTempBlueSq);
    

    for (unsigned i = 1; i < im.width(); i++) {
        vector <long> tempRed;
        vector <long> tempGreen;
        vector <long> tempBlue;
        vector <long> tempRedSq;
        vector <long> tempGreenSq;
        vector <long> tempBlueSq;

        for (unsigned j=0; j < im.height(); j++){ 
            RGBAPixel *pixel = im.getPixel(i,j);

            if (j == 0) {
                tempRed.push_back(pixel->r + sumRed[i-1][j]);
                tempGreen.push_back(pixel->g + sumGreen[i-1][j]);
                tempBlue.push_back(pixel->b + sumBlue[i-1][j]);
                tempRedSq.push_back((pixel->r)*(pixel->r) + sumsqRed[i-1][j]);
                tempGreenSq.push_back((pixel->g)*(pixel->g) + sumsqGreen[i-1][j]);
                tempBlueSq.push_back((pixel->b)*(pixel->b) + sumsqBlue[i-1][j]);
            } else {
                tempRed.push_back(pixel->r +  sumRed[i-1][j] + tempRed[j-1] - sumRed[i-1][j-1]);
                tempGreen.push_back(pixel->g +  sumGreen[i-1][j] + tempGreen[j-1] - sumGreen[i-1][j-1]);
                tempBlue.push_back(pixel->b + sumBlue[i-1][j] + tempBlue[j-1] - sumBlue[i-1][j-1]);
                tempRedSq.push_back((pixel->r)*(pixel->r) + sumsqRed[i-1][j] + tempRedSq[j-1] - sumsqRed[i-1][j-1]);
                tempGreenSq.push_back((pixel->g)*(pixel->g) + sumsqGreen[i-1][j] + tempGreenSq[j-1] - sumsqGreen[i-1][j-1]);
                tempBlueSq.push_back((pixel->b)*(pixel->b) + sumsqBlue[i-1][j] + tempBlueSq[j-1] - sumsqBlue[i-1][j-1]);
            }
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
    int x = ul.first;
    int y = ul.second;

    if (x == 0 && y == 0) {
        if (channel == 'r') {
            return sumRed[w-1][h-1];
        } else if (channel == 'g') {
            return sumGreen[w-1][h-1];
        } else if (channel == 'b') {
            return sumBlue[w-1][h-1];
        }
    
    } else if (x == 0) {
        if (channel == 'r') {
            return sumRed[w-1][y+h-1] - sumRed[w-1][y-1];
        } else if (channel == 'g') {
            return sumGreen[w-1][y+h-1] - sumGreen[w-1][y-1];
        } else if (channel == 'b') {
            return sumBlue[w-1][y+h-1] - sumBlue[w-1][y-1];
        }

    } else if (y == 0) {
        if (channel == 'r') {
            return sumRed[x+w-1][h-1] - sumRed[x-1][h-1];
        } else if (channel == 'g') {
            return sumGreen[x+w-1][h-1] - sumGreen[x-1][h-1];
        } else if (channel == 'b') {
            return sumBlue[x+w-1][h-1] - sumBlue[x-1][h-1];
        }

    } else {
        if (channel == 'r') {
            return sumRed[x+w-1][y+h-1] - sumRed[x+w-1][y-1] - sumRed[x-1][y+h-1] + sumRed[x-1][y-1];
        } else if (channel == 'g') {
            return sumGreen[x+w-1][y+h-1] - sumGreen[x+w-1][y-1] - sumGreen[x-1][y+h-1] + sumGreen[x-1][y-1];
        } else if (channel == 'b') {
            return sumBlue[x+w-1][y+h-1] - sumBlue[x+w-1][y-1] - sumBlue[x-1][y+h-1] + sumBlue[x-1][y-1];
        }
    }

    return (long)0;
}

long stats::getSumSq(char channel, pair<int,int> ul, int w, int h){
    int x = ul.first;
    int y = ul.second;

    if (x == 0 && y == 0) {
        if (channel == 'r') {
            return sumsqRed[w-1][h-1];
        } else if (channel == 'g') {
            return sumsqGreen[w-1][h-1];
        } else if (channel == 'b') {
            return sumsqBlue[w-1][h-1];
        }
    
    } else if (x == 0) {
        if (channel == 'r') {
            return sumsqRed[w-1][y+h-1] - sumsqRed[w-1][y-1];
        } else if (channel == 'g') {
            return sumsqGreen[w-1][y+h-1] - sumsqGreen[w-1][y-1];
        } else if (channel == 'b') {
            return sumsqBlue[w-1][y+h-1] - sumsqBlue[w-1][y-1];
        }

    } else if (y == 0) {
        if (channel == 'r') {
            return sumsqRed[x+w-1][h-1] - sumsqRed[x-1][h-1];
        } else if (channel == 'g') {
            return sumsqGreen[x+w-1][h-1] - sumsqGreen[x-1][h-1];
        } else if (channel == 'b') {
            return sumsqBlue[x+w-1][h-1] - sumsqBlue[x-1][h-1];
        }

    } else {
        if (channel == 'r') {
            return sumsqRed[x+w-1][y+h-1] - sumsqRed[x+w-1][y-1] - sumsqRed[x-1][y+h-1] + sumsqRed[x-1][y-1];
        } else if (channel == 'g') {
            return sumsqGreen[x+w-1][y+h-1] - sumsqGreen[x+w-1][y-1] - sumsqGreen[x-1][y+h-1] + sumsqGreen[x-1][y-1];
        } else if (channel == 'b') {
            return sumsqBlue[x+w-1][y+h-1] - sumsqBlue[x+w-1][y-1] - sumsqBlue[x-1][y+h-1] + sumsqBlue[x-1][y-1];
        }
    }

    return (long)0;
}


// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int,int> ul, int w, int h){
    double area = w * h;
    if (area <= 1) {
        return 0.0;
    }

    double rSum = getSum('r', ul, w, h);
    double gSum = getSum('g', ul, w, h);
    double bSum = getSum('b', ul, w, h);
    double rSumSq = getSumSq('r', ul, w, h);
    double gSumSq = getSumSq('g', ul, w, h);
    double bSumSq = getSumSq('b', ul, w, h);

    return (rSumSq + gSumSq + bSumSq) - (rSum * rSum + gSum * gSum + bSum * bSum) / area;
}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int w, int h){
    long area = w * h;
    if (area == 0) {
        return RGBAPixel(0,0,0);
    }

    long rSum = getSum('r', ul, w, h);
    long gSum = getSum('g', ul, w, h);
    long bSum = getSum('b', ul, w, h);
    
    RGBAPixel pixel = RGBAPixel((int)((double)rSum/(double)area), (int)((double)gSum/(double)area), (int)((double)bSum/(double)area));
    return pixel;
}
