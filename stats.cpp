#include "stats.h"


#include "stats.h"

stats::stats(PNG & im){
    /*
    vector< vector< long >> sumRed(im.height(), vector<long> (im.width())); //[row][col]
    vector< vector< long >> sumGreen(im.height(), vector<long> (im.width()));
    vector< vector< long >> sumBlue(im.height(), vector<long> (im.width()));
    vector< vector< long >> sumsqRed(im.height(), vector<long> (im.width()));
    vector< vector< long >> sumsqGreen(im.height(), vector<long> (im.width()));
    vector< vector< long >> sumsqBlue(im.height(), vector<long> (im.width()));*/
    //sumRed.resize(im.height(), vector<long>(im.width()));
    //cout << "initial size: " << sumRed.size() << endl;
    //sumGreen.resize(im.height(), vector<long>(im.width()));
    //sumBlue.resize(im.height(), vector<long>(im.width()));
    //sumsqRed.resize(im.height(), vector<long>(im.width()));
    //sumsqGreen.resize(im.height(), vector<long>(im.width()));
    //sumsqBlue.resize(im.height(), vector<long>(im.width()));
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
        
        /*int tempRedSum = j==0 ? pixel->r : pixel->r + firstTempRed[j-1];
        firstTempRed.push_back(tempRedSum);

        int tempGreenSum = j==0 ? pixel->g : pixel->g + firstTempGreen[j-1];
        firstTempGreen.push_back(tempGreenSum);

        int tempBlueSum = j==0 ? pixel->b : pixel->b + firstTempBlue[j-1];
        firstTempBlue.push_back(tempBlueSum);*/
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

        /*int tempRedSumSq = j==0 ? (pixel->r)*(pixel->r) : (pixel->r)*(pixel->r) + firstTempRedSq[j-1];
        firstTempRedSq.push_back(tempRedSumSq);
            
        int tempGreenSumSq = j==0 ? (pixel->g)*(pixel->g) : (pixel->g)*(pixel->g) + firstTempGreenSq[j-1];
        firstTempGreenSq.push_back(tempGreenSumSq);
            
        int tempBlueSumSq = j==0 ? (pixel->b)*(pixel->b) : (pixel->b)*(pixel->b) + firstTempBlueSq[j-1];
        firstTempBlueSq.push_back(tempBlueSumSq);*/
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
                tempRed.push_back(pixel->r + sumRed[i-1][j] + tempRed[j-1]);
                tempGreen.push_back(pixel->g + sumGreen[i-1][j] + tempGreen[j-1]);
                tempBlue.push_back(pixel->b + sumBlue[i-1][j] + tempBlue[j-1]);
                tempRedSq.push_back((pixel->r)*(pixel->r) + sumRed[i-1][j] + tempRedSq[j-1]);
                tempGreenSq.push_back((pixel->g)*(pixel->g) + sumGreen[i-1][j] + tempGreenSq[j-1]);
                tempBlueSq.push_back((pixel->b)*(pixel->b) + sumBlue[i-1][j] + tempBlueSq[j-1]);
            }

            /*int tempRedSum = j==0 ? pixel->r + sumRed[i-1][j] : pixel->r + sumRed[i-1][j] + tempRed[j-1];
            tempRed.push_back(tempRedSum);
            
            int tempGreenSum = j==0 ? pixel->g + sumGreen[i-1][j] : pixel->g + sumGreen[i-1][j] + tempGreen[j-1];
            tempGreen.push_back(tempGreenSum);
            
            int tempBlueSum = j==0 ? pixel->b + sumBlue[i-1][j] : pixel->b + sumBlue[i-1][j] + tempBlue[j-1];
            tempBlue.push_back(tempBlueSum);

            int tempRedSumSq = j==0 ? (pixel->r)*(pixel->r) + sumRed[i-1][j] : (pixel->r)*(pixel->r) + sumRed[i-1][j] + tempRedSq[j-1];
            tempRedSq.push_back(tempRedSumSq);
            
            int tempGreenSumSq = j==0 ? (pixel->g)*(pixel->g) + sumGreen[i-1][j] : (pixel->g)*(pixel->g) + sumGreen[i-1][j] + tempGreenSq[j-1];
            tempGreenSq.push_back(tempGreenSumSq);
            
            int tempBlueSumSq = j==0 ? (pixel->b)*(pixel->b) + sumBlue[i-1][j] : (pixel->b)*(pixel->b) + sumBlue[i-1][j] + tempBlueSq[j-1];
            tempBlueSq.push_back(tempBlueSumSq);*/
        }
        sumRed.push_back(tempRed);
        sumGreen.push_back(tempGreen);
        sumBlue.push_back(tempBlue);
        sumsqRed.push_back(tempRedSq);
        sumsqGreen.push_back(tempGreenSq);
        sumsqBlue.push_back(tempBlueSq);
        
    }
    //cout << "final size: " << sumRed.size() << endl;
    //cout << "final element size: " << sumRed[0].size() << endl;
    //cout << "final element size 1: " << sumRed[1].size() << endl;
    for (int n = 0; n < 4; n++) {
        for (int m = 0; m < 4; m++) {
            cout << sumRed[m][n] << " | ";
        }
        cout << endl;
    }
}


