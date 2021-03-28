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
        } else {
            firstTempRed.push_back(pixel->r + firstTempRed[j-1]);
            firstTempGreen.push_back(pixel->g + firstTempGreen[j-1]);
            firstTempBlue.push_back(pixel->b + firstTempBlue[j-1]);
        }
    }
    sumRed.push_back(firstTempRed);
    sumGreen.push_back(firstTempGreen);
    sumBlue.push_back(firstTempBlue);

    for(unsigned j=0; j < im.height(); j++) {
        RGBAPixel *pixel = im.getPixel(0,j);

        if (j == 0) {
            firstTempRedSq.push_back((pixel->r)*(pixel->r));
            firstTempGreenSq.push_back((pixel->g)*(pixel->g));
            firstTempBlueSq.push_back((pixel->b)*(pixel->b));
        } else {
            firstTempRedSq.push_back((pixel->r)*(pixel->r) + firstTempRedSq[j-1]);
            firstTempGreenSq.push_back((pixel->g)*(pixel->g) + firstTempGreenSq[j-1]);
            firstTempBlueSq.push_back((pixel->b)*(pixel->b) + firstTempBlueSq[j-1]);
        }
    }
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
                tempRedSq.push_back((pixel->r)*(pixel->r) + sumRed[i-1][j]);
                tempGreenSq.push_back((pixel->g)*(pixel->g) + sumGreen[i-1][j]);
                tempBlueSq.push_back((pixel->b)*(pixel->b) + sumBlue[i-1][j]);
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

    for (int n = 0; n < 4; n++) {
        for (int m = 0; m < 4; m++) {
            cout << sumRed[m][n] << " | ";
        }
        cout << endl;
    }
}


long stats::getSum(char channel, pair<int,int> ul, int w, int h){
    int x = ul.first;
    int y = ul.second;

    if (w == 0 && h == 0) {
        return (long)0;
    } 
    if (x == 0 && y == 0) {
        if (channel == 'r') {
            return sumRed[h-1][w-1];
        } else if (channel == 'g') {
            return sumGreen[h-1][w-1];
        } else if (channel == 'b') {
            return sumBlue[h-1][w-1];
        }
    }

    if (channel == 'r') {
        return sumRed[y+h-1][x+w-1] - (sumRed[y+h-1][x-1]+sumRed[y-1][x+w-1]) + sumRed[y-1][x-1];
    } else if (channel == 'g') {
        return sumGreen[y+h-1][x+w-1] - (sumGreen[y+h-1][x-1]+sumGreen[y-1][x+w-1]) + sumGreen[y-1][x-1];
    } else if (channel == 'b') {
        return sumBlue[y+h-1][x+w-1] - (sumBlue[y+h-1][x-1]+sumBlue[y-1][x+w-1]) + sumBlue[y-1][x-1];
    }

    return (long)0;
}

long stats::getSumSq(char channel, pair<int,int> ul, int w, int h){
    int x = ul.first;
    int y = ul.second;

    if (w == 0 && h == 0) {
        return (long)0;
    } 
    if (x == 0 && y == 0) {
        if (channel == 'r') {
            return sumsqRed[h-1][w-1];
        } else if (channel == 'g') {
            return sumsqGreen[h-1][w-1];
        } else if (channel == 'b') {
            return sumsqBlue[h-1][w-1];
        }
    }
    
    if (channel == 'r') {
        return sumsqRed[y+h-1][x+w-1] - (sumsqRed[y+h-1][x-1]+sumsqRed[y-1][x+w-1]) + sumsqRed[y-1][x-1];
    } else if (channel == 'g') {
        return sumsqGreen[y+h-1][x+w-1] - (sumsqGreen[y+h-1][x-1]+sumsqGreen[y-1][x+w-1]) + sumsqGreen[y-1][x-1];
    } else if (channel == 'b') {
        return sumsqBlue[y+h-1][x+w-1] - (sumsqBlue[y+h-1][x-1]+sumsqBlue[y-1][x+w-1]) + sumsqBlue[y-1][x-1];
    }

    return (long)0;
}


// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int,int> ul, int w, int h){
    long area = w * h;
    if (area == 0) {
        return 0.0;
    }

    double rSSD = getSumSq('r', ul, w, h) - (getSum('r', ul, w, h) * getSum('r', ul, w, h)) / area;
    cout << "rSSD: " << rSSD << endl;
    double gSSD = getSumSq('g', ul, w, h) - (getSum('g', ul, w, h) * getSum('g', ul, w, h)) / area;
    cout << "gSSD: " << gSSD << endl;
    double bSSD = getSumSq('b', ul, w, h) - (getSum('b', ul, w, h) * getSum('b', ul, w, h)) / area;
    cout << "bSSD: " << bSSD << endl;

    double varResult = rSSD + gSSD + bSSD;
    cout << "variance: " << varResult << endl;
    return varResult;
    // return 0.0;
}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int w, int h){
    long area = w * h;
    if (area == 0) {
        return RGBAPixel(0,0,0);
    }
    cout << "area: " << area << endl;

    long rSum = getSum('r', ul, w, h);
    cout << "rSum: " << rSum << endl;
    long gSum = getSum('g', ul, w, h);
    cout << "gSum: " << gSum << endl;
    long bSum = getSum('b', ul, w, h);
    cout << "bSum: " << bSum << endl;
    
    RGBAPixel pixel = RGBAPixel((int)((double)rSum/(double)area), (int)((double)gSum/(double)area), (int)((double)bSum/(double)area));
    return pixel;
    cout << "average: " << pixel << endl;
    //return RGBAPixel(0,0,0);
}