long stats::getSum(char channel, pair<int,int> ul, int w, int h){
    //vector< vector< long >> sum;
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
        return sumRed[h][w] - (sumRed[h][ul.first-1]+sumRed[ul.second-1][w]) + sumRed[ul.second-1][ul.first-1];
    } else if (channel == 'g') {
        return sumGreen[h][w] - (sumGreen[h][ul.first-1]+sumGreen[ul.second-1][w]) + sumGreen[ul.second-1][ul.first-1];
    } else if (channel == 'b') {
        return sumBlue[h][w] - (sumBlue[h][ul.first-1]+sumBlue[ul.second-1][w]) + sumBlue[ul.second-1][ul.first-1];
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
        return sumsqRed[h][w] - (sumsqRed[h][ul.first-1]+sumsqRed[ul.second-1][w]) + sumsqRed[ul.second-1][ul.first-1];
    } else if (channel == 'g') {
        return sumsqGreen[h][w] - (sumsqGreen[h][ul.first-1]+sumsqGreen[ul.second-1][w]) + sumsqGreen[ul.second-1][ul.first-1];
    } else if (channel == 'b') {
        return sumsqBlue[h][w] - (sumsqBlue[h][ul.first-1]+sumsqBlue[ul.second-1][w]) + sumsqBlue[ul.second-1][ul.first-1];
    }

    return (long)0;
}


// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int,int> ul, int w, int h){
    //int x = ul.first;
    //int y = ul.second;

    long area = w * h;
    if (area == 0) {
        return 0.0;
    }

    double rSSD = getSumSq('r', ul, w, h) - (getSum('r', ul, w, h) * getSum('r', ul, w, h)) / area;
    //cout << "rSSD: " << rSSD << endl;
    double gSSD = getSumSq('g', ul, w, h) - (getSum('g', ul, w, h) * getSum('g', ul, w, h)) / area;
    //cout << "gSSD: " << gSSD << endl;
    double bSSD = getSumSq('b', ul, w, h) - (getSum('b', ul, w, h) * getSum('b', ul, w, h)) / area;
    //cout << "bSSD: " << bSSD << endl;

    return rSSD + gSSD + bSSD;
    // return 0.0;
}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int w, int h){
    //int x = ul.first;
    //int y = ul.second;
    //double numPixels = (w - x + 1) * (h - y + 1);

    // w, h = 3 and ul = 0, 0: sumred[2][2]
    // w, h = 1 and ul = 0, 0: sumred[0][0]

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
    //return RGBAPixel(0,0,0);
}
